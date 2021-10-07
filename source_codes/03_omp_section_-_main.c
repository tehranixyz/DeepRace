void main()
{
  int i;
  float a[1000];
  float b[1000];
  float c[1000];
  float d[1000];
  for (i = 0; i < 1000; i++)
  {
    a[i] = i * 1.5;
    b[i] = i + 22.35;
  }

  #pragma omp parallel shared(a,b,c,d) private(i)
  {
    #pragma omp sections nowait
    {
      #pragma omp section
      for (i = 0; i < 1000; i++)
      {
        c[i] = a[i] + b[i];
      }

      #pragma omp section
      for (i = 0; i < 1000; i++)
      {
        d[i] = a[i] * b[i];
      }

    }
  }
}

