// -------------------------------------------------------------------------
// -----               R3BAsyChimeraIdData header file             -----
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

#ifndef R3BASYCHIMERAIDITEM_H
#define R3BASYCHIMERAIDITEM_H

#include "TObject.h"

class R3BAsyChimeraIdData : public TObject
{
  public:
    R3BAsyChimeraIdData();
    R3BAsyChimeraIdData(UInt_t, Float_t, Float_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, double, double);

    UInt_t GetNumTel() const;
    Float_t GetFast() const;
    Float_t GetSlow() const;
    UInt_t GetTimeCsI() const;
    UInt_t GetZ() const;
    UInt_t GetA() const;
    UInt_t GetStopped() const;
    UInt_t GetCode() const;
    UInt_t GetPID() const;
    double GetDE() const;
    double GetEnergy() const;

  private:
    UInt_t fNumTel;
    Float_t fFast;
    Float_t fSlow;
    UInt_t fTimeCsI;
    UInt_t fZ;
    UInt_t fA;
    UInt_t fStopped;
    UInt_t fCode;
    UInt_t fPID;
    double fDE;
    double fEnergy;

  public:
    ClassDef(R3BAsyChimeraIdData, 1)
};

#endif
