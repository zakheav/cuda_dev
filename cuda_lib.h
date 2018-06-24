#ifndef CUDA_LIB_
#define CUDA_LIB_
#define GRID_SIZE 32
#define BLOCK_SIZE 32
#define MAX_SIZE 100

void cuda_sparse_matrix_mult(float A[100][100], float B[100][100], float C[100][100], int a_row, int a_col, int b_col);
#endif
