#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

void print_mat(int* mat, int dimension){
  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      cout << mat[i*dimension + j] << "\t";
    }
    cout << endl;
  }
}

void mat_mult(int* mat1, int* mat2, int* output, int dimension){
  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      for(int k = 0; k < dimension; k++){
        output[i*dimension + j] += mat1[i*dimension + k] * mat2[k*dimension + j];
      }
    }
  }
}

void subtract_mat(int* mat1, int* mat2, int* output, int dimension){

  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      output[i*dimension + j] = mat1[i*dimension + j] - mat2[i*dimension + j];
    }
  }
}

void add_mat(int* mat1, int* mat2, int* output, int dimension){

  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      output[i*dimension + j] = mat1[i*dimension + j] + mat2[i*dimension + j];
    }
  }
}

void strassen(int* mat1, int* mat2, int* output, int dimension){

  int halfDim = int(dimension / 2);
  int output1[dimension * dimension];
  int output2[dimension * dimension];

  if(dimension <= 1){
    return mat_mult(mat1, mat2, output1, dimension);
  } else {

    int flag = 0;
    if(dimension % 2 != 0 && dimension != 1){
      flag = 1;
      halfDim += 1;
    }

  }

}

int main(){





  return 0;
}
