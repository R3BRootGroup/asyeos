// ------------------------------------------------------------------
// -----          R3BAsyChimeraHitData header file              -----
// -----    Created 27/03/23  by E. De Filippo and P. Russotto  -----
// ------------------------------------------------------------------

#ifndef R3BAsyChimeraHitData_H
#define R3BAsyChimeraHitData_H
#include "TObject.h"

class R3BAsyChimeraHitData : public TObject
{

  public:
    /** Default constructor **/
    R3BAsyChimeraHitData();

    /** Constructor with arguments
     *@param fDetId  Detector number
     *@param fEloss  Energy Loss in [MeV]
     *@param fFast   Fast CsI component in arb. units
     *@param fSlow   Slow CsI component in arb. units
     *@param fToF    Tof in [ns]
     **/
    R3BAsyChimeraHitData(Int_t DetId, Double_t ELoss, Double_t Fast, Double_t Slow, Double_t ToF);

    /** Destructor **/
    virtual ~R3BAsyChimeraHitData() {}

    /** Accessors **/
    Int_t GetDetId() const { return fDetId; }
    Double_t GetEloss() const { return fELoss; }
    Double_t GetFast() const { return fFast; }
    Double_t GetSlow() const { return fSlow; }
    Double_t GetToF() const { return fToF; }

    /** Modifiers **/
    void SetDetID(Int_t ndet) { fDetId = ndet; };
    void SetELoss(Double_t eloss) { fELoss = eloss; };
    void SetFast(Double_t fast) { fFast = fast; };
    void SetSlow(Double_t slow) { fSlow = slow; };
    void SetTof(Double_t t) { fToF = t; };

  private:
    Int_t fDetId;
    Double_t fELoss, fFast, fSlow, fToF;

    ClassDef(R3BAsyChimeraHitData, 1)
};

#endif
