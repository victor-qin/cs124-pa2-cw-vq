#include <array>
#include <chrono>
#include <iostream>
#include <random>

#include "strassen.cpp"

using namespace std;
using namespace std::chrono;

void graphGen(vector<int>& matrix, int dim, float p) {
    // Generates graph with dim vertices, edge probability p.

    // Define random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // std::default_random_engine generator;
    std::bernoulli_distribution distribution(p);

    // Fill in random values for matrices
    for (int i = 0; i < dim; i++) {
        for (int j = i; j < dim; j++) {
            if (i == j) {
                matrix[i * dim + j] = 0;
            } else {
                int edgeVal = distribution(generator);
                matrix[i * dim + j] = edgeVal;
                matrix[j * dim + i] = edgeVal;
            }
        }
    }
    return;
}

double triangles(vector<int>& matrix, vector<int>& output, int dim, float p) {
    // Computes number of triangles in a graph using Strassen's algorithm.
    const double divFactor = 6.0;

    // Generate graph with given probabilities
    graphGen(matrix, dim, p);

    // Compute A^3
    strassen(matrix, matrix, output, dim);
    strassen(matrix, output, output, dim);

    // Add diagonal entries
    double diagSum = 0.0;
    for (int i = 0; i < dim; i++) {
        diagSum = diagSum + (double) output[i * dim + i];
    }
    double numTriangles = (double) diagSum / (double) divFactor;
    return numTriangles;
}

int main() {
    // Edit dims, probabilities, numTrials here
    int dim = 1024;
    std::array<float, 5> probs = {0.01, 0.02, 0.03, 0.04, 0.05};
    double numTrials = 5;

    // Initialize adjacency, output matrices
    vector<int> matrix;
    matrix.resize(dim * dim);
    vector<int> output;
    output.resize(dim * dim);

    // Compute average number of triangles for given parameters
    for (int i = 0; i < probs.size(); i++) {
        double avg = 0;
        for (int j = 0; j < numTrials; j++) {
            avg += triangles(matrix, output, dim, probs[i]);
        }
        avg = avg / numTrials;
        cout << "Average number of triangles, probability " << probs[i] << ": "
             << avg << endl;
        cout << "Expected number of triangles: "
             << 178433024 * (probs[i] * probs[i] * probs[i]) << endl;
    }

    return 0;
}
