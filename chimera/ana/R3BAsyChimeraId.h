// -------------------------------------------------------------------------
// -----            R3BAsyChimeraId header file             -----
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

#ifndef R3BAsyChimeraId_H
#define R3BAsyChimeraId_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "FairTask.h"
#include "R3BAsyChimeraIdData.h"
#include "R3BAsyChimeraMatchedData.h"
#include "R3BEventHeader.h"
#include "TCHICsIEnergy.h"
#include "TCHIResult.h"
#include "TCanvas.h"
#include "TCsIIdent.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRootCHIEvent.h"
#include "TRootDefine.h"

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyChimeraId : public FairTask
{
  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    R3BAsyChimeraId(const char* inFileName);

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~R3BAsyChimeraId();

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

    string CalDirName;
    string GridFileName;
    string ECalibFileName;
    string ECalibTableFileName;

    inline void SetCalDir(string DirName) { CalDirName = DirName; }
    inline void SetGridFileName(string FileName) { GridFileName = FileName; }
    inline void SetECalibFileName(string FileName) { ECalibFileName = FileName; }
    inline void SetECalibTableFileName(string FileName) { ECalibTableFileName = FileName; }
    void Set_optZ2(bool opt){opt_Z2=opt;}
    //void Set_slow_corr(float slowcorr){slow_corr=slowcorr;}



  private:
    TClonesArray* fChimeraMatchedData; /**< Array with chimera matched items. */
    TClonesArray* fChimeraIdData;      /**< Array with chimera Id items. */
    bool fOnline = false;
    bool opt_Z2;
    //float slow_corr;

    // check for trigger should be done globablly (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */
    Int_t fTrigger = -1;
    Int_t fTpat = 2;
    TCsIIdent* fCsIIdent;
    TCHIResult* fCHIResult;
    TCHICsIGSIEnergy* fCHICsIEnergy;
    
    

    Float_t GetThetaRnd(int);
    Float_t GetPhiRnd(int);
    TRandom* rrn;

    TCanvas* cc;
    TH2F* h2_ylab_bt;

    TFile* f1;

    TRootDefine chitree;
    TRootCHIEvent* evt;

    const char* finFileName;

    R3BAsyChimeraIdData* AddIdData(UInt_t numtel,
                                   Float_t fast,
                                   Float_t slow,
                                   UInt_t time,
                                   Int_t Z,
                                   Int_t A,
                                   Int_t Stopped,
                                   Int_t Code,
                                   Float_t PID,
                                   double DE,
                                   double Energy);

  public:
    ClassDef(R3BAsyChimeraId, 1)
};

#endif
