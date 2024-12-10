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

#include "R3BAsyChimeraHitData.h"

// -----   Default constructor   -------------------------------------------
R3BAsyChimeraHitData::R3BAsyChimeraHitData()
    : fDetId(0), fELoss(0.), fFast(0.), fSlow(0.), fToF(0.) {}

// -----   Standard constructor   ------------------------------------------
R3BAsyChimeraHitData::R3BAsyChimeraHitData(Int_t ndet, Double_t eloss,
                                           Double_t fast, Double_t slow,
                                           Double_t tof)
    : fDetId(ndet), fELoss(eloss), fFast(fast), fSlow(slow), fToF(tof) {}
// -------------------------------------------------------------------------

ClassImp(R3BAsyChimeraHitData)
