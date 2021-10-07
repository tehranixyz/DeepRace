int main()
{
  printf("\n\n\n");
  int thread_num;
  #pragma omp parallel
  {
    thread_num = omp_get_thread_num();
    printf("Bonjour je suis le thread n° %d\n", thread_num);
    #pragma omp master
    {
      printf("Bonjour je suis le thread maitre avec le numero : %d\n", omp_get_thread_num());
    }
    ;
  }
  printf("\n\n\nThis is an example of using the directive Single\n");
  int a;
  int rang;
  #pragma omp parallel
  {
    rang = omp_get_thread_num();
    a = 1;
    #pragma omp single
    {
      a = 2;
      printf("je suis le premier thread (%d) arrivé  et j'ai modifié la variable a = %d\n", rang, a);
    }
    ;
    printf("je suis le thread %d, avec a = %d\n", rang, a);
  }
  printf("\n\nThis is an example of the directive single and the clause copyprivate() \n");
  #pragma omp parallel
  {
    rang = omp_get_thread_num();
    a = 1;
    #pragma single copyprivate()
    {
      a = 2;
    }
    printf("thread n°%d \t a = %d\n", rang, a);
  }
}

