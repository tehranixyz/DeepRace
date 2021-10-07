int main()
{
  int threadsnum = 1;
  double start;
  double end;
  double time;
  double startchuan;
  double endchuan;
  double timechuan;
  int i;
  int j;
  int flg;
  int sum = 0;
  int a = 0;
  FILE *fp;
  fp = fopen("result", "w");
  startchuan = omp_get_wtime();
  for (i = 2; i <= 100000; i++)
  {
    flg = 1;
    for (j = 2; j < i; j++)
    {
      if ((i % j) == 0)
      {
        flg = 0;
        break;
      }

    }

    if (flg)
    {
      sum += i;
      a = a + 1;
      fprintf(fp, "%d\t", i);
    }

  }

  endchuan = omp_get_wtime();
  timechuan = endchuan - startchuan;
  printf("串行运行时间 = %13.5f seconds\n", timechuan);
  for (threadsnum = 1; threadsnum <= 8; threadsnum++)
  {
    omp_set_num_threads(threadsnum);
    start = omp_get_wtime();
    #pragma omp parallel for
    for (i = 2; i <= 100000; i++)
    {
      if (i == 2)
      {
        printf("线程数为%5d\n", omp_get_num_threads());
      }

      flg = 1;
      for (j = 2; j < i; j++)
      {
        if ((i % j) == 0)
        {
          flg = 0;
          break;
        }

      }

    }

    end = omp_get_wtime();
    time = end - start;
    printf("并行时间为 %13.5f seconds\n", time);
    printf("加速比为 %13.5f\n ", time / timechuan);
  }

  printf("%d\n", a);
  fclose(fp);
  return 0;
}

