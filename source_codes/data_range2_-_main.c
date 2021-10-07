int main()
{
  {
    int isum = 0;
    #pragma omp parallel for
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for firstprivate(isum) lastprivate(isum)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for reduction(+:isum)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for reduction(+:isum) schedule(static)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for reduction(+:isum) schedule(static, 100)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for reduction(+:isum) schedule(dynamic, 100)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for reduction(+:isum) schedule(guided, 100)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for reduction(+:isum) schedule(runtime)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    int n = 800;
    #pragma omp parallel for reduction(+:isum) schedule(runtime) if (800 <= n)
    for (int i = 0; i <= 1000; i++)
      isum = isum + i;

    printf("isum=%d\n", isum);
  }
  {
    int isum = 0;
    #pragma omp parallel for ordered
    for (int i = 0; i <= 10; i++)
      printf("%d ", i);

    printf("\n");
    #pragma omp parallel for ordered
    for (int i = 0; i <= 10; i++)
      #pragma omp ordered

    printf("%d ", i);
  }
  return 0;
}

