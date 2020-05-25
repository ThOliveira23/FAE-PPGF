  
s1 = "n77e77w"
s2 = "n77e77w"

def new(s1,s2):
    if (len(s1) % 2 == 1 and len(s2) % 2 == 1):
        print s1[0] + s2[0] + s1[(len(s1) - 1)/2] + s2[(len(s2) - 1)/2] + s1[len(s1) - 1] + s2[len(s2) - 1]
    else:
        print "String with a even number of char does not have a middle value, will print only the first and last values"
        print s1[0] + s2[0] + s1[(len(s1) - 1)/2] + s1[len(s1) - 1] + s2[len(s2) - 1]
        
new(s1,s2)
