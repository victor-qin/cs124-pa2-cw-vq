import time
from conventional_v0 import make_mat
from strassen_v1 import subtractMatrix, addMatrix, matmult, strassenHelper, strassen


def main():

    dimension = range(700, 701)
    # make matrices
    for dim in dimension:
        print("Dimension: ", dim)
        mat1 = make_mat(dim)
        mat2 = make_mat(dim)

        start = time.time()
        conv = matmult(mat1, mat2)
        stop = time.time()
        duration = stop - start
        print("Conventional: ", duration)

        start = time.time()
        conv = strassen(mat1, mat2)
        stop = time.time()
        duration = stop - start
        print("Strassen: ", duration)


    return 0

if __name__ == '__main__':
    main()
