void SetTH2(TH2F *h2, TString hname, TString xname, TString yname){
  h2->SetTitle(hname);
  h2->GetXaxis()->SetTitle(xname);
  h2->GetXaxis()->CenterTitle();
//  h2->GetXaxis()->SetNdivisions(000);
  h2->GetYaxis()->SetTitle(yname);
  h2->GetYaxis()->CenterTitle();
//  h2->GetYaxis()->SetNdivisions(000);
  h2->SetMinimum(0.8);
  h2->GetYaxis()->SetTitleOffset(1.5);
  h2->SetLineWidth(0);
  h2->SetTitleSize(0.05,"");
}

void draw_tlatex(){

TH2F *h_frame = new TH2F("h_frame","h_frame",10,-0.2, 2.2, 10, -0.2, 2.2);
//SetTH2(h_frame , "box", "x", "y");
h_frame->GetXaxis()->SetNdivisions(000);
h_frame->GetYaxis()->SetNdivisions(000);
h_frame->SetStats(0);
h_frame->SetTitle();
double x0 = 0.10;
double y0 = 0.50;

TLine *line  = new TLine(0.,0.,0., 0.);
line ->SetLineColor(4);
line ->SetLineWidth(2.0);
line ->SetLineStyle(2);

TLatex *latex = new TLatex(x0,y0,"");
latex->SetTextFont(22);//20->Times bold, 2->precision
latex->SetTextSize(0.05);//ratio against canvas pad size
latex->SetTextColor(1);
//latex->SetTextAlign(22);//center-center(x y)
//latex->SetTextAlign(12);//left-center
//latex->SetTextAlign(11);//left-bottom



TCanvas *c = new TCanvas("c","c",900,800);
h_frame ->Draw();
line->DrawLine( 0.0,-0.2, 0.0, 2.2);
line->Draw("same");
line->DrawLine( 1.0,-0.2, 1.0, 2.2);
line->Draw("same");
line->DrawLine( 2.0,-0.2, 2.0, 2.2);
line->Draw("same");
line->DrawLine(-0.2, 0.0, 2.2, 0.0);
line->Draw("same");
line->DrawLine(-0.2, 1.0, 2.2, 1.0);
line->Draw("same");
line->DrawLine(-0.2, 2.0, 2.2, 2.0);
line->Draw("same");

latex  ->SetTextAlign(11);//left-bottom
latex  ->DrawLatex(0.,2.,"Align11");
//latex  ->Draw("same");

latex  ->SetTextAlign(12);//left-center
latex  ->DrawLatex(0.,1.,"Align12");
//latex  ->Draw("same");

latex  ->SetTextAlign(13);//left-top
latex  ->DrawLatex(0.,0.,"Align13");

latex  ->SetTextAlign(21);//center-bottom
latex  ->DrawLatex(1.,2.,"Align21");

latex  ->SetTextAlign(22);//center-center
latex  ->DrawLatex(1.,1.,"Align22");

latex  ->SetTextAlign(23);//center-top
latex  ->DrawLatex(1.,0.,"Align23");

latex  ->SetTextAlign(31);//right-bottom
latex  ->DrawLatex(2.,2.,"Align31");

latex  ->SetTextAlign(32);//right-center
latex  ->DrawLatex(2.,1.,"Align32");

latex  ->SetTextAlign(33);//right-top
latex  ->DrawLatex(2.,0.,"Align33");

TCanvas *c1 = new TCanvas("c1","c1",900,800);
h_frame ->Draw();
double ypos=2.;
latex  ->SetTextAlign(22);//c-c

for(int i=1;i<16;i++){
latex  ->SetTextFont(10*i+2);
latex  ->DrawLatex(1.,ypos,Form("Font%d2",i));
ypos -= 0.15;
}


c->Print("latex.pdf[");
c->Print("latex.pdf");
c1->Print("latex.pdf");
c1->Print("latex.pdf]");

}
