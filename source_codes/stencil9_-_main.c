double X[1000 + 2][1000 + 2];
double Y[1000 + 2][1000 + 2];
int main()
{
  int i;
  int j;
  struct timespec start_time;
  struct timespec end_time;
  struct timespec diff_time;
  initArr(X);
  double delta = 0.0;
  int numIters = 0;
  if (clock_gettime(CLOCK_MONOTONIC, &start_time) != 0)
    perror("Error from clock_gettime - getting start time!\n");

  do
  {
    numIters += 1;
    #pragma omp parallel for shared(X) shared(Y)
    for (i = 1; i <= 1000; ++i)
    {
      for (j = 1; j <= 1000; ++j)
      {
        Y[i][j] = ((X[i][j] * .25) + ((((X[i + 1][j] + X[i - 1][j]) + X[i][j + 1]) + X[i][j - 1]) * .125)) + ((((X[i + 1][j + 1] + X[i - 1][j + 1]) + X[i - 1][j - 1]) + X[i + 1][j - 1]) * .0625);
      }

    }

    delta = 0;
    #pragma omp parallel for reduction(max:delta) shared(X) shared(Y)
    for (i = 1; i <= 1000; ++i)
    {
      for (j = 1; j <= 1000; ++j)
      {
        double tmp_d = fabs(X[i][j] - Y[i][j]);
        delta = fmax(delta, tmp_d);
      }

    }

    #pragma omp parallel for shared(X) shared(Y)
    for (i = 1; i <= 1000; ++i)
    {
      for (j = 1; j <= 1000; ++j)
      {
        X[i][j] = Y[i][j];
      }

    }

  }
  while (delta > .000001);
  if (clock_gettime(CLOCK_MONOTONIC, &end_time) != 0)
    perror("Error from clock_gettime - getting end time!\n");

  timespec_diff(start_time, end_time, &diff_time);
  printf("Overall time: %i.%09li\n", (int) diff_time.tv_sec, diff_time.tv_nsec);
  printf("Took %d iterations to converge\n", numIters);
}

