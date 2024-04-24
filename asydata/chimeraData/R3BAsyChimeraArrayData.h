// -------------------------------------------------------------------------
// -----              R3BAsyChimeraArrayData header file               -----
// -----    Created 19/04/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

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

#ifndef R3BASYCHIMERAARRAYITEM_H
#define R3BASYCHIMERAARRAYITEM_H

#include "TObject.h"
const int dmaxx = 128;

class R3BAsyChimeraArrayData : public TObject {
 public:
  R3BAsyChimeraArrayData();
  R3BAsyChimeraArrayData(UInt_t, UInt_t *, UInt_t *, UInt_t *, UInt_t *,
                         UInt_t *, UInt_t, UInt_t);
  virtual ~R3BAsyChimeraArrayData() {}

  UInt_t GetMulti() const;
  UInt_t GetDetectorId(int) const;
  UInt_t GetSideId(int) const;
  UInt_t GetStripId(int) const;
  UInt_t GetEnergy(int) const;
  UInt_t GetTime(int) const;
  UInt_t GetMultiE12() const;
  UInt_t GetMultiEFB1() const;

 private:
  UInt_t fMulti;
  UInt_t *fDet;        //[fMulti]
  UInt_t *fSide;       //[fMulti]
  UInt_t *fStrip;      //[fMulti]
  UInt_t *fRawEnergy;  //[fMulti]
  UInt_t *fRawTime;    //[fMulti]
  UInt_t fMultiE12;
  UInt_t fMultiEFB1;

 public:
  ClassDef(R3BAsyChimeraArrayData, 1)
};

#endif
