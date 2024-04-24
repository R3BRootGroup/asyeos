// --------------------------------------------------------------------------
// -----                   R3BAsyChimeraReader source file             ------
// --------------------------------------------------------------------------

#include "R3BAsyChimeraReader.h"

#include <FairLogger.h>
#include <FairRootManager.h>
#include <TClonesArray.h>

#include "R3BAsyChimeraMappedData.h"
#include "R3BWRData.h"

//#include <ext_data_struct_info.hh>

#include "R3BLogger.h"

#define verbose 0

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_chimera.h"
}

R3BAsyChimeraReader::R3BAsyChimeraReader(EXT_STR_h101_ASYCHIMERA* data,
                                         size_t offset)
    : R3BReader("R3BAsyChimeraReader"),
      fData(data),
      fOffset(offset),
      fArray(new TClonesArray("R3BAsyChimeraMappedData")),
      fArrayTrigger(new TClonesArray("R3BAsyChimeraMappedData")),
      fArrayWR(new TClonesArray("R3BWRData")) {}

R3BAsyChimeraReader::~R3BAsyChimeraReader() {
  if (fArray) {
    delete fArray;
  }
  if (fArrayTrigger) {
    delete fArrayTrigger;
  }
  if (fArrayWR) {
    delete fArrayWR;
  }
}

Bool_t R3BAsyChimeraReader::Init(ext_data_struct_info* a_struct_info) {
  Int_t ok;
  R3BLOG(info, "");
  EXT_STR_h101_ASYCHIMERA_ITEMS_INFO(ok, *a_struct_info, fOffset,
                                     EXT_STR_h101_ASYCHIMERA, 0);
  if (!ok) {
    R3BLOG(error, "Failed to setup structure information");
    return kFALSE;
  }

  // Register output array in tree
  FairRootManager::Instance()->Register(
      "AsyChimeraMappedData", "AsyChimera mapped data", fArray, !fOnline);
  fArray->Clear();
  if (!fSkiptriggertimes) {
    FairRootManager::Instance()->Register("AsyChimeraTriggerMapped",
                                          "AsyChimera trigger mapped data",
                                          fArrayTrigger, DoNotWrite);
  } else {
    fArrayTrigger = nullptr;
  }

  FairRootManager::Instance()->Register("AsyChimeraWRData", "WRChimera",
                                        fArrayWR, !fOnline);

  Reset();
  // initial clear (set number of hits to 0)
  EXT_STR_h101_ASYCHIMERA_onion* data = (EXT_STR_h101_ASYCHIMERA_onion*)fData;

  return kTRUE;
}

Bool_t R3BAsyChimeraReader::R3BRead() {
  R3BLOG(debug1, "Event data.");
  // Convert plain raw data to multi-dimensional array
  EXT_STR_h101_ASYCHIMERA_onion* data = (EXT_STR_h101_ASYCHIMERA_onion*)fData;
  // S1 detector

  auto const& fTIMESTAMP_CHIMERA_ID = data->TIMESTAMP_CHIMERA_ID;
  auto const& fTIMESTAMP_CHIMERA_WR_T1 = data->TIMESTAMP_CHIMERA_WR_T[0];
  auto const& fTIMESTAMP_CHIMERA_WR_T2 = data->TIMESTAMP_CHIMERA_WR_T[1];
  auto const& fTIMESTAMP_CHIMERA_WR_T3 = data->TIMESTAMP_CHIMERA_WR_T[2];
  auto const& fTIMESTAMP_CHIMERA_WR_T4 = data->TIMESTAMP_CHIMERA_WR_T[3];

  if (verbose) {
    std::cout << " *** " << fTIMESTAMP_CHIMERA_ID << std::endl;
    std::cout << " ****** " << fTIMESTAMP_CHIMERA_WR_T1 << " "
              << fTIMESTAMP_CHIMERA_WR_T2 << " " << fTIMESTAMP_CHIMERA_WR_T3
              << " " << fTIMESTAMP_CHIMERA_WR_T4 << " " << std::endl;
  }
  uint64_t timestamp = 0;
  timestamp = ((uint64_t)fTIMESTAMP_CHIMERA_WR_T4 << 48) |
              ((uint64_t)fTIMESTAMP_CHIMERA_WR_T3 << 32) |
              ((uint64_t)fTIMESTAMP_CHIMERA_WR_T2 << 16) |
              (uint64_t)fTIMESTAMP_CHIMERA_WR_T1;

  if (verbose)
    std::cout << " ********* " << std::hex << timestamp << std::dec
              << std::endl;

  new ((*fArrayWR)[fArrayWR->GetEntriesFast()])
      R3BWRData(timestamp, fTIMESTAMP_CHIMERA_ID);

  if (timestamp == 0) {
    new ((*fArray)[fArray->GetEntriesFast()])
        R3BAsyChimeraMappedData(0, 0, 0, 0, 0);
  } else {
    auto const& numchae = data->CHIM_S[0].FRONTDE;
    auto const& numchat = data->CHIM_S[0].FRONTTOF;
    auto const& numchaeb = data->CHIM_S[0].BACKDE;
    auto const& numchatb = data->CHIM_S[0].BACKTOF;

    uint32_t ener[32];
    uint32_t tof[32];
    uint32_t enerb[32];
    uint32_t tofb[32];
    uint32_t patt[32];

    // clearing data
    for (int i = 0; i < 32; i++) {
      ener[i] = 0;
      tof[i] = 0;
      enerb[i] = 0;
      tofb[i] = 0;
      patt[i] = 0;
    }
    // decoding zero suppressed data
    for (int i = 0; i < numchae; i++) {
      uint32_t ch = data->CHIM_S[0].FRONTDEI[i];
      ener[ch - 1] = data->CHIM_S[0].FRONTDEv[i];
      // std::cout<<ch-1<<" "<<ener[ch-1]<<std::endl;
    }

    for (int i = 0; i < numchat; i++) {
      uint32_t ch = data->CHIM_S[0].FRONTTOFI[i];
      tof[ch - 1] = data->CHIM_S[0].FRONTTOFv[i];
    }

    // back S1
    for (int i = 0; i < numchaeb; i++) {
      uint32_t ch = data->CHIM_S[0].BACKDEI[i];
      enerb[ch - 1] = data->CHIM_S[0].BACKDEv[i];
    }

    for (int i = 0; i < numchatb; i++) {
      uint32_t ch = data->CHIM_S[0].BACKTOFI[i];
      tofb[ch - 1] = data->CHIM_S[0].BACKTOFv[i];
    }

    // filling mapped data of detector 1 (S[0] mapping->  DE FRONT)
    uint32_t detector = 1;  // de silicon
    uint32_t side = 1;      // front
    for (int strip = 0; strip < 32; strip++) {
      if (ener[strip] > 0 || tof[strip] > 0) {
        new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyChimeraMappedData(
            detector, side, strip, ener[strip], tof[strip]);
        //	  std::cout << "detector 1F found " <<std::endl;
      }
    }

    // filling mapped data of detector 1 (S[0] mapping->  DE BACK)
    detector = 1;  // de silicon
    side = 2;      // back
    for (int strip = 0; strip < 32; strip++) {
      if (enerb[strip] > 0 || tofb[strip] > 0) {
        new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyChimeraMappedData(
            detector, side, strip, enerb[strip], tofb[strip]);
        //	  std::cout << "detector 1B found " <<std::endl;
      }
    }

    //////////////////////////////////////////////////////////////////////
    // S2  detector  (front only)
    //  clearing data
    for (int i = 0; i < 32; i++) {
      ener[i] = 0;
      tof[i] = 0;
    }
    auto const& numchae1 = data->CHIM_S[1].FRONTDE;
    auto const& numchat1 = data->CHIM_S[1].FRONTTOF;
    // decoding zero suppressed data
    for (int i = 0; i < numchae1; i++) {
      uint32_t ch = data->CHIM_S[1].FRONTDEI[i];
      ener[ch - 1] = data->CHIM_S[1].FRONTDEv[i];
    }

    for (int i = 0; i < numchat1; i++) {
      uint32_t ch = data->CHIM_S[1].FRONTTOFI[i];
      tof[ch - 1] = data->CHIM_S[1].FRONTTOFv[i];
    }

    // filling mapped data of detector 2 (CHIM_S[1] mapping->  DE FRONT)
    detector = 2;  // de silicon
    side = 1;      // front
    for (int strip = 0; strip < 32; strip++) {
      if (ener[strip] > 0 || tof[strip] > 0) {
        new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyChimeraMappedData(
            detector, side, strip, ener[strip], tof[strip]);
        //	  std::cout << "detector 2F found " <<std::endl;
      }
    }

    auto const& numpatt = data->CHIM_PATTERNCHI;
    for (int i = 0; i < numpatt; i++) {
      uint32_t ch = data->CHIM_PATTERNCHII[i];
      patt[ch - 1] = data->CHIM_PATTERNCHIv[i];
    }
    // filling mapped data of PATTERN TDC)
    detector = 3;  // de silicon
    side = 1;      //
    uint32_t epatt = 0;
    for (int ch = 0; ch < 32; ch++) {
      if (patt[ch] > 0) {
        new ((*fArray)[fArray->GetEntriesFast()])
            R3BAsyChimeraMappedData(detector, side, ch, epatt, patt[ch]);
        // std::cout << "detector 3 found " <<std::endl;
      }
    }
    //  std::cout << "****** end of  AsyChimeraReader"
    //  <<std::endl<<std::endl<<std::endl;
  }
  return kTRUE;
}

void R3BAsyChimeraReader::Reset() {
  // Reset the output array
  fArray->Clear();
  if (fArrayTrigger) fArrayTrigger->Clear();
  fArrayWR->Clear();
}

ClassImp(R3BAsyChimeraReader)
