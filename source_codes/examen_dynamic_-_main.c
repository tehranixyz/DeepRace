int main()
{
  int iam = 0;
  int np = 1;
  int i = 0;
  double start = omp_get_wtime();
  #pragma omp parallel private(iam,np,i)
  {
    printf("Hello from thread %d out of %d \n", iam, np);
    #pragma omp for schedule(dynamic)
    for (i = 0; i < (np * 2); i++)
    {
      printf("Thread %d,contador %d\n", iam, i);
    }

  }
  double end = omp_get_wtime();
  printf("start time = %f\n", start);
  printf("end time = %f\n", end);
  printf("diff time = %f\n", end - start);
}

