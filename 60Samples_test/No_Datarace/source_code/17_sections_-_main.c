int main()
{
  int i;
  int a[10];
  int b[20];
  omp_set_num_threads(1);
  #pragma omp parallel private(i)
  {
    #pragma omp sections
    {
      #pragma omp section
      for (i = 0; i < 10; i++)
        a[i] = (i * 10) + 5;

      #pragma omp section
      for (i = 0; i < 20; i++)
        b[i] = (i * 5) + 10;

    }
  }
  for (i = 0; i < 10; i++)
    printf("%d ", a[i]);

  printf("\n");
  for (i = 0; i < 20; i++)
    printf("%d ", b[i]);

  printf("\n");
}

