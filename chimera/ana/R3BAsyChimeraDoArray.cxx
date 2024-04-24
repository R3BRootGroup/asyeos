// --------------------------------------------------------------------------
// -----                  R3BAsyChimeraDoArray source file             ------
// --------------------------------------------------------------------------

#include "R3BAsyChimeraDoArray.h"

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
#include "R3BAsyChimeraArrayData.h"
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
#define TT 0

R3BAsyChimeraDoArray::R3BAsyChimeraDoArray()
    : FairTask("AsyChimeraDoArray", 1),
      fMappedItemsChimera(NULL),
      fChimeraArrayData(0),
      fNEvents(0),
      iMulti(0) {
  iDet = new UInt_t[dmax];
  iSide = new UInt_t[dmax];
  iStrip = new UInt_t[dmax];
  iRawEnergy = new UInt_t[dmax];
  iRawTime = new UInt_t[dmax];
}

R3BAsyChimeraDoArray::R3BAsyChimeraDoArray(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose),
      fMappedItemsChimera(NULL),
      fChimeraArrayData(0),
      fNEvents(0),
      iMulti(0) {
  iDet = new UInt_t[dmax];
  iSide = new UInt_t[dmax];
  iStrip = new UInt_t[dmax];
  iRawEnergy = new UInt_t[dmax];
  iRawTime = new UInt_t[dmax];
}

R3BAsyChimeraDoArray::~R3BAsyChimeraDoArray() {
  LOG(info) << "R3BAsyChimeraDoArray::Delete instance";
  if (fChimeraArrayData) {
    delete fChimeraArrayData;
  }
}

InitStatus R3BAsyChimeraDoArray::Init() {
  LOG(info) << "R3BAsyChimeraDoArray::Init ";

  // try to get a handle on the EventHeader. EventHeader may not be
  // present though and hence may be null. Take care when using.

  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyChimeraDoArray::Init FairRootManager not found";
  // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

  if (verbose) LOG(info) << "R3BAsyChimeraDoArray::Init line 72";

  // --- ------------------------------------- --- //
  // --- get access to mapped data of CHIMERA  --- //
  // --- ------------------------------------- --- //
  if (verbose) LOG(info) << "R3BAsyChimeraDoArray::Init line 80";

  fMappedItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraMappedData");
  if (!fMappedItemsChimera) {
    return kFATAL;
  }
  if (verbose) LOG(info) << "R3BAsyChimeraDoArray::Init line 87";

  // Register output array in tree
  fChimeraArrayData = new TClonesArray("R3BAsyChimeraArrayData");
  FairRootManager::Instance()->Register(
      "ChimeraArrayData", "AsyChimera Array data", fChimeraArrayData, !fOnline);

  LOG(info) << "R3BAsyChimeraDoArray::Init DONE";
  nn = 0;
  return kSUCCESS;
}

void R3BAsyChimeraDoArray::Exec(Option_t* option) {
  Reset();
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal) << "R3BAsyChimeraDoArray::Exec FairRootManager not found";
  Int_t nHits;
  iMulti = 0;

  for (int i = 0; i < dmaxs; i++) {
    E1F[i] = 0;
    T1F[i] = 0;
    E1B[i] = 0;
    T1B[i] = 0;
    E2F[i] = 0;
    T2F[i] = 0;
    E3F[i] = 0;
    T3F[i] = 0;

    uE1F[i] = false;
    uT1F[i] = false;
    uE1B[i] = false;
    uT1B[i] = false;
    uE2F[i] = false;
    uT2F[i] = false;
  }

  UInt_t multE12 = 0;
  UInt_t multEFB1 = 0;

  if (fMappedItemsChimera && fMappedItemsChimera->GetEntriesFast()) {
    // --- --------------------- --- //
    // --- loop over mapped data --- //
    // --- --------------------- --- //
    nHits = fMappedItemsChimera->GetEntriesFast();
    //    LOG(info) << "R3BAsyChimeraDoArray::Exec";
    //    std::cout << "nHits=" << nHits << std::endl;
    for (Int_t ihit = 0; ihit < nHits; ihit++) {
      R3BAsyChimeraMappedData* hitmapped =
          (R3BAsyChimeraMappedData*)fMappedItemsChimera->At(ihit);
      if (!hitmapped) continue;
      //      std::cout << "* temp_multi=" << temp_multi << std::endl;
      //      std::cout << "* iDet=" << hitmapped->GetDetectorId() << std::endl;
      if (hitmapped->GetEnergy() > 0 || hitmapped->GetTime() > 0) {
        iDet[iMulti] = hitmapped->GetDetectorId();
        iSide[iMulti] = hitmapped->GetSideId();
        iStrip[iMulti] = hitmapped->GetStripId();
        iRawEnergy[iMulti] = hitmapped->GetEnergy();
        iRawTime[iMulti] = hitmapped->GetTime();
        iMulti++;

        if (hitmapped->GetDetectorId() == 1 && hitmapped->GetSideId() == 1) {
          int strip = hitmapped->GetStripId();
          if (strip != 4 && strip != 16 && strip != 19 && strip != 31) {
            if (hitmapped->GetEnergy() > 0) E1F[strip] = hitmapped->GetEnergy();
            if (hitmapped->GetTime() > 0) T1F[strip] = hitmapped->GetEnergy();
          }
        }
        if (hitmapped->GetDetectorId() == 1 && hitmapped->GetSideId() == 2) {
          int strip = hitmapped->GetStripId();
          if (strip != 29) {
            if (hitmapped->GetEnergy() > 0) E1B[strip] = hitmapped->GetEnergy();
            if (hitmapped->GetTime() > 0) T1B[strip] = hitmapped->GetEnergy();
          }
        }
        if (hitmapped->GetDetectorId() == 2 && hitmapped->GetSideId() == 1) {
          int strip = hitmapped->GetStripId();
          if (hitmapped->GetEnergy() > 0) E2F[strip] = hitmapped->GetEnergy();
          if (hitmapped->GetTime() > 0) T2F[strip] = hitmapped->GetEnergy();
        }

        if (hitmapped->GetDetectorId() == 3 && hitmapped->GetSideId() == 1) {
          int strip = hitmapped->GetStripId();
          if (hitmapped->GetEnergy() > 0) E3F[strip] = hitmapped->GetEnergy();
          if (hitmapped->GetTime() > 0) T3F[strip] = hitmapped->GetEnergy();
        }
      }
    }
    //    if(iMulti>0)AddHitData(iMulti/*, iDet, iSide, iStrip, iRawEnergy,
    //    iRawTime*/);
  }

  if (iMulti > 0) {
    if (E1F[9] <= 229) E1F[9] = 0;
    if (E1F[30] <= 91) E1F[30] = 0;

    if (E2F[31] <= 112) E2F[31] = 0;

    if (E1B[12] <= 81) E1B[12] = 0;
    if (E1B[16] <= 80) E1B[12] = 0;
    if (E1B[23] <= 81) E1B[23] = 0;
    if (E1B[26] <= 82) E1B[26] = 0;
    if (E1B[28] <= 88) E1B[28] = 0;
    if (E1B[30] <= 75) E1B[30] = 0;
    if (E1B[31] <= 65) E1B[31] = 0;

    for (int i = 0; i < dmaxs; i++) {
      uE1F[i] = false;
      uT1F[i] = false;
      uE2F[i] = false;
      uT2F[i] = false;
    }

    for (int i = 0; i < dmaxs; i++) {
      if (E1F[i] > 0 && E2F[i] > 0 && T1F[i] >= TT && T2F[i] >= TT &&
          (!uE1F[i]) && (!uE2F[i])) {
        int diffE = E1F[i] - E2F[i];
        int diffT = T1F[i] - T2F[i];
        if (diffE < 0) diffE = -diffE;
        if (diffT < 0) diffT = -diffT;
        if (diffE < 155) {
          multE12++;
          uE1F[i] = true;
          uE2F[i] = true;
        }
      }
    }

    for (int i = 0; i < (dmaxs - 1); i++) {
      if (E1F[i] > 0 && E2F[i + 1] > 0 && T1F[i] >= TT && T2F[i + 1] >= TT &&
          (!uE1F[i]) && (!uE2F[i + 1])) {
        int diffE = E1F[i] - E2F[i + 1];
        int diffT = T1F[i] - T2F[i + 1];
        if (diffE < 0) diffE = -diffE;
        if (diffT < 0) diffT = -diffT;
        if (diffE < 155) {
          multE12++;
          uE1F[i] = true;
          uE2F[i + 1] = true;
        }
      }
    }

    for (int i = 1; i < dmaxs; i++) {
      if (E1F[i] > 0 && E2F[i - 1] > 0 && T1F[i] >= TT && T2F[i - 1] >= TT &&
          (!uE1F[i]) && (!uE2F[i - 1])) {
        int diffE = E1F[i] - E2F[i - 1];
        int diffT = T1F[i] - T2F[i - 1];
        if (diffE < 0) diffE = -diffE;
        if (diffT < 0) diffT = -diffT;
        if (diffE < 155) {
          multE12++;
          uE1F[i] = true;
          uE2F[i - 1] = true;
        }
      }
    }

    for (int i = 0; i < dmaxs; i++) {
      uE1F[i] = false;
      uT1F[i] = false;
      uE1B[i] = false;
      uT1B[i] = false;
    }

    for (int i = 0; i < dmaxs; i++) {
      if (E1F[i] > 0 && T1F[i] >= TT && (!uE1F[i])) {
        for (int ii = 0; ii < dmaxs; ii++) {
          if (E1B[ii] > 0 && T1B[ii] >= TT && (!uE1B[ii])) {
            int diffE = E1F[i] - E1B[ii];
            int diffT = T1F[i] - T1B[ii];
            if (diffE < 0) diffE = -diffE;
            if (diffT < 0) diffT = -diffT;
            if (diffE < 255) {
              multEFB1++;
              uE1F[i] = true;
              uE1B[ii] = true;
            }
          }
        }
      }
    }
  }

  //  std::cout << multE12 << " @@@ " << multEFB1 << std::endl;

  if (iMulti > 0) {
    AddHitData(iMulti, iDet, iSide, iStrip, iRawEnergy, iRawTime, multE12,
               multEFB1);
  } else {
    AddHitData(iMulti, 0, 0, 0, 0, 0, 0, 0);
  }
  //  std::cout << "R3BAsyChimeraDoArray: ** " << nn << " " << iMulti <<
  //  std::endl;

  //  if(iMulti>0)new ((*fArray)[fArray->GetEntriesFast()])
  //  R3BAsyChimeraArrayData(
  //          iMulti/*, iDet, iSide, iStrip, iRawEnergy, iRawTime*/);

  nn++;
  //  LOG(info) << "R3BAsyChimeraDoArray: " <<
  //  fChimeraArrayData->GetEntriesFast() << " points registered in this event";
}

void R3BAsyChimeraDoArray::Reset() {
  // Reset the output array
  if (fChimeraArrayData) {
    fChimeraArrayData->Clear();
  }
}

// -----   Private method AddHitData -------------------------------------------
R3BAsyChimeraArrayData* R3BAsyChimeraDoArray::AddHitData(
    UInt_t multi, UInt_t* Det, UInt_t* Side, UInt_t* Strip, UInt_t* RawEnergy,
    UInt_t* RawTime, UInt_t multiE12, UInt_t multEFB1) {
  TClonesArray& clref = *fChimeraArrayData;
  Int_t size = clref.GetEntriesFast();
  return new (clref[size]) R3BAsyChimeraArrayData(
      multi, Det, Side, Strip, RawEnergy, RawTime, multiE12, multEFB1);
}

ClassImp(R3BAsyChimeraDoArray)
