#include "Setting.cc"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Double_t pol2_oneside(Double_t *x, Double_t *par){
  //par[0] : a
  //par[1] : b
  //par[2] : const 
  Double_t val;
  if(x[0]< par[1])val= par[2];
  else{
    val = par[0]*(x[0]-par[1])*(x[0]-par[1]) +par[2];
  }

  return val;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void myfunc(){

  Setting *set = new Setting();

  TF1 *f = new TF1("f",pol2_oneside,-1,1,3);
  set->SetTF1(f,2,1,1);
  f->SetParameter(0, 1.0);
  f->SetParameter(1,-0.2);
  f->SetParameter(2, 0.3);

  f->Draw();
}
