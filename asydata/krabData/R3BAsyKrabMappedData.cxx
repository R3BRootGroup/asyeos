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

#include "R3BAsyKrabMappedData.h"

R3BAsyKrabMappedData::R3BAsyKrabMappedData()
    : fRing(-1), fSector(-1), fPhi(-1000), fqx(-1000), fqy(-1000) {}

R3BAsyKrabMappedData::R3BAsyKrabMappedData(UInt_t ring, UInt_t sector,
                                           Float_t phi, Float_t qx, Float_t qy)
    : fRing(ring), fSector(sector), fPhi(phi), fqx(qx), fqy(qy) {}

UInt_t R3BAsyKrabMappedData::GetRing() const { return fRing; }

UInt_t R3BAsyKrabMappedData::GetSector() const { return fSector; }

Float_t R3BAsyKrabMappedData::GetPhi() const { return fPhi; }

Float_t R3BAsyKrabMappedData::Getqx() const { return fqx; }

Float_t R3BAsyKrabMappedData::Getqy() const { return fqy; }

ClassImp(R3BAsyKrabMappedData)
