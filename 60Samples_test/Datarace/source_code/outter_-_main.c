int main()
{
  clock_t start;
  clock_t end;
  int *sequence;
  int *aux;
  int p;
  double cpu_time_used;
  start = clock();
  int s_seq;
  #pragma omp parallel for
  for (p = 8; p <= 14; p++)
  {
    s_seq = pow(2, p);
    sequence = (int *) malloc(s_seq * (sizeof(int)));
    aux = (int *) malloc(s_seq * (sizeof(int)));
    for (int k = 0; k < s_seq; k++)
    {
      aux[k] = (sequence[k] = k);
    }

    int jump = 0;
    int i;
    int j;
    int a = 0;
    while (pow(2, jump) < s_seq)
    {
      {
        if (a == 0)
        {
          printf("numbrs of threads: %d\n", omp_get_thread_num());
        }

        a = 1;
        for (i = s_seq - 1; i > 0; i--)
        {
          j = i - pow(2, jump);
          if (j >= 0)
          {
            sequence[i] = sequence[i] + sequence[j];
          }
          else
          {
            i = 0;
          }

        }

      }
      jump++;
    }

    for (i = 0; i < s_seq; i++)
    {
      printf("%d ", sequence[i]);
    }

    sequence = (aux = 0);
    printf("\n");
  }

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f\n", cpu_time_used);
  return 0;
}

