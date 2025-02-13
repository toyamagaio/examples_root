void proton_mom_Ekin(){

  const double Mp = 938.272046;          // proton       mass (MeV/c2)

  TF1 *fp= new TF1("fp","sqrt(x*x+[0]*[0])-[0]",0,80);
  fp->SetParameter(0,Mp);

  fp->SetLineColor(2);

  fp->Draw();

}
