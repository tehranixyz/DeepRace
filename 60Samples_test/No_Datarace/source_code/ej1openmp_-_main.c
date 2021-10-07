int main()
{
  long long int tid;
  long long int i;
  long long int suma;
  suma = 0;
  double kuz;
  double zain;
  kuz = omp_get_wtime();
  #pragma omp parallel private(tid)
  {
    #pragma omp for private(i) reduction(+:suma) schedule(guided,100000)
    for (i = 0; i < 10000000; ++i)
    {
      suma += i;
    }

  }
  zain = omp_get_wtime();
  printf("%lli y tarde %f\n", suma, zain - kuz);
  return 0;
}

