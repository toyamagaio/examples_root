//Demonstration of time walk correction
//#include "Setting.cc"
//
const int NCanvas = 4;
/////////////////
double f_sqinv(double  x){
  double p[2];
  p[0]=-5;
  p[1]=0;
  double val=p[0]/TMath::Sqrt(x-p[1]);
  //cout<<x<<" "<<val<<endl;
  return val;
}
/////////////////
void fit_slice(){
  gROOT->Reset();
  gRandom -> SetSeed( time(NULL) ); //seed set by time
  gStyle->SetOptStat(0);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);

  TH2D *h2 = new TH2D("h2","h2",100,0,100,100,-10,10);

  //Event generation  
  //x:QDC,  y:ToF in a realistic analysis
  int ENum = 10000;
  for(int n=0;n<ENum;n++){
    if(n%1000==0)cout<< n <<" / "<<ENum<<endl;
    double x=gRandom->Uniform(0,100);
    double y=gRandom->Gaus(0.,1.)+f_sqinv(x);//  ;
    //cout<<x<<" "<<y<<" "<<f_sqinv(x)<<endl;
    //cout<<f_sqinv(x)<<endl;
    h2->Fill(x,y);
  }


  //////////////
  //FitSlicesY//
  //////////////
  TF1 *f_ga = new TF1("f_ga","gaus",-10,10);    
  h2->FitSlicesY(f_ga,0,-1,2,"QNRG2");
  //FitSlicesY( TF1*f1=0,Int_t firstxbin = 0,Int_t lastxbin = -1, cut =0,Option_t* option = "QNR",TObjArray*arr=0)
  //f1: fit function for projection
  //Option: Q : quiet mode
  //        N : do not show the result of fit
  //        R : fit the function in the specific function range
  //        G2 : merge 2 consecutive bins along Y
  //        G3 : merge 3 consecutive bins along Y
  //        G4 : merge 4 consecutive bins along Y
  //        S sliding merge: merge n consecutive bins along Y accordingly to what Gn is given. It makes sense when used together with a Gn option
  TH1D *h_slice = (TH1D*)gROOT->FindObject("h2_1");

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  TF1 *f_sq = new TF1("f_sq","[0]/sqrt(x-[1])+[2]",0,100);
  f_sq->SetNpx(2000);
  f_sq->SetLineColor(2);
  f_sq->SetLineWidth(2);
  
  h_slice ->Fit(f_sq,"","0QR",0,100);

  c1->Clear();
  c1->Divide(2,2);
  c1->cd(1);h2->Draw("colz");
  c1->cd(2);h2->Draw("colz");h_slice->Draw("same");
  c1->cd(3);h_slice->Draw("");f_sq->Draw("same");
}
