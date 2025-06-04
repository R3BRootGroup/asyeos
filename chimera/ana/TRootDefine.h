#ifndef TROOTDEFINE_H
#define TROOTDEFINE_H
//////////////////////////////////
// TRootDefine class
// generic interface to Root/Trees 
// e.d.f revision 03/2011
//////////////////////////////////
#include "TTree.h"
#include "TFile.h"
#include "TRootCHIEvent.h"
#include "TRootKRABEvent.h"
#include <array>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class TRootDefine 
{
 private:
  TTree *ftr;
  TFile *frootW;
  TRootCHIEvent *fchievt;
  TRootKRABEvent *fkrabevt;
 public:
  TRootDefine() {ftr=0; frootW=0; fchievt=0; fkrabevt=0;};
  void Open(const char *name);
  void Close();
  TTree *GetTree() {return ftr;}
  TRootCHIEvent *GetCHIEvt() {return fchievt;}
  TRootKRABEvent *GetKRABEvt() {return fkrabevt;}
  ClassDef(TRootDefine,1);
};
#endif
