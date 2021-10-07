int main()
{
  double *a;
  int i;
  int tid;
  int nthreads;
  int chunk_size;
  a = malloc(32 * (sizeof(double)));
  #pragma omp parallel private(i, tid)
  {
    tid = omp_get_thread_num();
    #pragma omp for
    for (i = 0; i < 32; i++)
    {
      a[i] = tid;
    }

  }
  for (i = 0; i < 32; i++)
  {
    printf("%f\n", a[i]);
  }

}

