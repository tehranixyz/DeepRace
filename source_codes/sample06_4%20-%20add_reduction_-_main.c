static long num_steps = 500000000;
double step;
int main()
{
  int i;
  double x;
  double pi;
  double sum = 0.0;
  step = 1.0 / ((double) num_steps);
  #pragma omp parallel for reduction(+:sum)
  for (i = 1; i <= num_steps; i++)
  {
    x = (i - 0.5) * step;
    sum = sum + (4.0 / (1.0 + (x * x)));
  }

  pi = step * sum;
  printf("PI = %f\n", pi);
  return 0;
}

