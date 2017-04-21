void grErr(TString input)
{
  gStyle->SetOptFit(1111);
  
  TGraphErrors *gr1 = new TGraphErrors (input);
  
  TCanvas *c1 = new TCanvas ("c1","Carica Condensatore",1500,500);
  c1->SetGridx();
  c1->SetGridy();
  
  TF1 *FitFunz = new TF1 ("f1","[0]*(1-exp(-x/[1]))");
  FitFunz->SetParameters(8,0.004);
  
  gr1->Fit("f1");
   
  gr1->Draw("AP");
  
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(0.5);
  gr1->SetTitle("Carica Condensatore");
  gr1->GetXaxis()->SetTitle("t [secondi]");
  gr1->GetYaxis()->SetTitle("V(t) [Volt]");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  
  cout<<"\nIl risultato del Fit con la funzione V(t)=V0*[1-exp(-t/RC)] è:\n";
  cout<<"V0 = "<<FitFunz->GetParameter(0)<<" +/- "<<FitFunz->GetParError(0)<<endl;
  cout<<"RC = "<<FitFunz->GetParameter(1)<<" +/- "<<FitFunz->GetParError(1)<<endl;
    
}
