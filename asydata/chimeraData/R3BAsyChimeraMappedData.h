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

#ifndef R3BASYCHIMERAMAPPEDITEM_H
#define R3BASYCHIMERAMAPPEDITEM_H

#include "TObject.h"

class R3BAsyChimeraMappedData : public TObject {
 public:
  R3BAsyChimeraMappedData();
  R3BAsyChimeraMappedData(UInt_t, UInt_t, UInt_t, UInt_t, UInt_t);

  UInt_t GetDetectorId() const;
  UInt_t GetSideId() const;
  UInt_t GetStripId() const;
  UInt_t GetEnergy() const;
  UInt_t GetTime() const;

 private:
  UInt_t fDetector;  // 1..n
  UInt_t fSide;      // 1 = front, 2 = back
  UInt_t fStrip;     // 0..31
  UInt_t fEnergy;
  UInt_t fTime;

 public:
  ClassDef(R3BAsyChimeraMappedData, 1)
};

#endif
