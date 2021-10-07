int main()
{
  float a[100000];
  float b[100000];
  float c[100000];
  float res[100000];
  float val;
  int i;
  int err = 0;
  #pragma omp parallel for
  for (i = 0; i < 100000; i++)
  {
    a[i] = (float) i;
    b[i] = 2.0 * ((float) i);
    c[i] = 0.0;
    res[i] = i + (2 * i);
  }

  #pragma omp target
  #pragma omp teams distribute parallel for simd
  for (i = 0; i < 100000; i++)
  {
    c[i] = a[i] + b[i];
  }

  #pragma omp parallel for reduction(+:err)
  for (i = 0; i < 100000; i++)
  {
    val = c[i] - res[i];
    val = val * val;
    if (val > 0.0000001)
      err++;

  }

  printf(" vectors added with %d errors\n", err);
  return 0;
}

