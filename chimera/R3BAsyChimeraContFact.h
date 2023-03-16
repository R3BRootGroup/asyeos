// ----------------------------------------------------------------------
//								    -----
//  Factory for the parameter containers in libR3BAsyChimera           -----
//								    -----
// ----------------------------------------------------------------------

#ifndef R3BAsyChimeraContFact_H
#define R3BAsyChimeraContFact_H

#include "FairContFact.h"

class FairContainer;

class R3BAsyChimeraContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    R3BAsyChimeraContFact();
    ~R3BAsyChimeraContFact() {}
    FairParSet* createContainer(FairContainer*);
    void activateParIo(FairParIo* io);
    ClassDef(R3BAsyChimeraContFact, 0) // Factory for all TofWall parameter containers
};

#endif /* !R3BAsyChimeraContFact_H */
