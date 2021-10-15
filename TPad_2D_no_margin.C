const int Nx = 4;
const int Ny = 4;
const double Lm = 0.10;//left margin
const double Rm = 0.05;//right margin
const double Tm = 0.05;//top margin
const double Bm = 0.10;//bottom margin

void TPad_2D_no_margin() {

  TCanvas *c1 = new TCanvas("c1","multipads",1000, 500);
  TCanvas *c2 = new TCanvas("c2","multipads2",1000, 500);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TPad *tp[Nx][Ny];
  TH1F *h[Nx][Ny];

  TLatex *latex = new TLatex();
  latex->SetTextFont(22);//20->Times bold, 2->precision
  latex->SetTextSize(0.15);//ratio against canvas pad size
  latex->SetTextColor(1);
  latex->SetTextAlign(22);//center-center

  double W = (1.0 - Lm - Rm)/(double)Nx;
  double H = (1.0 - Tm - Bm)/(double)Ny;
  cout<<"W:"<<W<<", H:"<<H<<endl;

  c2->cd();
  for(int ix=0;ix<Nx;ix++){
    for(int iy=0;iy<Ny;iy++){
      tp[ix][iy] = new TPad(Form("tp_%d_%d",ix, iy),"", Lm + ix*W, 1.-Tm -(iy+1.)*H,  Lm + (ix+1.)*W, 1.-Tm -iy*H,0,5,0);

      h[ix][iy] = new TH1F(Form("h_%d_%d",ix, iy),"",20,-3,3);
      if(ix >  0   )tp[ix][iy]->SetLeftMargin(0);
      if(ix != Nx-1)tp[ix][iy]->SetRightMargin(0);
      if(iy >  0   )tp[ix][iy]->SetTopMargin(0);
      if(iy != Ny-1)tp[ix][iy]->SetBottomMargin(0);
      h[ix][iy]->FillRandom("gaus",500);
      tp[ix][iy]->Draw();
    }
  }


  

  for(int ix=0;ix<Nx;ix++){
    for(int iy=0;iy<Ny;iy++){
      tp[ix][iy]->cd();
      h[ix][iy]->Draw();
      latex->DrawLatexNDC(0.5,0.5, Form("ix: %d iy: %d",ix,iy));
    }
  }
  c1->cd();
  latex->DrawLatexNDC(0.5,0.05, "x-title");
}
