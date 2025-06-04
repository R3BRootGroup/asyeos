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

#include "R3BAsyChimeraPuls.h"

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

R3BAsyChimeraPuls::R3BAsyChimeraPuls()
    : FairTask("AsyChimeraPuls", 1)
    , fMappedItemsChimera(NULL)
    , fNEvents(0)
{
}

R3BAsyChimeraPuls::R3BAsyChimeraPuls(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMappedItemsChimera(NULL)
    , fNEvents(0)
{
}

R3BAsyChimeraPuls::~R3BAsyChimeraPuls() { LOG(info) << "R3BAsyChimeraPuls::Delete instance"; }

InitStatus R3BAsyChimeraPuls::Init()
{
    LOG(info) << "R3BAsyChimeraPuls::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraPuls::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");
    header = dynamic_cast<R3BEventHeader*>(mgr->GetObject("EventHeader."));

    if (verbose)
        LOG(info) << "R3BAsyChimeraPuls::Init line 72";
    // Register output array in tree

    LOG(info) << "R3BAsyChimeraPuls::Init DONE";

    // --- ------------------------------------- --- //
    // --- get access to mapped data of CHIMERA --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraPuls::Init line 80";

    fMappedItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraMappedData");
    if (!fMappedItemsChimera)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyChimeraPuls::Init line 87";

    //    f1= new TFile("pulser_out.root","RECREATE");

    char Name1[255];
    char Name2[255];

    char Name11[255];
    char Name22[255];

    int nch = 1000;
    int xymin = -0.5;
    int xymax = 4000.5;

    for (Int_t j = 0; j <= 79; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        fh1_fast_HG[j] = new TH1I(Name1, Name1, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name2, nch, xymin, xymax);
    }

    for (Int_t j = 80; j <= 111; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 80) <= 9)
        {
            sprintf(Name11, "R3SLOW0%i-I", j - 80);
            sprintf(Name22, "R3SLOW0%i-I", j - 80);
        }
        else
        {
            sprintf(Name11, "R3SLOW%i-I", j - 80);
            sprintf(Name22, "R3SLOW%i-I", j - 80);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }
    for (Int_t j = 112; j <= 143; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 112) <= 9)
        {
            sprintf(Name11, "R3SLOW0%i-E", j - 112);
            sprintf(Name22, "R3SLOW0%i-E", j - 112);
        }
        else
        {
            sprintf(Name11, "R3SLOW%i-E", j - 112);
            sprintf(Name22, "R3SLOW%i-E", j - 112);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }

    for (Int_t j = 144; j <= 183; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 144) <= 9)
        {
            sprintf(Name11, "R4SLOW0%i-I", j - 144);
            sprintf(Name22, "R4SLOW0%i-I", j - 144);
        }
        else
        {
            sprintf(Name11, "R4SLOW%i-I", j - 144);
            sprintf(Name22, "R4SLOW%i-I", j - 144);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }
    for (Int_t j = 184; j <= 223; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 184) <= 9)
        {
            sprintf(Name11, "R4SLOW0%i-E", j - 184);
            sprintf(Name22, "R4SLOW0%i-E", j - 184);
        }
        else
        {
            sprintf(Name11, "R4SLOW%i-E", j - 184);
            sprintf(Name22, "R4SLOW%i-E", j - 184);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }

    for (Int_t j = 224; j <= 263; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 224) <= 9)
        {
            sprintf(Name11, "R5SLOW0%i-I", j - 224);
            sprintf(Name22, "R5SLOW0%i-I", j - 224);
        }
        else
        {
            sprintf(Name11, "R5SLOW%i-I", j - 224);
            sprintf(Name22, "R5SLOW%i-I", j - 224);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }
    for (Int_t j = 264; j <= 303; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 264) <= 9)
        {
            sprintf(Name11, "R5SLOW0%i-E", j - 264);
            sprintf(Name22, "R5SLOW0%i-E", j - 264);
        }
        else
        {
            sprintf(Name11, "R5SLOW%i-E", j - 264);
            sprintf(Name22, "R5SLOW%i-E", j - 264);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }

    for (Int_t j = 304; j <= 351; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 303) <= 9)
        {
            sprintf(Name11, "R6SLOW0%i-I", j - 304);
            sprintf(Name22, "R6SLOW0%i-I", j - 304);
        }
        else
        {
            sprintf(Name11, "R6SLOW%i-I", j - 304);
            sprintf(Name22, "R6SLOW%i-I", j - 304);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }
    for (Int_t j = 352; j <= 399; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        if ((j - 352) <= 9)
        {
            sprintf(Name11, "R6SLOW0%i-E", j - 352);
            sprintf(Name22, "R6SLOW0%i-E", j - 352);
        }
        else
        {
            sprintf(Name11, "R6SLOW%i-E", j - 352);
            sprintf(Name22, "R6SLOW%i-E", j - 352);
        }
        fh1_fast_HG[j] = new TH1I(Name1, Name11, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name22, nch, xymin, xymax);
    }

    for (Int_t j = 400; j <= 1191; j++)
    {
        sprintf(Name1, "h%i", 10000 + j);
        sprintf(Name2, "h%i", 20000 + j);
        fh1_fast_HG[j] = new TH1I(Name1, Name1, nch, xymin, xymax);
        fh1_fast_LG[j] = new TH1I(Name2, Name2, nch, xymin, xymax);
    }

    LOG(info) << "R3BAsyChimeraPuls::Init DONE";
    //    coll

    return kSUCCESS;
}

void R3BAsyChimeraPuls::Reset_Histo() { LOG(info) << "R3BAsyChimeraPuls::Reset_Histo"; }

void R3BAsyChimeraPuls::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraPuls::Exec FairRootManager not found";

    Int_t nHits;
    UShort_t iNumTel, iFastHG, iFastLG, iSlowHG, iSlowLG, iTimeCsI, iSilHG, iSilLG, iTimeSil, iPatt;

    Int_t trig = -1000;
    if (header)
    {
        trig = header->GetTrigger();
        // std:: cout << "R3BAsyChimPhys:: " << trig << " " << std::endl;
    }

    if (fMappedItemsChimera && fMappedItemsChimera->GetEntriesFast())
    {
        // --- --------------------- --- //
        // --- loop over mapped data --- //
        // --- --------------------- --- //
        nHits = fMappedItemsChimera->GetEntriesFast();
        int time_trig = 0;
        int time1 = 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            R3BAsyChimeraMappedData* hitmapped = (R3BAsyChimeraMappedData*)fMappedItemsChimera->At(ihit);
            if (!hitmapped)
                continue;
            iNumTel = hitmapped->GetNumTel();
            iFastHG = hitmapped->GetFastHG();
            iFastLG = hitmapped->GetFastLG();
            iSlowHG = hitmapped->GetSlowHG();
            iSlowLG = hitmapped->GetSlowLG();
            iTimeCsI = hitmapped->GetTimeCsI();
            iSilHG = hitmapped->GetSilHG();
            iSilLG = hitmapped->GetSilLG();
            iTimeSil = hitmapped->GetTimeSil();
            iPatt = hitmapped->GetPatt();

            if (iSlowLG > 480)
                fh1_fast_LG[iNumTel]->Fill(iSlowLG);
            if (iSlowHG > 0)
                fh1_fast_HG[iNumTel]->Fill(iSlowHG);
        }
    }

    fNEvents += 1;
}

void R3BAsyChimeraPuls::FinishEvent()
{
    if (fMappedItemsChimera)
    {
        fMappedItemsChimera->Clear();
    }
}

void R3BAsyChimeraPuls::FinishTask()
{
    bool towrite = true;
    if (fMappedItemsChimera)
    {
        //     f1->cd();
        for (Int_t j = 0; j < 1192; j++)
        {
            fh1_fast_HG[j]->Write();
            fh1_fast_LG[j]->Write();
            if (towrite)
                std::cout << "write " << std::endl;
            towrite = false;
        }
        //     f1->Close();
    }
}

ClassImp(R3BAsyChimeraPuls)
