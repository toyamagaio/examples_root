void sim_DAQeff(){
  gROOT->Reset();
  gRandom -> SetSeed( time(NULL) ); //seed set by time
  double meanDAQeff = 0.7;
  
  TH1D *h_gene = new TH1D("h_gene","h_gene",22,-11,11);
  TH1D *h_spll = new TH1D("h_spll","h_spll",22,-11,11);
  TH1D *h_mean = new TH1D("h_mean","h_mean",22,-11,11);
  SetTH1(h_gene,"gene" ,"","",1,3000,0);
  SetTH1(h_spll,"spill","","",2,3001,2);
  SetTH1(h_mean,"mean" ,"","",4,3001,4);

  int ENum=200;
  int accepted=0;
  TH2I *h_frame = new TH2I("h_frame","h_frame",10,0,ENum,10,0,1);
  SetTH2(h_frame,"","EvNum","Efficiency");
  h_frame->SetStats(0);
  TGraph *tg = new TGraph();
  SetGr(tg,"","","",2,2,1,2,22,0.5);

  for(int n=0;n<ENum;n++){
    double spillDAQeff = meanDAQeff + gRandom -> Uniform(-0.2, 0.2);
    if(n<ENum/2)spillDAQeff=0.5; 
    else        spillDAQeff=0.9;
    tg->SetPoint(n,n,spillDAQeff);

    if(n%100==0)cout<<n<<"/"<<ENum<<" "<<spillDAQeff<<endl;
    double val = gRandom -> Uniform(-10, 10);
    h_gene->Fill(val);
    if( gRandom -> Uniform(0, 1)<spillDAQeff ){
      h_spll ->Fill(val, 1./spillDAQeff);
      h_mean ->Fill(val);
      accepted++;
    }
  }

  meanDAQeff = (double)accepted/(double)ENum;

  h_mean ->Scale(1./meanDAQeff);

  TCanvas *c[2];
  for(int i=0;i<2;i++){
    c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),1200,800);
  }
  c[0]->cd();
  h_gene ->Draw("histE1");
  h_spll ->Draw("sameE1");
  h_mean ->Draw("sameE1");
  c[1]->Divide(2,2);
  c[1]->cd(1);h_gene ->Draw("histE1");
  c[1]->cd(2);h_spll ->Draw("histE1");
  c[1]->cd(3);h_mean ->Draw("histE1");
  c[1]->cd(4);h_frame->Draw();tg->Draw("sameP");

  c[0]->Print("pdf/sim_DAQeff.pdf[");
  c[0]->Print("pdf/sim_DAQeff.pdf" );
  c[1]->Print("pdf/sim_DAQeff.pdf" );
  c[1]->Print("pdf/sim_DAQeff.pdf]");
}
