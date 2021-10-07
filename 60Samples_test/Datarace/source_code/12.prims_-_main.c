void main()
{
  int i;
  int j;
  int TID;
  int nthreads;
  int n = 3;
  int cost[10][10];
  printf("\nEnter the costs of edges in matrix form :");
  #pragma omp parallel default(none),, shared(cost,n)
  {
    #pragma omp for
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
    {
      scanf("%d", &cost[i][j]);
    }


  }
  #pragma omp parallel default(none),, shared(nthreads,cost,n)
  {
    TID = omp_get_thread_num();
    if (TID == 0)
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads = (%d) \n", nthreads);
    }

    printf("Thread %d starting \n", TID);
    #pragma omp for
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        printf("%d\t", cost[i][j]);
      }

      printf("\n");
    }

  }
  int startVertex;
  int endVertex;
  int k;
  int nr[10];
  int temp;
  int minimumCost = 0;
  int tree[10][3];
  temp = cost[0][0];
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      if (temp > cost[i][j])
      {
        temp = cost[i][j];
        startVertex = i;
        endVertex = j;
      }

    }

  }

  tree[0][0] = startVertex;
  tree[0][1] = endVertex;
  tree[0][2] = temp;
  minimumCost = temp;
  for (i = 0; i < n; i++)
  {
    if (cost[i][startVertex] < cost[i][endVertex])
      nr[i] = startVertex;
    else
      nr[i] = endVertex;

  }

  nr[startVertex] = 100;
  nr[endVertex] = 100;
  temp = 99;
  for (i = 1; i < (n - 1); i++)
  {
    for (j = 0; j < n; j++)
    {
      if ((nr[j] != 100) && (cost[j][nr[j]] < temp))
      {
        temp = cost[j][nr[j]];
        k = j;
      }

    }

    tree[i][0] = k;
    tree[i][1] = nr[k];
    tree[i][2] = cost[k][nr[k]];
    minimumCost = minimumCost + cost[k][nr[k]];
    nr[k] = 100;
    for (j = 0; j < n; j++)
    {
      if ((nr[j] != 100) && (cost[j][nr[j]] > cost[j][k]))
        nr[j] = k;

    }

    temp = 99;
  }

  printf("\nThe min spanning tree is:- ");
  for (i = 0; i < (n - 1); i++)
  {
    for (j = 0; j < 3; j++)
      printf("%d", tree[i][j]);

    printf("\n");
  }

  printf("\nMin cost : %d", minimumCost);
}

