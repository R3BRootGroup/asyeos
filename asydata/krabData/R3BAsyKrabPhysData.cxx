// --------------------------------------------------------------------------
// -----               R3BAsyKrabPhysData source file             ------
// --------------------------------------------------------------------------

#include "R3BAsyKrabPhysData.h"

R3BAsyKrabPhysData::R3BAsyKrabPhysData() : fMulti(-1), fKRABRP(-1000) {}

R3BAsyKrabPhysData::R3BAsyKrabPhysData(UInt_t multi, Float_t krabrp)
    : fMulti(multi), fKRABRP(krabrp) {}

UInt_t R3BAsyKrabPhysData::GetMulti() const { return fMulti; }

Float_t R3BAsyKrabPhysData::GetRP() const { return fKRABRP; }

ClassImp(R3BAsyKrabPhysData)
