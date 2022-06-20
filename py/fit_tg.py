#python3
import ROOT
import numpy as np
import math

def myfunc(x, p):
  energy=-999.
  EPS=0.001
  b1= x[0]-p[1]
  c1= p[0]*p[3]  + b1
  d1=b1*p[3]-p[2]
  term = c1*c1 - 4 * p[0]* d1
  if ((p[0]<EPS) or (term<0)):
      energy=-999.9
  else:
      energy = (c1+math.sqrt(term))/(2*p[0])
  return energy

def Calib_Function(tot, a,b,c,t): #v2
    EPS=0.001
    b1= tot-b
    c1= a*t  + b1
    d1=b1*t-c
    term = c1*c1 - 4 * a* d1
    if ((a<EPS) or (term<0)):
        status=False
        energy=-999.9
    else:
        status=True
        energy = (c1+math.sqrt(term))/(2*a)
    return energy,status

f1= ROOT.TF1("f1","x",0,50)
f2= ROOT.TF1("f2",myfunc,0,50,4)
f2.SetParameter(0,2.)
f2.SetParameter(1,20.)
f2.SetParameter(2,60.)
f2.SetParameter(3,1.)
f2.SetLineColor(2)


ene=[3.0, 3.5, 4.4, 6.0, 6.5, 7.0, 10.]
tot=[ 0., 7.5, 15., 24., 26., 30., 40.]
e_ene=[0.2, 0.2,0.2, 0.2, 0.2, 0.2, 0.2]
e_tot=[ 0., 0., 0., 0., 0., 0., 0.]
print(type(ene))
ndata=len(tot)
tg=ROOT.TGraphErrors(ndata, np.asarray(tot), np.asarray(ene), np.asarray(e_tot), np.asarray(e_ene))
tg.SetLineColor(6)
tg.SetMarkerColor(6)
tg.SetMarkerSize(1.1)
tg.SetMarkerStyle(25)
tg.Fit(f2,'QRMN')

cv=ROOT.TCanvas("cv","cv",800,800)


tg.Draw("AP")
#f1.Draw("same")
f2.Draw("same")
par=np.empty(4,dtype=np.float64)
f2.GetParameters(par)
print(par)
cv.Print("test_fit.png")
