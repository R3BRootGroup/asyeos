// -----------------------------------------------------------------------
//								    ------
//  Factory for the parameter containers in libR3BAsyKrab        ------
//								    ------
// -----------------------------------------------------------------------

#include "R3BAsyKrabContFact.h"

#include "FairLogger.h"
#include "FairRuntimeDb.h"
#include "R3BAsyKrabCalPar.h"
#include "R3BAsyKrabHitPar.h"
#include "R3BLogger.h"
#include "R3BTGeoPar.h"
#include "TClass.h"

static R3BAsyKrabContFact gR3BAsyKrabContFact;

R3BAsyKrabContFact::R3BAsyKrabContFact() {
  // Constructor (called when the library is loaded)
  fName = "R3BAsyKrabContFact";
  fTitle = "Factory for parameter containers in libR3BAsyKrab";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void R3BAsyKrabContFact::setAllContainers() {
  // Creates the Container objects with all accepted contexts and adds them to
  // the list of containers for the STS library.

  FairContainer *p1 = new FairContainer("KrabCalPar", "Krab Cal Parameters",
                                        "KrabCalParContext");
  p1->addContext("KrabCalParContext");
  containers->Add(p1);

  FairContainer *p2 = new FairContainer("KrabHitPar", "Krab Hit Parameters",
                                        "KrabHitParContext");
  p2->addContext("KrabHitParContext");
  containers->Add(p2);

  FairContainer *p3 = new FairContainer(
      "KrabGeoPar", "Krab geometry parameters", "GeometryParameterContext");
  p3->addContext("GeometryParameterContext");
  containers->Add(p3);

  FairContainer *p4 = new FairContainer(
      "KrabMappingPar", "Krab mapping parameters", "KrabMappingContext");
  p4->addContext("KrabMappingContext");
  containers->Add(p4);
}

FairParSet *R3BAsyKrabContFact::createContainer(FairContainer *c) {
  // Trals the constructor of the corresponding parameter container.
  // For an actual context, which is not an empty string and not the default
  // context of this container, the name is concatinated with the context.

  const char *name = c->GetName();
  R3BLOG(info, "Create container name: " << name);
  FairParSet *p = 0;
  if (strcmp(name, "KrabCalPar") == 0) {
    p = new R3BAsyKrabCalPar(c->getConcatName().Data(), c->GetTitle(),
                             c->getContext());
  }

  if (strcmp(name, "KrabHitPar") == 0) {
    p = new R3BAsyKrabHitPar(c->getConcatName().Data(), c->GetTitle(),
                             c->getContext());
  }

  if (strcmp(name, "KrabGeoPar") == 0) {
    p = new R3BTGeoPar(c->getConcatName().Data(), c->GetTitle(),
                       c->getContext());
  }

  if (strcmp(name, "KrabMappingPar") == 0) {
    p = new R3BTGeoPar(c->getConcatName().Data(), c->GetTitle(),
                       c->getContext());
  }

  return p;
}

ClassImp(R3BAsyKrabContFact)
