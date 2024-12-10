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
// -----                R3BChimeraCalPar source file           ------
// ------------------------------------------------------------------

#include "R3BAsyChimeraCalPar.h"

#include "FairDetParIo.h"
#include "FairLogger.h"
#include "FairParamList.h"
#include "R3BLogger.h"
#include "TArrayF.h"
#include "TArrayI.h"
#include "TMath.h"
#include "TString.h"

// ---- Standard Constructor ---------------------------------------------------
R3BAsyChimeraCalPar::R3BAsyChimeraCalPar(const char *name, const char *title,
                                         const char *context)
    : FairParGenericSet(name, title, context)

{
  // just template, start version
}

// ----  Destructor ------------------------------------------------------------
R3BAsyChimeraCalPar::~R3BAsyChimeraCalPar() { clear(); }

// ----  Method clear ----------------------------------------------------------
void R3BAsyChimeraCalPar::clear() {
  status = kFALSE;
  resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BAsyChimeraCalPar::putParams(FairParamList *list) {
  R3BLOG(info, "called");
  if (!list) {
    R3BLOG(fatal, "Could not find FairParamList");
    return;
  }
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BAsyChimeraCalPar::getParams(FairParamList *list) {
  R3BLOG(info, "called");
  if (!list) {
    R3BLOG(fatal, "Could not find FairParamList");
    return kFALSE;
  }

  return kTRUE;
}

// ----  Method print ----------------------------------------------------------
void R3BAsyChimeraCalPar::print() { printParams(); }

// ----  Method printParams ----------------------------------------------------
void R3BAsyChimeraCalPar::printParams() {
  R3BLOG(info, "Chimera parameters not yet defined");
}

ClassImp(R3BAsyChimeraCalPar);
