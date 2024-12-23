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

#include "R3BAsyChimeraMappedData.h"

R3BAsyChimeraMappedData::R3BAsyChimeraMappedData()
    : fNumTel(-1)
    , fFastHG(-1)
    , fFastLG(-1)
    , fSlowHG(-1)
    , fSlowLG(-1)
    , fTimeCsI(-1)
    , fSilHG(-1)
    , fSilLG(-1)
    , fTimeSil(-1)
    , fPatt(-1)
{
}

R3BAsyChimeraMappedData::R3BAsyChimeraMappedData(UInt_t numtel,
                                                 UInt_t fastHG,
                                                 UInt_t fastLG,
                                                 UInt_t slowHG,
                                                 UInt_t slowLG,
                                                 UInt_t timeCsI,
                                                 UInt_t silHG,
                                                 UInt_t silLG,
                                                 UInt_t timeSil,
                                                 UInt_t patt)
    : fNumTel(numtel)
    , fFastHG(fastHG)
    , fFastLG(slowLG)
    , fSlowHG(slowHG)
    , fSlowLG(slowLG)
    , fTimeCsI(timeCsI)
    , fSilHG(silHG)
    , fSilLG(silLG)
    , fTimeSil(timeSil)
    , fPatt(patt)
{
}

UInt_t R3BAsyChimeraMappedData::GetNumTel() const { return fNumTel; }

UInt_t R3BAsyChimeraMappedData::GetFastHG() const { return fFastHG; }

UInt_t R3BAsyChimeraMappedData::GetFastLG() const { return fFastLG; }

UInt_t R3BAsyChimeraMappedData::GetSlowHG() const { return fSlowHG; }

UInt_t R3BAsyChimeraMappedData::GetSlowLG() const { return fSlowLG; }

UInt_t R3BAsyChimeraMappedData::GetTimeCsI() const { return fTimeCsI; }

UInt_t R3BAsyChimeraMappedData::GetSilHG() const { return fSilHG; }

UInt_t R3BAsyChimeraMappedData::GetSilLG() const { return fSilLG; }

UInt_t R3BAsyChimeraMappedData::GetTimeSil() const { return fTimeSil; }

UInt_t R3BAsyChimeraMappedData::GetPatt() const { return fPatt; }

ClassImp(R3BAsyChimeraMappedData)
