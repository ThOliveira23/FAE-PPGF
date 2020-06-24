# Write a code that estimate the area of a unit disk using the hit-or-miss Monte Carlo method. We know the radius of the unit disk is 1 thus the unit circle is inscribed with a square of legnth 2.
# We could generate samples within this square and count the numer of points falling within the disk
#To test whether the point is inside(hit) or outside(miss) the disk, we simply need to measure the distance of the samples from the origin (the center of the unit disk) and check whether this distance is smaller or equal than the disk radius (1 for a unit disk).

import random
import math

N = 100000

# We have to account the number of hits inside the circle and oustide the circle(inside the square)
circle_hits = 0.
square_hits = 0.

# The area of a square with length 2
sqaure_area = 2**2

# Total random numbers generate = possible x values * possible y values
for i in range(N):
    # Randomly generated x and y values from a uniform distribution
    # Since the length of the square is 2, the range of x and y possible values is -1 to 1
    rand_x = random.uniform(-1,1)
    rand_y = random.uniform(-1,1)
    print (rand_x,rand_y)
    
    # Distance between (x.y) from the origin
    dist = math.sqrt(rand_x*rand_x + rand_y*rand_y)
    #print dist
    # Checking if (x,y) lies inside the circle
    if dist <=1:
        circle_hits += 1
    square_hits += 1
    
# Since the distance from origin can be measured in 4 different quadrants.
area = 4*circle_hits/N
    
#area = square_points*math.pow(circle_points,-1)
print area
    
    
    
    
    
    
    
