#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

void print_mat(int* mat, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            cout << mat[i * dimension + j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Define your dimensions
    const int dimension = 100;

    // Define your matrices
    int mat1[dimension * dimension];
    int mat2[dimension * dimension];
    int output[dimension * dimension];

    // Define your random number generator
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            mat1[i * dimension + j] = distribution(generator);
            mat2[i * dimension + j] = distribution(generator);

            output[i * dimension + j] = 0;
        }
    }

    // Non-tiling implementation - we just slap things together

    auto start = high_resolution_clock::now();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 0; k < dimension; k++) {
                output[i * dimension + j] +=
                    mat1[i * dimension + k] * mat2[k * dimension + j];
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // print_mat(output, dimension);
    cout << duration.count() * 0.000001 << endl;

    return 0;
}
