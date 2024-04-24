// --------------------------------------------------------------------------
// -----            R3BAsyChimeraOnlineSpectra source file             ------
// --------------------------------------------------------------------------

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
  run->GetHttpServer()->RegisterCommand(
      "Reset_Chimera", Form("/Objects/%s/->Reset_Histo()", GetName()));

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
  char Name4[255];
  char Name5[255];
  char Name6[255];
  char Name7[255];
  char Name8[255];
  char Name9[255];
  char Name10[255];

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

  c_1_rawEnergy_back =
      new TCanvas("c_1_rawEnergy_back", "1_rawEnergy_back", 0, 0, 2400, 1200);
  c_1_rawEnergy_back->Divide(8, 4);
  c_1_rawTime_back =
      new TCanvas("c_1_rawTime_back", "1_rawTime_back", 0, 0, 2400, 1200);
  c_1_rawTime_back->Divide(8, 4);
  c_1_rawEnergy_vs_rawTime_back =
      new TCanvas("c_1_rawEnergy_vs_rawTime_back",
                  "1_rawEnergy_vs_rawTime_back", 0, 0, 2400, 1200);
  c_1_rawEnergy_vs_rawTime_back->Divide(8, 4);

  c_2_rawEnergy_front =
      new TCanvas("c_2_rawEnergy_front", "2_rawEnergy_front", 0, 0, 2400, 1200);
  c_2_rawEnergy_front->Divide(8, 4);
  c_2_rawTime_front =
      new TCanvas("c_2_rawTime_front", "2_rawTime_front", 0, 0, 2400, 1200);
  c_2_rawTime_front->Divide(8, 4);
  c_2_rawEnergy_vs_rawTime_front =
      new TCanvas("c_2_rawEnergy_vs_rawTime_front",
                  "2_rawEnergy_vs_rawTime_front", 0, 0, 2400, 1200);
  c_2_rawEnergy_vs_rawTime_front->Divide(8, 4);

  c_12_multi_front =
      new TCanvas("c_12_multi_front", "12_multi_front", 0, 0, 800, 800);
  c_12_multi_front->Divide(2, 2);

  c_12_DE_vs_DE_front =
      new TCanvas("c_12_DE_vs_DE_front", "12_DE_vs_DE_front", 0, 0, 800, 800);
  c_12_DE_vs_DE_front->Divide(8, 4);

  c_1_pattern = new TCanvas("c_1_pattern", "c_1_pattern", 0, 0, 2400, 1200);
  c_1_pattern->Divide(2, 2);

  c_trigger = new TCanvas("c_trigger", "c_trigger", 0, 0, 2400, 1200);
  c_trigger->Divide(2, 2);

  // mapfol->Add(c_1_multi_front);

  int nch = 500;
  int xymin = -0.5;
  int xymax = 4095.5;

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

    sprintf(Name8, "AsyChimera_1_rawEnergy_back_%i", j);
    fh1_1_rawEnergy_back[j] = new TH1I(Name8, Name8, nch, xymin, xymax);
    fh1_1_rawEnergy_back[j]->GetXaxis()->SetTitle("raw Energy (ch)");
    fh1_1_rawEnergy_back[j]->GetYaxis()->SetTitle("Yield");
    c_1_rawEnergy_back->cd(j + 1);
    fh1_1_rawEnergy_back[j]->Draw();

    sprintf(Name9, "AsyChimera_1_rawTime_back_%i", j);
    fh1_1_rawTime_back[j] = new TH1I(Name9, Name9, nch, xymin, xymax);
    fh1_1_rawTime_back[j]->GetXaxis()->SetTitle("raw Time (ch)");
    fh1_1_rawTime_back[j]->GetYaxis()->SetTitle("Yield");
    c_1_rawTime_back->cd(j + 1);
    fh1_1_rawTime_back[j]->Draw();

    sprintf(Name10, "AsyChimera_1_rawEnergy_vs_rawTime_back_%i", j);
    fh2_1_rawEnergy_vs_rawTime_back[j] =
        new TH2F(Name10, Name10, nch, xymin, xymax, nch, xymin, xymax);
    fh2_1_rawEnergy_vs_rawTime_back[j]->GetXaxis()->SetTitle("raw Time (ch)");
    fh2_1_rawEnergy_vs_rawTime_back[j]->GetYaxis()->SetTitle("raw Energy (ch)");
    c_1_rawEnergy_vs_rawTime_back->cd(j + 1);
    fh2_1_rawEnergy_vs_rawTime_back[j]->Draw("Zcol");

    sprintf(Name4, "AsyChimera_2_rawEnergy_front_%i", j);
    fh1_2_rawEnergy_front[j] = new TH1I(Name4, Name4, nch, xymin, xymax);
    fh1_2_rawEnergy_front[j]->GetXaxis()->SetTitle("raw Energy (ch)");
    fh1_2_rawEnergy_front[j]->GetYaxis()->SetTitle("Yield");
    c_2_rawEnergy_front->cd(j + 1);
    fh1_2_rawEnergy_front[j]->Draw();

    sprintf(Name5, "AsyChimera_2_rawTime_front_%i", j);
    fh1_2_rawTime_front[j] = new TH1I(Name5, Name5, nch, xymin, xymax);
    fh1_2_rawTime_front[j]->GetXaxis()->SetTitle("raw Time (ch)");
    fh1_2_rawTime_front[j]->GetYaxis()->SetTitle("Yield");
    c_2_rawTime_front->cd(j + 1);
    fh1_2_rawTime_front[j]->Draw();

    sprintf(Name6, "AsyChimera_2_rawEnergy_vs_rawTime_front_%i", j);
    fh2_2_rawEnergy_vs_rawTime_front[j] =
        new TH2F(Name6, Name6, nch, xymin, xymax, nch, xymin, xymax);
    fh2_2_rawEnergy_vs_rawTime_front[j]->GetXaxis()->SetTitle("raw Time (ch)");
    fh2_2_rawEnergy_vs_rawTime_front[j]->GetYaxis()->SetTitle(
        "raw Energy (ch)");
    c_2_rawEnergy_vs_rawTime_front->cd(j + 1);
    fh2_2_rawEnergy_vs_rawTime_front[j]->Draw("Zcol");

    sprintf(Name7, "AsyChimera_12_DE_vs_DE_front_%i", j);
    fh2_12_rawEnergy_vs_rawEnergy_front[j] =
        new TH2F(Name7, Name7, nch, xymin, xymax, nch, xymin, xymax);
    fh2_12_rawEnergy_vs_rawEnergy_front[j]->GetXaxis()->SetTitle(
        "raw Energy (ch)");
    fh2_12_rawEnergy_vs_rawEnergy_front[j]->GetYaxis()->SetTitle(
        "raw Energy (ch)");
    c_12_DE_vs_DE_front->cd(j + 1);
    fh2_12_rawEnergy_vs_rawEnergy_front[j]->Draw("Zcol");
  }

  fh1_1_multi_front = new TH1I("AsyChimera_1_multi_front",
                               "AsyChimera_1_multi_front", 33, -0.5, 32.5);
  fh1_2_multi_front = new TH1I("AsyChimera_2_multi_front",
                               "AsyChimera_2_multi_front", 33, -0.5, 32.5);
  fh2_12_multi_front =
      new TH2I("AsyChimera_12_multi_front", "AsyChimera_12_multi_front", 33,
               -0.5, 32.5, 33, -0.5, 32.5);
  fh1_1_multi_back = new TH1I("AsyChimera_1_multi_back",
                              "AsyChimera_1_multi_back", 33, -0.5, 32.5);

  fh1_1_patt_front = new TH1I("AsyChimera_1_patt_front",
                              "AsyChimera_1_patt_front", 33, -0.5, 32.5);
  fh1_2_patt_front = new TH1I("AsyChimera_2_patt_front",
                              "AsyChimera_2_patt_front", 33, -0.5, 32.5);
  fh1_1_patt_back = new TH1I("AsyChimera_1_patt_back", "AsyChimera_1_patt_back",
                             33, -0.5, 32.5);

  fh1_triggerT1 =
      new TH1F("AsyChimera_trigger_T1", "AsyChimera_trigger_T1", 4000, 0, 4000);
  fh1_triggerT3 =
      new TH1F("AsyChimera_trigger_T3", "AsyChimera_trigger_T3", 4000, 0, 4000);
  fh1_triggerW =
      new TH1F("AsyChimera_trigger_W", "AsyChimera_trigger_W", 4000, 0, 4000);
  fh1_triggerW_chan4 = new TH1F("AsyChimera_trigger_Wch4",
                                "AsyChimera_trigger_Wch4", 4000, 0, 4000);

  c_12_multi_front->cd(1);
  gPad->SetLogy();
  fh1_1_multi_front->Draw();
  c_12_multi_front->cd(2);
  gPad->SetLogy();
  fh1_2_multi_front->Draw();
  c_12_multi_front->cd(3);
  gPad->SetLogz();
  fh2_12_multi_front->Draw("ZCOL");
  c_12_multi_front->cd(4);
  gPad->SetLogy();
  fh1_1_multi_back->Draw();

  c_1_pattern->cd(1);
  // gPad->SetLogy();
  fh1_1_patt_front->Draw();
  c_1_pattern->cd(2);
  // gPad->SetLogy();
  fh1_2_patt_front->Draw();
  c_1_pattern->cd(3);
  // gPad->SetLogy();
  fh1_1_patt_back->Draw();

  c_trigger->cd(1);
  fh1_triggerT1->Draw();
  c_trigger->cd(2);
  fh1_triggerT3->Draw();
  c_trigger->cd(3);
  fh1_triggerW->Draw();
  c_trigger->cd(4);
  fh1_triggerW_chan4->Draw();

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
    fh1_1_rawEnergy_back[i]->Reset();
    fh1_1_rawTime_back[i]->Reset();
    fh2_1_rawEnergy_vs_rawTime_back[i]->Reset();

    fh1_2_rawEnergy_front[i]->Reset();
    fh1_2_rawTime_front[i]->Reset();
    fh2_2_rawEnergy_vs_rawTime_front[i]->Reset();
    fh2_12_rawEnergy_vs_rawEnergy_front[i]->Reset();
  }
  // Multiplicity reset
  fh1_1_multi_front->Reset();
  fh1_1_multi_back->Reset();
  fh1_2_multi_front->Reset();
  fh2_12_multi_front->Reset();
  // Pattern reset
  fh1_1_patt_front->Reset();
  fh1_2_patt_front->Reset();
  fh1_1_patt_back->Reset();

  fh1_triggerT1->Reset();
  fh1_triggerT3->Reset();
  fh1_triggerW->Reset();
  fh1_triggerW_chan4->Reset();
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
  UShort_t multi_back_1 = 0;
  UShort_t multi_front_2 = 0;

  UShort_t de1[Nstrips];
  UShort_t de1b[Nstrips];
  UShort_t de2[Nstrips];
  for (int i = 0; i < Nstrips; i++) {
    de1[i] = -1;
    de1b[i] = -1;
    de2[i] = -1;
  }

  if (fMappedItemsChimera && fMappedItemsChimera->GetEntriesFast()) {
    // --- --------------------- --- //
    // --- loop over mapped data --- //
    // --- --------------------- --- //
    nHits = fMappedItemsChimera->GetEntriesFast();
    int time_trig = 0;
    int time1 = 0;
    for (Int_t ihit = 0; ihit < nHits; ihit++) {
      R3BAsyChimeraMappedData* hitmapped =
          (R3BAsyChimeraMappedData*)fMappedItemsChimera->At(ihit);
      if (!hitmapped) continue;
      iDet = hitmapped->GetDetectorId();
      iSide = hitmapped->GetSideId();
      iCh = hitmapped->GetStripId();
      // if(iDet==3) {
      //	 std::cout << iDet << " " << iSide << " " << iCh << std::endl;
      // }
      rawEnergy = hitmapped->GetEnergy();
      rawTime = hitmapped->GetTime();
      // std::cout << iDet << " " << iSide << " " << iCh << std::endl;
      // S1 front
      if (iDet == 1 && iSide == 1 && iCh < Nstrips) {
        if (rawEnergy > 0) {
          fh1_1_rawEnergy_front[iCh]->Fill(rawEnergy);
          de1[iCh] = rawEnergy;
        }
        if (rawTime > 0) fh1_1_rawTime_front[iCh]->Fill(rawTime);
        if (rawEnergy > 0 && rawTime > 0) {
          fh2_1_rawEnergy_vs_rawTime_front[iCh]->Fill(rawTime, rawEnergy);
          multi_front_1++;
          fh1_1_patt_front->Fill(iCh);
        }
      }

      // S1 Back
      if (iDet == 1 && iSide == 2 && iCh < Nstrips) {
        if (rawEnergy > 0) {
          fh1_1_rawEnergy_back[iCh]->Fill(rawEnergy);
          de1b[iCh] = rawEnergy;
        }
        if (rawTime > 0) fh1_1_rawTime_back[iCh]->Fill(rawTime);
        if (rawEnergy > 0 && rawTime > 0) {
          fh2_1_rawEnergy_vs_rawTime_back[iCh]->Fill(rawTime, rawEnergy);
          multi_back_1++;
          fh1_1_patt_back->Fill(iCh);
        }
      }

      // S2  front
      if (iDet == 2 && iSide == 1 && iCh < Nstrips) {
        if (rawEnergy > 0) {
          fh1_2_rawEnergy_front[iCh]->Fill(rawEnergy);
          de2[iCh] = rawEnergy;
        }
        if (rawTime > 0) fh1_2_rawTime_front[iCh]->Fill(rawTime);
        if (rawEnergy > 0 && rawTime > 0) {
          fh2_2_rawEnergy_vs_rawTime_front[iCh]->Fill(rawTime, rawEnergy);
          multi_front_2++;
          fh1_2_patt_front->Fill(iCh);
        }
      }

      // triggers
      if (iDet == 3 && iSide == 1 && iCh == 7) {
        time1 = rawTime;
        fh1_triggerT1->Fill(rawTime);
      }
      int time3 = 0;
      if (iDet == 3 && iSide == 1 && iCh == 6) {
        time3 = rawTime;
        fh1_triggerT3->Fill(rawTime);
      }
      if (iDet == 3 && iSide == 1 && iCh == 4) {
        time_trig = rawTime;
        // std::cout<<iCh<<" "<<rawTime<<std::endl;
        fh1_triggerW_chan4->Fill(rawTime);
      }
    }
    if (time1 > 0 && time_trig > 0) fh1_triggerW->Fill(time1 - time_trig);
  }

  for (int i = 0; i < Nstrips; i++) {
    if (de1[i] > 0 && de2[i] > 0) {
      fh2_12_rawEnergy_vs_rawEnergy_front[i]->Fill(de2[i], de1[i]);
    }
  }

  fh1_1_multi_front->Fill(multi_front_1);
  fh1_1_multi_back->Fill(multi_back_1);
  fh1_2_multi_front->Fill(multi_front_2);
  fh2_12_multi_front->Fill(multi_front_1, multi_front_2);
  fMulti_Front_1 = multi_front_1;
  fMulti_Front_2 = multi_front_2;
  fNEvents += 1;
}

void R3BAsyChimeraOnlineSpectra::FinishEvent() {
  if (fMappedItemsChimera) {
    fMappedItemsChimera->Clear();
  }
}

void R3BAsyChimeraOnlineSpectra::FinishTask() {
  if (fMappedItemsChimera) {
    c_1_rawEnergy_front->Write();
    c_1_rawTime_front->Write();
    c_1_rawEnergy_vs_rawTime_front->Write();

    c_1_rawEnergy_back->Write();
    c_1_rawTime_back->Write();
    c_1_rawEnergy_vs_rawTime_back->Write();

    c_2_rawEnergy_front->Write();
    c_2_rawTime_front->Write();
    c_2_rawEnergy_vs_rawTime_front->Write();

    c_12_multi_front->Write();
    c_12_DE_vs_DE_front->Write();

    c_1_pattern->Write();
    c_trigger->Write();
  }
}
ClassImp(R3BAsyChimeraOnlineSpectra)
