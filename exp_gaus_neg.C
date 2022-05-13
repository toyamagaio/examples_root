//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double expgaus_neg(double *x, double *par) {
  //par[0]=Total area
  //par[1]=tau of exp function
  //par[2]=Width (sigma) of convoluted Gaussian function
  //par[3]=Shift of Function Peak
  double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
  double np = 500.0;      // number of convolution steps
  double sc =   8.0;      // convolution extends to +-sc Gaussian sigmas
  double xx, fland, sum = 0.0, xlow, xupp, step, i;
  double val;

// Range of convolution integral
  xlow = x[0] - sc * par[2];
  xupp = 0.;
  step = (xupp-xlow) / np;
// Convolution integral
  for(i=1.0; i<=np/2; i++){
     xx = xlow + (i-0.5) * step - par[3];
     fland = TMath::Gaus(xx,x[0],par[2]);
     sum += fland * TMath::Exp( xx/par[1]);

     xx = xupp - (i-.5) * step - par[3];
     fland = TMath::Gaus(xx,x[0],par[2]);
     sum += fland * TMath::Exp( xx/par[1]);
  }
//  val = par[2] * step * sum * invsq2pi / par[3];
  val = par[0] * step * sum * invsq2pi / (par[2]*par[1]*exp(par[3]/par[1]));

  return val;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double expgaus(double *x, double *par) {
  //par[0]=Total area
  //par[1]=tau of exp function
  //par[2]=Width (sigma) of convoluted Gaussian function
  //par[3]=Shift of Function Peak
  double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
  double np = 500.0;      // number of convolution steps
  double sc =   8.0;      // convolution extends to +-sc Gaussian sigmas
  double xx, fland, sum = 0.0, xlow, xupp, step, i;
  double val;

// Range of convolution integral
  xlow = 0.;
  xupp = x[0] + sc * par[2];
  step = (xupp-xlow) / np;
// Convolution integral
  for(i=1.0; i<=np/2; i++){
     xx = xlow + (i-0.5) * step - par[3];
     fland = TMath::Gaus(xx,x[0],par[2]);
     sum += fland * TMath::Exp(-xx/par[1]);

     xx = xupp - (i-.5) * step - par[3];
     fland = TMath::Gaus(xx,x[0],par[2]);
     sum += fland * TMath::Exp(-xx/par[1]);
  }
//  val = par[2] * step * sum * invsq2pi / par[3];
  val = par[0] * step * sum * invsq2pi / (par[2]*par[1]*exp(par[3]/par[1]));

  return val;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetTF1(TF1 *f, int LColor=2, int LWidth=0, int LStyle=1, int Npx=1000){
  f->SetLineColor(LColor);
  f->SetLineWidth(LWidth);
  f->SetLineStyle(LStyle);
  f->SetNpx(Npx);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void exp_gaus_neg(){

gRandom -> SetSeed( time(NULL) ); //seed file set by time
gStyle->SetOptStat(0);

TH1F *hist = new TH1F("hist","hist",50, -2.5, 1.0);//define histgram
  hist->SetTitle("");
  hist->SetLineColor(4);
  hist->SetLineWidth(1);
  hist->GetXaxis()->SetTitle("Decay time[ns]");
  hist->GetYaxis()->SetTitle("counts/50ps");

  double t;
  double tau = 0.2;//define (lifetime)
  double sigma = 0.1;//define (resolution)
  for(int i=0;i<1000;i++){//loop
    t       =  -1*gRandom -> Exp(tau);//generate random value
    t      +=     gRandom -> Gaus(0.,sigma);//generate random value
    hist ->Fill(t);
  }

  TF1 *f,*f_gaus;
  f = new TF1("f",expgaus_neg,-1000,3000,4);
  f->SetParNames("area","tau","sigma","mean");
  f->SetParameter(0,1000/50.); //20 bin num.
  f->SetParameter(1,tau);  f->SetParameter(2,sigma);  f->SetParameter(3,0.);
  SetTF1(f    ,1,3,1,2000);

  f_gaus = new TF1("f","gaus",-1000,3000);
  SetTF1(f_gaus,2,3,1,2000);
  f_gaus->SetParameter(0,f->GetMaximum(-1,2));
  f_gaus->SetParameter(1,f->GetParameter(3));
  f_gaus->SetParameter(2,f->GetParameter(2));

  //hist->Fit(f,"0LL","",-0.5,2);

  TCanvas *c1 = new TCanvas("c1","c1",800,1000);
  c1->Clear();
  c1->Divide(1,2);
  c1->cd(1);
  gPad->SetLogy(1);
  hist->Draw();
  f->Draw("same");
  c1->cd(2);
  f->Draw("AL");
  //f_gaus->Draw("same");

}
