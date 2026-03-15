//////////////////////////////////////
// TCHICsIEnergy implementation
// for all derived classes
//////////////////////////////////////

#include "TCHICsIEnergy.h"
#define tollup 1.03
#define tolldown 0.97

/////////////////////////////////////////////
// CsI Calibration for AsyEos experiment
/////////////////////////////////////////////

// Constructor
TCHICsIGSIEnergy::TCHICsIGSIEnergy(string filener, string filenerec, string calibdir)
{
    ffilenerg = calibdir + '/' + filener;
    ffilenergrec = calibdir + '/' + filenerec;
    ffilecut = calibdir + "CHIcutsgood2.root";

    cout << "TCHICsIGSIEnergy::ffilenerg=" << ffilenerg << endl;
    cout << "TCHICsIGSIEnergy::ffilenergrec=" << ffilenergrec << endl;
    cout << "TCHICsIGSIEnergy::MAXTEL=" << MAXTEL << endl;
    cout << "TCHICsIGSIEnergy:: press enter to continue" << endl;
    //    getchar();

    for (int i = 0; i < MAXTEL; i++)
    {
        fa[i] = -1;
        fb[i] = -1;
    }
}

// parameters initialization for all telescopes
int TCHICsIGSIEnergy::Init()
{
    const int LEN = 128;
    int row = 0;
    char line[LEN];
    int numtel;
    double a, b;
    ifstream freg(ffilenerg.c_str());
    if (!freg)
    {
        cout << "TCHICsIGSIEnergy>> Calibration file " << ffilenerg << " can not be opened" << endl;
        return -1;
    }

    istringstream is;
    while (freg.getline(line, LEN))
    {
        line[strlen(line)] = ' ';
        row++;
        switch (line[0])
        {
            case '*':
                break;
            default:
                is.str(line);
                is >> numtel >> a >> b;
                if (is.fail())
                {
                    cout << "TCHICsIGSIEnergy>> Bad line " << row << " skipped" << endl;
                    is.clear();
                    break;
                }
                if (numtel >= 0 && numtel < MAXTEL)
                {
                    fa[numtel] = a;
                    fb[numtel] = b;
                    cout << "TCHICsIGSIEnergy:: " << numtel << " " << fa[numtel] << " " << fb[numtel] << endl;
                }
                break;
        }
    }
    cout << "TCHICsIGSIEnergy>> Read " << row << " lines from calibration file " << ffilenerg << endl;
    cout << "TCHICsIGSIEnergy>> press enter to continue" << endl;
    //    getchar();

    freg.close();
    fisdefined = true;
    // getchar();
    // paolo 21/11/2011
    //   ifstream pippo("../CALFILES/de-e-bs.txt");
    ifstream pippo(ffilenergrec.c_str());
    if (!pippo)
        cout << "error: file " << ffilenergrec << " not found" << endl;
    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;

    for (int iii = 0; iii < 70; iii++)
    {
        pippo >> DE11[iii] >> E11[iii];
        cout << iii << " " << DE11[iii] << " " << E11[iii] << endl;
    }
    //  getchar();

    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;
    for (int iii = 0; iii < 45; iii++)
    {
        pippo >> DE12[iii] >> E12[iii];
        cout << iii << " " << DE12[iii] << " " << E12[iii] << endl;
    }
    //  getchar();

    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;
    for (int iii = 0; iii < 41; iii++)
    {
        pippo >> DE13[iii] >> E13[iii];
        cout << iii << " " << DE13[iii] << " " << E13[iii] << endl;
    }
    //  getchar();

    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;
    for (int iii = 0; iii < 64; iii++)
    {
        pippo >> DE24[iii] >> E24[iii];
        cout << iii << " " << DE24[iii] << " " << E24[iii] << endl;
    }
    //  getchar();

    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;
    for (int iii = 0; iii < 69; iii++)
    {
        pippo >> DE37[iii] >> E37[iii];
        cout << iii << " " << DE37[iii] << " " << E37[iii] << endl;
    }
    //  getchar();

    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;
    for (int iii = 0; iii < 57; iii++)
    {
        pippo >> DE49[iii] >> E49[iii];
        cout << iii << " " << DE49[iii] << " " << E49[iii] << endl;
    }
    //  getchar();

    pippo >> ZZZ >> AAA;
    cout << "reading energy loss table for Z=" << ZZZ << " A=" << AAA << endl;
    for (int iii = 0; iii < 12; iii++)
    {
        pippo >> DE511[iii] >> E511[iii];
        cout << iii << " " << DE511[iii] << " " << E511[iii] << endl;
    }
    //  getchar();

    pippo.close();

    /*
      TFile *fcut=new TFile(ffilecut.c_str());
      cut3Hebis=  (TCutG *)fcut->Get("bad3HeStop_bis");
      cut3He=     (TCutG *)fcut->Get("bad3HeStop");
      cut7Li =    (TCutG *)fcut->Get("bad7LiStop");
      cut4He=     (TCutG *)fcut->Get("bad4HeStop");
      fcut->Close();
    */

    // paolo 21/11/2011

    //    optZ2=false;
    return 0;
}

// List data for debug
void TCHICsIGSIEnergy::PrintData()
{
    if (!fisdefined)
        return;
    for (int i = 0; i < MAXTEL; i++)
    {
        if (fa[i] != -1 && fb[i] != -1)
        {
            cout << "Telescope: " << setw(4) << i << " " << fa[i] << " " << fb[i] << endl;
        }
    }
}

// Energy calibration routine.
// Da completare per Paolo con la formula per il calcolo dell'energia
// totale per le particelle che traversano
void TCHICsIGSIEnergy::EvalEnergy(int numtel, int fast, int slow, TCHIResult* idr)
{
    double erec = -100;
    int stopped = 1;
    fDE = -100.;
    fEnergy = -100.;
    fecod = kENER2;
    idr->SetStopped();
    fZ = idr->GetZ();          // charge
    fA = idr->GetA();          // mass
    fPID = idr->GetPID();      // PID
    ECode cod = idr->Getcod(); // identification code

    double de = -100.0;
    if (fa[numtel] != -1 && fb[numtel] != -1)
    {
        if (fast > 0)
        {
            de = fast * fa[numtel] + fb[numtel];
        }
    }

    //    if(numtel == 95) cout <<"bf TCHICsIGSIEnergy:: " <<  de << " " << fast << " " << fa[numtel] << " " <<
    //    fb[numtel] << endl;
    // paolo 21/11/2011
    int iii;
    int myflag = 0;
    if (de > 0)
    {
        if (fZ == 2 && fA == 2 && de < 330)
        {
            idr->SetA(0);
            fA = 0;
            idr->SetZ(1);
            fZ = 1;
            idr->Setcod(kICODE5); // ok Z2A2->Z1A0
        }

        if (fZ == 1)
        {
            if (fA == 1)
            {
                if (de > 222.1 * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z1A1->Z1A2
                    idr->SetA(2);
                    fA = 2;
                }
                if (de > 292.8 * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z1A1->Z1A3
                    idr->SetA(3);
                    fA = 3;
                }
                if (de > 347.6 * tollup)
                {
                    idr->Setcod(kICODE5); // ok Z1A1->Z2A4
                    idr->SetA(4);
                    fA = 4;
                    idr->SetZ(2);
                    fZ = 2;
                }
            } // if(fA==1){

            if (fA == 2)
            {
                if (de > 292.8 * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z1A2->Z1A3
                    idr->SetA(3);
                    fA = 3;
                }
                if (de > 347.6 * tollup)
                {
                    idr->Setcod(kICODE5); // ok Z1A2->Z2A4
                    idr->SetA(4);
                    fA = 4;
                    idr->SetZ(2);
                    fZ = 2;
                }
            } // if(fA==2)

            if (fA == 3)
            {
                if (de > 347.6 * tollup)
                {
                    idr->Setcod(kICODE5); // ok Z1A3->Z2A4
                    idr->SetA(4);
                    fA = 4;
                    idr->SetZ(2);
                    fZ = 2;
                }
                // if(fA==3 && (de>292.8*tollup) && (fPID!=3) && (idr->Getcod()<3))idr->Setcod(kICODE4);//2011
                // code...needed??????????????????????????????????? if(fA==3 && (de>292.8*tollup) && (fPID==3) &&
                // (idr->Getcod()<3))idr->Setcod(kICODE2);//2011 code...needed???????????????????????????????????
            } // if(fA==3)

            if (fA == 0)
            {
                if (de < 222.1 && de > 0)
                {
                    for (iii = 0; iii < 70; iii++)
                    {
                        if (de >= DE11[iii] && de < DE11[iii + 1])
                        {
                            erec =
                                E11[iii] + (de - DE11[iii]) / (DE11[iii + 1] - DE11[iii]) * (E11[iii + 1] - E11[iii]);
                        }
                        if (de < DE11[0])
                        {
                            erec = -100;
                            idr->Setcod(kICODE8); // ok....tbc
                        }
                        if (de > DE11[69])
                            erec = de + 1;
                    }
                    idr->SetA(1);
                    fA = 1;
                    stopped = 0;
                    idr->SetUnStopped();
                    if (idr->Getcod() < 3)
                        idr->Setcod(kICODE3); // ok...tbc
                }

                if (de > 222.1 && de < 292.8)
                {
                    for (iii = 0; iii < 45; iii++)
                    {
                        if (de >= DE12[iii] && de < DE12[iii + 1])
                        {
                            ;
                            erec =
                                E12[iii] + (de - DE12[iii]) / (DE12[iii + 1] - DE12[iii]) * (E12[iii + 1] - E12[iii]);
                        }
                        if (de < DE12[0])
                        {
                            erec = -100;
                            idr->Setcod(kICODE8); // ok....tbc
                        }
                        if (de > DE12[44])
                            erec = de + 1;
                    }
                    idr->SetA(2);
                    fA = 2;
                    stopped = 0;
                    idr->SetUnStopped();
                    if (idr->Getcod() < 3)
                        idr->Setcod(kICODE3); // ok....tbc
                }

                if (de > 292.8 && de < 347.6 * tollup)
                {
                    if (!optZ2)
                    {
                        for (iii = 0; iii < 41; iii++)
                        {
                            if (de >= DE13[iii] && de < DE13[iii + 1])
                            {
                                ;
                                erec = E13[iii] +
                                       (de - DE13[iii]) / (DE13[iii + 1] - DE13[iii]) * (E13[iii + 1] - E13[iii]);
                            }
                            if (de < DE13[0])
                            {
                                erec = -100;
                                idr->Setcod(kICODE8); // ok....tbc
                            }
                            if (de > DE13[40])
                                erec = de + 1;
                        }
                        idr->SetA(3);
                        fA = 3;
                        stopped = 0;
                        idr->SetUnStopped();
                        if (idr->Getcod() < 3)
                            idr->Setcod(kICODE3); // ok....tbc
                    }
                    else
                    {
                        idr->SetA(2);
                        idr->SetZ(2);
                        fA = 2;
                        fZ = 2;
                    }
                }

                if (de > 347.6 * tollup)
                {
                    idr->Setcod(kICODE5); // ok Z1A0->Z2A2
                    idr->SetA(2);
                    fA = 2;
                    idr->SetZ(2);
                    fZ = 2;
                }
            } // if(fA==0)
        }     // if(fZ==1)

        if (fZ == 2)
        {
            myflag = 0;
            if (fA == 3)
            {
                if (de > 792.4 * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z2A3->Z2A4
                    idr->SetA(4);
                    fA = 4;
                }
            } // if(fA==3)

            if (fA == 4)
            {
                if (de > 888.1 * tollup)
                {
                    idr->Setcod(kICODE5); // ok Z2A4->Z3A7
                    idr->SetA(7);
                    fA = 7;
                    idr->SetZ(3);
                    fA = 3;
                }
            } // if(fA==4)

            if (fA == 2)
            {
                if (de > 888.1 * tollup && myflag == 0)
                {
                    idr->Setcod(kICODE5); // ok Z2A2->Z3A5
                    idr->SetA(5);
                    fA = 5;
                    idr->SetZ(3);
                    fZ = 3;
                    stopped = 0;
                    idr->SetUnStopped();
                }
                if (de < 888.1 * tollup)
                {
                    for (iii = 0; iii < 64; iii++)
                    {
                        if (de >= DE24[iii] && de < DE24[iii + 1])
                        {
                            ;
                            erec =
                                E24[iii] + (de - DE24[iii]) / (DE24[iii + 1] - DE24[iii]) * (E24[iii + 1] - E24[iii]);
                        }
                        if (de < DE24[0])
                        {
                            erec = -100;
                            idr->Setcod(kICODE8); // ok....tbc
                        }
                        if (de > DE24[63])
                            erec = de + 1;
                    }
                    idr->SetA(4);
                    fA = 4;
                    stopped = 0;
                    idr->SetUnStopped();
                    if (idr->Getcod() < 3)
                        idr->Setcod(kICODE3); // ok...tbc
                    //     if(myflag==1)idr->Setcod(kICODE5);
                }
            } // if(fA==2)
        }     // if(fZ==2)

        if (fZ == 3)
        {
            if (fA == 6)
            {
                if (de > 1696.87 * tollup && de < 1801.49 * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z3A6->Z3A7
                    idr->SetA(7);
                    fA = 7;
                }
                if (de > 1801.49 * tollup && de < 1899. * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z3A6->Z3A8
                    idr->SetA(8);
                    fA = 8;
                }
                if (de > 1899. * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z3A6->Z4A9
                    idr->SetZ(4);
                    fZ = 4;
                    idr->SetA(8);
                    fA = 8;
                }
            } // if(fA==6)

            if (fA == 7)
            {
                if (de > 1801.49 * tollup && de < 1899. * tollup)
                {
                    idr->Setcod(kICODE4); // ok Z3A7->Z3A8
                    idr->SetA(8);
                    fA = 8;
                }
                if (de > 1899. * tollup)
                {
                    idr->Setcod(kICODE5); // ok Z3A7->Z4A9
                    idr->SetZ(4);
                    fZ = 4;
                    idr->SetA(9);
                    fA = 9;
                }
            } // if(fA==7){

            if (fA == 8)
            {
                if (de > 1899 * tollup)
                {                         // mettere valore esatto di PT
                    idr->Setcod(kICODE5); // ok Z3A8->Z4A9
                    idr->SetZ(4);
                    fA = 4;
                    idr->SetA(9);
                    fA = 9;
                }
            } // if(fA==8){

            if (fA == 5)
            {
                if (de > 1801.49 * tollup)
                {
                    idr->Setcod(kICODE5); // Z3A5->Z4A6
                    idr->SetA(6);
                    fA = 6;
                    idr->SetZ(4);
                    fZ = 4;
                }
                if (de < 1808.1 * tollup)
                {
                    for (iii = 0; iii < 69; iii++)
                    {
                        if (de >= DE37[iii] && de < DE37[iii + 1])
                        {
                            ;
                            erec =
                                E37[iii] + (de - DE37[iii]) / (DE37[iii + 1] - DE37[iii]) * (E37[iii + 1] - E37[iii]);
                        }
                        if (de < DE37[0])
                        {
                            erec = -100;
                            idr->Setcod(kICODE8);
                        }
                        if (de > DE37[68])
                            erec = de + 1;
                    }
                    idr->SetA(7);
                    fA = 7;
                    stopped = 0;
                    idr->SetUnStopped();
                    if (idr->Getcod() < 3)
                        idr->Setcod(kICODE3);
                }
            } // if(fA==5)
        }     // if(fZ==3)

        if (fZ == 4)
        {
            if (fA == 7)
            {
                if (de > 2573.71 * tollup && de < 2827.02 * tollup)
                {                         // mettere valore esatto di PT
                    idr->Setcod(kICODE4); // Z4A7->Z4A9
                    idr->SetA(9);
                    fA = 9;
                }
                if (de > 2827.02 * tollup)
                {                         // mettere valore esatto di PT
                    idr->Setcod(kICODE5); // Z4A7->Z511
                    idr->SetA(11);
                    fA = 11;
                    idr->SetZ(5);
                    fZ = 5;
                }
            } // if(fA==7)
            if (fA == 9)
            {
                if (de > 2827.02 * tollup)
                {
                    idr->Setcod(kICODE5); // Z4A9->Z5A11
                    idr->SetA(11);
                    fA = 11;
                    idr->SetZ(5);
                    fZ = 5;
                }
            } // if(fA==9)

            if (fA == 6)
            {
                if (de > 2827.02 * tollup)
                {
                    idr->Setcod(kICODE5); // Z4A6->Z5A9
                    idr->SetA(9);
                    fA = 7;
                    idr->SetZ(5);
                    fZ = 5;
                }
                if (de < 2863.9 * tollup)
                {
                    for (iii = 0; iii < 57; iii++)
                    {
                        if (de >= DE49[iii] && de < DE49[iii + 1])
                        {
                            ;
                            erec =
                                E49[iii] + (de - DE49[iii]) / (DE49[iii + 1] - DE49[iii]) * (E49[iii + 1] - E49[iii]);
                        }
                        if (de < DE49[0])
                        {
                            erec = -100;
                            idr->Setcod(kICODE8);
                        }
                        if (de > DE49[56])
                            erec = de + 1;
                    }
                    idr->SetA(9);
                    fA = 9;
                    stopped = 0;
                    idr->SetUnStopped();
                    if (idr->Getcod() < 3)
                        idr->Setcod(kICODE3);
                }
            } // if(fA==6)
        }     // if(fZ==4)

        if (fZ == 5 && fA == 7)
        {
            for (iii = 0; iii < 12; iii++)
            {
                if (de >= DE511[iii] && de < DE511[iii + 1])
                {
                    ;
                    erec = E511[iii] + (de - DE511[iii]) / (DE511[iii + 1] - DE511[iii]) * (E511[iii + 1] - E511[iii]);
                }
                if (de < DE511[0])
                {
                    erec = -100;
                    idr->Setcod(kICODE8);
                }
                if (de > DE511[11])
                    erec = de + 1;
            }
            idr->SetA(11);
            fA = 11;
            stopped = 0;
            idr->SetUnStopped();
            if (idr->Getcod() < 3)
                idr->Setcod(kICODE3);
        } // if(fZ==5 && fA==7)

        if ((idr->Getcod() == 8) && (idr->GetZ() == -1) && (slow > 2500))
        {
            if (de < 888.1)
            {
                idr->SetA(4);
                fA = 4;
                idr->SetZ(2);
                fZ = 2;
            }
            if (de > 888.1 && de < 1808.1)
            {
                idr->SetA(7);
                fA = 7;
                idr->SetZ(3);
                fZ = 3;
            }
            if (de > 1808.1 && de < 2863.9)
            {
                idr->SetA(9);
                fA = 9;
                idr->SetZ(4);
                fZ = 4;
            }
            if (de > 2863.9)
            {
                idr->SetA(11);
                fA = 11;
                idr->SetZ(5);
                fZ = 5;
            }
            idr->Setcod(kICODE6);
            idr->SetStopped();
            stopped = 1;
        }

        /*2011 code...needed?
          if(fZ==2 && fA==2 && stopped==1 && (idr->Getcod()<8)){
           //getchar();
           cout <<" 22 " << de << endl;
          }
          if(fZ==1 && fA==0 && stopped==1 && (idr->Getcod()<8)&& de>0){
           //getchar();
           cout <<" 10 " << de << endl;
          }
          if(fZ==3 && fA==3 && stopped==1 && (idr->Getcod()<8)){
           //getchar();
           cout <<" 33 " << de << endl;
          }
          if(fZ==4 && fA==4 && stopped==1 && (idr->Getcod()<8)){
           //getchar();
           cout <<" 44 " << de << endl;
          }
          if(fZ==5 && fA==5 && stopped==1 && (idr->Getcod()<8)){
           //getchar();
           cout <<" 55 " << de << endl;
          }
        */

    } // if(de>0){

    //    if(numtel == 95) cout <<"aft TCHICsIGSIEnergy:: " <<  de << " " << fast << " " << fa[numtel] << " " <<
    //    fb[numtel] << endl;

    fDE = de;
    if (stopped)
        fEnergy = fDE;
    if (!stopped)
        fEnergy = erec;
    fecod = kENER0;
}
