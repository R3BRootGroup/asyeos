// -------------------------------------------------------------------------
// -----            R3BAsyChimeraId header file             -----
// -----    Created 15/10/24  by E. De Filippo and P. Russotto         -----
// -------------------------------------------------------------------------

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




#ifndef TCsIIdent_H
#define TCsIIdent_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <cmath>
#include "TCsIParams.h"
#include "TCHIResult.h"

using namespace std;

const int CNTEL = 1192;      //Chimera max number of telescopes 
const int UNSET = -10;       //A start init value for some variables 



/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//Class for CsI identification
class TCsIIdent {
protected:
 int frun; 
 TCsIParams *ftableCHI_CsI[CNTEL];         //Chimera identification table for a given run 
 string fname;                             //Current file name for CsI parameters 
 bool fgridexist[CNTEL];                   //are grids filled ?  
public: 
 TCsIIdent(string dir, string filename, int *code, int run);  //constructor
 TCsIIdent(string dir, string filename, int run);             //constructor
 ~TCsIIdent();                                                //destructor
 int ReadAsciiFile();                                         //Read fit parameters from ascii file 
// int Get_Alternate_Offset_Data(string filename, TCHIEvent *gevent);  //Read alternate offset data (if any)
 bool IsGridExisting(int nt) {return fgridexist[nt];}         //Is grid defined ?
 TCsIParams *GetParams(int nt) {return ftableCHI_CsI[nt];}    //Return the parameter table or null 
// void CsI_Identification(vector<int> &, SParticle* , int, float, bool);  //Main CsI Identification routine
 void CsI_Identification(Int_t Numtel, Float_t fastpg, Float_t slowpg, TCHIResult *fchiresult, float tave);
 void CsI_Identification_Base(TCsIParams *, float, float, int *, int*, float*);    //Common base for CsI identification 
};

#endif
