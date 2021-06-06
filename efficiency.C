#include "Setting.cc"
void efficiency(){

  Setting *set=new Setting();
  int Total[6]={10,100,1000,10000,100000,1000000};
  double eff[10]={0.01,0.05,0.1,0.3,0.5,0.7,0.9,0.95,0.99,0.999};

  TGraphErrors *tg_bi_eff[10];
  TGraph *tg_bi_err[6], *tg_tedef_err_high[6], *tg_tedef_err_low[6];

  TEfficiency *pEff_def[10];
  TLegend *leg_err = new TLegend( 0.40, 0.20, 0.60, 0.40);
  leg_err -> SetBorderSize(1);
  leg_err -> SetFillColor(0);
  leg_err -> SetFillStyle(1);
  leg_err -> SetTextFont(22);
  
  for(int k=0;k<10;k++){
    tg_bi_eff[k]=new TGraphErrors();
    set->SetGrErr(tg_bi_eff[k],Form("eff. =%03lf binary",eff[k]),"N","efficiency",1,1,22+k);

    pEff_def[k] = new TEfficiency(Form("pEff_def%d:eff.=%03lf:N:efficiency",k+1,eff[k]),"",Total[5],0,Total[5]);
    pEff_def[k]->SetLineColor(2);
  }
  for(int i=0;i<6;i++){
    tg_bi_err[i]        =new TGraph();
    tg_tedef_err_high[i]=new TGraph();
    tg_tedef_err_low[i] =new TGraph();
    set->SetGr(tg_bi_err[i],Form("N=%d",Total[i]),"Efficiency","",1,1,22,1.0);
    set->SetGr(tg_tedef_err_high[i],Form("N=%d",Total[i]),"Efficiency","",2,2,23,1.0);
    set->SetGr(tg_tedef_err_low[i] ,Form("N=%d",Total[i]),"Efficiency","",4,4,24,1.0);
    tg_tedef_err_high[i]->SetMinimum(0.);
  }
  leg_err -> AddEntry(tg_bi_err[0]        ,"Binary"   ,"p");
  leg_err -> AddEntry(tg_tedef_err_high[0],"TEff. up" ,"p");
  leg_err -> AddEntry(tg_tedef_err_low[0] ,"TEff. low","p");
  
  for(int i=0;i<6;i++){
    for(int k=0;k<10;k++){
      int Passed = Total[i]*eff[k];
      double epsilon = (double)Passed/(double)Total[i];
      double er_bi = sqrt(epsilon*(1.-epsilon)/(double)Total[i]);
      //cout<<Total[i]<<" "<<Passed<<" "<<eff[k]<<" "<<er_bi<<endl;
      tg_bi_eff[k]->SetPoint(i,Total[i],epsilon);
      tg_bi_eff[k]->SetPointError(i,0.,er_bi);

      tg_bi_err[i]->SetPoint(k,epsilon,er_bi);

      pEff_def[k]->SetTotalEvents(Total[i]  ,Total[i]);
      pEff_def[k]->SetPassedEvents(Total[i] ,Passed);

      double e_high=pEff_def[k]->GetEfficiencyErrorUp(Total[i]);
      double e_low =pEff_def[k]->GetEfficiencyErrorLow(Total[i]);
      tg_tedef_err_high[i]->SetPoint(k,epsilon,e_high);
      tg_tedef_err_low[i] ->SetPoint(k,epsilon,e_low);

      cout<<Form("%d %d %.03lf %.03lf %lf %lf %lf",Total[i],Passed, eff[k],epsilon, er_bi, e_high, e_low)<<endl;
    }
  }

  ///
  //for(int i=0;i<6;i++){
  //  for(int k=0;k<10;k++){
  //    int Passed = Total[i]*eff[k];
  //    double epsilon = (double)Passed/(double)Total[i];
  //    double e_high=pEff_def[k]->GetEfficiencyErrorUp(Total[i]);
  //    double e_low =pEff_def[k]->GetEfficiencyErrorLow(Total[i]);
  //    tg_tedef_err_high[i]->SetPoint(k,epsilon,e_high);
  //    tg_tedef_err_low[i] ->SetPoint(k,epsilon,e_low);
  //  }
  //}

  TCanvas *c[6];
  
  for(int i=0;i<6;i++){
    c[i]=new TCanvas(Form("c%d",i+1),Form("c%d",i+1),800,800);
  }

  c[0]->Clear();
  c[0]->Divide(2,2);
  for(int i=0;i<4;i++){
    c[0]->cd(i+1);gPad->SetLogx(1);
    pEff_def[i]->Draw("AP");
    tg_bi_eff[i]->Draw("sameP");
  }

  c[1]->Clear();
  c[1]->Divide(2,2);
  for(int i=0;i<4;i++){
    c[1]->cd(i+1);gPad->SetLogx(1);
    pEff_def[i+4]->Draw("AP");
    tg_bi_eff[i+4]->Draw("sameP");
  }

  c[2]->Clear();
  c[2]->Divide(2,2);
  for(int i=0;i<2;i++){
    c[2]->cd(i+1);gPad->SetLogx(1);
    pEff_def[i+8]->Draw("AP");
    tg_bi_eff[i+8]->Draw("sameP");
  }
  //tg_bi_err[2]->Draw("AP");
  //tg_bi_eff[2]->Draw("AP");
  c[3]->Clear();
  c[3]->Divide(1,2);
  for(int i=0;i<2;i++){
    c[3]->cd(i+1);gPad->SetLogx(0);
    tg_tedef_err_high[i]->Draw("AP");
    tg_tedef_err_low[i] ->Draw("sameP");
    tg_bi_err[i]->Draw("sameP");
    leg_err ->Draw("same");
  }

  c[4]->Clear();
  c[4]->Divide(1,2);
  for(int i=0;i<2;i++){
    c[4]->cd(i+1);gPad->SetLogx(0);
    tg_tedef_err_high[i+2]->Draw("AP");
    tg_tedef_err_low[i+2] ->Draw("sameP");
    tg_bi_err[i+2]->Draw("sameP");
    leg_err ->Draw("same");
  }

  c[5]->Clear();
  c[5]->Divide(1,2);
  for(int i=0;i<2;i++){
    c[5]->cd(i+1);gPad->SetLogx(0);
    tg_tedef_err_high[i+4]->Draw("AP");
    tg_tedef_err_low[i+4] ->Draw("sameP");
    tg_bi_err[i+4]->Draw("sameP");
    leg_err ->Draw("same");
  }

  c[0]->Print("pdf/tefficiency.pdf[");
  for(int i=0;i<6;i++)c[i]->Print("pdf/tefficiency.pdf");
  c[5]->Print("pdf/tefficiency.pdf]");
}
///
void efficiency_lowstat(){
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  TH1D *h_pass  = new TH1D("h_pass" ,"h_pass" ,6,0,12);
  TH1D *h_total = new TH1D("h_total","h_total",6,0,12);

  TLatex *latex = new TLatex();
  latex->SetTextFont(22);//20->Times bold, 2->precision
  latex->SetTextSize(0.05);//ratio against canvas pad size
  latex->SetTextColor(1);
  latex->SetTextAlign(13);

  //bin:   1   2   3    4   5    6  
  //mean:  1   3   5    7   9   11  
  //pass:  0   1   0    1   0   10  
  //tot:   1   1  10   10   0   10  
  //val:  0/1 1/1 0/10 1/10 0  10/10

  double mean[]={1,  3 , 5 ,  7  ,  9 , 11};
  int    pass[]={0,  1 , 0 ,  1  ,  0 , 10};
  int    tot[] ={1,  1 ,10 , 10  ,  0 , 10};

  h_pass->Fill(3);
  h_pass->Fill(7);
  h_total->Fill(1);
  h_total->Fill(3);
  for(int i=0;i<10;i++){
    h_pass ->Fill(11);
    h_total->Fill(5);
    h_total->Fill(7);
    h_total->Fill(11);
  }


  TEfficiency  *pEff = new TEfficiency( *h_pass, *h_total);
  pEff->SetTitle("Efficiency;val;Efficiency");
  double e_mean=pEff->GetEfficiency(1);
  double e_high=pEff->GetEfficiencyErrorUp(1);
  double e_low =pEff->GetEfficiencyErrorLow(1);
  cout<<"first bin"<<e_mean<<" +"<<e_high<<" -"<<e_low<<endl;

  TCanvas *c1=new TCanvas("c1","c1",1200,800);
  c1->Divide(2,2);
  c1->cd(1);gPad->SetLogy(0);h_pass ->Draw();
  c1->cd(2);gPad->SetLogy(0);h_total->Draw();
  c1->cd(3);gPad->SetLogy(0);pEff->Draw("AP");
  for(int i=0;i<6;i++)latex->DrawLatex(mean[i]+0.2,0.8,Form("%d/%d",pass[i],tot[i]));
  c1->cd(4);gPad->SetLogy(1);pEff->Draw("AP");
  for(int i=0;i<6;i++)latex->DrawLatex(mean[i]+0.2,0.8,Form("%d/%d",pass[i],tot[i]));


}
///
void efficiency_aaa(){

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
////
