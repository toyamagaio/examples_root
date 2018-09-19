void get_mom_of_histo(){
  gROOT->Reset();
  TH1F *h = new TH1F("h","h",50,-2,2);
  
  int Nbg = 1000;
  int Ns  = 100;
  double val;
  for(int i=0;i<Ns;i++){
    val  = gRandom->Gaus(0.0,0.2);
    val += gRandom->Exp(0.26);
    h->Fill(val);
  }

  for(int i=0;i<Nbg;i++){
    val  = gRandom->Gaus(0.0,0.2);
    h->Fill(val);
  }
  
  h->Draw();

  int total_event = h->Integral(0,50);
  cout<<"total: "<<total_event<<endl;
  
  double rel_freq;//soutai dosuu
  double xval,mom=0;
  for(int i=h->FindFirstBinAbove(0.);i<h->FindLastBinAbove(0.);i++){
    rel_freq = (double)h->GetBinContent(i)/total_event;
    xval = h->GetBinCenter(i);
    //mom += i;
    mom += xval*rel_freq;
  }
    cout<<mom<<"  "<<i<<endl;
  
   cout<<((double)Nbg+(double)Ns)/(double)Ns*mom<<endl;
  
    cout<<"**************"<<endl;
  double mean = h->GetMean();
  cout<<mean<<endl;
}
