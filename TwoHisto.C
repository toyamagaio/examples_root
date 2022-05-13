void TwoHisto()
{
  gROOT->Reset();
  gRandom->SetSeed(0);
  
  const int NofHist  = 2;

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
  // first hist
  hist[0] = new TH1F("h0", "h0", Nbinx, minx, maxx);
  hist[0]->FillRandom("gaus", 10000);
  for(int i = 1; i<NofHist; ++i){
    hist[i] = new TH1F(Form("h%d", i), Form("h%d", i), Nbinx, minx, maxx);
    hist[i]->FillRandom("landau", 1000*i);
  }

  // make TGaxis X
  TGaxis *axis_x[NofHist];
  TGaxis *axis_y[NofHist];
  for(int i = 0; i<NofHist; ++i){
    // Draw histogram
    double max_y     = hist[i]->GetMaximum()*1.1;
    double max_yaxis = (double)dummy_Nbiny/NofHist;
    double scale     = max_yaxis/max_y;
    hist[i]->Scale(scale);
    for(int bin = 0; bin<Nbinx; ++bin){
      hist[i]->AddBinContent(bin+1, i*(max_yaxis));
    }

    //hist[i]->Draw("same");

    // Draw y axis
    axis_y[i] = new TGaxis(minx, i*max_yaxis, minx, (i+1)*max_yaxis, 
			   0, max_y,
			   505,"W",0.78);
    axis_y[i]->ImportAxisAttributes(base->GetYaxis());
    axis_y[i]->SetTitle(ytitle);
    axis_y[i]->CenterTitle();
    axis_y[i]->Draw();

    // Draw x axis
    if(i == 0){
      axis_x[i] = new TGaxis(minx, dummy_miny, maxx, dummy_miny,
			     minx, maxx,
			     510,"W",0.83);
      axis_x[i]->ImportAxisAttributes(base->GetXaxis());
      axis_x[i]->SetTitle(xtitle);
      axis_x[i]->CenterTitle();
    }else{
      axis_x[i] = new TGaxis(minx, i*max_yaxis, maxx, i*max_yaxis,
			     minx, maxx,
			     510,"U+-");
      axis_x[i]->ImportAxisAttributes(base->GetXaxis());
    }

    axis_x[i]->Draw();
  }
}
