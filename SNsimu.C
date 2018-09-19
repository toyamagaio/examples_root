void SNsimu(){
gROOT->Reset();
TH1F *hist[6];
//char histname[10],histtitle[12];
for(int k;k<6;k++){
//sprintf(histname,"hist%d",k+1);
//sprintf(histtitle,"SNsimulaton");
hist[k] = new TH1F(Form("hist%d",k+1),"",30,-2,2);
SetTH1(hist[k],"SNsimulation", "energy [MeV]", "count");
 }
hist[2]->SetFillColor(2);
hist[2]->SetFillStyle(1001);
hist[1]->SetFillColor(3);
hist[1]->SetFillStyle(1001);

int counter = 0;
double S[50],N[200];
double sigma =0.5;
gRandom -> SetSeed( time(NULL) ); //seed set by time
/*
for(int i=0;i<10000;i++){
//cout<<2*(gRandom->Uniform(1)-0.5)<<endl;
double aa = 2*(gRandom->Uniform(1)-0.5);
hist[0]->Fill(aa);
}
hist[0]->Draw("");
*/
#if 1
for(int i;i<50;i++){
S[i] = gRandom -> Gaus(0.,sigma);
cout<<S[i]<<endl;
if(fabs(S[i])<log(2)*sigma)counter++;
if(counter>20)break;
hist[0]->Fill(S[i]);
}
cout<<"counter = "<<counter<<endl;
int counter1 = 0;
for(int j;j<200;j++){
N[j] = gRandom -> Uniform(-5*sigma, 5*sigma);
hist[1]->Fill(N[j]);
if(fabs(N[j])<log(2)*sigma)counter1++;
if(counter1>29)break;
}
cout << "counter1 = " <<counter1<<endl;
hist[2]->Add(hist[0],1);
hist[2]->Add(hist[1],1);


TCanvas *c1 =new TCanvas("c1","canvas",800,600);

hist[2]->Draw();
hist[1]->Draw("same");
#endif
}
