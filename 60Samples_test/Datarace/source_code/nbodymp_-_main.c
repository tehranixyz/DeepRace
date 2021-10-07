{
  double rx;
  double ry;
  double vx;
  double vy;
  double fx;
  double fy;
  double masa;
} stParticula;
int main()
{
  int i;
  int j;
  stParticula particulas[1000];
  tomarTiempo();
  srand(time(0));
  for (i = 0; i < 1000; i++)
  {
    vfnGenerarParticula(&particulas[i]);
  }

  int iCntInteracciones = 0;
  while (iCntInteracciones < 2)
  {
    #pragma omp parallel for
    for (i = 0; i < 1000; i++)
    {
      vfnBorrarFuerzas(&particulas[i]);
      for (j = 0; j < 1000; j++)
      {
        if (i != j)
        {
          vfnCalcularFuerzas(&particulas[i], particulas[j]);
        }

      }

    }

    vfnCalcularMovimiento(particulas, 1e11);
    vfnImprimir(iCntInteracciones, particulas);
    iCntInteracciones++;
  }

  tomarTiempo();
  return 0;
}

