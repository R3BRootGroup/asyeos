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

#include "R3BAsyCommonAnaNC.h"

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

R3BAsyCommonAnaNC::R3BAsyCommonAnaNC()
    : FairTask("AsyCommonAnaNC", 1)
    , fPhysItemsChimera(0)
    , fPhysItemsKrab(0)
    , fNeulandMappedData(0)
    , fNEvents(0)
{
}

R3BAsyCommonAnaNC::R3BAsyCommonAnaNC(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fPhysItemsChimera(0)
    , fPhysItemsKrab(0)
    , fNeulandMappedData(0)
    , fNEvents(0)
{
}

R3BAsyCommonAnaNC::~R3BAsyCommonAnaNC()
{
    LOG(info) << "R3BAsyCommonAnaNC::Delete instance";
    if (fPhysItemsChimera)
        delete fPhysItemsChimera;
    if (fPhysItemsKrab)
        delete fPhysItemsKrab;
    if (fNeulandMappedData)
        delete fNeulandMappedData;
}

InitStatus R3BAsyCommonAnaNC::Init()
{
    LOG(info) << "R3BAsyCommonAnaNC::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyCommonAnaNC::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    if (verbose)
        LOG(info) << "R3BAsyCommonAnaNC::Init line 72";

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
        LOG(info) << "R3BAsyCommonAnaNC::Init line 80";

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
    if (verbose)
        LOG(info) << "R3BAsyCommonAnaNC::Init line 87";


    c_NL_CHIMERA_KRAB = new TCanvas("c_NL_CHIMERA_KRAB", "NL_CHIMERA_KRAB", 0, 0, 1200, 1200);
    c_NL_CHIMERA_KRAB->Divide(2, 2);
    fh2_KRAB_NL_multi = new TH2I("fh2_KRAB_NL_multi", "KRAB_NL_multi", 100, -0.5, 99.5, 100, -0.5, 99.5);
    fp_KRAB_NL_multi = new TProfile("fp_KRAB_NL_multi", "KRAB_NL_multi", 100, -0.5, 99.5,  -0.5, 99.5);

    fh2_CHIMERA_NL_multi = new TH2I("fh2_CHIMERA_NL_multi", "CHIMERA_NL_multi", 100, -0.5, 99.5, 50, -0.5, 49.5);
    fp_CHIMERA_NL_multi = new TProfile("fp_CHIMERA_NL_multi", "CHIMERA_NL_multi", 100, -0.5, 99.5, 1 -0.5, 49.5);
    
    c_NL_CHIMERA_KRAB->cd(1);
    fh2_KRAB_NL_multi->Draw();
    fp_KRAB_NL_multi->Draw("same");
    c_NL_CHIMERA_KRAB->cd(2);
    fh2_CHIMERA_NL_multi->Draw();
    fp_CHIMERA_NL_multi->Draw("same");
    
    fp_CHIMERA_NL_multi->SetMarkerStyle(20);
    fp_KRAB_NL_multi->SetMarkerStyle(20);
    
    LOG(info) << "R3BAsyCommonAnaNC::Init DONE";
    return kSUCCESS;
}

void R3BAsyCommonAnaNC::Reset_Histo()
{
    LOG(info) << "R3BAsyCommonAnaNC::Reset_Histo";
    fh2_KRAB_NL_multi->Reset();
    fh2_CHIMERA_NL_multi->Reset();
    fp_KRAB_NL_multi->Reset();
    fp_CHIMERA_NL_multi->Reset();
}

void R3BAsyCommonAnaNC::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyCommonAnaNC::Exec FairRootManager not found";

    Int_t nHits_CHI, nHits_KRAB, nHits_NL;
    UInt_t multi_CHI = -10, multi_KRAB = -10;
    Float_t RP_CHI = -1000, RP_KRAB = -1000;
    Float_t RP_CHImKRAB = -1000;

    if (fPhysItemsChimera && fPhysItemsChimera->GetEntriesFast() && 
        fPhysItemsKrab && fPhysItemsKrab->GetEntriesFast() && 
	fNeulandMappedData && fNeulandMappedData->GetEntriesFast() )
    {
        // --- --------------------- --- //
        // --- loop over mapped data --- //
        // --- --------------------- --- //
        nHits_CHI = fPhysItemsChimera->GetEntriesFast();
        nHits_KRAB = fPhysItemsKrab->GetEntriesFast();
        nHits_NL = fNeulandMappedData->GetEntriesFast();

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

    
    fh2_KRAB_NL_multi->Fill(nHits_NL, multi_KRAB);
    fh2_CHIMERA_NL_multi->Fill(nHits_NL, multi_CHI);
    fp_KRAB_NL_multi->Fill(nHits_NL, multi_KRAB);
    fp_CHIMERA_NL_multi->Fill(nHits_NL, multi_CHI);
    
    fNEvents += 1;
    //  std::cout << "#### Common Ana :: 142 " << std::endl;
    //  getchar();
}

void R3BAsyCommonAnaNC::FinishEvent()
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
}

void R3BAsyCommonAnaNC::FinishTask()
{
    //  std::cout << "#### Common Ana :: 160 " << std::endl;
    //  getchar();

    if (fPhysItemsChimera && fPhysItemsKrab && fNeulandMappedData)
    {
        std::cout << "#### CommonAnaNC :: Finish Task " << std::endl;
        //   getchar();
        c_NL_CHIMERA_KRAB->Update();
	c_NL_CHIMERA_KRAB->Write();
    }
}

ClassImp(R3BAsyCommonAnaNC)
