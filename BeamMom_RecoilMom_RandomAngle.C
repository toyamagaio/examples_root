Double_t myfunc(Double_t *x, Double_t *par){

	Double_t momg = x[0]; //beam momentum
	Double_t mk = 0.493677, ml = 1.115683, mp = 0.9382; // mass of particles
//	Double_t mk = 0.493677, ml = 11.356, mp = 11.174; // mass of particles
	Double_t beta = momg/(momg + mp);
	Double_t gamma = 1/TMath::Sqrt(1 - beta*beta);
	Double_t ecm = TMath::Sqrt(2*momg*mp + mp*mp); //total energy (CM) 
	Double_t elcm = (ecm + (ml*ml -mk*mk)/ecm)/2; //energy of lambda (CM)
	Double_t momlcm = TMath::Sqrt((ecm + ml + mk)*(ecm + ml - mk)*(ecm - ml - mk)*(ecm - ml + mk))/(2*ecm); //momentum of lambda (CM)

//	Double_t rad = TMath::Pi()*par[0]/180; //theta in Lab

	Double_t rad = par[0]; //theta in Lab
	cout<<momg ;

	Double_t a,b,c;

	c = beta*gamma*elcm;
	a = c*c + gamma*gamma*momlcm*momlcm;
	b = cos(rad)*cos(rad) + gamma*gamma*sin(rad)*sin(rad);

	Double_t l,m,n;
	m = -2*a*b + 4*c*c*gamma*gamma*sin(rad)*sin(rad);
	l = b*b;
	n = a*a - 4*c*c*gamma*gamma*momlcm*momlcm;

	Double_t momlsq = (-m - TMath::Sqrt(m*m - 4*l*n))/(2*l); //square of momentum of lambda(Lab)

	Double_t f = TMath::Sqrt(momlsq);

//deal with "NAN"
    if( (ecm + ml + mk)*(ecm + ml - mk)*(ecm - ml - mk)*(ecm - ml + mk) < 0 )f=0;
	if(m*m - 4*l*n < 0)f=0;
	if(momlsq<0)f=0;

	cout<<f<<endl;
	return f;
}

Double_t pion_kaon(Double_t *x, Double_t *par){

	Double_t mompi = x[0]; //beam momentum
	Double_t mn = 939.5654133, mpi  = 139.57, mk = 0.493677, ml = 1.115683; // mass of particles
//	Double_t mk = 0.493677, ml = 11.356, mp = 11.174; // mass of particles
	Double_t beta = mompi/(TMath::Sqrt(mpi*mpi + mompi*mompi) + mn);
	Double_t gamma = 1/TMath::Sqrt(1 - beta*beta);
	Double_t ecm = TMath::Sqrt(mompi*mompi + mn*mn + 2*mn*TMath::Sqrt(mpi*mpi + mompi*mompi)); //total energy (CM) 
	Double_t elcm = (ecm + (ml*ml -mk*mk)/ecm)/2; //energy of lambda (CM)
//	Double_t momlcm = TMath::Sqrt((ecm + ml + mk)*(ecm + ml - mk)*(ecm - ml - mk)*(ecm - ml + mk))/(2*ecm); //momentum of lambda (CM)
	Double_t momlcm = TMath::Sqrt(elcm*elcm - ml*ml);

	Double_t rad = TMath::Pi()*par[0]/180; //theta in Lab

	cout<<mompi ;

	Double_t a,b,c;

	c = beta*gamma*elcm;
	a = c*c + gamma*gamma*momlcm*momlcm;
	b = cos(rad)*cos(rad) + gamma*gamma*sin(rad)*sin(rad);

	Double_t l,m,n;
	m = -2*a*b + 4*c*c*gamma*gamma*sin(rad)*sin(rad);
	l = b*b;
	n = a*a - 4*c*c*gamma*gamma*momlcm*momlcm;

	Double_t momlsq = (-m - TMath::Sqrt(m*m - 4*l*n))/(2*l); //square of momentum of lambda(Lab)

	Double_t f = TMath::Sqrt(momlsq);

//deal with "NAN"
    if( (ecm + ml + mk)*(ecm + ml - mk)*(ecm - ml - mk)*(ecm - ml + mk) < 0 )f=0;
	if(m*m - 4*l*n < 0)f=0;
	if(momlsq<0)f=0;

	cout<<f<<endl;
	return f;
}
void BeamMom_RecoilMom_RandomAngle(){

	TCanvas *c1 = new TCanvas("c1","canvas",800,600);
//	c1->Divide(2,2);
//	for(int i=0;i<4;i++){
//    gROOT->SetBatch(1);
//	TF1 *f0 = new TF1("f0",myfunc, 0.4, 5.0, 1);
//	RecoilMom->SetParameter(0,10*i);
//	c1->cd(i+1);
//	f0->Draw();
//	}

	TF1 *f0 = new TF1("f0",myfunc, 0.3, 5.0, 1);
	f0->SetParameter(0,0);
	f0->SetLineColor(1);

	TF1 *f10 = new TF1("f10",myfunc, 0.3, 5.0, 1);
	f10->SetParameter(0,10);
	f10->SetLineColor(2);

	TF1 *f20 = new TF1("f20",myfunc, 0.3, 5.0, 1);
	f20->SetParameter(0,20);
	f20->SetLineColor(3);

	TF1 *f30 = new TF1("f30",myfunc, 0.3, 5.0, 1);
	f30->SetParameter(0,30);
	f30->SetLineColor(4);

	TF1 *g = new TF1("g",pion_kaon, 0.3, 5.0, 1);
	f30->SetParameter(0,10);
	f30->SetLineColor(5);

	TH2D *h = new TH2D("h","h",0,0.3,2,0,0,3);
    SetTH2(h,"Momentum tansfer","beam momentum (GeV/c)","recoil momentum (GeV/c)",0.4);
	h->SetStats(kFALSE);

//	c1->cd();
	h->Draw();
	f0->Draw("same");
	f10->Draw("same");
	f20->Draw("same");
	f30->Draw("same");
	g->Draw("same");
}

