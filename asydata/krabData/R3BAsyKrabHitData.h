// -------------------------------------------------------------------
// -----          R3BAsyKrabHitData header file                 ------
// -----    Created 24/10/23  by E. De Filippo and P. Russotto  ------
// -------------------------------------------------------------------

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

#ifndef R3BAsyKrabHitData_H
#define R3BAsyKrabHitData_H
#include "TObject.h"

class R3BAsyKrabHitData : public TObject
{
  public:
    /** Default constructor **/
    R3BAsyKrabHitData();

    /** Constructor with arguments
     *@param fCellId  Cell number
     *@param fEloss  Energy Loss in [MeV]
     *@param fLight  Light in arb. units
     *@param fToF    Tof in [ns]
     **/
    R3BAsyKrabHitData(Int_t CellId, Double_t ELoss, Double_t Light, Double_t ToF);

    /** Destructor **/
    virtual ~R3BAsyKrabHitData() {}

    /** Accessors **/
    Int_t GetCellId() const { return fCellId; }
    Double_t GetEloss() const { return fELoss; }
    Double_t GetLight() const { return fLight; }
    Double_t GetToF() const { return fToF; }

    /** Modifiers **/
    void SetCellID(Int_t ncell) { fCellId = ncell; };
    void SetELoss(Double_t eloss) { fELoss = eloss; };
    void SetLight(Double_t light) { fLight = light; };
    void SetTof(Double_t t) { fToF = t; };

  private:
    Int_t fCellId;
    Double_t fELoss, fLight, fToF;

    ClassDef(R3BAsyKrabHitData, 1)
};

#endif
