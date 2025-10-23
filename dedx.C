  const double Mpi = 139.57018;   // charged pion mass (MeV/c2)
  const double MK  = 493.677;     // charged Kaon mass (MeV/c2)
  const double Mp  = 938.272046;  // proton       mass (MeV/c2)
  const double Me  = 0.510998928; // electron     mass (MeV/c2)
  const double Mmu = 105.6583715; // muon         mass (MeV/c2)
////////////////////////////////////////////////////////////////
double GetBeta(const double M_in, double mom_in){
  double beta;
  beta = mom_in/sqrt(mom_in*mom_in +M_in*M_in);
  return beta;
}
////////////////////////////////////////////////////////////////
double GetEkin(const double M_in, double mom_in){
  double Ekin;
  Ekin = sqrt(mom_in*mom_in +M_in*M_in) - M_in;
  return Ekin;
}
////////////////////////////////////////////////////////////////
double GetdEdx(double beta, double I=64.7, double rho=1.032,double z=1.0, double AZ=2.0){
  double  D, B;
	
  //Ionization energy (eV)
  //	I = 237; //Hexane
  //	I = 78.0; //C (from Leo)
  //	I = 64.7; //plastic scint (from Leo)
  //    I =322;//Cu (from Leo)
  
  //density [g/cm3]
  //	rho = 2.0;   //C
  // 	rho = 1.032; //scint
  //	rho = 4.63e-6;
  //	rho = 4.63e-6; //Cu
  
  //double Wmax=2*Me*1e6*beta*beta/(1.-beta*beta);
  
  D = 0.3071;// 
  B = D*rho*z*z/AZ;
  double dedx     = B*(log(2.0*Me*1e6*beta*beta/(I*(1-beta*beta)))/(beta*beta)-1.0);
  //double dedx2    = B*(0.5*log(2.0*Me*1e6*beta*beta*Wmax/(I*I*(1.-beta*beta)))/(beta*beta)-1.0);
  //cout<<"dE/dx:"<<dedx<<", "<<dedx2<<endl;
  return dedx;
}
////////////////////
void dedx(){
  string ofname_pdf;
  ofname_pdf = "./pdf/dedx.pdf";
  const int step = 20000;
  double mommin=0.01;//GeV/c
  double mommax=120.;  //GeV/c
  //TH2F *h_frame = new TH2F("h_frame","h_frame",10,0,400,10,0,10.);
  //SetTH2(h_frame , "", "E_{kin}[MeV]", "dE/dx[MeV/cm]");
  TH2F *h_frame = new TH2F("h_frame","h_frame",10,mommin,mommax,10,1,10.);
  h_frame->SetTitle("");
  h_frame->GetXaxis()->SetTitle("Mom [GeV/c]");
  h_frame->GetYaxis()->SetTitle("dE/dx [MeV/cm]");
  h_frame->GetXaxis()->CenterTitle();
  h_frame->GetYaxis()->CenterTitle();
  h_frame->GetXaxis()->SetTitleOffset(1.35);
  h_frame->SetStats(0);
  TGraph *tg_pi, *tg_k, *tg_p, *tg_mu;
  tg_pi  =new TGraph();
  tg_k   =new TGraph();
  tg_p   =new TGraph();
  tg_mu  =new TGraph();
  
  for(int i=0;i<step;i++){
    double mom  = mommin+i*(mommax-mommin)/step;

    double beta_pi = GetBeta(Mpi,1000.*mom);
    double Ekin_pi = GetEkin(Mpi,1000.*mom);
    double dedx_pi = GetdEdx(beta_pi);

    double beta_k = GetBeta(MK,1000.*mom);
    double Ekin_k = GetEkin(MK,1000.*mom);
    double dedx_k = GetdEdx(beta_k);

    double beta_p = GetBeta(Mp,1000.*mom);
    double Ekin_p = GetEkin(Mp,1000.*mom);
    double dedx_p = GetdEdx(beta_p);

    double beta_mu = GetBeta(Mmu,1000.*mom);
    double Ekin_mu = GetEkin(Mmu,1000.*mom);
    double dedx_mu = GetdEdx(beta_mu);
    //double dedx_mu = GetdEdx(beta_mu,322.,1.0);//Cu, rho=1 to compare Fig2.3 in Leo

    tg_pi  ->SetPoint(i,mom,dedx_pi);
    tg_k   ->SetPoint(i,mom,dedx_k );
    tg_p   ->SetPoint(i,mom,dedx_p );
    tg_mu  ->SetPoint(i,mom,dedx_mu);
  }
  tg_pi->SetLineColor(2);
  tg_k ->SetLineColor(3);
  tg_p ->SetLineColor(4);
  tg_mu->SetLineColor(6);
  tg_pi->SetLineWidth(2);
  tg_k ->SetLineWidth(2);
  tg_p ->SetLineWidth(2);
  tg_mu->SetLineWidth(2);

  TLegend *leg_beta = new TLegend( 0.7, 0.5, 0.8, 0.8);
  leg_beta -> SetBorderSize(1);
  leg_beta -> SetFillColor(10);
  leg_beta -> SetFillStyle(1001);
  leg_beta -> SetTextFont(42);
  leg_beta -> AddEntry(tg_mu , "#mu"    , "l");
  leg_beta -> AddEntry(tg_pi , "#pi"    , "l");
  leg_beta -> AddEntry(tg_k  , "K"      , "l");
  leg_beta -> AddEntry(tg_p  , "p"      , "l");

  //TLatex *tla_pi = new TLatex(50,4,"#pi");
  //TLatex *tla_p  = new TLatex(100,8,"p");
  //tla_pi->SetTextColor(2);
  //tla_pi->SetTextSize(0.10);
  //tla_pi->SetTextFont(22);
  //tla_pi->SetTextAlign(22);
  //tla_p->SetTextColor(4);
  //tla_p->SetTextSize(0.10);
  //tla_p->SetTextFont(22);
  //tla_p->SetTextAlign(22);

  TCanvas *c1 =new TCanvas("c1","canvas",800,600);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  gPad->SetGrid(1,1);
  h_frame ->Draw();
  tg_pi ->Draw("same");
  tg_k  ->Draw("same");
  tg_p  ->Draw("same");
  tg_mu ->Draw("same");
  //tla_pi->Draw("same");
  //tla_p ->Draw("same");
  //leg_beta ->Draw("same"); 
  
  TCanvas *c2 =new TCanvas("c2","canvas2",800,600);
  h_frame ->Draw();
  gPad->SetLogx(1);
  gPad->SetGrid(1,1);
  tg_pi ->Draw("same");
  tg_k  ->Draw("same");
  tg_p  ->Draw("same");
  tg_mu ->Draw("same");
  leg_beta ->Draw("same"); 

  //c1->Print(Form("%s[",ofname_pdf.c_str()));
  //c1->Print(Form("%s" ,ofname_pdf.c_str()));
  //c2->Print(Form("%s" ,ofname_pdf.c_str()));
  //c2->Print(Form("%s]",ofname_pdf.c_str()));



}
