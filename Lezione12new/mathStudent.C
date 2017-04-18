/// \file
/// \ingroup tutorial_math
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include <Riostream.h>
#include "TLegend.h"
#include "TLegendEntry.h"

void mathChi()
{
   
   TCanvas *c1 = new TCanvas("c1", "", 10, 10, 800, 650);



   TF1* chi = new TF1("chi", "TMath::Gamma(n/2,1/2)", -5, 5);
   chi->Draw();

 
}
