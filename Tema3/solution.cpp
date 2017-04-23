/*
macro root
compile with:
root -l
.x solution.cpp 
*/


{
	
	float omega=1040; 		//velocità di rotazione
	float omega_err=10;  	//errore casuale sulla lettura della velocità
	float spost=30;			//spostamento
	float spost_err=7;		//errore casuale sullo spostamento
     
    float sum[3],sumq[3],rms[3];
 
    float stima_c2,stima_err_c2;
	float stima_c1=0, stima_err_c1=0;
	
	int Nmis=50; //numero di misure effettuate in laboratorio
	int Nesp=10000; //numero di volte in cui si ripete l'esperimento
		
	float rnd_omega,rnd_spost;
	TRandom1 *RndG1=new TRandom1();	
    TRandom1 *RndG2=new TRandom1();   
    
    //istogrammi
    int nbin=200;
	TH1F *Homega=new TH1F("Homega","omega",nbin,omega-3*omega_err/sqrt(Nmis),omega-3*omega_err/sqrt(Nmis));
    TH1F *Hspost=new TH1F("Hspost","spostamento",nbin,spost-3*spost_err/sqrt(Nmis),spost-3*spost_err/sqrt(Nmis));

	TH1F *Hc1=new TH1F("Hc1","stima c1",nbin,25,45);
	TH1F *Herr_c1=new TH1F("Herr_c1","err stima c1",nbin,0,10);

	TH1F *Hc2=new TH1F("Hc2","stima c2",nbin,25,45);
	TH1F *Herr_c2=new TH1F("Herr_c2","err stima c2",nbin,0,10);
    

    for (int k=0;k<Nesp;k++) {
	  for(int j=0;j<3;j++) {sumq[j]=0; sum[j]=0;}
      for (int j=0;j<Nmis;j++){
			rnd_omega=RndG2->Gaus(omega,omega_err);
			rnd_spost=RndG1->Gaus(spost,spost_err);
			sum[0]+=rnd_omega; //somma
			sum[1]+=rnd_spost;
			sum[2]+=rnd_omega/rnd_spost;
			sumq[0]+=pow(rnd_omega,2); //somma quadratica
			sumq[1]+=pow(rnd_spost,2);
			sumq[2]+=pow(rnd_omega/rnd_spost,2);				  
      }
      for(int j=0;j<3;j++) {
		  sum[j]/=Nmis*1.;  //valori medi
		  sumq[j]/=Nmis*1.; //valori quadratici medi	  
		  }
      for(int j=0;j<3;j++) {
		  rms[j]=sqrt(sumq[j]-sum[j]*sum[j])*sqrt((Nmis*1.)/(Nmis-1.))/sqrt(Nmis*1.);  //deviazione standard dalla media
	  }
	  
	  //c1
      stima_c1=sum[0]/sum[1];     
      stima_err_c1=stima_c1*sqrt(pow(rms[1]/sum[1],2)+pow(rms[0]/sum[0],2));
      
      //c2
      stima_c2=sum[2]; 
      stima_err_c2=rms[2]; 
      
      //istogrammi
      Homega->Fill(sum[0]); 
      Hspost->Fill(sum[1]);     
  
      Hc1->Fill(stima_c1); 
      Herr_c1->Fill(stima_err_c1);   
       
      Hc2->Fill(stima_c2);      
      Herr_c2->Fill(stima_err_c2);  
	}
	
	
  gStyle->SetOptFit(1111);
  
  TCanvas *c2 = new TCanvas("c2", "",0,330,1000,1000); 
  c2->Divide(2,3);

  c2->cd(5);
  Homega->Draw();
  Homega->Fit("gaus","L");  
  c2->cd(6);
  Hspost->Draw();
  Hspost->Fit("gaus","L");
  
  c2->cd(1);
  Hc1->Draw();
  Hc1->Fit("gaus","L");
  c2->cd(2);
  Herr_c1->Draw();
  
  c2->cd(3);
  Hc2->Draw();
  Hc2->Fit("gaus","L");
  c2->cd(4);
  Herr_c2->Draw();

  cout<<"Valore vero "<<(omega/spost)<<endl;
  cout<<"Bias c1 % Stima "<<(omega/spost-Hc1->GetMean())<<endl;
  cout<<"Bias c2 % Stima "<<(omega/spost-Hc2->GetMean())<<endl;

}