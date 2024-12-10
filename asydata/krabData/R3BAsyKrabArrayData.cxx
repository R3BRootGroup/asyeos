// ---------------------------------------------------------------------------
// -----                R3BAsyKrabArrayData source file                 ------
// ---------------------------------------------------------------------------

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

#include "R3BAsyKrabArrayData.h"

#include "FairLogger.h"

R3BAsyKrabArrayData::R3BAsyKrabArrayData()
    : fMulti(0), fRP(-1000), fRing(0), fSector(0), fPhi(0) {}

R3BAsyKrabArrayData::R3BAsyKrabArrayData(UInt_t multi, Double_t rp,
                                         UInt_t* ring, UInt_t* sector,
                                         Float_t* phi)
    : fMulti(multi), fRP(rp), fRing(ring), fSector(sector), fPhi(phi) {}

UInt_t R3BAsyKrabArrayData::GetMulti() const { return fMulti; }

Double_t R3BAsyKrabArrayData::GetRP() const { return fRP; }

UInt_t R3BAsyKrabArrayData::GetRing(int i) const { return fRing[i]; }

UInt_t R3BAsyKrabArrayData::GetSector(int i) const { return fSector[i]; }

Float_t R3BAsyKrabArrayData::GetPhi(int i) const { return fPhi[i]; }

ClassImp(R3BAsyKrabArrayData)
