void projectTH2_range(){

  TH2D *h2 = new TH2D("h2","h2;x;y;",30,-1, 1,30,-1,1);
  TH1D *h_pxlow, *h_pxhig;
  double yth=0.2;

  gRandom -> SetSeed( time(NULL) ); //seed set by time
  double mean  = 0.;
  double sigma = 0.3;
  int ENum = 100000;

  for(int i=0;i<ENum;i++){
    double x = gRandom->Gaus(mean,sigma);
    double y = x * gRandom->Landau(mean,sigma);
    h2 ->Fill(x,y);
  }
  h2->SetContour(99);

  int first = h2->GetYaxis()->FindBin(-1.);
  int th    = h2->GetYaxis()->FindBin(yth);
  int last  = h2->GetYaxis()->FindBin( 1.);
  h_pxlow =h2->ProjectionX("h_pxlow",first,th);
  h_pxhig =h2->ProjectionX("h_pxhig",th+1 ,last);
  h_pxlow ->SetTitle(Form("ProjectionX (y<=%.2lf)",yth));
  h_pxhig ->SetTitle(Form("ProjectionX (y>%.2lf)",yth));

  TCanvas *c1 = new TCanvas("c1","c1",900,900);
  c1->Divide(2,2);
  c1->cd(1); gPad->SetLogz(1);h2   ->Draw("colz");//default
  c1->cd(2); gPad->SetLogy(0);h_pxlow   ->Draw("");//default
  c1->cd(3); gPad->SetLogy(0);h_pxhig   ->Draw("");//default

}
