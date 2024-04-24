// --------------------------------------------------------------------------
// -----               R3BAsyChimeraMappedData source file             ------
// --------------------------------------------------------------------------

#include "R3BAsyChimeraMappedData.h"

R3BAsyChimeraMappedData::R3BAsyChimeraMappedData()
    : fDetector(-1), fSide(-1), fStrip(-1), fEnergy(-1), fTime(-1) {}

R3BAsyChimeraMappedData::R3BAsyChimeraMappedData(UInt_t detector, UInt_t side,
                                                 UInt_t strip, UInt_t energy,
                                                 UInt_t time)
    : fDetector(detector),
      fSide(side),
      fStrip(strip),
      fEnergy(energy),
      fTime(time) {}

UInt_t R3BAsyChimeraMappedData::GetDetectorId() const { return fDetector; }

UInt_t R3BAsyChimeraMappedData::GetSideId() const { return fSide; }

UInt_t R3BAsyChimeraMappedData::GetStripId() const { return fStrip; }

UInt_t R3BAsyChimeraMappedData::GetEnergy() const { return fEnergy; }

UInt_t R3BAsyChimeraMappedData::GetTime() const { return fTime; }

ClassImp(R3BAsyChimeraMappedData)
