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
// -----        Created 03/11/19 by J.L. Rodriguez            -----
// ----------------------------------------------------------------

#include "R3BAsyChimeraTreat.h"
#include "R3BAsyChimeraPoint.h"
#include "R3BLogger.h"
#include "R3BMCTrack.h"
#include "R3BTGeoPar.h"

#include <FairLogger.h>
#include <FairRootManager.h>
#include <FairRunAna.h>
#include <FairRuntimeDb.h>

#include <TClonesArray.h>
#include <TMath.h>
#include <TVector3.h>

// R3BAsyChimeraTreat: Default Constructor --------------------------
R3BAsyChimeraTreat::R3BAsyChimeraTreat()
    : R3BAsyChimeraTreat("R3BAsyChimeraTreat", 1)
{
}

// R3BAsyChimeraTreat: Standard Constructor --------------------------
R3BAsyChimeraTreat::R3BAsyChimeraTreat(const TString& name, int iVerbose)
    : FairTask(name.Data(), iVerbose)
{
    rand = new TRandom();
}

// Virtual R3BAsyChimeraTreat: Destructor ----------------------------
R3BAsyChimeraTreat::~R3BAsyChimeraTreat()
{
    R3BLOG(debug, "");
    if (fAsyChimeraHits)
    {
        delete fAsyChimeraHits;
    }
}

void R3BAsyChimeraTreat::SetParContainers()
{
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    fAsyChimeraGeoPar = (R3BTGeoPar*)rtdb->getContainer("ChimeraGeoPar");
    if (!fAsyChimeraGeoPar)
    {
        R3BLOG(error, "Could not get access to ChimeraGeoPar container.");
        return;
    }
    else
    {
        R3BLOG(info, "Container ChimearaGeoPar found.");
    }
}

void R3BAsyChimeraTreat::SetParameter()
{
    // p    fsigma_y = fTofWGeoPar->GetSigmaY();

    // p    fRot.RotateX(-fTofWGeoPar->GetRotX() * TMath::DegToRad());
    // p    fRot.RotateY(-fTofWGeoPar->GetRotY() * TMath::DegToRad());
    // p    fRot.RotateZ(-fTofWGeoPar->GetRotZ() * TMath::DegToRad());

    // p    fTrans.SetXYZ(fTofWGeoPar->GetPosX(), fTofWGeoPar->GetPosY(), fTofWGeoPar->GetPosZ());
}

// ----   Public method Init  -----------------------------------------
InitStatus R3BAsyChimeraTreat::Init()
{
    R3BLOG(info, "");

    // Get input array
    auto* ioman = FairRootManager::Instance();
    R3BLOG_IF(fatal, !ioman, "FairRootManager not found.");

    fMCTrack = dynamic_cast<TClonesArray*>(ioman->GetObject("MCTrack"));
    fAsyChimeraPoints = dynamic_cast<TClonesArray*>(ioman->GetObject("AsyChimeraPoint"));

    // Register output array fAsyChimeraHits
    fAsyChimeraHits = new TClonesArray("R3BAsyChimeraHitData");
    ioman->Register("AsyChimeraHitData", "Response in CHIMERA", fAsyChimeraHits, kTRUE);

    h1_DE = new TH1F("h1_DE", "DE", 500, 0, 20);
    cout << "h1_DE " << h1_DE << endl;
    getchar();
    SetParameter();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BAsyChimeraTreat::Exec(Option_t*)
{
    Reset();

    for (int i = 0; i < ntels; i++)
    {
        DE_nt[i] = 0;
        slow_nt[i] = 0;
        fast_nt[i] = 0;
    }

    // Reading the Input -- Point Data --
    auto nHits = fAsyChimeraPoints->GetEntries();
    if (nHits == 0)
    {
        return;
    }
    // Data from Point level
    int ndet = -1;
    int TrackId = 0, PID = 0, mother = -1;
    double x = 0., y = 0., z = 0., time = 0.;
    TVector3 vpos;
    double DE = 0;
    double fast = 0, slow = 0;
    for (Int_t i = 0; i < nHits; i++)
    {
        auto* pointData = dynamic_cast<R3BAsyChimeraPoint*>(fAsyChimeraPoints->At(i));
        TrackId = pointData->GetTrackID();

        auto* Track = dynamic_cast<R3BMCTrack*>(fMCTrack->At(TrackId));
        PID = Track->GetPdgCode();

        if (PID != 0) // Z=8 and A=16
        {
            auto fX_in = pointData->GetXIn();
            auto fY_in = pointData->GetYIn();
            auto fZ_in = pointData->GetZIn();
            auto fX_out = pointData->GetXOut();
            auto fY_out = pointData->GetYOut();
            auto fZ_out = pointData->GetZOut();
            ndet = pointData->GetDetCopyID();
            //            std::cout<<"ndet = " << ndet << std::endl;

            x = ((fX_in + fX_out) / 2.);
            y = ((fY_in + fY_out) / 2.);
            z = ((fZ_in + fZ_out) / 2.);
            vpos.SetXYZ(x, y, z);

            // p             vpos = fRot * (vpos - fTrans);
            time = pointData->GetTime(); // p  + rand->Gaus(0., fsigma_t);
            auto fDE = pointData->GetEnergyLoss();
            auto fFast = pointData->GetLightYield();
            auto fSlow = pointData->GetSlow();
            if (fDE > 0)
            {
                DE_nt[ndet] = DE_nt[ndet] + fDE;
                fast_nt[ndet] = fast_nt[ndet] + fFast;
                slow_nt[ndet] = slow_nt[ndet] + fSlow;
                //               std::cout << "### ndet = " << ndet << " " << fDE << " " << fFast << " " << fSlow << " "
                //               << PID << std::endl;
                // Add hit data
            }
        }
    }
    //    std::cout<<"DE=" << DE << std::endl;
    h1_DE->Fill(DE);

    for (int i = 0; i < ntels; i++)
    {
        if (DE_nt[i] > 0)
        {
            AddHitData(i, DE_nt[i], fast_nt[i], slow_nt[i], time);
            //         std::cout<<"### ### ndet = " << i << std::endl;
            //       getchar();
        }
    }
    //    LOG(info) << "R3BAsyChimeraTreat: " << fAsyChimeraHits->GetEntriesFast() << " points registered in this
    //    event";

    return;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BAsyChimeraTreat::ReInit()
{
    SetParContainers();
    SetParameter();
    return kSUCCESS;
}

// -----   Public method Reset   -----------------------------------------------
void R3BAsyChimeraTreat::Reset()
{
    R3BLOG(debug, "");
    if (fAsyChimeraHits)
    {
        fAsyChimeraHits->Clear();
    }
}

void R3BAsyChimeraTreat::FinishTask()
{
    h1_DE->Write();
    h1_DE->Draw();
    cout << "h1_DE written" << endl;
    getchar();
}
// -----   Private method AddHitData  -------------------------------------------
R3BAsyChimeraHitData* R3BAsyChimeraTreat::AddHitData(int ndet, double eloss, double fast, double slow, double time)
{
    // It fills the R3BSofTofWHitData
    TClonesArray& clref = *fAsyChimeraHits;
    auto size = clref.GetEntriesFast();
    return new (clref[size]) R3BAsyChimeraHitData(ndet, eloss, fast, slow, time);
}

ClassImp(R3BAsyChimeraTreat)
