import math
import ROOT

def binomial(N,s,p):
    P = (math.factorial(N)/(math.factorial(N-s)*math.factorial(s)))*(math.pow(p,s))*(math.pow((1-p),N-s))
    return P

def makelist(N):
    list = []
    for i in range(0,N,1):
        list.append(i)
    return list
    

def histplot():
    list_P = []
    h = ROOT.TH2F("","",16,0,16,16,0,0.3)
    c = ROOT.TCanvas()
    for s in makelist(16):
        #print s,binomial(15,s,0.25)
        h.Fill(s,binomial(15,s,0.25))
        if (s >= 3):
            list_P.append(binomial(15,s,0.25))
            
    print "The number of students that answer correctly at least 3 questions can be calculated by N(s>3) = no_of_students * P(s>3) = ","1000*",sum(list_P),1000*sum(list_P)
    h.Draw("COL")
    h.SetMarkerStyle
    c.SaveAs("Binomial.pdf")
    #return P
    #print P
    
    

histplot()

