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

#include "R3BAsyChimeraId.h"

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
const Float_t delta_phi[35] = { 22.5,  22.5,  15.,   15.,   11.25, 11.25, 9.,    9.,    9.,    9.,    7.5,   7.5,
                                7.5,   7.5,   7.5,   7.5,   7.5,   7.5,   11.25, 11.25, 11.25, 11.25, 11.25, 11.25,
                                11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 22.5,  45.0 };

R3BAsyChimeraId::R3BAsyChimeraId(const char* inFileName)
    : FairTask("AsyChimeraId", 1)
    , fChimeraMatchedData(0)
    , fChimeraIdData(0)
    , fNEvents(0)
    , finFileName(inFileName)

{
}

R3BAsyChimeraId::~R3BAsyChimeraId()
{
    LOG(info) << "R3BAsyChimeraId::Delete instance";
    if (fChimeraIdData)
        delete fChimeraIdData;
}

InitStatus R3BAsyChimeraId::Init()
{
    LOG(info) << "R3BAsyChimeraId::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraId::Init FairRootManager not found";

    header = dynamic_cast<R3BEventHeader*>(mgr->GetObject("EventHeader."));
    R3BLOG_IF(error, header == nullptr, "EventHeader. not found");

    if (verbose)
        LOG(info) << "R3BAsyChimeraId::Init line 72";
    // Register output array in tree
    fChimeraIdData = new TClonesArray("R3BAsyChimeraIdData");
    FairRootManager::Instance()->Register("AsyChimeraIdData", "AsyChimera Id data", fChimeraIdData, !fOnline);

    LOG(info) << "R3BAsyChimeraId::Init DONE";

    FairRunOnline* run = FairRunOnline::Instance();
    UInt_t Nrun = run->getRunId();

    // --- ------------------------------------- --- //
    // --- get access to matched data of Chimera --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraId::Init line 80";

    fChimeraMatchedData = (TClonesArray*)mgr->GetObject("AsyChimeraMatchedData");
    if (!fChimeraMatchedData)
    {
        LOG(info) << "R3BAsyChimeraId:: fChimeraMatchedData not found";
        getchar();
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyChimeraId::Init line 87";

    LOG(info) << "R3BAsyChimeraId::Init DONE";
    //    getchar();
    //**********************************************************************************

    string dir = "/u/russotto/R3BRoot/calfiles";
    string filename = "grid.asc";
    int nrun = 1;

    string chiecalib = "ecalib141111.txt";

    string chiecalibrec = "dee-16072025.txt";

    fCsIIdent = new TCsIIdent(CalDirName, GridFileName, nrun);
    fCsIIdent->ReadAsciiFile();

    fCHICsIEnergy = new TCHICsIGSIEnergy(ECalibFileName, ECalibTableFileName, CalDirName);
    fCHICsIEnergy->Init();
    fCHICsIEnergy->Set_optZ2(opt_Z2);

    fCHIResult = new TCHIResult();

    rrn = new TRandom();

    cc = new TCanvas("cc", "cc", 800, 800);
    h2_ylab_bt = new TH2F("h2_ylab_bt", "ylab_bt", 500, -0.5, 1.5, 500, 0, 2);
    cc->cd(1);
    h2_ylab_bt->Draw("ZCol");

    f1 = new TFile("my_output.root", "RECREATE");
    f1->cd();

    evt = 0;
    ostringstream os;
    os << "Id_run" << Nrun << ".root";
    chitree.Open(os.str().c_str());
    chitree.GetTree()->SetTitle("AsyEos beam");
    evt = chitree.GetCHIEvt();
    //**********************************************************************************
    return kSUCCESS;
}

void R3BAsyChimeraId::Reset_Histo() { LOG(info) << "R3BAsyChimeraId::Reset_Histo"; }

void R3BAsyChimeraId::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraId::Exec FairRootManager not found";

    if ((fTrigger >= 0) && (header) && (header->GetTrigger() != fTrigger))
        return;

    Int_t trig = -1000;

    trig = header->GetTrigger();

    int tpatvalue = -1000;
    int itpat = -1000;
    int fTpat_bit = fTpat - 1;

    if (fTpat_bit >= 0)
    {
        itpat = header->GetTpat();
        tpatvalue = (itpat & (1 << fTpat_bit)) >> fTpat_bit;
        if ((header) && (tpatvalue == 0))
            return;
    }

    if (trig == 1 && tpatvalue)
    {

        Int_t nHits;

        UInt_t NumTel, TimeCsI;

        Float_t Fast, Slow;

        Float_t tave = 1000;

        if (fChimeraMatchedData && fChimeraMatchedData->GetEntriesFast())
        {
            // --- --------------------- --- //
            // --- loop over matched data --- //
            // --- --------------------- --- //
            nHits = fChimeraMatchedData->GetEntriesFast();

            //	std::cout <<  nHits << std::endl;

            Int_t num = 0;
            evt->tavecsi = -100;

            for (Int_t ihit = 0; ihit < nHits; ihit++)

            {
                Fast = -1, Slow = -1;
                R3BAsyChimeraMatchedData* hitmatched = (R3BAsyChimeraMatchedData*)fChimeraMatchedData->At(ihit);
                if (!hitmatched)
                    continue;
                NumTel = hitmatched->GetNumTel();
                Fast = hitmatched->GetFast();
                Slow = hitmatched->GetSlow();
                TimeCsI = hitmatched->GetTimeCsI();

                fCsIIdent->CsI_Identification(NumTel, Fast, Slow, fCHIResult, tave);

                UInt_t IdNumTel = NumTel;

                fCHICsIEnergy->EvalEnergy(NumTel, Fast, Slow, fCHIResult);
                double DE = fCHICsIEnergy->GetDE();
                double Energy = fCHICsIEnergy->GetEnergy();

                Int_t Z = fCHIResult->GetZ();
                Int_t A = fCHIResult->GetA();
                Int_t Stopped = fCHIResult->GetIfStopped();
                Int_t Icod = fCHIResult->GetIcod();
                Float_t PID = fCHIResult->GetPID();
                bool IDOK = fCHIResult->GetIDOK();
                bool Zident = fCHIResult->GetZident();
                bool Aident = fCHIResult->GetAident();

                //	    if(NumTel== 371) std::cout <<" R3BAsyChimeraId::ntel=371 " <<  Fast << " " << Slow << " "  <<
                // fCHIResult->GetZ() << " " << fCHIResult->GetA() << std::endl;

                if (NumTel >= 80 && NumTel <= 399 && fCsIIdent->IsGridExisting(NumTel))
                {
                    AddIdData(NumTel, Fast, Slow, TimeCsI, Z, A, Stopped, Icod, PID, DE, Energy);
                    //                    std::cout << "R3BAsyChimeraID" << endl;
                    //                    std::cout << num  << " " << NumTel << " " << Z << " " << A << " " << Energy <<
                    //                    std::endl;

                    if (Icod < 10)
                    {
                        evt->IdA[num] = A;
                        evt->Idcode[num] = Icod;
                        evt->IdPID[num] = PID;
                        evt->IdE[num] = Energy;
                        evt->IdDE[num] = DE;
                        evt->IdZ[num] = Z;
                        evt->Idnumtel[num] = NumTel;
                        evt->Idstopped[num] = Stopped;
                        evt->fast[num] = Fast;
                        evt->slow[num] = Slow;
                        //	      cout << num << " *** " << evt->IdA[num] << " " << A << endl;
                        //                        if(NumTel == 95) cout <<"R3BAsyChimeraId:: " <<  DE << " " << Fast <<
                        //                        endl;
                        num++;
                    }
                    //              cout  << Z << " " << A << " " << Icod << " " << PID << " " << Fast << " " << NumTel
                    //              << endl;

                    float EsuA = Energy / A;
                    if (Icod >= 0 && Icod <= 5 && EsuA > 20 && EsuA < 1000 && Z >= 1)
                    {
                        float EKin = Energy * 1.0;
                        float ETot = EKin + 939 * A;
                        float gamma = ETot / (939 * A);
                        float gamma2 = gamma * gamma;
                        float beta = sqrt((gamma2 - 1) / gamma2);
                        //              cout << EKin << " " << ETot << " " << gamma << " " << beta << " " << Z << " " <<
                        //              A << endl;
                        //	      cout << NumTel << " " << theta << endl;
                        gamma = 1 / sqrt(1 - beta * beta);
                        float theta = GetThetaRnd(NumTel);
                        float bz = beta * cos(theta * TMath::DegToRad());
                        float bt = beta * sin(theta * TMath::DegToRad());
                        float gammabt = gamma * bt;
                        float ylab = 0.5 * TMath::Log((1 + bz) / (1 - bz));
                        //	      cout << EKin << " " << ETot << " " << gamma << " " << beta << " " << ylab << " " <<
                        // gammabt << endl;
                        h2_ylab_bt->Fill(ylab, gammabt);
                    }
                }
                fCHIResult->SetZ(-10);
            }
            evt->Idmulti = num;
            //            chitree.GetTree()->Fill();
        }
        //        getchar();

        fNEvents += 1;
    }
}

void R3BAsyChimeraId::FinishEvent()
{
    if (fChimeraMatchedData)
    {
        fChimeraMatchedData->Clear();
    }
    if (fChimeraIdData)
    {
        fChimeraIdData->Clear();
    }
}

void R3BAsyChimeraId::FinishTask()
{
    if (fChimeraMatchedData)
    {
    }
    if (fChimeraIdData)
    {
        cc->Update(), cc->Write();
        h2_ylab_bt->Write();
    }
    chitree.Close();
}

Float_t R3BAsyChimeraId::GetThetaRnd(int numtel)
{
    float xrn = (float)rrn->Rndm();
    float thr = -1000.0;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
            float theta = (thetamin[i] + thetamax[i]) / 2;
            thr = xrn * (thetamax[i] - thetamin[i]) + thetamin[i];
        }
    }
    return thr;
}

Float_t R3BAsyChimeraId::GetPhiRnd(int numtel)
{
    float xrn = (float)rrn->Rndm();
    float phir = -1000;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
            float phi = ((numtel - telmin[i]) * 360. / (telmax[i] - telmin[i] + 1)) + 90.0;
            float dphi = delta_phi[i];
            phir = (0.5 - xrn) * dphi + phi;
            if (phir < 0)
                phir += 360.0;
            // if(numtel>=80 && numtel<=90)std::cout << numtel << " " << phi << " " <<phir<< std::endl;
        }
    }
    return phir;
}

// -----   Private method AddHitData -------------------------------------------

R3BAsyChimeraIdData* R3BAsyChimeraId::AddIdData(UInt_t numtel,
                                                Float_t fast,
                                                Float_t slow,
                                                UInt_t time,
                                                Int_t Z,
                                                Int_t A,
                                                Int_t Stopped,
                                                Int_t Code,
                                                Float_t PID,
                                                double DE,
                                                double Energy)
{
    TClonesArray& clref = *fChimeraIdData;
    Int_t size = clref.GetEntriesFast();
    //    std::cout << "Added....numtel=" << numtel << std::endl;
    return new (clref[size]) R3BAsyChimeraIdData(numtel, fast, slow, time, Z, A, Stopped, Code, PID, DE, Energy);
}

ClassImp(R3BAsyChimeraId)
