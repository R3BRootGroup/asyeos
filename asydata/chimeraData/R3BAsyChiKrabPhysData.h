// -------------------------------------------------------------------------
// -----               R3BAsyChiKrabPhysData header file             -----
// -----    Created 09/01/26  by P. Russotto         -----
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

#ifndef R3BASYCHIKRABPHYSDATA_H
#define R3BASYCHIKRABPHYSDATA_H

#include "TObject.h"
#include <TProfile.h>

class R3BAsyChiKrabPhysData : public TObject
{
  public:
   /** Default constructor **/
   R3BAsyChiKrabPhysData();
   /** Constructor with arguments
   **/
   R3BAsyChiKrabPhysData(Int_t Multi_CHI, Int_t ZBound_CHI, Float_t ZRat_CHI, Float_t ERat_CHI, Float_t RP_CHI, 
                          Int_t Multi_KRAB, Int_t MultiR0_KRAB, Int_t MultiR14_KRAB, Float_t RP_KRAB, 
                          Float_t RP_CHIKRAB, Float_t dRP_CHIKRAB);
   /** Destructor **/
   virtual ~R3BAsyChiKrabPhysData() {}

   /** Accessors **/
   Int_t GetMulti_CHI() const { return fMulti_CHI; };
   Int_t GetZBound_CHI() const { return fZBound_CHI; };
   Float_t GetZRat_CHI() const { return fZRat_CHI; };
   Float_t GetERat_CHI() const { return fERat_CHI; };
   Float_t GetRP_CHI() const { return fRP_CHI; };

   Int_t GetMulti_KRAB() const { return fMulti_KRAB; };
   Int_t GetMultiR0_KRAB() const { return fMultiR0_KRAB; };
   Int_t GetMultiR14_KRAB() const { return fMultiR14_KRAB; };
   Float_t GetRP_KRAB() const { return fRP_KRAB; };
 
   Float_t GetRP_CHIKRAB() const { return fRP_CHIKRAB; };
   Float_t GetdRP_CHIKRAB() const { return fdRP_CHIKRAB; };

  private:
    Int_t   fMulti_CHI;
    Int_t   fZBound_CHI;
    Float_t fZRat_CHI;
    Float_t fERat_CHI;
    Float_t fRP_CHI;
    
    Int_t   fMulti_KRAB;
    Int_t   fMultiR0_KRAB;
    Int_t   fMultiR14_KRAB;
    Float_t fRP_KRAB;
    
    Float_t fRP_CHIKRAB;
    Float_t fdRP_CHIKRAB;

  public:
    ClassDef(R3BAsyChiKrabPhysData, 1)
};

#endif
