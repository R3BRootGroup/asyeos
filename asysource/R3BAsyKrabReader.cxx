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

#include "R3BAsyKrabReader.h"

#include <FairLogger.h>
#include <FairRootManager.h>
#include <TClonesArray.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "R3BAsyKrabMappedData.h"
#include "R3BWRData.h"
#include "TString.h"

// #include <ext_data_struct_info.hh>

#include "R3BLogger.h"

#define verbose 0

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_krab.h"
}

R3BAsyKrabReader::R3BAsyKrabReader(EXT_STR_h101_ASYKRAB* data, size_t offset, const char* inFileName)
    : R3BReader("R3BAsyKrabReader")
    , fData(data)
    , fOffset(offset)
    , fArray(new TClonesArray("R3BAsyKrabMappedData"))
    , fArrayTrigger(new TClonesArray("R3BAsyKrabMappedData"))
    , fArrayWR(new TClonesArray("R3BWRData"))
    , finFileName(inFileName)
{
}

R3BAsyKrabReader::~R3BAsyKrabReader()
{
    if (fArray)
    {
        delete fArray;
    }
    if (fArrayTrigger)
    {
        delete fArrayTrigger;
    }
    if (fArrayWR)
    {
        delete fArrayWR;
    }
}

Bool_t R3BAsyKrabReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    R3BLOG(info, "");

    EXT_STR_h101_ASYKRAB_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_ASYKRAB, 0);
    if (!ok)
    {
        R3BLOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // Register output array in tree
    FairRootManager::Instance()->Register("AsyKrabMappedData", "AsyKrab mapped data", fArray, !fOnline);
    fArray->Clear();
    if (!fSkiptriggertimes)
    {
        FairRootManager::Instance()->Register(
            "AsyKrabTriggerMapped", "AsyKrab trigger mapped data", fArrayTrigger, DoNotWrite);
    }
    else
    {
        fArrayTrigger = nullptr;
    }

    FairRootManager::Instance()->Register("AsyKrabWRData", "WRKrab", fArrayWR, !fOnline);

    Reset();
    // initial clear (set number of hits to 0)
    EXT_STR_h101_ASYKRAB_onion* data = (EXT_STR_h101_ASYKRAB_onion*)fData;

    int CH_KRAB;
    int CH_RING;
    float ANGLE;
    int RING;
    int CITIROCK;
    int CH_CROCK;
    int TB_BOARD;
    int INPUT;
    int FPGA;
    int CH_FPGA;
    int CH_TBOX; // channel from V2495 BOARD3-INPUT1 not connected
                 //+ BOARDS6-5 connected to top input (mezzanine) of V2495
    int CB_BOARD;
    int HV_No;

    std::string dummy;

    std::ifstream fpars(finFileName, std::ifstream::in);

    //  std::ifstream
    //  fpars("/home/pcget/R3BRoot/asyeos/asysource/TBOX-KRAB.map",std::ifstream::in);
    if (!fpars)
    {
        printf("cannot open file: TBOX-KRAB.map\n");
        exit(1);
    }
    getline(fpars, dummy);
    getline(fpars, dummy);
    for (int ih = 0; ih < 26 * 5 * 6; ih++)
    {
        fpars >> CH_KRAB >> CH_RING >> ANGLE >> RING >> CITIROCK >> CH_CROCK >> TB_BOARD >> INPUT >> FPGA >> CH_FPGA >>
            CH_TBOX >> CB_BOARD >> HV_No;

        xtbox[CH_TBOX] = CH_KRAB;
        xtboxch[CH_TBOX] = CH_KRAB;
        xtboxring[CH_TBOX] = RING;
        xtboxringch[CH_TBOX] = CH_RING;
        xtboxang[CH_TBOX] = ANGLE;
        xtboxboard[CH_TBOX] = TB_BOARD;
        xtboxinp[CH_TBOX] = INPUT;
        xtboxfpga[CH_TBOX] = FPGA;
        xtboxfpgach[CH_TBOX] = CH_FPGA;
        xtboxcrock[CH_TBOX] = CITIROCK;
        xtboxcrockch[CH_TBOX] = CH_CROCK;
        xring[TB_BOARD - 1][FPGA - 1][CH_FPGA] = RING;
        xringch[TB_BOARD - 1][FPGA - 1][CH_FPGA] = CH_RING;
        xringang[TB_BOARD - 1][FPGA - 1][CH_FPGA] = ANGLE;
    }
    mynev = 0;
    return kTRUE;
}

Bool_t R3BAsyKrabReader::R3BRead()
{
    Reset();
    R3BLOG(debug1, "Event data.");
    EXT_STR_h101_ASYKRAB_onion* data = (EXT_STR_h101_ASYKRAB_onion*)fData;

    uint32_t fTIMESTAMP_KRAB_ID = 555;
    /*
        auto const& fTIMESTAMP_KRAB_WR_T1 = data->TIMESTAMP_KRAB_WR_T[0];
        auto const& fTIMESTAMP_KRAB_WR_T2 = data->TIMESTAMP_KRAB_WR_T[1];
        auto const& fTIMESTAMP_KRAB_WR_T3 = data->TIMESTAMP_KRAB_WR_T[2];
        auto const& fTIMESTAMP_KRAB_WR_T4 = data->TIMESTAMP_KRAB_WR_T[3];

        if (verbose > 1)
        {
            std::cout << " *** " << fTIMESTAMP_KRAB_ID << std::endl;
            std::cout << "evt=" << mynev << "   ###  TS= " << std::hex << fTIMESTAMP_KRAB_WR_T1 << " "
                      << fTIMESTAMP_KRAB_WR_T2 << " " << fTIMESTAMP_KRAB_WR_T3 << " " << fTIMESTAMP_KRAB_WR_T4 << " "
                      << std::dec << std::endl;
        }
    */
    uint64_t timestamp = 1;
    /*
        timestamp = ((uint64_t)fTIMESTAMP_KRAB_WR_T4 << 48) | ((uint64_t)fTIMESTAMP_KRAB_WR_T3 << 32) |
                    ((uint64_t)fTIMESTAMP_KRAB_WR_T2 << 16) | (uint64_t)fTIMESTAMP_KRAB_WR_T1;
    */
    new ((*fArrayWR)[fArrayWR->GetEntriesFast()]) R3BWRData(timestamp, fTIMESTAMP_KRAB_ID);

    if (timestamp == 0)
    {
        new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyKrabMappedData(0, 0, 0, 0, 0);
    }
    else
    {
        for (int i = 0; i < 32; i++)
        {
            auto const& test = data->KRAB_DATAv[i];
            if (verbose > 1)
                std::cout << std::hex << test << std::dec << " ";
            if (verbose > 1 && i == 31)
                std::cout << std::endl;
        }
        if (verbose > 1)
        {
            std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
            std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
            getchar();
        }
        float mult = 0;
        int imult = 0;
        int itest = 0;
        int multr[6] = { 0, 0, 0, 0, 0, 0 };
        int icorr[780] = { 0 };
        for (int ii = 0; ii < 780; ii++)
            icorr[ii] = 0;
        int imultk = 0;
        int icorrk[780] = { 0 };
        for (int ii = 0; ii < 780; ii++)
            icorrk[ii] = 0;

        const int HSIZE = 0; // header+timestamps size

        for (int ichtb = 0; ichtb < 30; ichtb++)
        { // TBox FPGAs
            uint32_t pattern = (uint32_t)data->KRAB_DATAv[ichtb + HSIZE];
            if (pattern > 0)
            {
                for (int bit = 0; bit < 26; bit++)
                {
                    if (pattern & (1 << bit))
                    {
                        int detid = ichtb * 26 + bit;
                        icorr[imult] = detid;
                        imult++;
                        if (xtbox[detid] > -1)
                        {
                            icorrk[imultk] = xtbox[detid];
                            imultk++;
                            float ang = xtboxang[detid];
                            int rng = xtboxring[detid];
                            int chrng = xtboxringch[detid];
                            float r = 18. - (4 - rng);
                            float qx = cos(ang * 0.0174532925199);
                            float qy = sin(ang * 0.0174532925199);
                            mult += 1.;
                            multr[rng]++;
                            multr[5]++;
                            if (rng == 1 && chrng == 25)
                                itest = 1;
                            new ((*fArray)[fArray->GetEntriesFast()]) R3BAsyKrabMappedData(rng, chrng, ang, qx, qy);
                        }
                    }
                }
            }
        }
    }
    mynev++;

    //  for(int i=0;i<32;i++){
    //   data->KRAB_DATAv[i]=0;
    //  }
    return kTRUE;
}

void R3BAsyKrabReader::Reset()
{
    // Reset the output array
    fArray->Clear();
    if (fArrayTrigger)
        fArrayTrigger->Clear();
    fArrayWR->Clear();
}

ClassImp(R3BAsyKrabReader)
