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

// ----------------------------------------------------------------
// -----             R3BKrabCalPar header file            ------
// -----   Created 24/10/23 by E. De Filippo and P. Russotto ------
// ----------------------------------------------------------------

#ifndef R3BAsyKrabCalPar_H
#define R3BAsyKrabCalPar_H 1

#include <Rtypes.h>
#include <stdint.h>

#include <vector>

#include "FairParGenericSet.h"
#include "TArrayF.h"
#include "TArrayI.h"

class FairParamList;

class R3BAsyKrabCalPar : public FairParGenericSet
{
  public:
    /** Standard constructor **/
    R3BAsyKrabCalPar(const char* name = "KrabCalPar",
                     const char* title = "Krab Cal Parameters",
                     const char* context = "KrabCalParContext");

    /** Destructor **/
    virtual ~R3BAsyKrabCalPar();

    /** Method to reset all parameters **/
    virtual void clear();

    /** Method to store all parameters using FairRuntimeDB **/
    virtual void putParams(FairParamList* list);

    /** Method to retrieve all parameters using FairRuntimeDB**/
    Bool_t getParams(FairParamList* list);

    /** Method to print values of parameters to the standard output **/
    virtual void print();
    void printParams();

    /** Accessor functions **/
    // not yet defined

  private:
    // private params not yet defined
    const R3BAsyKrabCalPar& operator=(const R3BAsyKrabCalPar&);
    R3BAsyKrabCalPar(const R3BAsyKrabCalPar&);

  public:
    ClassDef(R3BAsyKrabCalPar, 1);
};

#endif /* R3BAsyKrabCalPar_H */
