#include "Setting.cc"
//
//calculate binding energy of deuteron
//assuming finite well potential
//
//Iki Kawai basic QM p125 [2]
//
double etacot(double *x, double *par){
  double val=0;

  val = -x[0]*TMath::Cos(x[0])/TMath::Sin(x[0]);
  if(val<0)val=-1.;
  return val;
}
//
double etasq(double *x, double *par){
  //par0: a
  //par1: mu (reduced mass)
  //par2: V0
  //par3: hbar
  double sq=-1;
  sq = par[0]*par[0]*2.*par[1]*par[2]/(par[3]*par[3]) - x[0]*x[0];

  double val=-1;
  if(sq>0)val=sqrt(sq);

  return val;
}
//
double eta_diff(double *x, double *par){
  double val= etacot(x,par) - etasq(x,par);
  return val;
}

void QM_wellpot(){

  Setting *set=new Setting();
  TCanvas *c1 = new TCanvas("c1","canvas",1200,600);
  TF1 *f_k = new TF1("f_k", etacot, 0.0, 4.0, 0);
  TF1 *f_l = new TF1("f_l", etasq , 0.0, 4.0, 4);
  TF1 *f_d = new TF1("f_d", eta_diff , 0.0, 4.0, 4);
  double a   =    2.8;//MeV
  double hbar=   197.;//MeV fm
  double V0  =   22.8;//MeV
  double mu  =939./2.;//MeV/c^2


  f_l->SetParameter(0,a   );
  f_l->SetParameter(1,mu  );
  f_l->SetParameter(2,V0  );
  f_l->SetParameter(3,hbar);
  f_d->SetParameter(0,a   );
  f_d->SetParameter(1,mu  );
  f_d->SetParameter(2,V0  );
  f_d->SetParameter(3,hbar);
  set->SetTF1(f_k,2,1,2);
  set->SetTF1(f_l,2,1,2);
  set->SetTF1(f_d,4,1,2);

  double xi  = f_d->GetX(0.,1.,3.);
  double eta = etacot(&xi, &xi);
  double BE=-(hbar*eta)*(hbar*eta)/(2.*mu*a*a);
  cout<<"xi: "<<xi<<", eta: "<<eta<<endl;
  cout<<"BE: "<<BE<<" MeV"<<endl;

  TH2D *h_frame=new TH2D("h_frame","h_frame",10,0,3.2,10,0.,4);
  set->SetTH2(h_frame,"","#xi","#eta");


  c1->Divide(2,1);
  c1->cd(1);h_frame->Draw();f_k->Draw("same");f_l->Draw("same");
  c1->cd(2);f_d->Draw();
}
