import time
import multiprocessing
from conventional_v0 import make_mat
from strassen_v1 import subtractMatrix, addMatrix, matmult, strassenHelper, strassen


def main():

    dimension = range(700, 1501, 100)
    flag = 0
    # make matrices
    for dim in dimension:
        print("Dimension: ", dim)
        mat1 = make_mat(dim)
        mat2 = make_mat(dim)

        start = time.time()
        conv = matmult(mat1, mat2)
        stop = time.time()
        duration_conv = stop - start
        print("Conventional: ", duration_conv)

        timeout = duration_conv + 60

        start = time.time()
        stras = multiprocessing.Process(target = strassen, args = (mat1, mat2, ), name="strassen")

        stras.start()
        stras.join(timeout)

        if stras.is_alive():
            print('Function terminated')
            stras.terminate()
            stras.join()



        stop = time.time()
        duration_stras = stop - start
        print("Strassen: ", duration_stras)

        if(duration_stras < duration_conv):
            print("CROSSOVER FOUND Terminating: ", dim)
            break

    return 0

if __name__ == '__main__':
    main()
