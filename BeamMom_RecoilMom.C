Double_t recoil_mom(Double_t *x, Double_t *par){

    Double_t mom_g = x[0];
    
	Double_t m_k = 0.493677, m_l = 1.115683, m_p = 0.9382; //mass of particles
	Double_t s0 = -0.521793862;
	Double_t t0 = s0/2.0;
	Double_t a0,b0,c0;

	a0 = -2.0*mom_g*m_p - s0 -m_l*m_l - m_k*m_k;
	b0 = 2.0*mom_g*mom_g*m_p + mom_g*s0 + 2.0*mom_g*m_l*m_l;
	c0 = mom_g*mom_g*m_p*m_p - mom_g*mom_g*m_l*m_l - m_k*m_k*m_l*m_l +t0*t0+mom_g*m_p*s0;
//	c0 = mom_g*mom_g*m_p*m_p - mom_g*mom_g*m_l*m_l - m_k*m_k*m_l*m_l +t0*t0;

	Double_t f = (-b0 + TMath::Sqrt(b0*b0 -4.0*a0*c0))/(2.0*a0);
	if ( b0*b0 -4.0*a0*c0 < 0 ){
		f = 0.0;
	}

	return f;
}



void BeamMom_RecoilMom(){
//	Double_t mk = 0.493677, ml = 1.115683, mp = 0.9382; //mass of particles
//	Double_t momg; //momentum of gamma
//	Double_t s = -0.521793862;
//	Double_t t = s/2.0;
//	Double_t a,b,c;

	TCanvas *c1 = new TCanvas("c1","canvas",800,600);

	//a = -2.0*momg*mp - s -ml*ml - mk*mk;
	//b = 2.0*momg*momg*mp + momg*s + 2.0*momg*ml*ml;
	//c = momg*mp - momg*momg*ml*ml - mk*mk*ml*ml + t*t;

	TF1 *RecoilMom = new TF1("RecoilMom", recoil_mom, 0.8, 5.0, 0);
	RecoilMom->Draw();

//	Double_t kai[2];

//	momg = 0.0;
//	Int_t i;

//	for(i=0,i<50,i++){

//	kai[0] = (-b + TMath::Sqrt2(b*b -4*a*c))/(2*a);
//	}
}
