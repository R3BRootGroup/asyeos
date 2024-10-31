// --------------------------------------------------------------------------
// -----              R3BAsyKrabMappedData header file                 ------
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

#ifndef R3BASYKRABMAPPEDITEM_H
#define R3BASYKRABMAPPEDITEM_H

#include "TObject.h"

class R3BAsyKrabMappedData : public TObject {
 public:
  R3BAsyKrabMappedData();
  R3BAsyKrabMappedData(UInt_t, UInt_t, Float_t, Float_t, Float_t);

  UInt_t GetRing() const;
  UInt_t GetSector() const;
  Float_t GetPhi() const;
  Float_t Getqx() const;
  Float_t Getqy() const;

 private:
  UInt_t fRing;
  UInt_t fSector;
  Float_t fPhi;
  Float_t fqx;
  Float_t fqy;

 public:
  ClassDef(R3BAsyKrabMappedData, 1)
};

#endif
