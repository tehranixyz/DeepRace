int main()
{
  srand(time(0));
  int a[20][20];
  int b[20][20];
  int mult[20][20];
  int mult2[20][20];
  int i;
  int j;
  int k;
  int r = 20;
  int c = 20;
  int result = 1;
  #pragma omp parallel for private(i,j)
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
  {
    a[i][j] = rand() % 100;
  }


  #pragma omp parallel for private(i,j)
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
  {
    b[i][j] = rand() % 100;
  }


  #pragma omp parallel for private(i,j)
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
  {
    mult[i][j] = 0;
    mult2[i][j] = 0;
  }


  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
    for (k = 0; k < c; ++k)
  {
    mult[i][j] += a[i][k] * b[k][j];
  }



  #pragma omp parallel for private(i,j,k)
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
    for (k = 0; k < c; ++k)
  {
    mult2[i][j] += a[i][k] * b[k][j];
  }



  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
  {
    printf("%d ", mult[i][j]);
    if (j == (c - 1))
      printf("\n ");

  }


  printf("\n ");
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
  {
    printf("%d ", mult2[i][j]);
    if (j == (c - 1))
      printf("\n ");

  }


  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j)
  {
    if (mult[i][j] != mult2[i][j])
    {
      result = 0;
    }

  }


  if (result == 1)
    printf("True\n");
  else
    printf("False\n");

  return 0;
}

