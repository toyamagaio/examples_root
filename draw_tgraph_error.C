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
  gr->GetYaxis()->SetRangeUser(min,max);
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

void draw_tgraph_error(){
gStyle->SetOptStat(0);
gStyle->SetPadTopMargin(0.1);
gStyle->SetPadRightMargin(0.04);
gStyle->SetPadBottomMargin(0.15);

const int i = 5;
double Vb[i]  ={55,
                56,
                57,
                58,
                58.5};
double sigma_ToF[i]={157,
                     145,
                     118,
                     118,
                     118
                     };
double er_Vb[i];
for(int j=0;j<i;j++){er_Vb[j]=0;}
double er_sigmaToF[i]={7,8,7,7,7};
TGraphErrors *tg_sigmaToF  = new TGraphErrors(i, Vb, sigma_ToF, er_Vb, er_sigmaToF); 
// TGraphError(number of array, x value, y value, error x, error y); 

tg_sigmaToF -> SetMarkerStyle(22);
tg_sigmaToF -> SetMarkerSize(2);
tg_sigmaToF -> SetMarkerColor(6);


TH2F *h_frame = new TH2F("h_frame","h_frame",10,54,60,10,60,180);
SetTH2(h_frame , "#sigma_{ToF} [ps] vs. MPPC bias [V]", "MPPC bias [V]", "#sigma_{ToF}[ps]");

TCanvas *c = new TCanvas("c","c",900,800);
h_frame ->Draw();
tg_sigmaToF  ->Draw("sameP");

}
