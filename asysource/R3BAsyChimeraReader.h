// -------------------------------------------------------------------------
// -----                R3BAsyChimeraReader    header file             -----
// -----    Created 19/04/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

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

#pragma once

#include <Rtypes.h>

#include "R3BReader.h"
#include "TClonesArray.h"

struct EXT_STR_h101_ASYCHIMERA_t;
typedef struct EXT_STR_h101_ASYCHIMERA_t EXT_STR_h101_ASYCHIMERA;
typedef struct EXT_STR_h101_ASYCHIMERA_onion_t EXT_STR_h101_ASYCHIMERA_onion;
// class ext_data_struct_info;

class R3BAsyChimeraReader : public R3BReader {
 public:
  // Standard constructor
  R3BAsyChimeraReader(EXT_STR_h101_ASYCHIMERA*, size_t);

  // Destructor
  virtual ~R3BAsyChimeraReader();

  // Setup structure information
  Bool_t Init(ext_data_struct_info*) override;

  // Read data from full event structure
  Bool_t R3BRead() override;

  // Reset
  void Reset() override;

  // Accessor to select online mode
  inline void SetOnline(bool option) { fOnline = option; }

  // Accessor to skip trigger times
  inline void SetSkipTriggerTimes() { fSkiptriggertimes = true; }

 private:
  // Reader specific data structure from ucesb
  EXT_STR_h101_ASYCHIMERA* fData;
  // Data offset
  size_t fOffset;
  // Don't store data for online
  UInt_t fWhiterabbitId;
  // A pointer to the R3BEventHeader structure
  bool fOnline = false;
  bool DoNotWrite = false;
  // Skip trigger times
  bool fSkiptriggertimes = false;
  // Output array
  TClonesArray* fArray;        /**< Output array. */
  TClonesArray* fArrayTrigger; /**< Output array for triggers. */
  TClonesArray* fArrayWR;      /**< Output array. */

 public:
  ClassDefOverride(R3BAsyChimeraReader, 0);
};
