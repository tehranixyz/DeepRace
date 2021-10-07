int main()
{
  long long A[2000][1000];
  long long B[1000][2500];
  long long C[1000][1000];
  int i;
  int j;
  int k;
  int l;
  int sum;
  int numb_proc;
  int id;
  int part;
  int offset;
  for (i = 0; i < 2000; i++)
    for (j = 0; j < 1000; j++)
    A[i][j] = i * j;


  for (i = 0; i < 1000; i++)
    for (j = 0; j < 2500; j++)
    B[i][j] = i * j;


  memset(C, 0, ((sizeof(int)) * 1000) * 1000);
  #pragma omp parallel shared(A,B,C) private(i,j,k,l,sum,numb_proc,id,part,offset)
  {
    id = omp_get_thread_num();
    numb_proc = omp_get_num_threads();
    part = 2000 / (numb_proc - 1);
    offset = part * (id - 1);
    if (id == (numb_proc - 1))
      part += 2000 % (numb_proc - 1);

    if (id != 0)
    {
      for (i = offset; i < (part + offset); i++)
      {
        for (j = 0; j < 2500; j++)
        {
          sum = 0;
          for (k = 0; k < 1000; k++)
            sum += A[i][k] * B[k][j];

          C[i][j] = sum;
        }

      }

    }

  }
  for (i = 0; i < 2000; i++)
    printf("%ll\n", A[i][0]);

  return 0;
}

