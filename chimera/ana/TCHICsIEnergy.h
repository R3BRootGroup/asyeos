#ifndef TCHICSIENERGY_H
#define TCHICSIENERGY_H 

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include "TCHIResult.h"
#include "TCutG.h"
#include "TFile.h"

using namespace std;

// e.d.f. v. 0.1beta   Start 9/9/2011
//These classes manage CsI energy calibration for identified particles
//Specialized classes can handle different kinds of initialization files 
//and procedures for CsI calibration. Currently only derived classes 
//and procedures for the AsyEos experiment are defined. 

// Quality codes for CSI as defined by Chimera-Isospin program
enum ECsIEnergyCode {
 kENER0,  //ok
 kENER1,  //ok, but obtained by estrapolation or normalization from neighbours
 kENER2,  //bad or not done 
};

// Base abstract class for CsI energy calibration
// This abstract class can not be instanziated
class TCHICsIEnergy
{
protected:
 int fZ;          //Z of particle
 int fA;          //A of the particle
 double fPID;     //PID
 double fDE;      //Loss of energy
 double fEnergy;  //Total energy
 ECsIEnergyCode fecod;  //Quality
 string ffilenerg;         // energy calibration data file
 string ffilenergrec;      // energy loss->enery reconstructed data file
 string ffilecut;
 bool fisdefined;       // calibration data are present or not
public:
 TCHICsIEnergy() {fZ=-1; fA=-1; fDE=-1; fecod = kENER2;
                  fEnergy=-1; fisdefined=false;}      //constructor
 virtual ~TCHICsIEnergy() {}                          //destructor 
 virtual int Init() = 0;                              //Energy initialization
 virtual void PrintData() = 0;                        //List Data file 
 virtual void EvalEnergy() {};                        //Energy calibration 
 virtual double GetDE() {return fDE;}               
 virtual double GetEnergy() {return fEnergy;}
 virtual ECsIEnergyCode GetECod() {return fecod;}
 Int_t GetIECod() {
  Int_t IECod=-10;
  if (fecod==kENER0) IECod= 0;
  if (fecod==kENER1) IECod= 1;
  if (fecod==kENER2) IECod= 2;
  return IECod;
 }
 virtual bool IsEnergyDefined() {return fisdefined;}                      
};


class TCHICsIGSIEnergy: public  TCHICsIEnergy
{
private:
 double fa[MAXTEL];    // light calibration a coeff. 
 double fb[MAXTEL];    // light calibration b coeff.  
//paolo 21/11/2011 
  int ZZZ,AAA;
  double  DE11[70],  E11[70];
  double  DE12[45],  E12[45];
  double  DE13[41],  E13[41];
  double  DE24[64],  E24[64];
  double  DE37[69],  E37[69];
  double  DE49[57],  E49[57];
  double DE511[12], E511[12];
  TCutG *cut3He;
  TCutG *cut3Hebis; 
  TCutG *cut7Li;
  TCutG *cut4He;
  //paolo 21/11/2011 
public:
 TCHICsIGSIEnergy(string filener, string filenerec, string calibdir);   //Constructor
 ~TCHICsIGSIEnergy() {}              //Destructor
 int Init();                         //Initialization method
 void PrintData();                   //List Data file
 void EvalEnergy(int numtel, int fast, int slow, TCHIResult *idr ); //Calculate energy 
 ClassDef(TCHICsIGSIEnergy,1); 
};
#endif
