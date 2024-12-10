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

#ifndef R3BAsyKrabHitPar_H
#define R3BAsyKrabHitPar_H 1

#include <TObjString.h>

#include <iostream>
#include <vector>

#include "FairDetParIo.h"
#include "FairLogger.h"
#include "FairParGenericSet.h"
#include "FairParamList.h"
#include "R3BTsplinePar.h"
#include "TArrayF.h"
#include "TArrayI.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TObject.h"
#include "TSpline.h"
#include "TString.h"

class FairParamList;

class R3BAsyKrabHitPar : public FairParGenericSet {
 public:
  /** Standard constructor **/
  R3BAsyKrabHitPar(const char* name = "AsyKrabHitPar",
                   const char* title = "AsyKrab Hit Parameters",
                   const char* context = "AsyKrabHitParContext");

  /** Destructor **/
  virtual ~R3BAsyKrabHitPar();

  /** Method to reset all parameters **/
  virtual void clear();

  /** Method to store all parameters using FairRuntimeDB **/
  virtual void putParams(FairParamList* list);

  /** Method to retrieve all parameters using FairRuntimeDB**/
  Bool_t getParams(FairParamList* list);

  /** Method to print values of parameters to the standard output **/
  virtual void print();
  void printParams();

  // Create more Methods if you need them!

 private:
  const R3BAsyKrabHitPar& operator=(
      const R3BAsyKrabHitPar&);              /*< an assignment operator>*/
  R3BAsyKrabHitPar(const R3BAsyKrabHitPar&); /*< a copy constructor >*/

  ClassDef(R3BAsyKrabHitPar, 1);
};

#endif
