void TwoHisto_log(){
  const int NofHist  = 2;
  int    Nbinx = 120;
  double minx  = -6;
  double maxx  = 6;
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadTopMargin(0.0001);
  gStyle->SetPadBottomMargin(0.001);

  TH1F *hist[NofHist];
  for(int i = 0; i<NofHist; ++i){
    hist[i] = new TH1F(Form("h%d", i), Form("h%d", i), Nbinx, minx, maxx);
    hist[i]->FillRandom("gaus", 1000);
    hist[i]->SetTitle("");
    hist[i]->SetStats(0);
  }

  // make TGaxis X
  TGaxis *axis_x[NofHist];// = hist[0]->GetXaxis();
  for(int i =0 ;i<NofHist;i++){
    axis_x[i] = new TGaxis(minx,   0., maxx, 0.,
                           minx, maxx,  510,"W",0.);
    //axis_x[i] ->ImportAxisAttributes(hist[i]->GetXaxis()); 
  }

  //draw
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(1,2);
  c1->cd(1);
  gPad->SetLogy(1);
  gPad->SetPad(0.,0.51,1.,0.9);
  hist[0]  ->Draw();
  axis_x[0]->Draw();

  c1->cd(2);
  gPad->SetLogy(1);
  gPad->SetPad(0.,0.01,1.,0.5);
  hist[1]  ->Draw();
  axis_x[1]->Draw();
}
