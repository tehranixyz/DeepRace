int main()
{
  int x;
  int count;
  int i;
  x = 0;
  count = 0;
  #pragma omp parallel shared(x)
  {
    #pragma omp critical
    x = x + 1;
  }
  printf("critical section done. x=%d\n", x);
  #pragma omp parallel
  {
    for (i = 0; i < 100; i++)
      #pragma omp atomic

    count++;
  }
  printf("atomic done. count=%d\n", count);
  return 0;
}

