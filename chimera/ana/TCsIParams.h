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

#ifndef TCsIParams_H
#define TCsIParams_H

#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int TABZM[5][11] = { 0, 0, 0, 0, 0, 0, 0,  0,  0,  0, 0, 0, 1,  2, 3, // gamma=0,p,d,t
                           0, 0, 0, 0, 0, 0, 0,  0,  0,  0, 4, 5, 0,  6, 0, // 3,4,6He
                           0, 0, 0, 0, 0, 0, 0,  0,  0,  7, 8, 9, 10, 0, 0, // 6,7,8,9Li
                           0, 0, 0, 0, 0, 0, 11, 12, 13, 14 };              // 7,8,9,10Be

class TCsIParams
{
  private:
    int fln;                      // lines number
    int ftel, fring;              // telescope, ring number
    int fpoints;                  // total number of points
    int *fiz, *fim, *fnp;         // charge,mass,points number
    int* fptrgap;                 // pointers to particles lines (nodes)
    int* fgap;                    // the lines distances (gaps)
    float* fcx;                   // lines x coordinates
    float* fcy;                   // lines y coordinates
    int fbittel;                  // pattern code for a given telescope, not implemented
    float fcsFoff, fcsSoff;       // alternate offset (if any) for fast and slow
    float fcsFgain, fcsSgain;     // alternate gain (if any) for fast and slow
    void CalculateLineDistance(); // calculate the line distance (private function)
  public:
    TCsIParams(int ntel,
               int ring,
               int nlign,
               int* iz,
               int* im,
               int* np,
               int* inode,
               int num,
               float* xc,
               float* yc);               // constructor
    TCsIParams(const TCsIParams& other); // copy constructor
    ~TCsIParams();                       // destructor
    void PrintData();                    // print the grid data for a given telescope (if existing) on stdout
    int Getbittel() { return fbittel; }
    int Getln() { return fln; }
    int* Getnp() { return fnp; }
    int* Getptrgap() { return fptrgap; }
    int* Getiz() { return fiz; }
    int* Getim() { return fim; }
    int* Getgap() { return fgap; }
    float* Getcx() { return fcx; }
    float* Getcy() { return fcy; }
    float GetFoff() { return fcsFoff; }
    float GetSoff() { return fcsSoff; }
    float GetFgain() { return fcsFgain; }
    float GetSgain() { return fcsSgain; }
    void SetFoff(float f) { fcsFoff = f; }
    void SetSoff(float s) { fcsSoff = s; }
    void SetFgain(float fg) { fcsFgain = fg; }
    void SetSgain(float sg) { fcsSgain = sg; }
};

#endif
