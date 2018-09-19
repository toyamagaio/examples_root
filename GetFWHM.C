void GetFWHM(){

gROOT->Reset();
gStyle->SetOptStat("MER");
  TH1F* hist = new TH1F("hist","hist",200,-10,10);
  SetTH1(hist,"", "x", "counts/0.1",1,4,3001);
  double bin=(10.-(-10.))/200.;
  
  TLine *line = new TLine(0,0,0,0);//x1,y1,x2,y2
  line->SetLineColor(6);
  line->SetLineWidth(1);
  line->SetLineStyle(1);

  TArrow *arrow = new TArrow(0,0,0,0,0.01,"");//x1,y1,x2,y2,arrow size,option
  arrow->SetAngle(45);
  arrow->SetLineColor(1);
  arrow->SetLineWidth(1);
  
  TLatex *latex = new TLatex(0,0,"Vamos Frontale!!!");//x,y,"text"
  latex->SetTextFont(42);//Please check draw_latex.C
  latex->SetTextSize(0.05);
  latex->SetTextColor(1);
  latex->SetTextAlign(12);
  
  double MPV=0.0;
  double sigma =1.;
  double par[3];//fit parameter
  double er_par[3];//error of fit parameter
  
  gRandom -> SetSeed( time(NULL) ); //seed set by time
  
    for(int i;i<100000;i++){//generate gauss distribution
      double y = gRandom -> Gaus(MPV,sigma);
      hist->Fill(y);
    }
  
  TF1 *ga = new TF1("ga","gaus",-4,14);
  ga->SetLineWidth(3);
  ga->SetLineColor(2);
  ga->SetLineStyle(2);
  
  TCanvas *c1 =new TCanvas("c1","canvas",1200,600);
/////////////////////////////////
//FWHM from fitting
/////////////////////////////////
  c1->Divide(2,1);
  c1->cd(1);
  hist->Draw();
  hist->Fit(ga,"0QR","");
  ga->Draw("same");
  ga->GetParameters(&par[0]);
    for(int i=0;i<3;i++){
      er_par[i]=ga->GetParError(i);
    }
  double factor=2.*sqrt(2.*log(2.));
  latex->DrawLatex(par[1]+1.5*par[2],par[0]*0.8,Form("#sigma^{fit}=%.02lf#pm%.02lf",par[2],er_par[2]) );
  latex->DrawLatex(par[1]+1.5*par[2],par[0]*0.6,Form("FWHM^{fit}=%.02lf#pm%.02lf",par[2]*factor,er_par[2]*factor) );

/////////////////////////////////
//FWHM from histogram
/////////////////////////////////
  double max_val = hist->GetBinContent(hist->GetMaximumBin());
  double first_edge = hist ->GetXaxis()->GetBinCenter(hist ->FindFirstBinAbove(max_val/2.));
  double last_edge  = hist ->GetXaxis()->GetBinCenter(hist ->FindLastBinAbove(max_val/2.));
  double fwhm = last_edge - first_edge;
  cout<<max_val<<"  "<<first_edge<<" "<<last_edge<<" "<<fwhm<<endl;
  c1->cd(2);
  hist->Draw();
  line->DrawLine(first_edge,0,first_edge,max_val/2.);
  line->DrawLine(last_edge,0,last_edge,max_val/2.);
  arrow->DrawArrow(first_edge,max_val/2.,last_edge,max_val/2.,0.01,"<|>");
  latex->DrawLatex(par[1]+1.5*par[2],par[0]*0.6,Form("FWHM^{hist}=%.02lf#pm%.02lf",fwhm,bin) );
  //error is just binning parameter, it is very rough estimation


}
