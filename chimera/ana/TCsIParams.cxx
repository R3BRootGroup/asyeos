//TCsIParams
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// generic constructor for a single telescope 

#include "TCsIParams.h"

TCsIParams::TCsIParams(int ntel,int ring, int nlign, int *iz, 
            int *im, int *np, int *inode, int num, float *xc, float *yc)
{
 ftel = ntel;
 fring = ring;
 fln = nlign;
 fpoints = num;
 fbittel = 0;  

 fiz= new int[nlign];
 fim= new int[nlign];
 fnp= new int[nlign]; 
 fptrgap= new int[nlign];
 fgap = new int[nlign];

 for(int i=0; i<nlign; i++) {
  fiz[i] = iz[i];
  fim[i] = im[i];
  fnp[i] = np[i];
  fptrgap[i] = inode[i];  
  if(fiz[i]>0 && fim[i]>0) {               //gammas are not included in the pattern
   fbittel |= 1 << TABZM[fiz[i]][fim[i]];  //bit pattern of identified particles
  }
 }

 fcx = new float[num];
 fcy = new float[num];
 fcsFoff=0; 
 fcsSoff=0;
 fcsFgain=1;
 fcsSgain=1;
 for(int i=0; i<num; i++) {
  fcx[i] = (int)(xc[i]*4.0+0.5);  //original values are multiplied by 4   
  fcy[i] = (int)(yc[i]*4.0+0.5);
 }

//Finally, it calculates the line distances filling the data "fgap"
 CalculateLineDistance();
}

//a copy constructor is defined for this class 
TCsIParams::TCsIParams(const TCsIParams &other) : ftel(other.ftel), fring(other.fring), 
                                                  fln(other.fln), fbittel(other.fbittel),
                                                  fpoints(other.fpoints)
{
 fiz= new int[fln];
 fim= new int[fln];
 fnp= new int[fln]; 
 fptrgap= new int[fln]; 
 fcx = new float[fpoints];
 fcy = new float[fpoints]; 
 for(int i=0; i<fln; i++) {
  fiz[i] = other.fiz[i];
  fim[i] = other.fim[i];
  fnp[i] = other.fnp[i];
  fptrgap[i] = other.fptrgap[i]; 
  fgap[i] = other.fgap[i];
 } 
 for(int i=0; i<fpoints; i++) {
  fcx[i] = other.fcx[i];
  fcy[i] = other.fcy[i];
 }  
}

//Destructor 
TCsIParams::~TCsIParams()
{
 delete [] fcx;
 delete [] fcy;
 delete [] fptrgap;
 delete [] fiz;
 delete [] fim;
 delete [] fnp;
 delete [] fgap;
}

//Print data for an existing CsI grid  
void TCsIParams::PrintData()
{
 if(fln==0)return;
 cout<<setw(5)<<fring<<setw(5)<<ftel<<endl;
 cout<<setw(5)<<fln<<endl;
 for(int k=0; k<fln; k++) {
   cout << setw(5) << fiz[k] << setw(5) << fim[k] << setw(5) << fnp[k] <<endl;
 }

 int mod = 5;
 int j=1;
 cout.setf(ios::fixed);
 cout<<setprecision(1);
 for(int k=0; k<fpoints; k++) {
  if(mod==0) {
   cout<<endl;
   mod=5;
  }
  cout<<right<<setw(8)<<fcx[k]<<setw(8)<<fcy[k];
  if(k==fptrgap[j]-1) {
   cout<< " &&"<<endl;
   j++;
   mod=5;
  }
  else 
   mod--;   
 }
 if(mod!=0)
  cout<<endl;
 else 
  cout<<endl;
}

//calculate the line distance (private function)
void TCsIParams::CalculateLineDistance()
{
 float x1,y1,x2,y2,x3,y3;

 for(int k=0; k<fln; k++) {
  if(k != (fln-1) && fiz[k]==fiz[k+1]) {
   int ia1, ia2;
   for(int nl=-1; nl<=1; nl+=2) {
    int next = k+1;
    if(nl>0) {
     ia1 = fptrgap[k] + fnp[k] - 1;       //final point 
     ia2 = fptrgap[next] + fnp[next] - 1;
    }
    else {
     ia1 = fptrgap[k];                   //start point
     ia2 = fptrgap[next]; 
    }
    x1 = fcx[ia1];
    y1 = fcy[ia1];
    x2 = fcx[ia2];
    y2 = fcy[ia2];    
    if((x1-x2)*nl > 0) {
      next = k;
      x1 = x2;
      y1 = y2;
    }
    if(nl > 0) 
     ia2 = fptrgap[next+1] - 2;
    else
     ia2 = fptrgap[next] + 1; 
    while((fcx[ia2]-x1)*nl >= 0) {
     ia2 = ia2 - nl;
    }
    x3 = fcx[ia2 + nl];
    y3 = fcy[ia2 + nl];
    float ac = (fcy[ia2] - y3) / (fcx[ia2]-x3);
    float dist = fabs(ac * (x1-x3) + (y3-y1));

    if(nl < 0) {
     dist = dist * 3.0;
     fgap[k] = round(dist);
    }
    else {
     float ig = fgap[k];
     fgap[k] = fmin(ig, round(dist));
    }
   }  //for(int nl=
  } //if(k != 
  else if(k>0 && fiz[k] == fiz[k-1]) {
   fgap[k] = fgap[k-1];
  }
  else {
   fgap[k] = 16000;
  }
 // cout<<ftel<<" "<<k<<" "<<fgap[k]<<endl;
 } //for(int k=
}  
