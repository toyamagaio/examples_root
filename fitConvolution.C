#include <TCanvas.h>
#include <TRandom.h>
#include <TF1Convolution.h>
#include <TF1.h>
#include <TH1F.h>
 
void fitConvolution()
{
  //Construction of histogram to fit.
  TH1F *h_ExpGauss = new TH1F("h_ExpGauss", "Exponential convoluted by Gaussian", 125, -20., 5.);
  for (int i = 0; i < 1e6; i++) {
    // Gives a alpha of -0.3 in the exp.
    double x = gRandom->Exp(-1. / 0.4);
    x += gRandom->Gaus(0., 0.5);
    // Probability density function of the addition of two variables is the
    // convolution of two density functions.
    h_ExpGauss->Fill(x);
  }
  
  TF1Convolution *f_conv = new TF1Convolution("expo", "gaus", -20, 5, true);
  f_conv->SetRange(-20., 5.);
  f_conv->SetNofPointsFFT(1000);
  TF1 *f = new TF1("f", *f_conv, 0., 5., f_conv->GetNpar());
  f->SetParameters(1., -0.3, 0., 0.5);
  
  // Fit.
  new TCanvas("c", "c", 800, 1000);
  h_ExpGauss->Fit("f");
  h_ExpGauss->Draw();
}
