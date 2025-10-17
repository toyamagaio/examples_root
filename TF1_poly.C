#include "Setting.cc"
void TF1_poly(){


  Setting *set = new Setting();

  TF1 *f[3];
  f[0] = new TF1("f","pol0",-1,1);
  f[1] = new TF1("f","pol1",-1,1);
  f[2] = new TF1("f","pol2",-1,1);
  for(int i=0;i<3;i++){
    set->SetTF1(f[i],1+i,1,1);
  }
  f[0]->SetParameter(0, 1.0);
  f[1]->SetParameter(0, 1.0);
  f[2]->SetParameter(0, 1.0);
  f[1]->SetParameter(1,-0.2);
  f[2]->SetParameter(1,-0.2);
  f[2]->SetParameter(2, 0.3);

  f[0]->Draw();
  f[1]->Draw("same");
  f[2]->Draw("same");
}
