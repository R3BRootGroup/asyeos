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

#include "R3BAsyChimeraIdData.h"

R3BAsyChimeraIdData::R3BAsyChimeraIdData()
    : fNumTel(-1)
    , fFast(-1)
    , fSlow(-1)
    , fTimeCsI(-1)
    , fZ(-1)
    , fA(-1)
    , fStopped(-1)
    , fCode(-1)
    , fPID(-1)
    , fDE(-1)
    , fEnergy(-1)
{
}

R3BAsyChimeraIdData::R3BAsyChimeraIdData(UInt_t numtel,
                                         Float_t fast,
                                         Float_t slow,
					 UInt_t timeCsI,
                                         UInt_t Z,
                                         UInt_t A,
					 UInt_t Stopped,
					 UInt_t Code,
					 UInt_t PID,
                                         double DE,
					 double Energy)
    : fNumTel(numtel)
    , fFast(fast)
    , fSlow(slow)
    , fTimeCsI(timeCsI)
    , fZ(Z)
    , fA(A)
    , fStopped(Stopped)
    , fCode(Code)
    , fPID(PID)
    , fDE(DE)
    , fEnergy(Energy)
{
}

UInt_t R3BAsyChimeraIdData::GetNumTel() const { return fNumTel; }

Float_t R3BAsyChimeraIdData::GetFast() const { return fFast; }

Float_t R3BAsyChimeraIdData::GetSlow() const { return fSlow; }

UInt_t R3BAsyChimeraIdData::GetZ() const { return fZ; }

UInt_t R3BAsyChimeraIdData::GetA() const { return fA; }

UInt_t R3BAsyChimeraIdData::GetTimeCsI() const { return fTimeCsI; }

UInt_t R3BAsyChimeraIdData::GetStopped() const { return fStopped; }

UInt_t R3BAsyChimeraIdData::GetCode() const { return fCode; }

UInt_t R3BAsyChimeraIdData::GetPID() const { return fPID; }

double R3BAsyChimeraIdData::GetDE() const { return fDE; }

double R3BAsyChimeraIdData::GetEnergy() const { return fEnergy; }


ClassImp(R3BAsyChimeraIdData)
