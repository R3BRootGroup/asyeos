// ------------------------------------------------------------
// -----              R3BAsyChimeraOnlineSpectra             -----
// -----           Fill SOFIA online histograms           -----
// ------------------------------------------------------------

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

// to be fixed
#define Nstrips 32
#define NbChs 2

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyChimeraOnlineSpectra : public FairTask {
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

  // Canvas
  TCanvas* c_1_rawEnergy_front;
  TCanvas* c_1_rawTime_front;
  TCanvas* c_1_rawEnergy_vs_rawTime_front;
  TCanvas* c_1_multi_front;

  // Histograms for Mapped data : Fine Time and Mult
  TH1I* fh1_1_rawEnergy_front[Nstrips];
  TH1I* fh1_1_rawTime_front[Nstrips];
  TH2F* fh2_1_rawEnergy_vs_rawTime_front[Nstrips];
  TH1I* fh1_1_multi_front;

 public:
  ClassDef(R3BAsyChimeraOnlineSpectra, 1)
};

#endif
