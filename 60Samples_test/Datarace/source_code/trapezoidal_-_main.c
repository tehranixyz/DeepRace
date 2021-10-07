void main()
{
  double integral;
  double local_integral[16 * 1] = {0.0};
  double a;
  double b;
  int n;
  int max_threads;
  double h;
  double x;
  int i;
  int nthreads;
  double start;
  double end;
  double compute_time;
  double PI16D = 3.141592653589793;
  int thread_id;
  double f(double x);
  printf("************** cs525 hw1 p1 *******************\n");
  max_threads = omp_get_max_threads();
  printf("Enter the number of threads (= 1 2 4 8 16)");
  scanf("%d", &nthreads);
  while (!(((((nthreads == 1) || (nthreads == 2)) || (nthreads == 4)) || (nthreads == 8)) || (nthreads == 16)))
  {
    printf("ERROR: invalid input\n");
    printf("Enter the number of threads (= 1 2 4 8 16)");
    scanf("%d", &nthreads);
  }

  omp_set_num_threads(nthreads);
  n = 100000000 + 1;
  a = 0.0;
  b = 1.0;
  h = (b - a) / n;
  integral = (f(a) + f(b)) / 2.0;
  x = a;
  start = omp_get_wtime();
  #pragma omp parallel for shared(h,a,n,local_integral)
  for (i = 1; i < n; i++)
  {
    x = a + (i * h);
    thread_id = omp_get_thread_num();
    local_integral[thread_id * 1] += f(x);
  }

  #pragma omp barrier
  for (i = 0; i < nthreads; i++)
    integral += local_integral[i * 1];

  integral = (integral * h) * 4.0;
  end = omp_get_wtime();
  compute_time = end - start;
  printf("With nthreads = %d threads, and n = %d intervals, the error in PI \n", nthreads, n);
  printf(" = %25.16e\n", PI16D - integral);
  printf("Time taken with MY OWN reduction operator is %15.2e\n", compute_time);
}

