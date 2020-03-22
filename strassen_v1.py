import math
import time
import random


def subtractMatrix(m1, m2):
    dim = range(len(m1))
    result = []

    for i in dim:
        result.append([])
        for j in dim:
            result[i].append(m1[i][j] - m2[i][j])
    return result


def addMatrix(m1, m2):
    dim = range(len(m1))
    result = []

    for i in dim:
        result.append([])
        for j in dim:
            result[i].append(m1[i][j] + m2[i][j])
    return result


def matmult(m1, m2):
    """ Conventional matrix multiplication algorithm. """
    dim = range(len(m1))

    result = []
    for i in dim:
        result.append([])
        for j in dim:
            result[i].append(0)
            for k in dim:
                result[i][j] += m1[i][k] * m2[k][j]
    return result


def strassenHelper(m1, m2):
    """ Recursive helper function for Strassen's algorithm. Assumes matrix with dim = power of 2. """
    # Compute size of submatrix
    resultSize = len(m1)
    subSize = int(resultSize / 2)

    # Conventional multiplication if dimension 1
    if(resultSize <= 1):
        return matmult(m1, m2)
    else:
        # Check if matrix is odd - buffer if so
        flag = resultSize % 2 != 0 and resultSize != 1
        if(flag):
            subSize += 1
        sub = range(subSize)
        res = range(resultSize)

        # slice off half of rows
        a = m1[:subSize]
        b = m1[:subSize]
        c = m1[subSize:]
        d = m1[subSize:]
        e = m2[:subSize]
        f = m2[:subSize]
        g = m2[subSize:]
        h = m2[subSize:]

        # if buffer append in a row
        if(flag):
            temp = []
            for i in res:
                temp.append(0)

            c.append(temp)
            d.append(temp)
            g.append(temp)
            h.append(temp)

        # slice half of columns
        for i in sub:
            a[i] = a[i][:subSize]
            b[i] = b[i][subSize:]
            c[i] = c[i][:subSize]
            d[i] = d[i][subSize:]
            e[i] = e[i][:subSize]
            f[i] = f[i][subSize:]
            g[i] = g[i][:subSize]
            h[i] = h[i][subSize:]

        # if flag add extra column

        if(flag):
            for i in sub:
                b[i].append(0)
                d[i].append(0)
                f[i].append(0)
                h[i].append(0)

        # Compute 7 products of Strassen's algorithm

        # f - h
        dim = range(len(f))
        subfh = []

        for i in dim:
            subfh.append([])
            for j in dim:
                subfh[i].append(f[i][j] - h[i][j])

        # a + b
        dim = range(len(a))
        addab = []

        for i in dim:
            addab.append([])
            for j in dim:
                addab[i].append(a[i][j] + b[i][j])

        # c + d
        dim = range(len(c))
        addcd = []

        for i in dim:
            addcd.append([])
            for j in dim:
                addcd[i].append(c[i][j] + d[i][j])

        # g - e
        dim = range(len(g))
        subge = []

        for i in dim:
            subge.append([])
            for j in dim:
                subge[i].append(g[i][j] - e[i][j])

        # a + d
        dim = range(len(a))
        addad = []

        for i in dim:
            addad.append([])
            for j in dim:
                addad[i].append(a[i][j] + d[i][j])

        # e + h
        dim = range(len(e))
        addeh = []

        for i in dim:
            addeh.append([])
            for j in dim:
                addeh[i].append(e[i][j] + h[i][j])

        # b - d
        dim = range(len(b))
        subbd = []

        for i in dim:
            subbd.append([])
            for j in dim:
                subbd[i].append(b[i][j] - d[i][j])

        # g + h
        dim = range(len(g))
        addgh = []

        for i in dim:
            addgh.append([])
            for j in dim:
                addgh[i].append(g[i][j] + h[i][j])

        # a - c
        dim = range(len(a))
        subac = []

        for i in dim:
            subac.append([])
            for j in dim:
                subac[i].append(a[i][j] - c[i][j])

        # e + f
        dim = range(len(g))
        addef = []

        for i in dim:
            addef.append([])
            for j in dim:
                addef[i].append(e[i][j] + f[i][j])

        p1 = strassenHelper(a, subfh)  # p1 = a(f - h)
        p2 = strassenHelper(addab, h)  # p2 = (a + b)h
        p3 = strassenHelper(addcd, e)  # p3 = (c + d)e
        p4 = strassenHelper(d, subge)  # p4 = d(g - e)
        # p5 = (a + d)(e + h)
        p5 = strassenHelper(addad, addeh)
        p6 = strassenHelper(subbd, addgh)  # p6 = (b - d)(g + h)
        p7 = strassenHelper(subac, addef)  # p7 = (a - c)(e + f)

        # Compute four quadrants of result matrix
        aebg = addMatrix(subtractMatrix(addMatrix(p5, p4), p2),
                         p6)  # p5 + p3 - p2 + p6
        afbh = addMatrix(p1, p2)  # p1 + p2
        cedg = addMatrix(p3, p4)  # p3 + p4
        cfdh = subtractMatrix(subtractMatrix(
            addMatrix(p5, p1), p3), p7)  # p5 + p1 - p3 - p7

        # make results matrix
        result = []
        for i in sub:
            result.append(aebg[i] + afbh[i])
        for i in sub:
            result.append(cedg[i] + cfdh[i])

        # if odd take out extra column and row
        if(resultSize % 2 != 0 and resultSize != 1):
            for i in res:
                result[i] = result[i][0:-1]
            result = result[0:-1]

        return result


def strassen(m1, m2):
    """ Matrix multiplication using Strassen's algorithm """

    start = time.time()
    # Determine new padded dimension
    originalDim = len(m1)

    # Multiplication using Strassen's alg
    multResult = strassenHelper(m1, m2)

    stop = time.time()
    totalTime = stop - start
    return multResult, totalTime


def make_mat(dim):
    """ Create random 0, 1 matrix of specified dimension. """
    out = []

    for i in range(dim):
        out.append([])
        for j in range(dim):
            out[i].append(random.randint(0, 1))

    return out


if __name__ == "__main__":

    m1 = make_mat(40)
    m2 = make_mat(40)
    numTrials = 5

    # Run for numTrials and compute avg time
    totalTime = 0
    for i in range(numTrials):
        stras, trialTime = strassen(m1, m2)
        totalTime += trialTime
    avgTime = totalTime / numTrials
    print("Average time: %f" % avgTime)

    conv = matmult(m1, m2)
    for i in range(len(m1)):
        for j in range(len(m1)):
            if(stras[i][j] != conv[i][j]):
                print("ERRORRR")
                break
