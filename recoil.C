//constant
const double Mp = 0.938272046;          // proton       mass (GeV/c2)
const double ML = 1.115683;            // Lambda       mass (GeV/c2)
const double MK = 0.493677;             // charged Kaon mass (GeV/c2)
const double degtorad = PI/180. ;
/////////////////////
//momentun function//
/////////////////////
double momentum(double *x, double *par){

double momk, mom;
double Eg = x[0];
double theta_lab = par[0];

double beta = Eg/(Eg+Mp);
double gamma = 1./sqrt(1.-beta*beta);

double s = sqrt( pow(Mp,2.) + 2*Eg*Mp );
double pKcm =sqrt( pow(s*s - ML*ML - MK*MK,2.) -4.*ML*ML*MK*MK  )/(2.*s); 
double EKcm = (s*s - ML*ML + MK*MK)/(2.*s);

double C = cos(theta_lab * degtorad)*cos(theta_lab * degtorad) + gamma*gamma*sin(theta_lab * degtorad)*sin(theta_lab * degtorad); 
double a = pow(C ,2.);
double b = pow(2*beta*gamma*gamma*EKcm*sin(theta_lab * degtorad),2.) - 2*gamma*gamma*( pKcm*pKcm + beta*beta*EKcm*EKcm)*C;
double c = pow(gamma*gamma*(pKcm*pKcm+beta*beta*EKcm*EKcm)  ,2.) -pow(2.*beta*gamma*gamma*EKcm*pKcm ,2.);

momk = sqrt( (-b + sqrt(b*b-4*a*c))/(2*a) ) ;
mom = sqrt( Eg*Eg - 2*momk*Eg*cos(theta_lab * degtorad) + momk*momk );
if(mom > 0)double toyama =0 ;//cout<<"ok"<<flush; 
else mom = 9.;
//cout <<"Eg = "<<Eg <<" : mom = "<< mom<<endl;

return mom;
}


void recoil(){
//double p[100], theta, E;
//E=300.;
//theta = 10.;
//for(int i=0;i<100;i++){
//p[i]= momentum(E, theta);
//E = E + 10. ;
//cout << "Egamma" << " === " << "momentun" <<endl;
//cout << E << " === " << p[i] <<endl;
//   }
	TF1 *f0 = new TF1("f0",momentum, 0.3, 9.0, 1);
	f0->SetParameters(0,0);
	f0->SetLineColor(1);

	TF1 *f10 = new TF1("f10",momentum, 0.3, 8.0, 1);
	f10->SetParameters(10,0);
	f10->SetLineColor(2);

	TF1 *f20 = new TF1("f20",momentum, 0.3, 7.0, 1);
	f20->SetParameters(20,0);
	f20->SetLineColor(3);

	TF1 *f30 = new TF1("f30",momentum, 0.3, 6.0, 1);
	f30->SetParameters(30,0);
	f30->SetLineColor(4);

	TH2D *h = new TH2D("h","h",0,0.,2.,0,0,0.71);
    SetTH2(h,"Momentum tansfer","beam momentum (GeV/c)","recoil momentum (GeV/c)",0.4);
	h->SetStats(kFALSE);

TCanvas = new TCanvas("c","canvas",800,600);
//	c1->cd();
	h   -> Draw();
	f0  -> Draw("same");
	f10 -> Draw("same");
	f20 -> Draw("same");
	f30 -> Draw("same");

}
