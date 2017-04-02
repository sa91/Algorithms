#!/usr/bin/python
import random as R
import sys
N=1000000;
print N 
for i in xrange(N) :
    T=max(1,int(R.random()*4))
    print T
    if T == 1:
        print max(1,int(R.random()*(10**9))) 
    elif  T == 2:
        print max(1,int(R.random()*(10**2))) 
        
