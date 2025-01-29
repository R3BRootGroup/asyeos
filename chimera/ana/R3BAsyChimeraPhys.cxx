/******************************************************************************
 *   Copyright (C) 2022 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2022-2025 Members of R3B Collaboration                     *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU Lesser General Public Licence (LGPL) version 3,        *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

#include "R3BAsyChimeraPhys.h"

#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "R3BAsyChimeraMappedData.h"
#include "R3BEventHeader.h"
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include "THttpServer.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TRandom.h"
#include "TVector3.h"

#define verbose 0

const Float_t thetamin[35] = { 1.,    1.80,  2.60,  3.60,  4.60,  5.80,  7.00, 8.50, 10.00, 11.50, 13.00, 14.50,
                               16.00, 18.00, 20.00, 22.00, 24.00, 27.00, 30.,  38.,  46.,   54.,   62.,   70.,
                               78.,   86.,   94.,   102.,  110.,  118.,  126., 134., 142.,  150.,  163. };
const Float_t thetamax[35] = { 1.80,  2.60,  3.60,  4.60,  5.80,  7.00, 8.50, 10.00, 11.50, 13.00, 14.50, 16.00,
                               18.00, 20.00, 22.00, 24.00, 27.00, 30.,  38.,  46.,   54.,   62.,   70.,   78.,
                               86.,   94.,   102.,  110.,  118.,  126., 134., 142.,  150.,  163.,  176. };
const Int_t telmin[35] = { 0,   16,  32,  56,  80,   112,  144,  184,  224,  264,  304, 352,
                           400, 448, 496, 544, 592,  640,  688,  720,  752,  784,  816, 848,
                           880, 912, 944, 976, 1008, 1040, 1072, 1104, 1136, 1168, 1184 };
const Int_t telmax[35] = { 15,  31,  55,  79,   111,  143,  183,  223,  263,  303,  351, 399,
                           447, 495, 543, 591,  639,  687,  719,  751,  783,  815,  847, 879,
                           911, 943, 975, 1007, 1039, 1071, 1103, 1135, 1167, 1183, 1191 };

R3BAsyChimeraPhys::R3BAsyChimeraPhys()
    : FairTask("AsyChimeraPhys", 1)
    , fMappedItemsChimera(NULL)
    , fChimeraPhysData(0)
    , fNEvents(0)
{
}

R3BAsyChimeraPhys::R3BAsyChimeraPhys(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMappedItemsChimera(NULL)
    , fChimeraPhysData(0)
    , fNEvents(0)
{
}

R3BAsyChimeraPhys::~R3BAsyChimeraPhys()
{
    LOG(info) << "R3BAsyChimeraPhys::Delete instance";
    if (fChimeraPhysData)
        delete fChimeraPhysData;
}

InitStatus R3BAsyChimeraPhys::Init()
{
    LOG(info) << "R3BAsyChimeraPhys::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraPhys::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    if (verbose)
        LOG(info) << "R3BAsyChimeraPhys::Init line 72";
    // Register output array in tree
    fChimeraPhysData = new TClonesArray("R3BAsyChimeraPhysData");
    FairRootManager::Instance()->Register("AsyChimeraPhysData", "AsyChimera Phys data", fChimeraPhysData, !fOnline);

    LOG(info) << "R3BAsyChimeraPhys::Init DONE";

    FairRunOnline* run = FairRunOnline::Instance();
    // for online server  run->GetHttpServer()->Register("", this);

    // Register command to reset histograms
    // for online server  run->GetHttpServer()->RegisterCommand("Reset_Chimera",
    // Form("/Objects/%s/->Reset_Histo()", GetName()));

    // --- ------------------------------------- --- //
    // --- get access to mapped data of the TofW --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraPhys::Init line 80";

    fMappedItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraMappedData");
    if (!fMappedItemsChimera)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyChimeraPhys::Init line 87";

    c_CHIMERA_phys = new TCanvas("c_CHIMERA_phys", "CHIMERA_phys", 0, 0, 1200, 1200);
    fh1_CHIMERA_multi = new TH1I("fh1_CHIMERA_multi", "CHIMERA_multi", 100, -0.5, 99.5);
    fh1_CHIMERA_RP = new TH1F("fh1_CHIMERA_RP", "CHIMERA_RP", 200, -200, 200);
    fh1_CHIMERA_RP12 = new TH1F("fh1_CHIMERA_RP12", "CHIMERA_RP12", 400, -400, 400);
    c_CHIMERA_phys->Divide(2, 2);
    c_CHIMERA_phys->cd(1);
    fh1_CHIMERA_multi->Draw();
    c_CHIMERA_phys->cd(2);
    fh1_CHIMERA_RP->Draw();
    c_CHIMERA_phys->cd(3);
    fh1_CHIMERA_RP12->Draw();

    rr = new TRandom();

    LOG(info) << "R3BAsyChimeraPhys::Init DONE";
    return kSUCCESS;
}

void R3BAsyChimeraPhys::Reset_Histo()
{
    LOG(info) << "R3BAsyChimeraPhys::Reset_Histo";
    fh1_CHIMERA_multi->Reset();
    fh1_CHIMERA_RP->Reset();
    fh1_CHIMERA_RP12->Reset();
}

void R3BAsyChimeraPhys::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraPhys::Exec FairRootManager not found";

    Int_t nHits;
    UShort_t multi = 0, multi1 = 0, multi2 = 0;
    Float_t CHIRP = -1000, CHIRP1 = -2000, CHIRP2 = -3000;
    Float_t QX = 0, QY = 0;
    Float_t Q1X = 0, Q1Y = 0;
    Float_t Q2X = 0, Q2Y = 0;

    UShort_t iNumTel, iFastHG, iFastLG, iSlowHG, iSlowLG, iTimeCsI, iSilHG, iSilLG, iTimeSil, iPatt;

    if (fMappedItemsChimera && fMappedItemsChimera->GetEntriesFast())
    {
        // --- --------------------- --- //
        // --- loop over mapped data --- //
        // --- --------------------- --- //
        nHits = fMappedItemsChimera->GetEntriesFast();
        int time_trig = 0;
        int time1 = 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            R3BAsyChimeraMappedData* hitmapped = (R3BAsyChimeraMappedData*)fMappedItemsChimera->At(ihit);
            if (!hitmapped)
                continue;
            iNumTel = hitmapped->GetNumTel();
            iFastHG = hitmapped->GetFastHG();
            iFastLG = hitmapped->GetFastLG();
            iSlowHG = hitmapped->GetSlowHG();
            iSlowLG = hitmapped->GetSlowLG();
            iTimeCsI = hitmapped->GetTimeCsI();
            iSilHG = hitmapped->GetSilHG();
            iSilLG = hitmapped->GetSilLG();
            iTimeSil = hitmapped->GetTimeSil();
            iPatt = hitmapped->GetPatt();

            if (iFastLG > 0 && iTimeCsI > 0)
            {
                multi++;
                Float_t phi = GetPhi(iNumTel);
                Float_t theta = GetTheta(iNumTel);
                Float_t qx = sin(theta * TMath::DegToRad()) * cos(phi * TMath::DegToRad());
                Float_t qy = sin(theta * TMath::DegToRad()) * sin(phi * TMath::DegToRad());

//                std::cout << "#####  " << iNumTel << " " << theta << " "
//                          << " " << phi << std::endl;
//                getchar();
                QX = QX + qx;
                QY = QY + qy;
                Float_t rrr = rr->Uniform();
                if (rrr > 0.5)
                {
                    Q1X = Q1X + qx;
                    Q1Y = Q1Y + qy;
                    multi1++;
                }
                else
                {
                    Q2X = Q2X + qx;
                    Q2Y = Q2Y + qy;
                    multi2++;
                }
            }
        }
    }

    UShort_t dmulti12 = TMath::Abs(multi1 - multi2);
    Float_t dmm = 1.0 * dmulti12 / multi;

    CHIRP = atan2(QY, QX) * TMath::RadToDeg();
    CHIRP1 = atan2(Q1Y, Q1X) * TMath::RadToDeg();
    CHIRP2 = atan2(Q2Y, Q2X) * TMath::RadToDeg();
    Float_t DCHIRP12 = CHIRP1 - CHIRP2;

    fh1_CHIMERA_multi->Fill(multi);
    if (multi >= 8)
    {
        fh1_CHIMERA_RP->Fill(CHIRP);
        if (dmm < 0.33333)
            fh1_CHIMERA_RP12->Fill(DCHIRP12);
        AddPhysData(multi, CHIRP);
    }
    fNEvents += 1;
}

void R3BAsyChimeraPhys::FinishEvent()
{
    if (fMappedItemsChimera)
    {
        fMappedItemsChimera->Clear();
    }
}

void R3BAsyChimeraPhys::FinishTask()
{
    if (fMappedItemsChimera)
    {
        c_CHIMERA_phys->Update();
        c_CHIMERA_phys->Write();
    }
}

Float_t R3BAsyChimeraPhys::GetTheta(int numtel)
{
    float theta = -1;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
//            std::cout << "------ " << thetamin[i] << " " << thetamax[i] << std::endl;
            theta = (thetamin[i] + thetamax[i]) / 2;
        }
    }
    return theta;
}

Float_t R3BAsyChimeraPhys::GetPhi(int numtel)
{
    float phi = -1000;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
            phi = (numtel - telmin[i]) * 360 / (telmax[i] - telmin[i] + 1);
        }
    }
    return phi;
}

// -----   Private method AddHitData -------------------------------------------
R3BAsyChimeraPhysData* R3BAsyChimeraPhys::AddPhysData(Float_t multi, Float_t CHIRP)
{
    TClonesArray& clref = *fChimeraPhysData;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BAsyChimeraPhysData(multi, CHIRP);
}

ClassImp(R3BAsyChimeraPhys)
