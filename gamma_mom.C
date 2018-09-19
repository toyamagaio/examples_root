void gamma_mom(){
Double_t m[3]={1.115,3.99, 4.};//mass of Lambda, H3L, H4L [GeV/c^2]

TCanvas *c1 =new TCanvas("c1","canvas",800,600);
  TH1F* frames =  c1 -> DrawFrame( 0, 1, 1., 1.5 );
frames->GetXaxis()->SetTitle("momentum[GeV/#it{c}]");
frames->GetYaxis()->SetTitle("#gamma factor");
frames->Draw();

TF1 *f[3];
for(int i=0;i<3;i++){
   f[i] =new TF1(Form("f%d",i+1),"sqrt([0] +pow(x/[1],2.))",0.,1.5);
   f[i] ->SetParameter(0, 1.);
   f[i] ->SetParameter(1, m[i]);
   f[i] ->SetLineColor(i+2);
   f[i] ->SetTitle("mom-gamma");
   f[i]->SetLineStyle(1);
   f[i]->SetLineWidth(2);
  }

//f[0]->GetXaxis()->SetTitle("");
//f[0]->GetYaxis()->SetTitle("");
frames ->Draw();
f[0]->Draw("same");
f[1]->Draw("same");
f[2]->Draw("same");

}
