int main()
{
  int myid;
  int num_thds;
  int i;
  #pragma omp parallel for private(myid, num_thds)
  for (i = 0; i < 16; i++)
  {
    myid = omp_get_thread_num();
    num_thds = omp_get_num_threads();
    printf("i = %d. Executed by thread %d out of %d threads.\n", i, myid, num_thds);
  }

}

