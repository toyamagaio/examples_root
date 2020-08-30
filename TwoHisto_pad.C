void TwoHisto_pad()
{
  gROOT->Reset();
  gRandom->SetSeed(0);
  
  const int NofHist  = 5;// >=2

  int    Nbinx = 120;
  double minx  = -6;
  double maxx  = 6;
  
  double l_margin = 0.15;
  double r_margin = 0.05;
  double t_margin = 0.10;//affect the first hist only
  double b_margin = 0.20;//affect the last hist only
  double gap_margin = 0.02;//

  string xtitle = "Channel";
  string ytitle = "Counts";

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gPad->SetLogy(0);
  
  // prepare histogram
  TH1F *hist[NofHist];
  TPad *tp[NofHist+1];
  double ygap=1./(double)NofHist;
  double l_tp = 1./(1./(1.-t_margin) + 1./(1.-b_margin) + (double)NofHist -2.);
  double l_tp_first = l_tp/(1.-t_margin);
  double l_tp_last  = l_tp/(1.-b_margin);
  double epsilon=0.001;
  cout<<"ygap "<<ygap<<" "<<l_tp<<" "<<l_tp_last<<endl;
  tp[0]  = new TPad( "tp1", "tp1", 0.,        1.-l_tp_first, 1., 1.0 );
  for ( int i=NofHist-2; i>0; i-- ) {
    double ylow =((double)i-1.)*l_tp + l_tp_last;
    double yup  =(double)i*l_tp + l_tp_last + epsilon;
    cout<<i<<"  "<<ylow<<"  "<<yup<<endl;
    tp[i]  = new TPad( Form("tp%d",i+1), Form("tp%d",i+1) , 0., ylow , 1., yup );
  }
  tp[NofHist - 1]  = new TPad( Form("tp%d",NofHist)  ,Form("tp%d",NofHist)   , 0.,        0.0,            1., l_tp_last+epsilon );
  tp[NofHist]      = new TPad( Form("tp%d",NofHist+1),Form("tp%d",NofHist+1) , 0.,        0.0, 0.75*l_margin,                1. );//for ytitle
  for(int i = 0; i<NofHist+1; i++){
    cout<<i<<endl;
    tp[i] -> SetBottomMargin(gap_margin);
    tp[i] -> SetTopMargin( 0. );
    tp[i] -> SetLeftMargin(  l_margin );
    tp[i] -> SetRightMargin( r_margin );
    tp[i] -> SetTickx(0);
    tp[i] -> SetTicky(1);
    tp[i] -> SetLogy(0);
    tp[i] -> SetFrameFillStyle(4000);
    tp[i] -> SetFrameLineWidth(0);
    tp[i] -> Draw();
  }
  tp[0] -> SetTopMargin( t_margin );
  tp[NofHist-1] -> SetBottomMargin( b_margin );
  for(int i = 0; i<NofHist; i++){
    hist[i] = new TH1F(Form("h%d", i), Form("h%d", i), Nbinx, minx, maxx);
    hist[i]->FillRandom("landau", 1000*i);
    hist[i]->SetTitle(0);
    hist[i]->SetStats(0);
    hist[i]->GetXaxis()->SetNdivisions(0);
    hist[i]->GetXaxis()->SetTickLength(0);
    //hist[i]->GetYaxis()->SetNdivisions(0);
    //hist[i]->GetYaxis()->SetTickLength(0);
    hist[i]->SetLineColor(i+1);
  }
  hist[0]->FillRandom("gaus", 10000);
  hist[NofHist-1]->GetXaxis()->SetTitle(xtitle.c_str());
  hist[NofHist-1]->GetXaxis()->SetTitleOffset(0.7);
  hist[NofHist-1]->GetXaxis()->SetTitleSize(0.025*(double)NofHist);
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
    //axis_y[i] = new TGaxis(minx, 0, minx, max_y, 
	//		   0, max_y,
	//		   505,"G",0.78);
    //axis_y[i]->ImportAxisAttributes(hist[i]->GetYaxis());
    //axis_y[i]->SetTitle(0);
    //axis_y[i]->SetTitle(ytitle.c_str());
    //axis_y[i]->CenterTitle();
    //axis_y[i]->Draw();

    // Draw x axis
    if(i == 0){
      axis_x[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"U+-");
      axis_x[i]->ImportAxisAttributes(hist[i]->GetXaxis());
      line->DrawLineNDC(   l_margin,1.-t_margin,1.-r_margin,1.-t_margin);//top horizontal
      line->DrawLineNDC(1.-r_margin,0.00       ,1.-r_margin,1.-t_margin);//right vertical
      line->DrawLineNDC(   l_margin,0.00       ,   l_margin,1.-t_margin);//left vertical
      axis_x[i]->Draw();
    }else if(i==NofHist-1) {
      axis_x[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"+");
      axis_x[i]->ImportAxisAttributes(hist[i]->GetXaxis());
      line->DrawLineNDC(1.-r_margin,b_margin,1.-r_margin,1.);//right vertical
      line->DrawLineNDC(   l_margin,b_margin,   l_margin,1.);//left vertical
      axis_x[i]->Draw();
    }else{
      axis_x[i] = new TGaxis(minx, 0, maxx, 0,
			     minx, maxx,
			     510,"U+-");
      axis_x[i]->ImportAxisAttributes(hist[i]->GetXaxis());
      axis_x[i]->SetTickLength(10000);
      axis_x[i]->SetTickSize(10000);
      line->DrawLineNDC(1.-r_margin,0.,1.-r_margin,1.);//right vertical
      line->DrawLineNDC(   l_margin,0.,   l_margin,1.);//left vertical
      axis_x[i]->Draw();
    }


  }

  //Draw y title
  TLatex *latex=new TLatex();
  latex -> SetTextSize(0.32); 
  latex -> SetTextColor(1);
  latex -> SetTextAlign(22);
  latex -> SetTextFont(42);
  latex -> SetTextAngle(90);
  tp[NofHist]->cd();
  latex->DrawLatexNDC(0.5,0.5,ytitle.c_str() );

}
