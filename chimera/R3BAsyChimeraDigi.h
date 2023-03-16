// ----------------------------------------------------------------
// -----          R3BAsyChimeraDigi source file             -----
// -----         Created 03/11/19  by JL Rodriguez            -----
// ----------------------------------------------------------------

#ifndef R3BAsyChimeraDigi_H
#define R3BAsyChimeraDigi_H 1

#include "FairTask.h"
#include "R3BAsyChimeraHitData.h"
#include "TRandom3.h"
#include "TRotation.h"
#include "TVector3.h"

#include <map>
#include <string>

class TClonesArray;
class R3BTGeoPar;

class R3BAsyChimeraDigi : public FairTask
{

  public:
    /** Default constructor **/
    R3BAsyChimeraDigi();

    /** Standard constructor **/
    R3BAsyChimeraDigi(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    ~R3BAsyChimeraDigi();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    // Fair specific
    virtual void SetParContainers();

    virtual void Reset();

    /** Setters for sigmas **/
    void SetFWHM_t(Float_t FWHM_t) { fFWHM_t = FWHM_t; }
    void SetFWHM_ELoss(Float_t FWHM_ELoss) { fFWHM_ELoss = FWHM_ELoss; }
    void SetFWHM_fast(Float_t FWHM_fast) { fFWHM_fast = FWHM_fast; }
    void SetFWHM_slow(Float_t FWHM_slow) { fFWHM_slow = FWHM_slow; }

  private:
    void SetParameter();

    TClonesArray* fMCTrack;
    TClonesArray* fChimeraPoints;
    TClonesArray* fChimeraHits;
    R3BTGeoPar* fChimeraGeoPar;
    TRandom3* rand;
    Float_t fFWHM_fast;
    Float_t fFWHM_slow;
    Float_t fFWHM_t;
    Float_t fFWHM_ELoss;
    TVector3 fTrans;
    TRotation fRot;

    /** Private method AddHitData **/
    // Adds a R3BSofTofWHitData to the TofWHitCollection
    R3BAsyChimeraHitData* AddHitData(Int_t ndet, Double_t eloss, Double_t fast, Double_t slow, Double_t tof);

  public:
    // Class definition
    ClassDef(R3BAsyChimeraDigi, 1);
};

#endif
