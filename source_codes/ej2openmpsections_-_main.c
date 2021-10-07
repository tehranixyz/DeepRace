int main()
{
  long long int tid;
  long long int i;
  long long int suma;
  suma = 0;
  double kuz;
  double zain;
  kuz = omp_get_wtime();
  double inicio;
  double fin;
  double A[100000];
  double B[100000];
  double S[100000];
  double P[100000];
  for (i = 0; i < 100000; ++i)
  {
    A[i] = i * 1.75;
    B[i] = i * 0.58;
  }

  omp_set_nested(1);
  #pragma omp parallel num_threads(2)
  {
    #pragma omp sections
    {
      #pragma omp section
      for (i = 0; i < 100000; ++i)
      {
        P[i] = A[i] * B[i];
      }

      #pragma omp section
      for (i = 0; i < 100000; ++i)
      {
        S[i] = A[i] + B[i];
      }

    }
  }
  zain = omp_get_wtime();
  printf("tarde %f\n", zain - kuz);
  return 0;
}

