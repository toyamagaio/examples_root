#include "Setting.cc"
double rho0_mass(double *x, double *par){
  //par[0]=amp;
  //par[1]=mean;
  //par[2]=width (FWHM);
  double mpi=0.13957;
  double val;
  double q, q0, Gamma;
  
  double m0    =par[1];
  double Gamma0=par[2];
  double m = x[0];
  q = sqrt(m*m*0.25 - mpi*mpi);
  q0 = sqrt(m0*m0*0.25 - mpi*mpi);
  Gamma = Gamma0*pow(q/q0,3.)*2.*q0*q0/(q0*q0+q*q);
  
  val = par[0] * m/q *Gamma/( (m*m-m0*m0)*(m*m-m0*m0) + m0*m0*Gamma*Gamma );

  if(m*m*0.25 - mpi*mpi<0)return 0.;
  return val;
}

void rho0_mass_dist(){

  Setting *set = new Setting();
  TF1 *f_rho0= new TF1("f_rho0",rho0_mass,0,2,3);


  set->SetTF1(f_rho0, 2, 1,1.8);
  f_rho0->SetParameter(0,1);
  f_rho0->SetParameter(1,0.770);
  f_rho0->SetParameter(2,0.140);


  f_rho0->Draw();
}
