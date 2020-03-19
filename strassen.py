import math


def subtractMatrix(m1, m2):
    dim = len(m1)
    result = [[0 for i in range(dim)] for j in range(dim)]
    for i in range(dim):
        for j in range(dim):
            result[i][j] = m1[i][j] - m2[i][j]
    return result


def addMatrix(m1, m2):
    dim = len(m1)
    result = [[0 for i in range(dim)] for j in range(dim)]
    for i in range(dim):
        for j in range(dim):
            result[i][j] = m1[i][j] + m2[i][j]
    return result


def matmult(m1, m2):
    """ Conventional matrix multiplication algorithm. """
    dim = len(m1)
    result = [[0 for i in range(dim)] for j in range(dim)]
    for i in range(dim):
        for k in range(dim):
            for j in range(dim):
                result[i][j] += m1[i][k] * m2[k][j]
    return result


def strassenHelper(m1, m2):
    """ Recursive helper function for Strassen's algorithm. Assumes matrix with dim = power of 2. """

    # Compute size of submatrix
    resultSize = len(m1)
    subSize = resultSize / 2

    if(resultSize <= 1):
        return matmult(m1, m2)
    else:
        # Divide each matrix into four submatrices
        a = [[0 for i in range(subSize)] for j in range(subSize)]
        b = [[0 for i in range(subSize)] for j in range(subSize)]
        c = [[0 for i in range(subSize)] for j in range(subSize)]
        d = [[0 for i in range(subSize)] for j in range(subSize)]
        e = [[0 for i in range(subSize)] for j in range(subSize)]
        f = [[0 for i in range(subSize)] for j in range(subSize)]
        g = [[0 for i in range(subSize)] for j in range(subSize)]
        h = [[0 for i in range(subSize)] for j in range(subSize)]

        for i in range(subSize):
            for j in range(subSize):
                a[i][j] = m1[i][j]
                b[i][j] = m1[i][j + subSize]
                c[i][j] = m1[i + subSize][j]
                d[i][j] = m1[i + subSize][j + subSize]
                e[i][j] = m2[i][j]
                f[i][j] = m2[i][j + subSize]
                g[i][j] = m2[i + subSize][j]
                h[i][j] = m2[i + subSize][j + subSize]

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

        # Copy results into result matrix
        result = [[0 for i in range(resultSize)] for j in range(resultSize)]
        for i in range(subSize):
            for j in range(subSize):
                result[i][j] = aebg[i][j]
                result[i][j + subSize] = afbh[i][j]
                result[i + subSize][j] = cedg[i][j]
                result[i + subSize][j + subSize] = cfdh[i][j]
        return result


def strassen(m1, m2):
    """ Matrix multiplication using Strassen's algorithm """

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
    multResult = strassenHelper(pad1, pad2)

    # Reduce matrix size to original dimensions
    finalResult = [[0 for i in range(originalDim)] for j in range(originalDim)]
    for i in range(originalDim):
        for j in range(originalDim):
            finalResult[i][j] = multResult[i][j]
    return finalResult


if __name__ == "__main__":
    m1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    m2 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    print(strassen(m1, m2))
