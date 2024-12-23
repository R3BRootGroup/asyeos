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

#include "R3BAsyKrabHitData.h"

// -----   Default constructor   -------------------------------------------
R3BAsyKrabHitData::R3BAsyKrabHitData()
    : fCellId(0)
    , fELoss(0.)
    , fLight(0.)
    , fToF(0.)
{
}

// -----   Standard constructor   ------------------------------------------
R3BAsyKrabHitData::R3BAsyKrabHitData(Int_t ncell, Double_t eloss, Double_t light, Double_t tof)
    : fCellId(ncell)
    , fELoss(eloss)
    , fLight(light)
    , fToF(tof)
{
}
// -------------------------------------------------------------------------

ClassImp(R3BAsyKrabHitData)
