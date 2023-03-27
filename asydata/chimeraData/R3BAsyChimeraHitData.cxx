// --------------------------------------------------------------------------
// -----                  R3BAsyChimeraHitData source file              -----
// --------------------------------------------------------------------------

#include "R3BAsyChimeraHitData.h"

// -----   Default constructor   -------------------------------------------
R3BAsyChimeraHitData::R3BAsyChimeraHitData()
    : fDetId(0), fELoss(0.), fFast(0.), fSlow(0.), fToF(0.) {}

// -----   Standard constructor   ------------------------------------------
R3BAsyChimeraHitData::R3BAsyChimeraHitData(Int_t ndet, Double_t eloss,
                                           Double_t fast, Double_t slow,
                                           Double_t tof)
    : fDetId(ndet), fELoss(eloss), fFast(fast), fSlow(slow), fToF(tof) {}
// -------------------------------------------------------------------------

ClassImp(R3BAsyChimeraHitData)
