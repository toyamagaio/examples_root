
void Random_inverse(){

  TH1D *h=new TH1D("h",";x;Counts",100,0,10);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();

  gRandom->SetSeed(0);
  int Nev=1e5;
  for(int i=0;i<Nev;i++){
    double x=-log(1.-gRandom->Uniform(0.,1.));
    h->Fill(x);
  }

  TCanvas *cv=new TCanvas("cv","cv",1000,800);
  gPad->SetLogy();
  h->Draw();

}

/*
#include "Setting.cc"
void Prob_dens(){
  Setting* set=new Setting();
  TH2D *h_frame=new TH2D("h_frame","frame",10,0,10,10,0,1.05);
  set->SetTH2(h_frame,"","x","");

  TF1 *fx=new TF1("fx","exp(-x)",0,10);
  TF1 *Fx=new TF1("Fx","1-exp(-x)",0,10);
  set->SetTF1(fx,2,1,2);
  set->SetTF1(Fx,4,1,2);

  h_frame->Draw();
  fx->Draw("same");
  Fx->Draw("same");

}
*/
