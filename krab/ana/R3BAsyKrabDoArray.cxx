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

#include "R3BAsyKrabDoArray.h"

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
#include "R3BAsyKrabArrayData.h"
#include "R3BAsyKrabMappedData.h"
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

R3BAsyKrabDoArray::R3BAsyKrabDoArray()
    : FairTask("AsyKrabDoArray", 1)
    , fMappedItemsKrab(NULL)
    , fKrabArrayData(0)
    , fNEvents(0)
    , iMulti(0)
    , iRP(-1000)
{
    iRing = new UInt_t[dmaxKrab];
    iSector = new UInt_t[dmaxKrab];
    iPhi = new float_t[dmaxKrab];
}

R3BAsyKrabDoArray::R3BAsyKrabDoArray(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMappedItemsKrab(NULL)
    , fKrabArrayData(0)
    , fNEvents(0)
    , iMulti(0)
    , iRP(-1000)
{
    iRing = new UInt_t[dmaxKrab];
    iSector = new UInt_t[dmaxKrab];
    iPhi = new Float_t[dmaxKrab];
}

R3BAsyKrabDoArray::~R3BAsyKrabDoArray()
{
    LOG(info) << "R3BAsyKrabDoArray::Delete instance";
    if (fKrabArrayData)
    {
        delete fKrabArrayData;
    }
}

InitStatus R3BAsyKrabDoArray::Init()
{
    LOG(info) << "R3BAsyKrabDoArray::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyKrabDoArray::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    if (verbose)
        LOG(info) << "R3BAsyKrabDoArray::Init line 72";

    // --- ------------------------------------- --- //
    // --- get access to mapped data of KRAB     --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyKrabDoArray::Init line 80";

    fMappedItemsKrab = (TClonesArray*)mgr->GetObject("AsyKrabMappedData");
    if (!fMappedItemsKrab)
    {
        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyKrabDoArray::Init line 87";

    // Register output array in tree
    fKrabArrayData = new TClonesArray("R3BAsyKrabArrayData");
    FairRootManager::Instance()->Register("KrabArrayData", "AsyKrab Array data", fKrabArrayData, !fOnline);

    LOG(info) << "R3BAsyKrabDoArray::Init DONE";
    nn = 0;
    rr = new TRandom();
    fh1_DRP12_mgt10 = new TH1F("fh1_DRP12_mgt10", "DRP12_mgt10", 60, -360., 360.);
    fh1_DRP12_mgt20 = new TH1F("fh1_DRP12_mgt20", "DRP12_mgt20", 60, -360., 360.);
    fh1_DRP12_mgt40 = new TH1F("fh1_DRP12_mgt40", "DRP12_mgt40", 60, -360., 360.);
    c_DRP12_mgt10 = new TCanvas("c_DRP12_mgt10", "DRP12_mgt10", 800, 800);
    c_DRP12_mgt10->Draw();
    c_DRP12_mgt10->Divide(2, 2);
    c_DRP12_mgt10->cd(1);
    fh1_DRP12_mgt10->Draw();
    c_DRP12_mgt10->cd(2);
    fh1_DRP12_mgt20->Draw();
    c_DRP12_mgt10->cd(3);
    fh1_DRP12_mgt40->Draw();
    return kSUCCESS;
}

void R3BAsyKrabDoArray::Exec(Option_t* option)
{
    Reset();
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyKrabDoArray::Exec FairRootManager not found";
    Int_t nHits;
    iMulti = 0;
    Int_t iMulti1 = 0, iMulti2 = 0;
    Double_t iRP1 = -1000, iRP2 = -1000, DRP12 = -1000;
    float Qx = 0;
    float Qy = 0;
    float Qx1 = 0;
    float Qy1 = 0;
    float Qx2 = 0;
    float Qy2 = 0;

    if (fMappedItemsKrab && fMappedItemsKrab->GetEntriesFast())
    {
        // --- --------------------- --- //
        // --- loop over mapped data --- //
        // --- --------------------- --- //
        nHits = fMappedItemsKrab->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            R3BAsyKrabMappedData* hitmapped = (R3BAsyKrabMappedData*)fMappedItemsKrab->At(ihit);
            if (!hitmapped)
                continue;
            if (hitmapped->GetRing() >= 0 && hitmapped->GetSector() >= 0)
            {
                iRing[iMulti] = hitmapped->GetRing();
                iSector[iMulti] = hitmapped->GetSector();
                iPhi[iMulti] = hitmapped->GetPhi();
                Qx = Qx + hitmapped->Getqx();
                Qy = Qy + hitmapped->Getqy();
                Double_t rrr = rr->Uniform();
                if (iMulti1 >= nHits / 2)
                    rrr = 0.25;
                if (iMulti2 >= nHits / 2)
                    rrr = 0.75;
                //	std::cout << ihit << " " << iMulti1 << " " << iMulti2 << " " <<
                // nHits/2 << " " << rrr << std::endl;
                if (rrr > 0.5)
                {
                    Qx1 = Qx1 + hitmapped->Getqx();
                    Qy1 = Qy1 + hitmapped->Getqy();
                    iMulti1++;
                }
                else
                {
                    Qx2 = Qx2 + hitmapped->Getqx();
                    Qy2 = Qy2 + hitmapped->Getqy();
                    iMulti2++;
                }
                iMulti++;
            }
        }
    }
    /*
      std::cout << "-----------------------------------" << std::endl;
      std::cout << "-----------------------------------" << std::endl;
      std::cout << "-----------------------------------" << std::endl;
      getchar();
    */
    if (iMulti > 1)
    {
        iRP = TMath::ATan2(Qy, Qx) * TMath::RadToDeg();
        if (verbose)
            std::cout << " iRP= " << iRP << std::endl;
        AddHitData(iMulti, iRP, iRing, iSector, iPhi);
    }
    else
    {
        iRP = -1000;
        AddHitData(0, iRP, 0, 0, 0);
    }
    if (iMulti >= 10)
    {
        iRP1 = TMath::ATan2(Qy1, Qx1) * TMath::RadToDeg();
        iRP2 = TMath::ATan2(Qy2, Qx2) * TMath::RadToDeg();
        DRP12 = iRP1 - iRP2;
        if (DRP12 < -180)
            DRP12 = DRP12 + 360;
        if (DRP12 > 180)
            DRP12 = DRP12 - 360;
        fh1_DRP12_mgt10->Fill(DRP12);
        if (iMulti >= 20)
            fh1_DRP12_mgt20->Fill(DRP12);
        if (iMulti >= 40)
            fh1_DRP12_mgt40->Fill(DRP12);
        // std::cout << iMulti1 << "  $$$  " << iMulti2 << std::endl;
    }

    if (verbose)
        std::cout << "R3BAsyKrabDoArray: ** " << nn << " " << iMulti << std::endl;

    nn++;
    if (verbose)
        LOG(info) << "R3BAsyKrabDoArray: " << fKrabArrayData->GetEntriesFast() << " points registered in this event";
}

void R3BAsyKrabDoArray::Reset()
{
    // Reset the output array
    if (fKrabArrayData)
    {
        fKrabArrayData->Clear();
    }
}

void R3BAsyKrabDoArray::FinishTask()
{
    fh1_DRP12_mgt10->Fit("gaus", "", "", -90., 90.);
    fh1_DRP12_mgt10->Write();
    fh1_DRP12_mgt20->Write();
    fh1_DRP12_mgt40->Write();
}

// -----   Private method AddHitData -------------------------------------------
R3BAsyKrabArrayData* R3BAsyKrabDoArray::AddHitData(UInt_t Multi,
                                                   Double_t RP,
                                                   UInt_t* Ring,
                                                   UInt_t* Sector,
                                                   Float_t* Phi)
{
    TClonesArray& clref = *fKrabArrayData;
    Int_t size = clref.GetEntriesFast();
    if (verbose)
        LOG(info) << "Add Hit Data....";
    return new (clref[size]) R3BAsyKrabArrayData(Multi, RP, Ring, Sector, Phi);
}

ClassImp(R3BAsyKrabDoArray)
