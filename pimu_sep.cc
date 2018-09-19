void pimu_sep(){
gRandom -> SetSeed( time(NULL) ); //seed set by time
TH2D *h_pi = new TH2D("h_pi","",4000,100.,140.,500.,0.5,1.);
SetTH2(h_pi,"mom vs beta", "momentum[MeV/c]","beta");
h_pi -> SetStats(0);
TH1D *h_b = new TH1D("h_b","",100.,-0.05,0.05);
Double_t mompi,Lpi,betapi_i,dtpi,betapi_m;
Double_t sigma;
const double sigma_d = 0.1;//resolution of new detector
sigma = sqrt(0.255*0.255+sigma_d*sigma_d);
for(int i=0;i<50000;i++){
mompi = gRandom -> Uniform(100.,140.);
Lpi   = 10.;
//cout<<"Lpi = "<<Lpi<<endl;
betapi_i = mompi/sqrt(mompi*mompi+Mpi*Mpi);
mompi += gRandom -> Gaus(0.,mompi/10000.);
dtpi = Lpi/(c*betapi_i);
dtpi += gRandom -> Gaus(0.,sigma);
Lpi   += gRandom -> Gaus(0.,Lpi/100.);
//cout<<"Lpi = "<<Lpi<<"(w/ reso)"<<endl;
betapi_m = Lpi/(c*dtpi);

h_pi->Fill(mompi,betapi_m);
//h_b->Fill(betapi_m - betapi_i);
   }

Double_t mommu,Lmu,betamu_i,dtmu,betamu_m;
for(int i=0;i<50000;i++){
mommu = gRandom -> Uniform(100.,140.);
Lmu   = 10.;
betamu_i = mommu/sqrt(mommu*mommu+Mmu*Mmu);
mommu += gRandom -> Gaus(0.,mommu/10000.);
dtmu = Lmu/(c*betamu_i);
dtmu += gRandom -> Gaus(0.,sigma);
Lmu   += gRandom -> Gaus(0.,Lmu/100.);
betamu_m = Lmu/(c*dtmu);

h_pi->Fill(mommu,betamu_m);
h_b->Fill(betamu_m - betamu_i);
   }

//TCanvas *c2 =new TCanvas("c2","mu-pi separation",1800,600);
//c2->Divide(2,1);
//c2->cd(1);h_pi -> Draw("colz");
//c2->cd(2);h_b -> Draw("");

TCanvas *c2 =new TCanvas("c2","mu-pi separation",800,600);
h_pi -> Draw("colz");
}
