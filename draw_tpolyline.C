//draw dodecagon TDL event display like something
const double PI = 4.*atan(1.);
const double deg2rad = PI / 180.;
const double rad2deg = 180. / PI;

void draw_tpolyline(){

  TPolyLine tp_tdl;
  tp_tdl.SetFillColor(2);
  tp_tdl.SetFillStyle(1001);
  tp_tdl.SetLineColor(1);


  TGaxis tga1;
  double z[5], y[5];

  double tdl_y1[24],tdl_y2[24],tdl_y3[24], tdl_y4[24];
  double tdl_z1[24],tdl_z2[24],tdl_z3[24], tdl_z4[24];


  double r_in  = 52.; 
  double r_out = r_in + 5.;
  double theta_off  = 0.;
  double theta_step = 360./12.;


  TCanvas*c1 = new TCanvas("c1","c1",900,900);
  c1->Range(-100,-100,100,100);
  tga1.SetTitle("z[mm]");
  tga1.DrawAxis(-100.,-100.,-100., 100.,-130.,150., 514,"S");
  tga1.SetTitle("y[mm]");
  tga1.DrawAxis(-100.,-100., 100.,-100.,-130.,150., 514,"S");


  double theta =theta_off;
  for(int i=0;i<12;i++){
    tdl_y1[i]= r_in*sin(theta*deg2rad); tdl_y2[i]=r_in*sin((theta+theta_step)*deg2rad); tdl_y3[i]=r_out*sin((theta+theta_step)*deg2rad);tdl_y4[i]=r_out*sin(theta*deg2rad);
    tdl_z1[i]= r_in*cos(theta*deg2rad); tdl_z2[i]=r_in*cos((theta+theta_step)*deg2rad); tdl_z3[i]=r_out*cos((theta+theta_step)*deg2rad);tdl_z4[i]=r_out*cos(theta*deg2rad);
    z[0]=tdl_z1[i];y[0]=tdl_y1[i];
    z[1]=tdl_z2[i];y[1]=tdl_y2[i];
    z[2]=tdl_z3[i];y[2]=tdl_y3[i];
    z[3]=tdl_z4[i];y[3]=tdl_y4[i];
    z[4]=tdl_z1[i];y[4]=tdl_y1[i];
    theta+=theta_step;
    tp_tdl.DrawPolyLine(5,z,y,"f");
  } 






}
