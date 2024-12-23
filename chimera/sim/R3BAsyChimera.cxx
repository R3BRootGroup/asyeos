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

#include "R3BAsyChimera.h"

#include "FairRootManager.h"
#include "FairRun.h"
#include "FairVolume.h"
#include "R3BAsyChimeraPoint.h"
#include "R3BLogger.h"
#include "R3BMCStack.h"
#include "TClonesArray.h"
#include "TGeoManager.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "TVirtualMCStack.h"

#define U_MEV 931.4940954

R3BAsyChimera::R3BAsyChimera()
    : R3BAsyChimera("")
{
}

R3BAsyChimera::R3BAsyChimera(const TString& geoFile, const TGeoTranslation& trans, const TGeoRotation& rot)
    : R3BAsyChimera(geoFile, { trans, rot })
{
}

R3BAsyChimera::R3BAsyChimera(const TString& geoFile, const TGeoCombiTrans& combi)
    : R3BDetector("R3BAsyChimera", kCHIMERA, geoFile, combi)
    , fAsyChimeraCollection(new TClonesArray("R3BAsyChimeraPoint"))
    , fPosIndex(0)
{
    ResetParameters();
}

R3BAsyChimera::~R3BAsyChimera()
{
    if (fAsyChimeraCollection)
    {
        fAsyChimeraCollection->Delete();
        delete fAsyChimeraCollection;
    }
}

void R3BAsyChimera::Initialize()
{
    FairDetector::Initialize();

    R3BLOG(info, "R3BAsyChimera: initialisation");
    R3BLOG(debug, "R3BAsyChimera: Vol (McId) def");

    // Initialise variables from Birk law
    Double_t dP = 1.;
    // Set constants for Birk's Law implentation
    fBirkC0 = 1.;
    fBirkC1 = 0.0023 / dP;
    fBirkC2 = 0. / (dP * dP);

    fBirkCS0 = 1.;
    // 1  fBirkCS1 =  1.2/dP;
    fBirkCS1 = 0.033 / dP; // 2 0.013 0.023
    fBirkCS2 = 0. / (dP * dP);
}

// -----   Public method ProcessHits  --------------------------------------
Bool_t R3BAsyChimera::ProcessHits(FairVolume* vol)
{
    /** This method is called from the MC stepping */

    // Set parameters at entrance of volume. Reset ELoss.
    if (TVirtualMC::GetMC()->IsTrackEntering())
    {
        fELoss = 0.;
        fLightYield = 0.;
        fSlow = 0;
        fNSteps = 0; // FIXME
        fTime = TVirtualMC::GetMC()->TrackTime() * 1.0e09;
        fLength = TVirtualMC::GetMC()->TrackLength();
        TVirtualMC::GetMC()->TrackPosition(fPosIn);
        TVirtualMC::GetMC()->TrackMomentum(fMomIn);
        fEinc = TVirtualMC::GetMC()->Etot() - TVirtualMC::GetMC()->TrackMass(); // be aware!! Relativistic mass!
    }

    // Sum energy loss for all steps in the active volume
    fELoss += TVirtualMC::GetMC()->Edep() * 1000.; // in MeV;

    Double_t M_in = TVirtualMC::GetMC()->TrackMass() * 1000.;
    // Charge and mass are now obtained from PDG Code
    //    Double_t fZ_in = int(TVirtualMC::GetMC()->TrackPid() / 10000) - 100000.;
    //    Double_t fA_in = 0.1 * (TVirtualMC::GetMC()->TrackPid() - (100000 +
    //    fZ_in) * 10000.);

    Double_t fA_in = M_in / U_MEV;
    Double_t fZ_in = TVirtualMC::GetMC()->TrackCharge();

    Double_t dE = TVirtualMC::GetMC()->Edep() * 1000.; // in MeV
    TString ptype = TVirtualMC::GetMC()->GetStack()->GetCurrentTrack()->GetName();

    Double_t lightYield = dE;
    Double_t slow = dE;

    Double_t MCTrackCharge = TVirtualMC::GetMC()->TrackCharge();

    if (MCTrackCharge != 0)
    {
        Double_t birkC1Mod = 0;
        // Eventually apply correction for higher charge states TBD
        if (fBirkC0 == 1)
        {
            if (TMath::Abs(MCTrackCharge) >= 2)
                birkC1Mod = fBirkC1 * 1.;
            else
                birkC1Mod = fBirkC1;
        }
        //     if (MCTrackCharge<0)birkC1Mod=0;

        Double_t birkCS1Mod = 0;
        // Eventually apply correction for higher charge states TBD
        if (fBirkCS0 == 1)
        {
            if (TMath::Abs(MCTrackCharge) >= 2)
                birkCS1Mod = fBirkCS1 * 1.;
            else
                birkCS1Mod = fBirkCS1;
        }
        //     if (MCTrackCharge<0)birkCS1Mod=0;//2

        Double_t dedxcm = 0.;
        Double_t lightYieldxcm = 0.;
        Double_t MCstep = TVirtualMC::GetMC()->TrackStep();
        if (MCstep > 0)
        {
            dedxcm = 1000. * TVirtualMC::GetMC()->Edep() / (MCstep * 4.51);
            lightYield = lightYield / (1. + birkC1Mod * dedxcm + fBirkC2 * dedxcm * dedxcm);
            fLightYield = fLightYield + lightYield;
            lightYieldxcm = lightYield / MCstep;
            slow = slow / (1. + birkCS1Mod * dedxcm + fBirkCS2 * dedxcm * dedxcm); // 2
            fSlow = fSlow + slow;
        }
    }

    if (fELoss > 0)
    {
        fNSteps++;
        // Set additional parameters at exit of active volume. Create
        // R3BAsyChimeraPoint.
        if (TVirtualMC::GetMC()->IsTrackExiting() || TVirtualMC::GetMC()->IsTrackStop() ||
            TVirtualMC::GetMC()->IsTrackDisappeared())
        {
            fTrackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
            fParentTrackID = TVirtualMC::GetMC()->GetStack()->GetCurrentParentTrackNumber();
            fVolumeID = vol->getMCid();
            fDetCopyID = vol->getCopyNo();
            fTrackPID = TVirtualMC::GetMC()->TrackPid();
            fUniqueID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrack()->GetUniqueID();
            fLength = gMC->TrackLength();
            gMC->TrackPosition(fPosOut);
            gMC->TrackMomentum(fMomOut);

            if (fELoss == 0.)
            {
                return kFALSE;
            }
            AddPoint(fTrackID,
                     fVolumeID,
                     fDetCopyID,
                     fZ_in,
                     fA_in,
                     TVector3(fPosIn.X(), fPosIn.Y(), fPosIn.Z()),
                     TVector3(fPosOut.X(), fPosOut.Y(), fPosOut.Z()),
                     TVector3(fMomIn.Px(), fMomIn.Py(), fMomIn.Pz()),
                     TVector3(fMomOut.Px(), fMomOut.Py(), fMomOut.Pz()),
                     fTime,
                     fLength,
                     fELoss,
                     fLightYield,
                     fSlow);

            // Increment number of AsyChimeraPoints for this track
            R3BStack* stack = static_cast<R3BStack*>(TVirtualMC::GetMC()->GetStack());
            stack->AddPoint(kCHIMERA);
            ResetParameters();
        }
    }
    return kTRUE;
}

// -----   Public method EndOfEvent   -----------------------------------------
void R3BAsyChimera::EndOfEvent()
{
    if (fVerboseLevel)
    {
        Print();
    }
    Reset();
}

// -----   Public method Register   -------------------------------------------
void R3BAsyChimera::Register()
{
    FairRootManager::Instance()->Register("AsyChimeraPoint", GetName(), fAsyChimeraCollection, kTRUE);
}

// -----   Public method GetCollection   --------------------------------------
TClonesArray* R3BAsyChimera::GetCollection(Int_t iColl) const
{
    if (iColl == 0)
        return fAsyChimeraCollection;
    else
    {
        return nullptr;
    }
}

// -----   Public method Print   ----------------------------------------------
void R3BAsyChimera::Print(Option_t* option) const
{
    Int_t nHits = fAsyChimeraCollection->GetEntriesFast();
    R3BLOG(info, nHits << " points registered in this event");
}

// -----   Public method Reset   ----------------------------------------------
void R3BAsyChimera::Reset()
{
    fAsyChimeraCollection->Clear();
    ResetParameters();
}

// -----   Private method AddPoint --------------------------------------------
R3BAsyChimeraPoint* R3BAsyChimera::AddPoint(Int_t trackID,
                                            Int_t detID,
                                            Int_t volid,
                                            Double_t Z,
                                            Double_t A,
                                            TVector3 posIn,
                                            TVector3 posOut,
                                            TVector3 momIn,
                                            TVector3 momOut,
                                            Double_t time,
                                            Double_t length,
                                            Double_t eLoss,
                                            Double_t LightYield,
                                            Double_t slow)
{
    TClonesArray& clref = *fAsyChimeraCollection;
    Int_t size = clref.GetEntriesFast();
    if (fVerboseLevel > 1)
    {
        R3BLOG(info,
               "Adding point at (" << posIn.X() << ", " << posIn.Y() << ", " << posIn.Z() << ") cm,  detector " << detID
                                   << ", track " << trackID << ", energy loss " << eLoss * 1e06 << " keV "
                                   << ", LightYield " << LightYield * 1e03 << " MeVeq "
                                   << ", slow " << slow * 1e03 << " MeVeq ");
    }
    return new (clref[size]) R3BAsyChimeraPoint(
        trackID, detID, volid, Z, A, posIn, posOut, momIn, momOut, time, length, eLoss, LightYield, slow);
}

// -----  Public method CheckIfSensitive  ----------------------------------
Bool_t R3BAsyChimera::CheckIfSensitive(std::string name)
{
    if (TString(name).Contains("CsI-R"))
    {
        R3BLOG(info, "Found CHIMERA geometry from ROOT file: " << name);
        return kTRUE;
    }
    return kFALSE;
}

ClassImp(R3BAsyChimera)
