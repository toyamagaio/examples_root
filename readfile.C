void readfile(char *optarg = "v1190-11.dat"){
//example for filling value from text file
//expected file

/*
0 1
0 4
1 3
*/


std::ifstream ifs;
ifs.open(optarg);
//std::ifstream ifs(optarg);
 Int_t tdc1[10000];
 Int_t tdc2[10000];
 Int_t tdc3[10000];
 Int_t tdc4[10000];
 Int_t tdc5[10000];
 Int_t run[10000];
 Int_t a,b,k,p,q;
 Int_t i=0;
 
 while(!ifs.eof()){
 ifs >> a >> b ;
// ifs >> ch >> tdc ;
run[i]=i;
if(a==1)tdc1[i]=b;
else if(a==2)tdc2[i]=b;
else if(a==3)tdc3[i]=b;
else if(a==4)tdc4[i]=b;
else if(a==5){tdc5[i]=b;i++;}
 
if(i>9999)break;
 }
 TGraph *Tdc[5];
 Tdc[0] = new TGraph(i,run,tdc1);
 Tdc[1] = new TGraph(i,run,tdc2);
 Tdc[2] = new TGraph(i,run,tdc3);
 Tdc[3] = new TGraph(i,run,tdc4);
 Tdc[4] = new TGraph(i,run,tdc5);
// TGraphErrors *TWC = new TGraphErrors(i,TDC,QDC,eTDC,eQDC);
 cout<<"i="<<i<<endl;
 TCanvas *c = new TCanvas("c","canvas",800,600);
 TH1 *frame = c ->DrawFrame(0,-20,100,0);
// TH1 *frame = c ->DrawFrame(0,-20,i,0);
// TH1 *frame = c ->DrawFrame(100,3180,1200,3210);
// TH1 *frame = c ->DrawFrame(300,3300,1200,3340);
// TH1 *frame = c ->DrawFrame(3300,300,3340,1200);
 frame->GetXaxis()->SetTitle("event");
 frame->GetYaxis()->SetTitle("TDC[ch]");
for(int j=0;j<5;j++){ 
 Tdc[j] -> SetMarkerStyle(1);
 Tdc[j] -> SetMarkerColor(j+1);
 if(j<4)Tdc[j] -> SetLineColor(j+1);
 else Tdc[j] -> SetLineColor(j+2);
if(j==0) Tdc[j] -> Draw("L");
else Tdc[j] -> Draw("Lsame");
  }
}
