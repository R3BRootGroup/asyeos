// --------------------------------------------------------------------------
// -----            R3BAsyCommonAna source file             ------
// --------------------------------------------------------------------------

#include "R3BAsyCommonAna.h"

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
#include "R3BAsyChimeraPhysData.h"
#include "R3BAsyKrabPhysData.h"
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

R3BAsyCommonAna::R3BAsyCommonAna()
    : FairTask("AsyCommonAna", 1),
      fPhysItemsChimera(0),
      fPhysItemsKrab(0),
      fNEvents(0) {}

R3BAsyCommonAna::R3BAsyCommonAna(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose),
      fPhysItemsChimera(0),
      fPhysItemsKrab(0),
      fNEvents(0) {}

R3BAsyCommonAna::~R3BAsyCommonAna() {
  LOG(info) << "R3BAsyCommonAna::Delete instance";
  if (fPhysItemsChimera) delete fPhysItemsChimera;
  if (fPhysItemsKrab) delete fPhysItemsKrab;
}

InitStatus R3BAsyCommonAna::Init() {
  LOG(info) << "R3BAsyCommonAna::Init ";

  // try to get a handle on the EventHeader. EventHeader may not be
  // present though and hence may be null. Take care when using.

  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyCommonAna::Init FairRootManager not found";
  // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

  if (verbose) LOG(info) << "R3BAsyCommonAna::Init line 72";

  FairRunOnline* run = FairRunOnline::Instance();
  // for online server  run->GetHttpServer()->Register("", this);

  // Register command to reset histograms
  // for online server  run->GetHttpServer()->RegisterCommand("Reset_Chimera",
  // Form("/Objects/%s/->Reset_Histo()", GetName()));

  // --- ------------------------------------- --- //
  // --- get access to phys data of CHIMERA and KRAB --- //
  // --- ------------------------------------- --- //
  if (verbose) LOG(info) << "R3BAsyCommonAna::Init line 80";

  fPhysItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraPhysData");
  if (!fPhysItemsChimera) {
    //   std::cout << "#### Common Ana :: 79 fPhysItemsChimera not found" <<
    //   std::endl; getchar();
    //        return kFATAL;
  }
  fPhysItemsKrab = (TClonesArray*)mgr->GetObject("AsyKrabPhysData");
  if (!fPhysItemsKrab) {
    //        return kFATAL;
  }

  if (verbose) LOG(info) << "R3BAsyCommonAna::Init line 87";

  c_CHIMERA_KRAB =
      new TCanvas("c_CHIMERA_KRAB", "CHIMERA_KRAB", 0, 0, 1200, 1200);
  fh2_CHIMERA_KRAB_multi =
      new TH2I("fh2_CHIMERA_KRAB_multi", "CHIMERA_KRAB_multi", 100, -0.5, 99.5,
               100, -0.5, 99.5);
  fh2_CHIMERA_KRAB_RP = new TH2F("fh2_CHIMERA_KRAB_RP", "CHIMERA_KRAB_RP", 90,
                                 -180., 180., 90, -180., 180.);
  c_CHIMERA_KRAB->Divide(2, 2);
  c_CHIMERA_KRAB->cd(1);
  fh2_CHIMERA_KRAB_multi->Draw();
  c_CHIMERA_KRAB->cd(2);
  fh2_CHIMERA_KRAB_RP->Draw();

  LOG(info) << "R3BAsyCommonAna::Init DONE";
  return kSUCCESS;
}

void R3BAsyCommonAna::Reset_Histo() {
  LOG(info) << "R3BAsyCommonAna::Reset_Histo";
  fh2_CHIMERA_KRAB_multi->Reset();
  fh2_CHIMERA_KRAB_RP->Reset();
}

void R3BAsyCommonAna::Exec(Option_t* option) {
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyCommonAna::Exec FairRootManager not found";

  Int_t nHits_CHI, nHits_KRAB;
  UInt_t multi_CHI = -10, multi_KRAB = -10;
  Float_t RP_CHI = -1000, RP_KRAB = -1000;

  if (fPhysItemsChimera && fPhysItemsChimera->GetEntriesFast() &&
      fPhysItemsKrab && fPhysItemsKrab->GetEntriesFast()) {
    // --- --------------------- --- //
    // --- loop over mapped data --- //
    // --- --------------------- --- //
    nHits_CHI = fPhysItemsChimera->GetEntriesFast();
    nHits_KRAB = fPhysItemsKrab->GetEntriesFast();

    for (Int_t ihit = 0; ihit < nHits_CHI; ihit++) {
      R3BAsyChimeraPhysData* physdata =
          (R3BAsyChimeraPhysData*)fPhysItemsChimera->At(ihit);
      if (!physdata) continue;
      multi_CHI = physdata->GetMulti();
      RP_CHI = physdata->GetRP();
    }

    for (Int_t ihit = 0; ihit < nHits_KRAB; ihit++) {
      R3BAsyKrabPhysData* physdata =
          (R3BAsyKrabPhysData*)fPhysItemsKrab->At(ihit);
      if (!physdata) continue;
      multi_KRAB = physdata->GetMulti();
      RP_KRAB = physdata->GetRP();
    }
  }

  fh2_CHIMERA_KRAB_multi->Fill(multi_CHI, multi_KRAB);
  fh2_CHIMERA_KRAB_RP->Fill(RP_CHI, RP_KRAB);
  fNEvents += 1;
  //  std::cout << "#### Common Ana :: 142 " << std::endl;
  //  getchar();
}

void R3BAsyCommonAna::FinishEvent() {
  if (fPhysItemsChimera) {
    fPhysItemsChimera->Clear();
  }
  if (fPhysItemsKrab) {
    fPhysItemsKrab->Clear();
  }
}

void R3BAsyCommonAna::FinishTask() {
  //  std::cout << "#### Common Ana :: 160 " << std::endl;
  //  getchar();

  if (fPhysItemsChimera && fPhysItemsKrab) {
    //   std::cout << "#### Common Ana :: 161 " << std::endl;
    //   getchar();

    c_CHIMERA_KRAB->Update();
    c_CHIMERA_KRAB->Write();
  }
}

ClassImp(R3BAsyCommonAna)
