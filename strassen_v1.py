import math
import time
import random
from conventional_v0 import matmult


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
    if(resultSize <= 8):
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
        p1 = strassenHelper(a, subtractMatrix(f, h))
        p2 = strassenHelper(addMatrix(a, b), h)
        p3 = strassenHelper(addMatrix(c, d), e)
        p4 = strassenHelper(d, subtractMatrix(g, e))
        p5 = strassenHelper(addMatrix(a, d), addMatrix(e, h))
        p6 = strassenHelper(subtractMatrix(b, d), addMatrix(g, h))
        p7 = strassenHelper(subtractMatrix(a, c), addMatrix(e, f))

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
    newDim = 2 ** int(math.ceil(math.log(originalDim, 2)))

    pad1 = [[0 for i in range(newDim)] for j in range(newDim)]
    pad2 = [[0 for i in range(newDim)] for j in range(newDim)]

    # TODO - omit copying over all values manually?
    for i in range(originalDim):
        for j in range(originalDim):
            pad1[i][j] = m1[i][j]
            pad2[i][j] = m2[i][j]

    # Multiplication using Strassen's alg
    # multResult = strassenHelper(pad1, pad2)
    multResult = strassenHelper(m1, m2)

    # Reduce matrix size to original dimensions
    finalResult = [[0 for i in range(originalDim)] for j in range(originalDim)]
    for i in range(originalDim):
        for j in range(originalDim):
            finalResult[i][j] = multResult[i][j]

    stop = time.time()
    print("Internal Duration: ", stop - start)
    return finalResult


def make_mat(dim):

    out = []

    for i in range(dim):
        out.append([])
        for j in range(dim):
            out[i].append(random.randint(0, 1))

    return out


if __name__ == "__main__":
    # m1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    # m2 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

    m1 = make_mat(100)
    m2 = make_mat(100)

    stras = strassen(m1, m2)

    conv = matmult(m1, m2)
    for i in range(len(m1)):
        for j in range(len(m1)):
            if(stras[i][j] != conv[i][j]):
                print("ERRORRR")
                break
