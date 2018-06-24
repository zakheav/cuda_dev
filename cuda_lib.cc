#include <stdio.h>
#include <iostream>
#include <math.h>
#include "cuda_lib.h"
#include "stl.h"
/*__global__ void matrix_mult(float* A_row_valid_value, int* A_row_valid_idx, int* A_info,
  float* A_row_valid_value, int* A_row_valid_idx, int* A_info) {

}*/

void cuda_sparse_matrix_mult(float A[MAX_SIZE][MAX_SIZE], float B[MAX_SIZE][MAX_SIZE], float C[MAX_SIZE][MAX_SIZE], 
  int a_row, int a_col, int b_col) {
    // 构建sparse_matrix结构
    float** A_info = new float *[a_row];
    float** B_info = new float *[a_col];
    int A_total = 0, B_total = 0;

    vec<int>* A_row_valid_idx_temp = new vec<int>[a_row];
    vec<int>* B_row_valid_idx_temp = new vec<int>[a_col];
    
    for (int i = 0; i < a_row; ++i) {
        A_info[i] = new float[2];
        A_info[i][0] = 0;
        for (int j = 0; j < a_col; ++j) {
            if (fabs(A[i][j]) > 0.000001) {
                ++A_info[i][0];
                ++A_total;
                A_row_valid_idx_temp[i].add(j);
            }
        }
    }
    for (int i = 0; i < a_col; ++i) {
        B_info[i] = new float[2];
        B_info[i][0] = 0;
        for (int j = 0; j < b_col; ++j) {
            if (fabs(B[i][j]) > 0.000001) {
                ++B_info[i][0];
                ++B_total;
                B_row_valid_idx_temp[i].add(j);
            }
        }
    }

    int* A_row_valid_idx = new int[A_total];
    int* B_row_valid_idx = new int[B_total];
    float* A_row_valid_value = new float[A_total];
    float* B_row_valid_value = new float[B_total];

    int A_idx = 0;
    for (int i = 0; i < a_row; ++i) {
        A_info[i][1] = A_idx;
        for (int j = 0; j < A_row_valid_idx_temp[i].m_size; ++j) {
            A_row_valid_idx[A_idx] = A_row_valid_idx_temp[i].get(j);
            A_row_valid_value[A_idx] = A[i][A_row_valid_idx_temp[i].get(j)];
            ++A_idx;
        }
    }

    int B_idx = 0;
    for (int i = 0; i < a_col; ++i) {
        B_info[i][1] = B_idx;
        for (int j = 0; j < B_row_valid_idx_temp[i].m_size; ++j) {
            B_row_valid_idx[B_idx] = B_row_valid_idx_temp[i].get(j);
            B_row_valid_value[B_idx] = B[i][B_row_valid_idx_temp[i].get(j)];
            ++B_idx;
        }
    }

    // debug
    for (int i = 0; i < A_total; ++i) {
        std::cout << A_row_valid_value[i] << " ";
        std::cout << A_row_valid_idx[i] << std::endl;
    }

    delete[] A_row_valid_idx;
    delete[] B_row_valid_idx;
    delete[] A_row_valid_value;
    delete[] B_row_valid_value;
    delete[] A_row_valid_idx_temp;
    delete[] B_row_valid_idx_temp;
    for (int i = 0; i < a_row; ++i) {
        delete[] A_info[i];
    }
    delete[] A_info;
    for (int i = 0; i < a_col; ++i) {
        delete[] B_info[i];
    }
    delete[] B_info;
}
int main() {
    float A[100][100] = {
        {1,0,0,2,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1}
    };
    float B[100][100] = {
        {1,0,0,0,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1}
    };
    
    float C[100][100] = {0};
    cuda_sparse_matrix_mult(A, B, C, 5, 5, 5);
}
