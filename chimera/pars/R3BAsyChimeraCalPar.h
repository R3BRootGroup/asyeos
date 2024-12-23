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
// -----             R3BChimeraCalPar header file            ------
// -----   Created 27/03/23 by E. De Filippo and P. Russotto ------
// ----------------------------------------------------------------

#ifndef R3BAsyChimeraCalPar_H
#define R3BAsyChimeraCalPar_H 1

#include <Rtypes.h>
#include <stdint.h>

#include <vector>

#include "FairParGenericSet.h"
#include "TArrayF.h"
#include "TArrayI.h"

class FairParamList;

class R3BAsyChimeraCalPar : public FairParGenericSet
{
  public:
    /** Standard constructor **/
    R3BAsyChimeraCalPar(const char* name = "ChimeraCalPar",
                        const char* title = "Chimera Cal Parameters",
                        const char* context = "ChimeraCalParContext");

    /** Destructor **/
    virtual ~R3BAsyChimeraCalPar();

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
    const R3BAsyChimeraCalPar& operator=(const R3BAsyChimeraCalPar&);
    R3BAsyChimeraCalPar(const R3BAsyChimeraCalPar&);

  public:
    ClassDef(R3BAsyChimeraCalPar, 1);
};

#endif /* R3BAsyChimeraCalPar_H */
