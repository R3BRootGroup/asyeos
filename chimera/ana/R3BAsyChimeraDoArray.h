// -------------------------------------------------------------------------
// -----            R3BAsyChimeraDoArray header file                   -----
// -----    Created 19/04/24  by E. De Filippo and P. Russotto         -----
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

#ifndef R3BAsyChimeraDoArray_H
#define R3BAsyChimeraDoArray_H

#include <R3BShared.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairTask.h"
#include "R3BAsyChimeraArrayData.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"

// to be fixed
#define Nstrips 32
#define NbChs 2
const int dmax = 128;
const int dmaxs = 32;

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads mapped data and plots online histograms
 */
class R3BAsyChimeraDoArray : public FairTask {
 public:
  /**
   * Default constructor.
   * Creates an instance of the task with default parameters.
   */
  R3BAsyChimeraDoArray();

  /**
   * Standard constructor.
   * Creates an instance of the task.
   * @param name a name of the task.
   * @param iVerbose a verbosity level.
   */
  R3BAsyChimeraDoArray(const char* name, Int_t iVerbose = 1);

  /**
   * Destructor.
   * Frees the memory used by the object.
   */
  virtual ~R3BAsyChimeraDoArray();

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

  // Reset
  virtual void Reset();

 private:
  TClonesArray* fMappedItemsChimera; /**< Array with chimera mapped items. */
  TClonesArray* fChimeraArrayData;
  // check for trigger should be done globablly (somewhere else)
  R3BEventHeader* header; /**< Event header.      */
  Int_t fNEvents;         /**< Event counter.     */
  bool fOnline = false;

  UInt_t iMulti;
  UInt_t* iDet;        //[iMulti]
  UInt_t* iSide;       //[iMulti]
  UInt_t* iStrip;      //[iMulti]
  UInt_t* iRawEnergy;  //[iMulti]
  UInt_t* iRawTime;    //[iMulti]

  UInt_t nn;

  int E1F[dmaxs];
  int T1F[dmaxs];

  int E1B[dmaxs];
  int T1B[dmaxs];

  int E2F[dmaxs];
  int T2F[dmaxs];

  int E3F[dmaxs];
  int T3F[dmaxs];

  bool uE1F[dmaxs];
  bool uT1F[dmaxs];

  bool uE1B[dmaxs];
  bool uT1B[dmaxs];

  bool uE2F[dmaxs];
  bool uT2F[dmaxs];

  R3BAsyChimeraArrayData* AddHitData(UInt_t multi, UInt_t* Det, UInt_t* Side,
                                     UInt_t* Strip, UInt_t* RawEnergy,
                                     UInt_t* RawTime, UInt_t multiE12,
                                     UInt_t multEFB1);

 public:
  ClassDef(R3BAsyChimeraDoArray, 1)
};

#endif
