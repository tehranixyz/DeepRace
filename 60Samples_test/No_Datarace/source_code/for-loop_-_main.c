int main()
{
  int i;
  int chunk;
  float a[1000];
  float b[1000];
  float c[1000];
  for (i = 0; i < 1000; i++)
    a[i] = (b[i] = i * 1.0);

  chunk = 100;
  #pragma omp parallel for shared(a,b,c,chunk) private(i) schedule(static,chunk)
  for (i = 0; i < 1000; i++)
  {
    c[i] = a[i] + b[i];
  }

  return 0;
}

