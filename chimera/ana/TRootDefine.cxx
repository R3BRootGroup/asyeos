#include <TRootDefine.h>


void TRootDefine::Open(const char *name)
{
 frootW = new TFile(name,"recreate");
 if(frootW->IsZombie()) {
  std::cout<<"RootTree>> Can not create ROOT file "<<name<<std::endl;
  return;
 }
 else {
  std::cout<<"RootTree>> Opened ROOT file "<<name<<std::endl;
 }
  
 frootW->SetCompressionLevel(1); 

 ftr = new TTree("h1","Root Tree");
 ftr->SetAutoSave(1000000000);
// important: uncomment the only branches you want to write!
 ftr->Branch("CHIevent", &fchievt, 32768, 2);
// ftr->Branch("KRABevent", &fkrabevt, 32768, 2);

}

void TRootDefine::Close()
{
 if(frootW) {
  frootW->Write();
  std::cout<<"RootTree>> closing ROOT file"<<std::endl;
  frootW->Close();
  delete frootW;
 }
}
