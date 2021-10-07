int main()
{
  int arr[16];
  int i;
  #pragma omp parallel num_threads(4) private(i) shared(arr)
  {
    #pragma omp single
    {
      printf("[Thread %d/%d] I am the producer\n", omp_get_thread_num(), omp_get_num_threads());
      for (i = 0; i < 16; i++)
      {
        #pragma omp task firstprivate(i) shared(arr)
        {
          printf("[Thread %d/%d] i is %d. I will execute\n", omp_get_thread_num(), omp_get_num_threads(), i);
          arr[i] = i * 2;
        }
      }

    }
  }
  printf("\n----------------\n");
  for (i = 0; i < 16; i++)
    printf("arr[%d] is %d\n", i, arr[i]);

  return 0;
}

