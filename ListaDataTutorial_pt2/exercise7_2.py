'''Question 4 - Write a function that represents Breit-Wigner distribution to the values of the histogram.

To get information about mass and lifetime of the detected resonance, a function that describes the distribution of the invariant masses must be fitted to the values of the histogram. In our case the values follow a Breit-Wigner distribution:

where E is the energy, M is the maximum of the distribution (equals to the mass of the particle that is detected in the resonance), Gamma the full width at half maximum (FWHM) or the decay width of the distribution and K a constant.


The Breit-Wigner distribution can also be expressed in the following form where the constant K is written open.


The decay width Gamma and the lifetime tau of the particle detected in the resonance are related in the following way:

Gamma = h/2pi*tau


'''

import pandas as pd
import numpy as np
from numpy import pi
import matplotlib.pyplot as plt
import math

# Create the dataset using the csv file
dataset = pd.read_csv("../Data/Zmumu_Run2011A_masses.csv")

mass = dataset['M']
E1 = dataset['E1']
E2 = dataset['E2']
E = (dataset['E1']**2 + dataset['E2']**2)**0.5
#print E

# Let's limit thw fit near to the peak of the histogram
min = 70
max = 110
bins = 100

# Let's select the invariant mass values that are inside the limitations
limitedmasses = mass[(mass > min) & (mass < max)]

# Let's create a histogram of the selected values
h = plt.hist(limitedmasses, bins=bins, range=(min,max))

# In y-axis the number of the events per each bin (can be got from the variable histogram)
y = h[0]
#print ('y = ',y)
# In x-axis the center value of the bins
x = 0.5*(h[1][0:-1] + h[1][1:])
#print ('x = ',x)
#print dataset.head()

# Let's define a function that describes Breit-Wigner distribution for the fit.
# E is the energy, gamma is the decay width, M the maximum of the distribution and a, b and A different parameters that are used for noticing the effect of the background events for the fit

def breitwigner(E,gamma,M,a,b,A):
    return a*E+b+A*( (2*np.sqrt(2)*M*gamma*np.sqrt(M**2*(M**2+gamma**2)))/(np.pi*np.sqrt(M**2+np.sqrt(M**2*(M**2+gamma**2)))) )/((E**2-M**2)**2+M**2*gamma**2)
    
# Initial values for the optimization in the following order
# gamma (the full width at half maximum (FWHM) of the distribution)
# M (the maximum of the distribution)
# a (the slope that is used for noticing the effect of the background)
# b (the y intercept that is used for noticing the effect of the background)
# A (the "height" of the Breit-Wigner distribution)

#parameters = [gamma, M, a, b, A]
parameters = [6, 91, -2, 200, 13000]


# Let's import the module that is used in the optimization.
# Run the optimization and calculate the uncertainties of the optimized parameters
from scipy.optimize import curve_fit
#From https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.curve_fit.html
#scipy.optimize.curve_fit(f, xdata, ydata, p0=None, sigma=None, absolute_sigma=False, check_finite=True, bounds=- inf, inf, method=None, jac=None, **kwargs)[source]
best, covariance = curve_fit(breitwigner, x, y, p0=parameters, sigma=np.sqrt(y))
error = np.sqrt(np.diag(covariance))

# Let's print the values and uncertainties that are got from the optimization
print("The values and the uncertainties from the optimization")
print("")
first = "The value of the decay width (gamma) + {} +- {}".format(best[0],error[0])
second = "The value of the maximum of the distribution (M) = {} +- {}".format(best[1], error[1])
third = "a = {} +- {}".format(best[2], error[2])
fourth = "b = {} +- {}".format(best[3], error[3])
fifth = "A = {} +- {}".format(best[4], error[4])

print(first,second,third,fourth,fifth)

plt.plot(x, breitwigner(x, *best), 'r-', label='gamma = {}, M = {}'.format(best[0], best[1]))
plt.xlabel('Invariant mass [GeV]')
plt.ylabel('Number of event')
plt.title('The Breit-Wigner fit')
plt.legend()
#plt.show()

'''Question 5 - Calculate the lifetime tau of the Z boson with the uncertainty by using the fit. Compare the calculated value to known the lifetime of the Z, What do you notice? What could possibly explain your observations?'''


# Planck constant in eV.s
h_c = 6.5821*math.pow(10,-25)

# Decay Width in GeV http://pdg.lbl.gov/2020/listings/rpp2020-list-z-boson.pdf
Gamma_Z = 2.4952
err_Gamma_Z = 0.0023

# Calculating the lifetime of Z
tau_Z = h_c/Gamma_Z

err_tau_Z = tau_Z*(err_Gamma_Z/Gamma_Z)

# lifetime of the Z boson is seconds using the PDG decay width value
print ("The lifetime of the Z boson, using the decay width = {} +- {}".format(tau_Z,err_tau_Z))

#===========================================================================================================

# Calculating the lifetime of Z using fit results
tau = h_c/best[0]
# Obtaining the error from the error propagation
error_tau = tau*(error[0]/best[0])



# lifetime of the Z boson is seconds using the fit results
print ("The lifetime of the Z boson is given by tau = {} +- {}".format(tau,error_tau))



''' The difference in Z lifetime value is because the origin of its decay width value, since the difference between the two values are way more than 2 sigma. The origin of this problem can be associated to the determination of the boson Z decay width, since those two quantities are related by a constant. The decay width value obtained as a fit result is not compatible with the expected value as we can see in PDG.   '''
