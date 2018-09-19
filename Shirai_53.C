void Shirai_53(){
  TCanvas *c1 = new TCanvas("c1","c1",600,800);

  const int n = 8;
  double t[n] = {  0, 60,120,180,240,300,360,420};
  double N[n] = {107, 84, 65, 50, 36, 48, 33, 25};
  double eN[n], et[n];
  for(int i=0;i<n;i++){
    eN[i] = sqrt(N[i]);
    et[i] = 0.;
  }

  TGraphErrors* tg1 = new TGraphErrors(n,t,N,et,eN);
  TF1 *f = new TF1("f","[0]*exp(-x/[1])",-1,450);
  f->SetParameter(0,100);
  f->SetParameter(1,100);

  tg1->Fit(f);
  
  gPad->SetLogy(1);
  tg1->Draw("APE");
  f->Draw("same");

  double tau = f->GetParameter(1);
  double half_life = tau * log(2);

  cout<<"tau="<<tau<<", t1/2="<<half_life<<endl;
}
