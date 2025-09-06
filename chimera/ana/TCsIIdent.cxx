///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// constructor class for chimera CsI identification
#include "TCsIIdent.h"

TCsIIdent::TCsIIdent(string dir, string filename, int* code, int run)
{
    frun = run;

    string cname = dir + '/' + filename;
    fname = cname;
    for (int i = 0; i < CNTEL; i++)
    {
        ftableCHI_CsI[i] = 0;
        fgridexist[i] = false;
    }
    int status = ReadAsciiFile();
    *code = status;
}

// generic constructor class for call from derived classes
TCsIIdent::TCsIIdent(string dir, string filename, int run)
{
    frun = run;

    string cname = dir + '/' + filename;
    fname = cname;
    for (int i = 0; i < CNTEL; i++)
    {
        ftableCHI_CsI[i] = 0;
        fgridexist[i] = false;
    }
}

TCsIIdent::~TCsIIdent()
{
    for (int i = 0; i < CNTEL; i++)
    {
        if (ftableCHI_CsI[i] != 0)
        {
            delete ftableCHI_CsI[i];
            ftableCHI_CsI[i] = 0;
        }
    }
}

// Read the ascii file with the CsI identification
// lines (Chimera-isospin format) and
// fill a TCsIParams table
int TCsIIdent::ReadAsciiFile()
{
    int status = 0;
    string s;
    int ring, ntel, ia1, ia2;

    cout << "TCsIIdent>> ascii files=" << fname.c_str() << endl;
    getchar();
    cout << "TCsIIdent>> press enter to continue" << endl;

    ifstream fd(fname.c_str());
    if (!fd)
    {
        cout << "TCsIIdent>> Can not find initialization file " << fname << endl;
        status = 1;
        return status;
    }

    int it = 0;
    while (!fd.eof())
    {
        // read a line of data
        getline(fd, s);
        if (s.find('*') == 0)
            continue;
        if (s.empty())
            continue;
        istringstream is(s);
        is >> ring >> ntel >> ia1 >> ia2;
        //  cout<<ring<<" "<<ntel<<" "<<ia1<<" "<<ia2<<endl;
        if (is.fail())
        {
            cout << "TCsIIdent>> Error reading line: " << s << endl;
            is.clear();
            status = 2;
            break;
        }
        // check run coherence and skip to next telescope
        // if coherence is not fit. The operator >> is used
        // from now because we expect numerical values only
        cout << "TCsIIdent>> sono qui " << endl;
        if (status == 0)
        {
            if (frun < ia1 || frun > ia2)
            {
                cout << "TCsIIdent>> run number not coherent. tel= " << ntel << endl;
                ;
                // skip to next telescope
                int nlign;
                fd >> nlign;
                int j = 0;
                for (int i = 0; i < nlign; i++)
                {
                    int iz, im, np;
                    fd >> iz >> im >> np;
                    j += np;
                }
                for (int i = 0; i < j; i++)
                {
                    float x, y;
                    fd >> x >> y >> ws;
                }
                continue;
            }
        } // end check coherence

        // read the lines. Exceptions handler
        // will be inserted in a next version
        it++; // next telescope
        int nlign;
        fd >> nlign;
        int* iz = new int[nlign];
        int* im = new int[nlign];
        int* np = new int[nlign];
        int* inode = new int[nlign];
        int num = 0;
        for (int i = 0; i < nlign; i++)
        {
            fd >> iz[i] >> im[i] >> np[i];
            inode[i] = num;
            num += np[i];
        }
        float* xc = new float[num];
        float* yc = new float[num];
        for (int i = 0; i < num; i++)
        {
            fd >> xc[i];
            fd >> yc[i];
        }
        // protection with malformed data in file
        fd >> ws; // eat up any leading white space
        // construct the CsI parameters table

        ftableCHI_CsI[ntel] = new TCsIParams(ntel, ring, nlign, iz, im, np, inode, num, xc, yc);
        //  ftableCHI_CsI[ntel]->PrintData();
        fgridexist[ntel] = true;
        // delete temporary variables
        delete[] xc;
        delete[] yc;
        delete[] iz;
        delete[] im;
        delete[] np;
        delete[] inode;
    }
    fd.close();
    cout << "TCsIIdent>> Read " << it << " telescopes from file " << fname.c_str() << endl;
    getchar();
    return status;
}

/////////////////////////////////////////////////////////////////////////////////////////
//  General routine for CsI charge and mass Identification
//  based on procedures defined by the DP2 Orsay method.
//  Adapted to the isospin program from the routine
//  IdnCsOr developed by L. Tassan-Got.
//  Re-written for the Chimera Unpacker, C++ version, e.d.f. 11/2015
//  AsyEos-2   2025
//////////////////////////////////////////////////////////////////////////////////////////
//  Table of defined code (in common with KaliVeda library KVIDGCsI)
//     1  : Z ok, mais les masses superieures a A sont possibles
//     2  : Z ok, mais les masses inferieures a A sont possibles
//     3  : Z ok, mais les masses superieures ou inferieures a A sont possibles
//     4  : Z ok, masse hors limit superieure ou egale a A
//     5  : Z ok, masse hors limit inferieure ou egale a A
//     6  : au-dessus de la ligne fragment, Z est alors un Zmin
//     7  : a gauche  de la ligne fragment, Z est alors un Zmin et le plus probable
//     8  : Z indetermine ou (slow,fast) hors limites
//     9  : pas de lignes pour ce module
//    10  : good gamma code (not implemented). Gamma have variable codes <=4 is good
//    11  : no grid defined (code 9 repetition)
//    12  : init value (UNSET)
///////////////////////////////////////////////////////////////////////////////////////////
// note: the identification loop is defined in the calling process
void TCsIIdent::CsI_Identification(Int_t Numtel, Float_t fastpg, Float_t slowpg, TCHIResult* chiresult, float tave)
{
    float fastp, slowp;
    int icode = 0;
    int izt;
    float iat;

    chiresult->SetZ(UNSET);
    chiresult->SetA(UNSET);
    chiresult->Setcod(kICODE_UNSET);
    int numtel = Numtel;
    // the grid does not exist
    if (!fgridexist[numtel])
    {
        chiresult->Setcod(kICODE9);
        return;
    }

    // Get the Grid parameters for the current telescope
    TCsIParams* param = GetParams(numtel);
    fastp = fastpg;
    slowp = slowpg;

    if (slowp == 0 || fastp == 0)
    {
        chiresult->Setcod(kICODE8); // code 8: no identification
        return;
    }

    // grid points are multiplied by 4
    slowp = (slowp + 0.5) * 4.0;
    fastp = (fastp + 0.5) * 4.0;

    // attributing the pattern code to CsI. This is a property of CsI not depending from
    // identification procedure.
    // chiresult->Setbittel(param->Getbittel());   //not defined in asyeos

    // main algorithm for CsI identification
    CsI_Identification_Base(param, fastp, slowp, &icode, &izt, &iat);

    // fill TCHIResult instance
    ECode cd = static_cast<ECode>(icode);
    chiresult->Setcod(cd);
    chiresult->SetZ(izt);
    chiresult->SetA(TMath::Nint(iat));

    // fill pid
    float pid_new = izt + 0.1 * (iat - 2.0 * izt);
    float pid_old = iat;
    chiresult->Setpid(pid_old);
    if (izt < 0 && iat < 0)
        chiresult->Setpid(100);
    if (izt == 4 && iat == 8)
        chiresult->Setpid(50);
}

void TCsIIdent::CsI_Identification_Base(TCsIParams* param, float fastp, float slowp, int* icods, int* izts, float* as)
{
    int kind, ksup, kinfi, ksups;
    float dinf = 0.0, dsup = 0.0, dsups = 0.0, dinfi = 0.;
    int icode = 0;
    int ia1, ia2, j, ibif, ki, izt, ix1, ix2, it;
    float x1, x2, y1, y2, ac, dist, dt, a, yy;
    float distgamma = 0.0;

    int ln = param->Getln();
    int* ptrgap = param->Getptrgap();
    int* np = param->Getnp();
    float* cx = param->Getcx();
    float* cy = param->Getcy();
    int* iz = param->Getiz();
    int* im = param->Getim();
    int* igap = param->Getgap();

    // clear params. Important
    kind = -1; // bug 11/2016
    ksup = -1; // bug corrected 10/2016
    kinfi = 0;
    ksups = 0;
    *icods = 0;

    for (int k = 0; k < ln; k++)
    {
        if (ksups != 0)
            break;
        ia1 = ptrgap[k];
        ia2 = ia1 + np[k] - 1;
        x1 = cx[ia1];
        x2 = cx[ia2];
        if (slowp >= x1 && slowp < x2)
        {
            x2 = slowp - 1;
            j = ia1;
            while (slowp > x2)
            {
                j++;
                x2 = cx[j];
            }
            y2 = cy[j];
            x1 = cx[j - 1];
            y1 = cy[j - 1];
            ac = (y2 - y1) / (x2 - x1);
            dist = fastp - y1 - ac * (slowp - x1);
            // distance from (0 0) line saved for gamma identification
            if (k == 0)
                distgamma = dist;
            if (dist > 0.)
            {
                kinfi = kind;
                dinfi = dinf;
                kind = k;
                dinf = dist;
            }
            else if (ksup == -1)
            { // bug corrected 10/2016
                ksup = k;
                dsup = -dist;
            }
            else
            {
                ksups = k;
                dsups = -dist;
            }
        }
    }

    ibif = 0;
    if (ksup >= 0)
    { // bug corrected 10/2016
        // point between two lines
        if (kind >= 0)
        { // bug corrected 11/2016
            ki = iz[ksup] - iz[kind];
            dt = dinf + dsup;
            // same Z
            if (ki == 0)
            {
                izt = iz[kind];
                j = im[ksup] - im[kind];
                dist = dt / (float)j;

                //  A = Asup
                if (dinf > dsup)
                {
                    ibif = 1;
                    ki = ksup;
                    a = im[ksup];
                    yy = -dsup;

                    if (ksups > 0)
                    {
                        y2 = dsups - dsup;
                        it = iz[ksups];
                        if (it == izt)
                        {
                            ibif = 0;
                            y2 = y2 / 2;
                            ix2 = im[ksups] - im[ksup];
                        }
                        else
                        {
                            if (it > 0)
                                y2 = y2 / 2;
                            x2 = igap[ksup];
                            x2 = fmax(x2, dist) / 2.;
                            y2 = fmin(y2, x2);
                            ix2 = 1;
                        }
                    }
                    else
                    {
                        y2 = igap[ksup];
                        y2 = fmax(y2, dist) / 2.;
                        ix2 = 1;
                    }
                    y1 = -dt / 2;
                    ix1 = -j;
                } // if(dinf > dsup)

                // A = Ainf
                else
                {
                    ibif = 2;
                    ki = kind;
                    a = im[kind];
                    yy = dinf;
                    if (kinfi == 0)
                    {
                        y1 = (dinfi - dinf) / 2;
                        it = iz[kinfi];
                        if (it == izt)
                        {
                            ibif = 0;
                            ix1 = im[kinfi] - im[kind];
                            y1 = -y1;
                        }
                        else
                        {
                            x1 = igap[kind];
                            x1 = fmax(x1, dist) / 2;
                            y1 = -fmin(y1, x1);
                            ix1 = -1;
                        }
                    }
                    else
                    {
                        y1 = igap[kind];
                        y1 = -fmax(y1, dist) / 2;
                        ix1 = -1;
                    }
                    y2 = dt / 2;
                    ix2 = j;
                }
            } // if(ki==0)

            // Z different
            else
            {
                if (iz[ksup] < 0)
                {
                    dt = dt * 2;
                    dsup = dt - dinf;
                }
                // Z=Zsup
                ibif = 3;
                if (dinf > dsup)
                {
                    ki = ksup;
                    izt = iz[ksup];
                    a = im[ksup];
                    yy = -dsup;
                    y1 = igap[ksup];
                    y1 = y1 / 2;
                    if (ksups > 0)
                    {
                        y2 = dsups - dsup;
                        it = iz[ksups];
                        if (it == izt)
                        {
                            ibif = 2;
                            ix2 = im[ksups] - im[ksup];
                            x1 = (y2 / ix2) / 2;
                            y1 = fmax(y1, x1);
                            y1 = -fmin(y1, dt / 2);
                            ix1 = -1;
                            y2 = y2 / 2;
                        }
                        else
                        {
                            if (it > 0)
                                y2 = y2 / 2;
                            y2 = fmin(y1, y2);
                            ix2 = 1;
                            y1 = -fmin(y1, dt / 2);
                            ix1 = -1;
                        }
                    }
                    else
                    {
                        icode = 7;
                        y2 = y1;
                        ix2 = 1;
                        y1 = -fmin(y1, dt / 2);
                        ix1 = -1;
                    }
                } // if(dinf > dsup)
                // Z=Zinf
                else
                {
                    ki = kind;
                    izt = iz[kind];
                    a = im[kind];
                    yy = dinf;
                    y2 = igap[kind];
                    y2 = y2 / 2;
                    if (kinfi >= 0)
                    { // bug 11/2016
                        y1 = dinfi - dinf;
                        it = iz[kinfi];
                        if (it == izt)
                        {
                            ibif = 1;
                            ix1 = im[kinfi] - im[kind];
                            x2 = (-y1 / (float)ix1) / 2;
                            y2 = fmax(y2, x2);
                            y2 = fmin(y2, dt / 2);
                            ix2 = 1;
                            y1 = -y1 / 2;
                        }
                        else
                        {
                            y1 = -fmin(y2, y1 / 2);
                            ix1 = -1;
                            y2 = fmin(y2, dt / 2);
                            ix2 = 1;
                        }
                    }
                } // if(dinf > dsup)
            }     // else Z different
        }         // if(kind > 0)

        // Only the upper line found
        else if (iz[ksup] >= 0)
        {
            ibif = 3;
            ki = ksup;
            izt = iz[ksup];
            a = im[ksup];
            yy = -dsup;
            y1 = igap[ksup];
            y1 = y1 / 2;
            if (ksups > 0)
            {
                y2 = dsups - dsup;
                it = iz[ksups];
                if (it == izt)
                {
                    ibif = 2;
                    ix2 = im[ksups] - im[ksup];
                    x1 = (y2 / (float)ix2) / 2;
                    y1 = -fmax(y1, x1);
                    ix1 = -1;
                    y2 = y2 / 2;
                }
                else
                {
                    if (it > 0)
                        y2 = y2 / 2;
                    y2 = fmin(y1, y2);
                    ix2 = 1;
                    y1 = -y1;
                    ix1 = -1;
                }
            }
            else
            {
                icode = 7;
                y2 = y1;
                ix2 = 1;
                y1 = -y1;
                ix1 = -1;
            }
        }
        else
        {
            icode = 8;
            izt = UNSET;
            a = UNSET;
        }
    } // if(ksup > 0)

    // Only the lower line found
    else if (kind > 0)
    {
        // Sep. fragment
        if (iz[kind] < 0)
        {
            izt = iz[kind - 1] + 1;
            a = -1.;
            icode = 6;
            ki = 0;
        }
        //  Ligne de crete
        else
        {
            ibif = 3;
            ki = kind;
            izt = iz[kind];
            a = im[kind];
            yy = dinf;
            y2 = igap[kind];
            y2 = y2 / 2;
            if (kinfi > 0)
            {
                y1 = dinfi - dinf;
                it = iz[kinfi];
                if (it == izt)
                {
                    ibif = 1;
                    ix1 = im[kinfi] - im[kind];
                    x2 = (-y1 / (float)ix1) / 2;
                    y2 = fmax(y2, x2);
                    ix2 = 1;
                    y1 = -y1 / 2;
                }
                else
                {
                    y1 = -fmin(y2, y1 / 2);
                    ix1 = -1;
                    ix2 = 1;
                }
            }
            else
            {
                y1 = -y2;
                ix1 = -1;
                ix2 = 1;
            }
            icode = 7; // bug corrected 10/2016
        }
    }
    // no line found
    else
    {
        icode = 8;
        izt = UNSET;
        a = UNSET;
    }

    ///////////////////////////////////////////////////////////
    //  Test on limits
    ///////////////////////////////////////////////////////////
    if (ki != 0 && icode == 0)
    {
        if (yy > y2)
            icode = 4;
    }
    if (ki != 0 && (icode == 0 || icode == 7))
    {
        if (yy < y1)
            icode = 5;
    }

    // paolo 18072025 if(icode == 4 || icode == 5) a = -1.;

    // Other masses are possible ?
    if (icode == 0)
    {
        // Superior mass
        if (ibif == 1 || ibif == 3)
        {
            it = ki + 1;
            if (it < ln && iz[it] == izt)
            {
                j = it + 1;
                x1 = cx[ptrgap[it]];
                x2 = cx[ptrgap[j] - 1];
                if (slowp < x1 || slowp > x2)
                    icode = icode + 1;
            }
        }
        // Inferior masse
        if (ibif == 2 || ibif == 3)
        {
            it = ki - 1;
            if (it >= 0 && iz[it] == izt && it < ln)
            {
                x1 = cx[ptrgap[it]];
                x2 = cx[ptrgap[ki] - 1];
                if (slowp < x1 || slowp > x2)
                    icode = icode + 2;
            }
        }
    }

    // some protections
    if (izt > 100 && a > 100)
    {
        izt = UNSET;
        a = UNSET;
        icode = 8;
    }

    // added for definition of good gamma identification
    if (izt == 0)
    {
        icode = -distgamma / 10;
        //  if(icode<0) {   // commentato Nancy 11-09-2017
        //   icode=8;
        //  }
        // else if(icode<=4) {
        //  icode = 10;           //GAMMA good code. KaliVeda code compatibility. Not implemented
        // }
        // if(icode>5)icode=8;     //commentato Nancy 11-09-2017
    }

    // return values;
    *icods = icode;
    *izts = izt;
    *as = a;
}
