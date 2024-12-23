// -------------------------------------------------------------------------
// -----               R3BAsyChimeraPhysData header file             -----
// -----    Created 11/10/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

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

#ifndef R3BASYCHIMERAPHYSITEM_H
#define R3BASYCHIMERAPHYSITEM_H

#include "TObject.h"

class R3BAsyChimeraPhysData : public TObject
{
  public:
    R3BAsyChimeraPhysData();
    R3BAsyChimeraPhysData(UInt_t, Float_t);

    UInt_t GetMulti() const;
    Float_t GetRP() const;

  private:
    UInt_t fMulti;
    Float_t fCHIRP;

  public:
    ClassDef(R3BAsyChimeraPhysData, 1)
};

#endif
