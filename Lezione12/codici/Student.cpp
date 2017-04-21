#include <math.h> 
#include <iostream>
#include <fstream>
#include "TF1.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TApplication.h"



using namespace std;

double const pi=3.1415926535897;

//c++  Student.cpp  `root-config --cflags --glibs` -o Student

double MyGauss (double *x, double *par){

        //par[0] = posizione 
  		//par[1] = sigma => fhwm = par[2]*2.35
        double fval = 0;   
        if(par[1]>0) { 
					fval = (x[0]-par[0])/par[1];
					fval = 1/sqrt(2*pi)/par[1] * TMath::Exp(-0.5*fval*fval);
					}
        return fval;
}


double MyStudent (double *x, double *par){
    		
        double enne=par[0];  //par[0] = numero gradi libertà  
        double fval = 1/sqrt(pi*par[0])*tgamma((enne+1)/2)/tgamma(enne/2);
        fval = fval*pow(1+x[0]*x[0]/enne,-1*(enne+1)/2);
        return fval;
}

// Sum of background and peak function
double MyDiff(double *x, double *par) {
       return MyStudent(x,par) - MyGauss(x,&par[1]);
}


int main(int argc, char **argv) { 
	
   TApplication *myApp= new TApplication("myApp", &argc, argv);
	
   double ndf,media=0,varianza=0,valore;
   
   cout<<"Numero di misure effettuate "<<endl;
   cin>>ndf;
   
   for (int i=1;i<ndf+1;i++) {
	     cout<<"Misura "<<i<<") ";
         cin>>valore;
		 media+=valore;
		 varianza+=valore*valore;   
	   }
   media=media/ndf;
   varianza=(varianza-media*media*ndf)/(ndf-1);   //estimatore unbiased per la varianza   
	   
    
   cout<<endl<<"Media campionaria delle misure effettuate "<<media<<endl;
   cout<<"Deviazione standard delle misure effettuate "<<sqrt(varianza)<<endl;
   double stdevm=sqrt(varianza/ndf);
   cout<<"Deviazione standard dalla media delle misure effettuate "<<stdevm<<endl;

	
   double a=-5.;
   double b=5.;	
   int nbin=1000;
   double step=(b-a)/nbin;
   double *x=new double;
   double *par=new double;	
 
   TH1F *histoStudent=new TH1F("histoStudent","pdf Student",nbin,a,b);
   TH1F *cdfStudent=new TH1F("cdfStudent","cdf Student",nbin,a,b);
   for (int i=1;i<nbin;i++){
	   x[0]=i*step+a;
	   par[0]=ndf-1;
	   histoStudent->SetBinContent(i,MyStudent(x,par));
	   if(i>1) cdfStudent->SetBinContent(i,cdfStudent->GetBinContent(i-1)+MyStudent(x,par)*step);
	   else cdfStudent->SetBinContent(i,0);
	   } 
	   
   TH1F *histoGauss=new TH1F("histoGauss","pdf Gauss",nbin,a,b);
   TH1F *cdfGauss=new TH1F("cdfGauss","cdf Gauss",nbin,a,b);
   for (int i=1;i<nbin;i++){
	   x[0]=i*step+a;
	   par[0]=0; //media della gaussiana
	   par[1]=1; //sigma della gaussiana
	   histoGauss->SetBinContent(i,MyGauss(x,par));
	   if(i>1) cdfGauss->SetBinContent(i,(cdfGauss->GetBinContent(i-1)+MyGauss(x,par)*step));
	   else cdfGauss->SetBinContent(i,0);
	   }
   
   TH1F *histoDiff=new TH1F("histoDiff","pdf Diff",nbin,a,b);
   for (int i=1;i<nbin;i++){
	   histoDiff->SetBinContent(i,(histoStudent->GetBinContent(i)-histoGauss->GetBinContent(i)));
	   }
	   
	   
   TCanvas *MyCanvas = new TCanvas("MyCanvas", "Student Distribution ", 10, 10, 1000, 400);
   MyCanvas->Divide(3, 1);
   
   MyCanvas->cd(1);
   histoGauss->SetLineColor(4);
   histoGauss->SetLineWidth(2);
   histoGauss->DrawCopy();
   histoStudent->SetLineColor(2);
   histoStudent->SetLineWidth(2);
   histoStudent->DrawCopy("same");
   
   
   MyCanvas->cd(2);  
   // disegno la differenza tra le due pdf 
   histoDiff->SetLineWidth(2);
   histoDiff->SetLineColor(3);
   histoDiff->DrawCopy(); 
   
   MyCanvas->cd(3);
   cdfGauss->SetLineColor(4);
   cdfGauss->SetLineWidth(2);
   cdfGauss->DrawCopy();
   cdfStudent->SetLineColor(2);
   cdfStudent->SetLineWidth(2);
   cdfStudent->DrawCopy("same");
   
  
   
   TF1* pdfStudent = new TF1("pdfStudent", MyStudent, a,b,1);
   pdfStudent->SetParameter(0,ndf-1);
   TF1* pdfGauss = new TF1("NpdfGauss", MyGauss, a,b,2);  
   pdfGauss->SetParameter(0,0); //media della gaussiana
   pdfGauss->SetParameter(1,1); //sigma della gaussiana
    
   
   TF1 *pdfdiff = new TF1 ("pdfdiff", MyDiff,a,b,3);
   pdfdiff->SetParameter(0,ndf-1);
   pdfdiff->SetParameter(1,0); //media della gaussiana
   pdfdiff->SetParameter(2,1); //sigma della gaussiana
   
   
   
   TCanvas *Canvas = new TCanvas("DistCanvas", "Student Distribution graphs", 10, 10, 1000, 400);
   Canvas->Divide(3, 1);
   
   Canvas->cd(1);
   // qui disegno le due distribuzioni Student e Gaussiana relative alla variabile normalizzata
   // (x-media)/stdevm
   pdfGauss->SetLineColor(4);
   pdfGauss->SetLineWidth(2);
   pdfGauss->DrawCopy();
   pdfStudent->SetLineWidth(2);
   pdfStudent->DrawCopy("same");
    
   Canvas->cd(2);  
   // disegno la differenza tra le due pdf 
   pdfdiff->SetLineWidth(2);
   pdfdiff->SetLineColor(3);
   pdfdiff->DrawCopy();
   
   Canvas->cd(3);
   // uso il metodo che mi restituisce l'integrale
   TGraph *gStudent = (TGraph*)pdfStudent->DrawIntegral("AL");
   TGraph *gGauss = (TGraph*)pdfGauss->DrawIntegral("L");

   cout<<"Intervallo di confidenza al 68% associato alla mia misura secondo Gauss "<<media-stdevm<<" - "<<media+stdevm<<endl;

  //calcolo t associato al 68%
   double t,probab;
   for(int i=0;i<nbin;i++) {
	   t=i*step+a;
	   probab=cdfStudent->GetBinContent(i);
	   //~ if ((gStudent->Eval(t)-gStudent->Eval(-t))>0.682) exit;
	   cout<<i<<" "<<probab<<" "<<t<<endl;
	   if ( probab>0.159 ) break;
	      
	   }
  cout<<t<<endl;

   cout<<"Intervallo di confidenza al 68% associato alla mia misura secondo Student "<<media+t*stdevm<<" - "<<media-t*stdevm<<endl;
    
  
   
   myApp->Run();
 }
