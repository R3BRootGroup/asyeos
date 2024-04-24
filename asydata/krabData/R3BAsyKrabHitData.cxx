// ---------------------------------------------------------------------------
// -----                  R3BAsyKrabHitData source file                 ------
// ---------------------------------------------------------------------------

#include "R3BAsyKrabHitData.h"

// -----   Default constructor   -------------------------------------------
R3BAsyKrabHitData::R3BAsyKrabHitData()
    : fCellId(0), fELoss(0.), fLight(0.), fToF(0.) {}

// -----   Standard constructor   ------------------------------------------
R3BAsyKrabHitData::R3BAsyKrabHitData(Int_t ncell, Double_t eloss,
                                     Double_t light, Double_t tof)
    : fCellId(ncell), fELoss(eloss), fLight(light), fToF(tof) {}
// -------------------------------------------------------------------------

ClassImp(R3BAsyKrabHitData)
