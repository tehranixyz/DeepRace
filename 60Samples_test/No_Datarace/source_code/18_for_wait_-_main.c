int a[20000][20000];
int main()
{
  int i;
  int j;
  #pragma omp parallel private(i,j)
  {
    #pragma omp for
    for (i = 0; i < 20000; i++)
      for (j = i; j < 20000; j++)
      a[i][j] = i + j;


    #pragma omp for
    for (i = 0; i < 20000; i++)
      for (j = 0; j < i; j++)
      a[i][j] = i - j;


  }
}

