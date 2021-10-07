void main()
{
  struct timeval etstart;
  struct timeval etstop;
  struct timezone tzdummy;
  clock_t etstart2;
  clock_t etstop2;
  unsigned long long usecstart;
  unsigned long long usecstop;
  struct tms cputstart;
  struct tms cputstop;
  static int dim;
  int i;
  int j;
  int k;
  static int sum = 0;
  static int a[10000][10000];
  static int b[10000][10000];
  static int c[10000][10000];
  printf("Specify the dimension value\n");
  scanf("%d", &dim);
  if (dim > 10000)
  {
    printf("enter the range less than 10000");
  }

  for (i = 0; i < dim; i++)
  {
    for (j = 0; j < dim; j++)
    {
      a[i][j] = rand();
    }

  }

  for (i = 0; i < dim; i++)
  {
    for (j = 0; j < dim; j++)
    {
      b[i][j] = rand();
    }

  }

  printf("\nStarting clock.\n");
  gettimeofday(&etstart, &tzdummy);
  etstart2 = times(&cputstart);
  #pragma omp parallel shared(a,b,c,dim) private(i,j,k)
  {
    #pragma omp for schedule(static)
    for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
      {
        c[i][j] = 0;
      }

    }

    for (i = 0; i < dim; i++)
    {
      #pragma omp for schedule(static)
      for (j = 0; j < dim; j++)
        for (k = 0; k < dim; k++)
        c[i][j] += a[i][k] * b[k][j];


    }

  }
  gettimeofday(&etstop, &tzdummy);
  etstop2 = times(&cputstop);
  printf("Stopped clock.\n");
  usecstart = (((unsigned long long) etstart.tv_sec) * 1000000) + etstart.tv_usec;
  usecstop = (((unsigned long long) etstop.tv_sec) * 1000000) + etstop.tv_usec;
  printf("\nElapsed time = %g ms.\n", ((float) (usecstop - usecstart)) / ((float) 1000));
}

