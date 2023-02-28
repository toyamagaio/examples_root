import ROOT

#making TH1 (or TH2) class objects in a list
h =[   ROOT.TH1D('h_{}'.format(i) ,"",200,-5,5) for i in range(3) ]

for i in range(3):
 h[i].FillRandom("gaus",100*(i+1))

cv=[ ROOT.TCanvas('cv{}'.format(i+1),'cv{}'.format(i+1),1200,600) for i in range(3)]
for i in range(3):
  print(i)
  cv[i].cd()
  h[i].Draw()

cv[0].Print('multi_TH1.pdf[')
for i in range(3):
  cv[i].Print('multi_TH1.pdf')
cv[2].Print('multi_TH1.pdf]')
