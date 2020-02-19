//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetTH2org(TH2 *h, TString name, TString xname, TString yname, double min=0.8){
  h->SetTitle(name);
  h->SetMinimum(min);
  h->SetLineWidth(0);
  h->SetStats(0);
  h->SetTitleSize(0.08,"");
  h->SetTitleSize(0.08,"x");
  h->SetTitleSize(0.08,"y");
  //h->SetMarkerStyle(1);
  //h->SetMarkerSize(1.5);
  h->SetMarkerColor(1);

  h->GetXaxis()->SetTitle(xname);
  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetTitleOffset(0.90);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelOffset(0.01);
  h->GetXaxis()->SetLabelSize(0.05);

  h->GetYaxis()->SetTitle(yname);
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleOffset(1.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelOffset(0.01);
  h->GetYaxis()->SetLabelSize(0.045);
  ((TGaxis*)h->GetYaxis())->SetMaxDigits(3);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void draw_TH2(){
  gStyle->SetNdivisions(510); // tertiary*10000 + secondary*100 + first
// Title
  gStyle->SetTitleX(0.15);
  gStyle->SetTitleFontSize(0.08);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFont(42,"XYZ");

  TH2F *h2 = new TH2F("h2","h2",30,-1, 1,30,-1,1);
  TH2F *h2_scat, *h2_colz, *h2_arr, *h2_box,*h2_cont, *h2_cont1,*h2_cont2,*h2_cont3,*h2_cont4;
  TH2F *h2_text, *h2_lego, *h2_lego2, *h2_surf, *h2_surf2, *h2_surf3;
  TH2F *h2_contz, *h2_cont4z, *h2_lego2z, *h2_surf2z;
  SetTH2org(h2,"2D hist","x","y");


  //gRandom->SetSeed(0);
  gRandom -> SetSeed( time(NULL) ); //seed set by time
  double mean  = 0.;
  double sigma = 0.3;
  int ENum = 100000;

  for(int i=0;i<ENum;i++){
    double x = gRandom->Gaus(mean,sigma);
    double y = gRandom->Gaus(mean,sigma);
    h2 ->Fill(x,y);
  }

  h2->SetContour(99);

  h2_scat   =(TH2F*)h2->Clone();
  h2_colz   =(TH2F*)h2->Clone();
  h2_arr    =(TH2F*)h2->Clone();
  h2_box    =(TH2F*)h2->Clone();
  h2_cont   =(TH2F*)h2->Clone();
  h2_contz  =(TH2F*)h2->Clone();
  h2_cont1  =(TH2F*)h2->Clone();
  h2_cont2  =(TH2F*)h2->Clone();
  h2_cont3  =(TH2F*)h2->Clone();
  h2_cont4z =(TH2F*)h2->Clone();
  h2_text   =(TH2F*)h2->Clone();
  h2_lego   =(TH2F*)h2->Clone();
  h2_lego2z =(TH2F*)h2->Clone();
  h2_surf   =(TH2F*)h2->Clone();
  h2_surf2z =(TH2F*)h2->Clone();
  h2_surf3  =(TH2F*)h2->Clone();
  TCanvas *c1 = new TCanvas("c1","c1",900,900);
  c1->Divide(4,4);
  c1->cd(1); gPad->SetLogz(1);h2_scat   ->SetTitle("scat");  h2_scat   ->Draw("scat");//default
  c1->cd(2); gPad->SetLogz(1);h2_colz   ->SetTitle("colz");  h2_colz   ->Draw("colz");
  c1->cd(3); gPad->SetLogz(0);h2_arr    ->SetTitle("arr");   h2_arr    ->Draw("arr");
  c1->cd(4); gPad->SetLogz(0);h2_box    ->SetTitle("box");   h2_box    ->Draw("box");
  c1->cd(5); gPad->SetLogz(0);h2_cont   ->SetTitle("cont");  h2_cont   ->Draw("cont");
  c1->cd(6); gPad->SetLogz(0);h2_contz  ->SetTitle("contz"); h2_contz  ->Draw("contz");
  c1->cd(7); gPad->SetLogz(0);h2_cont1  ->SetTitle("cont1"); h2_cont1  ->Draw("cont1");
  c1->cd(8); gPad->SetLogz(0);h2_cont2  ->SetTitle("cont2"); h2_cont2  ->Draw("cont2");
  c1->cd(9); gPad->SetLogz(0);h2_cont3  ->SetTitle("cont3"); h2_cont3  ->Draw("cont3");
  c1->cd(10);gPad->SetLogz(1);h2_cont4z ->SetTitle("cont4z");h2_cont4z ->Draw("cont4z");
  c1->cd(11);gPad->SetLogz(0);h2_text   ->SetTitle("text");  h2_text   ->Draw("text");
  c1->cd(12);gPad->SetLogz(0);h2_lego   ->SetTitle("lego");  h2_lego   ->Draw("lego");
  c1->cd(13);gPad->SetLogz(0);h2_lego2z ->SetTitle("lego2z");h2_lego2z ->Draw("lego2z");
  c1->cd(14);gPad->SetLogz(0);h2_surf   ->SetTitle("surf");  h2_surf   ->Draw("surf");
  c1->cd(15);gPad->SetLogz(0);h2_surf2z ->SetTitle("surf2z");h2_surf2z ->Draw("surf2z");
  c1->cd(16);gPad->SetLogz(0);h2_surf3  ->SetTitle("surf3"); h2_surf3  ->Draw("surf3");


  c1->Print("root_TH2.pdf");
}
