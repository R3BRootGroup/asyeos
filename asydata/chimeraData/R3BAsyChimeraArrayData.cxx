// --------------------------------------------------------------------------
// -----               R3BAsyChimeraArrayData source file              ------
// --------------------------------------------------------------------------

#include "R3BAsyChimeraArrayData.h"

#include "FairLogger.h"

R3BAsyChimeraArrayData::R3BAsyChimeraArrayData()
    : fMulti(0),
      fDet(0),
      fSide(0),
      fStrip(0),
      fRawEnergy(0),
      fRawTime(0),
      fMultiE12(0),
      fMultiEFB1(0) {}

R3BAsyChimeraArrayData::R3BAsyChimeraArrayData(UInt_t multi, UInt_t* detector,
                                               UInt_t* side, UInt_t* strip,
                                               UInt_t* energy, UInt_t* time,
                                               UInt_t multiE12,
                                               UInt_t multiEFB1)
    : fMulti(multi),
      fDet(detector),
      fSide(side),
      fStrip(strip),
      fRawEnergy(energy),
      fRawTime(time),
      fMultiE12(multiE12),
      fMultiEFB1(multiEFB1) {
  //       fMulti=multi;
  //       LOG(info) << "R3BAsyChimeraArrayData::new entry";

  /*
         fDet=new UInt_t[multi];
         fSide=new UInt_t[multi];
         fStrip=new UInt_t[multi];
         fRawEnergy=new UInt_t[multi];
         fRawTime=new UInt_t[multi];
         fDet=detector;
         fSide=side;
         fStrip=strip;
         fRawEnergy=energy;
         fRawTime=time;*/
}
UInt_t R3BAsyChimeraArrayData::GetMulti() const { return fMulti; }

UInt_t R3BAsyChimeraArrayData::GetDetectorId(int i) const { return fDet[i]; }

UInt_t R3BAsyChimeraArrayData::GetSideId(int i) const { return fSide[i]; }

UInt_t R3BAsyChimeraArrayData::GetStripId(int i) const { return fStrip[i]; }

UInt_t R3BAsyChimeraArrayData::GetEnergy(int i) const { return fRawEnergy[i]; }

UInt_t R3BAsyChimeraArrayData::GetTime(int i) const { return fRawTime[i]; }

UInt_t R3BAsyChimeraArrayData::GetMultiE12() const { return fMultiE12; }

UInt_t R3BAsyChimeraArrayData::GetMultiEFB1() const { return fMultiEFB1; }

ClassImp(R3BAsyChimeraArrayData)
