#ifndef CUDA_LIB_
#define CUDA_LIB_
#define GRID_SIZE 32
#define BLOCK_SIZE 32
#define MAX_SIZE 100

void cuda_sparse_matrix_mult(float A[MAX_SIZE][MAX_SIZE], float B[MAX_SIZE][MAX_SIZE], float C[MAX_SIZE][MAX_SIZE], 
  int a_row, int a_col, int b_col);
#endif
