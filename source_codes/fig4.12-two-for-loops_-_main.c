int main()
{
  int i;
  int n = 9;
  int a[n];
  int b[n];
  #pragma omp parallel default(none) shared(n,a,b) private(i)
  {
    #pragma omp single
    printf("First for-loop: number of threads is %d\n", 1);
    #pragma omp for schedule(runtime)
    for (i = 0; i < n; i++)
    {
      printf("Thread %d executes loop iteration %d\n", 0, i);
      a[i] = i;
    }

    #pragma omp single
    printf("Second for-loop: number of threads is %d\n", 1);
    #pragma omp for schedule(runtime)
    for (i = 0; i < n; i++)
    {
      printf("Thread %d executes loop iteration %d\n", 0, i);
      b[i] = 2 * a[i];
    }

  }
  return 0;
}

