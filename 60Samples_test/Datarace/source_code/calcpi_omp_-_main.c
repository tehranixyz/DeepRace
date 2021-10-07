int main()
{
  int i;
  double mid;
  double height;
  double width;
  double sum = 0.0;
  double area;
  double t1;
  double t2;
  t1 = gettimeofday_sec();
  width = 1.0 / ((double) 100000000);
  #pragma omp parallel for reduction(+:sum)
  for (i = 0; i < 100000000; i++)
  {
    mid = (i + 0.5) * width;
    height = 4.0 / (1.0 + (mid * mid));
    sum += height;
  }

  area = width * sum;
  t2 = gettimeofday_sec();
  printf("pi=%1.20lf\n", area);
  printf("time=%lf [sec]\n", (double) (t2 - t1));
  return 0;
}

