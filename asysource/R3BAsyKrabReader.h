// -------------------------------------------------------------------------
// -----                R3BAsyKrabReader header file                   -----
// -----    Created 19/04/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

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

#ifndef R3BASYKRABREADER_H
#define R3BASYKRABREADER_H

#pragma once

#include <Rtypes.h>

#include "R3BReader.h"
#include "TClonesArray.h"
#define triggerbox_number_of_boards 6
#define triggerbox_number_of_FPGA_per_board 5
#define num_channels 26

struct EXT_STR_h101_ASYKRAB_t;
typedef struct EXT_STR_h101_ASYKRAB_t EXT_STR_h101_ASYKRAB;
typedef struct EXT_STR_h101_ASYKRAB_onion_t EXT_STR_h101_ASYKRAB_onion;
// class ext_data_struct_info;

class R3BAsyKrabReader : public R3BReader
{
  public:
    // Standard constructor
    R3BAsyKrabReader(EXT_STR_h101_ASYKRAB*, size_t, const char* inFileName);

    // Destructor
    virtual ~R3BAsyKrabReader();

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
    EXT_STR_h101_ASYKRAB* fData;
    // Data offset
    size_t fOffset;
    // Don't store data for online
    UInt_t fWhiterabbitId;
    // A pointer to the R3BEventHeader structure*/
    bool fOnline = false;
    bool DoNotWrite = false;
    // Skip trigger times
    bool fSkiptriggertimes = false;
    // Output array
    TClonesArray* fArray;        /**< Output array. */
    TClonesArray* fArrayTrigger; /**< Output array for triggers. */
    TClonesArray* fArrayWR;      /**< Output array. */

    int mynev;
    int xring[triggerbox_number_of_boards][triggerbox_number_of_FPGA_per_board][num_channels];
    int xringch[triggerbox_number_of_boards][triggerbox_number_of_FPGA_per_board][num_channels];
    float xringang[triggerbox_number_of_boards][triggerbox_number_of_FPGA_per_board][num_channels];

    int xtboxring[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxch[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtbox[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxringch[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    float xtboxang[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxboard[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxinp[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxfpga[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxfpgach[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxcrock[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];
    int xtboxcrockch[triggerbox_number_of_boards * triggerbox_number_of_FPGA_per_board * num_channels];

    const char* finFileName;

  public:
    ClassDefOverride(R3BAsyKrabReader, 0);
};
#endif // R3BASYKRABREADER_H
