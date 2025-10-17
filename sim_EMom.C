#include "Setting.cc"
void sim_EMom(){

  gROOT->Reset();
  double mass=Mu*4.002602 + Mmu;//MeV
  cout<<"mass:"<<mass<<" MeV"<<endl;
  gRandom -> SetSeed( time(NULL) ); //seed set by time

  int n=1000000;//num of sample
  double Ekin, mom, beta;
  Setting *set=new Setting();

  double maxEkin=10;//keV
  double maxE=mass+0.001*maxEkin;
  double maxMom=sqrt(maxE*maxE-mass*mass);
  cout<<"maxMom:"<<maxMom<<endl;

  TH1D *h_Ekin, *h_mom, *h_beta;
  TH2D *h2_Ekin_mom, *h2_Ekin_beta;
  h_Ekin = new TH1D("h_Ekin","h_Ekin",1000,-5., 15.);
  h_mom  = new TH1D("h_mom" ,"h_mom" ,1000,-0.010,10.000);
  h_beta = new TH1D("h_beta","h_beta",1000,-0.001, 0.005);
  set->SetTH1(h_Ekin,"","E_{kin} [keV]","",4,3000,0);
  set->SetTH1(h_mom ,"","p [MeV/#it{c}]","",4,3000,0);
  set->SetTH1(h_beta,"","#beta","",4,3000,0);
  h2_Ekin_mom=new TH2D("h2_Ekin_mom","h2_Ekin_mom",200, -5, 15, 200,-0.01,10);
  set->SetTH2(h2_Ekin_mom,"","E_{kin} [keV]","p [MeV/#it{c}]");

  for(int i=0;i<n;i++){
    if(i%100000==0)cout<<i<<"/"<<n<<endl;
    //Ekin=gRandom->Uniform(0,maxEkin);//keV
    while(1){
      Ekin=gRandom->Gaus(5,3);//keV
      if(Ekin>0 && Ekin<10)break;
    }
    double Etot=mass+0.001*Ekin;
    mom = sqrt(Etot*Etot-mass*mass);
    beta=mom/Etot;
    //cout<<Form("Ekin: %lf, mom: %lf, beta: %lf",Ekin,mom,beta)<<endl;
    h_Ekin ->Fill(Ekin);
    h_mom  ->Fill(mom );
    h_beta ->Fill(beta);
    h2_Ekin_mom->Fill(Ekin,mom);
  }

 
  TCanvas *cv =new TCanvas("cv","canvas",800,600);
  cv->Divide(2,2);
  cv->cd(1);h_Ekin ->Draw();
  cv->cd(2);h_mom  ->Draw();
  cv->cd(3);h_beta ->Draw();
  cv->cd(4);h2_Ekin_mom ->Draw();

  cv->Print("fig_sim_Emom.png");
}
