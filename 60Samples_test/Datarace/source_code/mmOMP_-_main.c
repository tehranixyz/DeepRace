int main()
{
  int tid;
  int nthreads;
  int i;
  int j;
  int k;
  int chunk;
  double a[8][10];
  double b[10][5];
  double c[8][5];
  chunk = 10;
  #pragma omp parallel shared(a,b,c,nthreads,chunk)
  {
    tid = omp_get_thread_num();
    if (tid == 0)
    {
      nthreads = omp_get_num_threads();
      printf("Starting matrix multiple example with %d threads\n", nthreads);
      printf("Initializing matrices...\n");
    }

    #pragma omp for schedule (static, chunk)
    for (i = 0; i < 8; i++)
      for (j = 0; j < 10; j++)
      a[i][j] = i + j;


    #pragma omp for schedule (static, chunk)
    for (i = 0; i < 10; i++)
      for (j = 0; j < 5; j++)
      b[i][j] = i * j;


    #pragma omp for schedule (static, chunk)
    for (i = 0; i < 8; i++)
      for (j = 0; j < 5; j++)
      c[i][j] = 0;


    printf("Thread %d starting matrix multiply...\n", tid);
    #pragma omp for schedule (static, chunk)
    for (i = 0; i < 8; i++)
    {
      printf("Thread=%d did row=%d\n", tid, i);
      for (j = 0; j < 5; j++)
        for (k = 0; k < 10; k++)
        c[i][j] += a[i][k] * b[k][j];


    }

  }
  printf("******************************************************\n");
  printf("Result Matrix:\n");
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 5; j++)
      printf("%6.2f   ", c[i][j]);

    printf("\n");
  }

  printf("******************************************************\n");
  printf("Done.\n");
  return 0;
}

