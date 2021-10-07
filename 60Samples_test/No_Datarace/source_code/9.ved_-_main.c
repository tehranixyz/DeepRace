int main()
{
  int a;
  int n;
  int N;
  int sum = 0;
  int d1[10];
  int d[10];
  int i;
  int j;
  int nj;
  int nj1;
  int t1;
  int t2;
  int t3;
  int tsum = 0;
  int k;
  printf("enter the n digit number to be squared\n");
  scanf("%d", &N);
  a = N;
  for (i = 0; a; i++)
  {
    d[i] = a % 10;
    a = a / 10;
  }

  n = i;
  printf("The Number is %d", N);
  printf("\nTotal digits are %d\n", n);
  #pragma omp parallel num_threads(n) private(sum,nj,nj1,t1,t2,t3)
  {
    #pragma omp for
    for (j = 1; j <= n; j++)
    {
      int id = omp_get_thread_num();
      nj = n - j;
      nj1 = (n - j) + 1;
      t1 = N % ((int) pow(10, nj));
      t2 = N % ((int) pow(10, nj1));
      t3 = d[nj] * ((int) pow(10, nj));
      printf("Thread-%d printing N= %d\t n= %d\t j= %d\t nj= %d \t nj1= %d\t t1= %d\t t2= %d\t t3= %d\n", id, N, n, j, nj, nj1, t1, t2, t3);
      sum = t3 * (t1 + t2);
      printf("Summation thread-%d is  %d\n", id, sum);
      #pragma omp atomic
      tsum += sum;
    }

  }
  printf("the suqare of %d is %d\n", N, tsum);
  return 0;
}

