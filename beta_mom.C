void beta_mom(){
Double_t m[4]={938.272046, 493.677 ,139.57018,  0.511};
Double_t n[2]={1.05, 1.5};

TCanvas *c1 =new TCanvas("c1","canvas",800,600);
  TH1F* frames =  c1 -> DrawFrame(   0,   0, 1500, 1.1 );
frames->GetXaxis()->SetTitle("Momentum[MeV/c]");
frames->GetYaxis()->SetTitle("#beta");
frames->Draw();

TF1 *f[6];
for(int i=0;i<4;i++){
   f[i] =new TF1(Form("f%d",i+1),"x/sqrt(pow([0],2.) +pow(x,2.))",0,1500);
   f[i] ->SetParameter(0, m[i]);
   f[i] ->SetLineColor(i+2);
   f[i] ->SetTitle("beta-mom");
   f[i]->SetLineStyle(1);
   f[i]->SetLineWidth(2);
  }

for(int i=4;i<6;i++){
   f[i] =new TF1(Form("f%d",i+1),"[0]",0,1500);
   f[i] ->SetParameter(0, 1./n[i-4]);
   f[i] ->SetLineColor(1);
   f[i]->SetLineStyle(2);
   f[i]->SetLineWidth(1);
  }
f[0]->GetXaxis()->SetTitle("momentum[MeV/c]");
f[0]->GetYaxis()->SetTitle("beta");
f[0]->Draw("same");
f[1]->Draw("same");
f[2]->Draw("same");
f[3]->Draw("same");
f[4]->Draw("same");
f[5]->Draw("same");

}
