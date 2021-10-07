int buffer[100];
int main()
{
  int nthreads;
  int tid;
  #pragma omp parallel num_threads(3)
  {
    tid = omp_get_thread_num();
    printf("Hello World from thread = %d\n", tid);
    if (tid == 0)
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }

  }
  #pragma omp for schedule(runtime)
  for (int i = 0; i < 100; i++)
  {
    buffer[i] = omp_get_thread_num();
  }

  #pragma omp barrier
  for (int i = 0; i < 100; i++)
  {
    printf("data --> %d, %d\n", buffer[i], i);
  }

  return 0;
}

