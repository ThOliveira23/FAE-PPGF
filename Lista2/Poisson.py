import math
import ROOT


def Poisson(mu,N):
    h=ROOT.TH1F("Poisson Distribution for #mu = 3.870","Poisson Distribution for #mu = 3.870",100,0.,20.)
    c = ROOT.TCanvas()
    
    P = (math.exp(-mu)*math.pow(mu,N))/(math.factorial(N))
    for i in range(0,N,1):
            x = ROOT.gRandom.Poisson(mu)
            h.Fill(x)
    h.Draw("HIST")
    c.SaveAs("Poisson.pdf")
 
    return h


Poisson(3.870,15)
