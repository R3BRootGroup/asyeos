#ifndef TROOTCHIEVENT_H
#define TROOTCHIEVENT_H
//////////////////////////////////
// TRootCHIEvent class
// generic interface to Root/Trees 
// e.d.f revision 03/2011
//////////////////////////////////
#include "TTree.h"
#include "TFile.h"

const int dCHImax = 500;

// Generic raw Chimera event
// Note that //[multi] are not C++ comments but 
// mandatory Root dictionary directives


class TRootCHIEvent 
{
 public:
 int Idmulti;
 float tavecsi;
 UInt_t *Idnumtel;  //[Idmulti]
 int *IdZ; //[Idmulti]
 int *IdA; //[Idmulti]
 int *Idstopped;  //[Idmulti]
 int *Idcode;  //[Idmulti]
 float *IdPID;  //[Idmulti]
 double *IdE;  //[Idmulti]
 double *IdDE;  //[Idmulti]
 float *fast;//[Idmulti]
 float *slow;//[Idmulti]
 //constructor 
 TRootCHIEvent() {
  Idmulti=-1;
  Idnumtel  = new UInt_t[dCHImax];
  IdZ = new int[dCHImax];
  IdA  = new int[dCHImax];
  Idstopped  = new int[dCHImax];
  Idcode  = new int[dCHImax];
  IdPID  = new float[dCHImax];
  IdE = new double[dCHImax];
  IdDE = new double[dCHImax];
  fast  = new float[dCHImax];
  slow = new float[dCHImax];
 }
 //destructor
 virtual ~TRootCHIEvent() {
  delete [] Idnumtel;
  delete [] IdZ;
  delete [] IdA;
  delete [] Idstopped;
  delete [] Idcode;
  delete [] IdPID;
  delete [] IdE;
  delete [] IdDE;
  delete [] fast;
  delete [] slow;
 }
 ClassDef(TRootCHIEvent,1);
};
#endif
