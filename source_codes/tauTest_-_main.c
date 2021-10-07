int main()
{
  int i = 0;
  omp_set_num_threads(4);
  int *values = (int *) malloc((sizeof(int)) * omp_get_num_threads());
  int threadNum = 0;
  #pragma omp parallel shared(values)
  {
    threadNum = omp_get_thread_num();
    printf("Thread %d\n", threadNum);
    values[threadNum] = doComputation((1 + threadNum) * 100000000);
  }
  for (i = 0; i < 4; i++)
  {
    printf("Thread %d calculated %d\n", i, values[i]);
  }

}

