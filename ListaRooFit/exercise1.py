# Create e Gaussian pdf, generate some toy data and fit it
# Play with some other
# Exponential and Breit-Wigner

from ROOT import *

w = RooWorkspace("w")


# Variables for the Gaussian
x = RooRealVar("x","x",-5.,5.)
mu = RooRealVar("mu","mu",0,-10.,10.)
sigma = RooRealVar("sigma","sigma",1,0,1000)
#N = RooRealVar("N","N",100,0,10000)

# Variables for the Exponential
y = RooRealVar("y","y",0.,10.)
c = RooRealVar("c","c",-0.5,-2.,0.2)

# Variables for the Breit-Wigner
z = RooRealVar("z","z",20.,160.)
mean = RooRealVar("mean","mean",90.0,20,180.)
gamma = RooRealVar("gamma","gamma",4.12,0.1,100.)

# Building the distributions
gauss_pdf = RooGaussian("pdf","Gaussian Distribution",x,mu,sigma)
expo_pdf = RooExponential("expo_pdf","Exponential Distribution",y,c)
BW_pdf = RooBreitWigner("BW_pdf","Breit-Wigner Distribution",z,mean,gamma)

# Declaring the frames
plg = x.frame()
ple = y.frame()
plb = z.frame()

# Ploting the pdf
gauss_pdf.plotOn(plg)
expo_pdf.plotOn(ple)
BW_pdf.plotOn(plb)
###

# Datasets
#data_gauss = RooDataSet()
data_gauss = gauss_pdf.generate(RooArgSet(x),1000)

#data_expo = RooDataSet()
data_expo = expo_pdf.generate(RooArgSet(y),1000)

#data_gauss = RooDataSet()
data_BW = BW_pdf.generate(RooArgSet(z),1000)

# Ploting the data
data_gauss.plotOn(plg)
data_expo.plotOn(ple)
data_BW.plotOn(plb)

# Fitting
gauss_fit = gauss_pdf.fitTo(data_gauss,RooFit.Minimizer("Minuit2","Migrad"),RooFit.FitOptions(RooFit.Save(1)))
expo_fit = expo_pdf.fitTo(data_expo,RooFit.Minimizer("Minuit2","Migrad"),RooFit.FitOptions(RooFit.Save(1)))
BW_fit = BW_pdf.fitTo(data_BW,RooFit.Minimizer("Minuit2","Migrad"),RooFit.FitOptions(RooFit.Save(1)))

# Gauss
cgauss = TCanvas()
gauss_pdf.plotOn(plg)
gauss_pdf.paramOn(plg)
plg.Draw()
cgauss.SaveAs("cgauss.pdf")

# Exponential
cexpo = TCanvas()
expo_pdf.plotOn(ple)
expo_pdf.paramOn(ple)
ple.Draw()
cexpo.SaveAs("cexpo.pdf")

# Breit-Wigner
cBW = TCanvas()
BW_pdf.plotOn(plb)
BW_pdf.paramOn(plb)
plb.Draw()
cBW.SaveAs("cBW.pdf")




