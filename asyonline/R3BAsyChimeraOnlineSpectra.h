// -------------------------------------------------------------------------
// -----            R3BAsyChimeraOnlineSpectra header file             -----
// -----    Created 15/10/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

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

#ifndef R3BAsyChimeraOnlineSpectra_H
#define R3BAsyChimeraOnlineSpectra_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairTask.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyChimeraOnlineSpectra : public FairTask
{
  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    R3BAsyChimeraOnlineSpectra();

    /**
     * Standard constructor.
     * Creates an instance of the task.
     * @param name a name of the task.
     * @param iVerbose a verbosity level.
     */
    R3BAsyChimeraOnlineSpectra(const char* name, Int_t iVerbose = 1);

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~R3BAsyChimeraOnlineSpectra();

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

  private:
    TClonesArray* fMappedItemsChimera; /**< Array with chimera mapped items. */

    // check for trigger should be done globablly (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */

    TCanvas* c_CHIMERA_numtel;
    TH1I* fh1_CHIMERA_numtel;
    TH1I* fh1_CHIMERA_numtel_wtime;

    TCanvas* c_CHIMERA_multi;
    TH1I* fh1_CHIMERA_rawmulti;
    TH1I* fh1_CHIMERA_timemulti;
    TH1I* fh1_CHIMERA_multi_fast;
    TH1I* fh1_CHIMERA_multi_slow;
    TH1I* fh1_CHIMERA_multi_sil;

    TCanvas* c_CHIMERA_fast;
    TH2I* fh2_CHIMERA_numtel_fastLG;
    TH2I* fh2_CHIMERA_numtel_fastHG;

    TCanvas* c_CHIMERA_slow;
    TH2I* fh2_CHIMERA_numtel_slowLG;
    TH2I* fh2_CHIMERA_numtel_slowHG;

    TCanvas* c_CHIMERA_patt;
    TH1I* fh1_CHIMERA_patt[32];

  public:
    ClassDef(R3BAsyChimeraOnlineSpectra, 1)
};

#endif
