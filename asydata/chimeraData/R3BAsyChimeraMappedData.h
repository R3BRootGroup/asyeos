// -------------------------------------------------------------------------
// -----               R3BAsyChimeraMappedData header file             -----
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

#ifndef R3BASYCHIMERAMAPPEDITEM_H
#define R3BASYCHIMERAMAPPEDITEM_H

#include "TObject.h"

class R3BAsyChimeraMappedData : public TObject
{
  public:
    R3BAsyChimeraMappedData();
    R3BAsyChimeraMappedData(UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t, UInt_t);

    UInt_t GetNumTel() const;
    UInt_t GetFastHG() const;
    UInt_t GetFastLG() const;
    UInt_t GetSlowHG() const;
    UInt_t GetSlowLG() const;
    UInt_t GetTimeCsI() const;
    UInt_t GetSilHG() const;
    UInt_t GetSilLG() const;
    UInt_t GetTimeSil() const;
    UInt_t GetPatt() const;

  private:
    UInt_t fNumTel;
    UInt_t fFastHG;
    UInt_t fFastLG;
    UInt_t fSlowHG;
    UInt_t fSlowLG;
    UInt_t fTimeCsI;
    UInt_t fSilHG;
    UInt_t fSilLG;
    UInt_t fTimeSil;
    UInt_t fPatt;

  public:
    ClassDef(R3BAsyChimeraMappedData, 1)
};

#endif
