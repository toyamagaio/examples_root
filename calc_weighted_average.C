void WeightAv(double *data, double *error, int npoint, double &mean, double &emean){
  // data: value of each data point
  // error: statistical error of each data point
  // npoint: the num. of data points
  // mean: weighted average
  // emean: conbined error of weighted average
  mean = emean =0.;
  double w_sum  =0.;
  double wp_sum =0.;

  for(int i=0;i<npoint;i++){
    double w  = 1./(error[i]*error[i]);
    double wp = w*data[i];
    w_sum  += w;
    wp_sum += wp;
  }

  mean  = wp_sum/w_sum;
  emean = 1./sqrt(w_sum);

}
/////////
void calc_weighted_average(){

  int np=4;
  double  data[4]={1.4, 1.2, 1.0, 1.3};
  double edata[4]={0.5, 0.2, 0.25, 0.2};

  double  wa, ewa;
  WeightAv(data, edata, np, wa, ewa);
  cout<<wa<<" +/- "<<ewa<<endl;
}
