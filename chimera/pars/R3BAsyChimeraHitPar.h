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

// ---------------------------------------------------------------
// -----            R3BAsyChimeraHitPar header file         ------
// ----- Created 27/03/23 by E. De Filippo and P. Russotto  ------
// ---------------------------------------------------------------

#ifndef R3BAsyChimeraHitPar_H
#define R3BAsyChimeraHitPar_H 1

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

class R3BAsyChimeraHitPar : public FairParGenericSet
{
  public:
    /** Standard constructor **/
    R3BAsyChimeraHitPar(const char* name = "AsyChimeraHitPar",
                        const char* title = "AsyChimera Hit Parameters",
                        const char* context = "AsyChimeraHitParContext");

    /** Destructor **/
    virtual ~R3BAsyChimeraHitPar();

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
    const R3BAsyChimeraHitPar& operator=(const R3BAsyChimeraHitPar&); /*< an assignment operator>*/
    R3BAsyChimeraHitPar(const R3BAsyChimeraHitPar&);                  /*< a copy constructor >*/

    ClassDef(R3BAsyChimeraHitPar, 1);
};

#endif
