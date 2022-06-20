#python3
import ROOT

def myfunc(x, p):
  return p[0]*x[0]+p[1]

f1= ROOT.TF1("f1","x",0,1)
f1.Draw()
f2= ROOT.TF1("f2",myfunc,0,1,2)
f2.SetParameter(0,1);
f2.SetParameter(1,0.5);
f2.SetLineColor(2);
f2.Draw("same")
