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

// ------------------------------------------------------------------
// -----                R3BKrabCalPar source file           ------
// ------------------------------------------------------------------

#include "R3BAsyKrabCalPar.h"

#include "FairDetParIo.h"
#include "FairLogger.h"
#include "FairParamList.h"
#include "R3BLogger.h"
#include "TArrayF.h"
#include "TArrayI.h"
#include "TMath.h"
#include "TString.h"

// ---- Standard Constructor ---------------------------------------------------
R3BAsyKrabCalPar::R3BAsyKrabCalPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)

{
    // just template, start version
}

// ----  Destructor ------------------------------------------------------------
R3BAsyKrabCalPar::~R3BAsyKrabCalPar() { clear(); }

// ----  Method clear ----------------------------------------------------------
void R3BAsyKrabCalPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BAsyKrabCalPar::putParams(FairParamList* list)
{
    R3BLOG(info, "called");
    if (!list)
    {
        R3BLOG(fatal, "Could not find FairParamList");
        return;
    }
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BAsyKrabCalPar::getParams(FairParamList* list)
{
    R3BLOG(info, "called");
    if (!list)
    {
        R3BLOG(fatal, "Could not find FairParamList");
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method print ----------------------------------------------------------
void R3BAsyKrabCalPar::print() { printParams(); }

// ----  Method printParams ----------------------------------------------------
void R3BAsyKrabCalPar::printParams() { R3BLOG(info, "Krab parameters not yet defined"); }

ClassImp(R3BAsyKrabCalPar);
