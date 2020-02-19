void vec(){
 TVector3 vec;
 //vec.SetMagThetaPhi(1,0,0);
 vec.SetMagThetaPhi(1,0.5*PI,0.5*PI);
 vec.RotateZ(0.25*PI);

 cout<<vec.x()<<" "<<vec.y()<<" "<<vec.z()<<endl;


}
