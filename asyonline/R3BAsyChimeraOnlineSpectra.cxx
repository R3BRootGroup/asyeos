// ------------------------------------------------------------
// -----              R3BAsyChimeraOnlineSpectra             -----
// -----           Fill SOFIA online histograms           -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with SOFIA online data
 */

#include "R3BAsyChimeraOnlineSpectra.h"

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

R3BAsyChimeraOnlineSpectra::R3BAsyChimeraOnlineSpectra()
    : FairTask("AsyChimeraOnlineSpectra", 1),
      fMappedItemsChimera(NULL),
      fNEvents(0) {}

R3BAsyChimeraOnlineSpectra::R3BAsyChimeraOnlineSpectra(const char* name,
                                                       Int_t iVerbose)
    : FairTask(name, iVerbose), fMappedItemsChimera(NULL), fNEvents(0) {}

R3BAsyChimeraOnlineSpectra::~R3BAsyChimeraOnlineSpectra() {
  LOG(info) << "R3BAsyChimeraOnlineSpectra::Delete instance";
  if (fMappedItemsChimera) delete fMappedItemsChimera;
}

InitStatus R3BAsyChimeraOnlineSpectra::Init() {
  LOG(info) << "R3BAsyChimeraOnlineSpectra::Init ";

  // try to get a handle on the EventHeader. EventHeader may not be
  // present though and hence may be null. Take care when using.

  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyChimeraOnlineSpectra::Init FairRootManager not found";
  // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

  if (verbose) LOG(info) << "R3BAsyChimeraOnlineSpectra::Init line 72";

  FairRunOnline* run = FairRunOnline::Instance();
  run->GetHttpServer()->Register("", this);

  // Register command to reset histograms
  // run->GetHttpServer()->RegisterCommand("Reset_Chimera",
  // Form("/Objects/%s/->Reset_Histo()", GetName()));

  // --- ------------------------------------- --- //
  // --- get access to mapped data of the TofW --- //
  // --- ------------------------------------- --- //
  if (verbose) LOG(info) << "R3BAsyChimeraOnlineSpectra::Init line 80";

  fMappedItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraMappedData");
  if (!fMappedItemsChimera) {
    //        return kFATAL;
  }
  if (verbose) LOG(info) << "R3BAsyChimeraOnlineSpectra::Init line 87";

  // --- ------------------------------- --- //
  // --- Create histograms for detectors --- //
  // --- ------------------------------- --- //

  char Name1[255];
  char Name2[255];
  char Name3[255];

  // Chimera/Farcos main folder
  TFolder* mainfol = new TFolder("Chimera", "Si Strips");
  TFolder* mapfol = new TFolder("Map", "Map Si Strips");
  mainfol->Add(mapfol);

  c_1_rawEnergy_front =
      new TCanvas("c_1_rawEnergy_front", "1_rawEnergy_front", 0, 0, 2400, 1200);
  c_1_rawEnergy_front->Divide(8, 4);
  c_1_rawTime_front =
      new TCanvas("c_1_rawTime_front", "1_rawTime_front", 0, 0, 2400, 1200);
  c_1_rawTime_front->Divide(8, 4);
  c_1_rawEnergy_vs_rawTime_front =
      new TCanvas("c_1_rawEnergy_vs_rawTime_front",
                  "1_rawEnergy_vs_rawTime_front", 0, 0, 2400, 1200);
  c_1_rawEnergy_vs_rawTime_front->Divide(8, 4);

  c_1_multi_front =
      new TCanvas("c_1_multi_front", "1_multi_front", 0, 0, 800, 800);
  c_1_multi_front->Divide(2, 2);
  mapfol->Add(c_1_multi_front);

  int nch = 500;
  int xymin = -0.5;
  int xymax = 4199.5;

  for (Int_t j = 0; j < Nstrips; j++) {
    sprintf(Name1, "AsyChimera_1_rawEnergy_front_%i", j);
    fh1_1_rawEnergy_front[j] = new TH1I(Name1, Name1, nch, xymin, xymax);
    fh1_1_rawEnergy_front[j]->GetXaxis()->SetTitle("raw Energy (ch)");
    fh1_1_rawEnergy_front[j]->GetYaxis()->SetTitle("Yield");
    c_1_rawEnergy_front->cd(j + 1);
    fh1_1_rawEnergy_front[j]->Draw();

    sprintf(Name2, "AsyChimera_1_rawTime_front_%i", j);
    fh1_1_rawTime_front[j] = new TH1I(Name2, Name2, nch, xymin, xymax);
    fh1_1_rawTime_front[j]->GetXaxis()->SetTitle("raw Time (ch)");
    fh1_1_rawTime_front[j]->GetYaxis()->SetTitle("Yield");
    c_1_rawTime_front->cd(j + 1);
    fh1_1_rawTime_front[j]->Draw();

    sprintf(Name3, "AsyChimera_1_rawEnergy_vs_rawTime_front_%i", j);
    fh2_1_rawEnergy_vs_rawTime_front[j] =
        new TH2F(Name3, Name3, nch, xymin, xymax, nch, xymin, xymax);
    fh2_1_rawEnergy_vs_rawTime_front[j]->GetXaxis()->SetTitle("raw Time (ch)");
    fh2_1_rawEnergy_vs_rawTime_front[j]->GetYaxis()->SetTitle(
        "raw Energy (ch)");
    c_1_rawEnergy_vs_rawTime_front->cd(j + 1);
    fh2_1_rawEnergy_vs_rawTime_front[j]->Draw("Zcol");
  }

  fh1_1_multi_front = new TH1I("AsyChimera_1_multi_front",
                               "AsyChimera_1_multi_front", 32, -0.5, 31.5);
  c_1_multi_front->cd(1);
  fh1_1_multi_front->Draw();

  run->AddObject(mainfol);
  LOG(info) << "R3BAsyChimeraOnlineSpectra::Init DONE";
  return kSUCCESS;
}

void R3BAsyChimeraOnlineSpectra::Reset_Histo() {
  LOG(info) << "R3BAsyChimeraOnlineSpectra::Reset_Histo";
  // reset mapped data (for defined spectra)
  for (Int_t i = 0; i < Nstrips; i++) {
    fh1_1_rawEnergy_front[i]->Reset();
    fh1_1_rawTime_front[i]->Reset();
    fh2_1_rawEnergy_vs_rawTime_front[i]->Reset();
  }
  // Multiplicity reset
  fh1_1_multi_front->Reset();
}

void R3BAsyChimeraOnlineSpectra::Exec(Option_t* option) {
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyChimeraOnlineSpectra::Exec FairRootManager not found";

  Int_t nHits;
  UShort_t iDet;
  UShort_t iSide;
  UShort_t iCh;
  UShort_t rawEnergy;
  UShort_t rawTime;
  UShort_t multi_front_1 = 0;

  if (fMappedItemsChimera && fMappedItemsChimera->GetEntriesFast()) {
    // --- --------------------- --- //
    // --- loop over mapped data --- //
    // --- --------------------- --- //
    nHits = fMappedItemsChimera->GetEntriesFast();
    for (Int_t ihit = 0; ihit < nHits; ihit++) {
      R3BAsyChimeraMappedData* hitmapped =
          (R3BAsyChimeraMappedData*)fMappedItemsChimera->At(ihit);
      if (!hitmapped) continue;
      iDet = hitmapped->GetDetectorId();
      iSide = hitmapped->GetSideId();
      iCh = hitmapped->GetStripId();
      rawEnergy = hitmapped->GetEnergy();
      rawTime = hitmapped->GetTime();
      // std::cout << iDet << " " << iSide << " " << iCh << std::endl;
      if (iDet == 1 && iSide == 1 && iCh < Nstrips) {
        if (rawEnergy > 0) fh1_1_rawEnergy_front[iCh]->Fill(rawEnergy);
        if (rawTime > 0) fh1_1_rawTime_front[iCh]->Fill(rawTime);
        if (rawEnergy > 0 && rawTime > 0) {
          fh2_1_rawEnergy_vs_rawTime_front[iCh]->Fill(rawTime, rawEnergy);
          multi_front_1++;
        }
      }
    }
  }
  fh1_1_multi_front->Fill(multi_front_1);

  fNEvents += 1;
}

void R3BAsyChimeraOnlineSpectra::FinishEvent() {
  if (fMappedItemsChimera) {
    fMappedItemsChimera->Clear();
  }
}

void R3BAsyChimeraOnlineSpectra::FinishTask() {
  LOG(info) << "Double click (somewhere) into c_1_rawEnergy_vs_rawTime_front "
               "canvas to terminate....";
  c_1_rawEnergy_vs_rawTime_front->WaitPrimitive();

  if (fMappedItemsChimera) {
    c_1_rawEnergy_front->Write();
    c_1_rawTime_front->Write();
    c_1_rawEnergy_vs_rawTime_front->Write();
    c_1_multi_front->Write();
  }
}
ClassImp(R3BAsyChimeraOnlineSpectra)
