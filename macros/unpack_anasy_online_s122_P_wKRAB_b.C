typedef struct EXT_STR_h101_t 
{
 EXT_STR_h101_unpack_t unpack; 
 EXT_STR_h101_TPAT_t unpacktpat;
 EXT_STR_h101_ASYCHIMERA_onion_t asychimera;  // onion 
 EXT_STR_h101_LOS_t los_t;
// EXT_STR_h101_TRLO_onion unpackTRLO;
 EXT_STR_h101_WRMASTER_t wrmaster;
 EXT_STR_h101_ASYKRAB_onion_t asykrab;  // onion 
} EXT_STR_h101;

int unpack_anasy_online_s122(int nev)
{
 TString inputfile = "/home/pcget/main_0072_*_stitched.lmd";
 //TString inputfile = "--stream=172.16.11.115:6004";
 TString outputfile = "asyout_p_P_wKRAB-last.root";
 TString ucesb_dir  = getenv("UCESB_DIR");
 TString ucesb_path = ucesb_dir + 
 "/../upexps/asyeos_gsi_s122/asyeos_s122 --input-buffer=90Mi"; 
 ucesb_path.ReplaceAll("//", "/");
 TString ntuple_options = "RAW";  
 
 FairLogger::GetLogger()->SetLogScreenLevel("INFO");
 FairLogger::GetLogger()->SetColoredLog(true);

 int RunId = 72;
// int nev = -1;
 auto* run = new FairRunOnline();
 run->SetRunId(RunId);
 run->SetSink(new FairRootFileSink(outputfile));
 auto* eheader = new R3BEventHeader();
 run->SetEventHeader(eheader);

 EXT_STR_h101 ucesb_struct;
 auto* source = new R3BUcesbSource(inputfile, ntuple_options, 
                     ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
 source->SetMaxEvents(nev);  //until contr-c
 
 // Adding readers here
// auto unpackReader = new R3BUnpackReader((EXT_STR_h101_unpack_t*)&ucesb_struct.unpack, offsetof(EXT_STR_h101, unpack));
// source->AddReader(unpackReader); 

 auto losReader =   new R3BLosReader((EXT_STR_h101_LOS_t*)&ucesb_struct.los_t, offsetof(EXT_STR_h101, los_t));
 source->AddReader(losReader);





// source->AddReader(new R3BTrloiiScalerReader(&ucesb_struct.unpacktTRLO, offsetof(EXT_STR_h101, unpackTRLO)));
 source->AddReader(new R3BTrloiiTpatReader(&ucesb_struct.unpacktpat, offsetof(EXT_STR_h101, unpacktpat)));
 source->AddReader(new R3BUnpackReader    (&ucesb_struct.unpack,     offsetof(EXT_STR_h101, unpack)));
 source->AddReader(new R3BAsyChimeraReader((EXT_STR_h101_ASYCHIMERA_t*)&ucesb_struct.asychimera, offsetof(EXT_STR_h101, asychimera)));
 source->AddReader(new R3BWhiterabbitMasterReader(&ucesb_struct.wrmaster, offsetof(EXT_STR_h101, wrmaster), 0x1000));
 source->AddReader(new R3BAsyKrabReader((EXT_STR_h101_ASYKRAB_t*)&ucesb_struct.asykrab, offsetof(EXT_STR_h101, asykrab),"/home/pcget/R3BRoot/asyeos/krab/pars/TBOX-KRAB.map"));


/* 
 R3BWhiterabbitMasterReader* unpackWRMaster;
 unpackWRMaster = new R3BWhiterabbitMasterReader(
            (EXT_STR_h101_WRMASTER*)&ucesb_struct.wrmaster, offsetof(EXT_STR_h101, wrmaster), 0x1000);
 source->AddReader(unpackWRMaster);
*/ 
 source->SetMaxEvents(nev);  //until contr-c

 run->SetSource(source);


 R3BAsyKrabMappingPar* KrabMappingPar=new R3BAsyKrabMappingPar("pippo","pippo","pippo");
 
 
 R3BAsyChimeraDoArray* ChimeraDoArray=new R3BAsyChimeraDoArray();
 R3BAsyKrabDoArray* KrabDoArray=new R3BAsyKrabDoArray();
 run->AddTask(ChimeraDoArray);
 run->AddTask(KrabDoArray); 

 run->Init();
// run->Run(0, max_events); //start, stop
 //run->Run(-1, 0);         //all
 run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
 char val;
 std::cout<<"Press any key to finish\n";
 std::cin>>val;
 return 0;
}

