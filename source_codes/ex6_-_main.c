int main()
{
  int A[6][10];
  int B[6][10];
  int C[6][10];
  int i;
  int j;
  for (i = 0; i < 6; i++)
  {
    for (j = 0; j < 10; j++)
    {
      A[i][j] = i + j;
      B[i][j] = (i * 2) + (j * 2);
    }

  }

  int id;
  int Sid;
  int Eid;
  int Nid;
  int T = 6;
  Nid = 6 / T;
  omp_set_num_threads(T);
  #pragma omp parallel
  {
    id = omp_get_thread_num();
    Sid = Nid * id;
    Eid = Sid + Nid;
    for (i = Sid; i < Eid; i++)
    {
      for (j = 0; j < 10; j++)
      {
        C[i][j] = A[i][j] + B[i][j];
      }

    }

  }
  int result = 1;
  for (i = 0; i < 6; i++)
  {
    if (result == 0)
    {
      break;
    }

    for (j = 0; j < 10; j++)
    {
      if (C[i][j] != (A[i][j] + B[i][j]))
      {
        result = 0;
        break;
      }

    }

  }

  if (result == 1)
  {
    printf("True");
  }
  else
  {
    printf("False");
  }

  return 0;
}

