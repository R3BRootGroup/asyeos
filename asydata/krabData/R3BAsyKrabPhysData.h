// -------------------------------------------------------------------------
// -----               R3BAsyKrabPhysData header file             -----
// -----    Created 11/10/24  by E. De Filippo and P. Russotto         -----
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

#ifndef R3BASYKRABPHYSITEM_H
#define R3BASYKRABPHYSITEM_H

#include "TObject.h"

class R3BAsyKrabPhysData : public TObject {
 public:
  R3BAsyKrabPhysData();
  R3BAsyKrabPhysData(UInt_t, Float_t);

  UInt_t GetMulti() const;
  Float_t GetRP() const;

 private:
  UInt_t fMulti;
  Float_t fKRABRP;

 public:
  ClassDef(R3BAsyKrabPhysData, 1)
};

#endif
