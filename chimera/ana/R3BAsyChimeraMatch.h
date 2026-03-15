// -------------------------------------------------------------------------
// -----            R3BAsyChimeraMatch header file             -----
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

#ifndef R3BAsyChimeraMatch_H
#define R3BAsyChimeraMatch_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "FairTask.h"
#include "R3BAsyChimeraMatchedData.h"
#include "R3BEventHeader.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"

#define ndim 400

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyChimeraMatch : public FairTask
{
  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    R3BAsyChimeraMatch(const char* inFileName, const char* inFileName2);

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~R3BAsyChimeraMatch();

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

    // Accessor to select online mode
    inline void SetOnline(bool option) { fOnline = option; }

    inline void SetNTelMin(Int_t ntel) { NTelMin = ntel; }
    inline void SetNTelMax(Int_t ntel) { NTelMax = ntel; }
    void Set_slow_corr(float slowcorr) { slow_corr = slowcorr; }

  private:
    TClonesArray* fMappedItemsChimera; /**< Array with chimera mapped items. */
    TClonesArray* fChimeraMatchedData;
    bool fOnline = false;
    Int_t NTelMin = 0;
    Int_t NTelMax = 0;
    float slow_corr = 1;

    // check for trigger should be done globally (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */
    Int_t fTrigger = -1;
    Int_t fTpat = 2;

    Float_t offset_fast[ndim], gain_fast[ndim];
    Float_t offset_slow[ndim], gain_slow[ndim];
    Float_t sat_slow[ndim];

    const char* finFileName;
    const char* finFileName2;

    Float_t slow_corr_ntel[ndim];

    R3BAsyChimeraMatchedData* AddMatchedData(UInt_t numtel, Float_t fast, Float_t slow, UInt_t timeCsI);

  public:
    ClassDef(R3BAsyChimeraMatch, 1)
};

#endif
