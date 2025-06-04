#ifndef TROOTKRABEVENT_H
#define TROOTKRABEVENT_H
//////////////////////////////////
// TRootKRABEvent class
// generic interface to Root/Trees 
// e.d.f revision 03/2011
//////////////////////////////////
#include "TTree.h"
#include "TFile.h"

const int dKRABmax = 500;

// Generic raw Chimera event
// Note that //[multi] are not C++ comments but 
// mandatory Root dictionary directives


class TRootKRABEvent 
{
 public:
 int multi;
/*
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
*/ 
 //constructor 
 TRootKRABEvent() {
  multi=-1;
/*
  Idnumtel  = new UInt_t[dKRABmax];
  IdZ = new int[dKRABmax];
  IdA  = new int[dKRABmax];
  Idstopped  = new int[dKRABmax];
  Idcode  = new int[dKRABmax];
  IdPID  = new float[dKRABmax];
  IdE = new double[dKRABmax];
  IdDE = new double[dKRABmax];
  fast  = new float[dKRABmax];
  slow = new float[dKRABmax];
*/
 }
 //destructor
 virtual ~TRootKRABEvent() {
/*
  delete [] IdZ;
  delete [] IdA;
  delete [] Idstopped;
  delete [] Idcode;
  delete [] IdPID;
  delete [] IdE;
  delete [] IdDE;
  delete [] fast;
  delete [] slow;
*/  
 }
 ClassDef(TRootKRABEvent,1);
};
#endif
