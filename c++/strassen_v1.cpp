#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

// matrix printing function for readability and debugging
void print_mat(vector<int>& mat, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            cout << mat[i * dimension + j] << "\t";
        }
        cout << endl;
    }
}

// base case of conventional matrix multiplication
void mat_mult(vector<int>& mat1,
              vector<int>& mat2,
              vector<int>& output,
              int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 0; k < dimension; k++) {
                output[i * dimension + j] +=
                    mat1[i * dimension + k] * mat2[k * dimension + j];
            }
        }
    }
}

// subtracting matrices
void subtract_mat(vector<int>& mat1,
                  vector<int>& mat2,
                  vector<int>& output,
                  int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            output[i * dimension + j] =
                mat1[i * dimension + j] - mat2[i * dimension + j];
        }
    }
}

// adding matrices
void add_mat(vector<int>& mat1,
             vector<int>& mat2,
             vector<int>& output,
             int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            output[i * dimension + j] =
                mat1[i * dimension + j] + mat2[i * dimension + j];
        }
    }
}

// main strassen function
<<<<<<< HEAD
void strassen(vector<int> &mat1, vector<int> &mat2, vector<int> &output, int dimension, int evlimit, int odlimit)
{

  // Get half size of matrix dimension
  int halfDim = int(dimension / 2);

  // check if we need padding
  int flag = 0;
  int fronthalfDim = halfDim;
  if (dimension % 2 != 0 && dimension != 1)
  {
    flag = 1;
    fronthalfDim += 1;
  }

  // If we're at base case return conventional multiplication
  if ((flag && dimension <= odlimit) || (!flag && dimension <= evlimit))
  {
    mat_mult(mat1, mat2, output, dimension);
    return;
  }

  // define a second output vector, resize our old one
  vector<int> output1;
  vector<int> output2;
  output2.resize(fronthalfDim * fronthalfDim);
  output1.resize(fronthalfDim * fronthalfDim);

  // define the quadrant matrices
  vector<int> a;
  a.resize(fronthalfDim * fronthalfDim);
  vector<int> b;
  b.resize(fronthalfDim * fronthalfDim);
  vector<int> c;
  c.resize(fronthalfDim * fronthalfDim);
  vector<int> d;
  d.resize(fronthalfDim * fronthalfDim);
  vector<int> e;
  e.resize(fronthalfDim * fronthalfDim);
  vector<int> f;
  f.resize(fronthalfDim * fronthalfDim);
  vector<int> g;
  g.resize(fronthalfDim * fronthalfDim);
  vector<int> h;
  h.resize(fronthalfDim * fronthalfDim);

  // use copy to get the parts of the matrices - specific sections to be copied
  for (int i = 0; i < halfDim; i++)
  {

    //a b, c d
    copy(mat1.begin() + (i * dimension), mat1.begin() + (i * dimension + fronthalfDim), a.begin() + (i * fronthalfDim));
    copy(mat1.begin() + (i * dimension + fronthalfDim), mat1.begin() + ((i + 1) * dimension), b.begin() + (i * fronthalfDim));

    copy(mat1.begin() + ((i + fronthalfDim) * dimension), mat1.begin() + ((i + fronthalfDim) * dimension + fronthalfDim), c.begin() + (i * fronthalfDim));
    copy(mat1.begin() + ((i + fronthalfDim) * dimension + fronthalfDim), mat1.begin() + ((i + fronthalfDim + 1) * dimension), d.begin() + (i * fronthalfDim));

    //e f, g h
    copy(mat2.begin() + (i * dimension), mat2.begin() + (i * dimension + fronthalfDim), e.begin() + (i * fronthalfDim));
    copy(mat2.begin() + (i * dimension + fronthalfDim), mat2.begin() + ((i + 1) * dimension), f.begin() + (i * fronthalfDim));

    copy(mat2.begin() + ((i + fronthalfDim) * dimension), mat2.begin() + ((i + fronthalfDim) * dimension + fronthalfDim), g.begin() + (i * fronthalfDim));
    copy(mat2.begin() + ((i + fronthalfDim) * dimension + fronthalfDim), mat2.begin() + ((i + fronthalfDim + 1) * dimension), h.begin() + (i * fronthalfDim));
  }
  if (flag)
  { // add in extra last line
    //a b
    copy(mat1.begin() + (halfDim * dimension), mat1.begin() + (halfDim * dimension + fronthalfDim), a.begin() + (halfDim * fronthalfDim));
    copy(mat1.begin() + (halfDim * dimension + fronthalfDim), mat1.begin() + ((halfDim + 1) * dimension), b.begin() + (halfDim * fronthalfDim));

    //e f
    copy(mat2.begin() + (halfDim * dimension), mat2.begin() + (halfDim * dimension + fronthalfDim), e.begin() + (halfDim * fronthalfDim));
    copy(mat2.begin() + (halfDim * dimension + fronthalfDim), mat2.begin() + ((halfDim + 1) * dimension), f.begin() + (halfDim * fronthalfDim));
  }

  // define the 7 products of Strassen
  vector<int> p1;
  p1.resize(fronthalfDim * fronthalfDim);
  vector<int> p2;
  p2.resize(fronthalfDim * fronthalfDim);
  vector<int> p3;
  p3.resize(fronthalfDim * fronthalfDim);
  vector<int> p4;
  p4.resize(fronthalfDim * fronthalfDim);
  vector<int> p5;
  p5.resize(fronthalfDim * fronthalfDim);
  vector<int> p6;
  p6.resize(fronthalfDim * fronthalfDim);
  vector<int> p7;
  p7.resize(fronthalfDim * fronthalfDim);

  // calculate the 7 values, recursion step
  subtract_mat(f, h, output1, fronthalfDim);
  strassen(a, output1, p1, fronthalfDim, evlimit, odlimit);

  add_mat(a, b, output1, fronthalfDim);
  strassen(output1, h, p2, fronthalfDim, evlimit, odlimit);

  add_mat(c, d, output1, fronthalfDim);
  strassen(output1, e, p3, fronthalfDim, evlimit, odlimit);

  subtract_mat(g, e, output1, fronthalfDim);
  strassen(d, output1, p4, fronthalfDim, evlimit, odlimit);

  add_mat(a, d, output1, fronthalfDim);
  add_mat(e, h, output2, fronthalfDim);
  strassen(output1, output2, p5, fronthalfDim, evlimit, odlimit);

  subtract_mat(b, d, output1, fronthalfDim);
  add_mat(g, h, output2, fronthalfDim);
  strassen(output1, output2, p6, fronthalfDim, evlimit, odlimit);

  subtract_mat(a, c, output1, fronthalfDim);
  add_mat(e, f, output2, fronthalfDim);
  strassen(output1, output2, p7, fronthalfDim, evlimit, odlimit);

  // calculate the combinations for the final matrix, reuse stuff
  add_mat(p5, p4, a, fronthalfDim);
  subtract_mat(a, p2, a, fronthalfDim);
  add_mat(a, p6, a, fronthalfDim);

  add_mat(p1, p2, b, fronthalfDim);

  add_mat(p3, p4, c, fronthalfDim);

  add_mat(p5, p1, d, fronthalfDim);
  subtract_mat(d, p3, d, fronthalfDim);
  subtract_mat(d, p7, d, fronthalfDim);

  // put stuff into output
  for (int i = 0; i < halfDim; i++)
  {
    copy(a.begin() + (i * fronthalfDim), a.begin() + ((i + 1) * fronthalfDim), output.begin() + (i * dimension));
    copy(b.begin() + (i * fronthalfDim), b.begin() + (i * fronthalfDim + halfDim), output.begin() + (i * dimension + fronthalfDim));

    copy(c.begin() + (i * fronthalfDim), c.begin() + ((i + 1) * fronthalfDim), output.begin() + ((i + fronthalfDim) * dimension));
    copy(d.begin() + (i * fronthalfDim), d.begin() + (i * fronthalfDim + halfDim), output.begin() + ((i + fronthalfDim) * dimension + fronthalfDim));
  }
  if (flag)
  {
    copy(a.begin() + (halfDim * fronthalfDim), a.begin() + (halfDim * fronthalfDim + fronthalfDim), output.begin() + (halfDim * dimension));
    copy(b.begin() + (halfDim * fronthalfDim), b.begin() + (halfDim * fronthalfDim + halfDim), output.begin() + (halfDim * dimension + fronthalfDim));
  }
}

int main()
{

  // Define your dimensions
  // const int dimension = 75;

  // Define your random number generator
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, 1);


  int trials = 5;
  for(int dimension = 256; dimension <= 512; dimension += 32){
    // Define your matrices
    vector<int> mat1;
    mat1.resize(dimension * dimension);
    vector<int> mat2;
    mat2.resize(dimension * dimension);
    vector<int> output;
    output.resize(dimension * dimension);
    vector<int> conv;
    conv.resize(dimension * dimension);

    int odlimit = 63;

    for(int evlimit = 16; evlimit < 20; evlimit+=2){
      // Timer intializing
      auto start = high_resolution_clock::now();
      auto stop = high_resolution_clock::now();
      auto stras_duration = duration_cast<microseconds>(stop - start);
      auto conv_duration = duration_cast<microseconds>(stop - start);

      // int evlimit = dimension / 2;

      // Running through the trials
      for(int k = 0; k < trials; k++){
        // Fill in random values for matrices
        for(int i = 0; i < dimension; i++)
        {
          for (int j = 0; j < dimension; j++)
          {
            mat1[i * dimension + j] = distribution(generator);
            mat2[i * dimension + j] = distribution(generator);
          }
        }

        //Testing Conventional step
        start = high_resolution_clock::now();
        mat_mult(mat1, mat2, conv, dimension);
        stop = high_resolution_clock::now();
        conv_duration += duration_cast<microseconds>(stop - start);

        // Testing Strassen step
=======
void strassen(vector<int>& mat1,
              vector<int>& mat2,
              vector<int>& output,
              int dimension,
              int evlimit,
              int odlimit) {
    // Get half size of matrix dimension
    int halfDim = int(dimension / 2);

    // check if we need padding
    int flag = 0;
    int fronthalfDim = halfDim;
    if (dimension % 2 != 0 && dimension != 1) {
        flag = 1;
        fronthalfDim += 1;
    }
>>>>>>> 047eddc298bb99a4d95e787bda954fffb0f0a2f5

    // If we're at base case return conventional multiplication
    if ((flag && dimension <= odlimit) || (!flag && dimension <= evlimit)) {
        mat_mult(mat1, mat2, output, dimension);
        return;
    }

<<<<<<< HEAD
      // timing strassens
      cout << dimension << "\t" << evlimit << "\t" << conv_duration.count() * 0.000001 / (double) trials << "\t" << stras_duration.count() * 0.000001 / (double) trials << endl;
=======
    // define a second output vector, resize our old one
    vector<int> output1;
    vector<int> output2;
    output2.resize(fronthalfDim * fronthalfDim);
    output1.resize(fronthalfDim * fronthalfDim);

    // define the quadrant matrices
    vector<int> a;
    a.resize(fronthalfDim * fronthalfDim);
    vector<int> b;
    b.resize(fronthalfDim * fronthalfDim);
    vector<int> c;
    c.resize(fronthalfDim * fronthalfDim);
    vector<int> d;
    d.resize(fronthalfDim * fronthalfDim);
    vector<int> e;
    e.resize(fronthalfDim * fronthalfDim);
    vector<int> f;
    f.resize(fronthalfDim * fronthalfDim);
    vector<int> g;
    g.resize(fronthalfDim * fronthalfDim);
    vector<int> h;
    h.resize(fronthalfDim * fronthalfDim);

    // use copy to get the parts of the matrices - specific sections to be
    // copied
    for (int i = 0; i < halfDim; i++) {
        // a b, c d
        copy(mat1.begin() + (i * dimension),
             mat1.begin() + (i * dimension + fronthalfDim),
             a.begin() + (i * fronthalfDim));
        copy(mat1.begin() + (i * dimension + fronthalfDim),
             mat1.begin() + ((i + 1) * dimension),
             b.begin() + (i * fronthalfDim));

        copy(mat1.begin() + ((i + fronthalfDim) * dimension),
             mat1.begin() + ((i + fronthalfDim) * dimension + fronthalfDim),
             c.begin() + (i * fronthalfDim));
        copy(mat1.begin() + ((i + fronthalfDim) * dimension + fronthalfDim),
             mat1.begin() + ((i + fronthalfDim + 1) * dimension),
             d.begin() + (i * fronthalfDim));

        // e f, g h
        copy(mat2.begin() + (i * dimension),
             mat2.begin() + (i * dimension + fronthalfDim),
             e.begin() + (i * fronthalfDim));
        copy(mat2.begin() + (i * dimension + fronthalfDim),
             mat2.begin() + ((i + 1) * dimension),
             f.begin() + (i * fronthalfDim));

        copy(mat2.begin() + ((i + fronthalfDim) * dimension),
             mat2.begin() + ((i + fronthalfDim) * dimension + fronthalfDim),
             g.begin() + (i * fronthalfDim));
        copy(mat2.begin() + ((i + fronthalfDim) * dimension + fronthalfDim),
             mat2.begin() + ((i + fronthalfDim + 1) * dimension),
             h.begin() + (i * fronthalfDim));
    }
    if (flag) {  // add in extra last line
        // a b
        copy(mat1.begin() + (halfDim * dimension),
             mat1.begin() + (halfDim * dimension + fronthalfDim),
             a.begin() + (halfDim * fronthalfDim));
        copy(mat1.begin() + (halfDim * dimension + fronthalfDim),
             mat1.begin() + ((halfDim + 1) * dimension),
             b.begin() + (halfDim * fronthalfDim));

        // e f
        copy(mat2.begin() + (halfDim * dimension),
             mat2.begin() + (halfDim * dimension + fronthalfDim),
             e.begin() + (halfDim * fronthalfDim));
        copy(mat2.begin() + (halfDim * dimension + fronthalfDim),
             mat2.begin() + ((halfDim + 1) * dimension),
             f.begin() + (halfDim * fronthalfDim));
>>>>>>> 047eddc298bb99a4d95e787bda954fffb0f0a2f5
    }

    // define the 7 products of Strassen
    vector<int> p1;
    p1.resize(fronthalfDim * fronthalfDim);
    vector<int> p2;
    p2.resize(fronthalfDim * fronthalfDim);
    vector<int> p3;
    p3.resize(fronthalfDim * fronthalfDim);
    vector<int> p4;
    p4.resize(fronthalfDim * fronthalfDim);
    vector<int> p5;
    p5.resize(fronthalfDim * fronthalfDim);
    vector<int> p6;
    p6.resize(fronthalfDim * fronthalfDim);
    vector<int> p7;
    p7.resize(fronthalfDim * fronthalfDim);

    // calculate the 7 values, recursion step
    subtract_mat(f, h, output1, fronthalfDim);
    strassen(a, output1, p1, fronthalfDim, evlimit, odlimit);

    add_mat(a, b, output1, fronthalfDim);
    strassen(output1, h, p2, fronthalfDim, evlimit, odlimit);

    add_mat(c, d, output1, fronthalfDim);
    strassen(output1, e, p3, fronthalfDim, evlimit, odlimit);

    subtract_mat(g, e, output1, fronthalfDim);
    strassen(d, output1, p4, fronthalfDim, evlimit, odlimit);

    add_mat(a, d, output1, fronthalfDim);
    add_mat(e, h, output2, fronthalfDim);
    strassen(output1, output2, p5, fronthalfDim, evlimit, odlimit);

    subtract_mat(b, d, output1, fronthalfDim);
    add_mat(g, h, output2, fronthalfDim);
    strassen(output1, output2, p6, fronthalfDim, evlimit, odlimit);

    subtract_mat(a, c, output1, fronthalfDim);
    add_mat(e, f, output2, fronthalfDim);
    strassen(output1, output2, p7, fronthalfDim, evlimit, odlimit);

    // calculate the combinations for the final matrix, reuse stuff
    add_mat(p5, p4, a, fronthalfDim);
    subtract_mat(a, p2, a, fronthalfDim);
    add_mat(a, p6, a, fronthalfDim);

    add_mat(p1, p2, b, fronthalfDim);

    add_mat(p3, p4, c, fronthalfDim);

    add_mat(p5, p1, d, fronthalfDim);
    subtract_mat(d, p3, d, fronthalfDim);
    subtract_mat(d, p7, d, fronthalfDim);

    // put stuff into output
    for (int i = 0; i < halfDim; i++) {
        copy(a.begin() + (i * fronthalfDim),
             a.begin() + ((i + 1) * fronthalfDim),
             output.begin() + (i * dimension));
        copy(b.begin() + (i * fronthalfDim),
             b.begin() + (i * fronthalfDim + halfDim),
             output.begin() + (i * dimension + fronthalfDim));

        copy(c.begin() + (i * fronthalfDim),
             c.begin() + ((i + 1) * fronthalfDim),
             output.begin() + ((i + fronthalfDim) * dimension));
        copy(d.begin() + (i * fronthalfDim),
             d.begin() + (i * fronthalfDim + halfDim),
             output.begin() + ((i + fronthalfDim) * dimension + fronthalfDim));
    }
    if (flag) {
        copy(a.begin() + (halfDim * fronthalfDim),
             a.begin() + (halfDim * fronthalfDim + fronthalfDim),
             output.begin() + (halfDim * dimension));
        copy(b.begin() + (halfDim * fronthalfDim),
             b.begin() + (halfDim * fronthalfDim + halfDim),
             output.begin() + (halfDim * dimension + fronthalfDim));
    }
}

int main() {
    // Define your dimensions
    // const int dimension = 75;

    // Define your random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 1);

    int trials = 5;
    for (int dimension = 257; dimension <= 513; dimension += 32) {
        // Define your matrices
        vector<int> mat1;
        mat1.resize(dimension * dimension);
        vector<int> mat2;
        mat2.resize(dimension * dimension);
        vector<int> output;
        output.resize(dimension * dimension);
        vector<int> conv;
        conv.resize(dimension * dimension);

        int evlimit = 48;

        for (int odlimit = 37; odlimit < 77; odlimit += 2) {
            // Timer intializing
            auto start = high_resolution_clock::now();
            auto stop = high_resolution_clock::now();
            auto stras_duration = duration_cast<microseconds>(stop - start);
            auto conv_duration = duration_cast<microseconds>(stop - start);

            // int evlimit = dimension / 2;

            // Running through the trials
            for (int k = 0; k < trials; k++) {
                // Fill in random values for matrices
                for (int i = 0; i < dimension; i++) {
                    for (int j = 0; j < dimension; j++) {
                        mat1[i * dimension + j] = distribution(generator);
                        mat2[i * dimension + j] = distribution(generator);
                    }
                }

                // Testing Conventional step
                start = high_resolution_clock::now();
                mat_mult(mat1, mat2, conv, dimension);
                stop = high_resolution_clock::now();
                conv_duration += duration_cast<microseconds>(stop - start);

                // Testing Strassen step

                start = high_resolution_clock::now();
                strassen(mat1, mat2, output, dimension, evlimit, odlimit);
                stop = high_resolution_clock::now();
                stras_duration += duration_cast<microseconds>(stop - start);
            }

            // timing strassens
            cout << dimension << "\t" << odlimit << "\t"
                 << conv_duration.count() * 0.000001 / (double) trials << "\t"
                 << stras_duration.count() * 0.000001 / (double) trials << endl;
        }
    }

    return 0;
}

// cout << "dimension: " << dimension << endl;
// cout << "conventiona, avg. duration: " << conv_duration.count() * 0.000001 /
// (double) trials << endl; cout << "strassen, avg. duration: " <<
// stras_duration.count() * 0.000001 / (double) trials << endl; cout << endl;
