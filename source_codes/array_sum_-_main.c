int main()
{
  double *a = (double *) malloc((sizeof(double)) * 10000000);
  double *c = (double *) malloc((sizeof(double)) * 10000000);
  int i;
  int j;
  double start_time;
  double run_time1;
  double run_time2;
  double run_time3;
  double run_time4;
  double run_time5;
  printf("secs1 secs2 secs3 secs4 secs5 nthreads\n");
  for (j = 1; j <= 10; j++)
  {
    omp_set_num_threads(j);
    double x = 12;
    for (i = 0; i < 10000000; i++)
    {
      c[i] = 2;
      a[i] = 10;
    }

    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < 10000000; i++)
      x = 10 * i;

    run_time1 = omp_get_wtime() - start_time;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < 10000000; i++)
      x = c[i] * 10;

    run_time2 = omp_get_wtime() - start_time;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < 10000000; i++)
      c[i] = c[i] * x;

    run_time4 = omp_get_wtime() - start_time;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < 10000000; i++)
      c[i] = a[i] * x;

    run_time5 = omp_get_wtime() - start_time;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < 10000000; i++)
      c[i] = x;

    run_time3 = omp_get_wtime() - start_time;
    printf("%f %f %f %f %f %d\n", run_time1, run_time2, run_time3, run_time4, run_time5, j);
  }

}

