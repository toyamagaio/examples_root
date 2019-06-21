double GetGamma(double Ee,double Eep, double theta_e){
  //Assuming electron mass is 0 because our energy/mom region is GeV order
  //input paramerters//
  //double Ee  = 4.5;//[GeV] beam energy
  //double Eep = 3.0;//[GeV] scattered electron energy
  //double theta_e = 6.5;//[deg] scattered angle

  //E05-115
  //Ee  = 2.344;//[GeV] beam energy
  //Eep = 0.844;//[GeV] scattered electron energy
  //theta_e = 4.0;//[deg] scattered angle

  //E12-15-008 proposal (48Ca proposal)
  //Ee  = 4.5238;//[GeV] beam energy
  //Eep = 3.0296;//[GeV] scattered electron energy
  //theta_e = 7.0;//[deg] scattered angle

  //E12-15-008 Aida Mthesis(48Ca)
  //Ee  = 4.52;//[GeV] beam energy
  //Eep = 3.0296;//[GeV] scattered electron energy
  //theta_e = 7.0;//[deg] scattered angle

  //JK Mthesis
  //Ee  = 4.5238;//[GeV] beam energy
  //Eep = 3.0951;//[GeV] scattered electron energy
  //theta_e = 7.0;//[deg] scattered angle


  
  double mp = 0.938272046;//proton mass [GeV/c^2]
  //calc.
  double theta_e_rad = theta_e*deg_to_rad;//[rad] scattered angle
  double Qsq = 2.*Ee*Eep*(1.-TMath::Cos(theta_e*deg_to_rad));//[(GeV/c)^2]  mom transfer (ignoring electron mass)
  double qq = Ee*Ee+Eep*Eep-2.*Ee*Eep*TMath::Cos(theta_e_rad);//squared absolute value of virtual photon mom vector. |q^2| [(GeV/c)^2]

  double epsilon = 2.*pow(Ee*Eep*TMath::Sin(theta_e_rad),2)/(Qsq*qq + 2.*pow(Ee*Eep*TMath::Sin(theta_e_rad),2));
  double Eg = (Ee-Eep) - 0.5*Qsq/mp;//[GeV]  photon energy

  double Gamma = 0.5*alpha*Eg*Eep/(PI*PI*Qsq*(1.-epsilon)*Ee);

  //cout<<"Ee  = "<<Ee<<" GeV"<<endl;
  //cout<<"Eep = "<<Eep<<" GeV"<<endl;
  //cout<<"theta_e = "<<theta_e<<" deg"<<endl;
  //cout<<"Q^2 = "<<Qsq<<" (GeV/c)^2"<<endl;
  //cout<<"Eg = "<<Eg<<" GeV"<<endl;
  //cout<<"|q_vec^2| = "<<qq<<" (GeV/c)^2"<<endl;
  //cout<<"epsilon = "<<epsilon<<endl;
  //cout<<"Gamma = "<<Gamma<<" /GeV/sr"<<endl;
  return Gamma;
}
//////////////////////
void VPflux(){
  
  double Eep_min = 3.5 - 3.5*0.045;
  double Eep_max = 3.5 + 3.5*0.045;
  double dEp = 0.001;//[GeV]
  double dOmega = 0.005;//[sr] solid angle
  double intGamma = 0.;
  double theta = 6.5;//deg
  double beam = 4.5;

  double Eep = Eep_min + 0.5*dEp;
  
  while(Eep<Eep_max){

   intGamma += 0.5*(GetGamma(beam,Eep-0.5*dEp,theta)+GetGamma(beam,Eep+0.5*dEp,theta))*dEp*dOmega;
   Eep+=dEp;
   cout<<" Eep : "<<Eep<<endl;
  }


  cout<<"integrated Gamma = "<<intGamma<<" /electron"<<endl;

}
