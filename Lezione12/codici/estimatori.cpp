#include<iostream>
#include<ctime>
#include<cmath>
#include"TCanvas.h"
#include"TH1F.h"
#include"TH1D.h"
#include"THStack.h"
#include"TApplication.h"
#include"TMath.h"
#include <string>

using namespace std;
double mu=10;

//c++  estimatori.cpp  `root-config --cflags --glibs` -o estimatori


//funzione poissoniana centrata in 10
double poissoniana(double x){
		double arg;
		arg= TMath::Poisson(x,mu);
        return arg;
        }

//funzione gaussiana centrata in zero e con larghezza 1
double gaussiana(double x){
		double arg;
		arg= 1/sqrt(2*TMath::Pi())* exp(-0.5*x*x);
        return arg;
        }

// funzione che genera numeri casuali in un determinato range con distribuzione piatta
double rand_range (double min, double max) {
        //srand(time(NULL));
        return (min + rand()/(RAND_MAX * 1.) * (max-min));
        }

// funzione che genera numeri casuali in un determinato range distribuiti secondo f(x)
// try and catch
double rand_TAC (double f (double), double xmin, double xmax, double ymax, double ymin) {
        double numx, numy;
        do{
        numx = rand_range (xmin, xmax);
        numy = rand_range (ymin, ymax);                                                                         
        } while (numy>f(numx));                                                                               
        return numx;                                                                                          
	} 
 
int main(int argc, char **argv) {
		
	int Nlanci=1000;	
	int Nesperimenti=200;
	double numero;
	double media, mediana, moda;
	double min=0,max=50;
	int nbin=5000,bin_moda=0,nnbin=1000;

	int tipo=1;
	
	if (argc>1) {	
				   tipo=atoi(argv[1]);					
				}
	 else 		{	cout<<"Usage: estimatori tipo "<<endl; 
					cout<<"       tipo=1 gaussiana"<<endl;
					cout<<"       tipo=1 poissoniana"<<endl;
					exit(1); 					
				}
	string funzione;
	if (tipo==2) {	funzione="poissoniana";
					min=0,max=30;
				 }
	else {	funzione="gaussiana";
			min=-10,max=10;
		 }
	cout<<"Estrazioni da "<<funzione<<endl;
	
	
	TApplication theApp("App", &argc, argv);
	TCanvas *c1 = new TCanvas("c1","c1",10,10,600,400); 
	c1->Divide(2,1);
	c1->cd(1);
	
	
	THStack *StackMedia= new THStack("StackMedia","StackMedia");
	
	TH1D *histo_media = new TH1D("hmedia","histo media",nnbin,min,max);
	histo_media->SetLineColor(1);
	TH1D *histo_mediana = new TH1D("hmediana","histo mediana",nnbin,min,max);
	histo_mediana->SetLineColor(2);
	TH1D *histo_moda = new TH1D("hmoda","histo moda",nnbin,min,max);
	histo_moda->SetLineColor(3);
	

	for (int j=0; j<Nesperimenti; j++) {
		TH1D *histo = new TH1D("h","histo ",nbin,min,max);
		for (int i=0; i<Nlanci; i++){
			if (tipo==2) numero=rand_TAC(poissoniana,min,max,0,1);
			else numero=rand_TAC(gaussiana,min,max,0,1);
			media+=numero;
			histo->Fill(numero);				
		}
		media=media/Nlanci;
		
		//calcolo approssimativamente la mediana
		mediana=histo->GetBinContent(0);
		int i=0;	
		while (mediana<Nlanci/2) {
				i++;
				mediana+=histo->GetBinContent(i);	
		}	
		mediana=(i*1.-0.5)/nbin*(max-min)+min;	
		
		//calcolo approssimativamente la moda
		histo->Rebin(10);
		moda=histo->GetBinContent(0);	
		for	(int i=1; i<(nbin/10); i++) {
			if (histo->GetBinContent(i)>moda) {
				moda=histo->GetBinContent(i);	
				bin_moda=i;
			}	
		}
		moda=(bin_moda*1.-0.5)/nbin*10*(max-min)+min;	
		
		//riempio gli istogrammi
		histo_media->Fill(media);
		histo_mediana->Fill(mediana);
		histo_moda->Fill(moda);
		
		//disegno le distribuzioni dei miei primi 10 esperimenti
		histo->Rebin(5);
		if (j==0) histo->DrawCopy();
		if (j>0 && j<10) {
			histo->SetLineColor(j+2); 
			histo->DrawCopy("same");
		}
		delete histo;
		
	}
	c1->cd(2);
	StackMedia->Add(histo_media);
	StackMedia->Add(histo_mediana);
	StackMedia->Add(histo_moda);
	StackMedia->Draw("histo nostack");
	
	
	theApp.Run();
	
	return 0;
	
	}                                                                                                     
           
           
