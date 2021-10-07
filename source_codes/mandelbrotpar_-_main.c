struct d_complex
{
  double r;
  double i;
};
void testpoint(struct d_complex);
struct d_complex c;
int numoutside = 0;
int main()
{
  int i;
  int j;
  double area;
  double error;
  double eps = 1.0e-5;
  #pragma omp parallel for default(shared) firstprivate(eps)
  for (i = 0; i < 1000; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      c.r = ((-2.0) + ((2.5 * ((double) i)) / ((double) 1000))) + eps;
      c.i = ((1.125 * ((double) j)) / ((double) 1000)) + eps;
      testpoint(c);
    }

  }

  area = (((2.0 * 2.5) * 1.125) * ((double) ((1000 * 1000) - numoutside))) / ((double) (1000 * 1000));
  error = area / ((double) 1000);
  printf("%lf\n", area);
  printf("%lf\n", error);
  return 0;
}

