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

#include "R3BAsyChimeraMatchedData.h"

R3BAsyChimeraMatchedData::R3BAsyChimeraMatchedData()
    : fNumTel(-1)
    , fFast(-1)
    , fSlow(-1)
    , fTimeCsI(-1)
{
}

R3BAsyChimeraMatchedData::R3BAsyChimeraMatchedData(UInt_t numtel, Float_t fast, Float_t slow, UInt_t timeCsI)
    : fNumTel(numtel)
    , fFast(fast)
    , fSlow(slow)
    , fTimeCsI(timeCsI)
{
}

UInt_t R3BAsyChimeraMatchedData::GetNumTel() const { return fNumTel; }

Float_t R3BAsyChimeraMatchedData::GetFast() const { return fFast; }

Float_t R3BAsyChimeraMatchedData::GetSlow() const { return fSlow; }

UInt_t R3BAsyChimeraMatchedData::GetTimeCsI() const { return fTimeCsI; }

ClassImp(R3BAsyChimeraMatchedData)
