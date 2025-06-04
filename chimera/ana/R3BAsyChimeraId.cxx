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

#include "R3BAsyChimeraId.h"

#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "R3BAsyChimeraMappedData.h"
#include "R3BEventHeader.h"
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include "THttpServer.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TRandom.h"
#include "TVector3.h"
#define verbose 0


R3BAsyChimeraId::R3BAsyChimeraId(const char* inFileName)
    : FairTask("AsyChimeraId", 1)
    , fChimeraMatchedData(0)
    , fChimeraIdData(0)
    , fNEvents(0)    
    , finFileName(inFileName)

{
}


R3BAsyChimeraId::~R3BAsyChimeraId()
{
    LOG(info) << "R3BAsyChimeraId::Delete instance";
//    if (fChimeraMatchedData)
//        delete fChimeraMatchedData;
}

InitStatus R3BAsyChimeraId::Init()
{
    LOG(info) << "R3BAsyChimeraId::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraId::Init FairRootManager not found";

    header = dynamic_cast<R3BEventHeader*>(mgr->GetObject("EventHeader."));
    R3BLOG_IF(error, header == nullptr, "EventHeader. not found");
    
    if (verbose)
        LOG(info) << "R3BAsyChimeraId::Init line 72";
    // Register output array in tree
    fChimeraIdData = new TClonesArray("R3BAsyChimeraIdData");
    FairRootManager::Instance()->Register("AsyChimeraIdData", "AsyChimera Id data", fChimeraIdData, !fOnline);

    LOG(info) << "R3BAsyChimeraId::Init DONE";

    FairRunOnline* run = FairRunOnline::Instance();

    // --- ------------------------------------- --- //
    // --- get access to mapped data of the TofW --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraId::Init line 80";

    fChimeraMatchedData = (TClonesArray*)mgr->GetObject("AsyChimeraMatchedData");
    if (!fChimeraMatchedData)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyChimeraId::Init line 87";

    LOG(info) << "R3BAsyChimeraId::Init DONE";
    getchar();
//**********************************************************************************
    
    string dir = "/u/russotto/R3BRoot/calfiles";
    string filename = "grid.asc";
    int nrun=1;

    string chiecalib = "ecalib141111.txt";
    string chiecalibrec = "dee.txt";
   
    fCsIIdent = new  TCsIIdent(CalDirName,GridFileName,nrun);  
    fCsIIdent->ReadAsciiFile();

    fCHICsIEnergy = new  TCHICsIGSIEnergy(ECalibFileName,ECalibTableFileName,CalDirName);  
    fCHICsIEnergy->Init();  

    fCHIResult = new  TCHIResult();  
    
//**********************************************************************************    
    return kSUCCESS;
}

void R3BAsyChimeraId::Reset_Histo()
{
    LOG(info) << "R3BAsyChimeraId::Reset_Histo";
}

void R3BAsyChimeraId::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraId::Exec FairRootManager not found";
    
    if ((fTrigger >= 0) && (header) && (header->GetTrigger() != fTrigger))
        return;

    Int_t trig = -1000;

    trig = header->GetTrigger();
    
    int tpatvalue = -1000;
    int itpat = -1000;
    int fTpat_bit = fTpat - 1;
    
    if (fTpat_bit >= 0)
    {
     itpat = header->GetTpat();
     tpatvalue = (itpat & (1 << fTpat_bit)) >> fTpat_bit;
     if((header) && (tpatvalue == 0))return;
    }
    

    if(trig==1 && tpatvalue){

     Int_t nHits;
    
     UInt_t NumTel, TimeCsI;
    
     Float_t Fast, Slow;
     
     Float_t tave=1000;
     
     if (fChimeraMatchedData && fChimeraMatchedData->GetEntriesFast())
     {
        // --- --------------------- --- //
        // --- loop over mapped data --- //
        // --- --------------------- --- //
        nHits = fChimeraMatchedData->GetEntriesFast();
	
//	std::cout <<  nHits << std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            Fast=-1, Slow=-1;
	    R3BAsyChimeraMatchedData* hitmatched = (R3BAsyChimeraMatchedData*)fChimeraMatchedData->At(ihit);
            if (!hitmatched)
                continue;
            NumTel = hitmatched->GetNumTel();
            Fast   = hitmatched->GetFast();
            Slow   = hitmatched->GetSlow();
            TimeCsI = hitmatched->GetTimeCsI();
	    
	    fCsIIdent->CsI_Identification(NumTel, Fast, Slow, fCHIResult, tave);
	    
	    
	    UInt_t IdNumTel= NumTel;

	    fCHICsIEnergy->EvalEnergy(NumTel,Fast,Slow,fCHIResult);
            double DE= fCHICsIEnergy->GetDE();
            double Energy= fCHICsIEnergy->GetEnergy();

	    UInt_t Z= fCHIResult->GetZ();
	    UInt_t A= fCHIResult->GetA();
	    UInt_t Stopped= fCHIResult->GetIfStopped();
	    UInt_t Icod= fCHIResult->GetIcod();
	    Double_t PID= fCHIResult->GetPID(); 
	    bool IDOK=   fCHIResult->GetIDOK();     
            bool Zident= fCHIResult->GetZident();   
            bool Aident= fCHIResult->GetAident(); 

	    if(NumTel== 371) std::cout <<" R3BAsyChimeraId::ntel=371 " <<  Fast << " " << Slow << " "  << fCHIResult->GetZ() << " " << fCHIResult->GetA() << std::endl;

	    
	    if(NumTel>= 304 && NumTel<= 399 && fCsIIdent->IsGridExisting(NumTel))AddIdData(NumTel, Fast, Slow, TimeCsI, Z, A, Stopped, Icod, PID, DE, Energy);
	    
	    fCHIResult->SetZ(-10);
	    
        }
    }

    fNEvents += 1;
   } 
}

void R3BAsyChimeraId::FinishEvent()
{
    if (fChimeraMatchedData)
    {
        fChimeraMatchedData->Clear();
    }
    if (fChimeraIdData)
    {
        fChimeraIdData->Clear();
    }
}

void R3BAsyChimeraId::FinishTask()
{
    if (fChimeraMatchedData)
    {
    }
    if (fChimeraIdData)
    {
    }
}


// -----   Private method AddHitData -------------------------------------------

R3BAsyChimeraIdData* R3BAsyChimeraId::AddIdData(UInt_t numtel, Float_t fast, Float_t slow, UInt_t time, UInt_t Z, UInt_t A, UInt_t Stopped, UInt_t Code, UInt_t PID, double DE, double Energy)
{
    TClonesArray& clref = *fChimeraIdData;
    Int_t size = clref.GetEntriesFast();
//    std::cout << "Added....numtel=" << numtel << std::endl;
    return new (clref[size]) R3BAsyChimeraIdData(numtel, fast, slow, time, Z, A, Stopped, Code, PID, DE, Energy);
}

ClassImp(R3BAsyChimeraId)
