void MultipleScatApprox(){

  double X0   = 8.90;//cm
  double x    = 0.175;//cm
  //x    = 4.42;//cm
  double beta =1.;
  double p    =2.e+3;//MeV
  double z    =1.;

  double theta = 13.6*z/(p*beta)*sqrt(x/X0)*( 1. + 0.038*TMath::Log(x/X0) );
  cout<<theta<<endl;
}
