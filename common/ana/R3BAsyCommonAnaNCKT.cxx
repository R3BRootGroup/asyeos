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

#include "R3BAsyCommonAnaNCKT.h"

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
#include "R3BAsyChimeraPhysData.h"
#include "R3BAsyKrabPhysData.h"
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

R3BAsyCommonAnaNCKT::R3BAsyCommonAnaNCKT()
    : FairTask("AsyCommonAnaNC", 1)
    , fPhysItemsChimera(0)
    , fPhysItemsKrab(0)
    , fNeulandMappedData(0)
    , fTofdMappedData(0)
    , fNEvents(0)
{
}

R3BAsyCommonAnaNCKT::R3BAsyCommonAnaNCKT(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fPhysItemsChimera(0)
    , fPhysItemsKrab(0)
    , fNeulandMappedData(0)
    , fTofdMappedData(0)
    , fNEvents(0)
{
}

R3BAsyCommonAnaNCKT::~R3BAsyCommonAnaNCKT()
{
    LOG(info) << "R3BAsyCommonAnaNCKT::Delete instance";
    if (fPhysItemsChimera)
        delete fPhysItemsChimera;
    if (fPhysItemsKrab)
        delete fPhysItemsKrab;
    if (fNeulandMappedData)
        delete fNeulandMappedData;
    if (fTofdMappedData)
        delete fTofdMappedData;
}

InitStatus R3BAsyCommonAnaNCKT::Init()
{
    LOG(info) << "R3BAsyCommonAnaNCKT::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyCommonAnaNCKT::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    if (verbose)
        LOG(info) << "R3BAsyCommonAnaNCKT::Init line 72";

    FairRunOnline* run = FairRunOnline::Instance();
    // for online server
    run->GetHttpServer()->Register("", this);

    // Register command to reset histograms
    // for online server
    run->GetHttpServer()->RegisterCommand("Reset_Common_Ana", Form("/Objects/%s/->Reset_Histo()", GetName()));

    // --- ------------------------------------- --- //
    // --- get access to phys data of CHIMERA and KRAB --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyCommonAnaNCKT::Init line 80";

    fPhysItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraPhysData");
    if (!fPhysItemsChimera)
    {
        //   std::cout << "#### Common Ana :: 79 fPhysItemsChimera not found" <<
        //   std::endl; getchar();
        //        return kFATAL;
    }
    fPhysItemsKrab = (TClonesArray*)mgr->GetObject("AsyKrabPhysData");
    if (!fPhysItemsKrab)
    {
        //        return kFATAL;
    }

    fNeulandMappedData = (TClonesArray*)mgr->GetObject("NeulandMappedData");
    if (!fNeulandMappedData)
    {
        //        return kFATAL;
    }

    fTofdMappedData = (TClonesArray*)mgr->GetObject("TofdMapped");
    if (!fTofdMappedData)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyCommonAnaNCKT::Init line 87";


    c_NCKT = new TCanvas("c_NCKT", "NCKT", 0, 0, 1200, 1200);
    c_NCKT->Divide(2, 2);

    
    c_NCKT->cd(1);
    fh2_KRAB_NL_multi = new TH2I("fh2_KRAB_NL_multi", "KRAB_NL_multi", 100, -0.5, 99.5, 100, -0.5, 99.5);
    fp_KRAB_NL_multi = new TProfile("fp_KRAB_NL_multi", "KRAB_NL_multi", 100, -0.5, 99.5,  -0.5, 99.5);
    fh2_KRAB_NL_multi->Draw();
    fp_KRAB_NL_multi->Draw("same");
    
    c_NCKT->cd(2);
    fh2_CHIMERA_NL_multi = new TH2I("fh2_CHIMERA_NL_multi", "CHIMERA_NL_multi", 100, -0.5, 99.5, 50, -0.5, 49.5);
    fp_CHIMERA_NL_multi = new TProfile("fp_CHIMERA_NL_multi", "CHIMERA_NL_multi", 100, -0.5, 99.5, 1 -0.5, 49.5);
    fh2_CHIMERA_NL_multi->Draw();
    fp_CHIMERA_NL_multi->Draw("same");
    
    fp_CHIMERA_NL_multi->SetMarkerStyle(20);
    fp_KRAB_NL_multi->SetMarkerStyle(20);
    
    
    c_NCKT->cd(3);
    fh2_KRAB_Tofd_multi = new TH2I("fh2_KRAB_Tofd_multi", "KRAB_Tofd_multi", 100, -0.5, 99.5, 100, -0.5, 99.5);
    fp_KRAB_Tofd_multi = new TProfile("fp_KRAB_Tofd_multi", "KRAB_Tofd_multi", 100, -0.5, 99.5,  -0.5, 99.5);
    fh2_KRAB_Tofd_multi->Draw();
    fp_KRAB_Tofd_multi->Draw("same");

    
    c_NCKT->cd(4);
    fh2_CHIMERA_Tofd_multi = new TH2I("fh2_CHIMERA_Tofd_multi", "CHIMERA_Tofd_multi", 100, -0.5, 99.5, 50, -0.5, 49.5);
    fp_CHIMERA_Tofd_multi = new TProfile("fp_CHIMERA_Tofd_multi", "CHIMERA_Tofd_multi", 100, -0.5, 99.5,   -0.5, 49.5);
    fh2_CHIMERA_Tofd_multi->Draw();
    fp_CHIMERA_Tofd_multi->Draw("same");

    
    fp_CHIMERA_Tofd_multi->SetMarkerStyle(20);
    fp_KRAB_Tofd_multi->SetMarkerStyle(20);
    
    LOG(info) << "R3BAsyCommonAnaNCKT::Init DONE";
    return kSUCCESS;
}

void R3BAsyCommonAnaNCKT::Reset_Histo()
{
    LOG(info) << "R3BAsyCommonAnaNCKT::Reset_Histo";
    fh2_KRAB_Tofd_multi->Reset();
    fp_KRAB_Tofd_multi->Reset();
    fh2_CHIMERA_Tofd_multi->Reset();
    fp_CHIMERA_Tofd_multi->Reset();    
    fh2_KRAB_NL_multi->Reset();
    fh2_CHIMERA_NL_multi->Reset();
    fp_KRAB_NL_multi->Reset();
    fp_CHIMERA_NL_multi->Reset();

}

void R3BAsyCommonAnaNCKT::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyCommonAnaNCKT::Exec FairRootManager not found";

    Int_t nHits_CHI, nHits_KRAB, nHits_NL, nHits_Tofd, mult_Tofd=0;
    UInt_t multi_CHI = -10, multi_KRAB = -10;
    Float_t RP_CHI = -1000, RP_KRAB = -1000;
    Float_t RP_CHImKRAB = -1000;

    if (fPhysItemsChimera && fPhysItemsChimera->GetEntriesFast() && 
        fPhysItemsKrab && fPhysItemsKrab->GetEntriesFast() && 
	fNeulandMappedData && fNeulandMappedData->GetEntriesFast() && 
	fTofdMappedData && fTofdMappedData->GetEntriesFast() 
	)
    {
        // --- --------------------- --- //
        // --- loop over mapped data --- //
        // --- --------------------- --- //
        nHits_CHI = fPhysItemsChimera->GetEntriesFast();
        nHits_KRAB = fPhysItemsKrab->GetEntriesFast();
        nHits_NL = fNeulandMappedData->GetEntriesFast();
        nHits_Tofd = fTofdMappedData->GetEntriesFast();

	//--------------------------------------------------------------------------------
	// ToFD
	//--------------------------------------------------------------------------------
	//std::cout << nHits_Tofd << std::endl;
        Int_t hit[4][48] = {0};
        for (Int_t imapped = 0; imapped < nHits_Tofd; imapped++)
        {
            R3BTofdMappedData* mapped = (R3BTofdMappedData*)fTofdMappedData->At(imapped);
            if (!mapped)
                continue; // should not happen

            Int_t iPlane = mapped->GetDetectorId(); // 1..4
            Int_t iBar = mapped->GetBarId();        // 1..48
            Int_t iSide = mapped->GetSideId();      // 1..2 (down and up)
            Int_t iEdge = mapped->GetEdgeId();	    // 1..2 (leading and trailing)
            
            //example of how many bars are hit in each plane            
	    hit[iPlane-1][iBar-1] = 1; 
        }
        Int_t n_particle[4] = {0};
        for (Int_t ip = 1; ip < 5; ip++)
	{
	    for (Int_t ib = 1; ib < 45; ib++)
	    {
	    	if(ip == 1 && (ib == 22 || ib == 23)) continue;
		if(ip == 2 && (ib == 22 || ib == 23)) continue;		 
		n_particle[ip - 1] += hit[ip - 1][ib - 1];
	    }
        }
        //std::cout << "Number of particles on plane 1 of ToFD: " << n_particle[0] <<  std::endl;
        //std::cout << "Number of particles on plane 2 of ToFD: " << n_particle[1] <<  std::endl;
	mult_Tofd=n_particle[0];
	
	// end ToFD
	//--------------------------------------------------------------------------------

        for (Int_t ihit = 0; ihit < nHits_CHI; ihit++)
        {
            R3BAsyChimeraPhysData* physdata = (R3BAsyChimeraPhysData*)fPhysItemsChimera->At(ihit);
            if (!physdata)
                continue;
            multi_CHI = physdata->GetMulti();
            RP_CHI = physdata->GetRP();
        }

        for (Int_t ihit = 0; ihit < nHits_KRAB; ihit++)
        {
            R3BAsyKrabPhysData* physdata = (R3BAsyKrabPhysData*)fPhysItemsKrab->At(ihit);
            if (!physdata)
                continue;
            multi_KRAB = physdata->GetMulti();
            RP_KRAB = physdata->GetRP();
        }
    }

   
    fh2_KRAB_Tofd_multi->Fill(multi_KRAB, mult_Tofd);
    fh2_CHIMERA_Tofd_multi->Fill(mult_Tofd, multi_CHI);
    fp_KRAB_Tofd_multi->Fill(multi_KRAB, mult_Tofd);
    fp_CHIMERA_Tofd_multi->Fill(mult_Tofd, multi_CHI);


    fh2_KRAB_NL_multi->Fill(nHits_NL, multi_KRAB);
    fh2_CHIMERA_NL_multi->Fill(nHits_NL, multi_CHI);
    fp_KRAB_NL_multi->Fill(nHits_NL, multi_KRAB);
    fp_CHIMERA_NL_multi->Fill(nHits_NL, multi_CHI);

    
    fNEvents += 1;
    //  std::cout << "#### Common Ana :: 142 " << std::endl;
    //  getchar();
}

void R3BAsyCommonAnaNCKT::FinishEvent()
{
    if (fPhysItemsChimera)
    {
        fPhysItemsChimera->Clear();
    }
    if (fPhysItemsKrab)
    {
        fPhysItemsKrab->Clear();
    }
    if (fNeulandMappedData)
    {
        fNeulandMappedData->Clear();
    }
    if (fTofdMappedData)
    {
        fTofdMappedData->Clear();
    }
}

void R3BAsyCommonAnaNCKT::FinishTask()
{
    //  std::cout << "#### Common Ana :: 160 " << std::endl;
    //  getchar();

    if (fPhysItemsChimera && fPhysItemsKrab && fNeulandMappedData && fTofdMappedData)
    {
        std::cout << "#### CommonAnaNC :: Finish Task " << std::endl;
        //   getchar();
        c_NCKT->Update();
	c_NCKT->Write();
    }
}

ClassImp(R3BAsyCommonAnaNCKT)
