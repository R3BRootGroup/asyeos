// -----------------------------------------------------------------------
//								    ------
//  Factory for the parameter containers in libR3BAsyChimera        ------
//        created 27/03/2023 by E. De Filippo and P. Russotto	    ------
// -----------------------------------------------------------------------

#ifndef R3BAsyChimeraContFact_H
#define R3BAsyChimeraContFact_H 1

#include "FairContFact.h"

class FairContainer;

class R3BAsyChimeraContFact : public FairContFact {
 private:
  void setAllContainers();

 public:
  R3BAsyChimeraContFact();
  ~R3BAsyChimeraContFact() {}
  FairParSet* createContainer(FairContainer*);
  ClassDef(R3BAsyChimeraContFact,
           0)  // Factory for all Chimera parameter containers
};

#endif /* R3BAsyChimeraContFact_H */
