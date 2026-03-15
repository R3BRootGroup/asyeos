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

#include "R3BAsyChimeraMatch.h"

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

R3BAsyChimeraMatch::R3BAsyChimeraMatch(const char* inFileName, const char* inFileName2)
    : FairTask("AsyChimeraMatch", 1)
    , fMappedItemsChimera(NULL)
    , fChimeraMatchedData(0)
    , fNEvents(0)
    , finFileName(inFileName)
    , finFileName2(inFileName2)

{
}

R3BAsyChimeraMatch::~R3BAsyChimeraMatch()
{
    LOG(info) << "R3BAsyChimeraMatch::Delete instance";
    if (fChimeraMatchedData)
        delete fChimeraMatchedData;
}

InitStatus R3BAsyChimeraMatch::Init()
{
    LOG(info) << "R3BAsyChimeraMatch::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraMatch::Init FairRootManager not found";

    header = dynamic_cast<R3BEventHeader*>(mgr->GetObject("EventHeader."));
    R3BLOG_IF(error, header == nullptr, "EventHeader. not found");

    if (verbose)
        LOG(info) << "R3BAsyChimeraMatch::Init line 72";
    // Register output array in tree
    fChimeraMatchedData = new TClonesArray("R3BAsyChimeraMatchedData");
    FairRootManager::Instance()->Register(
        "AsyChimeraMatchedData", "AsyChimera Matched data", fChimeraMatchedData, !fOnline);

    LOG(info) << "R3BAsyChimeraMatch::Init DONE";

    FairRunOnline* run = FairRunOnline::Instance();

    // --- ------------------------------------- --- //
    // --- get access to mapped data of the TofW --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraMatch::Init line 80";

    fMappedItemsChimera = (TClonesArray*)mgr->GetObject("AsyChimeraMappedData");
    if (!fMappedItemsChimera)
    {
        //        return kFATAL;
    }
    if (verbose)
        LOG(info) << "R3BAsyChimeraMatch::Init line 87";

    Char_t arrow[5] = "-->";
    Char_t offword[8] = "OFFSET";
    Char_t gainword[8] = "GAIN";
    Char_t name[11] = "RXYYYYXX-X";

    Int_t n;
    float a, b, c, d;

    std::string dummy;

    std::ifstream fpars(finFileName, std::ifstream::in);

    std::cout << finFileName << std::endl;

    if (!fpars)
    {
        printf("R3BAsyChimeraMatch::Init cannot open input file: \n");
        exit(1);
    }

    getline(fpars, dummy);
    std::cout << dummy << std::endl;
    for (int ih = 0; ih < (ndim - 80); ih++)
    {
        fpars >> n >> name >> arrow >> offword >> b >> gainword >> a;
        gain_fast[n] = a;
        offset_fast[n] = b;

        if (a == 0 && b == 0)
        {
            gain_fast[n] = 8.;
            offset_fast[n] = 68.;
        }
        std::cout << n << " " << name << " " << arrow << " " << offword << " " << b << " " << gainword << " " << a
                  << std::endl;
    }
    for (int ih = 0; ih < (ndim - 80); ih++)
    {
        fpars >> n >> name >> arrow >> offword >> b >> gainword >> a;
        gain_slow[n] = a;
        offset_slow[n] = b;
        if (a == 0 && b == 0)
        {
            gain_slow[n] = 8.;
            offset_slow[n] = 68.;
        }
        std::cout << n << " " << name << " " << arrow << " " << offword << " " << b << " " << gainword << " " << a
                  << std::endl;
    }

    std::ifstream fsat(finFileName2, std::ifstream::in);

    std::cout << finFileName2 << std::endl;

    if (!fsat)
    {
        printf("R3BAsyChimeraMatch::Init cannot open input file: \n");
        exit(1);
    }

    getline(fsat, dummy);
    std::cout << dummy << std::endl;
    for (int ih = 0; ih < (ndim - 80); ih++)
    {
        fsat >> n >> a >> b;
        if (a == 0)
            a = 3530;
        sat_slow[n] = a;
        slow_corr_ntel[n] = b;
        std::cout << n << " sat_ch = " << a << " slow_corr = " << b << std::endl;
    }

    LOG(info) << "R3BAsyChimeraMatch::Init DONE";
    //    getchar();

    return kSUCCESS;
}

void R3BAsyChimeraMatch::Reset_Histo() { LOG(info) << "R3BAsyChimeraMatch::Reset_Histo"; }

void R3BAsyChimeraMatch::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraMatch::Exec FairRootManager not found";

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
        if ((header) && (tpatvalue == 0))
            return;
    }

    /*
        int aa=0;
        int bb=0;

        aa=itpat & 0x1;
        bb=itpat & 0x2;


    //    std::cout << "trig= " << trig << " " << tpatvalue << " " << aa << " " << bb << std::endl;

        if( aa && !bb){
         std::bitset<8> x(itpat);
         std::cout << "itpat=" << itpat << " x= " << x  <<std::endl;
         std::cout << "trig= " << trig << " " << tpatvalue << " " << aa << " " << bb << std::endl;
         getchar();
        }
        if(!aa &&  bb){
         std::bitset<8> x(itpat);
         std::cout << "itpat=" << itpat << " x= " << x  <<std::endl;
         std::cout << "trig= " << trig << " " << tpatvalue << " " << aa << " " << bb << std::endl;
         getchar();
        }
    */
    if (trig == 1 && tpatvalue)
    {

        //     std::cout << "tpatvalue= " << tpatvalue << std::endl;
        //     if( tpatvalue != 1) getchar();
        Int_t nHits;

        UShort_t iNumTel, iFastHG, iFastLG, iSlowHG, iSlowLG, iTimeCsI, iSilHG, iSilLG, iTimeSil, iPatt;

        Float_t fast, slow;

        if (fMappedItemsChimera && fMappedItemsChimera->GetEntriesFast())
        {
            // --- --------------------- --- //
            // --- loop over mapped data --- //
            // --- --------------------- --- //
            nHits = fMappedItemsChimera->GetEntriesFast();

            //	std::cout <<  nHits << std::endl;
            int time_trig = 0;
            int time1 = 0;
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {
                fast = -1, slow = -1;
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

                if (iFastHG > 0)
                {
                    fast = iFastHG / gain_fast[iNumTel] + offset_fast[iNumTel];
                }
                else if (iFastLG > 0)
                {
                    fast = 1.0 * iFastLG;
                }
                if (iSlowHG > 0)
                {
                    slow = iSlowHG / gain_slow[iNumTel] + offset_slow[iNumTel];
                }
                else if (iSlowLG > 0)
                {
                    slow = 1.0 * iSlowLG;
                }
                //          std::cout << fast << " " << slow << " " << iNumTel << std::endl;

                if (slow < sat_slow[iNumTel])
                {
                    slow = slow_corr * slow * slow_corr_ntel[iNumTel];
                }

                if ((slow > 0 && fast > 0) && iNumTel >= NTelMin && iNumTel <= NTelMax)
                {

                    AddMatchedData(iNumTel, fast, slow, iTimeCsI);
                    //	     std::cout <<  "added" << std::endl;
                }
            }
        }

        fNEvents += 1;
    }
}

void R3BAsyChimeraMatch::FinishEvent()
{
    if (fMappedItemsChimera)
    {
        fMappedItemsChimera->Clear();
    }
    if (fChimeraMatchedData)
    {
        fChimeraMatchedData->Clear();
    }
}

void R3BAsyChimeraMatch::FinishTask()
{
    if (fMappedItemsChimera)
    {
    }
}

// -----   Private method AddHitData -------------------------------------------
R3BAsyChimeraMatchedData* R3BAsyChimeraMatch::AddMatchedData(UInt_t numtel, Float_t fast, Float_t slow, UInt_t timeCsI)
{
    TClonesArray& clref = *fChimeraMatchedData;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BAsyChimeraMatchedData(numtel, fast, slow, timeCsI);
}

ClassImp(R3BAsyChimeraMatch)
