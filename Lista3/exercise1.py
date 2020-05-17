import ROOT

# Definition of the function

def function(p0,p1):
    c = ROOT.TCanvas()
    f = ROOT.TF1("f", "[0]*sin([1]*x)/x",0.0,10.0)
    f.SetLineColor(4)
    f.SetTitle("")
    f.SetParameters(p0,p1)
    f.Draw()
    c.SaveAs("Ex1_fun_"+str(p0)+"_"+str(p1)+".pdf")
    print("f.Eval = ",f.Eval(1))
    print("f.Derivative = ",f.Derivative(1))
    print("f.Integral = ",f.Integral(0,3))

# Ploting the function for different parameter values
function(1,2)
function(1,1)
function(2,2)
function(5,5)
function(7,3)
