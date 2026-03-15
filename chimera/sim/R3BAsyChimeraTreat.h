/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019-2026 Members of R3B Collaboration                     *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

// ----------------------------------------------------------------
// -----          R3BAsyChimeraTreat source file             -----
// -----         Created 03/11/19  by JL Rodriguez            -----
// ----------------------------------------------------------------
#ifndef R3BAsyChimeraTreat_H
#define R3BAsyChimeraTreat_H

#pragma once

#define ntels 1192

#include <FairTask.h>

#include <R3BAsyChimeraHitData.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TRotation.h>
#include <TVector3.h>
#include <map>
#include <string>

class TClonesArray;
class R3BTGeoPar;

class R3BAsyChimeraTreat : public FairTask
{

  public:
    /** Default constructor **/
    R3BAsyChimeraTreat();

    /** Standard constructor **/
    R3BAsyChimeraTreat(const TString& name, int iVerbose = 1);

    /** Destructor **/
    ~R3BAsyChimeraTreat();

    /** Method Init **/
    InitStatus Init() override;

    /** Method ReInit **/
    InitStatus ReInit() override;

    /** Method Exec **/
    void Exec(Option_t*) override;

    // Fair specific
    void SetParContainers() override;

    void FinishTask() override;

    void Reset();

    /** Setters for sigmas **/
    void SetSigma_t(double sigma_t) { fsigma_t = sigma_t; }
    void SetSigma_ELoss(double sigma_ELoss) { fsigma_ELoss = sigma_ELoss; }

  private:
    void SetParameter();

    TClonesArray* fMCTrack = nullptr;
    TClonesArray* fAsyChimeraPoints = nullptr;
    TClonesArray* fAsyChimeraHits = nullptr;
    R3BTGeoPar* fAsyChimeraGeoPar = nullptr;

    TRandom* rand;

    // p    double fsigma_y = 1.;    // mm
    double fsigma_t = 0.017; // ns
    double fsigma_ELoss = 1;
    double DE_nt[ntels];
    double fast_nt[ntels];
    double slow_nt[ntels];

    // p    TVector3 fTrans;
    // p    TRotation fRot;
    TH1F* h1_DE;
    /** Private method AddHitData **/
    // Adds a R3BAsyChimeraHitData to the AsyChimeraWHitCollection
    R3BAsyChimeraHitData* AddHitData(int ndet, double eloss, double fast, double slow, double time);

  public:
    // Class definition
    ClassDefOverride(R3BAsyChimeraTreat, 2);
};
#endif
