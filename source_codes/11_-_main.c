int main()
{
  int fibno[100] = {0};
  int i;
  int j;
  int temp;
  int n;
  int tid;
  printf("Enter the no range :");
  scanf("%d", &n);
  omp_set_num_threads(2);
  #pragma omp parallel
  {
    printf("No of threads ; %d\n", omp_get_num_threads());
    #pragma omp for
    for (j = 1; j <= n; j++)
    {
      temp = random_num();
      printf("Thread id %d\n", tid);
      #pragma omp critical
      {
        for (i = 0; i < temp; i++)
          fibno[i] = fib(i);

        printf("No of values in the series \n");
        for (i = 0; i < temp; i++)
          printf("%d\t", fibno[i]);

      }
    }

  }
}

