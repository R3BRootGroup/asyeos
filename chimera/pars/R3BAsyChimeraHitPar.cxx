/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019-2023 Members of R3B Collaboration                     *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

// -------------------------------------------------------------------
// -----             R3BAsyChimeraHitPar source file            ------
// -------------------------------------------------------------------

#include "FairDetParIo.h"
#include "FairLogger.h"
#include "FairParamList.h"

#include "R3BAsyChimeraHitPar.h"
#include "R3BLogger.h"

#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

// ---- Standard Constructor ---------------------------------------------------
R3BAsyChimeraHitPar::R3BAsyChimeraHitPar(const char *name, const char *title,
                                         const char *context)
    : FairParGenericSet(name, title, context) {}

// ----  Destructor ------------------------------------------------------------
R3BAsyChimeraHitPar::~R3BAsyChimeraHitPar() { clear(); }

// ----  Method clear ----------------------------------------------------------
void R3BAsyChimeraHitPar::clear() {
  status = kFALSE;
  resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BAsyChimeraHitPar::putParams(FairParamList *list) {
  R3BLOG(info, "R3BAsyChimeraHitPar::putParams() called");
  if (!list) {
    return;
  }
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BAsyChimeraHitPar::getParams(FairParamList *list) {
  R3BLOG(info, "R3BAsyChimeraHitPar::getParams() called");
  if (!list) {
    R3BLOG(fatal, "Could not find FairParamList");
    return kFALSE;
  }

  return kTRUE;
}

// ----  Method print ----------------------------------------------------------
void R3BAsyChimeraHitPar::print() { printParams(); }

// ----  Method printParams ----------------------------------------------------
void R3BAsyChimeraHitPar::printParams() {
  R3BLOG(info,
         "R3BAsyChimeraHitPar::printParams() AsyChimera detector Parameters");
}

ClassImp(R3BAsyChimeraHitPar);
