void Random(){
  TH1D *h = new TH1D("h",";x;Counts",100,-1.5,1.5);

  gRandom->SetSeed(0);
  for(int i=0;i<100000;i++){
    double val = gRandom->Uniform(-1.,1.);
    h->Fill(val);
    //cout<<val<<endl;
  }
  h->Draw();
}

