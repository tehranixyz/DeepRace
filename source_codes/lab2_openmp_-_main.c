int array_a[10];
int array_b[10];
int array_c[10];
int smallest_value;
int largest_value;
int average_value;
int main()
{
  smallest_value = 10;
  largest_value = -1;
  average_value = 0;
  srand(time(0) + 1);
  int i;
  int tid;
  int nthreads;
  omp_set_num_threads(4);
  #pragma omp parallel shared(smallest_value, largest_value, average_value) private(i, tid, nthreads)
  {
    #pragma omp for schedule(dynamic)
    for (i = 0; i < 10; i++)
    {
      tid = omp_get_thread_num();
      if (!1)
        printf("Thread ID: %d\n", tid);

      if (tid == 0)
      {
        nthreads = omp_get_num_threads();
        if (!1)
          printf("Number of threads = %d\n", nthreads);

      }

      array_a[i] = rand() % 10;
      array_b[i] = rand() % 10;
      array_c[i] = (array_a[i] + array_b[i]) / 2;
      #pragma omp critical
      {
        if (array_c[i] < smallest_value)
        {
          smallest_value = array_c[i];
        }

        if (array_c[i] > largest_value)
        {
          largest_value = array_c[i];
        }

        average_value += array_c[i];
      }
    }

  }
  print_array(array_a, "Array A");
  print_array(array_b, "Array B");
  print_array(array_c, "Array C");
  average_value /= 10;
  printf("Smallest: %d, Largest: %d, Average: %d\n", smallest_value, largest_value, average_value);
  return 0;
}

