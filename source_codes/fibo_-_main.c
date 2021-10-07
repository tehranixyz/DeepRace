int fibo(int);
int main()
{
  int nthreads;
  int tid;
  int n = 5;
  #pragma omp parallel num_threads(4) private(tid)
  {
    #pragma omp single
    {
      tid = omp_get_thread_num();
      printf("Hello world from (%d)\n", tid);
      printf("Fib(%d)=%d by %d\n", n, fibo(n), tid);
    }
  }
}

