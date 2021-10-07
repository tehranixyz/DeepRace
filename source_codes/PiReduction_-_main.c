void main()
{
  int n;
  long i;
  long id;
  long ini;
  long fin;
  double x;
  double a;
  double z;
  double pi16ds = 3.1415926535897932;
  double sum = 0.0;
  printf("Introduce la precision del calculo (número de intervalos > 0): ");
  scanf("%d", &n);
  a = omp_get_wtime();
  double h = 1.0 / ((double) n);
  #pragma omp parallel num_threads(NH) reduction(+:sum)
  {
    id = omp_get_thread_num();
    ini = (id * n) / 6;
    fin = ((id + 1) * n) / 6;
    x = h * (0.5 + ini);
    for (i = ini; i < fin; i++)
    {
      sum += 4.0 / (1.0 + (x * x));
      x += h;
    }

  }
  double pi = sum * h;
  printf("\nEl valor aproximado de PI es %0.9f con un error de %0.9f\n", pi, fabs(pi - pi16ds));
  z = omp_get_wtime();
  printf("El programa ha tardado %0.9f segundos \n", z - a);
}

