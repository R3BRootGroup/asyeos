// -------------------------------------------------------------------------
// -----            R3BAsyKrabOnlineSpectra header file             -----
// -----    Created 15/10/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019-2024 Members of R3B Collaboration                     *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

#ifndef R3BAsyKrabOnlineSpectra_H
#define R3BAsyKrabOnlineSpectra_H

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
class R3BAsyKrabOnlineSpectra : public FairTask {
 public:
  /**
   * Default constructor.
   * Creates an instance of the task with default parameters.
   */
  R3BAsyKrabOnlineSpectra();

  /**
   * Standard constructor.
   * Creates an instance of the task.
   * @param name a name of the task.
   * @param iVerbose a verbosity level.
   */
  R3BAsyKrabOnlineSpectra(const char* name, Int_t iVerbose = 1);

  /**
   * Destructor.
   * Frees the memory used by the object.
   */
  virtual ~R3BAsyKrabOnlineSpectra();

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
  TClonesArray* fMappedItemsKrab; /**< Array with krab mapped items. */

  // check for trigger should be done globablly (somewhere else)
  R3BEventHeader* header; /**< Event header.      */
  Int_t fNEvents;         /**< Event counter.     */

  // Canvas
  TCanvas* c_KRAB_rings;
  TH1I* fh1_KRAB_ring[5];

  TCanvas* c_KRAB_multi;
  TH1I* fh1_KRAB_multi;
  TH1I* fh1_KRAB_multi_ring[5];

 public:
  ClassDef(R3BAsyKrabOnlineSpectra, 1)
};

#endif
