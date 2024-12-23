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

#include "R3BAsyChimeraArrayData.h"

#include "FairLogger.h"

R3BAsyChimeraArrayData::R3BAsyChimeraArrayData()
    : fMulti(0)
    , fNumTel(0)
    , fFastHG(0)
    , fFastLG(0)
    , fSlowHG(0)
    , fSlowLG(0)
    , fTimeCsI(0)
    , fSilHG(0)
    , fSilLG(0)
    , fTimeSil(0)
    , fMultiCsI(0)
    , fMultiSil(0)
{
}

R3BAsyChimeraArrayData::R3BAsyChimeraArrayData(UInt_t multi,
                                               UInt_t* numtel,
                                               UInt_t* fastHG,
                                               UInt_t* fastLG,
                                               UInt_t* slowHG,
                                               UInt_t* slowLG,
                                               UInt_t* timeCsI,
                                               UInt_t* silHG,
                                               UInt_t* silLG,
                                               UInt_t* timeSil,
                                               UInt_t multiCsI,
                                               UInt_t multiSil)
    : fMulti(multi)
    , fNumTel(numtel)
    , fFastHG(fastHG)
    , fFastLG(fastLG)
    , fSlowHG(slowHG)
    , fSlowLG(slowLG)
    , fTimeCsI(timeCsI)
    , fSilHG(silHG)
    , fSilLG(silLG)
    , fTimeSil(timeSil)
    , fMultiCsI(multiCsI)
    , fMultiSil(multiSil)
{
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

UInt_t R3BAsyChimeraArrayData::GetNumTel(int i) const { return fNumTel[i]; }

UInt_t R3BAsyChimeraArrayData::GetFastHG(int i) const { return fFastHG[i]; }

UInt_t R3BAsyChimeraArrayData::GetFastLG(int i) const { return fFastLG[i]; }

UInt_t R3BAsyChimeraArrayData::GetSlowHG(int i) const { return fSlowHG[i]; }

UInt_t R3BAsyChimeraArrayData::GetSlowLG(int i) const { return fSlowLG[i]; }

UInt_t R3BAsyChimeraArrayData::GetTimeCsI(int i) const { return fTimeCsI[i]; }

UInt_t R3BAsyChimeraArrayData::GetSilHG(int i) const { return fSilHG[i]; }

UInt_t R3BAsyChimeraArrayData::GetSilLG(int i) const { return fSilLG[i]; }

UInt_t R3BAsyChimeraArrayData::GetTimeSil(int i) const { return fTimeSil[i]; }

UInt_t R3BAsyChimeraArrayData::GetMultiCsI() const { return fMultiCsI; }

UInt_t R3BAsyChimeraArrayData::GetMultiSil() const { return fMultiSil; }

ClassImp(R3BAsyChimeraArrayData)
