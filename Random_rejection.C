void Random_rejection(){
  TH1D *h  = new TH1D("h ","h ",100,0,1.);
  TH1D *h2 = new TH1D("h2","h2",100,0,1.);
  h2->SetFillStyle(3001);
  h2->SetFillColor(3);
  h->SetMinimum(0);
  
  gRandom->SetSeed(0);
  for(int i=0;i<1E+5;i++){
    double x  = gRandom->Uniform(0.,1.);
    double y = gRandom->Uniform(0.,1.);
    double fx  = 1. - x;
    h->Fill(x);
    if( y < fx ) h2->Fill(x);
  }
  h->Draw("");
  h2->Draw("same");
}

