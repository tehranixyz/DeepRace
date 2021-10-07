void testpoint(void);
struct d_complex
{
  double r;
  double i;
};
struct d_complex c;
int numoutside = 0;
int main()
{
  int i;
  int j;
  double area;
  double error;
  double eps = 1.0e-5;
  int num_threads;
  omp_set_dynamic(0);
  omp_set_num_threads(4);
  #pragma omp parallel default(none) shared(numoutside, num_threads) private(c,j) firstprivate(eps)
  #pragma omp master
  {
    num_threads = omp_get_num_threads();
  }
  #pragma omp for
  for (i = 0; i < 1000; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      c.r = ((-2.0) + ((2.5 * ((double) i)) / ((double) 1000))) + eps;
      c.i = ((1.125 * ((double) j)) / ((double) 1000)) + eps;
      struct d_complex z;
      int iter;
      double temp;
      z = c;
      for (iter = 0; iter < 1000; iter++)
      {
        temp = ((z.r * z.r) - (z.i * z.i)) + c.r;
        z.i = ((z.r * z.i) * 2) + c.i;
        z.r = temp;
        if (((z.r * z.r) + (z.i * z.i)) > 4.0)
        {
          #pragma omp atomic
          numoutside++;
          break;
        }

      }

    }

  }

  area = (((2.0 * 2.5) * 1.125) * ((double) ((1000 * 1000) - numoutside))) / ((double) (1000 * 1000));
  error = area / ((double) 1000);
  printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
  printf("Correct answer should be around 1.510659\n");
  printf("NUMBER of THREADS ALLOCATED: %d\n", num_threads);
}

