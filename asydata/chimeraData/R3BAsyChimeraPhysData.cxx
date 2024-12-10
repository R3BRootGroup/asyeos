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

#include "R3BAsyChimeraPhysData.h"

R3BAsyChimeraPhysData::R3BAsyChimeraPhysData() : fMulti(-1), fCHIRP(-1000) {}

R3BAsyChimeraPhysData::R3BAsyChimeraPhysData(UInt_t multi, Float_t chirp)
    : fMulti(multi), fCHIRP(chirp) {}

UInt_t R3BAsyChimeraPhysData::GetMulti() const { return fMulti; }

Float_t R3BAsyChimeraPhysData::GetRP() const { return fCHIRP; }

ClassImp(R3BAsyChimeraPhysData)
