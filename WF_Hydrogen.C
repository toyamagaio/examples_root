//graphics of wave function of hydrogen
#include "Setting.cc"
void WF_Hydrogen(){
  gStyle->SetNdivisions(510); // tertiary*10000 + secondary*100 + first
// Title
  gStyle->SetTitleX(0.15);
  gStyle->SetTitleFontSize(0.08);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);
  Setting *set=new Setting();

  TLegend *leg = new TLegend( 0.70, 0.70, 0.90, 0.90);
  leg -> SetBorderSize(1);
  leg -> SetFillColor(0);
  leg -> SetFillStyle(1);
  leg -> SetTextFont(22);

  double a = 0.0528;//Bohr-radius [nm]
  
  TH2D *h_frame[2];
  h_frame[0] = new TH2D("h_frame1","h_frame1",10,0,1,10,-20,180);
  h_frame[1] = new TH2D("h_frame2","h_frame2",10,0,1,10,0,12);
  set->SetTH2(h_frame[0],"","r [nm]","R_{nl} [nm^{-3/2}]");
  set->SetTH2(h_frame[1],"","r [nm]","|R_{nl}r|^{2} [nm^{-1}]");
  TF1 *fr[3], *fr_rs[3];//R_nl, R_nl*r^2
  int col[3]={2,4,6};
  fr[0]   =new TF1("fr1"   ,"2.*pow(1./[0],1.5)*exp(-x/[0])"                 ,0,5);
  fr[1]   =new TF1("fr2"   ,"pow(1./(2.*[0]),1.5)*(2.-x/[0])*exp(-0.5*x/[0])",0,5);
  fr[2]   =new TF1("fr3"   ,"pow(1./(2.*[0]),1.5)*(x/[0])*exp(-0.5*x/[0])/sqrt(3.)",0,5);
  fr_rs[0]=new TF1("fr_rs1","pow(  2.* pow(1./(1.*[0]),1.5) * exp(-x/[0])*x                   ,2)",0,5);
  fr_rs[1]=new TF1("fr_rs2","pow(      pow(1./(2.*[0]),1.5)*(2.-x/[0])*exp(-0.5*x/[0]) *x     ,2)",0,5);
  fr_rs[2]=new TF1("fr_rs3","pow(      pow(1./(2.*[0]),1.5)*(x/[0])*exp(-0.5*x/[0])/sqrt(3.)*x,2)",0,5);
  //fr_rs[0]=new TF1("fr_rs1","4.*pow(1./[0],3)*exp(-2.*x/[0])/(x*x)",0,5);
  //fr_rs[1]=new TF1("fr_rs2","pow(1./(2.*[0]),3)*(2.-x/[0])*(2.-x/[0])*exp(-x/[0])/(x*x)",0,5);
  for(int i=0;i<3;i++){
    fr[i]   ->SetParameter(0,a);
    fr_rs[i]->SetParameter(0,a);
    set->SetTF1(fr[i]   ,col[i],1,1);
    set->SetTF1(fr_rs[i],col[i],1,1);
    //cout<<fr_rs[i]->Integral(0,100)<<endl;
  }
  leg -> AddEntry(fr[0],"R_{10}","l");
  leg -> AddEntry(fr[1],"R_{20}","l");
  leg -> AddEntry(fr[2],"R_{21}","l");
  //fr[1]=new TF1("fr2","",0,5);
  //fr[2]=new TF1("fr3","",0,5);
  
  TCanvas *c[2];
  for(int i=0;i<2;i++)c[i]=new TCanvas(Form("c%d",i+1),Form("c%d",i+1),800,800);

  c[0]->Clear();c[0]->cd(1);
  h_frame[0]->Draw();for(int i=0;i<3;i++)fr[i]->Draw("same");
  leg->Draw("same");

  c[1]->Clear();c[1]->cd(1);
  h_frame[1]->Draw();for(int i=0;i<3;i++)fr_rs[i]->Draw("same");
  leg->Draw("same");

  c[0]->Print("pdf/WF_Hyd.pdf[");
  c[0]->Print("pdf/WF_Hyd.pdf");
  c[1]->Print("pdf/WF_Hyd.pdf");
  c[1]->Print("pdf/WF_Hyd.pdf]");
}
