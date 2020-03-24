#include <iostream>
#include <random>
#include <chrono>
#include <array>
#include "strassen_v0.cpp"

using namespace std;
using namespace std::chrono;

void graphGen(vector<int> &matrix, int dim, float p)
{
    // Generates graph with dim vertices, edge probability p.

    // Define random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 1);

    // Fill in random values for matrices
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            matrix[i * dim + j] = distribution(generator);
        }
    }
    return;
}

double triangles(vector<int> &matrix, vector<int> &output, int dim, float p)
{
    // Computes number of triangles in a graph using Strassen's algorithm.

    // Generate graph with given probabilities
    graphGen(matrix, dim, p);

    // Compute A^3
    strassen(matrix, matrix, output, dim);
    strassen(matrix, output, output, dim);

    // Add diagonal entries
    double diagSum = 0;
    for (int i = 0; i < dim; i++)
    {
        diagSum = diagSum + output[i * i];
    }
    double numTriangles = diagSum / 6;
    return numTriangles;
}

int main()
{

    // Edit dims, probabilities, numTrials here
    int dim = 1024;
    std::array<float, 5> probs = {0.01, 0.02, 0.03, 0.04, 0.05};
    int numTrials = 5;

    // Test values
    dim = 10;
    float p = 0.01;

    // Initialize adjacency matrix
    vector<int> matrix;
    matrix.resize(dim * dim);

    graphGen(matrix, dim, p);
    print_mat(matrix, dim);
    return 0;

    /* Code to run triangles
    // Compute average number of triangles for given parameters
    for (int i = 0; i < probs.size(); i++)
    {
        double avg = 0;
        for (int j = 0; j < numTrials; j++)
        {
            // avg += triangles(dim, p);
            avg += 1;
        }
        avg = avg / numTrials;
        cout << "Average number of triangles, probability " << probs[i] << ": " << avg << endl;
    }

    */
}