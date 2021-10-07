int main()
{
  int k;
  int j;
  int nt;
  int lim;
  int index;
  int A[8] = {1, 0, 0, 0, 1, 1, 0, 1};
  int B[4][8] = {0};
  int C[4][8] = {0};
  int D[8] = {0};
  omp_set_num_threads(8);
  #pragma omp parallel private(j)
  {
    j = omp_get_thread_num();
    B[3][j] = A[j];
  }
  nt = 4;
  for (k = 2; k >= 0; k--)
  {
    omp_set_num_threads(nt);
    #pragma omp parallel private(j)
    {
      j = omp_get_thread_num();
      B[k][j] = B[k + 1][2 * j] + B[k + 1][(2 * j) + 1];
    }
    nt /= 2;
  }

  for (k = 0; k <= 3; k++)
  {
    lim = 8 / pow(2, 3 - k);
    #pragma omp parallel for private(j)
    for (j = 0; j < lim; j++)
    {
      if (j == 0)
      {
        C[k][j] = B[k][j];
      }
      else
        if ((j % 2) == 1)
      {
        C[k][j] = C[k - 1][j / 2];
      }
      else
      {
        C[k][j] = C[k - 1][(j / 2) - 1] + B[k][j];
      }


    }

  }

  for (j = 0; j <= 3; j++)
  {
    for (k = 0; k < 8; k++)
    {
      printf("%d ", B[j][k]);
    }

    printf("\n");
  }

  printf("-----\nprefix sum tree\n");
  for (j = 0; j <= 3; j++)
  {
    for (k = 0; k < 8; k++)
    {
      printf("%d ", C[j][k]);
    }

    printf("\n");
  }

  printf("-----\ncompacted array\n");
  index = 0;
  for (k = 0; k < 8; k++)
  {
    if (A[k] == 1)
    {
      D[index++] = k;
    }

  }

  for (k = 0; k < 8; k++)
  {
    printf("%d ", D[k]);
  }

  printf("\n");
}

