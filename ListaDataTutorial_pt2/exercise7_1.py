# Importing panda, matplotlib and numpy

import pandas as pd
import numpy as np
from numpy import pi
import matplotlib.pyplot as plt
import math

# Create the dataset using the csv file
dataset = pd.read_csv("../Data/Zmumu_Run2011A_masses.csv")

# Conditions to large and small eta values.
# These conditions can be changed, but it is necesssary to have same amount events in both groups
cond_eta_1 = 1.00
cond_eta_2 = 1.00
# 1,32e 0.75

# Create two DataFrames

# Large eta, eta > cond_eta_1
large_eta = dataset[(np.absolute(dataset.eta1) > cond_eta_1) & (np.absolute(dataset.eta2) > cond_eta_1)]
# Small eta, eta < cond_eta_2
small_eta = dataset[(np.absolute(dataset.eta1) < cond_eta_2) & (np.absolute(dataset.eta2) < cond_eta_2)]

print('\n' * 2)

print('The amount of all events = %d' % len(dataset))
print('The amount of events where the pseudorapidity of both muons has been large = %d' %len(large_eta))
print('The amount of events where the pseudorapidity of both muons has been small = %d' %len(small_eta))

############ Histograms part #################

#For eta values larger than condition
inv_mass_large = large_eta['M']

# Create the histogram from data in variable "inv_mass1". Set bins and range.
plt.hist(inv_mass_large.values, bins=120, range=(60,120))

# Set y-axis range from 0 to 60.
axes = plt.gca()
axes.set_ylim([0,60])


# Name the axises and give a title.
plt.xlabel('Invariant mass [GeV]')
plt.ylabel('Number of events per bin')
plt.title('Histogram of invariant masses for the events where the\n pseudorapidity of both of the muons has been large\n')
plt.show()

#For eta values larger than condition
inv_mass_small = small_eta['M']

# Create the histogram from data in variable "inv_mass1". Set bins and range.
plt.hist(inv_mass_small.values, bins=120, range=(60,120))

# Set y-axis range from 0 to 60.
axes = plt.gca()
axes.set_ylim([0,60])


# Name the axises and give a title.
plt.xlabel('Invariant mass [GeV]')
plt.ylabel('Number of events per bin')
plt.title('Histogram of invariant masses for the events where the\n pseudorapidity of both of the muons has been small\n')
plt.show()


########## Exercises ##############

'''
Question 1 - In which way you can see the effect of the pseudorapidity to the measurement resolution of the CMS detector?

For the most central region, with eta close to 0, we have a better reconstruction of the particle invariant mass, it is most simple to measure the energy and momentum of the particles, due to material budget of the detector.

Question 2 - Do your results show the same than the theory predicts?

 Yes, this result is expected since the particles that hits the endcaps instead of the barrel encounters more matter than the particles in the barrel, causing more uncertainties in the measure of the its properties, like momenta/energy and positioning
 
After asnwering to the questions you can try to change the conditions for the large and small pseudorapidities in first code cell. The conditions are named cond_eta_1 and cond_eta_2. Make you sure choose conditions in a way that there will be nearly same amount of events in both groups.

Question 3 - After the changes run the code again, How do the changes affect the number of the events? And how to histograms?

If the changes in the threshold values increase the gap between the limits, the number of events gets too different, preventing the comparation between the two histograms. For changes that mantains the number of events for both groups almost the same we can observe a narrower distribution for the Z mass. 

'''

