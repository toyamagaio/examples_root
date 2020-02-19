void tspline(){

  TCanvas *c1=new TCanvas("c1","c1",800,800);
  c1->Divide(1,2);
  
  /////////
  //Array//
  /////////
  double x[]={0,1,2,3,4,5,6,7,8,9,10};
  double y[]={0,1,1,2,4,5,4,2,1,1, 0};

  TSpline3 *ts3 = new TSpline3("ts3",x,y,11);
  TGraph *tg = new TGraph(11,x,y);
  SetGr(tg,"","x","y",2,1,1,2,20,1.0);
  

  c1->cd(1);
  tg->Draw("APL");
  ts3->Draw("samel");

  //////////
  //vector//
  //////////
  vector<double> x_vec,y_vec;

  for(int i=0;i<11;i++){
    x_vec.push_back(i);
    y_vec.push_back((i-5)*(i-5));
  }

  TSpline3 *ts3_vec = new TSpline3("ts3_vec",&x_vec[0],&y_vec[0],x_vec.size() );
  TGraph *tg_vec = new TGraph(x_vec.size(),&x_vec[0],&y_vec[0]);
  SetGr(tg_vec,"","x","y",2,1,1,2,20,1.0);
  
  c1->cd(2);
  tg_vec->Draw("AP");
  ts3_vec->Draw("samel");
}
