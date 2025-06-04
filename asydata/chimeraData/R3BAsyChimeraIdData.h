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
<<<<<<< HEAD
    R3BAsyChimeraIdData(UInt_t, Float_t, Float_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, double, double);
=======
    R3BAsyChimeraIdData(UInt_t, Float_t, Float_t, UInt_t, Int_t, Int_t, Int_t, Int_t, Float_t, double, double);
>>>>>>> 9e0f3f8 (new classes for chimera ID and nergy calibration)

    UInt_t GetNumTel() const;
    Float_t GetFast() const;
    Float_t GetSlow() const;
    UInt_t GetTimeCsI() const;
<<<<<<< HEAD
    UInt_t GetZ() const;
    UInt_t GetA() const;
    UInt_t GetStopped() const;
    UInt_t GetCode() const;
    UInt_t GetPID() const;
=======
    Int_t GetZ() const;
    Int_t GetA() const;
    Int_t GetStopped() const;
    Int_t GetCode() const;
    Float_t GetPID() const;
>>>>>>> 9e0f3f8 (new classes for chimera ID and nergy calibration)
    double GetDE() const;
    double GetEnergy() const;

  private:
    UInt_t fNumTel;
    Float_t fFast;
    Float_t fSlow;
    UInt_t fTimeCsI;
<<<<<<< HEAD
    UInt_t fZ;
    UInt_t fA;
    UInt_t fStopped;
    UInt_t fCode;
    UInt_t fPID;
=======
    Int_t fZ;
    Int_t fA;
    Int_t fStopped;
    Int_t fCode;
    Float_t fPID;
>>>>>>> 9e0f3f8 (new classes for chimera ID and nergy calibration)
    double fDE;
    double fEnergy;

  public:
    ClassDef(R3BAsyChimeraIdData, 1)
};

#endif
