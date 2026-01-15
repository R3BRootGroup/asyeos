// -------------------------------------------------------------------------
// -----            R3BAsyChimeraPhys header file             -----
// -----    Created 12/01/26  by  P. Russotto         -----
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

#ifndef R3BAsyChimeraPhys_H
#define R3BAsyChimeraPhys_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairTask.h"
#include "R3BAsyChiKrabPhysData.h"
#include "R3BAsyChimeraIdData.h"
#include "R3BAsyKrabMappedData.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"

#define ndd 500

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyChimeraPhys : public FairTask
{
  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    R3BAsyChimeraPhys();

    /**
     * Standard constructor.
     * Creates an instance of the task.
     * @param name a name of the task.
     * @param iVerbose a verbosity level.
     */
    R3BAsyChimeraPhys(const char* name, Int_t iVerbose = 1);

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~R3BAsyChimeraPhys();

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
    inline void SetCHIRP_thr(Int_t thr) { CHIRP_thr = thr; }
    inline void SetKRABRP_thr(Int_t thr) { KRABRP_thr = thr; }
    inline void SetKRAB_MULT_min(Int_t km) { KM_min = km; }
    inline void SetKRAB_MULT_max(Int_t km) { KM_max = km; }
    inline void SetEnergy(Int_t energy) { this_energy = energy; }

  private:
    TClonesArray* fChimeraIdData;   /**< Array with chimera Id data */
    TClonesArray* fMappedItemsKrab; /**< Array with krab mapped items. */
    TClonesArray* fChiKrabPhysData;
    bool fOnline = false;
    Int_t CHIRP_thr = 3;
    Int_t KRABRP_thr = 3;
    int this_energy = 0;
    float ymid, EAMax, KRABww;
    float KM_min = 0, KM_max = 100;
    float dy = 0;
    float qqx[ndd], qqy[ndd];

    // check for trigger should be done globally (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */

    // Canvas
    Float_t GetTheta(int);
    Float_t GetPhi(int);
    Float_t GetThetaRnd(int);
    Float_t GetPhiRnd(int);
    Float_t GetThetaRndKRAB(int);

    TRandom* rr2;
    TRandom* rr3;
    TRandom* rrn;

    TCanvas* cc1;
    TCanvas* c_RP;
    TCanvas* c_RP2;
    TCanvas* c_RP3;
    TCanvas* c_b;
    TCanvas* c_b2;
    TCanvas* cc4;
    TCanvas* cc5;
    TCanvas* cc4_bis;
    TCanvas* cc5_bis;
    TCanvas* cc14;

    R3BAsyChiKrabPhysData* AddPhysData(Int_t Multi_CHI,
                                       Int_t ZBound_CHI,
                                       Float_t ZRat_CHI,
                                       Float_t ERat_CHI,
                                       Float_t RP_CHI,
                                       Int_t Multi_KRAB,
                                       Int_t MultiR0_KRAB,
                                       Int_t MultiR14_KRAB,
                                       Float_t RP_KRAB,
                                       Float_t RP_CHIKRAB,
                                       Float_t dRP_CHIKRAB);

  public:
    ClassDef(R3BAsyChimeraPhys, 1)
};

#endif
