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
#define myverbose 0

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
    // Set constants for Birk's Law implementation
    fBirkC0 = 1.;
    fBirkC1 = 0.0023 / dP;
    fBirkC2 = 0. / (dP * dP);

    fBirkCS0 = 1.;
    // 1  fBirkCS1 =  1.2/dP;
    fBirkCS1 = 0.033 / dP; // 2 0.013 0.023
    fBirkCS2 = 0. / (dP * dP);
    Double_t cutE1 = 1E-6; // 1 keV?????
    Double_t cutE2 = 1E-6; // 1 keV?????

    /*
        if (gGeoManager) {
         TGeoMedium* pCsI = gGeoManager->GetMedium("CsI");
         if ( pCsI ) {
          // Setting processes for CsI only
             gMC->Gstpar(pCsI->GetId()  ,"LOSS",3);
             gMC->Gstpar(pCsI->GetId()  ,"STRA",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"PAIR",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"COMP",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"PHOT",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"ANNI",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"BREM",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"HADR",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"DRAY",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"DCAY",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"MULS",1.0);
             gMC->Gstpar(pCsI->GetId()  ,"RAYL",1.0);

         // Setting Energy-CutOff for CsI Only

            std::cout << "-I- R3bChimera Scintillator Medium Id " << pCsI->GetId() << " Energy Cut-Off : " << cutE1 << "
     " << cutE2 << std::endl; std::cout << std::endl;

            gMC->Gstpar(pCsI->GetId(),"CUTGAM",cutE1);   // gammas (GeV)
            gMC->Gstpar(pCsI->GetId(),"CUTELE",cutE1);   // electrons (GeV)
            gMC->Gstpar(pCsI->GetId(),"CUTNEU",cutE1);   // neutral hadrons (GeV)
            gMC->Gstpar(pCsI->GetId(),"CUTHAD",cutE1);   // charged hadrons (GeV)
            gMC->Gstpar(pCsI->GetId(),"CUTMUO",cutE1);   // muons (GeV)
            gMC->Gstpar(pCsI->GetId(),"BCUTE",cutE1);    // electron bremsstrahlung (GeV)
            gMC->Gstpar(pCsI->GetId(),"BCUTM",cutE1);    // muon and hadron bremsstrahlung(GeV)
            gMC->Gstpar(pCsI->GetId(),"DCUTE",cutE1);    // delta-rays by electrons (GeV)
            gMC->Gstpar(pCsI->GetId(),"DCUTM",cutE1);    // delta-rays by muons (GeV)
            gMC->Gstpar(pCsI->GetId(),"PPCUTM",cutE1);   // direct pair production by muons (GeV)

         }

     } //!gGeoManager
    */
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
    Double_t dE = TVirtualMC::GetMC()->Edep() * 1000.; // in MeV

    fELoss += dE; // in MeV;

    Double_t M_in = TVirtualMC::GetMC()->TrackMass() * 1000.;
    // Charge and mass are now obtained from PDG Code
    //    Double_t fZ_in = int(TVirtualMC::GetMC()->TrackPid() / 10000) - 100000.;
    //    Double_t fA_in = 0.1 * (TVirtualMC::GetMC()->TrackPid() - (100000 +
    //    fZ_in) * 10000.);

    Double_t fA_in = M_in / U_MEV;
    Double_t fZ_in = TVirtualMC::GetMC()->TrackCharge();
    TString ptype = TVirtualMC::GetMC()->GetStack()->GetCurrentTrack()->GetName();

    Double_t lightYield = dE;
    Double_t slow = dE;
    Double_t BirkC1 = fBirkC1;
    Double_t BirkCS1 = fBirkCS1;

    if (M_in < 900)
    {
        BirkC1 = 0;
        BirkCS1 = 0;
    }

    Double_t dedxcm = 0.;
    Double_t lightYieldxcm = 0.;
    Double_t MCstep = TVirtualMC::GetMC()->TrackStep();

    if (myverbose)
        std::cout << "R3BAsyChimera::ProcessHits ### "
                  << " fZ_in= " << fZ_in << " fA_in= " << fA_in << "  M_in= " << M_in << " ptype= " << ptype
                  << " dE=    " << dE << " MCstep=    " << MCstep << " birkC1=    " << BirkC1
                  << " birkC2=    " << fBirkC2 << " birkCS1=    " << BirkCS1 << " birkCS2=    " << fBirkCS2
                  << std::endl;
    if (myverbose)
        getchar();

    if (MCstep != 0)
    {
        dedxcm = dE / (MCstep * 4.51);
        lightYieldxcm = lightYield / MCstep;
        fLightYield = fLightYield + lightYield / (1. + BirkC1 * dedxcm + fBirkC2 * dedxcm * dedxcm);
        fSlow = fSlow + slow / (1. + BirkCS1 * dedxcm + fBirkCS2 * dedxcm * dedxcm);
        if (myverbose)
            std::cout << "R3BAsyChimera::ProcessHits ### ###  "
                      << " fZ_in= " << fZ_in << " fA_in= " << fA_in << "  M_in= " << M_in << " ptype= " << ptype
                      << " dE=    " << dE << " fELoss=    " << fELoss << " fLightYield=    " << fLightYield
                      << " fSlow=    " << fSlow << std::endl;
        if (myverbose)
            getchar();
    }
    else
    {
        fLightYield = fLightYield + dE;
        fSlow = fSlow + dE;
        if (myverbose)
            std::cout << "R3BAsyChimera::ProcessHits ### ### ###  "
                      << " fZ_in= " << fZ_in << " fA_in= " << fA_in << "  M_in= " << M_in << " ptype= " << ptype
                      << " dE=    " << dE << " fELoss=    " << fELoss << " fLightYield=    " << fLightYield
                      << " fSlow=    " << fSlow << std::endl;
        if (myverbose)
            getchar();
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
