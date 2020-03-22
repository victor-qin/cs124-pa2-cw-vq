import time
import multiprocessing
from conventional_v0 import make_mat
from strassen_v1 import subtractMatrix, addMatrix, matmult, strassenHelper, strassen


def main():

    dimension = range(400, 401)
    flag = 0
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

        timeout = duration + 60

        start = time.time()
        stras = multiprocessing.Process(target = strassen, args = (mat1, mat2, ), name="strassen")

        stras.start()
        stras.join(timeout)

        if stras.is_alive():
            print('Function terminated')
            stras.terminate()
            stras.join()
        else:
            print('LIMIT FOUND: ', dim)
            flag = 1


        stop = time.time()
        duration = stop - start
        print("Strassen: ", duration)

        if(flag):
            print("Terminating: ", dim)
            break

    return 0

if __name__ == '__main__':
    main()
