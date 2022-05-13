#include "Setting.cc"
const int NBin = 100;
double  bincont_data[NBin];
double  bincont_tmp[NBin][2];
double  bincont_tmp_sum[NBin];
double ebincont_data[NBin];
double ebincont_tmp[NBin][2];
double ebincont_tmp_sum[NBin];
///
//double minuitFunc(){
void minuitFunction(int& nDim, double* gout, double& result, double par[], int flg){
  double chi2=0;
  double chi2_tmp , err;

  for(int bin=0;bin<NBin;bin++){
    bincont_tmp_sum[bin] = par[0]*bincont_tmp[bin][0] + (1.-par[0])*bincont_tmp[bin][1];
    ebincont_tmp_sum[bin] = par[0]*ebincont_tmp[bin][0] + (1.-par[0])*ebincont_tmp[bin][1];

    chi2_tmp = (bincont_data[bin]-bincont_tmp_sum[bin])*(bincont_data[bin]-bincont_tmp_sum[bin]);
    err      = ebincont_data[bin]*ebincont_data[bin] + ebincont_tmp_sum[bin]*ebincont_tmp_sum[bin] ;
    if(err>0)chi2_tmp /= err;
    chi2 += chi2_tmp;
  }

  result = chi2;
}
//  
//
//}
////////======
//
//  example of simultaneous fit of 
//
//
void simultaneous_minuit_fit(){

  Setting *set = new Setting();
  TH1D *h_data = new TH1D("h_data","h_data",NBin,-10,10);

  TH1D *h_tmp[2];
  for(int i=0;i<2;i++){
    h_tmp[i] = new TH1D(Form("h_tmp%d",i+1),Form("h_tmp%d",i+1),NBin,-10,10);
    set->SetTH1(h_tmp[i],"","","",4,3000,0);   
  }

  //data
  int ENum=100000;
  for(int n=0;n<ENum;n++){
    if(n%1000==0)cout<<n<<"/"<<ENum<<endl;
    double val =gRandom->Gaus(1,2);
    h_data->Fill(val);

    val =gRandom->Gaus(-1,1);
    h_data->Fill(val);
    val =gRandom->Gaus(-1,1);
    h_data->Fill(val);
  }

  //fitting template
  for(int n=0;n<10000;n++){
    double val =gRandom->Gaus(1,2);
    h_tmp[0]->Fill(val);
    val =gRandom->Gaus(-1,1);
    h_tmp[1]->Fill(val);
  }
  h_tmp[0]->Scale(3.*ENum/10000);
  h_tmp[1]->Scale(3.*ENum/10000);
  cout<<"integral h_tmp[0]="<<h_tmp[0]->Integral()<<endl;
    
  for(int bin=0;bin<NBin;bin++){
     bincont_data[bin] = h_data->GetBinContent(bin+1);
    ebincont_data[bin] = h_data->GetBinError(bin+1);
    if(bincont_data[bin]<1)cout<<bin<<" "<<bincont_data[bin]<<" "<<ebincont_data[bin]<<endl;
    for(int i=0;i<2;i++){
       bincont_tmp[bin][i] = h_tmp[i]->GetBinContent(bin+1);
      ebincont_tmp[bin][i] = h_tmp[i]->GetBinError(bin+1);
    }
  }

  TMinuit *minuit = new TMinuit();
  minuit -> SetFCN(minuitFunction);
  //           Define the parameters
  //                         arg1 - parameter number
  //                         |   arg2 - parameter name
  //                         |   |          arg3 - first guess at parameter value
  //                         |   |          |             arg4 - step size
  //                         |   |          |             |      arg5 - lower limt
  //                         |   |          |             |      |         arg6 - higher limit
  //                         |   |          |             |      |         |
  minuit -> DefineParameter( 0, "r"   ,    0.5          , 0.01,  0.      , 1.       );
  minuit -> Migrad();

  double r, er;
  minuit    ->GetParameter(0, r, er);
  cout<<"fit param: "<< r<<" +/- "<<er<<endl;
  h_tmp[0] ->Scale(r);
  h_tmp[1] ->Scale(1.-r);

  TH1D *h_tmp_sum = (TH1D*)h_tmp[0]->Clone("h_tmp_sum");
  h_tmp_sum->Add(h_tmp[1]);
  set->SetTH1(h_tmp_sum,"","","",6,3000,0);
  h_tmp_sum->SetLineWidth(2);

  h_data->Draw();
  h_tmp_sum->Draw("same");
  //h_tmp[0]->Draw("same");
  //h_tmp[1]->Draw("same");
}
