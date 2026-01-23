#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

typedef struct EXT_STR_h101_t 
{
 EXT_STR_h101_unpack_t unpack;  
 EXT_STR_h101_TPAT_t tpat;
 EXT_STR_h101_ASYCHIMERA_onion_t asychimera;  // onion 
 EXT_STR_h101_ASYKRAB_onion_t asykrab;  // onion 
} EXT_STR_h101;

int unpack_s122_rep_chi_match_id_wkrab(Int_t RunId = 38, int nev=-1)
{
 cout << "PLEASE READ COMMENTS MARKED WITH NOTE:: AND SET PARAMETRS AS SUGGESTED" << endl;
 cout << "PRESS ENTER TO GO ON AND AGAIN...AND AGAIN...UNTIL YOU SEE MACRO RUNNING" << endl;
 getchar();
 
 
 TString runNumber = Form("%04d", RunId);

 TString path1 = "/u/russotto/lustre/";
 TString inputfile = path1 + "stitched" + runNumber + "_*.lmd";
 TString outputfile = TString::Format("/u/russotto/my_lustre/ROOTFILES/asyout_rep_chi__krab_r%04d_pro.root", RunId);
 
 TString dir = gSystem->Getenv("VMCWORKDIR");
 TString ntuple_options = "RAW";  
 TString ucesb_dir  = getenv("UCESB_DIR");
 TString ucesb_path = ucesb_dir + "/../upexps/202503_s122/202503_s122 --input-buffer=138Mi --allow-errors";
 ucesb_path.ReplaceAll("//", "/");
 
 FairLogger::GetLogger()->SetLogScreenLevel("INFO");
 FairLogger::GetLogger()->SetColoredLog(true);

 const int parId = RunId;

// int nev = -1;
 auto* run = new FairRunOnline();
 auto *EvntHeader = new R3BEventHeader();
 EvntHeader->SetExpId(122);
 run->SetEventHeader(EvntHeader);
 run->SetRunId(parId);
 run->SetSink(new FairRootFileSink(outputfile)); // Test suggested by Philipp if lustre is full not to write data 

 int refresh = 10;
 int port=8880;
//  run->ActivateHttpServer(refresh,port);



 EXT_STR_h101 ucesb_struct;
 auto* source = new R3BUcesbSource(inputfile,ntuple_options, 
                     ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
 source->SetMaxEvents(nev);  //until contr-c
 
 source->AddReader(new R3BUnpackReader    (&ucesb_struct.unpack,     offsetof(EXT_STR_h101, unpack)));

 source->AddReader(new R3BTrloiiTpatReader(&ucesb_struct.tpat, offsetof(EXT_STR_h101,tpat)));


 auto chimeraReader =new R3BAsyChimeraReader((EXT_STR_h101_ASYCHIMERA_t*)&ucesb_struct.asychimera, offsetof(EXT_STR_h101, asychimera)); 
 chimeraReader->SetOnline(1);
 source->AddReader(chimeraReader);
 
 TString sKMap=dir+"/asyeos/krab/pars/TBOX-KRAB.map";
 const char *fKMap = sKMap.Data();

 auto krabReader = new R3BAsyKrabReader((EXT_STR_h101_ASYKRAB_t*)&ucesb_struct.asykrab, offsetof(EXT_STR_h101, asykrab),fKMap);
 krabReader->SetOnline(0);
 source->AddReader(krabReader);

 source->SetMaxEvents(nev);  //until contr-c

 run->SetSource(source);

 TString sMatch=dir+"/asyeos/chimera/pars/offset.par";
 TString sMatch2=dir+"/asyeos/chimera/pars/sat_slow_r357.dat";
  
 const char *fMatch = sMatch.Data();
 const char *fMatch2= sMatch2.Data();
 
 R3BAsyChimeraMatch* chimeraMatch=new R3BAsyChimeraMatch(fMatch, fMatch2);

 chimeraMatch->SetOnline(0);
 chimeraMatch->SetNTelMin(80);
 chimeraMatch->SetNTelMax(399);
 chimeraMatch->Set_slow_corr(1.0000);//NOTE::Set slow corr to 1.0045 for 600 MeV/A beam energy
 run->AddTask(chimeraMatch);

 R3BAsyChimeraId* chimeraId=new R3BAsyChimeraId(fMatch);
 chimeraId->SetOnline(0);
 
 chimeraId->SetCalDir((std::string)(dir+"/asyeos/chimera/calfiles"));
 chimeraId->SetGridFileName("R6.asc");//NOTE::use grids_run221.asc for 600 MeV/A beam energy
 chimeraId->SetECalibFileName("ecalib141111.txt");
 chimeraId->SetECalibTableFileName("dee-16072025.txt");
 // Z1A0->Z2A2
 chimeraId->Set_optZ2(0); //NOTE::set to 1 for 600 MeV/A beam energy
 
 run->AddTask(chimeraId);

 R3BAsyKrabMappingPar* KrabMappingPar=new R3BAsyKrabMappingPar("pippo","pippo","pippo");

 R3BAsyKrabPhys* krabPhys=new R3BAsyKrabPhys();
 krabPhys->SetOnline(0);
 krabPhys->SetRmin(0);
 krabPhys->SetRmax(2);
 krabPhys->SetRP_thr(4);
 run->AddTask(krabPhys);
 
 R3BAsyChimeraPhys* chiPhys=new R3BAsyChimeraPhys();
 chiPhys->SetOnline(0);
 chiPhys->SetEnergy(400); //NOTE::set beam energy here
 run->AddTask(chiPhys);

 run->Init();
// run->Run(0, max_events); //start, stop
 //run->Run(-1, 0);         //all
 run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
 char val;
 std::cout<<"Press any key to finish\n";
 std::cin>>val;
 return 0;
}

