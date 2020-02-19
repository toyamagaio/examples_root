double GetGamma(double Ee,double Eep, double theta_e){
  //Assuming electron mass is 0 because our energy/mom region is GeV order


  
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
  
  //input paramerters//
  //Ee  = 4.5;//[GeV] beam energy
  //Eep = 3.0;//[GeV] scattered electron energy
  //theta_e = 6.5;//[deg] scattered angle

  //E05-115
  //Ee       = 2.344  ;//[GeV] beam energy
  //Eep      = 0.844  ;//[GeV] scattered electron energy
  //mom bite = 0.17 
  //solid a  = 0.007
  //theta_e  = 7.0    ;//[deg] scattered angle

  //E12-15-008 proposal (48Ca proposal)
  //Ee       = 4.5238 ; //[GeV] beam energy
  //Eep      = 3.0296 ; //[GeV] scattered electron energy
  //mom bite = 0.045   //assumption
  //solid a  = 0.005   //assumption
  //theta_e  = 7.0    ;//[deg] scattered angle

  //E12-15-008 Aida Mthesis(48Ca)
  //Ee       = 4.52  ;//[GeV] beam energy
  //Eep      = 3.0296;//[GeV] scattered electron energy
  //mom bite = 0.053 //from thesis
  //solid a  = 0.005  //from thesis (acutually 4-7 msr depending mom and angle
  //theta_e  = 7.0   ;//[deg] scattered angle
  
  //Fujita Mthesis(48Ca)
  //Ee       = 4.52  ;//[GeV] beam energy
  //Eep      = 3.0296;//[GeV] scattered electron energy
  //mom bite = 0.05   //from thesis
  //solid a  = 0.006  //from thesis (acutually 4-7 msr depending mom and angle
  //theta_e  = 7.0   ;//[deg] scattered angle

  //JK Mthesis
  //Ee  = 4.5238;//[GeV] beam energy
  //Eep = 3.0951;//[GeV] scattered electron energy
  //theta_e = 7.0;//[deg] scattered angle

  //Nagao DE+DK
  //Ee       = 4.5    ; //[GeV] beam energy
  //Eep      = 3.0    ; //[GeV] scattered electron energy
  //mom bite = 0.045   //assumption
  //solid a  = 0.0034   //assumption
  //theta_e  = 6.5    ;//[deg] scattered angle
  
  double beam       =2.344;//4.5  ;
  double Eep_center =0.844;//3.0  ;
  double Eep_range  =0.17 ;//0.045;//relative momentum bite
  double dOmega     =0.008;//0.006;//[sr] solid angle
  double theta      =4.0  ;//deg

  double Eep_min = Eep_center - Eep_center*Eep_range;
  double Eep_max = Eep_center + Eep_center*Eep_range;
  double dEp = 0.0001;//[GeV]
  double intGamma = 0.;

  double Eep = Eep_min + 0.5*dEp;
  
  while(Eep<Eep_max){

   intGamma += 0.5*(GetGamma(beam,Eep-0.5*dEp,theta)+GetGamma(beam,Eep+0.5*dEp,theta))*dEp*dOmega;
   Eep+=dEp;
   cout<<" Eep : "<<Eep<<endl;
  }


  cout<<"center of Gamma = " <<GetGamma(beam,Eep_center,theta)<<" /GeV/sr"<<endl;
  cout<<"integrated Gamma = "<<intGamma<<" /electron"<<endl;

}
