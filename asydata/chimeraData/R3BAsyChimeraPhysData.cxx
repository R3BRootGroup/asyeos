// --------------------------------------------------------------------------
// -----               R3BAsyChimeraPhysData source file             ------
// --------------------------------------------------------------------------

#include "R3BAsyChimeraPhysData.h"

R3BAsyChimeraPhysData::R3BAsyChimeraPhysData() : fMulti(-1), fCHIRP(-1000) {}

R3BAsyChimeraPhysData::R3BAsyChimeraPhysData(UInt_t multi, Float_t chirp)
    : fMulti(multi), fCHIRP(chirp) {}

UInt_t R3BAsyChimeraPhysData::GetMulti() const { return fMulti; }

Float_t R3BAsyChimeraPhysData::GetRP() const { return fCHIRP; }

ClassImp(R3BAsyChimeraPhysData)
