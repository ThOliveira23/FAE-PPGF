# For a general circle area calculation, we can assume the square has length l and the circle with radius equals to l/2.

import random
import math


def area_calc(l,N):
    # We have to account the number of hits inside the circle with radius l/2 and oustide the circle(inside the square with length l)
    circle_hits = 0.           # should increase with dist < l/2
    square_hits = 0.           # should increase in each iteration step since all points will lie inside the square but not necessarily inside the circle
    square_area = math.pow(l,2)
    
    for i in range(N):
        # The x and y values will be generated randomly inside the square
        # The range shoud lie inside in the interval [-l/2,l/2] since the square has length l
        x = random.uniform(-l/2,l/2)
        y = random.uniform(-l/2,l/2)


        # Distance from the origin
        dist = math.sqrt(x*x + y*y)

        # Check if the (x,y) pair will lie inside the circle
        if dist <= l/2:
            circle_hits += 1
        # All points will lie inside the square
        square_hits +=1
        
    area = 4*circle_hits/square_hits
    print area
    return area
    
    
area_calc(2,100000)
