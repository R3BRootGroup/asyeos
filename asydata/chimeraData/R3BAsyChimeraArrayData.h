// -------------------------------------------------------------------------
// -----              R3BAsyChimeraArrayData header file               -----
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

#ifndef R3BASYCHIMERAARRAYITEM_H
#define R3BASYCHIMERAARRAYITEM_H

#include "TObject.h"
const int dmaxx = 512;

class R3BAsyChimeraArrayData : public TObject
{
  public:
    R3BAsyChimeraArrayData();
    R3BAsyChimeraArrayData(UInt_t,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t*,
                           UInt_t,
                           UInt_t);
    virtual ~R3BAsyChimeraArrayData() {}

    UInt_t GetMulti() const;
    UInt_t GetNumTel(int) const;
    UInt_t GetFastHG(int) const;
    UInt_t GetFastLG(int) const;
    UInt_t GetSlowHG(int) const;
    UInt_t GetSlowLG(int) const;
    UInt_t GetTimeCsI(int) const;
    UInt_t GetSilHG(int) const;
    UInt_t GetSilLG(int) const;
    UInt_t GetTimeSil(int) const;
    UInt_t GetMultiCsI() const;
    UInt_t GetMultiSil() const;

  private:
    UInt_t fMulti;
    UInt_t* fNumTel;  //[fMulti]
    UInt_t* fFastHG;  //[fMulti]
    UInt_t* fFastLG;  //[fMulti]
    UInt_t* fSlowHG;  //[fMulti]
    UInt_t* fSlowLG;  //[fMulti]
    UInt_t* fTimeCsI; //[fMulti]
    UInt_t* fSilHG;   //[fMulti]
    UInt_t* fSilLG;   //[fMulti]
    UInt_t* fTimeSil; //[fMulti]
    UInt_t fMultiCsI;
    UInt_t fMultiSil;

  public:
    ClassDef(R3BAsyChimeraArrayData, 1)
};

#endif
