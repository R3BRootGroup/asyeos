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

// ------------------------------------------------------------------
// -----          R3BAsyChimera header file                     -----
// -----    Created 28/03/23  by E. De Filippo and P. Russotto  -----
// ------------------------------------------------------------------

#ifndef R3BAsyChimera_H
#define R3BAsyChimera_H

#include <map>

#include "R3BDetector.h"
#include "TLorentzVector.h"

class TClonesArray;
class R3BAsyChimeraPoint;
class FairVolume;
class TGeoRotation;

class R3BAsyChimera : public R3BDetector
{
  public:
    /** Default constructor */
    R3BAsyChimera();

    /** Standard constructor.
     *@param geoFile name of the ROOT geometry file
     *@param trans   position
     *@param rot     rotation
     */
    R3BAsyChimera(const TString& geoFile, const TGeoTranslation& trans, const TGeoRotation& rot = TGeoRotation());

    /** Standard constructor.
     *@param geoFile name of the ROOT geometry file
     *@param combi   position + rotation
     */
    R3BAsyChimera(const TString& geoFile, const TGeoCombiTrans& combi = TGeoCombiTrans());

    /** Destructor **/
    ~R3BAsyChimera() override;

    /** Virtual method ProcessHits
     **
     ** Defines the action to be taken when a step is inside the
     ** active volume. Creates a R3BAsyChimeraPoint and adds it
     ** to the collection.
     *@param vol  Pointer to the active volume
     **/
    Bool_t ProcessHits(FairVolume* vol = 0) override;

    /** Virtual method EndOfEvent
     **
     ** If verbosity level is set, print hit collection at the
     ** end of the event and resets it afterwards.
     **/
    void EndOfEvent() override;

    /** Virtual method Register
     **
     ** Registers the hit collection in the ROOT manager.
     **/
    void Register() override;

    /** Gets the produced collection **/
    virtual TClonesArray* GetCollection(Int_t iColl) const override;

    /** Virtual method Print
     **
     ** Screen output of hit collection.
     **/
    void Print(Option_t* option = "") const override;

    /**      has to be called after each event to reset the containers      */
    void Reset() override;

    Bool_t CheckIfSensitive(std::string name) override;

    virtual void Initialize() override;
    virtual void SetSpecialPhysicsCuts() override { ; }

  private:
    /** Track information to be stored until the track leaves the
        active volume. **/
    Int_t fTrackID;                        //!  track index
    Int_t fTrackPID;                       //!  particle identification
    Int_t fVolumeID;                       //!  volume id
    Int_t fDetCopyID;                      //!  Det volume id
    Double_t fZ;                           //!  atomic number fragment
    Double_t fA;                           //!  mass number fragment
    Int_t fParentTrackID;                  //!  parent track index
    Int_t fUniqueID;                       //!  particle unique id (e.g. if Delta electron, fUniqueID=9)
    TLorentzVector fPosIn, fPosOut;        //!  position
    TLorentzVector fMomIn, fMomOut;        //!  momentum
    Double32_t fTime;                      //!  time
    Double32_t fLength;                    //!  length
    Double32_t fELoss;                     //!  energy loss
    Double32_t fLightYield;                //!  light yield
    Double32_t fSlow;                      //!  slow
    Int_t fPosIndex;                       //!
    Int_t fNSteps;                         //!  Number of steps in the active volume
    Double32_t fEinc;                      //!  Total incident energy
    Bool_t kGeoSaved;                      //!
                                           //    TList* flGeoPar;                //!
    Double_t fBirkC0, fBirkC1, fBirkC2;    //!
    Double_t fBirkCS0, fBirkCS1, fBirkCS2; //!

    TClonesArray* fAsyChimeraCollection; //  The point collection

    /** Private method AddPoint
     **
     ** Adds a AsyChimeraPoint to the HitCollection
     **/
    R3BAsyChimeraPoint* AddPoint(Int_t trackID,
                                 Int_t detID,
                                 Int_t volid,
                                 Double_t Z,
                                 Double_t A,
                                 TVector3 posIn,
                                 TVector3 pos_out,
                                 TVector3 momIn,
                                 TVector3 momOut,
                                 Double_t time,
                                 Double_t length,
                                 Double_t eLoss,
                                 Double_t lightYield,
                                 Double_t slow);

    /** Private method ResetParameters
     **
     ** Resets the private members for the track parameters
     **/
    void ResetParameters();

    //    TGeoRotation* createMatrix(Double_t phi, Double_t theta, Double_t psi);
    R3BAsyChimera(const R3BAsyChimera&);
    R3BAsyChimera& operator=(const R3BAsyChimera&);

  public:
    ClassDefOverride(R3BAsyChimera, 1);
};

inline void R3BAsyChimera::ResetParameters()
{
    fTrackID = fVolumeID = fParentTrackID = fTrackPID = fUniqueID = 0;
    fPosIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fPosOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fMomIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fMomOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fTime = fLength = fELoss = fEinc = fZ = fA = fLightYield = fSlow = 0;
    fPosIndex = 0;
    fNSteps = 0;
};

#endif
