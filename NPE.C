double t2NPE(double thick){
//assuming poisson distribution
double PDE =0.4;
double N0 = 1600;// /mm
double pixel = 7200.;
double NPE = pixel*( 1-TMath::Exp(-thick*PDE*N0/pixel) );
return NPE;
}
///*************?////
void NPE(){
const int step = 1000;
double Nd[step],thick[step],lin[step];
double thickmin=0;
double thickmax=20;
TGraph *tg_lin;
TGraph *tg_npe;

TCanvas *c1 =new TCanvas("c1","canvas",800,600);
TH2F *h_frame = new TH2F("h_frame","h_frame",10,thickmin,thickmax,10,0,7200);
SetTH2(h_frame , "", "thickness [mm]", "N_{d}");

  for(int i=0;i<step;i++){
  thick[i]  = 0+i*(thickmax-thickmin)/step;
  Nd[i]=t2NPE(thick[i]);
  lin[i]=thick[i]*0.4*1600;
   }
tg_npe = new TGraph(step,thick,Nd);
tg_lin = new TGraph(step,thick,lin);
h_frame ->Draw();
tg_npe  ->Draw("samel");
tg_lin  ->Draw("samel");

}
