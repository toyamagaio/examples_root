const double PI = 4.*atan(1.);
const double deg_to_rad = PI / 180.;
const double rad_to_deg = 180. / PI;
const double sigma_to_fwhm = 2.*sqrt(2.*log(2.));
const double fwhm_to_sigma = 1./sigma_to_fwhm;
const double cm_to_barn = 1e+24;
const double alpha = 1./137.035999074; // fine structure constant
const double hbar = 6.58211928*1e-22;  // Planc constant (reduced) (MeV x s)
const double hbarc = 197.3269718;      // conversion constant (MeV x fm)
const double kb = 8.6173324*1e-5;      // Boltzmann constant
const double e = 1.602176565*1e-19;    // electron charge magnitude (C)
const double c = 0.299792458;          // speed of light in vacuum (m/ns)
const double re = 2.817e-13;           // classical electron radius (cm)
const double Na = 6.02214129*1e+23;    // Avogadro constant
const double Me = 0.510998928;         // electron     mass (MeV/c2)
const double Mmu = 105.6583715;        // muon         mass (MeV/c2)
const double Mpi = 139.57018;          // charged pion mass (MeV/c2)
const double Mpi0 = 134.9766;          // charged pion mass (MeV/c2)
const double MK = 493.677;             // charged Kaon mass (MeV/c2)
const double Mp = 938.272046;          // proton       mass (MeV/c2)
const double Mn = 939.565379;          // proton       mass (MeV/c2)
const double Mu = 931.494061;          // proton       mass (MeV/c2)
const double ML = 1115.683;            // Lambda       mass (MeV/c2)
const double MS0 = 1192.642;           // Sigma Zero   mass (MeV/c2)
const double MSm = 1197.449;           // Sigma Minus  mass (MeV/c2)
const double MSp = 1189.37;            // Sigma Plus   mass (MeV/c2)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetTH1(TH1 *h, TString name, TString xname, TString yname, int LColor=1, int FStyle=0, int FColor=0){
  h->SetTitle(name);
  h->SetLineColor(LColor);
  h->SetLineWidth(2);
  h->SetFillStyle(FStyle);
  h->SetFillColor(FColor);
  h->SetTitleSize(0.06,"x");
  h->SetTitleSize(0.06,"y");

  h->GetXaxis()->SetTitle(xname);
  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetTitleOffset(1.10);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelOffset(0.01);
  ((TGaxis*)h->GetXaxis())->SetMaxDigits(4);

  h->GetYaxis()->SetTitle(yname);
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleOffset(1.4);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelOffset(0.01);
  ((TGaxis*)h->GetYaxis())->SetMaxDigits(3);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetTH2(TH2 *h, TString name, TString xname, TString yname, double min=0.8){
  h->SetTitle(name);
  //h->SetMinimum(min);
  h->SetLineWidth(1);
  h->SetTitleSize(0.05,"");
  h->SetTitleSize(0.06,"x");
  h->SetTitleSize(0.06,"y");
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.5);
  h->SetMarkerColor(1);

  h->GetXaxis()->SetTitle(xname);
//  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetTitleOffset(0.90);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelOffset(0.01);
  h->GetXaxis()->SetLabelSize(0.05);

  h->GetYaxis()->SetTitle(yname);
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleOffset(1.10);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelOffset(0.01);
  h->GetYaxis()->SetLabelSize(0.045);
  ((TGaxis*)h->GetYaxis())->SetMaxDigits(3);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetGr(TGraph *gr, TString name, TString xname, TString yname, int LColor=1, int LWidth=1, int LStyle=1, int MColor=1, int MStyle=20, double MSize=1.){
  gr->SetTitle(name);
  gr->SetName(name);

  gr->GetXaxis()->SetTitle(xname);
  gr->GetXaxis()->CenterTitle();
  gr->GetXaxis()->SetTitleFont(42);
  gr->GetXaxis()->SetTitleOffset(1.20);
  gr->GetXaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetLabelFont(42);
  gr->GetXaxis()->SetLabelOffset(0.01);

  gr->GetYaxis()->SetTitle(yname);
  gr->GetYaxis()->CenterTitle();
  gr->GetYaxis()->SetTitleFont(42);
  gr->GetYaxis()->SetTitleOffset(1.50);
  gr->GetYaxis()->SetTitleSize(0.04);
  gr->GetYaxis()->SetLabelFont(42);
  gr->GetYaxis()->SetLabelOffset(0.01);
  ((TGaxis*)gr->GetYaxis())->SetMaxDigits(3);

  gr->SetLineColor(LColor);
  gr->SetLineStyle(LStyle);
  gr->SetLineWidth(LWidth);
  gr->SetMarkerStyle(MStyle);
  gr->SetMarkerColor(MColor);
  gr->SetMarkerSize(MSize);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetGr(TGraphErrors *gr, TString name, TString xname, TString yname, int LColor=1, int LWidth=1, int LStyle=1, int MColor=1, int MStyle=20, double MSize=1.){
  gr->SetTitle(name);
  gr->SetName(name);

  gr->GetXaxis()->SetTitle(xname);
  gr->GetXaxis()->CenterTitle();
  gr->GetXaxis()->SetTitleFont(42);
  gr->GetXaxis()->SetTitleOffset(1.20);
  gr->GetXaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetLabelFont(42);
  gr->GetXaxis()->SetLabelOffset(0.01);

  gr->GetYaxis()->SetTitle(yname);
  gr->GetYaxis()->CenterTitle();
  gr->GetYaxis()->SetTitleFont(42);
  gr->GetYaxis()->SetTitleOffset(1.50);
  gr->GetYaxis()->SetTitleSize(0.04);
  gr->GetYaxis()->SetLabelFont(42);
  gr->GetYaxis()->SetLabelOffset(0.01);
  ((TGaxis*)gr->GetYaxis())->SetMaxDigits(3);

  gr->SetLineColor(LColor);
  gr->SetLineStyle(LStyle);
  gr->SetLineWidth(LWidth);
  gr->SetMarkerStyle(MStyle);
  gr->SetMarkerColor(MColor);
  gr->SetMarkerSize(MSize);
}
//____________________________________________________________________________________________
void SetTF1(TF1 *f, int LColor, int LStyle,double LWidth){
  f->SetLineColor(LColor);
  f->SetLineStyle(LStyle);
  f->SetLineWidth(LWidth);
  f->SetNpx(2000);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetGr(TGraphAsymmErrors *gr, TString name, TString xname, TString yname, int LColor=1, int LWidth=1, int LStyle=1, int MColor=1, int MStyle=20, double MSize=1.){
  gr->SetTitle(name);
  gr->SetName(name);

  gr->GetXaxis()->SetTitle(xname);
  gr->GetXaxis()->CenterTitle();
  gr->GetXaxis()->SetTitleFont(42);
  gr->GetXaxis()->SetTitleOffset(1.20);
  gr->GetXaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetLabelFont(42);
  gr->GetXaxis()->SetLabelOffset(0.01);

  gr->GetYaxis()->SetTitle(yname);
  gr->GetYaxis()->CenterTitle();
  gr->GetYaxis()->SetTitleFont(42);
  gr->GetYaxis()->SetTitleOffset(1.50);
  gr->GetYaxis()->SetTitleSize(0.04);
  gr->GetYaxis()->SetLabelFont(42);
  gr->GetYaxis()->SetLabelOffset(0.01);
  ((TGaxis*)gr->GetYaxis())->SetMaxDigits(3);

  gr->SetLineColor(LColor);
  gr->SetLineStyle(LStyle);
  gr->SetLineWidth(LWidth);
  gr->SetMarkerStyle(MStyle);
  gr->SetMarkerColor(MColor);
  gr->SetMarkerSize(MSize);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void BinLogX(TH2 *h){
   TAxis *axis = h->GetXaxis(); 
   int bins = axis->GetNbins();
   Axis_t from = axis->GetXmin();
   Axis_t to = axis->GetXmax();
   Axis_t width = (to - from) / bins;
   Axis_t *new_bins = new Axis_t[bins + 1];
   for (int i=0;i<=bins;i++){ new_bins[i] = TMath::Power(10,from + i*width); }
   axis->Set(bins, new_bins);
   delete[] new_bins; 
}  

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void BinLogY(TH2 *h){
   TAxis *axis = h->GetYaxis(); 
   int bins = axis->GetNbins();
   Axis_t from = axis->GetXmin();
   Axis_t to = axis->GetXmax();
   Axis_t width = (to - from) / bins;
   Axis_t *new_bins = new Axis_t[bins + 1];
   for (int i=0;i<=bins;i++){ new_bins[i] = TMath::Power(10,from + i*width); }
   axis->Set(bins, new_bins);
   delete[] new_bins;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double landaugaus(double *x, double *par) {
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
  double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
  double mpshift  = -0.22278298;       // Landau maximum location
  double np = 100.0;      // number of convolution steps
  double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas
  double xx, mpc, fland, sum = 0.0, xlow,xupp, step, i;
  double val;

// MP shift correction
  mpc = par[1] - mpshift * par[0];
// Range of convolution integral
  xlow = x[0] - sc * par[3];
  xupp = x[0] + sc * par[3];
  step = (xupp-xlow) / np;
// Convolution integral of Landau and Gaussian by sum
  for(i=1.0; i<=np/2; i++) {
     xx = xlow + (i-.5) * step;
     fland = TMath::Landau(xx,mpc,par[0]) / par[0];
     sum += fland * TMath::Gaus(x[0],xx,par[3]);

     xx = xupp - (i-.5) * step;
     fland = TMath::Landau(xx,mpc,par[0]) / par[0];
     sum += fland * TMath::Gaus(x[0],xx,par[3]);
  }
  val = par[2] * step * sum * invsq2pi / par[3];

  return val;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double landaugaus_pol0(double *x, double *par) {
  return landaugaus(x,par) + par[4];
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double landaugaus_pol1(double *x, double *par) {
  return landaugaus(x,par) + par[4] + par[5]*x[0];
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double landaugaus_pol2(double *x, double *par) {
  return landaugaus(x,par) + par[4] + par[5]*x[0] + par[6]*x[0]*x[0];
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//struct Vavilov_Func {  //cannot use old version
//   Vavilov_Func() {}
//
//   double operator() (const double *x, const double *p) {
//      double kappa = p[0];
//      double beta2 = p[1];
//      return p[4]*( pdf.Pdf( (x[0]-p[2])/p[3], kappa,beta2) );
//   }
//
//   ROOT::Math::VavilovAccurate pdf;
//};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// double Vavilov(double *x, double *par){  //cannot use old version
//   ROOT::Math::VavilovAccurate pdf;
// //  double val = par[2]*TMath::Vavilov((x[0]-par[3]),par[0],par[1]);
//   double val = par[4]*( pdf.Pdf((x[0]-par[2])/par[3],par[0],par[1]));
//   return val;
// }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double Fermi(double *x, double *par){
  // par[0]=Cliff Pos(x[0]/par[0]==1)) (should be > 0)
  // par[1]=Shape parameter
  // par[2]=Scale factor (should be > 0)
  double val = par[2] * ( 1. / ( exp((x[0]-par[0])/par[1]) + 1. ) );
  return val;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double Pois( double *x, double *par )
{
//  par[0] : lambda, average of #photon
//  par[1] : energy resolution factor
//  par[2] : menseki
  double val = 0;
  for( int np=1; np<500; np++ ){
    double pois;
    double sigma = par[1]*sqrt(np);
    if(np<50){
      pois = par[2]*pow( par[0], np )*exp(-par[0])/TMath::Gamma(np+1);
    }
    else{ // stirling's approximation
      pois = par[2]*pow( par[0]/np, np )*exp(-par[0]+np)/(sqrt(2.*PI)*pow(np,0.5));
    }
    val += pois/(sqrt(2.*PI)*sigma)*exp( -pow(x[0]-np,2)/2./sigma/sigma ); // adding gaussian distribution
  }
  return val;
}



