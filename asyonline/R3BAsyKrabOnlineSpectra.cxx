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

#include "R3BAsyKrabOnlineSpectra.h"

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

R3BAsyKrabOnlineSpectra::R3BAsyKrabOnlineSpectra()
    : FairTask("AsyKrabOnlineSpectra", 1),
      fMappedItemsKrab(NULL),
      fNEvents(0) {}

R3BAsyKrabOnlineSpectra::R3BAsyKrabOnlineSpectra(const char* name,
                                                 Int_t iVerbose)
    : FairTask(name, iVerbose), fMappedItemsKrab(NULL), fNEvents(0) {}

R3BAsyKrabOnlineSpectra::~R3BAsyKrabOnlineSpectra() {
  LOG(info) << "R3BAsyKrabOnlineSpectra::Delete instance";
  if (fMappedItemsKrab) delete fMappedItemsKrab;
}

InitStatus R3BAsyKrabOnlineSpectra::Init() {
  LOG(info) << "R3BAsyKrabOnlineSpectra::Init ";

  // try to get a handle on the EventHeader. EventHeader may not be
  // present though and hence may be null. Take care when using.

  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyKrabOnlineSpectra::Init FairRootManager not found";
  // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

  if (verbose) LOG(info) << "R3BAsyKrabOnlineSpectra::Init line 72";

  FairRunOnline* run = FairRunOnline::Instance();
  // for online server  run->GetHttpServer()->Register("", this);

  // Register command to reset histograms
  // for online server  run->GetHttpServer()->RegisterCommand("Reset_Krab",
  // Form("/Objects/%s/->Reset_Histo()", GetName()));

  // --- ------------------------------------- --- //
  // --- get access to mapped data of KRAB --- //
  // --- ------------------------------------- --- //
  if (verbose) LOG(info) << "R3BAsyKrabOnlineSpectra::Init line 80";

  fMappedItemsKrab = (TClonesArray*)mgr->GetObject("AsyKrabMappedData");
  if (!fMappedItemsKrab) {
    //        return kFATAL;
  }
  if (verbose) LOG(info) << "R3BAsyKrabOnlineSpectra::Init line 87";

  // --- ------------------------------- --- //
  // --- Create histograms for detectors --- //
  // --- ------------------------------- --- //

  char Name1[255];
  char Name2[255];

  c_KRAB_rings = new TCanvas("c_KRAB_rings", "KRAB_rings", 0, 0, 1200, 1200);
  c_KRAB_rings->Divide(2, 3);

  c_KRAB_multi = new TCanvas("c_KRAB_multi", "KRAB_multi", 0, 0, 1200, 1200);
  c_KRAB_multi->Divide(2, 3);
  fh1_KRAB_multi = new TH1I("fh1_KRAB_multi", "KRAB_multi", 200, -0.5, 199.5);
  c_KRAB_multi->cd(1);
  fh1_KRAB_multi->Draw();

  int nch = 1000;
  int xymin = -0.5;
  int xymax = 999.5;

  for (Int_t j = 0; j < 5; j++) {
    sprintf(Name1, "Krab_ring_%i", j);
    fh1_KRAB_ring[j] = new TH1I(Name1, Name1, nch, xymin, xymax);
    fh1_KRAB_ring[j]->GetXaxis()->SetTitle("sector (ch)");
    fh1_KRAB_ring[j]->GetYaxis()->SetTitle("Yield");
    c_KRAB_rings->cd(j + 1);
    fh1_KRAB_ring[j]->Draw();
  }

  nch = 200;
  xymin = -0.5;
  xymax = 199.5;

  for (Int_t j = 0; j < 5; j++) {
    sprintf(Name1, "Krab_multi_ring_%i", j);
    fh1_KRAB_multi_ring[j] = new TH1I(Name1, Name1, nch, xymin, xymax);
    fh1_KRAB_multi_ring[j]->GetXaxis()->SetTitle("multi");
    fh1_KRAB_multi_ring[j]->GetYaxis()->SetTitle("Yield");
    c_KRAB_multi->cd(j + 2);
    fh1_KRAB_multi_ring[j]->Draw();
  }

  /*
    // KRAB main folder
    TFolder* mainfol = new TFolder("KRAB", "KRAB rings");
    TFolder* mapfol = new TFolder("Map", "Map KRAB");
    mainfol->Add(mapfol);
    run->AddObject(mainfol);
  */

  LOG(info) << "R3BAsyKrabOnlineSpectra::Init DONE";
  return kSUCCESS;
}

void R3BAsyKrabOnlineSpectra::Reset_Histo() {
  LOG(info) << "R3BAsyKrabOnlineSpectra::Reset_Histo";
  // reset mapped data (for defined spectra)

  for (Int_t i = 0; i < 5; i++) {
    fh1_KRAB_ring[i]->Reset();
    fh1_KRAB_multi_ring[i]->Reset();
  }
  fh1_KRAB_multi->Reset();
}

void R3BAsyKrabOnlineSpectra::Exec(Option_t* option) {
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyKrabOnlineSpectra::Exec FairRootManager not found";

  Int_t nHits;
  UShort_t multi = 0, multiR[5] = {0, 0, 0, 0, 0};

  UInt_t iRing, iSector;
  Float_t iPhi, iqx, iqy;

  if (fMappedItemsKrab && fMappedItemsKrab->GetEntriesFast()) {
    // --- --------------------- --- //
    // --- loop over mapped data --- //
    // --- --------------------- --- //
    nHits = fMappedItemsKrab->GetEntriesFast();
    int time_trig = 0;
    int time1 = 0;
    for (Int_t ihit = 0; ihit < nHits; ihit++) {
      R3BAsyKrabMappedData* hitmapped =
          (R3BAsyKrabMappedData*)fMappedItemsKrab->At(ihit);
      if (!hitmapped) continue;
      iRing = hitmapped->GetRing();
      iSector = hitmapped->GetSector();
      iPhi = hitmapped->GetPhi();
      iqx = hitmapped->Getqx();
      iqy = hitmapped->Getqx();
      multi++;
      for (int i = 0; i < 5; i++) {
        if (i == iRing) {
          multiR[i]++;
          fh1_KRAB_ring[i]->Fill(iSector);
        }
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    fh1_KRAB_multi_ring[i]->Fill(multiR[i]);
  }

  fh1_KRAB_multi->Fill(multi);

  fNEvents += 1;
}

void R3BAsyKrabOnlineSpectra::FinishEvent() {
  if (fMappedItemsKrab) {
    fMappedItemsKrab->Clear();
  }
}

void R3BAsyKrabOnlineSpectra::FinishTask() {
  if (fMappedItemsKrab) {
    c_KRAB_rings->Update();
    c_KRAB_multi->Update();

    c_KRAB_rings->Write();
    c_KRAB_multi->Write();
  }
}
ClassImp(R3BAsyKrabOnlineSpectra)
