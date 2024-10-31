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
#define dmax 400

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

  uint64_t timestamp = 1;

  /*11102024
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
    timestamp = ((uint64_t)fTIMESTAMP_CHIMERA_WR_T4 << 48) |
                ((uint64_t)fTIMESTAMP_CHIMERA_WR_T3 << 32) |
                ((uint64_t)fTIMESTAMP_CHIMERA_WR_T2 << 16) |
                (uint64_t)fTIMESTAMP_CHIMERA_WR_T1;

    if (verbose)
      std::cout << " ********* " << std::hex << timestamp << std::dec
                << std::endl;

    new ((*fArrayWR)[fArrayWR->GetEntriesFast()])
        R3BWRData(timestamp, fTIMESTAMP_CHIMERA_ID);
  11102024*/

  if (timestamp == 0) {
    new ((*fArray)[fArray->GetEntriesFast()])
        R3BAsyChimeraMappedData(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  } else {
    auto const& numchfast = data->CHIM_FAST;
    auto const& numchRGfast = data->CHIM_RG_FAST;
    if (verbose)
      std::cout << " ********* numchfast=" << numchfast
                << "   numchRGfast=" << numchRGfast << std::endl;
    if (numchfast != numchRGfast)
      std::cout << "### CHIM_FAST  CHIM_RG_FAST lenght mismatch " << std::endl;

    auto const& numchslow = data->CHIM_SLOW;
    auto const& numchRGslow = data->CHIM_RG_SLOW;
    if (verbose)
      std::cout << " ********* numchslow=" << numchslow
                << "   numchRGslow=" << numchRGslow << std::endl;
    if (numchslow != numchRGslow)
      std::cout << "### CHIM_SLOW  CHIM_RG_SLOW lenght mismatch " << std::endl;

    auto const& numchsil = data->CHIM_SIL;
    auto const& numchRGsil = data->CHIM_RG_SIL;
    if (verbose)
      std::cout << " ********* numchsil=" << numchsil
                << "   numchRGsil=" << numchRGsil << std::endl;
    if (numchsil != numchRGsil)
      std::cout << "### CHIM_SIL  CHIM_RG_SIL lenght mismatch " << std::endl;

    auto const& numchtime = data->CHIM_TIME;

    auto const& numchtimesil = data->CHIM_TOFSIL;

    uint32_t numtel[dmax];
    uint32_t fastHG[dmax];
    uint32_t fastLG[dmax];
    uint32_t slowHG[dmax];
    uint32_t slowLG[dmax];
    uint32_t timeCsI[dmax];

    uint32_t silHG[dmax];
    uint32_t silLG[dmax];
    uint32_t timeSil[dmax];
    uint32_t patt[dmax];

    // clearing data
    for (int i = 0; i < dmax; i++) {
      numtel[i] = i;
      fastHG[i] = 0;
      fastLG[i] = 0;
      slowHG[i] = 0;
      slowLG[i] = 0;
      timeCsI[i] = 0;
      silHG[i] = 0;
      silLG[i] = 0;
      timeSil[i] = 0;
      patt[i] = 0;
    }

    // decoding zero suppressed data
    for (int i = 0; i < numchfast; i++) {
      uint32_t ch = data->CHIM_FASTI[i];
      uint32_t chRG = data->CHIM_RG_FASTI[i];
      uint32_t fast = data->CHIM_FASTv[i];
      uint32_t fastRG = data->CHIM_RG_FASTv[i];
      if (ch == chRG) {
        if (fastRG == 1) {
          fastLG[ch] = fast;
        } else if (fastRG == 0) {
          fastHG[ch] = fast;
        } else {
          std::cout << "### fast RG error, RG = " << fastRG << std::endl;
        }
      } else {
        std::cout << "### CHIM_FASTI  CHIM_RG_FASTI channel mismatch "
                  << std::endl;
      }
      if (verbose)
        std::cout << " ### FAST " << ch << " " << chRG << " " << fast << " "
                  << fastRG << std::endl;
    }

    for (int i = 0; i < numchslow; i++) {
      uint32_t ch = data->CHIM_SLOWI[i];
      uint32_t chRG = data->CHIM_RG_SLOWI[i];
      uint32_t slow = data->CHIM_SLOWv[i];
      uint32_t slowRG = data->CHIM_RG_SLOWv[i];
      if (ch == chRG) {
        if (slowRG == 1) {
          slowLG[ch] = slow;
        } else if (slowRG == 0) {
          slowHG[ch] = slow;
        } else {
          std::cout << "### slow RG error, RG = " << slowRG << std::endl;
        }
      } else {
        std::cout << "### CHIM_SLOWI  CHIM_RG_SLOWI channel mismatch "
                  << std::endl;
      }
      if (verbose)
        std::cout << " ### SLOW " << ch << " " << chRG << " " << slow << " "
                  << slowRG << std::endl;
    }

    for (int i = 0; i < numchsil; i++) {
      uint32_t ch = data->CHIM_SILI[i];
      uint32_t chRG = data->CHIM_RG_SILI[i];
      uint32_t sil = data->CHIM_SILv[i];
      uint32_t silRG = data->CHIM_RG_SILv[i];
      if (ch == chRG) {
        if (silRG == 1) {
          silLG[ch] = sil;
        } else if (silRG == 0) {
          silHG[ch] = sil;
        } else {
          std::cout << "### sil RG error, RG = " << silRG << std::endl;
        }
      } else {
        std::cout << "### CHIM_SILI  CHIM_RG_SILI channel mismatch "
                  << std::endl;
      }
      if (verbose)
        std::cout << " ### SIL " << ch << " " << chRG << " " << sil << " "
                  << silRG << std::endl;
    }

    for (int i = 0; i < numchtime; i++) {
      uint32_t ch = data->CHIM_TIMEI[i];
      uint32_t time = data->CHIM_TIMEv[i];
      timeCsI[ch] = time;
      if (verbose)
        std::cout << " ### CsI TIME " << ch << " " << time << std::endl;
    }

    for (int i = 0; i < numchtimesil; i++) {
      uint32_t ch = data->CHIM_TOFSILI[i];
      uint32_t time = data->CHIM_TOFSILv[i];
      timeSil[ch] = time;
      if (verbose)
        std::cout << " ### Sil TIME " << ch << " " << time << std::endl;
    }

    auto const& numpatt = data->CHIM_PATTERNCHI;
    if (verbose) std::cout << " ********* numpatt=" << numpatt << std::endl;

    for (int i = 0; i < numpatt; i++) {
      uint32_t ch = data->CHIM_PATTERNCHII[i];
      uint32_t patt_value = data->CHIM_PATTERNCHIv[i];
      patt[ch] = patt_value;
      if (verbose)
        std::cout << "### patt  " << ch << " *** " << patt_value << std::endl;
    }
    for (int i = 0; i < dmax; i++) {
      if (fastLG[i] > 0 || fastHG[i] > 0 || slowLG[i] > 0 || slowHG[i] > 0 ||
          timeCsI[i] > 0 || silHG[i] > 0 || silLG[i] > 0 || timeSil[i] ||
          patt[i] > 0) {
        new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyChimeraMappedData(
            numtel[i], fastHG[i], fastLG[i], slowHG[i], slowLG[i], timeCsI[i],
            silHG[i], silLG[i], timeSil[i], patt[i]);
      }
    }

    if (verbose)
      std::cout << "****** end of  AsyChimeraReader" << std::endl
                << std::endl
                << std::endl;
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
