void yieldMC(){
gRandom -> SetSeed( time(NULL) ); //seed set by time
TH1D *h_s = new TH1D("h_s","",250,-0.5,2.);
SetTH1(h_s,"", "t0 [ns]", "counts/0.01(ns)",1,3001,2);
//h_s->SetLineColor(2);
h_s->SetStats(0);

TH1D *h_n = new TH1D("h_n","",250,-0.5,2.);
SetTH1(h_n,"", "t0 [ns]", "counts/0.01(ns)",1,3001,3);
//h_n->SetLineColor(4);
h_n->SetStats(0);
Int_t counter[3]={0,0,0};
Double_t s,n,r,l;
Double_t sigma;
sigma = 0.1;
for(int i=0;i<10000;i++){

 for(int j=0;j<1000;j++){
 n = gRandom -> Gaus(0.,sigma);
 h_n -> Fill(n);
 }

r = gRandom -> Gaus(0.,sigma);
l = gRandom -> Exp(0.2);
s = r+l;
h_s -> Fill(s);
if(s>3.*sigma)counter[0]++;
if(s>4.*sigma)counter[1]++;
if(s>5.*sigma)counter[2]++;
   }
TCanvas *c2 =new TCanvas("c2","yield simu",800,600);
c2 -> SetLogy();
h_n ->Draw();
h_s ->Draw("same"); 
Double_t e[3];
for(int i=0;i<3;i++){e[i] = counter[i];
cout<<Form("%dsigma",i+3)<<endl;
cout<<e[i]/10000*100<<"%"<<endl;
 }

}
