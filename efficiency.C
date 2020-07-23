void efficiency(){

  TH1D *h_pass  = new TH1D("h_pass" ,"h_pass" ,100,-10,10);
  TH1D *h_total = new TH1D("h_total","h_total",100,-10,10);

  int NEv=10000;
  for(int n=0;n<NEv;n++){
    if(n%1000==0)cout<<n<<" / "<<NEv<<endl;
    double val=gRandom->Uniform( 0,1);
    double y  =gRandom->Uniform(-5,5);
    if(TMath::Gaus(y,0,1.)>val)h_pass ->Fill( y );
    h_total->Fill( y );
  }


  TEfficiency  *pEff = new TEfficiency( *h_pass, *h_total);
  pEff->SetTitle("Efficiency;val;Efficiency");
  // this will write the TEfficiency object to "myfile.root"
  //   // AND pEff will be attached to the current directory

  TCanvas *c1=new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);
  c1->cd(1);h_pass ->Draw();
  c1->cd(2);h_total->Draw();
  c1->cd(3);pEff->Draw("AP");
}
