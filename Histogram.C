//#include"rootlogon.C"

void BinAndXval(void)
{
  gRandom->SetSeed(0);

  TH1F *h = new TH1F("h","h",100,-10,10);
  h->FillRandom("gaus",1000);
  TCanvas *c1 =new TCanvas("c1","c1");
  h->Draw();

  int binNum     = h->FindBin(1.4392);      // x value to bin number
  double xValue  = h->GetBinCenter(binNum); // bin number to x value
  std::cout << "bin:" << binNum << " " 
	    << "x(center of bin):"<< xValue << std::endl;

  double CountsInBin = h->GetBinContent(binNum); // y value stored in bin
  std::cout << "Counts:" << CountsInBin << std::endl;

  std::cout << "Press some keys, waiting getchar()" << std::endl;
  c1->Modified();
  c1->Update();
  getchar();

  h->SetBinContent(binNum, 1000); // Set y value into bin
  c1->Modified();
  c1->Update();
}

void BinControl(void)
{
  gRandom->SetSeed(0);

  TH1F *h = new TH1F("h","h",100,-10,10);
  h->FillRandom("gaus",1000);
  h->FillRandom("pol2",1000);
  TCanvas *c1 =new TCanvas("c1","c1");
  h->Draw();

  int yMaxValue = h->GetMaximum();    // return max y value
  int binNumMax = h->GetMaximumBin(); // return bin num hasing max y value
  std::cout << "MaxValue:" << yMaxValue 
	    << " binNum:" << binNumMax << std::endl;

  int yMinValue = h->GetMinimum();    // usually 0 
  int binNumMin = h->GetMinimumBin(); // return the first bin among bins found
  std::cout << "MinValue:" << yMinValue 
	    << " binNum:" << binNumMin << std::endl;

  std::cout << "Number of bins in x axis: " << h->GetNbinsX() << std::endl;

  int xBin      = 0;
  double yValue = 50.1;
  h->GetBinWithContent(yValue, xBin, 0, 0, 0.5);
  std::cout << "bin num corresponding to x value meeting y = "
	    << yValue << " is " << xBin << std::endl;
  std::cout << "x val at bin" << xBin << " is " << h->GetBinCenter(xBin) << std::endl;
  std::cout << "y val at bin" << xBin << " is " << h->GetBinContent(xBin) << std::endl;
  
  c1->Modified();
  c1->Update();
  std::cout << "Press some keys, waiting getchar()" << std::endl;
  getchar();

  h->Rebin(2);
  c1->Modified();
  c1->Update();
  std::cout << "Rebined, Bin number is reduced from " 
	    << 100 << " to " << 50 << std::endl;

  std::cout << "Press some keys, waiting getchar()" << std::endl;
  getchar();
  
  h->GetXaxis()->SetRange(20,80);
  c1->Modified();
  c1->Update();
  std::cout << "Range is changed by SetRange" << std::endl;

  std::cout << "Press some keys, waiting getchar()" << std::endl;
  getchar();

  h->GetXaxis()->SetRangeUser(-5,5);
  c1->Modified();
  c1->Update();
  std::cout << "Range is changed by SetRangeUser" << std::endl;
}

void TwoHisto()
{
  rootlogon();
  gROOT->SetStyle("MyStyle");
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

  TH2F *base = new TH2F("base","base",
			Nbinx, minx, maxx,
			dummy_Nbiny, dummy_miny, dummy_maxy
			);
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

    hist[i]->Draw("same");

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

void WaitPrimi()
{
  TH1F *hist = new TH1F("hist","hist",5,0,5);
  hist->Draw();
  for(int i = 0; i<5; ++i){
    hist->Fill(i);
    c1->Modified();
    c1->Update();
    c1->WaitPrimitive();
  }
}

void Histogram(int n)
{
  if(n==0){
    BinAndXval();
  }else if(n==1){
    BinControl();
  }else if(n==2){
    TwoHisto();
  }else if(n==3){
    WaitPrimi();
  }
}
