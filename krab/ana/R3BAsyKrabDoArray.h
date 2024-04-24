// -------------------------------------------------------------------------
// -----             R3BAsyKrabDoArray header file                     -----
// -----    Created 19/04/24  by E. De Filippo and P. Russotto         -----
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

#ifndef R3BAsyKrabDoArray_H
#define R3BAsyKrabDoArray_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairTask.h"
#include "R3BAsyKrabArrayData.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"

// to be fixed
#define Nstrips 32
#define NbChs 2
const int dmaxKrab = 1024;

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyKrabDoArray : public FairTask {
 public:
  /**
   * Default constructor.
   * Creates an instance of the task with default parameters.
   */
  R3BAsyKrabDoArray();

  /**
   * Standard constructor.
   * Creates an instance of the task.
   * @param name a name of the task.
   * @param iVerbose a verbosity level.
   */
  R3BAsyKrabDoArray(const char* name, Int_t iVerbose = 1);

  /**
   * Destructor.
   * Frees the memory used by the object.
   */
  virtual ~R3BAsyKrabDoArray();

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

  virtual void FinishTask();

  // Reset
  virtual void Reset();

 private:
  TClonesArray* fMappedItemsKrab; /**< Array with Krab mapped items. */
  TClonesArray* fKrabArrayData;
  // check for trigger should be done globablly (somewhere else)
  R3BEventHeader* header; /**< Event header.      */
  Int_t fNEvents;         /**< Event counter.     */
  bool fOnline = false;

  UInt_t iMulti;
  Double_t iRP;
  UInt_t* iRing;    //[iMulti]
  UInt_t* iSector;  //[iMulti]
  Float_t* iPhi;    //[iMulti]

  UInt_t nn;
  TRandom* rr;
  TCanvas* c_DRP12_mgt10;
  TH1F* fh1_DRP12_mgt10;

  R3BAsyKrabArrayData* AddHitData(UInt_t Multi, Double_t RP, UInt_t* Ring,
                                  UInt_t* Sector, Float_t* Phi);

 public:
  ClassDef(R3BAsyKrabDoArray, 1)
};

#endif
