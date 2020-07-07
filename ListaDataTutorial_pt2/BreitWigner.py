
import pandas as pd
import numpy as np
from numpy import pi
import matplotlib.pyplot as plt
import math

# Create the dataset using the csv file
dataset = pd.read_csv("../Data/Zmumu_Run2011A_masses.csv")

mass = dataset['M']

# Let's limit thw fit near to the peak of the histogram
lowerlimit = 70
upperlimit = 110
bins = 100

# Let's select the invariant mass values that are inside the limitations
limitedmasses = mass[(mass > lowerlimit) & (mass < upperlimit)]

# Let's create a histogram of the selected values
histo = plt.hist(limitedmasses, bins=bins, range=(lowerlimit,upperlimit))

# In y-axis the number of the events per each bin (can be got from the variable histogram)
y = histo[0]
# In x-axis the centers of the bins
x = 0.5*(histo[1][0:-1] + histo[1][1:])

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

#BEST
initials = [6, 91, -2, 200, 13000]


# Let's import the module that is used in the optimization.
# Run the optimization and calculate the uncertainties of the optimized parameters
from scipy.optimize import curve_fit
best, covariance = curve_fit(breitwigner, x, y, p0=initials, sigma=np.sqrt(y))
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
plt.show()

# Planck constant in eV.s
h_c = 6.5821*math.pow(10,-25)

# lifetime of the Z boson is seconds
tau = h_c/best[0]
# Obtaining the error from the error propagation
error_tau = tau*(error[0]/best[0])

# tau + error_tau
print ("The lifetime of the Z boson is given by tau = {} +- {}".format(tau,error_tau))


