 
#include "TH1.h"
#include "TF1.h"
#include "TLine.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#ifndef __CINT__
#include "Math/DistFunc.h"  
#endif


void Gauss_vs_Student()
{ 
   double ndf=3.;
   cout<<"Numero di gradi di liberà "<<endl;
   cin>>ndf;
   gSystem->Load("libMathMore");	
   double a=-5.;
   double b=5.;	
	
   TF1* pdfStudent = new TF1("pdfStudent", "ROOT::Math::tdistribution_pdf(x,[0])", a,b);
   pdfStudent->SetParameter(0,ndf);
   TF1* pdfGauss = new TF1("pdfGauss", "ROOT::Math::normal_pdf(x,[0],[1])", a,b);
   pdfGauss->SetParameter(1,0);
   pdfGauss->SetParameter(0,1);
   TF1 *pdfdiff = new TF1 ("pdfdiff", "pdfStudent-pdfGauss",a,b);


   TF1* cdfStudent = new TF1("cdfStudent", "ROOT::Math::tdistribution_cdf(x,[0])", a,b);
   cdfStudent->SetParameter(0,ndf);
   TF1* cdfGauss = new TF1("cdfGauss", "ROOT::Math::normal_cdf(x,[0],[1])", a,b);
   cdfGauss->SetParameter(1,0); // [1] = media
   cdfGauss->SetParameter(0,1); // [0] = sigma
   TF1 *cdfdiff = new TF1 ("cdfdiff", "cdfStudent-cdfGauss",a,b);


   
   
   TCanvas *Canvas = new TCanvas("DistCanvas", "Student Distribution graphs", 10, 10, 1000, 800);
   pdfStudent->SetTitle("Student t distribution function");
   Canvas->Divide(2, 2);
   Canvas->cd(1);
   pdfStudent->SetLineWidth(2);
   pdfStudent->DrawCopy();
   pdfGauss->SetLineColor(4);
   pdfGauss->SetLineWidth(2);
   pdfGauss->DrawCopy("same");
   
   Canvas->cd(2);   
   pdfdiff->SetLineWidth(2);
   pdfdiff->SetLineColor(3);
   pdfdiff->DrawCopy();
   
   Canvas->cd(3);
   cdfStudent->SetLineWidth(2);
   cdfStudent->DrawCopy();
   cdfGauss->SetLineColor(4);
   cdfGauss->SetLineWidth(2);
   cdfGauss->DrawCopy("same");
   TLine linea(a,0.5,b,0.5);  
   linea.SetLineWidth(2);
   linea.SetLineColor(1);
   linea.DrawClone("same");
    
   TBox box34(a,0.16,b,0.84);
   box34.SetFillStyle(3001);
   box34.SetFillColor(5);
   box34.DrawClone("same");
   
  
   Canvas->cd(4);
   
   cdfdiff->SetLineWidth(2);
   cdfdiff->SetLineColor(3);
   cdfdiff->DrawCopy();
   
 }
