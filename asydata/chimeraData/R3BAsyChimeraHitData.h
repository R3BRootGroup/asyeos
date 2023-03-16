#ifndef R3BAsyChimeraHitData_H
#define R3BAsyChimeraHitData_H
#include "TObject.h"

class R3BAsyChimeraHitData : public TObject
{

  public:
    /** Default constructor **/
    R3BAsyChimeraHitData();

    /** Constructor with arguments
     *@param fPaddleId  Paddle number
     *@param fX         Position X in [mm]
     *@param fY         Position Y in [mm]
     *@param fTof      Tof [ns]
     **/
    R3BAsyChimeraHitData(Int_t DetId, Double_t ELoss, Double_t Fast, Double_t Slow, Double_t ToF);

    /** Destructor **/
    virtual ~R3BAsyChimeraHitData() {}

    /** Accessors **/
    inline const Int_t& GetDetId() const { return fDetId; }
    inline const Double_t& GetEloss() const { return fELoss; }
    inline const Double_t& GetFast() const { return fFast; }
    inline const Double_t& GetSlow() const { return fSlow; }
    inline const Double_t& GetToF() const { return fToF; }

    /** Modifiers **/
    void SetDetID(Int_t ndet) { fDetId = ndet; };
    void SetELoss(Double_t eloss) { fELoss = eloss; };
    void SetFast(Double_t fast) { fFast = fast; };
    void SetSlow(Double_t slow) { fSlow = slow; };
    void SetTof(Double_t t) { fToF = t; };

  protected:
    Int_t fDetId;
    Double_t fELoss, fFast, fSlow, fToF;

  public:
    ClassDef(R3BAsyChimeraHitData, 1)
};

#endif
