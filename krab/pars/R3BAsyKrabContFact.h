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

// -----------------------------------------------------------------------
//								    ------
//  Factory for the parameter containers in libR3BAsyKrab           ------
//        created 24/10/2023 by E. De Filippo and P. Russotto	    ------
// -----------------------------------------------------------------------

#ifndef R3BAsyKrabContFact_H
#define R3BAsyKrabContFact_H 1

#include "FairContFact.h"

class FairContainer;

class R3BAsyKrabContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    R3BAsyKrabContFact();
    ~R3BAsyKrabContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef(R3BAsyKrabContFact, 0) // Factory for all Krab parameter containers
};

#endif /* R3BAsyKrabContFact_H */
