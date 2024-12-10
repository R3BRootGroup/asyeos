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

#include "R3BAsyChimeraContFact.h"

#include "FairLogger.h"
#include "FairRuntimeDb.h"
#include "R3BAsyChimeraCalPar.h"
#include "R3BAsyChimeraHitPar.h"
#include "R3BLogger.h"
#include "R3BTGeoPar.h"
#include "TClass.h"

static R3BAsyChimeraContFact gR3BAsyChimeraContFact;

R3BAsyChimeraContFact::R3BAsyChimeraContFact() {
  // Constructor (called when the library is loaded)
  fName = "R3BAsyChimeraContFact";
  fTitle = "Factory for parameter containers in libR3BAsyChimera";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void R3BAsyChimeraContFact::setAllContainers() {
  // Creates the Container objects with all accepted contexts and adds them to
  // the list of containers for the STS library.

  FairContainer *p1 = new FairContainer(
      "ChimeraCalPar", "Chimera Cal Parameters", "ChimeraCalParContext");
  p1->addContext("ChimeraCalParContext");
  containers->Add(p1);

  FairContainer *p2 = new FairContainer(
      "ChimeraHitPar", "Chimera Hit Parameters", "ChimeraHitParContext");
  p2->addContext("ChimeraHitParContext");
  containers->Add(p2);

  FairContainer *p3 =
      new FairContainer("ChimeraGeoPar", "Chimera geometry parameters",
                        "GeometryParameterContext");
  p3->addContext("GeometryParameterContext");
  containers->Add(p3);
}

FairParSet *R3BAsyChimeraContFact::createContainer(FairContainer *c) {
  // Trals the constructor of the corresponding parameter container.
  // For an actual context, which is not an empty string and not the default
  // context of this container, the name is concatinated with the context.

  const char *name = c->GetName();
  R3BLOG(info, "Create container name: " << name);
  FairParSet *p = 0;
  if (strcmp(name, "ChimeraCalPar") == 0) {
    p = new R3BAsyChimeraCalPar(c->getConcatName().Data(), c->GetTitle(),
                                c->getContext());
  }

  if (strcmp(name, "ChimeraHitPar") == 0) {
    p = new R3BAsyChimeraHitPar(c->getConcatName().Data(), c->GetTitle(),
                                c->getContext());
  }

  if (strcmp(name, "ChimeraGeoPar") == 0) {
    p = new R3BTGeoPar(c->getConcatName().Data(), c->GetTitle(),
                       c->getContext());
  }

  return p;
}

ClassImp(R3BAsyChimeraContFact)
