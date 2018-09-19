void Landau_sim(){
gROOT->Reset();
gStyle->SetOptStat("MER");
TH1F* hist = new TH1F("hist","hist",270,-4,50);
SetTH1(hist,"", "x", "counts",1,4,3001);
//hist->SetFillColor(2);
//hist->SetFillStyle(3001);
//hist->SetFillColor(3);

int counter = 0;
double MPV=0.0;
double sigma =1.;
gRandom -> SetSeed( time(NULL) ); //seed set by time
/*
for(int i=0;i<10000;i++){
//cout<<2*(gRandom->Uniform(1)-0.5)<<endl;
double aa = 2*(gRandom->Uniform(1)-0.5);
hist[0]->Fill(aa);
}
hist[0]->Draw("");
*/
for(int i;i<100000;i++){
//double y = gRandom -> Gaus(MPV,sigma);
double y = gRandom -> Landau(MPV,sigma);
hist->Fill(y);
}
TF1 *la = new TF1("la","landau",-4,14);
la->SetLineWidth(3);
la->SetLineColor(2);
la->SetLineStyle(2);
TF1 *ga = new TF1("ga","gaus",-4,14);
ga->SetLineWidth(3);
ga->SetLineColor(2);
ga->SetLineStyle(2);
TCanvas *c1 =new TCanvas("c1","canvas",800,600);
hist->Draw("");
hist->Fit(la,"R","");
//hist->Fit(ga);
}
