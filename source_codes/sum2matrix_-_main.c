int main()
{
  int a[2][4];
  int b[2][4];
  int c[2][4];
  int i;
  int j;
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 4; j++)
    {
      a[i][j] = i + j;
      b[i][j] = (2 * i) + (2 * j);
    }

  }

  int id;
  int Sid;
  int Eid;
  int Nid;
  int T = 2;
  omp_set_num_threads(T);
  #pragma omp parallel
  {
    id = omp_get_thread_num();
    Nid = 2 / T;
    Sid = Nid * id;
    Eid = Sid + Nid;
    for (i = Sid; i < Eid; i++)
    {
      for (j = 0; j < 2; j++)
      {
        c[i][j] = a[i][j] + b[i][j];
      }

    }

  }
  for (i = 0; i < 4; i++)
  {
    for (j = 0; i < 2; j++)
    {
      printf("\t %d", c[i][j]);
    }

    printf("\n");
  }

}

