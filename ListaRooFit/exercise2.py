# Construct a JPsi and Psi(2S) + background PDF
# JPsi with a Crystal Ball function
# Psi(2S) with a similar Crystal Ball
# Background with polynomial
######################################

from ROOT import *

inputFile = TFile("DataSet_lowstat.root")
data = inputFile.Get("data")

#The observable using RooRealVar
#RooRealVar (const char *name, const char *title, Double_t value, Double_t minValue, Double_t maxValue, const char *unit="")
mass = RooRealVar("mass","#mu^{+}#mu^{-} invariant mass",2.,6.,"GeV")


# We will parametrize the JPsi using a Crystal Ball function, composed by: mean, sigma and alpha
#  The CrystalBall shape is Gaussian that is "connected" to an exponential taill at "alpha" sigma of the Gaussian. The sign determines if it happens on the left or right side. The n parameter control the slope of the exponential part.

#
JPsi_mean = RooRealVar("JPsi_mean","The Jpsi mean for Crystal Ball",3.1,2.8,3.2)
JPsi_sigma = RooRealVar("JPsi_sigma","The Jpsi width for Crystal Ball",0.3,0.0001,1.)
JPsi_alpha = RooRealVar("JPsi_alpha","The Jpsi alpha for Crystal Ball",1.5,-5.,5.)
JPsi_n = RooRealVar("JPsi_n","The JPsi n parameter for the Crystal Ball",1.5,0.5,5.)

# Writing the Crystal Ball parametrization for the JPsi using RooCBShape
# RooCBShape (const char *name, const char *title, RooAbsReal &_m, RooAbsReal &_m0, RooAbsReal &_sigma, RooAbsReal &_alpha, RooAbsReal &_n)
JPsi_CB = RooCBShape("JPsi_CB","The JPsi Crystal Ball parametrization",mass,JPsi_mean,JPsi_sigma,JPsi_alpha,JPsi_n)

# To parametrize the Psi(2S) we will use Crystal Ball function again, using the same parameters as for JPsi, but tooking a different mass value, since the mass for JPsi(2S) is shifted wrt to the JPsi, so it's necessary to declare it before declaring the parametrization itself.

Psi2S_mean = RooRealVar("Psi2S_mean","The mean of the Psi(2S) Crystal Ball",3.7,3.65,3.75)
# Writing the Crystal Ball parametrization for the Psi(2S) using RooCBShape
Psi2S_CB = RooCBShape("Psi2S_CB","The Psi(2S) Crystal Ball",mass,Psi2S_mean,JPsi_sigma,JPsi_alpha,JPsi_n)

# To the background, we will use a Polynomial parametrization, which uses a mean and three parameters. Polynomial::p(x,{a0,a1,a2})
# We have to declare the parameters a0,a1 and a2
a0 = RooRealVar("a0","a0",-0.7,-2.,2.)
a1 = RooRealVar("a1","a1",0.3,-2.,2.)
a2 = RooRealVar("a2","a2",-0.03,-2.,2.)

# To parametrize the background function
#RooChebychev (const char *name, const char *title, RooAbsReal &_x, const RooArgList &_coefList)
#RooPolynomial (const char *name, const char *title, RooAbsReal &_x, const RooArgList &_coefList, Int_t lowestOrder=1)
#background_PDF = RooChebychev("background_PDF","The PDF for background",mass,RooArgList(a0,a1,a2))
background_PDF = RooPolynomial("background_PDF","The PDF for background",mass,RooArgList(a0,a1,a2))

# Defining the number of signal (JPsi,Psi2S) and background events
JPsi_N = RooRealVar("JPsi_N","The number of Jpsi signal events",1500.,0.1,10000.)
Psi2S_N = RooRealVar("Psi2S_N","The number of Psi2S signal events",1500.,0.1,10000.)
background_N = RooRealVar("background_N","The number of background events",5000.,0.1,50000.)


# In order to construct the total PDF
total_PDF = RooAddPdf("total_PDF","The total PDF",RooArgList(JPsi_CB,Psi2S_CB,background_PDF),RooArgList(JPsi_N,Psi2S_N,background_N))

# To do the fit
total_PDF.fitTo(data, RooFit.Extended(1))

#Now plot the data and the fit result
frame = mass.frame()
data.plotOn(frame)
total_PDF.plotOn(frame)

#One can also plot the single components of the total PDF, like the background component
total_PDF.plotOn(frame, RooFit.Components("background_PDF"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))

#Draw the results
c = TCanvas()
frame.Draw()
c.SaveAs("exercise2.png")


