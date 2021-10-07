int main()
{
  int x = 12345;
  int y = 11111;
  int z = 22222;
  #pragma omp parallel shared(y, z)
  {
    x = omp_get_thread_num();
    printf("Hello\n");
  }
  return 0;
}

