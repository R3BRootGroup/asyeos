// ---------------------------------------------------------------------------
// -----                  R3BAsyKrabMappedData source file              ------
// ---------------------------------------------------------------------------

#include "R3BAsyKrabMappedData.h"

R3BAsyKrabMappedData::R3BAsyKrabMappedData()
    : fRing(-1), fSector(-1), fPhi(-1000), fqx(-1000), fqy(-1000) {}

R3BAsyKrabMappedData::R3BAsyKrabMappedData(UInt_t ring, UInt_t sector,
                                           Float_t phi, Float_t qx, Float_t qy)
    : fRing(ring), fSector(sector), fPhi(phi), fqx(qx), fqy(qy) {}

UInt_t R3BAsyKrabMappedData::GetRing() const { return fRing; }

UInt_t R3BAsyKrabMappedData::GetSector() const { return fSector; }

Float_t R3BAsyKrabMappedData::GetPhi() const { return fPhi; }

Float_t R3BAsyKrabMappedData::Getqx() const { return fqx; }

Float_t R3BAsyKrabMappedData::Getqy() const { return fqy; }

ClassImp(R3BAsyKrabMappedData)
