#!/usr/bin/python3

import numpy as np
import sys

## Generate noise points
def noise_gen(begin, end, dens):
    return np.random.randint(begin, end, (1, 2, dens+1))[0]

## Generate data heaps
def data_gen(pos, rad,dens):
    # generate the points
    theta = np.random.rand((dens+1)) * (2 * np.pi)
    r = np.random.randint(0,rad,(1,1,dens+1))
    return [r[0][0] * np.cos(theta) + pos[0], r[0][0] * np.sin(theta) + pos[1]]

def sample1():
    d1 = data_gen([50,50],5,100)
    d2 = data_gen([10,20],15,100)
    d3 = data_gen([80,30],10,100)
    n = noise_gen(0,100,100)
    return np.hstack((n,d1,d2,d3))

def sample2():
    d1 = data_gen([10,10],5,100)
    d2 = data_gen([90,90],5,100)
    d3 = data_gen([10,90],5,100)
    d4 = data_gen([90,10],5,100)
    n = noise_gen(0,100,100)
    return np.hstack((n,d1,d2,d3,d4))

def sample3():
    d1 = data_gen([20,20],10,100)
    d2 = data_gen([60,60],5,100)
    return np.hstack((d1,d2))

def sample4():
    ns = noise_gen(-100,100,200)
    return ns

def samples(n):
    if n==1:
        return sample1()
    elif n==2:
        return sample2()
    elif n==3:
        return sample3()
    elif n==4:
        return sample4()
    else:
        return sample1()


def generate(nsample):
    return samples(nsample)

def savetoFile(fname, res):
    f =open(fname,'w')
    for i in range(0,res[0].size):
        f.write("{0},{1},1\n".format(res[0][i],res[1][i]))
    f.close() 
    
def print_samples(res):
    for i in range(0,res[0].size):
        print(res[0][i],res[1][i], sep=',')

if __name__ == "__main__":
    save2file = False
    if len(sys.argv) == 2:
        n = int(sys.argv[1])
    elif len(sys.argv) == 3:
        n = int(sys.argv[1])
        outfile = sys.argv[2]
        save2file = True
    else:
        print("generator.py <sample num [1,2,3,4] | file name to save>\n\
              1 - 3 clusters + noise\n2 - 4 clusters + noise\n\
              3 - 2 clusters\n4 - noise\n")
        exit(0)
    res = samples(n)
    print_samples(res)
    if(save2file):
        savetoFile(outfile, res)