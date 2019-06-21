const int NCanvas = 1;
void SphericalUniform(){
  gRandom -> SetSeed( time(NULL) ); //seed set by time
  TH1F *h_theta = new TH1F("h_theta","h_theta",100,-0.1,3.2);
  TH1F *h_phi   = new TH1F("h_phi"  ,"h_phi"  ,100,-0.1,6.4);
  TH1F *h_costh = new TH1F("h_costh","h_costh",100,-1.1,1.1);
  TH1F *h_yy = new TH1F("h_yy","h_yy",100,-0.1,3.2);
  TH3F *h3 = new TH3F("h3","h3",100,-1.1,1.1,100,-1.1,1.1,100,-1.1,1.1);
  TH3F *h3_acc = new TH3F("h3_acc","h3_acc",100,-1.1,1.1,100,-1.1,1.1,100,-1.1,1.1);
  h3_acc->SetMarkerColor(2);
  TCanvas* c[NCanvas];

  double theta_min = 0.5*TMath::Pi()-0.06;//[rad]
  double theta_max = 0.5*TMath::Pi()+0.06;//[rad]
  double phi_min   = TMath::Pi()-0.03;//[rad]
  double phi_max   = TMath::Pi()+0.03;//[rad]

  double theta,phi;
  double x,y,z;

  int ENum = 500000;
  int EvAcc = 0;
  for(int i=0;i<ENum;i++){
    theta = TMath::ACos(gRandom -> Uniform(-1.,1.));
    phi   = gRandom -> Uniform(0.,2.*TMath::Pi());
    x = TMath::Cos(phi)*TMath::Sin(theta);
    y = TMath::Sin(phi)*TMath::Sin(theta);
    z = TMath::Cos(theta);

    h_theta ->Fill(theta);
    h_phi   ->Fill(phi);
    h_costh ->Fill(TMath::Cos(theta));
    h3      ->Fill(x,y,z);
    if(theta>theta_min && theta<theta_max && phi>phi_min && phi<phi_max){
      h3_acc->Fill(x,y,z);
      EvAcc++;
    }
  }

  cout<<EvAcc<<" / "<<ENum<<endl;
  cout<<"Solid angle : "<<"Accepted/Event *4*pi = "<<1000.* 4.*TMath::Pi()*(double)EvAcc/(double)ENum<<" msr"<<endl;

  for(int i=0;i<NCanvas;i++){
    c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),600,800);
  }

  c[0]->Divide(2,2);
  c[0]->cd(1);h_theta ->Draw();
  c[0]->cd(2);h_phi   ->Draw();
  c[0]->cd(3);h_costh ->Draw();
  c[0]->cd(4);h3->Draw();h3_acc->Draw("same");
  
}
