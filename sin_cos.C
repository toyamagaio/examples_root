#include "Setting.cc"

void sin_cos(){

  Setting *set = new Setting();

  TF1 *f_sin2 = new TF1("f_sin2","sin(x)*sin(x)",0,2.*TMath::Pi());
  TF1 *f_cos2 = new TF1("f_cos2","cos(x)*cos(x)",0,2.*TMath::Pi());
  set->SetTF1(f_sin2,2,1,1);
  set->SetTF1(f_cos2,4,1,1);
  TH2D *h_frame = new TH2D("h_frame","h_frame",10,0,1.*TMath::Pi(),10,0,1); 
  set->SetTH2(h_frame,"","#theta [rad]","");

  h_frame->Draw();
  f_sin2 ->Draw("same");
  f_cos2 ->Draw("same");
}
