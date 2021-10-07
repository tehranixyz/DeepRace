int main()
{
  int k;
  int j;
  int nt;
  int A[8] = {1, 1, 0, 0, 1, 1, 0, 1};
  int B[4][8] = {0};
  int C[4][8] = {0};
  int D[8] = {0};
  int E[16] = {0};
  int F[8] = {1, 2, 5, 7, 8, 9, 12, 13};
  int G[8] = {0, 3, 4, 6, 10, 11, 14, 15};
  omp_set_num_threads(8);
  #pragma omp parallel
  {
    j = omp_get_thread_num();
    B[3][j] = A[j];
  }
  nt = 4;
  for (k = 2; k >= 0; k--)
  {
    omp_set_num_threads(nt);
    #pragma omp parallel
    {
      j = omp_get_thread_num();
      B[k][j] = B[k + 1][2 * j] + B[k + 1][(2 * j) + 1];
    }
    nt /= 2;
  }

  nt = 1;
  for (k = 0; k <= 3; k++)
  {
    omp_set_num_threads(nt);
    #pragma omp parallel
    {
      j = omp_get_thread_num();
      if (j == 0)
      {
        C[k][j] = B[k][j];
      }
      else
      {
        if ((j % 2) == 1)
        {
          C[k][j] = C[k - 1][j / 2];
        }
        else
        {
          C[k][j] = C[k - 1][(j / 2) - 1] + B[k][j];
        }

      }

      if (k == 3)
      {
        if (A[j])
        {
          D[C[k][j] - 1] = j;
        }

      }

    }
    nt *= 2;
  }

  for (k = 0; k <= 3; k++)
  {
    for (j = 0; j < 8; j++)
    {
      printf("%2d ", B[k][j]);
    }

    printf("\n");
  }

  for (k = 0; k <= 3; k++)
  {
    for (j = 0; j < 8; j++)
    {
      printf("%2d ", C[k][j]);
    }

    printf("\n");
  }

  printf("---\n");
  for (j = 0; j < 8; j++)
  {
    printf("%2d ", D[j]);
  }

  printf("\n");
  for (j = 0; j < 8; j++)
  {
    printf("%2d ", A[j]);
  }

  printf("\n");
}

