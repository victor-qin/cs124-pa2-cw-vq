#!/usr/bin/env python
import random
import time

def make_mat(dim):

    out = []

    for i in range(dim):
        out.append([])
        for j in range(dim):
            out[i].append(random.randint(0,1))

    return out

def matmult(m1, m2):
    """ Conventional matrix multiplication algorithm. """
    dim = len(m1)

    result = [[0 for i in range(dim)] for j in range(dim)]

    for i in range(dim):
        for k in range(dim):
            for j in range(dim):
                result[i][j] += m1[i][k] * m2[k][j]
    return result

def main():

    # matrix dimension, n
    dimension = 100

    # initialize matrices
    mat1 = make_mat(dimension)
    mat2 = make_mat(dimension)
    # output = make_mat(dimension, 0)


    start = time.time()
    # multiply elements
    output = matmult(mat1, mat2)
    end = time.time()
    duration = end - start

    # print(output)
    print(duration)

    return 0

if __name__ == '__main__':
    main()
