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

#include "R3BAsyKrabPhys.h"

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

R3BAsyKrabPhys::R3BAsyKrabPhys()
    : FairTask("AsyKrabPhys", 1)
    , fMappedItemsKrab(NULL)
    , fKrabPhysData(0)
    , fNEvents(0)
{
}

R3BAsyKrabPhys::R3BAsyKrabPhys(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMappedItemsKrab(NULL)
    , fKrabPhysData(0)
    , fNEvents(0)
{
}

R3BAsyKrabPhys::~R3BAsyKrabPhys()
{
    LOG(info) << "R3BAsyKrabPhys::Delete instance";
    if (fKrabPhysData)
        delete fKrabPhysData;
}

InitStatus R3BAsyKrabPhys::Init()
{
    LOG(info) << "R3BAsyKrabPhys::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyKrabPhys::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    if (verbose)
        LOG(info) << "R3BAsyKrabPhys::Init line 72";
    // Register output array in tree
    fKrabPhysData = new TClonesArray("R3BAsyKrabPhysData");
    FairRootManager::Instance()->Register("AsyKrabPhysData", "AsyKrab Phys data", fKrabPhysData, !fOnline);

    LOG(info) << "R3BAsyKrabDoArray::Init DONE";

    FairRunOnline* run = FairRunOnline::Instance();
    // for online server  run->GetHttpServer()->Register("", this);

    // Register command to reset histograms
    // for online server  run->GetHttpServer()->RegisterCommand("Reset_Krab",
    // Form("/Objects/%s/->Reset_Histo()", GetName()));

    // --- ------------------------------------- --- //
    // --- get access to mapped data of the TofW --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyKrabPhys::Init line 80";

    fMappedItemsKrab = (TClonesArray*)mgr->GetObject("AsyKrabMappedData");
    if (!fMappedItemsKrab)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyKrabPhys::Init line 87";

    c_KRAB_phys = new TCanvas("c_KRAB_phys", "KRAB_phys", 0, 0, 1200, 1200);
    fh1_KRAB_multi = new TH1I("fh1_KRAB_multi", "KRAB_multi", 200, -0.5, 99.5);
    fh1_KRAB_RP = new TH1F("fh1_KRAB_RP", "KRAB_RP", 200, -200, 200);
    c_KRAB_phys->Divide(2, 2);
    c_KRAB_phys->cd(1);
    fh1_KRAB_multi->Draw();
    c_KRAB_phys->cd(2);
    fh1_KRAB_RP->Draw();

    LOG(info) << "R3BAsyKrabPhys::Init DONE";
    return kSUCCESS;
}

void R3BAsyKrabPhys::Reset_Histo()
{
    LOG(info) << "R3BAsyKrabPhys::Reset_Histo";
    fh1_KRAB_multi->Reset();
    fh1_KRAB_RP->Reset();
}

void R3BAsyKrabPhys::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyKrabPhys::Exec FairRootManager not found";

    Int_t nHits;
    UShort_t multi = 0;
    Float_t KRABRP = -1000;
    Float_t QX = 0, QY = 0;

    UInt_t iRing, iSector;
    Float_t iPhi, iqx, iqy;

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
            iRing = hitmapped->GetRing();
            iSector = hitmapped->GetSector();
            iPhi = hitmapped->GetPhi();
            iqx = hitmapped->Getqx();
            iqy = hitmapped->Getqy();

            multi++;
            QX = QX + iqx;
            QY = QY + iqy;
        }
    }

    fh1_KRAB_multi->Fill(multi);
    if (multi >= 10)
    {
        KRABRP = atan2(QY, QX) * TMath::RadToDeg();
        fh1_KRAB_RP->Fill(KRABRP);
    }
    AddPhysData(multi, KRABRP);

    fNEvents += 1;
}

void R3BAsyKrabPhys::FinishEvent()
{
    if (fMappedItemsKrab)
    {
        fMappedItemsKrab->Clear();
    }
}

void R3BAsyKrabPhys::FinishTask()
{
    if (fMappedItemsKrab)
    {
        c_KRAB_phys->Update();
        c_KRAB_phys->Write();
    }
}

// -----   Private method AddHitData -------------------------------------------
R3BAsyKrabPhysData* R3BAsyKrabPhys::AddPhysData(Float_t multi, Float_t KRABRP)
{
    TClonesArray& clref = *fKrabPhysData;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BAsyKrabPhysData(multi, KRABRP);
}

ClassImp(R3BAsyKrabPhys)
