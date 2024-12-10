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

#include "R3BAsyKrabPhysData.h"

R3BAsyKrabPhysData::R3BAsyKrabPhysData() : fMulti(-1), fKRABRP(-1000) {}

R3BAsyKrabPhysData::R3BAsyKrabPhysData(UInt_t multi, Float_t krabrp)
    : fMulti(multi), fKRABRP(krabrp) {}

UInt_t R3BAsyKrabPhysData::GetMulti() const { return fMulti; }

Float_t R3BAsyKrabPhysData::GetRP() const { return fKRABRP; }

ClassImp(R3BAsyKrabPhysData)
