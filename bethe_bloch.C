void bethe_bloch(){

  //////////////////////
  //BetheBloch formula//
  //////////////////////
  TGraph* tg1;
  TGraph *tg_pi, *tg_k, *tg_p, *tg_d;
  double beta_max = 0.995;
  double beta_min = 0.04;
  double  I, rho, z, AZ, D, B;
  	
  //	dx = 0.01;
  //	cout<<"beta_min"<<beta_min<<endl;
  //	cout<<"beta_max"<<beta_max<<endl;
  
  //	I = 237; //Hexane
  //	I = 78.0; //C (from Leo)
  	I = 64.7; //plastic scint (from Leo)
  
  //density
  //	rho = 2.0;   //C
  	rho = 1.032; //scint
  //	rho = 4.63e-6;
  
  //	cout<<"input particle z"<<endl;
  //	cin>>z;
  z=1;
  
  	/*A/Z*/
  	AZ = 2.0;
  
  	D = 0.3071;
  	B = D*rho*z*z/AZ;
  //	cout<<"B="<< B<<endl;
  const int step =4000;
  	double  x, dx;
  	dx = (beta_max - beta_min) / step;
  
  double mom_pi[step], mom_k[step], mom_p[step], mom_d[step];
  double dedx[step], bbeta[step];
  double gamma;
  int i = 0;
  	for (x = beta_min; x < beta_max; x += dx) {
  		double f     = log(2.0*0.511e+6*x*x/(I*(1-x*x)))/(x*x)-1.0;
          bbeta[i]=x;
          dedx[i]=B*f;

          gamma = 1./sqrt(1-x*x);
          mom_pi[i] = 0.001*Mpi*x*gamma;
          mom_k[i] = 0.001*MK*x*gamma;
          mom_p[i] = 0.001*Mp*x*gamma;
          i++;
              }
   tg1 = new TGraph(i, bbeta, dedx);   
      tg1 -> SetLineColor(1); 
      tg1 -> SetLineStyle(1); 
      tg1 -> SetLineWidth(0.81); 
  
   tg_pi = new TGraph(i, mom_pi, dedx);   
   tg_k  = new TGraph(i, mom_k,  dedx);   
   tg_p  = new TGraph(i, mom_p,  dedx);   
   SetGr(tg_pi,"Bethe-bloch","mom","dE/dx",4,1,1);
   SetGr(tg_k ,"Bethe-bloch","mom","dE/dx",3,1,1);
   SetGr(tg_p ,"Bethe-bloch","mom","dE/dx",2,1,1);

  TCanvas *c[2];
  for(int i=0;i<2;i++){
    c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),800,600);
  }
  c[0]->Clear();
  c[0]->cd(1);
  tg1->Draw("AL");

  c[1]->Clear();
  c[1]->cd(1);
  tg_p ->Draw("AL");
  tg_pi->Draw("Lsame");
  tg_k ->Draw("Lsame");

}
