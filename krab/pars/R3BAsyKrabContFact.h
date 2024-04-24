// -----------------------------------------------------------------------
//								    ------
//  Factory for the parameter containers in libR3BAsyKrab           ------
//        created 24/10/2023 by E. De Filippo and P. Russotto	    ------
// -----------------------------------------------------------------------

#ifndef R3BAsyKrabContFact_H
#define R3BAsyKrabContFact_H 1

#include "FairContFact.h"

class FairContainer;

class R3BAsyKrabContFact : public FairContFact {
 private:
  void setAllContainers();

 public:
  R3BAsyKrabContFact();
  ~R3BAsyKrabContFact() {}
  FairParSet* createContainer(FairContainer*);
  ClassDef(R3BAsyKrabContFact, 0)  // Factory for all Krab parameter containers
};

#endif /* R3BAsyKrabContFact_H */
