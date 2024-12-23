// --------------------------------------------------------------
// -----              R3BAsyKrabMappingPar source file         -----
// -----  Created 18/04/24 by P. Russotto && E. De Filippo  -----
// --------------------------------------------------------------

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

#include "R3BAsyKrabMappingPar.h"

#include <iostream>

#include "FairLogger.h"
#include "FairParamList.h"
#include "TMath.h"
#include "TString.h"

// ---- Standard Constructor ---------------------------------------------------
R3BAsyKrabMappingPar::R3BAsyKrabMappingPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fNumSectors(736)
{
    fxtboxring = new TArrayI(fNumSectors);
    fxtboxch = new TArrayI(fNumSectors);
    fxtbox = new TArrayI(fNumSectors);
    fxtboxringch = new TArrayI(fNumSectors);
    fxtboxang = new TArrayF(fNumSectors);
    fxtboxboard = new TArrayI(fNumSectors);
    fxtboxinp = new TArrayI(fNumSectors);
    fxtboxfpga = new TArrayI(fNumSectors);
    fxtboxfpgach = new TArrayI(fNumSectors);
    fxtboxcrock = new TArrayI(fNumSectors);
    fxtboxcrockch = new TArrayI(fNumSectors);
}

// ----  Destructor ------------------------------------------------------------
R3BAsyKrabMappingPar::~R3BAsyKrabMappingPar()
{
    if (fxtboxring)
        delete fxtboxring;
    if (fxtboxch)
        delete fxtboxch;
    if (fxtbox)
        delete fxtbox;
    if (fxtboxringch)
        delete fxtboxringch;
    if (fxtboxang)
        delete fxtboxang;
    if (fxtboxboard)
        delete fxtboxboard;
    if (fxtboxinp)
        delete fxtboxinp;
    if (fxtboxfpga)
        delete fxtboxfpga;
    if (fxtboxfpgach)
        delete fxtboxfpgach;
    if (fxtboxcrock)
        delete fxtboxcrock;
    if (fxtboxcrockch)
        delete fxtboxcrockch;
}

// ----  Method clear ----------------------------------------------------------
void R3BAsyKrabMappingPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BAsyKrabMappingPar::putParams(FairParamList* list)
{
    LOG(info) << "R3BAsyKrabMappingPar::putParams() called";
    if (!list)
    {
        return;
    }
    fxtboxring->Set(fNumSectors);
    list->add("krabBoxRingPar", *fxtboxring);
    fxtboxch->Set(fNumSectors);
    list->add("krabBoxChPar", *fxtboxch);
    fxtbox->Set(fNumSectors);
    list->add("krabBoxPar", *fxtbox);
    fxtboxringch->Set(fNumSectors);
    list->add("krabBoxRingChPar", *fxtboxringch);
    fxtboxang->Set(fNumSectors);
    list->add("krabBoxAngPar", *fxtboxang);
    fxtboxboard->Set(fNumSectors);
    list->add("KrabBoxBoardPar", *fxtboxboard);
    fxtboxinp->Set(fNumSectors);
    list->add("krabBoxInpPar", *fxtboxinp);
    fxtboxfpga->Set(fNumSectors);
    list->add("krabBoxFpgaPar", *fxtboxfpga);
    fxtboxfpgach->Set(fNumSectors);
    list->add("krabBoxFpgachPar", *fxtboxfpgach);
    fxtboxcrock->Set(fNumSectors);
    list->add("krabBoxCrockPar", *fxtboxcrock);
    fxtboxcrockch->Set(fNumSectors);
    list->add("krabBoxCrockChPar", *fxtboxcrockch);

    list->add("krabSectorNumberPar", fNumSectors);
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BAsyKrabMappingPar::getParams(FairParamList* list)
{
    LOG(info) << "R3BAsyKrabMappingPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }
    if (!list->fill("krabSectorNumberPar", &fNumSectors))
    {
        return kFALSE;
    }

    fxtboxring->Set(fNumSectors);
    if (!(list->fill("krabBoxRing", fxtboxring)))
    {
        LOG(info) << "---Could not initialize krabBoxRingPar";
        return kFALSE;
    }
    fxtboxch->Set(fNumSectors);
    if (!(list->fill("krabBoxChPar", fxtboxch)))
    {
        LOG(info) << "---Could not initialize krabBoxChPar";
        return kFALSE;
    }
    fxtbox->Set(fNumSectors);
    if (!(list->fill("krabBoxPar", fxtbox)))
    {
        LOG(info) << "---Could not initialize krabBoxPar";
        return kFALSE;
    }
    fxtboxringch->Set(fNumSectors);
    if (!(list->fill("krabBoxRingChPar", fxtboxringch)))
    {
        LOG(info) << "---Could not initialize krabBoxRingChPar";
        return kFALSE;
    }
    fxtboxang->Set(fNumSectors);
    if (!(list->fill("krabBoxAngPar", fxtboxang)))
    {
        LOG(info) << "---Could not initialize krabBoxAngPar";
        return kFALSE;
    }
    fxtboxboard->Set(fNumSectors);
    if (!(list->fill("krabBoxBoardPar", fxtboxboard)))
    {
        LOG(info) << "---Could not initialize krabBoxBoardPar";
        return kFALSE;
    }
    fxtboxinp->Set(fNumSectors);
    if (!(list->fill("krabBoxInpPar", fxtboxinp)))
    {
        LOG(info) << "---Could not initialize krabBoardInpPar";
        return kFALSE;
    }
    fxtboxfpga->Set(fNumSectors);
    if (!(list->fill("krabBoxFpgaPar", fxtboxfpga)))
    {
        LOG(info) << "---Could not initialize krabBoxFpgaPar";
        return kFALSE;
    }
    fxtboxfpgach->Set(fNumSectors);
    if (!(list->fill("krabBoxFpgaChPar", fxtboxfpgach)))
    {
        LOG(info) << "---Could not initialize krabBoxFpgaChPar";
        return kFALSE;
    }
    fxtboxcrock->Set(fNumSectors);
    if (!(list->fill("krabBoxCrockPar", fxtboxcrock)))
    {
        LOG(info) << "---Could not initialize krabBoxCrockPar";
        return kFALSE;
    }
    fxtboxcrockch->Set(fNumSectors);
    if (!(list->fill("krabBoxCrockChPar", fxtboxcrockch)))
    {
        LOG(info) << "---Could not initialize krabBoxCrockChPar";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method print ----------------------------------------------------------
void R3BAsyKrabMappingPar::print() { printParams(); }

// ----  Method printCrystalInfo -----------------------------------------------
void R3BAsyKrabMappingPar::printMapSectorInfo(const UInt_t sectorID)
{
    if (sectorID < 1)
    {
        LOG(error) << "sector_id must be given in 1-base";
        return;
    }
    else if (sectorID > fNumSectors)
    {
        LOG(error) << "sector_id does not exist, sector_id<=" << fNumSectors;
        return;
    }
    auto index = sectorID - 1;
    LOG(info) << "sector_id " << sectorID << " , "
              << "boxring " << fxtboxring->GetAt(index) << " , "
              << "boxch " << fxtboxch->GetAt(index) << " , "
              << "box " << fxtbox->GetAt(index) << " , "
              << "boxringch " << fxtboxringch->GetAt(index) << " , "
              << "boxang " << fxtboxang->GetAt(index) << " , "
              << "boxboard " << fxtboxboard->GetAt(index) << " , "
              << "boxinp " << fxtboxinp->GetAt(index) << " , "
              << "boxfpga " << fxtboxfpga->GetAt(index) << " , "
              << "boxfpgach " << fxtboxfpgach->GetAt(index) << " , "
              << "boxcrock " << fxtboxcrock->GetAt(index) << " , "
              << "boxcrock " << fxtboxcrockch->GetAt(index);
}

// ----  Method printParams ----------------------------------------------------
void R3BAsyKrabMappingPar::printParams()
{
    LOG(info) << "R3BAsyKrabMappingPar: Krab Mapping Parameters:";

    LOG(info) << "sector_id"
              << " "
              << "boxring"
              << " "
              << "boxch"
              << " "
              << "box"
              << " "
              << "boxringch"
              << " "
              << "boxang"
              << " "
              << "boxboard"
              << " "
              << "boxinp"
              << " "
              << "boxfpga"
              << " "
              << "boxfpgach"
              << " "
              << "boxcrock"
              << " "
              << "boxcrockch";
    for (Int_t i = 0; i < fNumSectors; i++)
    {
        LOG(info) << i + 1 << " " << fxtboxring->GetAt(i) << " " << fxtboxch->GetAt(i) << " " << fxtbox->GetAt(i) << " "
                  << fxtboxringch->GetAt(i) << " " << fxtboxang->GetAt(i) << " " << fxtboxboard->GetAt(i) << " "
                  << fxtboxinp->GetAt(i) << " " << fxtboxfpga->GetAt(i) << " " << fxtboxfpgach->GetAt(i) << " "
                  << fxtboxcrock->GetAt(i) << " " << fxtboxcrockch->GetAt(i);
    }
}

ClassImp(R3BAsyKrabMappingPar);
