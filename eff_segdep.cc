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
  gr->SetMarkerSize(4.0);
  gr->GetYaxis()->SetTitleOffset(Yoffset);
//  gr->GetYaxis()->SetRangeUser(min,max);
}

void SetTH2(TH2F *h2, TString hname, TString xname, TString yname){
  h2->SetTitle(hname);
  h2->GetXaxis()->SetTitle(xname);
  h2->GetXaxis()->SetTitleOffset(0.65);
//  h2->GetXaxis()->CenterTitle();
  h2->GetXaxis()->SetNdivisions(505);
  h2->GetYaxis()->SetTitle(yname);
  h2->GetYaxis()->SetTitleOffset(0.52);
  h2->GetYaxis()->CenterTitle();
  h2->SetMinimum(0.8);
  h2->SetLineWidth(0);
  h2->SetTitleSize(0.06,"x");
  h2->SetTitleSize(0.06,"y");
}

////////////////
void ReadCSV(string ifname,  vector<double> &xaxis,vector<double> &yaxis,  vector<double> &er_x,vector<double> &er_y, int &count, double xaxismin,double xaxismax, double xaxisoffset){
  ifstream ifs( ifname.c_str() );
  if ( ifs.fail() ) {
    std::cout << "file open fail : " << ifname << std::endl;
    return;
  }
  std::cout<<ifname.c_str()<<std::endl;
  string line;
double x,y,ey,ex;
double runnum;

count=0;
  while(!ifs.eof()){
    getline(ifs,line);
    if(line[0]=='#') continue;
  istringstream sline(line);
//csv data structure expected
/* runnum xvalue yvalue yerror  */
//for each line
  sline >> runnum;
  sline >> x;
  sline >> y;
  sline >> ey;
      ex=0;
if( (x + xaxisoffset)> xaxismin    && (x + xaxisoffset) < xaxismax){

   xaxis.push_back(x + xaxisoffset);
   er_x.push_back(ex);
   yaxis.push_back(y);
   er_y.push_back(ey);
    count++;
//    if(count%1000==0)cout<<"count = "<<count<<", xaxis = "<<t*1E9 + xaxisoffset<<", voltage = "<<v<<endl;
//    if(count>100)break;
  }
 }
cout<<"count = "<<count<<" "<<xaxis.size()<<endl;
cout<<"end of file"<<endl;

}
////////////////

int main(int argc, char** argv){
gStyle->SetOptStat(0);
gStyle->SetPadGridX(0);
gStyle->SetPadGridY(0);
gStyle->SetPadTopMargin(0.1);
gStyle->SetPadRightMargin(0.04);
gStyle->SetPadBottomMargin(0.17);
  TApplication theApp("App", &argc, argv);
  gROOT->SetBatch(1);
string ifname1 = "./csvfile/efficiency_segdepTDL1.csv";
string ifname2 = "./csvfile/efficiency_segdepTDL2.csv";
string ifname3 = "./csvfile/efficiency_segdepTDL3.csv";
string ifname4 = "./csvfile/eff_run41_tdl1.csv";
string ifname5 = "./csvfile/eff_run41_tdl2.csv";
string ifname6 = "./csvfile/eff_run41_tdl3.csv";
double xaxismin =   0;
double xaxismax =   7;
double Ymin =   0;
double Ymax = 105;
TH2F *h_frame = new TH2F("h_frame","h_frame",10,xaxismin,xaxismax,10,Ymin,Ymax);
SetTH2(h_frame , "", "Num. of segment", "efficiency[%]");
TH2F *h_frame2 = new TH2F("h_frame2","h_frame2",10,xaxismin,xaxismax,10,60,90.);
SetTH2(h_frame2 , "ToF resolution", "Vb [V]", "RMS_{ToF}[ps]");
TGraphErrors *tg1, *tg2, *tg3, *tg4, *tg5, *tg6;

vector<double> xaxis1, xaxis2, xaxis3, xaxis4, xaxis5, xaxis6;
vector<double> ex1, ex2, ex3, ex4, ex5, ex6;
vector<double> eff1, eff2, eff3, eff4, eff5, eff6;
vector<double> e_eff1, e_eff2, e_eff3, e_eff4, e_eff5, e_eff6;
int count1,count2,count3,count4,count5,count6;
double xaxisoffset=0;

TLegend *leg_eff = new TLegend( 0.70, 0.20, 0.95, 0.50);
leg_eff -> SetBorderSize(1);
leg_eff -> SetFillColor(0);
leg_eff -> SetFillStyle(1);
leg_eff -> SetTextFont(22);
TCanvas *c[5];
for(int i=0;i<5;i++){c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),2400,1600);}
//ReadCSV(string ifname,  vector<double> &xaxis,vector<double> &yaxis,  vector<double> &er_x,vector<double> &er_y, int &count, double xaxismin,double xaxismax, double xaxisoffset)
ReadCSV(ifname1,  xaxis1, eff1, ex1,e_eff1, count1, xaxismin, xaxismax, xaxisoffset);
ReadCSV(ifname2,  xaxis2, eff2, ex2,e_eff2, count2, xaxismin, xaxismax, xaxisoffset);
ReadCSV(ifname3,  xaxis3, eff3, ex3,e_eff3, count3, xaxismin, xaxismax, xaxisoffset);
ReadCSV(ifname4,  xaxis4, eff4, ex3,e_eff4, count4, xaxismin, xaxismax, xaxisoffset);
ReadCSV(ifname5,  xaxis5, eff5, ex3,e_eff5, count5, xaxismin, xaxismax, xaxisoffset);
ReadCSV(ifname6,  xaxis6, eff6, ex3,e_eff6, count6, xaxismin, xaxismax, xaxisoffset);
tg1 = new TGraphErrors(count1, &xaxis1[0], &eff1[0] , &ex1[0], &e_eff1[0] ); 
tg2 = new TGraphErrors(count2, &xaxis2[0], &eff2[0] , &ex2[0], &e_eff2[0] ); 
tg3 = new TGraphErrors(count3, &xaxis3[0], &eff3[0] , &ex3[0], &e_eff3[0] ); 
tg4 = new TGraphErrors(count4, &xaxis4[0], &eff4[0] , &ex4[0], &e_eff4[0] ); 
tg5 = new TGraphErrors(count5, &xaxis5[0], &eff5[0] , &ex5[0], &e_eff5[0] ); 
tg6 = new TGraphErrors(count6, &xaxis6[0], &eff6[0] , &ex6[0], &e_eff6[0] ); 
//SetGrErr(TGraphErrors *gr, TString hname, TString xname, TString yname, int LColor, int MColor, int MStyle, double Yoffset, double min, double max);
SetGrErr(tg1, "", "", "", 1, 2, 24, 0, 0, 0);
SetGrErr(tg2, "", "", "", 1, 4, 25, 0, 0, 0);
SetGrErr(tg3, "", "", "", 1, 6, 26, 0, 0, 0);
SetGrErr(tg4, "", "", "", 1, 2, 20, 0, 0, 0);
SetGrErr(tg5, "", "", "", 1, 4, 21, 0, 0, 0);
SetGrErr(tg6, "", "", "", 1, 6, 22, 0, 0, 0);
leg_eff -> AddEntry(tg1,"t=1.5mm","p");
leg_eff -> AddEntry(tg2,"t=3.0mm","p");
leg_eff -> AddEntry(tg3,"t=5.0mm","p");
TF1 *f100 = new TF1("f100","[0]",0,10);
f100 -> SetParameter(0,100.);
f100 -> SetLineColor(1);
f100 -> SetLineWidth(1);
f100 -> SetLineStyle(2);
TF1 *f1 = new TF1("f100","[0]+[1]*(x-[2])",1,10);
f1 -> SetParameter(0,100.0);
f1 -> SetParameter(1,-2.7);
f1 -> SetParameter(2, 1.);
f1 -> SetLineColor(1);
f1 -> SetLineWidth(1);
f1 -> SetLineStyle(5);

c[0]->Clear();
c[0]->SetTicks(0,1);
h_frame->Draw();
f100 ->Draw("same");
f1   ->Draw("same");
tg1  ->Draw("sameP");
tg2  ->Draw("sameP");
tg3  ->Draw("sameP");
tg4  ->Draw("sameP");
tg5  ->Draw("sameP");
tg6  ->Draw("sameP");
leg_eff ->Draw("same");

c[1]->Clear();
c[1]->SetTicks(0,1);
h_frame->Draw();
f100 ->Draw("same");
f1   ->Draw("same");
tg1 ->Draw("sameP");
tg4 ->Draw("sameP");

c[0]->Print("./pdf/eff_segdep.pdf["  );
c[0]->Print("./pdf/eff_segdep.pdf"   );
c[1]->Print("./pdf/eff_segdep.pdf"   );
c[1]->Print("./pdf/eff_segdep.pdf]"  );

    gSystem->Exit(0);
  theApp.Run();
  return 0;

}
