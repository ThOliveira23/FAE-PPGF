import math


# Perimeter for a rectangle
def perimeter_rect(h,w):
    P = 2*(h + w)
    return P
    
# Perimeter for a square
def perimeter_quad(a):
    P = 4*a
    return P

# Perimeter for a circle
def perimeter_cir(r):
    P = 2*math.pi*r
    return P


