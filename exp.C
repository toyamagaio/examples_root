void exp(){
gROOT ->Reset(); //no meaning 
gRandom -> SetSeed( time(NULL) ); //seed file set by time

TH2F *h2_time = new TH2F("h2_time","h2_time",100, -0.5, 2.0,100, -0.5, 2.0);//define histgram
SetTH2(h2_time,"decay time","recoil nucleus","pion");

TH1F *hist = new TH1F("hist","hist",100, -0.5, 2.0);//define histgram
//TH1F(name, title, number of bin, x min, x max);
  hist->SetTitle("aaa");
  hist->SetLineColor(4);
  hist->SetLineWidth(0);
//  hist->SetFillStyle(3001);
//  hist->SetFillColor(2);
  hist->GetXaxis()->SetTitle("t [ns]");
  hist->GetYaxis()->SetTitle("count");

TH1F *hist1 = new TH1F("hist1","hist1",100, -0.5, 2.0);//define histgram
  hist1->SetTitle("hoge");
  hist1->SetLineColor(2);
  hist1->SetLineWidth(0);
//  hist1->SetFillStyle(3001);
//  hist1->SetFillColor(3);
  hist1->GetXaxis()->SetTitle("t [ns]");
  hist1->GetYaxis()->SetTitle("count");

TH1F *hist2 = new TH1F("hist2","hist2",100, -0.5, 2.0);//define histgram
  hist2->SetTitle("hoge");
  hist2->SetLineColor(3);
  hist2->SetLineWidth(0);
//  hist2->SetFillStyle(3001);
//  hist2->SetFillColor(3);
  hist2->GetXaxis()->SetTitle("t [ns]");
  hist2->GetYaxis()->SetTitle("count");

double t, tr, tr_nucl;//define
double tau = 0.2;//define (lifetime)
double sigma = 0.1;//define (resolution)
for(int i;i<10000;i++){//loop
t       = gRandom -> Exp(tau);//generate random value
tr      = gRandom -> Gaus(0.,sigma);//generate random value
tr_nucl = gRandom -> Gaus(0.,sigma);//generate random value
hist -> Fill(t);
hist1 -> Fill(tr+t);
h2_time -> Fill(tr+t, tr_nucl + t);
}
TCanvas *c = new TCanvas("c","canvas",900,600);//define canvas
c->Divide(2,2);
c->cd(1);
hist->Draw();//draw histgram
hist1->Draw("same");//draw histgram in same canvas
c->cd(2);
gPad->SetLogz(1);
h2_time ->Draw("colz");
}
