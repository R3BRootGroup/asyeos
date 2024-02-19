/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019-2024 Members of R3B Collaboration                     *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

#include "AsyChimeraReader.h"

#include <FairLogger.h>
#include <FairRootManager.h>
#include <TClonesArray.h>

#include <ext_data_struct_info.hh>

#include "R3BAsyChimeraMappedData.h"
#include "R3BLogger.h"

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_chimera.h"
}

AsyChimeraReader::AsyChimeraReader(EXT_STR_h101_ASYCHIMERA_onion* data,
                                   size_t offset)
    : R3BReader("AsyChimeraReader"),
      fData(data),
      fOffset(offset),
      fArray(new TClonesArray("R3BAsyChimeraMappedData")),
      fArrayTrigger(new TClonesArray("R3BAsyChimeraMappedData")) {}

AsyChimeraReader::~AsyChimeraReader() {
  if (fArray) {
    delete fArray;
  }
  if (fArrayTrigger) {
    delete fArrayTrigger;
  }
}

Bool_t AsyChimeraReader::Init(ext_data_struct_info* a_struct_info) {
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

  if (!fSkiptriggertimes) {
    FairRootManager::Instance()->Register("AsyChimeraTriggerMapped",
                                          "AsyChimera trigger mapped data",
                                          fArrayTrigger, !fOnline);
  } else {
    fArrayTrigger = nullptr;
  }
  Reset();
  // initial clear (set number of hits to 0)
  auto* data = reinterpret_cast<EXT_STR_h101_ASYCHIMERA_onion*>(fData);

  return kTRUE;
}

Bool_t AsyChimeraReader::R3BRead() {
  R3BLOG(debug1, "Event data.");
  // Convert plain raw data to multi-dimensional array
  auto* data = reinterpret_cast<EXT_STR_h101_ASYCHIMERA_onion*>(fData);

  // S1 detector
  auto const& numchae = data->S[0].FRONTDE;
  auto const& numchat = data->S[0].FRONTTOF;

  uint32_t ener[32];
  uint32_t tof[32];
  // clearing data
  for (int i = 0; i < 32; i++) {
    ener[i] = 0;
    tof[i] = 0;
  }
  // decoding zero suppressed data
  for (int i = 0; i < numchae; i++) {
    uint32_t ch = data->S[0].FRONTDEI[i];
    ener[ch - 1] = data->S[0].FRONTDEv[i];
    // std::cout<<ch-1<<" "<<ener[ch-1]<<std::endl;
  }

  for (int i = 0; i < numchat; i++) {
    uint32_t ch = data->S[0].FRONTTOFI[i];
    tof[ch - 1] = data->S[0].FRONTTOFv[i];
  }

  // filling mapped data of detector 1 (S[0] mapping->  DE FRONT)
  uint32_t detector = 1;  // de silicon
  uint32_t side = 1;      // front
  for (int strip = 0; strip < 32; strip++) {
    if (ener[strip] > 0 || tof[strip] > 0) {
      new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyChimeraMappedData(
          detector, side, strip, ener[strip], tof[strip]);
    }
  }

  return kTRUE;
}

void AsyChimeraReader::Reset() {
  // Reset the output array
  fArray->Clear();
  if (fArrayTrigger) fArrayTrigger->Clear();
}

ClassImp(AsyChimeraReader)
