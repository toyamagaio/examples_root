
void kadai1(){
  TH2D *h  = new TH2D("h ",";x;y",100,-1.0,1.0,100,-1.0,1.0);
  TH2D *h2 = new TH2D("h2","h2"  ,100,-1.0,1.0,100,-1.0,1.0);
  h2->SetMarkerColor(2);
  gRandom->SetSeed(0);
  double Nev=1e5;
  for(int i=0;i<Nev;i++){
    double x = gRandom->Uniform(-1.0,1.0);
    double y = gRandom->Uniform(-1.0,1.0);
    double r  = sqrt(x*x+y*y);
    h->Fill(x,y);
    if( r < 1. ) h2->Fill(x,y);
  }
  h->Draw("");
  h2->Draw("same");

  double pi_stat=h2->Integral();
  double PI=TMath::Pi();
  
  cout<<"estimated pi: "<<4.*pi_stat/Nev<<endl;
  cout<<"pi: "<<PI<<endl;

}

void kadai2(){
  TH1D *h  = new TH1D("h ","h ",100,-1,1.);
  TH1D *h2 = new TH1D("h2","h2",100,-1,1.);
  h2->SetFillStyle(3001);
  h2->SetFillColor(3);
  h->SetMinimum(0);
  
  gRandom->SetSeed(0);
  for(int i=0;i<1E+5;i++){
    double x  = gRandom->Uniform(-1.,1.);
    double y = gRandom->Uniform(0.,1.);
    double fx  = 0.5*(1. + x);
    h->Fill(x);
    if( y < fx ) h2->Fill(x);
  }
  h->Draw("");
  h2->Draw("same");


}


void kadai3_wrong(){
  TH3D *h1 = new TH3D("h1","h1",100,-1.,1.,100,-1.,1.,100,-1.,1.);
  double PI=TMath::Pi();
  gRandom->SetSeed(0);
  for(int i=0;i<1E+4;i++){
    double theta  = gRandom->Uniform(0.,PI);
    double phi    = gRandom->Uniform(0.,2.*PI);
    double x = sin(theta)*cos(phi);
    double y = sin(theta)*sin(phi);
    double z = cos(theta);
    h1->Fill(x,y,z);
  }
  h1->Draw();
}


void kadai3(){
  TH3D *h1 = new TH3D("h1","h1",100,-1.,1.,100,-1.,1.,100,-1.,1.);
  double PI=TMath::Pi();
  gRandom->SetSeed(0);
  for(int i=0;i<1E+4;i++){
    double phi    = gRandom->Uniform(0.,2.*PI);
    double costheta = gRandom->Uniform(-1.,1);
    double theta=acos(costheta);
    double x = sin(theta)*cos(phi);
    double y = sin(theta)*sin(phi);
    double z = cos(theta);
    h1->Fill(x,y,z);
  }
  h1->Draw();
}
