#include <iostream>
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
void demonstrate_lifetime_fit(double sigma = 0.15){

  gRandom -> SetSeed( time(NULL) ); //seed file set by time
  gStyle->SetOptStat(0);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadLeftMargin(0.10);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadBottomMargin(0.15);

  //////////////
  //parameters//
  //////////////
  int nevent = 750;
  int nbin = 50;
  double t_min = -0.5;//ns
  double t_max = 2.;//ns
  double t;
  double t0;
  double tau = 0.2;//define (lifetime)
  //double sigma = 0.15;//define (resolution)

  TH1F *h_delay = new TH1F("h_delay","h_delay",nbin, t_min, t_max);//define h_delaygram
  SetTH1(h_delay,"","Decay time[ns]",Form("counts/%.0lfps",1000*(t_max - t_min)/nbin ),1,1000,0);
  h_delay->GetYaxis()->SetTitleOffset(0.7);

  TH1F *h_respo = new TH1F("h_respo","h_respo",nbin, t_min, t_max);//define h_respogram
  SetTH1(h_respo,"","Decay time[ns]",Form("counts/%.0lfps",1000*(t_max - t_min)/nbin ),2,1000,0);

  TF1 *f,*f_gaus;
  f = new TF1("f",expgaus,-1000,3000,4);
  f->SetParNames("area","tau","sigma","mean");
  f->SetParameter(0,(double)nevent/nbin); //20 bin num.
  f->SetParameter(1,tau);  f->SetParameter(2,sigma);  f->SetParameter(3,0.);
  SetTF1(f    ,1,3,1,2000);

  f_gaus = new TF1("f","gaus",-1000,3000);
  SetTF1(f_gaus,2,3,1,2000);
  f_gaus->SetParameter(0,f->GetMaximum(-1,2));
  f_gaus->SetParameter(1,f->GetParameter(3));
  f_gaus->SetParameter(2,f->GetParameter(2));

  for(int i=0;i<nevent;i++){//loop
    t       =  gRandom -> Exp(tau);//generate random value
    t0      =  gRandom -> Gaus(0.,sigma);//generate random value
    t      += t0;
    h_respo ->Fill(t0);
    h_delay ->Fill(t);
  }


  h_delay->Fit(f,"0LL","",-0.5,2);

  TCanvas *c[2];
  for(int i=0;i<2;i++){
    c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),1600,800);
  }
  c[0]->Clear();c[0]->cd(1);
  gPad->SetLogy(1);
  h_respo->Draw("");
  h_delay->Draw("same");
  
  c[1]->Clear();c[1]->cd(1);
  gPad->SetLogy(1);
  h_respo->Draw("");
  h_delay->Draw("same");
  f->Draw("same");
  //f_gaus->Draw("same");

  //c[0]->Print("pdf/demo_life.pdf[");
  //c[0]->Print("pdf/demo_life.pdf" );
  //c[1]->Print("pdf/demo_life.pdf" );
  //c[1]->Print("pdf/demo_life.pdf]");

  double tau_ps = 1000.*tau;
  double sigma_ps = 1000.*sigma;
  c[0]->Print(Form("pdf/demo_life1_tau%d_wid%d_ev%d.png" ,(int)tau_ps,(int)sigma_ps,nevent));
  c[1]->Print(Form("pdf/demo_life2_tau%d_wid%d_ev%d.png" ,(int)tau_ps,(int)sigma_ps,nevent));

  ofstream ofs;
  if( ofs.is_open() )ofs.close(); 
  ofs.open("output.txt",ios::out|ios::trunc);
  ofs<<tau_ps<<" "<<sigma_ps<<" "<<nevent<<" "<<1000.*f->GetParError(1)<<endl;


}
