// ----------------------------------------------------------------------
//								    -----
//  Factory for the parameter containers in libR3BAsyChimera           -----
//         Created 03/11/19  by J.L. Rodriguez-Sanchez              -----
//								    -----
// ----------------------------------------------------------------------

#include "R3BAsyChimeraContFact.h"
//#include "R3BAsyChimeraCalPar.h"
#include "R3BTGeoPar.h"

#include "FairLogger.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairRuntimeDb.h"
#include "TClass.h"

static R3BAsyChimeraContFact gR3BAsyChimeraContFact;

R3BAsyChimeraContFact::R3BAsyChimeraContFact()
{
    // Constructor (called when the library is loaded)
    fName = "R3BAsyChimeraContFact";
    fTitle = "Factory for parameter containers in libR3BAsyChimera";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void R3BAsyChimeraContFact::setAllContainers()
{
    // Creates the Container objects with all accepted contexts and adds them to
    // the list of containers for the TofW library.

    FairContainer* p1 = new FairContainer("tofwCalPar", "TofW Cal Parameters", "TofWCalParContext");
    p1->addContext("TofWCalParContext");

    containers->Add(p1);

    FairContainer* p2 = new FairContainer("tofwGeoPar", "TofW geometry parameters", "TestDefaultContext");
    p2->addContext("TestNonDefaultContext");

    containers->Add(p2);
}

FairParSet* R3BAsyChimeraContFact::createContainer(FairContainer* c)
{
    // Trals the constructor of the corresponding parameter container.
    // For an actual context, which is not an empty string and not the default context
    // of this container, the name is concatinated with the context.

    const char* name = c->GetName();
    LOG(INFO) << "R3BAsyChimeraContFact: Create container name: " << name;
    FairParSet* p = 0;
    if (strcmp(name, "tofwCalPar") == 0)
    {
        // p = new R3BAsyChimeraCalPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());//FIXME
    }

    if (strcmp(name, "tofwGeoPar") == 0)
    {
        p = new R3BTGeoPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return p;
}

void R3BAsyChimeraContFact::activateParIo(FairParIo* io)  
{
    // activates the input/output class for the parameters
    // needed by the tofw
    /*
    if (strcmp(io->IsA()->GetName(),"FairParRootFileIo")==0) {
      R3BAsyChimeraParRootFileIo* p=new R3BAsyChimeraParRootFileIo(((FairParRootFileIo*)io)->getParRootFile());
      io->setDetParIo(p);
    }
    if (strcmp(io->IsA()->GetName(),"FairParAsciiFileIo")==0) {
      R3BAsyChimeraParAsciiFileIo* p=new R3BAsyChimeraParAsciiFileIo(((FairParAsciiFileIo*)io)->getFile());
      io->setDetParIo(p);
      }
    */
}

ClassImp(R3BAsyChimeraContFact)
