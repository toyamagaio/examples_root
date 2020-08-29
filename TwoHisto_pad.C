void TwoHisto_pad()
{
  gROOT->Reset();
  gRandom->SetSeed(0);
  
  const int NofHist  = 4;// >=2

  int    Nbinx = 120;
  double minx  = -6;
  double maxx  = 6;

  string xtitle = "Channel";
  string ytitle = "Counts";

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gPad->SetLogy(0);
  
  // prepare histogram
  TH1F *hist[NofHist];
  TPad *tp[NofHist];
  double ygap=1./(double)NofHist;
  cout<<"ygap "<<ygap<<endl;
  tp[0]  = new TPad( "tp1", "tp1", 0.,        1.-ygap, 1., 1.0 );
  for ( int i=NofHist-2; i>0; i-- ) {
    double ylow =(double)i*ygap;
    double yup  =((double)i+1.)*ygap;
    cout<<i<<"  "<<ylow<<"  "<<yup<<endl;
    tp[i]  = new TPad( Form("tp%d",i+1), Form("tp%d",i+1) , 0., ylow , 1., yup );
  }
  tp[NofHist - 1]  = new TPad( Form("tp%d",NofHist),Form("tp%d",NofHist) , 0.,        0.0, 1., ygap );
  for(int i = 0; i<NofHist; i++){
    cout<<i<<endl;
    tp[i] -> SetBottomMargin( 0.02);
    tp[i] -> SetTopMargin( 0. );
    tp[i] -> SetLeftMargin( 0.20 );
    tp[i] -> SetRightMargin( 0.05 );
    tp[i] -> SetTickx(0);
    tp[i] -> SetTicky(0);
    tp[i] -> SetFrameLineWidth(0);
    tp[i] -> Draw();
  }
  tp[0] -> SetTopMargin( 0.12 );
  tp[0] -> SetBottomMargin( 0.015 );
  tp[NofHist-1] -> SetTopMargin( 0. );
  tp[NofHist-1] -> SetBottomMargin( 0.25 );
  // first hist
  hist[0] = new TH1F("h0", "h0", Nbinx, minx, maxx);
  hist[0]->FillRandom("gaus", 10000);
  hist[0]->SetTitle(0);
  hist[0]->SetStats(0);
  hist[0]->GetXaxis()->SetNdivisions(0);
  hist[0]->GetXaxis()->SetTickLength(0);
  hist[0]->GetYaxis()->SetNdivisions(0);
  hist[0]->GetYaxis()->SetTickLength(0);
  for(int i = 1; i<NofHist; i++){
    hist[i] = new TH1F(Form("h%d", i), Form("h%d", i), Nbinx, minx, maxx);
    hist[i]->FillRandom("landau", 1000*i);
    hist[i]->SetTitle(0);
    hist[i]->SetStats(0);
    hist[i]->GetXaxis()->SetNdivisions(0);
    hist[i]->GetXaxis()->SetTickLength(0);
    hist[i]->GetYaxis()->SetNdivisions(0);
    hist[i]->GetYaxis()->SetTickLength(0);
  }
  hist[NofHist-1]->GetXaxis()->SetTitle(xtitle.c_str());
  hist[NofHist-1]->GetXaxis()->SetTitleOffset(0.7);
  hist[NofHist-1]->GetXaxis()->SetTitleSize(0.025*(double)NofHist);//*(double)NofHist
  hist[NofHist-1]->GetXaxis()->CenterTitle();

  // make TGaxis X
  TGaxis *axis_x[NofHist];
  TGaxis *axis_y[NofHist];
  TLine *line = new TLine();
  line -> SetLineColor(1);line->SetLineWidth(1);line->SetLineStyle(1);

  for(int i = 0; i<NofHist; i++){
    // Draw histogram
    double max_y     = hist[i]->GetMaximum()*1.01;

    tp[i]->cd();
    hist[i]->Draw("");

    // Draw y axis
    axis_y[i] = new TGaxis(minx, 0, minx, max_y, 
			   0, max_y,
			   505,"",0.78);
    axis_y[i]->ImportAxisAttributes(hist[i]->GetYaxis());
    axis_y[i]->SetTitle(0);
    //axis_y[i]->SetTitle(ytitle.c_str());
    axis_y[i]->CenterTitle();
    axis_y[i]->Draw();

    // Draw x axis
    if(i == 0){
      axis_x[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"U");
      axis_x[i]->ImportAxisAttributes(hist[i]->GetXaxis());
      line->DrawLineNDC(0.20,0.88,0.95,0.88);//top horizontal
      line->DrawLineNDC(0.95,0.00,0.95,0.88);//right vertical
      line->DrawLineNDC(0.20,0.00,0.20,0.88);//left vertical
      axis_x[i]->Draw();
    }else if(i==NofHist-1) {
      axis_x[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"");
      axis_x[i]->ImportAxisAttributes(hist[i]->GetXaxis());
      line->DrawLineNDC(0.95,0.25,0.95,1.);//right vertical
      line->DrawLineNDC(0.20,0.25,0.20,1.);//left vertical
      axis_x[i]->Draw();
    }else{
      axis_x[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"U");
      axis_x[i]->ImportAxisAttributes(hist[i]->GetXaxis());
      line->DrawLineNDC(0.95,0.,0.95,1.);//right vertical
      line->DrawLineNDC(0.20,0.,0.20,1.);//left vertical
      axis_x[i]->Draw();
    }


  }

}
