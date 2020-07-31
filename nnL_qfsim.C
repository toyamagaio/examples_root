void nnL_qfsim(){

  gROOT->Reset();
  int ENum=400;//from paper draft of Bishnu
  double Bmin= 0.;
  double Bmax=40.;
  double a=30./40.;//dist.

  TH1D *h=new TH1D("h","",40,-10,50);
  TH1D *h_2=new TH1D("h_2","",30,-10,50);
  TH1D *h_4=new TH1D("h_4","",15,-10,50);
  double wbin=h->GetBinWidth(1); 
  double wbin2=h_2->GetBinWidth(1); 
  double wbin4=h_4->GetBinWidth(1); 
  cout<<"bin width"<<wbin<<endl;
  h  ->SetTitle(Form("%.2lf MeV/bin",wbin));
  h_2->SetTitle(Form("%.2lf MeV/bin",wbin2));
  h_4->SetTitle(Form("%.2lf MeV/bin",wbin4));

  for(int n=0;n<ENum;n++){
    if(n%100==0)cout<<n<<endl;
    while(1){
      double BL = gRandom -> Uniform(Bmin, Bmax);
      double yy = gRandom -> Uniform(0 , 60);
      if(yy<a*BL){
        h->Fill(BL);
        h_2->Fill(BL);
        h_4->Fill(BL);
        break;
      }
    }
  }

  TCanvas *c1=new TCanvas("c1","c1",800,800);
  h->Draw("E");
  TCanvas *c2=new TCanvas("c2","c2",800,800);
  h_2->Draw("E");
  TCanvas *c4=new TCanvas("c4","c4",800,800);
  h_4->Draw("E");

  c1->Print("nnL_qfsim.pdf[");
  c1->Print("nnL_qfsim.pdf");
  c2->Print("nnL_qfsim.pdf");
  c4->Print("nnL_qfsim.pdf");
  c4->Print("nnL_qfsim.pdf]");

}
