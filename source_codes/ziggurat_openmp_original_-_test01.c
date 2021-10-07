int main();
void test01();
void test02();
void test03();
void test04();
float r4_exp(uint32_t *jsr, uint32_t ke[256], float fe[256], float we[256]);
void r4_exp_setup(uint32_t ke[256], float fe[256], float we[256]);
float r4_nor(uint32_t *jsr, uint32_t kn[128], float fn[128], float wn[128]);
void r4_nor_setup(uint32_t kn[128], float fn[128], float wn[128]);
float r4_uni(uint32_t *jsr);
uint32_t shr3_seeded(uint32_t *jsr);
void timestamp();
void test01()
{
  uint32_t jsr;
  uint32_t jsr_value;
  double mega_rate_par;
  double mega_rate_seq;
  int r;
  int r_num = 1000;
  int *result_par;
  int *result_seq;
  int s;
  int s_num = 10000;
  uint32_t *seed;
  int thread;
  int thread_num;
  double wtime_par;
  double wtime_seq;
  printf("\n");
  printf("TEST01\n");
  printf("  SHR3_SEEDED computes random integers.\n");
  printf("  Since the output is completely determined\n");
  printf("  by the input value of SEED, we can run in\n");
  printf("  parallel as long as we make an array of seeds.\n");
  #pragma omp parallel
  {
    #pragma omp master
    {
      thread_num = omp_get_num_threads();
      printf("\n");
      printf("  The number of threads is %d\n", thread_num);
    }
  }
  seed = (uint32_t *) malloc(thread_num * (sizeof(uint32_t)));
  result_seq = (int *) malloc(thread_num * (sizeof(int)));
  result_par = (int *) malloc(thread_num * (sizeof(int)));
  jsr = 123456789;
  for (thread = 0; thread < thread_num; thread++)
  {
    seed[thread] = shr3_seeded(&jsr);
  }

  wtime_seq = omp_get_wtime();
  for (r = 0; r < r_num; r++)
  {
    thread = r % thread_num;
    jsr = seed[thread];
    for (s = 0; s < s_num; s++)
    {
      jsr_value = shr3_seeded(&jsr);
    }

    result_seq[thread] = jsr_value;
    seed[thread] = jsr;
  }

  wtime_seq = omp_get_wtime() - wtime_seq;
  mega_rate_seq = ((((double) r_num) * ((double) s_num)) / wtime_seq) / 1000000.0;
  jsr = 123456789;
  for (thread = 0; thread < thread_num; thread++)
  {
    seed[thread] = shr3_seeded(&jsr);
  }

  wtime_par = omp_get_wtime();
  #pragma omp parallel shared ( result_par, seed )
  {
    #pragma omp for schedule ( static, 1 )
    for (r = 0; r < r_num; r++)
    {
      thread = omp_get_thread_num();
      jsr = seed[thread];
      for (s = 0; s < s_num; s++)
      {
        jsr_value = shr3_seeded(&jsr);
      }

      result_par[thread] = jsr_value;
      seed[thread] = jsr;
    }

  }
  wtime_par = omp_get_wtime() - wtime_par;
  mega_rate_par = ((((double) r_num) * ((double) s_num)) / wtime_par) / 1000000.0;
  printf("\n");
  printf("  Correctness check:\n");
  printf("\n");
  printf("  Computing values sequentially should reach the\n");
  printf("  same result as doing it in parallel:\n");
  printf("\n");
  printf("    THREAD    Sequential      Parallel    Difference\n");
  printf("\n");
  for (thread = 0; thread < thread_num; thread++)
  {
    printf("  %8d  %12d  %12d  %12d\n", thread, result_seq[thread], result_par[thread], result_seq[thread] - result_par[thread]);
  }

  printf("\n");
  printf("  Efficiency check:\n");
  printf("\n");
  printf("  Computing values in parallel should be faster:\n");
  printf("\n");
  printf("              Sequential      Parallel\n");
  printf("\n");
  printf("      TIME:  %14f  %14f\n", wtime_seq, wtime_par);
  printf("      RATE:  %14f  %14f\n", mega_rate_seq, mega_rate_par);
  free(result_par);
  free(result_seq);
  free(seed);
  return;
}

