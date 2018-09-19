double angular_acceptance(double *x, double *par){
  //par[0] = theta
  //par[1] = radius
  double val;
  double theta = par[0];
  double rad   = par[1];
  double pi = 4.*atan(1.);

  if(TMath::Cos(theta)-x[0]/rad>0)val = (pi - TMath::ATan(TMath::Sin(theta)/(TMath::Cos(theta)-x[0]/rad)))/pi;
  else val = (TMath::ATan(TMath::Sin(theta)/(x[0]/rad-TMath::Cos(theta))))/pi;


  return val;
}
///////////////////////////////
void arctan(){
  gROOT->Reset();
  gRandom -> SetSeed( time(NULL) ); //seed set by time
//TF1 *func = new TF1("func","[0]*TMath::Sin(x)",0,2*PI);
//TF1 *func = new TF1("func","TMath::ATan(x)",-10.*PI,10.*PI);
//TF1 *func = new TF1("func","([0]-TMath::ATan(TMath::Sin([2])/abs(TMath::Cos([2])-x/[1])))/[0]",-3,10);
TF1 *func = new TF1("func",angular_acceptance,-3,10,2);
cout<<"sin="<<TMath::Sin(5.*deg_to_rad)<<" cos="<<TMath::Cos(5.*deg_to_rad)<<endl;
//func->SetParameter(0,PI);
func->SetParameter(1,8.25);
func->SetParameter(0,5.*deg_to_rad);



  TH1F *h = new TH1F("h","h",50,-2,2);
  h ->SetLineColor(1);
  TH1F *h2 = new TH1F("h2","h2",50,-2,2);
  h2->SetLineColor(2);
  
  double val,weight,yy;
  double x_gene,x_decay;
  double par[2]={5.*deg_to_rad,8.25};
  for(int i=0;i<10000;i++){
    val  = gRandom->Exp(0.26);
    x_gene  = gRandom->Uniform(-3.,3.);//target region
    x_decay = x_gene + val*0.4*30.;//assume beta =0.4, c=30cm/ns

    val += gRandom->Gaus(0.0,0.2);
    weight = angular_acceptance(&x_decay,&par[0]);
    yy = gRandom->Uniform(0,1);
    if(yy<weight)h->Fill(val);
    h2->Fill(val);
  }


TCanvas *c[2];
for(int i=0;i<2;i++){
 c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),900,800);
}

c[0]->Clear();
c[0]->cd(1);
gPad->SetLogy(1);
h->Draw();
h2->Draw("same");
cout<<h->GetMean()<<"  "<<h2->GetMean()<<endl;
c[1]->Clear();
c[1]->cd(1);
func->Draw();

c[0]->Print("arctan.pdf[");
c[0]->Print("arctan.pdf");
c[1]->Print("arctan.pdf");
c[1]->Print("arctan.pdf]");
}
