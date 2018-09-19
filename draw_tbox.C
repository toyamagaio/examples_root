void SetTH2(TH2F *h2, TString hname, TString xname, TString yname){
  h2->SetTitle(hname);
  h2->GetXaxis()->SetTitle(xname);
  h2->GetXaxis()->CenterTitle();
  h2->GetXaxis()->SetNdivisions(000);
  h2->GetYaxis()->SetTitle(yname);
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetNdivisions(000);
  h2->SetMinimum(0.8);
  h2->GetYaxis()->SetTitleOffset(1.5);
  h2->SetLineWidth(0);
  h2->SetTitleSize(0.05,"");
}

void draw_tbox(){

TH2F *h_frame = new TH2F("h_frame","h_frame",10,0,1,10,0,1);
//SetTH2(h_frame , "box", "x", "y");
h_frame->GetXaxis()->SetNdivisions(000);
h_frame->GetYaxis()->SetNdivisions(000);
h_frame->SetStats(0);
h_frame->SetTitle();
double x0 = 0.10;
double y0 = 0.50;

//TLatex *latex = new TLatex(x0,y0,"this is example");
TLatex *latex = new TLatex(x0,y0,"{}^{3}_{#Lambda} H is simplest hypernucleus");
latex->SetTextFont(22);//20->Times bold, 2->precision
latex->SetTextSize(0.05);//ratio against canvas pad size
latex->SetTextColor(1);
//latex->SetTextAlign(22);//center-center(x y)
//latex->SetTextAlign(12);//left-center
latex->SetTextAlign(11);//left-bottom



TCanvas *c = new TCanvas("c","c",900,800);
h_frame ->Draw();
latex   ->Draw("same");
double xwidth = latex->GetXsize();
double ywidth = latex->GetYsize();
cout<<"x width="<<xwidth<<", y width="<<ywidth<<endl;

double xmergine=gPad->GetX2();
double ymergine=gPad->GetY2();
cout<<"x mergine="<<xmergine<<", y mergine="<<ymergine<<endl;

TBox *box = new TBox(x0,y0,x0+xwidth+0.1,y0+ywidth);
//box->SetFillStyle(3001);

box->SetFillStyle(1001);//solid
box->SetFillColor(2);//
box     ->Draw("same");
latex   ->Draw("same");

}
