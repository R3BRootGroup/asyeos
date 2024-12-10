// -------------------------------------------------------------------------
// -----               R3BAsyKrabMappingPar header file                -----
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

#ifndef R3BKASYRABMAPPINGPAR_H
#define R3BASYKRABMAPPINGPAR_H 1

#include <TObjString.h>

#include "FairParGenericSet.h"
#include "TArrayF.h"
#include "TArrayI.h"
#include "TObjArray.h"
#include "TObject.h"

#define triggerbox_number_of_boards 6
#define triggerbox_number_of_FPGA_per_board 5
#define num_channels 26

class FairParamList;

class R3BAsyKrabMappingPar : public FairParGenericSet {
 public:
  /** Standard constructor **/
  R3BAsyKrabMappingPar(const char* name = "krabMappingPar",
                       const char* title = "Krab Mapping Parameters",
                       const char* context = "KrabMappingContext");

  /** Destructor **/
  virtual ~R3BAsyKrabMappingPar();

  /** Reset all parameters **/
  virtual void clear();

  /** Store all parameters using FairRuntimeDB **/
  virtual void putParams(FairParamList* list);

  /** Retrieve all parameters using FairRuntimeDB**/
  Bool_t getParams(FairParamList* list);

  /** Print values of parameters to the standard output **/
  virtual void print();
  void printParams();
  void printMapSectorInfo(const UInt_t sensorID);

  /** Accessor functions **/
  const Int_t GetNumSectors() { return fNumSectors; }
  const Int_t GetBoxRing(Int_t sensor) { return fxtboxring->GetAt(sensor - 1); }
  const Int_t GetBoxCh(Int_t sensor) { return fxtboxch->GetAt(sensor - 1); }
  const Int_t GetBox(Int_t sensor) { return fxtbox->GetAt(sensor - 1); }
  const Int_t GetBoxRingCh(Int_t sensor) {
    return fxtboxringch->GetAt(sensor - 1);
  }
  const Float_t GetBoxAng(Int_t sensor) { return fxtboxang->GetAt(sensor - 1); }
  const Int_t GetBoxBoard(Int_t sensor) {
    return fxtboxboard->GetAt(sensor - 1);
  }
  const Int_t GetBoxInp(Int_t sensor) { return fxtboxinp->GetAt(sensor - 1); }
  const Int_t GetBoxFpga(Int_t sensor) { return fxtboxfpga->GetAt(sensor - 1); }
  const Int_t GetBoxFpgaCh(Int_t sensor) {
    return fxtboxfpga->GetAt(sensor - 1);
  }
  const Int_t GetBoxCrock(Int_t sensor) {
    return fxtboxcrock->GetAt(sensor - 1);
  }
  const Int_t GetBoxCrockCh(Int_t sensor) {
    return fxtboxcrockch->GetAt(sensor - 1);
  }

  void Setnumsectors(Int_t numSectors) { fNumSectors = numSectors; }
  void SetBoxRing(Int_t value, Int_t sensor) {
    fxtboxring->AddAt(value, sensor - 1);
  }
  void SetBoxCh(Int_t value, Int_t sensor) {
    fxtboxch->AddAt(value, sensor - 1);
  }
  void SetBox(Int_t value, Int_t sensor) { fxtbox->AddAt(value, sensor - 1); }
  void SetBoxRingCh(Int_t value, Int_t sensor) {
    fxtboxringch->AddAt(value, sensor - 1);
  }
  void SetBoxAng(Float_t value, Int_t sensor) {
    fxtboxang->AddAt(value, sensor - 1);
  }
  void SetBoxBoard(Int_t value, Int_t sensor) {
    fxtboxboard->AddAt(value, sensor - 1);
  }
  void SetBoxInp(Int_t value, Int_t sensor) {
    fxtboxinp->AddAt(value, sensor - 1);
  }
  void SetBoxFpga(Int_t value, Int_t sensor) {
    fxtboxfpga->AddAt(value, sensor - 1);
  }
  void SetBoxFpgaCh(Int_t value, Int_t sensor) {
    fxtboxfpga->AddAt(value, sensor - 1);
  }
  void SetBoxCrock(Int_t value, Int_t sensor) {
    fxtboxcrock->AddAt(value, sensor - 1);
  }
  void SetBoxCrockCh(Int_t value, Int_t sensor) {
    fxtboxcrockch->AddAt(value, sensor - 1);
  }

 private:
  Int_t fNumSectors;  // total number of Krab Sectors
                      //    TArrayI* fxring;
                      //    TArrayI* fxringch;
                      //    TArrayI* fxringang;

  TArrayI* fxtboxring;
  TArrayI* fxtboxch;
  TArrayI* fxtbox;
  TArrayI* fxtboxringch;
  TArrayF* fxtboxang;
  TArrayI* fxtboxboard;
  TArrayI* fxtboxinp;
  TArrayI* fxtboxfpga;
  TArrayI* fxtboxfpgach;
  TArrayI* fxtboxcrock;
  TArrayI* fxtboxcrockch;

  /*
    Int_t
    fxring[triggerbox_number_of_boards][triggerbox_number_of_FPGA_per_board]
                [num_channels];
    Int_t fxringch[triggerbox_number_of_boards]
                  [triggerbox_number_of_FPGA_per_board][num_channels];
    Float_t fxringang[triggerbox_number_of_boards]
                     [triggerbox_number_of_FPGA_per_board][num_channels];

    Int_t fxtboxring[triggerbox_number_of_boards *
                     triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxch[triggerbox_number_of_boards *
                   triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtbox[triggerbox_number_of_boards *
                 triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxringch[triggerbox_number_of_boards *
                       triggerbox_number_of_FPGA_per_board * num_channels];
    Float_t fxtboxang[triggerbox_number_of_boards *
                      triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxboard[triggerbox_number_of_boards *
                      triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxinp[triggerbox_number_of_boards *
                    triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxfpga[triggerbox_number_of_boards *
                     triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxfpgach[triggerbox_number_of_boards *
                       triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxcrock[triggerbox_number_of_boards *
                      triggerbox_number_of_FPGA_per_board * num_channels];
    Int_t fxtboxcrockch[triggerbox_number_of_boards *
                        triggerbox_number_of_FPGA_per_board * num_channels];

  */

  const R3BAsyKrabMappingPar& operator=(
      const R3BAsyKrabMappingPar&); /*< an assignment operator>*/
  R3BAsyKrabMappingPar(const R3BAsyKrabMappingPar&); /*< a copy constructor >*/

  ClassDef(R3BAsyKrabMappingPar, 1);
};

#endif /* !R3BASYKRABMAPPINGPAR_H */
