// -------------------------------------------------------------------------
// -----                        R3BAsyChimera source file                  -----
// -----                  Created 24/11/17  by H.Alvarez-Pol          -----
// -------------------------------------------------------------------------
#include "R3BAsyChimera.h"
#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoNode.h"
#include "FairGeoRootBuilder.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairVolume.h"
#include "R3BMCStack.h"
//#include "R3BSofToFWCalData.h"
#include "R3BAsyChimeraPoint.h"
#include "TClonesArray.h"
#include "TGeoCompositeShape.h"
#include "TGeoMCGeometry.h"
#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoMatrix.h"
#include "TGeoMedium.h"
#include "TMCProcess.h"
#include "TObjArray.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "TVirtualMCStack.h"
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::cerr;
using std::endl;

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
//    , fAsyChimeraCalCollection(new TClonesArray("R3BAsyChimeraCalData"))
    , fPosIndex(0)
    , kGeoSaved(kFALSE)
    , flGeoPar(new TList())
{
    flGeoPar->SetName(GetName());
    ResetParameters();
}

R3BAsyChimera::~R3BAsyChimera()
{
    if (flGeoPar)
    {
        delete flGeoPar;
    }
    if (fAsyChimeraCollection)
    {
        fAsyChimeraCollection->Delete();
        delete fAsyChimeraCollection;
    }
//    if (fAsyChimeraCalCollection)
//    {
//        fAsyChimeraCalCollection->Delete();
//        delete fAsyChimeraCalCollection;
//    }
}

void R3BAsyChimera::Initialize()
{
    FairDetector::Initialize();

    LOG(INFO) << "R3BAsyChimera: initialisation";
    LOG(DEBUG) << "-I- R3BAsyChimera: Vol (McId) def";

    // TGeoVolume* vol = gGeoManager->GetVolume("AsyChimeraWorld");
    // vol->SetVisibility(kFALSE);
    
    // Initialise variables from Birk law
    Double_t dP = 1. ;
    // Set constants for Birk's Law implentation
    fBirkC0 =  1.;
    fBirkC1 =  0.0023/dP;
    fBirkC2 =  0./(dP * dP);

    fBirkCS0 =  1.;
   //1  fBirkCS1 =  1.2/dP;
    fBirkCS1 =  0.033/dP;//2 0.013 0.023
    fBirkCS2 =  0./(dP * dP);

}

// -----   Public method ProcessHits  --------------------------------------
Bool_t R3BAsyChimera::ProcessHits(FairVolume* vol)
{
    if (gMC->IsTrackEntering())
    {
        gGeoManager->cd(gMC->CurrentVolPath());
        Int_t nodeId = gGeoManager->GetNodeId();
    }
    if (gMC->IsTrackEntering())
    {
        fELoss = 0.;
	    fLightYield= 0.;
	    fSlow = 0;
        fNSteps = 0; // FIXME
        fTime = gMC->TrackTime() * 1.0e09;
        fLength = gMC->TrackLength();
        gMC->TrackPosition(fPosIn);
        gMC->TrackMomentum(fMomIn);
        fEinc = gMC->Etot() - gMC->TrackMass(); // be aware!! Relativistic mass!
    }

    // Sum energy loss for all steps in the active volume
    Double_t dE = gMC->Edep() * 1000.;                          // in MeV
    Double_t post_E = (gMC->Etot() - gMC->TrackMass()) * 1000.; // in MeV
    TString ptype = gMC->GetStack()->GetCurrentTrack()->GetName();

    Double_t M_in = gMC->TrackMass() * 1000.;
    Double_t fA_in = M_in / U_MEV;
    Double_t fZ_in = gMC->TrackCharge();

    fELoss += dE / 1000.; // back to GeV
    
    Double_t lightYield = gMC->Edep(); 
    Double_t slow = gMC->Edep(); 

    if (gMC->TrackCharge()!=0) {
     Double_t birkC1Mod = 0;
     // Apply correction for higher charge states
     if (fBirkC0==1){
      if (TMath::Abs(gMC->TrackCharge())>=2)
        birkC1Mod=fBirkC1*1.;
      else
        birkC1Mod=fBirkC1;
     }
     if (gMC->TrackCharge()<0)birkC1Mod=0;

     Double_t birkCS1Mod = 0;
     // Apply correction for higher charge states
     if (fBirkCS0==1){
      if (TMath::Abs(gMC->TrackCharge())>=2)
        birkCS1Mod=fBirkCS1*1.;
      else
        birkCS1Mod=fBirkCS1;
     }
     if (gMC->TrackCharge()<0)birkCS1Mod=0;//2

     Double_t dedxcm=0.;
     Double_t lightYieldxcm=0.;
     if (gMC->TrackStep()>0)
     {
      dedxcm=1000.*gMC->Edep()/(gMC->TrackStep()*4.51);
      lightYield=lightYield/(1.+birkC1Mod*dedxcm+fBirkC2*dedxcm*dedxcm);
//1      Double_t slow =  lightYield ;
      fLightYield=fLightYield+lightYield;
//1      lightYieldxcm=lightYield/(gMC->TrackStep());
//1      slow=slow/(1.+birkCS1Mod*lightYieldxcm+fBirkCS2*lightYieldxcm*lightYieldxcm);
      slow=slow/(1.+birkCS1Mod*dedxcm+fBirkCS2*dedxcm*dedxcm);//2
      fSlow=fSlow+slow;
     }
    }

    if (dE > 0)
    {

        fNSteps++;

        // Set additional parameters at exit of active volume. Create R3BSofToFWPoint.
        if (gMC->IsTrackExiting() || gMC->IsTrackStop() || gMC->IsTrackDisappeared())
        {

            fTrackID = gMC->GetStack()->GetCurrentTrackNumber();
            fParentTrackID = gMC->GetStack()->GetCurrentParentTrackNumber();
            fVolumeID = vol->getMCid();
            fDetCopyID = vol->getCopyNo();
            fTrackPID = gMC->TrackPid();
            fUniqueID = gMC->GetStack()->GetCurrentTrack()->GetUniqueID();

            gMC->TrackPosition(fPosOut);
            gMC->TrackMomentum(fMomOut);

            if (fELoss == 0.)
                return kFALSE;

//            cout << fVolumeID << " * " << fDetCopyID << endl;
//            getchar();
            
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
            R3BStack* stack = (R3BStack*)gMC->GetStack();
            stack->AddPoint(kCHIMERA);

            // Cal Data for each plastic
            // Adding a CalHit support
/*14112022
            Int_t nPlasticHits = fAsyChimeraCalCollection->GetEntriesFast();
            Bool_t existHit = 0;

            if (nPlasticHits == 0)
                AddCalHit(vol->getCopyNo(), 0, fTime, fELoss);
            else
            {
                for (Int_t i = 0; i < nPlasticHits; i++)
                {
                    if (((R3BSofToFWCalData*)(fAsyChimeraCalCollection->At(i)))->GetDetector() == vol->getCopyNo())
                    {
                        ((R3BSofToFWCalData*)(fAsyChimeraCalCollection->At(i)))
                            ->SetEnergy(fELoss + ((R3BSofToFWCalData*)(fAsyChimeraCalCollection->At(i)))->GetEnergy());
                        if (((R3BSofToFWCalData*)(fAsyChimeraCalCollection->At(i)))->GetTime() > fTime &&
                            fZ_in > 6) // Above Z=6
                        {
                            ((R3BSofToFWCalData*)(fAsyChimeraCalCollection->At(i)))->SetTime(fTime);
                        }
                        existHit = 1; // to avoid the creation of a new CalHit
                        break;
                    }
                }
                if (!existHit)
                    AddCalHit(vol->getCopyNo(), 0, fTime, fELoss);
            }

            existHit = 0;
14112022*/
            ResetParameters();
        }
    }
    return kTRUE;
}

// -----   Public method EndOfEvent   -----------------------------------------
void R3BAsyChimera::BeginEvent() {}

// -----   Public method EndOfEvent   -----------------------------------------
void R3BAsyChimera::EndOfEvent()
{
    if (fVerboseLevel)
        Print();

    fAsyChimeraCollection->Clear();
//    fAsyChimeraCalCollection->Clear();

    ResetParameters();
}

// -----   Public method Register   -------------------------------------------
void R3BAsyChimera::Register()
{
    FairRootManager::Instance()->Register("AsyChimeraPoint", GetName(), fAsyChimeraCollection, kTRUE);
//    FairRootManager::Instance()->Register("TofWCal", GetName(), fAsyChimeraCalCollection, kTRUE);
}

// -----   Public method GetCollection   --------------------------------------
TClonesArray* R3BAsyChimera::GetCollection(Int_t iColl) const
{
    if (iColl == 0)
        return fAsyChimeraCollection;
    else
        return NULL;
}

// -----   Public method Print   ----------------------------------------------
void R3BAsyChimera::Print(Option_t* option) const
{
    Int_t nHits = fAsyChimeraCollection->GetEntriesFast();
    LOG(INFO) << "R3BAsyChimera: " << nHits << " points registered in this event";
//    Int_t nCalHits = fAsyChimeraCalCollection->GetEntriesFast();
//    LOG(INFO) << "R3BAsyChimeraCalData: " << nCalHits << " points registered in this event";
}

// -----   Public method Reset   ----------------------------------------------
void R3BAsyChimera::Reset()
{
    fAsyChimeraCollection->Clear();
//    fAsyChimeraCalCollection->Clear();
    ResetParameters();
}

// -----   Public method CopyClones   -----------------------------------------
void R3BAsyChimera::CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset)
{
    Int_t nEntries = cl1->GetEntriesFast();
    LOG(INFO) << "R3BAsyChimera: " << nEntries << " entries to add";
    TClonesArray& clref = *cl2;
    R3BAsyChimeraPoint* oldpoint = NULL;
    for (Int_t i = 0; i < nEntries; i++)
    {
        oldpoint = (R3BAsyChimeraPoint*)cl1->At(i);
        Int_t index = oldpoint->GetTrackID() + offset;
        oldpoint->SetTrackID(index);
        new (clref[fPosIndex]) R3BAsyChimeraPoint(*oldpoint);
        fPosIndex++;
    }
    LOG(INFO) << "R3BAsyChimera: " << cl2->GetEntriesFast() << " merged entries";
}

// -----   Private method AddCalPoint   --------------------------------------------
/*14112022
R3BSofToFWCalData* R3BAsyChimera::AddCalHit(UShort_t ident, UShort_t pmt, Double_t time, Float_t eLoss)
{
    TClonesArray& clref = *fAsyChimeraCalCollection;
    Int_t size = clref.GetEntriesFast();
    if (fVerboseLevel > 1)
        LOG(INFO) << "TofWCalData: Adding Point at detector " << ident << ", pmt " << pmt << ", time " << time << " ps"
                  << ", energy loss " << eLoss << " MeV";
    return new (clref[size]) R3BAsyChimeraCalData(ident, pmt, time, eLoss);
}
14112022*/
// -----   Private method AddPoint   --------------------------------------------
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
        LOG(INFO) << "R3BAsyChimera: Adding Point at (" << posIn.X() << ", " << posIn.Y() << ", " << posIn.Z()
                  << ") cm,  detector " << detID << ", track " << trackID << ", energy loss " << eLoss * 1e06 << " keV "
		  << ", LightYield " << LightYield * 1e03 << " MeVeq " << ", slow " << slow * 1e03 << " MeVeq ";
    return new (clref[size])
        R3BAsyChimeraPoint(trackID, detID, volid, Z, A, posIn, posOut, momIn, momOut, time, length, eLoss,LightYield,slow);
}

// -----  Public method CheckIfSensitive  ----------------------------------
Bool_t R3BAsyChimera::CheckIfSensitive(std::string name)
{
    if (TString(name).Contains("CsI-R"))
    {
        LOG(INFO) << "Found CHIMERA geometry from ROOT file: " << name;
        return kTRUE;
    }
    return kFALSE;
}

ClassImp(R3BAsyChimera)
