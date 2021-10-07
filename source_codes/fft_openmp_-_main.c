int main();
void ccopy(int n, double x[], double y[]);
void cfft2(int n, double x[], double y[], double w[], double sgn);
void cffti(int n, double w[]);
double ggl(double *ds);
void step(int n, int mj, double a[], double b[], double c[], double d[], double w[], double sgn);
void timestamp();
int main()
{
  double error;
  int first;
  double flops;
  double fnm1;
  int i;
  int icase;
  int it;
  int ln2;
  int ln2_max = 25;
  double mflops;
  int n;
  int nits = 10000;
  int proc_num;
  static double seed;
  double sgn;
  int thread_num;
  double *w;
  double wtime;
  double *x;
  double *y;
  double *z;
  double z0;
  double z1;
  timestamp();
  printf("\n");
  printf("FFT_OPENMP\n");
  printf("  Demonstrate an implementation of the Fast Fourier Transform of a complex data vector, using OpenMP for parallel execution.\n");
  printf("  Number of processors available = %d\n", omp_get_num_procs());
  printf("  Number of threads = %d\n", omp_get_max_threads());
  printf("\n");
  printf("           N      NITS    Error         Time          Time/Call     MFLOPS\n");
  seed = 331.0;
  n = 1;
  for (ln2 = 1; ln2 <= ln2_max; ln2++)
  {
    n = 2 * n;
    w = (double *) malloc(n * (sizeof(double)));
    x = (double *) malloc((2 * n) * (sizeof(double)));
    y = (double *) malloc((2 * n) * (sizeof(double)));
    z = (double *) malloc((2 * n) * (sizeof(double)));
    first = 1;
    for (icase = 0; icase < 2; icase++)
    {
      if (first)
      {
        for (i = 0; i < (2 * n); i = i + 2)
        {
          z0 = ggl(&seed);
          z1 = ggl(&seed);
          x[i] = z0;
          z[i] = z0;
          x[i + 1] = z1;
          z[i + 1] = z1;
        }

      }
      else
      {
        #pragma omp parallel shared ( n, x, z ) private ( i, z0, z1 )
        #pragma omp for nowait
        for (i = 0; i < (2 * n); i = i + 2)
        {
          z0 = 0.0;
          z1 = 0.0;
          x[i] = z0;
          z[i] = z0;
          x[i + 1] = z1;
          z[i + 1] = z1;
        }

      }

      cffti(n, w);
      if (first)
      {
        sgn = +1.0;
        cfft2(n, x, y, w, sgn);
        sgn = -1.0;
        cfft2(n, y, x, w, sgn);
        fnm1 = 1.0 / ((double) n);
        error = 0.0;
        for (i = 0; i < (2 * n); i = i + 2)
        {
          error = (error + pow(z[i] - (fnm1 * x[i]), 2)) + pow(z[i + 1] - (fnm1 * x[i + 1]), 2);
        }

        error = sqrt(fnm1 * error);
        printf("%12d  %8d  %12e", n, nits, error);
        first = 0;
      }
      else
      {
        wtime = omp_get_wtime();
        for (it = 0; it < nits; it++)
        {
          sgn = +1.0;
          cfft2(n, x, y, w, sgn);
          sgn = -1.0;
          cfft2(n, y, x, w, sgn);
        }

        wtime = omp_get_wtime() - wtime;
        flops = (2.0 * ((double) nits)) * ((5.0 * ((double) n)) * ((double) ln2));
        mflops = (flops / 1.0E+06) / wtime;
        printf("  %12e  %12e  %12f\n", wtime, wtime / ((double) (2 * nits)), mflops);
      }

    }

    if ((ln2 % 4) == 0)
    {
      nits = nits / 10;
    }

    if (nits < 1)
    {
      nits = 1;
    }

    free(w);
    free(x);
    free(y);
    free(z);
  }

  printf("  Normal end of execution.\n");
  timestamp();
  return 0;
}

