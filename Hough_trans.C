#include "Setting.cc"
double get_rho(double x, double y, double phi){
  double rho;

  rho=(x*TMath::Cos(phi) + y*TMath::Sin(phi));

  return rho;
}
/////////////
const int NCanvas = 7;
/////////////
void Hough_trans(){
  gStyle->SetNdivisions(510); // tertiary*10000 + secondary*100 + first
// Title
  gStyle->SetTitleX(0.15);
  gStyle->SetTitleFontSize(0.08);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  Setting *set=new Setting();
  TCanvas *c[NCanvas];
  for(int i=0;i<NCanvas;i++){
    c[i]=new TCanvas(Form("c%d",i),Form("c%d",i),800,800);
  }
  TLatex *latex = new TLatex();
  set->SetTLatex(latex,1,0.1,22);
  TArrow *arrow = new TArrow();
  arrow->SetLineColor(1);arrow->SetLineWidth(2);arrow->SetLineStyle(1);
  TLine *line = new TLine();
  set->SetTLine(line,1,1,1.7);

  double xp[3]={-1.,0.,1.5};
  double yp[3];
  double alpha, beta, rho, phi;
  int phi_nbin=100, rho_nbin=80;


  alpha=0.5;beta=0.7;
  TF1 *f= new TF1("f","[0]*x+[1]",-2.,2.);
  f->SetParameter(0,alpha);
  f->SetParameter(1,beta );
  set->SetTF1(f,2,1,2);

  double x_cross = -beta/(alpha+1./alpha);
  double y_cross =  beta/(alpha*alpha+1.);
  cout<<"crossing point ("<<x_cross<<", "<<y_cross<<")"<<endl;
  rho = sqrt(x_cross*x_cross+y_cross*y_cross);
  phi = acos(x_cross/rho);
  TArc *arc =new TArc(0.,0.,0.2,0.,phi*TMath::RadToDeg());
  arc->SetLineColor(1);arc->SetLineWidth(2);arc->SetLineStyle(1);
  cout<<"(phi, rho) = ("<<phi<<" , "<<rho<<")"<<endl;

  for(int i=0;i<3;i++)yp[i]=f->Eval(xp[i]);
  TGraph *tg = new TGraph(3,xp,yp);
  set->SetGr(tg, "","","",1,1,21,0.7);
  
  double pi=TMath::Pi();
  TH2F* h_frame_xy    =new TH2F("h_frame_xy"    ,"h_frame_xy"    ,10,-2,2,10,-2,2);
  TH2F* h_frame_rhophi=new TH2F("h_frame_rhophi","h_frame_rhophi",phi_nbin,-pi,pi,rho_nbin,-3,3.);
  set->SetTH2(h_frame_xy    ,""      ,"x","y");
  set->SetTH2(h_frame_rhophi,"","#phi","#rho");
  TH2F* h_rhophi[3];

  for(int n=0;n<3;n++){
    h_rhophi[n]=(TH2F*)h_frame_rhophi->Clone();
    for(int i=0;i<phi_nbin;i++){
      double dphi=2*pi/(double)phi_nbin;
      phi = ((double)i+0.5)*dphi-pi;
      rho = get_rho(xp[n],yp[n],phi);
      
      //cout<<n<<" "<<i<<" "<<phi<<" "<<rho<<endl;
      h_rhophi[n]->Fill(phi,rho);
      h_frame_rhophi->Fill(phi,rho);
      
    }
  }

  int locmax, locmay, locmaz;
  int maxbin_cont;
  double phi_calc  ,rho_calc;
  for(int i=0;i<2;i++){
    h_frame_rhophi->GetMaximumBin(locmax,locmay,locmaz);
    maxbin_cont = h_frame_rhophi->GetBinContent(locmax,locmay);  
    phi_calc = h_frame_rhophi->GetXaxis()->GetBinCenter(locmax);
    rho_calc = h_frame_rhophi->GetYaxis()->GetBinCenter(locmay);
    cout<<"(phi, rho) = ("<<phi_calc<<" , "<<rho_calc<<")"<<endl;
    h_frame_rhophi->SetBinContent(locmax,locmay,0);
  }
  

  c[0]->Clear();
  c[0]->cd(1);h_frame_xy->Draw();f->Draw("same");tg->Draw("sameP");
              latex->DrawLatex(xp[0]-0.5,yp[0]+0.25,"A");latex->DrawLatex(xp[1]-0.5,yp[1]+0.25,"B");latex->DrawLatex(xp[2]-0.5,yp[2]+0.25,"C");
  c[1]->Clear();
  c[1]->cd(1);h_frame_xy->Draw();f->Draw("same");tg->Draw("sameP");
  c[2]->Clear();
  c[2]->cd(1);h_frame_rhophi->Draw("colz");


  c[3]->Clear();
  c[3]->cd(1);h_rhophi[0]->Draw("colz");latex->DrawLatex(-2.0,1.00,"A");
  c[4]->Clear();
  c[4]->cd(1);h_rhophi[1]->Draw("colz");latex->DrawLatex(-2.0,1.00,"A");latex->DrawLatex(0.0,0.50,"B");
  c[5]->Clear();
  c[5]->cd(1);h_rhophi[2]->Draw("colz");latex->DrawLatex(-2.0,1.00,"A");latex->DrawLatex(0.0,0.50,"B");
latex->DrawLatex(0.5,2.50,"C");


  c[6]->Clear();
  c[6]->cd(1);h_frame_xy->Draw();f->Draw("same");
              arrow->DrawArrow(0.,0.,x_cross,y_cross,0.012,">");
              arc->Draw("same");
              latex->SetTextSize(0.07);
              latex->DrawLatex( 0.25,0.25,"#phi");
              latex->DrawLatex(-0.30,0.20,"#rho");
               double x0=(x_cross+0.07);
               double y0=(x_cross+0.07)*alpha+beta;
               double dx=0.05;
               double dy=-dx/alpha;
              line->DrawLine(x0 ,y0, x0+dx,y0+dy);
               x0=x0+dx;
               y0=y0+dy;
               dx=-0.06;
               dy=dx*alpha;
              line->DrawLine(x0 ,y0, x0+dx,y0+dy);

  for(int i=0;i<NCanvas;i++){
    c[i]->Print(Form("hough_trans_%d.png",i+1));
  }
}
