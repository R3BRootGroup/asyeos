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

#include "R3BAsyChiKrabPhysData.h"

// -----   Default constructor   -------------------------------------------
R3BAsyChiKrabPhysData::R3BAsyChiKrabPhysData()
    : fMulti_CHI(-10.)
    , fZBound_CHI(-10.)
    , fZRat_CHI(-10.)
    , fERat_CHI(-10.)
    , fRP_CHI(-1000.)
    , fMulti_KRAB(-10.)
    , fMultiR0_KRAB(-10.)
    , fMultiR14_KRAB(-10.)
    , fRP_KRAB(-1000.)
    , fRP_CHIKRAB(-1000.)
    , fdRP_CHIKRAB(-1000.)
{
}

// -----   Standard constructor   ------------------------------------------
R3BAsyChiKrabPhysData::R3BAsyChiKrabPhysData(Int_t Multi_CHI,
                                             Int_t ZBound_CHI,
                                             Float_t ZRat_CHI,
                                             Float_t ERat_CHI,
                                             Float_t RP_CHI,
                                             Int_t Multi_KRAB,
                                             Int_t MultiR0_KRAB,
                                             Int_t MultiR14_KRAB,
                                             Float_t RP_KRAB,
                                             Float_t RP_CHIKRAB,
                                             Float_t dRP_CHIKRAB)
    : fMulti_CHI(Multi_CHI)
    , fZBound_CHI(ZBound_CHI)
    , fZRat_CHI(ZRat_CHI)
    , fERat_CHI(ERat_CHI)
    , fRP_CHI(RP_CHI)
    , fMulti_KRAB(Multi_KRAB)
    , fMultiR0_KRAB(MultiR0_KRAB)
    , fMultiR14_KRAB(MultiR14_KRAB)
    , fRP_KRAB(RP_KRAB)
    , fRP_CHIKRAB(RP_CHIKRAB)
    , fdRP_CHIKRAB(dRP_CHIKRAB)
{
}
// -------------------------------------------------------------------------

ClassImp(R3BAsyChiKrabPhysData)
