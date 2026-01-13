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

#include "R3BAsyChimeraPhys.h"

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
#define KRABMaxRing 2


const Float_t thetamin[35] = { 1.,    1.80,  2.60,  3.60,  4.62,  5.82,  6.97, 8.47,  9.99, 11.49, 13.55, 15.12,
                               16.00, 18.00, 20.00, 22.00, 24.00, 27.00, 30.,  38.,  46.,   54.,   62.,   70.,
                               78.,   86.,   94.,   102.,  110.,  118.,  126., 134., 142.,  150.,  163. };
const Float_t thetamax[35] = { 1.80,  2.60,  3.60,  4.60,  5.82,  7.03, 8.47,  9.96, 11.49, 12.99, 15.12, 16.68,
                               18.00, 20.00, 22.00, 24.00, 27.00, 30.,  38.,  46.,   54.,   62.,   70.,   78.,
                               86.,   94.,   102.,  110.,  118.,  126., 134., 142.,  150.,  163.,  176. };
const Int_t telmin[35] = { 0,   16,  32,  56,  80,   112,  144,  184,  224,  264,  304, 352,
                           400, 448, 496, 544, 592,  640,  688,  720,  752,  784,  816, 848,
                           880, 912, 944, 976, 1008, 1040, 1072, 1104, 1136, 1168, 1184 };
const Int_t telmax[35] = { 15,  31,  55,  79,   111,  143,  183,  223,  263,  303,  351, 399,
                           447, 495, 543, 591,  639,  687,  719,  751,  783,  815,  847, 879,
                           911, 943, 975, 1007, 1039, 1071, 1103, 1135, 1167, 1183, 1191 };
const Float_t delta_phi[35] = { 22.5,  22.5,  15.,   15.,   11.25, 11.25, 9.,    9.,    9.,    9.,    7.5,   7.5,
                                7.5,   7.5,   7.5,   7.5,   7.5,   7.5,   11.25, 11.25, 11.25, 11.25, 11.25, 11.25,
                                11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 11.25, 22.5,  45.0 };

const Float_t thetaminK[5] = {127.79, 58.41, 43.26, 33.41,  26.73};
const Float_t thetamaxK[5] = {167.63, 78.98, 58.41, 43.26,  33.41};

TH2F *h2_ylab_bt = new TH2F("h2_ylab_bt","ylab_bt",200, -0.5, 1.5, 70, 0 , 0.7);
TH2F *h2_ylab_bt2 = new TH2F("h2_ylab_bt2","ylab_bt2",200, -0.5, 1.5, 70, 0 , 0.7);

TH1F *h1_RP = new TH1F("h1_RP","RP",92,-184,184);
TH1F *h1_diffRP = new TH1F("h1_diffRP","diffRP",92,-2,182);
TH1F *h1_mult_RP = new TH1F("h1_mult_RP","mult_RP",100,-0.5,99.5);

TH2F *h2_RP_CHI_KRAB = new TH2F("h2_RP_CHI_KRAB","RP_CHI_KRAB",92,-184,184,92,-184,184);
TH1F *h1_dRP_CHI_KRAB = new TH1F("h1_dRP_CHI_KRAB","dRP_CHI_KRAB",92,-2,182);



TH2F *h2_mulCHI_mulKRAB = new TH2F("h2_mulCHI_mulKRAB","mulCHI_mulKRAB", 30, -0.5, 59.5, 50, -0.5, 49.5);
TProfile *hp_mulCHI_mulKRAB = new TProfile("hp_mulCHI_mulKRAB","mulCHI_mulKRAB", 30, -0.5, 59.5, -0.5, 49.5);

TH2F *h2_ZBound_mulKRAB = new TH2F("h2_ZBound_mulKRAB","ZBound_mulKRAB", 30, -0.5, 59.5, 25, -0.5, 49.5);
TProfile *hp_ZBound_mulKRAB = new TProfile("hp_ZBound_mulKRAB","ZBound_mulKRAB", 30, -0.5, 59.5, -0.5, 49.5);

TH2F *h2_Zrat_mulKRAB = new TH2F("h2_Zrat_mulKRAB","Zrat_mulKRAB", 30, -0.5, 59.5, 50, 0, 1);
TProfile *hp_Zrat_mulKRAB = new TProfile("hp_Zrat_mulKRAB","Zrat_mulKRAB", 30, -0.5, 59.5, 0., 1);

TH2F *h2_Erat_mulKRAB = new TH2F("h2_Erat_mulKRAB","Erat_mulKRAB", 30, -0.5, 59.5, 50, 0, 1);
TProfile *hp_Erat_mulKRAB = new TProfile("hp_Erat_mulKRAB","Erat_mulKRAB", 30, -0.5, 59.5, 0., 1);


TH2F *h2_ZBound_mulCHI = new TH2F("h2_ZBound_mulCHI","ZBound_mulCHI", 20, -0.5, 39.5, 25, -0.5, 49.5);
TProfile *hp_ZBound_mulCHI = new TProfile("hp_ZBound_mulCHI","ZBound_mulCHI", 20, -0.5, 39.5, -0.5, 49.5);

TH2F *h2_Zrat_mulCHI = new TH2F("h2_Zrat_mulCHI","Zrat_mulCHI", 20, -0.5, 39.5, 50, 0, 1);
TProfile *hp_Zrat_mulCHI = new TProfile("hp_Zrat_mulCHI","Zrat_mulCHI", 20, -0.5, 39.5, 0., 1);

TH2F *h2_Erat_mulCHI = new TH2F("h2_Erat_mulCHI","Erat_mulCHI", 20, -0.5, 39.5, 50, 0, 1);
TProfile *hp_Erat_mulCHI = new TProfile("hp_Erat_mulCHI","Erat_mulCHI", 20, -0.5, 39.5, 0., 1);

TH2F *h2_ZBound_Zrat = new TH2F("h2_ZBound_Zrat","ZBound_Zrat", 50, 0., 1., 25, 0, 49.5);
TProfile *hp_ZBound_Zrat = new TProfile("hp_ZBound_Zrat","ZBound_Zrat", 50, 0., 1., 0., 49.5);

TH1F *h1_yield_Z1 = new TH1F("h1_yield_Z1","yield_Z1",320, 79.5, 399.5);
TH1F *h1_yield_Z2 = new TH1F("h1_yield_Z2","yield_Z2",320, 79.5, 399.5);
TH1F *h1_yield_Z3 = new TH1F("h1_yield_Z3","yield_Z3",320, 79.5, 399.5);

TH1F *h1_yield_Z4 = new TH1F("h1_yield_Z4","yield_Z4",320, 79.5, 399.5);
TH1F *h1_yield_Z5 = new TH1F("h1_yield_Z5","yield_Z5",320, 79.5, 399.5);

TH1F *h1_yield_Z1_bis = new TH1F("h1_yield_Z1_bis","yield_Z1_bis",320, 79.5, 399.5);
TH1F *h1_yield_Z2_bis = new TH1F("h1_yield_Z2_bis","yield_Z2_bis",320, 79.5, 399.5);
TH1F *h1_yield_Z3_bis = new TH1F("h1_yield_Z3_bis","yield_Z3_bis",320, 79.5, 399.5);

TH1F *h1_yield_Z4_bis = new TH1F("h1_yield_Z4_bis","yield_Z4_bis",320, 79.5, 399.5);
TH1F *h1_yield_Z5_bis = new TH1F("h1_yield_Z5_bis","yield_Z5_bis",320, 79.5, 399.5);

TH1F *h1_ntel_R3I = new TH1F("h1_ntel_R3I","ntel_R3I",32, 79.5,111.5);
TH1F *h1_ntel_R3E = new TH1F("h1_ntel_R3E","ntel_R3E",32,111.5,143.5);
TH1F *h1_ntel_R4I = new TH1F("h1_ntel_R4I","ntel_R4I",40,143.5,183.5);
TH1F *h1_ntel_R4E = new TH1F("h1_ntel_R4E","ntel_R4E",40,183.5,223.5);
TH1F *h1_ntel_R5I = new TH1F("h1_ntel_R5I","ntel_R5I",40,223.5,263.5);
TH1F *h1_ntel_R5E = new TH1F("h1_ntel_R5E","ntel_R5E",40,263.5,303.5);
TH1F *h1_ntel_R6I = new TH1F("h1_ntel_R6I","ntel_R6I",48,303.5,351.5);
TH1F *h1_ntel_R6E = new TH1F("h1_ntel_R6E","ntel_R6E",48,351.5,399.5);


R3BAsyChimeraPhys::R3BAsyChimeraPhys()
    : FairTask("AsyChimeraPhys", 1)
    , fChimeraIdData(NULL)
    , fMappedItemsKrab(NULL)
    , fChiKrabPhysData(0)
    , fNEvents(0)
{
}

R3BAsyChimeraPhys::R3BAsyChimeraPhys(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fChimeraIdData(NULL)
    , fMappedItemsKrab(NULL)
    , fChiKrabPhysData(0)
    , fNEvents(0)
{
}

R3BAsyChimeraPhys::~R3BAsyChimeraPhys()
{
    LOG(info) << "R3BAsyChimeraPhys::Delete instance";
    if (fChiKrabPhysData)
        delete fChiKrabPhysData;
}

InitStatus R3BAsyChimeraPhys::Init()
{
    LOG(info) << "R3BAsyChimeraPhys::Init ";
    getchar();
    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraPhys::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");
    header = dynamic_cast<R3BEventHeader*>(mgr->GetObject("EventHeader."));

    if (verbose)
        LOG(info) << "R3BAsyChimeraPhys::Init line 72";
    // Register output array in tree
    fChiKrabPhysData = new TClonesArray("R3BAsyChiKrabPhysData");
    FairRootManager::Instance()->Register("AsyChiKrabPhysData", "AsyChimeraKrab Phys data", fChiKrabPhysData, !fOnline);

    LOG(info) << "R3BAsyChimeraPhys::Init DOING";

    FairRunOnline* run = FairRunOnline::Instance();
    // for online server
    if(fOnline){ 
		run->GetHttpServer()->Register("", this);
        // Register command to reset histograms
        // for online server
        run->GetHttpServer()->RegisterCommand("Reset_Chimera_Phys", Form("/Objects/%s/->Reset_Histo()", GetName()));
    }
    // --- ------------------------------------- --- //
    // --- get access to Chimera Id data --- //
    // --- ------------------------------------- --- //
    if (verbose)
        LOG(info) << "R3BAsyChimeraPhys::Init line 80";

    fChimeraIdData = (TClonesArray*)mgr->GetObject("AsyChimeraIdData");
    if (!fChimeraIdData)
    {
        LOG(info) << "R3BAsyChimeraPhys:: fChimeraIdData not found!";
        getchar();
    }

    // --- ------------------------------------- --- //
    // --- get access to Krab mapped data --- //
    // --- ------------------------------------- --- //
    fMappedItemsKrab = (TClonesArray*)mgr->GetObject("AsyKrabMappedData");
    if (!fMappedItemsKrab)
    {
        LOG(info) << "R3BAsyChimeraPhys:: fMappedItemsKrab not found!";
        getchar();
    }

    rrn = new TRandom();
    rr2 = new TRandom();
    rr3 = new TRandom();
    
    if(this_energy==400){
	 ymid=0.448;
	 EAMax=700;
	 KRABww=0.325;
//	 KM_min = 11;
//	 KM_max = 29;
	 dy=0.08;
    }
    
    cc1 = new TCanvas("cc1","cc1", 1000,1000);
    cc1->Divide(1,2);
    cc1->cd(1);h2_ylab_bt->Draw("ZCol");
    cc1->cd(2);h2_ylab_bt2->Draw("ZCOL");
  
    c_RP = new TCanvas("c_RP","c_RP",1000,1000);
    c_RP->Divide(2,2);
    c_RP->cd(1);h1_RP->Draw();
    c_RP->cd(2);h1_mult_RP->Draw();
    c_RP->cd(3);h1_diffRP->Draw();

    c_RP2 = new TCanvas("c_RP2","c_RP2",1000,1000);
    c_RP2->Divide(2,2);
    c_RP2->cd(1);h2_RP_CHI_KRAB->Draw("ZCol");
    c_RP2->cd(2);h1_dRP_CHI_KRAB->Draw();h1_dRP_CHI_KRAB->SetMinimum(0);
 
    c_RP3 = new TCanvas("c_RP3","c_RP3",1000,1000);
    c_RP3->Divide(2,2);
    c_RP3->cd(1);h2_RP_CHI_KRAB->Draw("ZCol"); 
    c_RP3->cd(2);h1_dRP_CHI_KRAB->Draw();h1_dRP_CHI_KRAB->SetMinimum(0);
    c_RP3->cd(3);h1_RP->Draw();
    c_RP3->cd(4);h1_diffRP->Draw();
   
    c_b = new TCanvas("c_b","c_b",1000,1000);
    c_b->Divide(2,2);
    c_b->cd(1);h2_mulCHI_mulKRAB->Draw("ZCol");hp_mulCHI_mulKRAB->Draw("same"); 
    c_b->cd(2);h2_ZBound_mulKRAB->Draw("Zcol");hp_ZBound_mulKRAB->Draw("same");
    c_b->cd(3);h2_Zrat_mulKRAB->Draw("Zcol");hp_Zrat_mulKRAB->Draw("same");
    c_b->cd(4);h2_Erat_mulKRAB->Draw("Zcol");hp_Erat_mulKRAB->Draw("same");
   
    hp_mulCHI_mulKRAB->SetMarkerStyle(20);
    hp_ZBound_mulKRAB->SetMarkerStyle(20);
    hp_Zrat_mulKRAB->SetMarkerStyle(20);
    hp_Erat_mulKRAB->SetMarkerStyle(20);
 
    c_b2 = new TCanvas("c_b2","c_b2",1000,1000);
    c_b2->Divide(2,2);
    c_b2->cd(2);h2_ZBound_mulCHI->Draw("Zcol");hp_ZBound_mulCHI->Draw("same");
    c_b2->cd(3);h2_Zrat_mulCHI->Draw("Zcol");hp_Zrat_mulCHI->Draw("same");
    c_b2->cd(4);h2_Erat_mulCHI->Draw("Zcol");hp_Erat_mulCHI->Draw("same");
   
    hp_ZBound_mulCHI->SetMarkerStyle(20);
    hp_Zrat_mulCHI->SetMarkerStyle(20);
    hp_Erat_mulCHI->SetMarkerStyle(20);
 
    c_b2->cd(1);h2_ZBound_Zrat->Draw("Zcol");hp_ZBound_Zrat->Draw("same");
    hp_ZBound_Zrat->SetMarkerStyle(20);
   
    cc4 = new TCanvas("cc4","cc4", 1000,1000);
    cc4->Divide(1,3);
    cc4->cd(1);h1_yield_Z1->Draw();
    cc4->cd(2);h1_yield_Z2->Draw();
    cc4->cd(3);h1_yield_Z3->Draw();

    cc5 = new TCanvas("cc5","cc5", 1000,1000);
    cc5->Divide(1,3);
    cc5->cd(1);h1_yield_Z4->Draw();
    cc5->cd(2);h1_yield_Z5->Draw();

    cc4_bis = new TCanvas("cc4_bis","cc4_bis", 1000,1000);
    cc4_bis->Divide(1,3);
    cc4_bis->cd(1);h1_yield_Z1_bis->Draw();
    cc4_bis->cd(2);h1_yield_Z2_bis->Draw();
    cc4_bis->cd(3);h1_yield_Z3_bis->Draw();

    cc5_bis = new TCanvas("cc5_bis","cc5_bis", 1000,1000);
    cc5_bis->Divide(1,3);
    cc5_bis->cd(1);h1_yield_Z4_bis->Draw();
    cc5_bis->cd(2);h1_yield_Z5_bis->Draw();
   
    cc14 = new TCanvas("cc14","cc14",1000,1000);
    cc14->Divide(3,3);
    cc14->cd(1);h1_ntel_R3I->Draw();
    cc14->cd(2);h1_ntel_R3E->Draw();
    cc14->cd(3);h1_ntel_R4I->Draw();
    cc14->cd(4);h1_ntel_R4E->Draw();
    cc14->cd(5);h1_ntel_R5I->Draw();
    cc14->cd(6);h1_ntel_R5E->Draw();
    cc14->cd(7);h1_ntel_R6I->Draw();
    cc14->cd(8);h1_ntel_R6E->Draw();

 
    LOG(info) << "R3BAsyChimeraPhys::Init DONE";
    return kSUCCESS;
}

void R3BAsyChimeraPhys::Reset_Histo()
{
    LOG(info) << "R3BAsyChimeraPhys::Reset_Histo";
}

void R3BAsyChimeraPhys::Exec(Option_t* option)
{
   FairRootManager* mgr = FairRootManager::Instance();
   if (NULL == mgr)
        LOG(fatal) << "R3BAsyChimeraPhys::Exec FairRootManager not found";

   Int_t nHits;
   
   UInt_t NumTel;
   Float_t ff,ss, PID;
   UInt_t timeCsI;
   Int_t Z, A, stopped, Icod;
   double DE, Energy;
   
//   std:: cout << "R3BAsyChimPhys:: " <<  std::endl;

   int mult_CHI=0;
   int mult_KRAB=0;
   int mult_KRABR0=0;
   int mult_KRABR14=0;
   int ZBound=0;
   float Elong=0,Etrans=0;
   float Zlong=0,Ztrans=0;
 
   Float_t QX = 0, QY = 0;
   Float_t QXa = 0, QYa = 0;
   Float_t QXb = 0, QYb = 0;
   Float_t QX_CHI = 0, QY_CHI = 0;    
   Float_t QX_KRAB = 0, QY_KRAB = 0;    
   int mult_RP=0,mult_RPa=0,mult_RPb=0,mult_RP_CHI=0,mult_RP_KRAB=0;
   float diffRP=-1000;
   float Zrat=-10,Erat=-10;     
   float RP=-1000, RPa=-1000, RPb=-1000;      
   float RP_CHI=-1000;
   float RP_KRAB=-1000;     
   float dRP_CHI_KRAB=-1000;




   for (int i=0;i<ndd;i++){
    qqx[i]=0;   
    qqy[i]=0;   
   }

    
   Int_t trig = -1000;
   Int_t tpat = -1000;
   if (header)
   {
        trig = header->GetTrigger();
        tpat = header->GetTpat();
//        std:: cout << "R3BAsyChimPhys:: " << trig << " " << std::endl;
   }
   
   if(trig == 1 && tpat&2){
 

    if (fChimeraIdData && fChimeraIdData->GetEntriesFast())
    {
        // --- --------------------- --- //
        // --- loop over Chimera Id data --- //
        // --- --------------------- --- //
        nHits = fChimeraIdData->GetEntriesFast();
//        std:: cout << "R3BAsyChimPhys:: nHits = " << nHits << std::endl;
        int time_trig = 0;
        int time1 = 0;
        for (Int_t ihit = 0; ihit < nHits ; ihit++)
        {
            R3BAsyChimeraIdData* IdData = (R3BAsyChimeraIdData*)fChimeraIdData->At(ihit);
            if (!IdData)
                continue;
            NumTel = IdData->GetNumTel();
            ff = IdData->GetFast();
            ss = IdData->GetSlow();
            timeCsI = IdData->GetTimeCsI();
            Z = IdData->GetZ();
            A = IdData->GetA();
            stopped = IdData->GetStopped();
            Icod = IdData->GetCode();
            PID = IdData->GetPID();
            DE = IdData->GetDE();
            Energy = IdData->GetEnergy();
            double EsuA=Energy/A;	     
            
            
//            std::cout << ihit << " " << NumTel << " " << Z << " " << A << " " << Energy << std::endl;
            if(NumTel ==  93 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 108 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 129 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 185 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 213 && (this_energy==400)) continue;// bad 400
            if(NumTel == 267 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 332 && (this_energy==280 || this_energy==400)) continue;// bad 400, 280
            if(NumTel == 366 && (this_energy==600)) continue;// bad 600
            if(NumTel == 380 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 383 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
            if(NumTel == 391 && (this_energy==280 || this_energy==400 || this_energy==600)) continue;// bad 400, 280
       
            if(NumTel == 125 && (this_energy==280 || this_energy==400)) continue;// brutto 400
            if(NumTel == 198 && (this_energy==280)) continue;// brutto 280
            if(NumTel == 150 && (this_energy==280)) continue;// brutto 280

// to flatten    
            if(NumTel ==    80 && (this_energy==280 || this_energy==400 || this_energy==600)) continue; //400, 280
            if(NumTel ==   112 && (this_energy==280 || this_energy==400)) continue; //400, 280
            if(NumTel ==   144 && (this_energy==400)) continue;//400
            if(NumTel ==   184 && (this_energy==280)) continue;//280

            if(Icod>=0 && Icod<=5 && EsuA> 15 && EsuA<EAMax && Z>=1 && Z<=5){ 
             float EKin = Energy*1.0;
             float ETot = EKin + 939 * A;
             float gamma = ETot/ (939 * A );
             float gamma2=gamma * gamma;
             float beta=sqrt((gamma2-1)/gamma2);
             float gammanew = 1/sqrt(1-beta*beta);
             float theta= GetThetaRnd(NumTel);
             float phi= GetPhiRnd(NumTel);
             float bz= beta * cos (theta*TMath::DegToRad());
             float bt= beta * sin (theta*TMath::DegToRad());
             float gammabt=gammanew * bt;
             float ylab = 0.5*TMath::Log((1+bz)/(1-bz));
             h2_ylab_bt->Fill(ylab,gammabt,1/gammabt);
             h2_ylab_bt2->Fill(ylab,gammabt,1/gammabt);
             if(Z>=2)ZBound=ZBound+Z;
             if(Z==1)h1_yield_Z1->Fill(NumTel);
             if(Z==2)h1_yield_Z2->Fill(NumTel);
             if(Z==3)h1_yield_Z3->Fill(NumTel);
             if(Z==4)h1_yield_Z4->Fill(NumTel);
             if(Z==5)h1_yield_Z5->Fill(NumTel);
     
             Elong =  Elong  + EKin * cos (theta*TMath::DegToRad()) * cos (theta*TMath::DegToRad());
             Etrans = Etrans + EKin * sin (theta*TMath::DegToRad()) * sin (theta*TMath::DegToRad());
 
             Zlong =  Zlong  + Z * cos (theta*TMath::DegToRad()) * cos (theta*TMath::DegToRad());
             Ztrans = Ztrans + Z * sin (theta*TMath::DegToRad()) * sin (theta*TMath::DegToRad());
     
             mult_CHI++;
     
             if(NumTel>= 80 && NumTel<=399){
              float ww=0;
              if(ylab>(ymid+dy))ww=   1;
              if(ylab<(ymid-dy))ww=   0;
              if(ylab>(ymid-dy) && ylab<(ymid+dy))ww=0;
              float qx=ww*gammabt*A*cos(phi*TMath::DegToRad());
              float qy=ww*gammabt*A*sin(phi*TMath::DegToRad());
              QX=QX+qx;
              QY=QY+qy;
              QX_CHI=QX_CHI+qx;
              QY_CHI=QY_CHI+qy;
              if(ww!=0){
               if(Z==1)h1_yield_Z1_bis->Fill(NumTel);
               if(Z==2)h1_yield_Z2_bis->Fill(NumTel);
               if(Z==3)h1_yield_Z3_bis->Fill(NumTel);
               if(Z==4)h1_yield_Z4_bis->Fill(NumTel);
               if(Z==5)h1_yield_Z5_bis->Fill(NumTel);
		       
//		       std:: cout << "R3BAsyChimPhys:: mult_RP = " << mult_RP << std::endl;
               qqx[mult_RP]=qx;   
		       qqy[mult_RP]=qy; 		
		       
		       if(NumTel>= 80 && NumTel<=111)h1_ntel_R3I->Fill(NumTel,gammabt*A);
		       if(NumTel>=112 && NumTel<=143)h1_ntel_R3E->Fill(NumTel,gammabt*A);
		       if(NumTel>=144 && NumTel<=183)h1_ntel_R4I->Fill(NumTel,gammabt*A);
		       if(NumTel>=184 && NumTel<=223)h1_ntel_R4E->Fill(NumTel,gammabt*A);
		       if(NumTel>=224 && NumTel<=263)h1_ntel_R5I->Fill(NumTel,gammabt*A);
		       if(NumTel>=264 && NumTel<=303)h1_ntel_R5E->Fill(NumTel,gammabt*A);
		       if(NumTel>=304 && NumTel<=351)h1_ntel_R6I->Fill(NumTel,gammabt*A);
		       if(NumTel>=352 && NumTel<=399)h1_ntel_R6E->Fill(NumTel,gammabt*A);
	          }
	          mult_RP=mult_RP+(int)TMath::Abs(ww);
	          mult_RP_CHI=mult_RP_CHI+(int)TMath::Abs(ww);
             }//NumTel
            }//Icod>=0 && Icod<=5 && EsuA> 15 && EsuA<280 && Z>=1
        }// for multi
//            getchar();
    }//if (fChimeraIdData && fChimeraIdData->GetEntriesFast() &&  trig == 1)
    
    
    if (fMappedItemsKrab && fMappedItemsKrab->GetEntriesFast())
    {
        // --- --------------------- --- //
        // --- loop over Krab mapped data --- //
        // --- --------------------- --- //
        nHits = fMappedItemsKrab->GetEntriesFast();
//        std:: cout << "########################## = " << nHits << std::endl;
//        std:: cout << "R3BAsyChimPhys:: nHitsKrab = " << nHits << std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
             R3BAsyKrabMappedData* KrabMappedData = (R3BAsyKrabMappedData*)fMappedItemsKrab->At(ihit);
             if (!KrabMappedData)
                continue;
     		 mult_KRAB++;	
             UInt_t KR= KrabMappedData->GetRing();
             float theta= GetThetaRndKRAB(KR);
             float xrn = rr3->Uniform();
             float EK = xrn * 100;
             float gamma= EK/939+1; 
             float gamma2=gamma * gamma;
             float beta=sqrt((gamma2-1)/gamma2);
             float bz= beta * cos (theta*TMath::DegToRad());
             float bt= beta * sin (theta*TMath::DegToRad());
             float ylab = 0.5*log((1+bz)/(1-bz));
             float gammabt=gamma * bt;
             h2_ylab_bt2->Fill(ylab,gammabt,1/gammabt);
             if(KR==0)mult_KRABR0++;
             if(KR>0) mult_KRABR14++;
             if(KR<=KRABMaxRing){
              QX_KRAB=QX_KRAB+KrabMappedData->Getqx();
              QY_KRAB=QY_KRAB+KrabMappedData->Getqy();
              mult_RP_KRAB++;
             }
             if(KR<=KRABMaxRing){
              qqx[mult_RP]=-KrabMappedData->Getqx()*KRABww;
              qqy[mult_RP]=-KrabMappedData->Getqy()*KRABww;
              QX=QX-KrabMappedData->Getqx()*KRABww;
              QY=QY-KrabMappedData->Getqy()*KRABww;
              mult_RP++;
             }
             if(KR==4 && 0){
              qqx[mult_RP]=KrabMappedData->Getqx()*KRABww;
              qqy[mult_RP]=KrabMappedData->Getqy()*KRABww;
              QX=QX+KrabMappedData->Getqx()*KRABww;
              QY=QY+KrabMappedData->Getqy()*KRABww;
              mult_RP++;
             }
        }		       
//            std:: cout << "R3BAsyChimPhys:: mult_RP_KRAB = " << mult_RP << std::endl;
     }//if(fMappedItemsKrab && fMappedItemsKrab->GetEntriesFast()
       
     if(mult_RP_KRAB>=KRABRP_thr){
        RP_KRAB=atan2(QY_KRAB,QX_KRAB)*TMath::RadToDeg();
     }
   
     if(mult_RP_CHI>=CHIRP_thr){
        RP_CHI=atan2(QY_CHI,QX_CHI)*TMath::RadToDeg();
     }
     if(mult_KRAB>=KM_min && mult_KRAB<=KM_max ){ //29 run 108
       if(RP_KRAB>-181 && RP_CHI>-181){
	    h2_RP_CHI_KRAB->Fill(RP_CHI, RP_KRAB);  
        dRP_CHI_KRAB=RP_CHI-RP_KRAB;
        if(dRP_CHI_KRAB<-180)dRP_CHI_KRAB=-360-dRP_CHI_KRAB;
        if(dRP_CHI_KRAB> 180)dRP_CHI_KRAB= 360-dRP_CHI_KRAB;
	    if(dRP_CHI_KRAB<0)dRP_CHI_KRAB=-dRP_CHI_KRAB;
	    h1_dRP_CHI_KRAB->Fill(dRP_CHI_KRAB);  
      }//if(RP_KRAB>-181 && RP_CHI>-181)

//     std::cout << "mult_RP= " << mult_RP << std::endl;
//     std::cout << "dRP_CHI_KRAB= " << dRP_CHI_KRAB << std::endl;
     if(dRP_CHI_KRAB>120){
       for(int j=0;j<mult_RP;j++){
//        std::cout << "j= " << j << std::endl;

 	    float rrr2=rr2->Rndm();
        if(mult_RPa>=mult_RP/2)rrr2=0.75;
        if(mult_RPb>=mult_RP/2)rrr2=0.25;
//        std::cout << "rrr2= " << rrr2 << std::endl;

        if(rrr2<0.5){
         QXa=QXa+qqx[j];
         QYa=QYa+qqy[j];
         mult_RPa++;
        }else{
         QXb=QXb+qqx[j];
         QYb=QYb+qqy[j];
         mult_RPb++;
        }
     }
//     std::cout << "mult_RPa= " << mult_RPa << std::endl;
//     std::cout << "mult_RPb= " << mult_RPb << std::endl;
      
     if(mult_RP>=  (CHIRP_thr+KRABRP_thr)  ) RP = TMath::ATan2(QY, QX)*TMath::RadToDeg();
     if(mult_RPa>= (CHIRP_thr+KRABRP_thr)/2) RPa= TMath::ATan2(QYa,QXa)*TMath::RadToDeg();
     if(mult_RPb>= (CHIRP_thr+KRABRP_thr)/2) RPb= TMath::ATan2(QYb,QXb)*TMath::RadToDeg();
  
     if(RPa>-180 && RPb>-180 && RP>-180){
        diffRP=RPa-RPb;
        if(diffRP<-180)diffRP=-360-diffRP;
        if(diffRP> 180)diffRP= 360-diffRP;
        h1_diffRP->Fill(TMath::Abs(diffRP));
     }
     if(RP>=-180)h1_RP->Fill(RP);
     h1_mult_RP->Fill(mult_RP);
    
     int diffm=mult_RPa-mult_RPb;
     if(TMath::Abs(diffm)>1){
        std::cout << "R3BAsyChimeraPhys:: subvents multiplicities differ by more than one " << mult_RP << " " << mult_RPa << " " << mult_RPb << std::endl;
        std::cout << "R3BAsyChimeraPhys:: press enter to continue"  << std::endl;
        getchar();
     } 
    }//if(dRP_CHI_KRAB>90)

   }//if(mult_KRAB>=KM_min && mult_KRAB<=KM_max )

  
   Zrat=10*Ztrans/Zlong;
   Erat=10*Etrans/Elong;
   h2_mulCHI_mulKRAB->Fill(mult_KRAB,mult_CHI);
   hp_mulCHI_mulKRAB->Fill(mult_KRAB,mult_CHI);

   h2_ZBound_mulKRAB->Fill(mult_KRAB,ZBound);
   hp_ZBound_mulKRAB->Fill(mult_KRAB,ZBound);
     
   h2_Zrat_mulKRAB->Fill(mult_KRAB,Zrat);
   hp_Zrat_mulKRAB->Fill(mult_KRAB,Zrat);

   h2_Erat_mulKRAB->Fill(mult_KRAB,Erat);
   hp_Erat_mulKRAB->Fill(mult_KRAB,Erat);

   h2_ZBound_mulCHI->Fill(mult_CHI,ZBound);
   hp_ZBound_mulCHI->Fill(mult_CHI,ZBound);
     
   h2_Zrat_mulCHI->Fill(mult_CHI,Zrat);
   hp_Zrat_mulCHI->Fill(mult_CHI,Zrat);

   h2_Erat_mulCHI->Fill(mult_CHI,Erat);
   hp_Erat_mulCHI->Fill(mult_CHI,Erat);

   h2_ZBound_Zrat->Fill(Zrat,ZBound);
   hp_ZBound_Zrat->Fill(Zrat,ZBound);
 
   AddPhysData(mult_CHI, ZBound, Zrat, Erat, RP_CHI,
               mult_KRAB, mult_KRABR0,mult_KRABR14,RP_KRAB,
               RP,dRP_CHI_KRAB);
  }//if(trig == 1 && tpat&2)
   fNEvents += 1;
}

void R3BAsyChimeraPhys::FinishEvent()
{
    if (fChimeraIdData)
    {
        fChimeraIdData->Clear();
    }

    if (fMappedItemsKrab)
    {
        fMappedItemsKrab->Clear();
    }

    if (fChiKrabPhysData)
    {
        fChiKrabPhysData->Clear();
    }

}

void R3BAsyChimeraPhys::FinishTask()
{
    if (fChiKrabPhysData)
    {
     float tot = h1_diffRP->Integral(1,90); 
     float p90 = h1_diffRP->Integral(46,90);
     float ratio= p90/tot;
     float xsi=sqrt(-2*log(2*ratio));
     std::cout << tot << " " << p90 << " " << xsi << std::endl; 

     h2_RP_CHI_KRAB->Write(); 
     h1_dRP_CHI_KRAB->Write();
     h1_RP->Write();
     h1_diffRP->Write();
     
     h2_ylab_bt->Write();
     h2_ylab_bt2->Write();  
     
     h2_mulCHI_mulKRAB->Write();
     hp_mulCHI_mulKRAB->Write();

     h2_ZBound_mulKRAB->Write();
     hp_ZBound_mulKRAB->Write();
       
     h2_Zrat_mulKRAB->Write();
     hp_Zrat_mulKRAB->Write();

     h2_Erat_mulKRAB->Write();
     hp_Erat_mulKRAB->Write();

     h2_ZBound_mulCHI->Write();
     hp_ZBound_mulCHI->Write();
       
     h2_Zrat_mulCHI->Write();
     hp_Zrat_mulCHI->Write();

     h2_Erat_mulCHI->Write();
     hp_Erat_mulCHI->Write();

     h2_ZBound_Zrat->Write();
     hp_ZBound_Zrat->Write(); 

     c_b->Write();
     c_b2->Write();
     c_RP3->Write();
     cc4->Write();
     cc5->Write();
     cc4_bis->Write();
     cc5_bis->Write();
     cc14->Write();
     cc1->Write();

    }
}

Float_t R3BAsyChimeraPhys::GetTheta(int numtel)
{
    float theta = -1;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {

            //            std::cout << "------ " << thetamin[i] << " " << thetamax[i] << std::endl;

            theta = (thetamin[i] + thetamax[i]) / 2;
        }
    }
    return theta;
}

Float_t R3BAsyChimeraPhys::GetPhi(int numtel)
{
    float phi = -1000;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
            phi = ((numtel - telmin[i]) * 360. / (telmax[i] - telmin[i] + 1)) + 90;
            if (phi > 360)
                phi = phi - 360;
            //            std::cout << numtel << " " << phi << std::endl;
        }
    }
    return phi;
}

Float_t R3BAsyChimeraPhys::GetThetaRnd(int numtel)
{
    float xrn = (float)rrn->Rndm();
    float thr = -1000.0;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
            float theta = (thetamin[i] + thetamax[i]) / 2;
            thr = xrn * (thetamax[i] - thetamin[i]) + thetamin[i];
        }
    }
    return thr;
}

Float_t R3BAsyChimeraPhys::GetPhiRnd(int numtel)
{
    float xrn = (float)rrn->Rndm();
    float phir = -1000;
    for (int i = 0; i < 35; i++)
    {
        if (numtel >= telmin[i] && numtel <= telmax[i])
        {
            float phi = ((numtel - telmin[i]) * 360. / (telmax[i] - telmin[i] + 1)) + 90.0;
            float dphi = delta_phi[i];
            phir = (0.5 - xrn) * dphi + phi;
            if (phir < 0)
                phir += 360.0;
            // if(numtel>=80 && numtel<=90)std::cout << numtel << " " << phi << " " <<phir<< std::endl;
        }
    }
    return phir;
}



Float_t R3BAsyChimeraPhys::GetThetaRndKRAB(int KR)
{
    float xrn = (float)rrn->Uniform(); 
    float thr = -1000.0;
    float thr2 = -1000.0;

    float cosmin=TMath::Cos(thetaminK[KR]*TMath::DegToRad()); 
    float cosmax=TMath::Cos(thetamaxK[KR]*TMath::DegToRad()); 
    float acosrnd=cosmax+xrn*(cosmin-cosmax);
    thr = TMath::ACos(acosrnd)*TMath::RadToDeg();
 
    float theta = (thetaminK[KR] + thetamaxK[KR]) / 2;
    thr2 = xrn *   (thetamaxK[KR] - thetaminK[KR]) + thetaminK[KR];
//    cout << thr << " " << thr2 << endl;
//    getchar();
    return thr;
}



// -----   Private method AddHitData -------------------------------------------
R3BAsyChiKrabPhysData* R3BAsyChimeraPhys::AddPhysData(Int_t Multi_CHI, Int_t ZBound_CHI, Float_t ZRat_CHI, Float_t ERat_CHI, Float_t RP_CHI, 
                                       Int_t Multi_KRAB, Int_t MultiR0_KRAB, Int_t MultiR14_KRAB, Float_t RP_KRAB, 
                                       Float_t RP_CHIKRAB, Float_t dRP_CHIKRAB)
{
    TClonesArray& clref = *fChiKrabPhysData;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BAsyChiKrabPhysData(Multi_CHI, ZBound_CHI, ZRat_CHI, ERat_CHI, RP_CHI, 
                                                   Multi_KRAB, MultiR0_KRAB, MultiR14_KRAB, RP_KRAB, 
                                                   RP_CHIKRAB, dRP_CHIKRAB);
}


ClassImp(R3BAsyChimeraPhys)
