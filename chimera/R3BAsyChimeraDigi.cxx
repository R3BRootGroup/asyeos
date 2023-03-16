// ----------------------------------------------------------------
// -----          R3BAsyChimeraDigi source file             -----
// -----        Created 03/11/19 by J.L. Rodriguez            -----
// ----------------------------------------------------------------

#include "R3BAsyChimeraDigi.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "R3BLogger.h"
#include "R3BMCTrack.h"
#include "R3BAsyChimeraPoint.h"
#include "R3BTGeoPar.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "TVector3.h"
#include "TGeoManager.h"

#define ndets 1192


// R3BAsyChimeraDigi: Default Constructor --------------------------
R3BAsyChimeraDigi::R3BAsyChimeraDigi()
    : FairTask("R3BAsyChimeraDigi", 1)
    , fMCTrack(NULL)
    , fChimeraPoints(NULL)
    , fChimeraHits(NULL)
    , fFWHM_fast(0.01)     // sigma=1%
    , fFWHM_slow(0.01)     // sigma=1%
    , fFWHM_t(1.)       // sigma=1 ns
    , fFWHM_ELoss(0.01)
{
    rand = new TRandom3();
}

// R3BAsyChimeraDigi: Standard Constructor --------------------------
R3BAsyChimeraDigi::R3BAsyChimeraDigi(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMCTrack(NULL)
    , fChimeraPoints(NULL)
    , fChimeraHits(NULL)
    , fFWHM_fast(0.01)     // sigma=1%
    , fFWHM_slow(0.01)     // sigma=1%
    , fFWHM_t(1.)       // sigma=1 ns
    , fFWHM_ELoss(0.01)
{
    rand = new TRandom3();
}

// Virtual R3BAsyChimeraDigi: Destructor ----------------------------
R3BAsyChimeraDigi::~R3BAsyChimeraDigi()
{
    R3BLOG(debug, "");
    if (fChimeraHits)
    {
        delete fChimeraHits;
    }
}

void R3BAsyChimeraDigi::SetParContainers()
{
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    fChimeraGeoPar = (R3BTGeoPar*)rtdb->getContainer("ChimeraGeoPar");
    if (!fChimeraGeoPar)
    {
        R3BLOG(error, "Could not get access to ChimeraGeoPar container.");
        return;
    }
    else
    {
        R3BLOG(info, "Container TofwGeoPar found.");
    }
}

void R3BAsyChimeraDigi::SetParameter()
{
/*
    fsigma_y = fTofWGeoPar->GetSigmaY();

    fRot.RotateX(-fTofWGeoPar->GetRotX() * TMath::DegToRad());
    fRot.RotateY(-fTofWGeoPar->GetRotY() * TMath::DegToRad());
    fRot.RotateZ(-fTofWGeoPar->GetRotZ() * TMath::DegToRad());

    fTrans.SetXYZ(fTofWGeoPar->GetPosX(), fTofWGeoPar->GetPosY(), fTofWGeoPar->GetPosZ());
*/
}

// ----   Public method Init  -----------------------------------------
InitStatus R3BAsyChimeraDigi::Init()
{
    R3BLOG(info, "");

    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();
    R3BLOG_IF(fatal, !ioman, "FairRootManager not found.");

    fMCTrack = (TClonesArray*)ioman->GetObject("MCTrack");
    fChimeraPoints = (TClonesArray*)ioman->GetObject("AsyChimeraPoint");

    // Register output array fTofHits
    fChimeraHits = new TClonesArray("R3BAsyChimeraHitData");
    ioman->Register("ChimeraHitData", "Digital response in Chimera", fChimeraHits, kTRUE);

    SetParameter();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BAsyChimeraDigi::Exec(Option_t* opt)
{
    Reset();
    // Reading the Input -- Point Data --
    double de[ndets],dfast[ndets],dslow[ndets];
    for (int i=0;i<ndets;i++){de[i]=0;dfast[i]=0;dslow[i]=0;} 

    Int_t nHits = fChimeraPoints->GetEntries();
    if (nHits == 0)
    {
        return;
    }
    // Data from Point level
    R3BAsyChimeraPoint** pointData = new R3BAsyChimeraPoint*[nHits];

    Int_t DetId = -1, ntel=-1;
    Int_t TrackId = 0, PID = 0, mother = -1;
    Double_t x = 0., y = 0., z = 0., time = 0.;
    Double_t fast = 0., slow = 0., eloss=0;
    TVector3 vpos;
    for (Int_t i = 0; i < nHits; i++)
    {
        pointData[i] = (R3BAsyChimeraPoint*)(fChimeraPoints->At(i));
        TrackId = pointData[i]->GetTrackID();

        R3BMCTrack* Track = (R3BMCTrack*)fMCTrack->At(TrackId);
        PID = Track->GetPdgCode();      
        mother = Track->GetMotherId();

/*
        if (PID > 1000080160) // Z=8 and A=16
        {
            Double_t fX_in = pointData[i]->GetXIn();
            Double_t fY_in = pointData[i]->GetYIn();
            Double_t fZ_in = pointData[i]->GetZIn();
            Double_t fX_out = pointData[i]->GetXOut();
            Double_t fY_out = pointData[i]->GetYOut();
            Double_t fZ_out = pointData[i]->GetZOut();
            paddle = pointData[i]->GetDetCopyID() + 1;
            // std::cout<<paddle<<std::endl;

            x = ((fX_in + fX_out) / 2.);
            y = ((fY_in + fY_out) / 2.);
            z = ((fZ_in + fZ_out) / 2.);
            vpos.SetXYZ(x, y, z);

            vpos = fRot * (vpos - fTrans);
            time = pointData[i]->GetTime() + rand->Gaus(0., fsigma_t);

            // Add hit data
            AddHitData(paddle, vpos.X() * 10., vpos.Y() * 10. + rand->Gaus(0., fsigma_y), time);
        }
*/

      eloss = pointData[i]->GetEnergyLoss()*1000.;  
      fast = pointData[i]->GetLightYield()*1000.;  
      slow = pointData[i]->GetSlow()*1000.;
  
      Double_t xIn = pointData[i]->GetXIn();
      Double_t yIn = pointData[i]->GetYIn();
      Double_t zIn = pointData[i]->GetZIn();
      Double_t xOut = pointData[i]->GetXOut();
      Double_t yOut = pointData[i]->GetYOut();
      Double_t zOut = pointData[i]->GetZOut();

      time = pointData[i]->GetTime();
      DetId = pointData[i]->GetDetectorID();
      ntel= pointData[i]->GetDetCopyID();
      
//      Int_t media = int(land_obj->GetPaddleType());
//      TrackId = chimera_obj->GetTrackID();
//      R3BMCTrack *aTrack = (R3BMCTrack*) fMCTrack->At(TrackId);      
//      Int_t PID = aTrack->GetPdgCode();
//      Int_t mother = aTrack->GetMotherId();
//      cout <<" TrackId " << TrackId << " PID = "<< PID << " mother = " << mother << 
//             " ELoss " << eloss << " fast " << fast <<" slow " << slow <<" detid = "<< DetId << endl;

//      if(!gGeoManager) cout << " gGeoManager missing" << endl;	     
//      gGeoManager->FindNode(xIn,yIn,zIn);
//      TGeoNode* curNode = gGeoManager->GetCurrentNode();
//      Int_t ntel=curNode->GetNumber();
//      ntel=DetId;
      if(mother==-1){
//       cout  << "ntel= " <<  ntel <<endl;
//       cout << "det= " << DetId << endl;
//       getchar();
      }
      
      if(ntel<1192){
       Double_t deR=rand->Gaus(eloss,eloss*fFWHM_ELoss/2.35);
       de[ntel]=de[ntel]+deR;
       Double_t lR=rand->Gaus(fast,fast*fFWHM_fast/2.35);
       dfast[ntel]=dfast[ntel]+lR;
       Double_t sR=rand->Gaus(slow,slow*fFWHM_slow/2.35);
       dslow[ntel]=dslow[ntel]+sR;
//       cout  << " " <<  ntel <<" "<<de[ntel] <<" "<<dfast[ntel]<<endl;
/*
       if(PID>1000020040)ratio=0.8;
       if(PID==1000020040)ratio=0.8;
       if(PID==1000020030)ratio=0.8;
       if(PID==1000010030)ratio=0.8;
       if(PID==1000010020)ratio=0.8;
       if(PID==2212)ratio=0.8;
       if(PID==22)ratio=0.8;
*/ 
//       dslow[ntel] =dslow[ntel] +5*(light-eloss*ratio);
//      cout << gMC->TrackCharge()<<endl;
//       hLight->Fill(dlight[ntel-144]);
      }
    }// for over hits
    
  int ifired=0;
  for(int i=0;i<ndets;i++){
//   if(dslow[i]>800)dslow[i]=800;
//   if(dlight[i]>1100)dlight[i]=1100;
   if(dfast[i]>0){
//   hFSTot->Fill(dslow[i],dlight[i],1.);
    AddHitData(i, de[i], dfast[i], dslow[i], time);
    ifired++;
  }
 }

    
    // Add hit data

    
    if (pointData)
    {
        delete[] pointData;
    }
    LOG(info) << "R3BAsyChimeraDigi: " << fChimeraHits->GetEntriesFast() << " points registered in this event";
    return;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BAsyChimeraDigi::ReInit()
{
    SetParContainers();
    SetParameter();
    return kSUCCESS;
}

// -----   Public method Reset   -----------------------------------------------
void R3BAsyChimeraDigi::Reset()
{
    R3BLOG(debug, "");
    if (fChimeraHits)
    {
        fChimeraHits->Clear();
    }
}

// -----   Private method AddHitData  -------------------------------------------
R3BAsyChimeraHitData* R3BAsyChimeraDigi::AddHitData(Int_t ndet, Double_t eloss, Double_t fast, Double_t slow, Double_t time)
{
    // It fills the R3BSofTofWHitData
    TClonesArray& clref = *fChimeraHits;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BAsyChimeraHitData(ndet, eloss, fast, slow, time);
}

ClassImp(R3BAsyChimeraDigi);
