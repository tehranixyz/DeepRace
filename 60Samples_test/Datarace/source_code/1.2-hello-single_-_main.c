int main()
{
  int myid;
  int nthreads;
  #pragma omp parallel shared(nthreads)
  {
    myid = omp_get_thread_num();
    #pragma omp single
    nthreads = omp_get_num_threads();
    printf("%d of %d - hello world!\n", myid, nthreads);
  }
  return 0;
}

