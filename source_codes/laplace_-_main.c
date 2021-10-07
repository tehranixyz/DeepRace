int main()
{
  double *u;
  double *b;
  double x;
  double y;
  double h;
  double uc;
  int i;
  int j;
  int n;
  int iter;
  int niter;
  n = 201;
  u = (double *) malloc((n * n) * (sizeof(double)));
  b = (double *) malloc((n * n) * (sizeof(double)));
  #pragma omp parallel for
  for (int j = 0; j < n; j++)
    for (int i = 0; i < n; i++)
    u[i + (j * n)] = 0;


  h = 1.0 / (n - 1);
  #pragma omp parallel for
  for (int j = 0; j < n; j++)
    for (int i = 0; i < n; i++)
  {
    x = i * h;
    y = j * h;
    b[i + (j * n)] = (h * h) * f(x, y);
  }


  ;
  niter = 10000;
  for (iter = 1; iter <= niter; iter++)
  {
    #pragma omp parallel for
    for (int j = 1; j < (n - 1); j++)
      for (int i = 1; i < (n - 1); i++)
    {
      if (((i + j) % 2) == 0)
        u[i + (j * n)] = ((((u[(i - 1) + (j * n)] + u[i + ((j - 1) * n)]) + u[(i + 1) + (j * n)]) + u[i + ((j + 1) * n)]) - b[i + (j * n)]) / 4.0;

    }


    #pragma omp parallel for
    for (int j = 1; j < (n - 1); j++)
      for (int i = 1; i < (n - 1); i++)
    {
      if (((i + j) % 2) == 1)
        u[i + (j * n)] = ((((u[(i - 1) + (j * n)] + u[i + ((j - 1) * n)]) + u[(i + 1) + (j * n)]) + u[i + ((j + 1) * n)]) - b[i + (j * n)]) / 4.0;

    }


    if ((iter % 1000) == 0)
      printf("%i u(0.5,0.5)= %lf\n", iter, u[((n - 1) / 2) + (((n - 1) / 2) * n)]);

  }

}

