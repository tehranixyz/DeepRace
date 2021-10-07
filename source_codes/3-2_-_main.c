void main()
{
  int i;
  int myval;
  #pragma omp parallel for ordered
  for (i = 1; i <= 10; i++)
  {
    myval = i + 2;
    #pragma omp ordered
    printf("%d %d\n", i, myval);
  }

}

