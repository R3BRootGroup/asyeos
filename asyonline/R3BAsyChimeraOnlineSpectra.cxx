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

#include "R3BAsyChimeraOnlineSpectra.h"

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

R3BAsyChimeraOnlineSpectra::R3BAsyChimeraOnlineSpectra()
    : FairTask("AsyChimeraOnlineSpectra", 1)
    , fMappedItemsChimera(NULL)
    , fNEvents(0)
{
}

R3BAsyChimeraOnlineSpectra::R3BAsyChimeraOnlineSpectra(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMappedItemsChimera(NULL)
    , fNEvents(0)
{
}

R3BAsyChimeraOnlineSpectra::~R3BAsyChimeraOnlineSpectra()
{
    LOG(info) << "R3BAsyChimeraOnlineSpectra::Delete instance";
    if (fMappedItemsChimera)
        delete fMappedItemsChimera;
}

InitStatus R3BAsyChimeraOnlineSpectra::Init()
{
    LOG(info) << "R3BAsyChimeraOnlineSpectra::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraOnlineSpectra::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    if (verbose)
        LOG(info) << "R3BAsyChimeraOnlineSpectra::Init line 72";

    FairRunOnline* run = FairRunOnline::Instance();
    // for online server
    run->GetHttpServer()->Register("", this);

    // Register command to reset histograms
    // for online server
    run->GetHttpServer()->RegisterCommand("Reset_Chimera", Form("/Objects/%s/->Reset_Histo()", GetName()));

    // --- ------------------------------------- --- //
    // --- get access to mapped data of CHIMERA --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraOnlineSpectra::Init line 80";

    fMappedItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraMappedData");
    if (!fMappedItemsChimera)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyChimeraOnlineSpectra::Init line 87";

    // --- ------------------------------- --- //
    // --- Create histograms for detectors --- //
    // --- ------------------------------- --- //

    char Name1[255];
    char Name2[255];
    char Name3[255];
    char Name4[255];
    char Name5[255];
    char Name6[255];
    char Name7[255];
    char Name8[255];
    char Name9[255];
    char Name10[255];

    c_CHIMERA_numtel = new TCanvas("c_CHIMERA_numtel", "CHIMERA_numtel", 0, 0, 1200, 1200);
    fh1_CHIMERA_numtel = new TH1I("fh1_CHIMERA_numtel", "CHIMERA_numtel", 400, -0.5, 399.5);
    fh1_CHIMERA_numtel_wtime = new TH1I("fh1_CHIMERA_numtel_wtime", "CHIMERA_numtel_wtime", 400, -0.5, 399.5);

    c_CHIMERA_multi = new TCanvas("c_CHIMERA_multi", "CHIMERA_multi", 0, 0, 1200, 1200);
    fh1_CHIMERA_rawmulti = new TH1I("fh1_CHIMERA_rawmulti", "CHIMERA_rawmulti", 100, -0.5, 99.5);
    fh1_CHIMERA_timemulti = new TH1I("fh1_CHIMERA_timemulti", "CHIMERA_timemulti", 100, -0.5, 99.5);
    fh1_CHIMERA_multi_fast = new TH1I("fh1_CHIMERA_multi_fast", "CHIMERA_multi_fast", 100, -0.5, 99.5);
    fh1_CHIMERA_multi_slow = new TH1I("fh1_CHIMERA_multi_slow", "CHIMERA_multi_slow", 100, -0.5, 99.5);
    fh1_CHIMERA_multi_sil = new TH1I("fh1_CHIMERA_multi_sil", "CHIMERA_multi_sil", 100, -0.5, 99.5);

    c_CHIMERA_fast = new TCanvas("c_CHIMERA_fast", "CHIMERA_fast", 0, 0, 1200, 1200);
    fh2_CHIMERA_numtel_fastLG =
        new TH2I("fh2_CHIMERA_numtel_fastLG", "CHIMERA_numtel_fastLG", 400, -0.5, 399.5, 500, 0, 4000);
    fh2_CHIMERA_numtel_fastHG =
        new TH2I("fh2_CHIMERA_numtel_fastHG", "CHIMERA_numtel_fastHG", 400, -0.5, 399.5, 500, 0, 4000);

    c_CHIMERA_slow = new TCanvas("c_CHIMERA_slow", "CHIMERA_slow", 0, 0, 1200, 1200);
    fh2_CHIMERA_numtel_slowLG =
        new TH2I("fh2_CHIMERA_numtel_slowLG", "CHIMERA_numtel_slowLG", 400, -0.5, 399.5, 500, 0, 4000);
    fh2_CHIMERA_numtel_slowHG =
        new TH2I("fh2_CHIMERA_numtel_slowHG", "CHIMERA_numtel_slowHG", 400, -0.5, 399.5, 500, 0, 4000);

    c_CHIMERA_patt = new TCanvas("c_CHIMERA_patt", "CHIMERA_patt", 0, 0, 2400, 1200);
    c_CHIMERA_patt->Divide(8, 4);

    int nch = 500;
    int xymin = -0.5;
    int xymax = 4095.5;

    for (Int_t j = 0; j < 32; j++)
    {
        sprintf(Name1, "AsyChimera_patt_%i", j);
        fh1_CHIMERA_patt[j] = new TH1I(Name1, Name1, nch, xymin, xymax);
        fh1_CHIMERA_patt[j]->GetXaxis()->SetTitle("patt (ch)");
        fh1_CHIMERA_patt[j]->GetYaxis()->SetTitle("Yield");
        c_CHIMERA_patt->cd(j + 1);
        fh1_CHIMERA_patt[j]->Draw();
    }
    // Chimera main folder
    TFolder* mainfol = new TFolder("Chimera", "raw data");
    mainfol->Add(mainfol);
    c_CHIMERA_numtel->cd();
    fh1_CHIMERA_numtel->Draw();
    fh1_CHIMERA_numtel->SetLineColor(1);
    fh1_CHIMERA_numtel_wtime->Draw("same");
    fh1_CHIMERA_numtel_wtime->SetLineColor(2);

    c_CHIMERA_multi->Divide(2, 2);
    c_CHIMERA_multi->cd(1);
    fh1_CHIMERA_rawmulti->Draw();
    fh1_CHIMERA_rawmulti->SetLineColor(1);
    fh1_CHIMERA_timemulti->Draw("same");
    fh1_CHIMERA_timemulti->SetLineColor(2);
    c_CHIMERA_multi->cd(2);
    fh1_CHIMERA_multi_fast->Draw();
    c_CHIMERA_multi->cd(3);
    fh1_CHIMERA_multi_slow->Draw();
    c_CHIMERA_multi->cd(4);
    fh1_CHIMERA_multi_sil->Draw();

    c_CHIMERA_fast->Divide(1, 2);
    c_CHIMERA_fast->cd(1);
    fh2_CHIMERA_numtel_fastHG->Draw("zcol");
    c_CHIMERA_fast->cd(2);
    fh2_CHIMERA_numtel_fastLG->Draw("zcol");

    c_CHIMERA_slow->Divide(1, 2);
    c_CHIMERA_slow->cd(1);
    fh2_CHIMERA_numtel_slowHG->Draw("zcol");
    c_CHIMERA_slow->cd(2);
    fh2_CHIMERA_numtel_slowLG->Draw("zcol");

    run->AddObject(mainfol);
    LOG(info) << "R3BAsyChimeraOnlineSpectra::Init DONE";
    return kSUCCESS;
}

void R3BAsyChimeraOnlineSpectra::Reset_Histo()
{
    LOG(info) << "R3BAsyChimeraOnlineSpectra::Reset_Histo";
    // reset mapped data (for defined spectra)
    for (Int_t i = 0; i < 32; i++)
    {
        fh1_CHIMERA_patt[i]->Reset();
    }

    fh1_CHIMERA_numtel->Reset();
    fh1_CHIMERA_numtel_wtime->Reset();
    fh1_CHIMERA_rawmulti->Reset();
    fh1_CHIMERA_timemulti->Reset();
    fh1_CHIMERA_multi_fast->Reset();
    fh1_CHIMERA_multi_slow->Reset();
    fh1_CHIMERA_multi_sil->Reset();
    fh2_CHIMERA_numtel_fastLG->Reset();
    fh2_CHIMERA_numtel_fastHG->Reset();
    fh2_CHIMERA_numtel_slowLG->Reset();
    fh2_CHIMERA_numtel_slowHG->Reset();
}

void R3BAsyChimeraOnlineSpectra::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraOnlineSpectra::Exec FairRootManager not found";

    Int_t nHits;
    UShort_t rawmulti = 0, timemulti = 0, multi_fast = 0, multi_slow = 0, multi_sil = 0;
    UShort_t iNumTel, iFastHG, iFastLG, iSlowHG, iSlowLG, iTimeCsI, iSilHG, iSilLG, iTimeSil, iPatt;

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
            fh1_CHIMERA_numtel->Fill(iNumTel);
            iFastHG = hitmapped->GetFastHG();
            iFastLG = hitmapped->GetFastLG();
            iSlowHG = hitmapped->GetSlowHG();
            iSlowLG = hitmapped->GetSlowLG();
            iTimeCsI = hitmapped->GetTimeCsI();
            iSilHG = hitmapped->GetSilHG();
            iSilLG = hitmapped->GetSilLG();
            iTimeSil = hitmapped->GetTimeSil();
            iPatt = hitmapped->GetPatt();
            rawmulti++;
            if (iTimeSil > 0 || iTimeCsI > 0)
            {
                timemulti++;
                fh1_CHIMERA_numtel_wtime->Fill(iNumTel);
            }
            if ((iFastHG > 0 || iFastLG > 0) && iTimeCsI > 0)
                multi_fast++;
            if ((iSlowHG > 0 || iSlowLG > 0) && iTimeCsI > 0)
                multi_slow++;
            if ((iSilHG > 0 || iSilLG > 0) && iTimeSil > 0)
                multi_sil++;
            if (iFastLG)
                fh2_CHIMERA_numtel_fastLG->Fill(iNumTel, iFastLG);
            if (iFastHG)
                fh2_CHIMERA_numtel_fastHG->Fill(iNumTel, iFastHG);
            if (iSlowLG)
                fh2_CHIMERA_numtel_slowLG->Fill(iNumTel, iSlowLG);
            if (iSlowHG)
                fh2_CHIMERA_numtel_slowHG->Fill(iNumTel, iSlowHG);

            if (iNumTel >= 0 && iNumTel <= 31)
            {
                if (iPatt > 0)
                    fh1_CHIMERA_patt[iNumTel]->Fill(iPatt);
            }
        }
    }

    fh1_CHIMERA_rawmulti->Fill(rawmulti);
    fh1_CHIMERA_timemulti->Fill(timemulti);
    fh1_CHIMERA_multi_fast->Fill(multi_fast);
    fh1_CHIMERA_multi_slow->Fill(multi_slow);
    fh1_CHIMERA_multi_sil->Fill(multi_sil);
    fNEvents += 1;
}

void R3BAsyChimeraOnlineSpectra::FinishEvent()
{
    if (fMappedItemsChimera)
    {
        fMappedItemsChimera->Clear();
    }
}

void R3BAsyChimeraOnlineSpectra::FinishTask()
{
    if (fMappedItemsChimera)
    {
        c_CHIMERA_numtel->Update();
        c_CHIMERA_multi->Update();
        c_CHIMERA_fast->Update();
        c_CHIMERA_slow->Update();
        c_CHIMERA_patt->Update();

        c_CHIMERA_numtel->Write();
        c_CHIMERA_multi->Write();
        c_CHIMERA_fast->Write();
        c_CHIMERA_slow->Write();
        c_CHIMERA_patt->Write();
    }
}
ClassImp(R3BAsyChimeraOnlineSpectra)
