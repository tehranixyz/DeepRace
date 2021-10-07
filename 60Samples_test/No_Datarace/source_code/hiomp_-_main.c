int main()
{
  int nthreads;
  int tid;
  #pragma omp parallel num_threads(8) private(nthreads, tid)
  {
    tid = omp_get_thread_num();
    printf("thread = %d\n", tid);
    if (tid == 0)
    {
      nthreads = omp_get_num_threads();
      printf("number of threads = %d\n", nthreads);
    }

  }
  return 0;
}

