double angle_z(double *x, double *par){

  //par[0]=const
  //par[1]=lambda_U
  double zeta;
  double k = 2.*TMath::Pi()/par[1];

  if(x[0]<0.5*par[1])         zeta = 0.5*par[0]*(1. - TMath::Cos(k*x[0]));
  else if(x[0]<6.*par[1])     zeta = -1.*par[0]*(TMath::Cos(k*x[0]));
  else if(x[0]<6.5*par[1])    zeta = -0.5*par[0]*(1. + TMath::Cos(k*x[0]));
  else                        zeta = 0.;

  if(x[0]<0.)            zeta = 0.;
  
  return zeta/k;
}
////////////////////////////////////////////////////
void und_field(){
  TF1 *f0 = new TF1("f0",angle_z, -100., 600.0, 2);
  f0->SetParameters(10,80);
  f0->SetNpx(1000);
  f0->SetLineColor(2);
  
  TH2D *h = new TH2D("h","h",1,-30.,550.,1,-150.,150.);
  SetTH2(h,"","z mm","angle",0.4);
  h->SetStats(kFALSE);
  
  TCanvas = new TCanvas("c","canvas",800,600);
  h   -> Draw();
  f0  -> Draw("same");

}
