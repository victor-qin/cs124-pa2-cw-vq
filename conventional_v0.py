#!/usr/bin/env python
import random
import time

def main():

    # matrix dimension, n
    dimension = 100

    # initialize matrices
    mat1 = []
    mat2 = []
    output = []

    # populate the matrices
    for i in range(dimension):
        mat1.append([])
        mat2.append([])
        output.append([])
        for j in range(dimension):
            mat1[i].append(random.randint(0,1))
            mat2[i].append(random.randint(0,1))
            output[i].append(0)


    start = time.time()
    # multiply elements
    for i in range(dimension):
        for j in range(dimension):
            for k in range(dimension):
                output[i][j] += mat1[i][k] * mat2[k][j]
    end = time.time()
    duration = end - start

    # print output
    print(duration)

    return 0

if __name__ == '__main__':
    main()
