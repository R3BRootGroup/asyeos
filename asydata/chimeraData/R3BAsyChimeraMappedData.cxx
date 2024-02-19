/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019-2024 Members of R3B Collaboration                     *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

#include "R3BAsyChimeraMappedData.h"

R3BAsyChimeraMappedData::R3BAsyChimeraMappedData()
    : fDetector(-1), fSide(-1), fStrip(-1), fEnergy(-1), fTime(-1) {}

R3BAsyChimeraMappedData::R3BAsyChimeraMappedData(UInt_t detector, UInt_t side,
                                                 UInt_t strip, UInt_t energy,
                                                 UInt_t time)
    : fDetector(detector),
      fSide(side),
      fStrip(strip),
      fEnergy(energy),
      fTime(time) {}

UInt_t R3BAsyChimeraMappedData::GetDetectorId() const { return fDetector; }

UInt_t R3BAsyChimeraMappedData::GetSideId() const { return fSide; }

UInt_t R3BAsyChimeraMappedData::GetStripId() const { return fStrip; }

UInt_t R3BAsyChimeraMappedData::GetEnergy() const { return fEnergy; }

UInt_t R3BAsyChimeraMappedData::GetTime() const { return fTime; }

ClassImp(R3BAsyChimeraMappedData)
