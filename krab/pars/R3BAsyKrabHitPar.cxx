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

#include "R3BAsyKrabHitPar.h"

#include <iostream>

#include "FairDetParIo.h"
#include "FairLogger.h"
#include "FairParamList.h"
#include "R3BLogger.h"
#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

// ---- Standard Constructor ---------------------------------------------------
R3BAsyKrabHitPar::R3BAsyKrabHitPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{
}

// ----  Destructor ------------------------------------------------------------
R3BAsyKrabHitPar::~R3BAsyKrabHitPar() { clear(); }

// ----  Method clear ----------------------------------------------------------
void R3BAsyKrabHitPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BAsyKrabHitPar::putParams(FairParamList* list)
{
    R3BLOG(info, "R3BAsyKrabHitPar::putParams() called");
    if (!list)
    {
        return;
    }
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BAsyKrabHitPar::getParams(FairParamList* list)
{
    R3BLOG(info, "R3BAsyKrabHitPar::getParams() called");
    if (!list)
    {
        R3BLOG(fatal, "Could not find FairParamList");
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method print ----------------------------------------------------------
void R3BAsyKrabHitPar::print() { printParams(); }

// ----  Method printParams ----------------------------------------------------
void R3BAsyKrabHitPar::printParams() { R3BLOG(info, "R3BAsyKrabHitPar::printParams() AsyKrab detector Parameters"); }

ClassImp(R3BAsyKrabHitPar);
