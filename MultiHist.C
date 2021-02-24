bool AddBinCont(TH1F **h, TGaxis **x_ax, TGaxis **y_ax, double minx, double maxx, int NofHist){
  for(int i=0;i<NofHist;i++){
    double max_y     = h[i]->GetMaximum()*1.1;
    double max_yaxis = 100./NofHist;
    h[i]->Scale(max_yaxis/max_y);

    int Nbinx =h[i]->GetNbinsX();
    for(int bin = 0; bin<Nbinx; ++bin){
      h[i]->AddBinContent(bin+1, i*(max_yaxis));
    }

    y_ax[i] = new TGaxis(minx, i*max_yaxis, minx, (i+1)*max_yaxis, 
			   0, max_y,
			   505,"-");

    if(i == 0){
      x_ax[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"",0.83);
    }else{
      x_ax[i] = new TGaxis(minx, i*max_yaxis, maxx, i*max_yaxis,
			     minx, maxx,
			     510,"U+-");
    }

  }
  return true;
}
//
void MultiHist(){
  //gROOT->Reset();
  gRandom->SetSeed(0);
  
  const int NofHist  = 4;

  int    Nbinx = 120;
  double minx  = -6;
  double maxx  = 6;
  int    dummy_Nbiny = 100;
  double dummy_miny  = 0;
  double dummy_maxy  = 100;

  char* xtitle = "Channel";
  char* ytitle = "Counts";

  TH2F *base = new TH2F("base","",
			Nbinx, minx, maxx,
			dummy_Nbiny, dummy_miny, dummy_maxy
			);
  base->SetStats(0);

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gPad->SetLogy(0);
  base->Draw("AH");
  
  // prepare histogram
  TH1F *hist[NofHist];
  TGaxis *axis_x[NofHist];
  TGaxis *axis_y[NofHist];

  // first hist
  hist[0] = new TH1F("h0", "h0", Nbinx, minx, maxx);
  hist[0]->FillRandom("gaus", 10000);
  for(int i = 1; i<NofHist; ++i){
    hist[i] = new TH1F(Form("h%d", i), Form("h%d", i), Nbinx, minx, maxx);
    hist[i]->FillRandom("landau", 1000*i);
  }

  if(!AddBinCont( &hist[0],&axis_x[0],&axis_y[0], minx, maxx, NofHist)) cout<<"AddBinCont fail!"<<endl;

  for(int i = 0; i<NofHist; ++i){
    hist[i]->Draw("same");
    axis_x[i]->Draw();
    axis_y[i]->Draw();
  }
}
