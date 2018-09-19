#include <iostream>
#include <sstream>
#include <iomanip>
#include <csignal>
#include <stdlib.h>
#include <climits>
#include <fstream>
#include <math.h>
#include <string>
#include <unistd.h>
using namespace std;

#include "TApplication.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TFile.h"
#include "TLeaf.h"
#include "TTree.h"
#include "TCut.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TGraph.h"
#include "TLine.h"
#include "TLatex.h"
#include "TText.h"
#include <TLegend.h>
#include "TStyle.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TProfile.h"
#include "TString.h"
#include "TPaveText.h"
#include "TSystem.h"

#include "TRandom.h"
#include "Tree.h"

void SetGrErr(TGraphErrors *gr, TString hname, TString xname, TString yname, int LColor, int MColor, int MStyle, double Yoffset, double min, double max){
  gr->SetTitle(hname);
  gr->SetName(hname);
  gr->GetXaxis()->SetTitle(xname);
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->SetTitle(yname);
  gr->GetYaxis()->CenterTitle();
  gr->SetLineColor(LColor);
  gr->SetMarkerStyle(MStyle);
  gr->SetMarkerColor(MColor);
  gr->SetMarkerSize(0.5);
  gr->GetYaxis()->SetTitleOffset(Yoffset);
//  gr->GetYaxis()->SetRangeUser(min,max);
}

void SetTH2(TH2F *h2, TString hname, TString xname, TString yname){
  h2->SetTitle(hname);
  h2->GetXaxis()->SetTitle(xname);
  h2->GetXaxis()->CenterTitle();
  h2->GetXaxis()->SetNdivisions(205);
  h2->GetYaxis()->SetTitle(yname);
  h2->GetYaxis()->CenterTitle();
  h2->SetMinimum(0.8);
  h2->GetYaxis()->SetTitleOffset(1.5);
  h2->SetLineWidth(0);
  h2->SetTitleSize(0.05,"");
}
////////////////

void draw_tgraph(){
gStyle->SetOptStat(0);
gStyle->SetPadTopMargin(0.1);
gStyle->SetPadRightMargin(0.04);
gStyle->SetPadBottomMargin(0.15);

double LedV[9]  ={1.715,
                   1.8,
                   1.9,
                   2.0,
                   2.1,
                   2.2,
                   2.3,
                   2.6,
                   1.715};
double sigmat[9] ={368,
                   254,
                   201,
                   166,
                   142,
                   128,
                   92,
                   73,
                   365};
int i = 9;
TGraph *tg_sigmat  = new TGraph(i, LedV, sigmat); 

tg_sigmat -> SetMarkerStyle(22);
tg_sigmat -> SetMarkerSize(2);
tg_sigmat -> SetMarkerColor(6);


TH2F *h_sigmatframe = new TH2F("h_sigmatframe","h_sigmatframe",10,1.7,2.7,10,60,400);
SetTH2(h_sigmatframe , "#sigma_{t} [ps] vs. LED bias [V]", "LED bias [V]", "#sigma_{t}[ps]");

TCanvas *c = new TCanvas("c","c",900,800);
h_sigmatframe ->Draw();tg_sigmat ->Draw("sameP");

}
