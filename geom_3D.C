void geom_3D(){

  TCanvas *c1 = new TCanvas("c1","c1",800,800);

  gSystem->Load("libGeom");
  //delete previous geometry objects in case this script is reexecuted
  if (gGeoManager) {
    gGeoManager->GetListOfNodes()->Delete();
    gGeoManager->GetListOfShapes()->Delete();
  }
 
 //  Define some volumes
 TTUBE *tube  = new TTUBE("TUBE","TUBE","void",100,100,400);
 tube->SetNumberOfDivisions(12);
 tube -> SetLineColor(6);

 tube->Draw("gl");

}
