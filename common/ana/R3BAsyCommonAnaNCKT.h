// -------------------------------------------------------------------------
// -----            R3BAsyCommonAnaNCKT header file             -----
// -----    Created 15/10/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

/******************************************************************************
 *   Copyright (C) 2022 GSI Helmholtzzentrum f�r Schwerionenforschung GmbH    *
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

#ifndef R3BAsyCommonAnaNCKT_H
#define R3BAsyCommonAnaNCKT_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairTask.h"
#include "R3BAsyChimeraPhysData.h"
#include "R3BAsyKrabPhysData.h"
#include "R3BAsyKrabPhysData.h"
#include "R3BPaddleTamexMappedData.h"
#include "R3BTofdMappedData.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"
#include "TProfile.h"

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyCommonAnaNCKT : public FairTask
{
  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    R3BAsyCommonAnaNCKT();

    /**
     * Standard constructor.
     * Creates an instance of the task.
     * @param name a name of the task.
     * @param iVerbose a verbosity level.
     */
    R3BAsyCommonAnaNCKT(const char* name, Int_t iVerbose = 1);

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~R3BAsyCommonAnaNCKT();

    /**
     * Method for task initialization.
     * This function is called by the framework before
     * the event loop.
     * @return Initialization status. kSUCCESS, kERROR or kFATAL.
     */
    virtual InitStatus Init();

    /**
     * Method for event loop implementation.
     * Is called by the framework every time a new event is read.
     * @param option an execution option.
     */
    virtual void Exec(Option_t* option);

    /**
     * A method for finish of processing of an event.
     * Is called by the framework for each event after executing
     * the tasks.
     */
    virtual void FinishEvent();

    /**
     * Method for finish of the task execution.
     * Is called by the framework after processing the event loop.
     */
    virtual void FinishTask();

    /**
     * Methods to clean histograms.
     */
    virtual void Reset_Histo();
    inline void SetOnline(bool option) { fOnline = option; }

  private:
    TClonesArray* fPhysItemsChimera;
    TClonesArray* fPhysItemsKrab;
    TClonesArray* fNeulandMappedData;
    TClonesArray* fTofdMappedData;
    bool fOnline = false;

    // check for trigger should be done globablly (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */

    // Canvas

    TCanvas* c_NCKT;
    TH2I* fh2_KRAB_Tofd_multi;
    TH2I* fh2_CHIMERA_Tofd_multi;
    TProfile* fp_KRAB_Tofd_multi;
    TProfile* fp_CHIMERA_Tofd_multi;
    TH2I* fh2_CHIMERA_NL_multi;
    TH2I* fh2_KRAB_NL_multi;
    TProfile* fp_CHIMERA_NL_multi;
    TProfile* fp_KRAB_NL_multi;
   
  public:
    ClassDef(R3BAsyCommonAnaNCKT, 1)
};

#endif
