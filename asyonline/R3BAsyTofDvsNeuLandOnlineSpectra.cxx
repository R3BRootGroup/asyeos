/******************************************************************************
 *   Copyright (C) 2025 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2025 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

// ------------------------------------------------------------
// -----         R3BAsyTofDvsNeuLandOnlineSpectra         -----
// -----    Created 03/03/25 by J.L. Rodriguez-Sanchez    -----
// -----      Fill Tofd vs NeuLAND online histograms      -----
// ------------------------------------------------------------

// ROOT headers
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TFolder.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THttpServer.h>
#include <TMath.h>
#include <TVector3.h>

// FAIR headers
#include <FairLogger.h>
#include <FairRootManager.h>
#include <FairRunOnline.h>
#include <FairRuntimeDb.h>

// R3B headers
#include "R3BAsyTofDvsNeuLandOnlineSpectra.h"
#include "R3BCoarseTimeStitch.h"
#include "R3BEventHeader.h"
#include "R3BLogger.h"
#include "R3BShared.h"
#include "R3BTCalEngine.h"
#include "R3BTofDMappingPar.h"
#include "R3BTofdCalData.h"
#include "R3BTofdHitData.h"
#include "R3BTofdMappedData.h"

#define IS_NAN(x) TMath::IsNaN(x)
using namespace std;

namespace
{
    uint64_t n1, n2;
} // namespace

// R3BAsyTofDvsNeuLandOnlineSpectra::Default Constructor --------------------------
R3BAsyTofDvsNeuLandOnlineSpectra::R3BAsyTofDvsNeuLandOnlineSpectra()
    : R3BAsyTofDvsNeuLandOnlineSpectra("TofDvsNeuLandOnlineSpectra", 1)
{
}

// R3BAsyTofDvsNeuLandOnlineSpectra::Standard Constructor --------------------------
R3BAsyTofDvsNeuLandOnlineSpectra::R3BAsyTofDvsNeuLandOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNeulandCalData("NeulandCalData")
    , fNeulandHits("NeulandHits")
{
}

// Virtual R3BAsyTofDvsNeuLandOnlineSpectra::Destructor
R3BAsyTofDvsNeuLandOnlineSpectra::~R3BAsyTofDvsNeuLandOnlineSpectra()
{
    R3BLOG(debug1, "Destructor");
    if (fMappedItems)
        delete fMappedItems;
    if (fCalItems)
        delete fCalItems;
    if (fHitItems)
        delete fHitItems;
}

void R3BAsyTofDvsNeuLandOnlineSpectra::SetParContainers()
{
    fMapPar = dynamic_cast<R3BTofDMappingPar*>(FairRuntimeDb::instance()->getContainer("tofdMappingPar"));
    R3BLOG_IF(warn, !fMapPar, "Could not get access to tofdMappingPar container");
    return;
}

void R3BAsyTofDvsNeuLandOnlineSpectra::SetParameter()
{
    R3BLOG_IF(info, fMapPar, "Nb of planes " << fMapPar->GetNbPlanes() << " and paddles " << fMapPar->GetNbPaddles());
    if (fMapPar)
    {
        fNofPlanes = fMapPar->GetNbPlanes();
        fPaddlesPerPlane = fMapPar->GetNbPaddles();
    }

    return;
}

InitStatus R3BAsyTofDvsNeuLandOnlineSpectra::Init()
{
    R3BLOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    R3BLOG_IF(fatal, mgr == nullptr, "FairRootManager not found");

    header = dynamic_cast<R3BEventHeader*>(mgr->GetObject("EventHeader."));
    R3BLOG_IF(error, header == nullptr, "EventHeader. not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    fCalTriggerItems = dynamic_cast<TClonesArray*>(mgr->GetObject("TofdTriggerCal"));
    R3BLOG_IF(warn, fCalTriggerItems == nullptr, "TofdTriggerCal not found");

    fMappedItems = dynamic_cast<TClonesArray*>(mgr->GetObject("TofdMapped"));
    R3BLOG_IF(fatal, fMappedItems == nullptr, "TofdMapped not found");

    fCalItems = dynamic_cast<TClonesArray*>(mgr->GetObject("TofdCal"));
    R3BLOG_IF(fatal, fCalItems == nullptr, "TofdCal not found");

    fHitItems = dynamic_cast<TClonesArray*>(mgr->GetObject("TofdHit"));
    R3BLOG_IF(warn, fHitItems == nullptr, "TofdHit not found");

    fNeulandCalData.Init();
    fNeulandHits.Init();

    SetParameter();

    // MAIN FOLDER
    auto* maintofd = new TFolder("TofD", "TofD info");

    //------------------------------------------------------------------------
    // Create histograms
    //------------------------------------------------------------------------

    if (fMappedItems && fCalItems)
    {
        auto* cBarsCorrelations =
            new TCanvas("TofD_NL_Bar_correlation", "TofD vs NL bar correlations", 10, 10, 1100, 1000);
        cBarsCorrelations->Divide(1, 2);

        fh2_tofdbar_vs_nlbar.resize(2);
        for (int pln = 0; pln < 2; pln++)
        {
            std::string nameHist = "fh2_TofD_Plane_" + std::to_string(pln + 3);
            std::string titleHist = "Bar correlation for TofD plane " + std::to_string(pln + 3) + " vs NL bars";

            fh2_tofdbar_vs_nlbar[pln] =
                R3B::root_owned<TH2F>(nameHist.c_str(), titleHist.c_str(), 1303, 0, 1302, 46, 0, 45);

            fh2_tofdbar_vs_nlbar[pln]->GetXaxis()->SetTitle("NL bar");
            fh2_tofdbar_vs_nlbar[pln]->GetYaxis()->SetTitle("TofD bar");
            fh2_tofdbar_vs_nlbar[pln]->GetYaxis()->SetTitleOffset(1.1);
            fh2_tofdbar_vs_nlbar[pln]->GetXaxis()->CenterTitle(true);
            fh2_tofdbar_vs_nlbar[pln]->GetYaxis()->CenterTitle(true);

            cBarsCorrelations->cd(pln + 1);
            fh2_tofdbar_vs_nlbar[pln]->Draw("colz");
        }
        maintofd->Add(cBarsCorrelations);
    }

    if (fHitItems)
    {
        auto* cTofDiff = new TCanvas("TofDiff_vs_NlBar", "Tof Diff. (TofD-Nl) vs NL bar", 10, 10, 1100, 1000);
        fh2_TofvsNlBar = R3B::root_owned<TH2F>("fh2_Tof_vs_NlBar", "", 1303, 0, 1302, 200, -5000, 5000);

        fh2_TofvsNlBar->GetXaxis()->SetTitle("NL bar");
        fh2_TofvsNlBar->GetYaxis()->SetTitle("Tof-Diff. (TofD-Nl) / ns");
        fh2_TofvsNlBar->GetYaxis()->SetTitleOffset(1.1);
        fh2_TofvsNlBar->GetXaxis()->CenterTitle(true);
        fh2_TofvsNlBar->GetYaxis()->CenterTitle(true);
        cTofDiff->cd();
        fh2_TofvsNlBar->Draw("colz");
        maintofd->Add(cTofDiff);

        auto* cXcorr = new TCanvas("XTofD_vs_XNl", "X correlation: TofD vs NL", 10, 10, 1100, 1000);
        fh2_XTofdvsXNl = R3B::root_owned<TH2F>("fh2_XTofD_vs_XNl", "", 300, -150, 150, 140, -70, 70);
        fh2_XTofdvsXNl->GetXaxis()->SetTitle("X-Nl / cm");
        fh2_XTofdvsXNl->GetYaxis()->SetTitle("X-TofD / cm");
        fh2_XTofdvsXNl->GetYaxis()->SetTitleOffset(1.1);
        fh2_XTofdvsXNl->GetXaxis()->CenterTitle(true);
        fh2_XTofdvsXNl->GetYaxis()->CenterTitle(true);
        cXcorr->cd();
        fh2_XTofdvsXNl->Draw("colz");
        maintofd->Add(cXcorr);

        auto* cYcorr = new TCanvas("YTofD_vs_XNl", "Y correlation: TofD vs NL", 10, 10, 1100, 1000);
        fh2_YTofdvsYNl = R3B::root_owned<TH2F>("fh2_YTofD_vs_YNl", "", 300, -150, 150, 100, -50, 50);
        fh2_YTofdvsYNl->GetXaxis()->SetTitle("Y-Nl / cm");
        fh2_YTofdvsYNl->GetYaxis()->SetTitle("Y-TofD / cm");
        fh2_YTofdvsYNl->GetYaxis()->SetTitleOffset(1.1);
        fh2_YTofdvsYNl->GetXaxis()->CenterTitle(true);
        fh2_YTofdvsYNl->GetYaxis()->CenterTitle(true);
        cYcorr->cd();
        fh2_YTofdvsYNl->Draw("colz");
        maintofd->Add(cYcorr);
    }

    run->AddObject(maintofd);
    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_TofD_vs_NeuLand_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    // Definition of a time stich object to correlate times coming from different systems
    fTimeStitch = std::make_unique<R3BCoarseTimeStitch>();

    return kSUCCESS;
}

void R3BAsyTofDvsNeuLandOnlineSpectra::Reset_Histo()
{
    R3BLOG(info, "");

    if (fMappedItems && fCalItems)
    {
        for (const auto& hist : fh2_tofdbar_vs_nlbar)
        {
            hist->Reset();
        }
    }
    if (fHitItems)
    {
        fh2_TofvsNlBar->Reset();
        fh2_XTofdvsXNl->Reset();
        fh2_YTofdvsYNl->Reset();
        // fh2_tofd_TofvsE->Reset();
        // fh2_nl_TofvsE_with_tofd->Reset();
        // fh2_nl_TofvsE_without_tofd->Reset();
    }
    return;
}

void R3BAsyTofDvsNeuLandOnlineSpectra::Exec(Option_t* option)
{

    if ((fTrigger >= 0) && (header) && (header->GetTrigger() != fTrigger))
        return;
    // fTpat = 1-16; fTpat_bit = 0-15
    Int_t fTpat_bit1 = fTpat1 - 1;
    Int_t fTpat_bit2 = fTpat2 - 1;
    Int_t tpatbin = 0;
    std::vector<int> tpatindex;

    if (header)
    {
        for (Int_t i = 0; i < 16; i++)
        {
            tpatbin = (header->GetTpat() & (1 << i));
            if (tpatbin != 0)
                tpatindex.push_back(i + 1);
        }
    }

    Int_t NumPaddles[fNofPlanes];
    for (int i = 0; i < fNofPlanes; i++)
        NumPaddles[i] = 0;

    const auto calDataNl = fNeulandCalData.Retrieve();
    const auto hitsNl = fNeulandHits.Retrieve();
    const double clight = 29.9792458;

    if (fMappedItems)
    {
        Int_t nMapped = fMappedItems->GetEntriesFast();
        Int_t iPlaneMem = 1, iBarMem = 0;

        Int_t nsum_top[fNofPlanes];
        Int_t nsum_bot[fNofPlanes];
        for (Int_t p = 0; p < fNofPlanes; p++)
        {
            nsum_top[p] = 0;
            nsum_bot[p] = 0;
        }

        for (Int_t imapped = 0; imapped < nMapped; imapped++)
        {
            auto mapped = dynamic_cast<R3BTofdMappedData*>(fMappedItems->At(imapped));
            if (!mapped)
                continue; // should not happen

            Int_t const iPlane = mapped->GetDetectorId(); // 1..n
            Int_t const iBar = mapped->GetBarId();        // 1..n
            Int_t const iSide = mapped->GetSideId();      // 1..n
            Int_t const iEdge = mapped->GetEdgeId();

            if (iSide == 1 && iEdge == 1 && iPlane < fNofPlanes)
                nsum_bot[iPlane - 1] += 1;
            if (iSide == 2 && iEdge == 1 && iPlane < fNofPlanes)
                nsum_top[iPlane - 1] += 1;

            if (iPlaneMem != iPlane)
                iBarMem = 0;
            if (iPlane == 1 && iBarMem != iBar && iSide == 1 && iEdge == 1)
                NumPaddles[0] += 1;
            if (iPlane == 2 && iBarMem != iBar && iSide == 1 && iEdge == 1)
                NumPaddles[1] += 1;
            if (iPlane == 3 && iBarMem != iBar && iSide == 1 && iEdge == 1)
                NumPaddles[2] += 1;
            if (iPlane == 3 && iBarMem != iBar && iSide == 1 && iEdge == 1)
                NumPaddles[3] += 1;

            iPlaneMem = iPlane;
            iBarMem = iBar;
        }
    }

    std::vector<double> fTof_without_trig(44, 0.);
    if (fCalItems)
    {
        UInt_t vmultihits[fNofPlanes + 1][fPaddlesPerPlane];
        UInt_t vmultihits_top[fNofPlanes + 1][fPaddlesPerPlane];
        UInt_t vmultihits_bot[fNofPlanes + 1][fPaddlesPerPlane];
        Double_t time_bar[fNofPlanes + 1][fPaddlesPerPlane][fMaxmul];
        for (Int_t i = 0; i < fNofPlanes + 1; i++)
        {
            for (Int_t j = 0; j < fPaddlesPerPlane; j++)
            {
                vmultihits[i][j] = 0;
                vmultihits_top[i][j] = 0;
                vmultihits_bot[i][j] = 0;
                for (Int_t l = 0; l < fMaxmul; l++)
                {
                    time_bar[i][j][l] = 0. / 0.;
                }
            }
        }

        //    std::cout<<"new event!*************************************\n";
        Int_t nHits = fCalItems->GetEntriesFast();

        Int_t nHitsEvent = 0;
        // Organize cals into bars.
        struct Entry
        {
            std::vector<R3BTofdCalData*> top;
            std::vector<R3BTofdCalData*> bot;
        };

        std::map<size_t, Entry> bar_map;
        //   puts("Event");
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            auto* hit = dynamic_cast<R3BTofdCalData*>(fCalItems->At(ihit));
            size_t idx = (hit->GetDetectorId() - 1) * fPaddlesPerPlane + hit->GetBarId() - 1;

            auto ret = bar_map.insert(std::pair<size_t, Entry>(idx, Entry()));

            // hit->GetSideId() gives 1 for bottom and 2 for top
            auto& vec = 1 == hit->GetSideId() ? ret.first->second.bot : ret.first->second.top;
            vec.push_back(hit);
        }

        // Build trigger map.
        std::vector<R3BTofdCalData*> trig_map;
        for (int i = 0; i < fCalTriggerItems->GetEntries(); ++i)
        {
            auto trig = dynamic_cast<R3BTofdCalData*>(fCalTriggerItems->At(i));
            if (trig_map.size() < trig->GetBarId())
            {
                trig_map.resize(trig->GetBarId());
            }
            trig_map.at(trig->GetBarId() - 1) = trig;
        }

        // Without coincidences
        bool s_was_trig_missing = false;

        for (auto it = bar_map.begin(); bar_map.end() != it; ++it)
        {
            auto const& top_vec = it->second.top;
            size_t top_i = 0;
            auto const& bot_vec = it->second.bot;
            size_t bot_i = 0;
            for (; top_i < top_vec.size();)
            {
                auto top = top_vec.at(top_i);
                Int_t top_trig_i = 0;

                if (fMapPar)
                    top_trig_i = fMapPar->GetTrigMap(top->GetDetectorId(), top->GetBarId(), top->GetSideId());

                Double_t top_trig_ns = 0;
                if (top_trig_i < trig_map.size() && trig_map.at(top_trig_i))
                {
                    auto top_trig = trig_map.at(top_trig_i);
                    top_trig_ns = top_trig->GetTimeLeading_ns();
                }
                else
                {
                    if (!s_was_trig_missing)
                    {
                        R3BLOG(error, "Missing trigger information!");
                        s_was_trig_missing = true;
                    }
                }

                Int_t iPlane = top->GetDetectorId(); // 1..n
                Int_t iBar = top->GetBarId();        // 1..n
                if (iPlane > fNofPlanes)             // this also errors for iDetector==0
                {
                    R3BLOG(error, "More detectors than expected! Det: " << iPlane << " allowed are 1.." << fNofPlanes);
                    continue;
                }
                if (iBar > fPaddlesPerPlane) // same here
                {
                    R3BLOG(error, "More bars then expected! Det: " << iBar << " allowed are 1.." << fPaddlesPerPlane);
                    continue;
                }

                auto top_tot = fmod(top->GetTimeTrailing_ns() - top->GetTimeLeading_ns() + fC_range_ns, fC_range_ns);
                // fh_tofd_TotPm[iPlane - 1]->Fill(iBar, top_tot);

                vmultihits_top[iPlane - 1][iBar - 1] += 1;
                ++top_i;
            }

            for (; bot_i < bot_vec.size();)
            {
                auto bot = bot_vec.at(bot_i);
                Int_t bot_trig_i = 0;

                if (fMapPar)
                    bot_trig_i = fMapPar->GetTrigMap(bot->GetDetectorId(), bot->GetBarId(), bot->GetSideId());

                Double_t bot_trig_ns = 0;
                if (bot_trig_i < trig_map.size() && trig_map.at(bot_trig_i))
                {
                    auto bot_trig = trig_map.at(bot_trig_i);
                    bot_trig_ns = bot_trig->GetTimeLeading_ns();
                }
                else
                {
                    if (!s_was_trig_missing)
                    {
                        R3BLOG(error, "Missing trigger information!");
                        s_was_trig_missing = true;
                    }
                }

                // Shift the cyclic difference window by half a window-length and move it back,
                // this way the trigger time will be at 0.
                auto bot_ns =
                    fmod(bot->GetTimeLeading_ns() - bot_trig_ns + fC_range_ns + fC_range_ns / 2, fC_range_ns) -
                    fC_range_ns / 2;

                Int_t iPlane = bot->GetDetectorId(); // 1..n
                Int_t iBar = bot->GetBarId();        // 1..n
                if (iPlane > fNofPlanes)             // this also errors for iDetector==0
                {
                    R3BLOG(error, "More detectors than expected! Det: " << iPlane << " allowed are 1.." << fNofPlanes);
                    continue;
                }
                if (iBar > fPaddlesPerPlane) // same here
                {
                    R3BLOG(error, "More bars then expected! Det: " << iBar << " allowed are 1.." << fPaddlesPerPlane);
                    continue;
                }

                auto bot_tot = fmod(bot->GetTimeTrailing_ns() - bot->GetTimeLeading_ns() + fC_range_ns, fC_range_ns);

                // fh_tofd_TotPm[iPlane - 1]->Fill(-iBar - 1, bot_tot);

                // register multi hits
                vmultihits_bot[iPlane - 1][iBar - 1] += 1;

                ++bot_i;
            }
        }

        for (Int_t ipl = 0; ipl < fNofPlanes; ipl++)
        {
            for (Int_t ibr = 1; ibr < fPaddlesPerPlane + 1; ibr++)
            {
                //  fh_tofd_multihit[ipl]->Fill(-ibr - 1, vmultihits_bot[ipl][ibr - 1]);
                //  fh_tofd_multihit[ipl]->Fill(ibr, vmultihits_top[ipl][ibr - 1]);
            }
        }

        // With coincidences:
        bool s_was_trig_missingc = false;
        for (auto it = bar_map.begin(); bar_map.end() != it; ++it)
        {
            auto const& topc_vec = it->second.top;
            auto const& botc_vec = it->second.bot;
            size_t topc_i = 0;
            size_t botc_i = 0;
            for (; topc_i < topc_vec.size() && botc_i < botc_vec.size();)
            {
                auto topc = topc_vec.at(topc_i);
                auto botc = botc_vec.at(botc_i);

                Int_t topc_trig_i = 0;
                Int_t botc_trig_i = 0;
                if (fMapPar)
                {
                    topc_trig_i = fMapPar->GetTrigMap(topc->GetDetectorId(), topc->GetBarId(), topc->GetSideId());
                    botc_trig_i = fMapPar->GetTrigMap(botc->GetDetectorId(), botc->GetBarId(), botc->GetSideId());
                }

                Double_t topc_trig_ns = 0, botc_trig_ns = 0;
                if (topc_trig_i < trig_map.size() && trig_map.at(topc_trig_i) && botc_trig_i < trig_map.size() &&
                    trig_map.at(botc_trig_i))
                {
                    auto topc_trig = trig_map.at(topc_trig_i);
                    auto botc_trig = trig_map.at(botc_trig_i);
                    topc_trig_ns = topc_trig->GetTimeLeading_ns();
                    botc_trig_ns = botc_trig->GetTimeLeading_ns();
                    ++n1;
                }
                else
                {
                    if (!s_was_trig_missingc)
                    {
                        R3BLOG(error, "Missing trigger information!");
                        s_was_trig_missingc = true;
                    }
                    ++n2;
                }

                // Shift the cyclic difference window by half a window-length and move it back,
                // this way the trigger time will be at 0.
                auto topc_ns = fTimeStitch->GetTime(topc->GetTimeLeading_ns() - topc_trig_ns);
                auto botc_ns = fTimeStitch->GetTime(botc->GetTimeLeading_ns() - botc_trig_ns);

                auto dt = topc_ns - botc_ns;
                // Handle wrap-around.
                auto dt_mod = fmod(dt + fC_range_ns, fC_range_ns);
                if (dt < 0)
                {
                    // We're only interested in the short time-differences, so we
                    // want to move the upper part of the coarse counter range close
                    // to the lower range, i.e. we cut the middle of the range and
                    // glue zero and the largest values together.
                    dt_mod -= fC_range_ns;
                }

                if (std::abs(dt_mod) < fC_bar_coincidence_ns * 10.)
                {
                    int iPlane = topc->GetDetectorId(); // 1..n
                    int iBar = topc->GetBarId();        // 1..n
                    // Histograms to display Y position
                    // fh2_tofd_ypos_cal[iPlane - 1]->Fill(iBar, dt_mod);
                    // fh2_tofd_timedif_cal[iPlane - 1]->Fill(iBar, topc_ns);
                    // fh2_tofd_timedif_cal[iPlane - 1]->Fill(-1 * iBar, botc_ns);

                    if (topc->GetTimeLeading_ns() > 0 && header->GetTStartSimple() > 0)
                    {
                        auto tof_without_trig_top =
                            fTimeStitch->GetTime(topc->GetTimeLeading_ns() - header->GetTStartSimple());
                        auto tof_without_trig_bot =
                            fTimeStitch->GetTime(botc->GetTimeLeading_ns() - header->GetTStartSimple());
                        auto mean_tof_trig = (tof_without_trig_top + tof_without_trig_bot) / 2.;
                        if (iPlane == 1)
                        {
                            fTof_without_trig[iBar - 1] = mean_tof_trig + fTofcor[iBar - 1];
                            // fh2_tofd_time_los_cal[topc->GetDetectorId() - 1]->Fill(topc->GetBarId(),
                            //                                                       fTof_without_trig[iBar - 1]);
                        }
                        // else
                        //   fh2_tofd_time_los_cal[topc->GetDetectorId() - 1]->Fill(
                        //     topc->GetBarId(), mean_tof_trig + fTofcor[44 * (topc->GetDetectorId() - 1) + iBar - 1]);
                    }
                }

                if (std::abs(dt_mod) < fC_bar_coincidence_ns)
                {
                    // Hit!
                    // std::cout << "Hit!\n";
                    Int_t iPlane = topc->GetDetectorId(); // 1..n
                    Int_t iBar = topc->GetBarId();        // 1..n
                    if (iPlane > fNofPlanes)              // this also errors for iDetector==0
                    {
                        R3BLOG(error,
                               "More detectors than expected! Det: " << iPlane << " allowed are 1.." << fNofPlanes);
                        continue;
                    }
                    if (iBar > fPaddlesPerPlane) // same here
                    {
                        R3BLOG(error,
                               "More bars then expected! Det: " << iBar << " allowed are 1.." << fPaddlesPerPlane);
                        continue;
                    }

                    auto topc_tot = fTimeStitch->GetTime(topc->GetTimeTrailing_ns() - topc->GetTimeLeading_ns());
                    auto botc_tot = fTimeStitch->GetTime(botc->GetTimeTrailing_ns() - botc->GetTimeLeading_ns());

                    // fh_tofd_TotPm_coinc[iPlane - 1]->Fill(-iBar - 1, botc_tot);
                    // fh_tofd_TotPm_coinc[iPlane - 1]->Fill(iBar, topc_tot);

                    // std::cout<<"ToT: "<<top_tot << " "<<bot_tot<<"\n";

                    if (iPlane == 3 || iPlane == 4)
                    {
                        for (const auto& data : calDataNl)
                        {
                            const auto Nlbar = data->GetBarId();
                            fh2_tofdbar_vs_nlbar[iPlane - 3]->Fill(Nlbar, iBar);
                        }
                    }

                    // register multi hits
                    Int_t imlt = vmultihits[iPlane - 1][iBar - 1];
                    time_bar[iPlane - 1][iBar - 1][imlt] = (topc_ns + botc_ns) / 2.;
                    vmultihits[iPlane - 1][iBar - 1] += 1;

                    ++topc_i;
                    ++botc_i;
                }
                else if (dt < 0 && dt > -fC_range_ns / 2)
                {
                    ++topc_i;
                }
                else
                {
                    ++botc_i;
                }
            }
        }

        for (Int_t ipl = 0; ipl < fNofPlanes; ipl++)
        {
            for (Int_t ibr = 1; ibr < fPaddlesPerPlane + 1; ibr++)
            {
                if (ipl == 1 || ipl == 3)
                {
                    for (Int_t imult1 = 0; imult1 < vmultihits[ipl][ibr - 1]; imult1++)
                    {
                        for (Int_t imult2 = 0; imult2 < vmultihits[ipl - 1][ibr - 1]; imult2++)
                        {
                            Double_t tof_plane = 0. / 0.;
                            tof_plane = fTimeStitch->GetTime(time_bar[ipl][ibr - 1][imult1] -
                                                             time_bar[ipl - 1][ibr - 1][imult2]);
                            // fh_tofd_dt[ipl - 1]->Fill(ibr, tof_plane);
                        }
                    }
                }
            }
        }

    } // endi if fCalItems

    if (fHitItems)
    {
        Int_t nHits = fHitItems->GetEntriesFast();
        if (nHits > fMaxmul)
            return;

        Double_t x[fNofPlanes][fMaxmul], y[fNofPlanes][fMaxmul], t[fNofPlanes][fMaxmul], q[fNofPlanes][fMaxmul],
            bar[fNofPlanes][fMaxmul];
        for (Int_t i = 0; i < fNofPlanes; i++)
        {
            for (Int_t k = 0; k < fMaxmul; k++)
            {
                x[i][k] = -1000.;
                y[i][k] = -1000.;
                q[i][k] = -1000.;
                t[i][k] = 0. / 0.;
                bar[i][k] = 0;
            }
        }

        Int_t nMulti[fNofPlanes], iCounts[fNofPlanes];
        for (Int_t i = 0; i < fNofPlanes; i++)
        {
            nMulti[i] = 0;
            iCounts[i] = 0;
        }

        double charges[4] = { 0 };
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            auto hitTofd = dynamic_cast<R3BTofdHitData*>(fHitItems->At(ihit));
            if (IS_NAN(hitTofd->GetTime()))
                continue;
            Int_t iPlane = hitTofd->GetDetId();
            Double_t randx = (std::rand() / (float)RAND_MAX) - 0.5;
            Int_t ictemp = iCounts[iPlane - 1];
            x[iPlane - 1][ictemp] = hitTofd->GetX() + 2.7 * randx;
            y[iPlane - 1][ictemp] = hitTofd->GetY();
            t[iPlane - 1][ictemp] = hitTofd->GetTime();
            q[iPlane - 1][ictemp] = hitTofd->GetEloss();
            bar[iPlane - 1][ictemp] = hitTofd->GetBarId();
            /*fh_tofd_Tot_hit[iPlane - 1]->Fill(bar[iPlane - 1][ictemp], q[iPlane - 1][ictemp]);
            fh_tofd_time_hit[iPlane - 1]->Fill(bar[iPlane - 1][ictemp], t[iPlane - 1][ictemp]);
            fh_tofd_bars[iPlane - 1]->Fill(hitTofd->GetBarId());
            fh_tofd_time_los_h2[iPlane - 1]->Fill(hitTofd->GetBarId(), hitTofd->GetTof());
            fh_tofd_time_los[hitTofd->GetBarId() - 1][iPlane - 1]->Fill(hitTofd->GetTof());*/

            if (hitTofd->GetEloss() > charges[iPlane - 1])
                charges[iPlane - 1] = hitTofd->GetEloss();

            if (iPlane == 3)
            {
                for (const auto& hit : hitsNl)
                {
                    const auto Nlbar = hit->GetPaddle();

                    if (!std::isnan(header->GetTStart()))
                    {
                        if (std::isnan(hit->GetT()))
                            continue;

                        const Double_t tcorr = hit->GetT() - (hit->GetPosition().Mag() - fDistanceToTarget) / clight;
                        fh2_TofvsNlBar->Fill(Nlbar, hitTofd->GetTof() - tcorr);

                        const int plane = static_cast<const int>(std::floor((Nlbar - 1) / 50)); // ig -1
                        auto xnl = hit->GetPosition().X() + (plane % 2) * 5. * randx;
                        fh2_XTofdvsXNl->Fill(xnl, x[iPlane - 1][ictemp]);
                        auto ynl = hit->GetPosition().Y() + ((plane + 1) % 2) * 5. * randx;
                        fh2_YTofdvsYNl->Fill(ynl, y[iPlane - 1][ictemp]);
                    }
                }

                iCounts[iPlane - 1] += 1;
                nMulti[iPlane - 1] += 1;
            }
        }
    }

    fNEvents += 1;
}

void R3BAsyTofDvsNeuLandOnlineSpectra::FinishEvent()
{
    R3BLOG(debug1, "Cleaning data structures");
    if (fMappedItems)
    {
        fMappedItems->Clear();
    }
    if (fCalItems)
    {
        fCalItems->Clear();
    }
    if (fHitItems)
    {
        fHitItems->Clear();
    }
}

void R3BAsyTofDvsNeuLandOnlineSpectra::FinishTask()
{
    if (fCalItems)
    {
        for (const auto& hist : fh2_tofdbar_vs_nlbar)
        {
            hist->Write();
        }
    }
    if (fHitItems)
    {
        fh2_TofvsNlBar->Write();
        fh2_XTofdvsXNl->Write();
        fh2_YTofdvsYNl->Write();
        // fh2_tofd_TofvsE->Write();
        // fh2_nl_TofvsE_with_tofd->Write();
        // fh2_nl_TofvsE_without_tofd->Write();
    }
}

ClassImp(R3BAsyTofDvsNeuLandOnlineSpectra)
