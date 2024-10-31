// --------------------------------------------------------------------------
// -----              R3BAsyKrabArrayData header file                  ------
// -----    Created 19/04/24  by E. De Filippo and P. Russotto         ------
// --------------------------------------------------------------------------

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

#ifndef R3BASYKRABARRAYITEM_H
#define R3BASYKRABARRAYITEM_H

#include "TObject.h"

class R3BAsyKrabArrayData : public TObject {
 public:
  R3BAsyKrabArrayData();
  R3BAsyKrabArrayData(UInt_t, Double_t, UInt_t *, UInt_t *, Float_t *);
  virtual ~R3BAsyKrabArrayData() {}

  UInt_t GetMulti() const;
  Double_t GetRP() const;
  UInt_t GetRing(int) const;
  UInt_t GetSector(int) const;
  Float_t GetPhi(int) const;

 private:
  UInt_t fMulti;
  Double_t fRP;
  UInt_t *fRing;    //[fMulti]
  UInt_t *fSector;  //[fMulti]
  Float_t *fPhi;    //[fMulti]

 public:
  ClassDef(R3BAsyKrabArrayData, 1)
};

#endif
