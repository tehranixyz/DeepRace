int main()
{
  printf("Line 95 - FIRST of MAIN\n");
  long int i;
  long int j;
  int chunk;
  double dec_to_rad = (2. * 3.14159621234161928) / 360.;
  double deg_to_rad = (2. * 3.14159621234161928) / 360.;
  double logr_min = -1.0;
  double logr_max = 1.3011;
  double logrSQ_min = log10(pow(pow(10., logr_min), 2.));
  double logrSQ_max = log10(pow(pow(10., logr_max), 2.));
  long int errorcounts = 0;
  printf("line104\n");
  long int distance_counts[15] = {0};
  long int distance20_counts[15] = {0};
  long int distance20z_counts[15] = {0};
  long int randdistance_counts[15] = {0};
  double Xi_func[15] = {0.0};
  double Xi20_func[15] = {0.0};
  double Xi20z_func[15] = {0.0};
  printf("Line 118\n");
  int dist_index;
  int distSQ_index;
  long int FILELENGTH20r = 28162;
  long int FILELENGTH20z = 28383;
  long int FILELENGTH21r = 5495;
  long int FILELENGTHrand = 42654;
  static const char r21_datafile[] = "SDSS_Mr21_rspace.dat";
  FILE *myfile = fopen(r21_datafile, "r");
  if (myfile == 0)
  {
    printf("input_file.txt not opened, exiting...\n");
    exit(0);
  }

  printf("Opened file - Begining assignment.\n");
  long int N_data = FILELENGTH21r;
  double RA_LIST[N_data];
  double DEC_LIST[N_data];
  double Z_LIST[N_data];
  for (i = 0; i < N_data; i++)
  {
    fscanf(myfile, "%lf", &RA_LIST[i]);
    fscanf(myfile, "%lf", &DEC_LIST[i]);
    fscanf(myfile, "%lf", &Z_LIST[i]);
    if (i >= (N_data - 2))
    {
      printf("Close or exceeded N_data limit. RA: %lf \n", RA_LIST[i]);
    }

  }

  fclose(myfile);
  printf("Closing File.\n");
  printf("Beginning Nested Loops...\n");
  double D;
  double logD;
  double DSQ;
  double logDSQ;
  double r = 0;
  double DEC_rad = 0;
  double RA_rad = 0;
  double x1 = 0;
  double y1 = 0;
  double z1 = 0;
  double rj = 0;
  double DEC_radj = 0;
  double RA_radj = 0;
  double x2 = 0;
  double y2 = 0;
  double z2 = 0;
  chunk = 50;
  #pragma omp parallel shared( Z_LIST, DEC_LIST, RA_LIST, N_data, deg_to_rad ,chunk) private (DSQ, logDSQ, r, rj, DEC_rad, DEC_radj, RA_rad, RA_radj, x1, y1, z1, x2, y2, z2, distSQ_index, i, j )
  {
    omp_set_num_threads(32);
    long int sum_local_counts[15];
    memset(sum_local_counts, 0, 15 * (sizeof(sum_local_counts[0])));
    #pragma omp for
    for (i = 0; i < (N_data - 1); ++i)
    {
      r = 2998. * Z_LIST[i];
      DEC_rad = DEC_LIST[i] * deg_to_rad;
      RA_rad = RA_LIST[i] * deg_to_rad;
      x1 = (r * cos(DEC_rad)) * cos(RA_rad);
      y1 = (r * cos(DEC_rad)) * sin(RA_rad);
      z1 = r * sin(DEC_rad);
      for (j = 0; j < (N_data - 1); ++j)
      {
        if (j != i)
        {
          rj = 2998. * Z_LIST[j];
          DEC_radj = DEC_LIST[j] * deg_to_rad;
          RA_radj = RA_LIST[j] * deg_to_rad;
          x2 = (rj * cos(DEC_radj)) * cos(RA_radj);
          y2 = (rj * cos(DEC_radj)) * sin(RA_radj);
          z2 = rj * sin(DEC_radj);
          DSQ = (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))) + ((z1 - z2) * (z1 - z2));
          logDSQ = log10(DSQ);
          distSQ_index = (int) floor((logDSQ - logrSQ_min) * (15 / (logrSQ_max - logrSQ_min)));
          if ((distSQ_index >= 0) && (distSQ_index < 15))
          {
            if (distSQ_index >= 15)
              printf("YELLING!");

            sum_local_counts[distSQ_index] += 1;
          }

        }

      }

    }

    #pragma omp critical
    {
      for (i = 0; i < 15; ++i)
      {
        distance_counts[i] += sum_local_counts[i];
      }

    }
  }
  printf("\n*");
  printf("\n   *");
  printf("\n     *");
  printf("\n       *");
  printf("\n      *");
  printf("\n     *");
  printf("\n    *");
  printf("\n   *        *");
  printf("\n   *");
  printf("\n     *");
  printf("\n      *");
  printf("\n       **");
  printf("\n        * *");
  printf("\n        * * *");
  printf("\n       * * * *\n");
  printf("****************************\n");
  printf("FINISHED PRAGMA OMP CRITICAL\n");
  printf("****************************\n");
  printf("FINISHED Mr21 NESTED LOOP. \n");
  printf("Dividing Counts by two to correct double counting...");
  for (i = 0; i < 15; ++i)
  {
    distance_counts[i] = (long long) floor(distance_counts[i] / 2.);
    printf("%ld ", distance_counts[i]);
  }

  printf("Counts: ");
  printf("\n");
  static const char r20_datafile[] = "SDSS_Mr20_rspace.dat";
  FILE *my20file = fopen(r20_datafile, "r");
  if (my20file == 0)
  {
    printf("input_file.txt not opened, exiting...\n");
    exit(0);
  }

  printf("Opened file - Begining assignment.\n");
  long int N20_data = FILELENGTH20r;
  double RA20_LIST[N20_data];
  double DEC20_LIST[N20_data];
  double Z20_LIST[N20_data];
  for (i = 0; i < N20_data; i++)
  {
    fscanf(my20file, "%lf", &RA20_LIST[i]);
    fscanf(my20file, "%lf", &DEC20_LIST[i]);
    fscanf(my20file, "%lf", &Z20_LIST[i]);
    if (i >= (N20_data - 2))
    {
      printf("Close or exceeded N20_data limit. RA: %lf \n", RA20_LIST[i]);
    }

  }

  fclose(my20file);
  printf("Closing File.\n");
  printf("Beginning Nested Loops...\n");
  #pragma omp parallel shared( Z20_LIST, DEC20_LIST, RA20_LIST, N20_data, deg_to_rad ,chunk) private (DSQ, logDSQ, r, rj, DEC_rad, DEC_radj, RA_rad, RA_radj, x1, y1, z1, x2, y2, z2, distSQ_index, i, j )
  {
    omp_set_num_threads(32);
    long int sum_local_counts[15];
    memset(sum_local_counts, 0, 15 * (sizeof(sum_local_counts[0])));
    #pragma omp for
    for (i = 0; i < (N20_data - 1); ++i)
    {
      r = 2998. * Z20_LIST[i];
      DEC_rad = DEC20_LIST[i] * deg_to_rad;
      RA_rad = RA20_LIST[i] * deg_to_rad;
      x1 = (r * cos(DEC_rad)) * cos(RA_rad);
      y1 = (r * cos(DEC_rad)) * sin(RA_rad);
      z1 = r * sin(DEC_rad);
      for (j = 0; j < (N20_data - 1); ++j)
      {
        if (j != i)
        {
          rj = 2998. * Z20_LIST[j];
          DEC_radj = DEC20_LIST[j] * deg_to_rad;
          RA_radj = RA20_LIST[j] * deg_to_rad;
          x2 = (rj * cos(DEC_radj)) * cos(RA_radj);
          y2 = (rj * cos(DEC_radj)) * sin(RA_radj);
          z2 = rj * sin(DEC_radj);
          DSQ = (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))) + ((z1 - z2) * (z1 - z2));
          logDSQ = log10(DSQ);
          distSQ_index = (int) floor((logDSQ - logrSQ_min) * (15 / (logrSQ_max - logrSQ_min)));
          if ((distSQ_index >= 0) && (distSQ_index < 15))
          {
            if (distSQ_index >= 15)
              printf("YELLING!");

            sum_local_counts[distSQ_index] += 1;
          }

        }

      }

    }

    #pragma omp critical
    {
      for (i = 0; i < 15; ++i)
      {
        distance20_counts[i] += sum_local_counts[i];
      }

    }
  }
  printf("FINISHED Mr20 NESTED LOOP. \n");
  printf("Counts: ");
  for (i = 0; i < 15; ++i)
  {
    distance20_counts[i] = (long long) floor(distance20_counts[i] / 2.);
    printf("%ld ", distance20_counts[i]);
  }

  printf("\n");
  static const char r20z_datafile[] = "SDSS_Mr20_zspace.dat";
  FILE *my20zfile = fopen(r20z_datafile, "r");
  if (my20zfile == 0)
  {
    printf("input_file.txt not opened, exiting...\n");
    exit(0);
  }

  printf("Opened file - Begining assignment.\n");
  long int N20z_data = FILELENGTH20z;
  double RA20z_LIST[N20z_data];
  double DEC20z_LIST[N20z_data];
  double Z20z_LIST[N20z_data];
  for (i = 0; i < N20z_data; i++)
  {
    fscanf(my20zfile, "%lf", &RA20z_LIST[i]);
    fscanf(my20zfile, "%lf", &DEC20z_LIST[i]);
    fscanf(my20zfile, "%lf", &Z20z_LIST[i]);
    if (i >= (N20z_data - 2))
    {
      printf("Close or exceeded N20z_data limit. RA: %lf \n", RA20z_LIST[i]);
    }

  }

  fclose(my20zfile);
  printf("Closing File.\n");
  printf("Beginning Nested Loops...\n");
  #pragma omp parallel shared( Z20z_LIST, DEC20z_LIST, RA20z_LIST, N20z_data, deg_to_rad ,chunk) private (DSQ, logDSQ, r, rj, DEC_rad, DEC_radj, RA_rad, RA_radj, x1, y1, z1, x2, y2, z2, distSQ_index, i, j )
  {
    long int sum_local_counts[15];
    memset(sum_local_counts, 0, 15 * (sizeof(sum_local_counts[0])));
    #pragma omp for schedule(guided, chunk)
    for (i = 0; i < (N20z_data - 1); ++i)
    {
      r = 2998. * Z20z_LIST[i];
      DEC_rad = DEC20z_LIST[i] * deg_to_rad;
      RA_rad = RA20z_LIST[i] * deg_to_rad;
      x1 = (r * cos(DEC_rad)) * cos(RA_rad);
      y1 = (r * cos(DEC_rad)) * sin(RA_rad);
      z1 = r * sin(DEC_rad);
      for (j = 0; j < (N20z_data - 1); ++j)
      {
        if (j != i)
        {
          rj = 2998. * Z20z_LIST[j];
          DEC_radj = DEC20z_LIST[j] * deg_to_rad;
          RA_radj = RA20z_LIST[j] * deg_to_rad;
          x2 = (rj * cos(DEC_radj)) * cos(RA_radj);
          y2 = (rj * cos(DEC_radj)) * sin(RA_radj);
          z2 = rj * sin(DEC_radj);
          DSQ = (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))) + ((z1 - z2) * (z1 - z2));
          logDSQ = log10(DSQ);
          distSQ_index = (int) floor((logDSQ - logrSQ_min) * (15 / (logrSQ_max - logrSQ_min)));
          if ((distSQ_index >= 0) && (distSQ_index < 15))
          {
            if (distSQ_index >= 15)
              printf("YELLING!");

            sum_local_counts[distSQ_index] += 1;
          }

        }

      }

    }

    #pragma omp critical
    {
      for (i = 0; i < 15; ++i)
      {
        distance20z_counts[i] += sum_local_counts[i];
      }

    }
  }
  printf("FINISHED Mr20z NESTED LOOP. \n");
  printf("Counts: ");
  for (i = 0; i < 15; ++i)
  {
    distance20z_counts[i] = (long long) floor(distance20z_counts[i] / 2.);
    printf("%ld ", distance20z_counts[i]);
  }

  printf("\n");
  static const char random_datafile[] = "SDSS_random.dat";
  long int N_rand = FILELENGTHrand;
  FILE *myrandfile = fopen(random_datafile, "r");
  if (myrandfile == 0)
  {
    printf("input_file.txt not opened, exiting...\n");
    exit(0);
  }

  double randRA_LIST[N_rand];
  double randDEC_LIST[N_rand];
  double randZ_LIST[N_rand];
  for (i = 0; i < N_rand; ++i)
  {
    fscanf(myrandfile, "%lf", &randRA_LIST[i]);
    fscanf(myrandfile, "%lf", &randDEC_LIST[i]);
    fscanf(myrandfile, "%lf", &randZ_LIST[i]);
    if (i >= (N_rand - 2))
    {
      printf("Close or exceeded N_data limit. RA: %lf \n", randRA_LIST[i]);
    }

  }

  fclose(myrandfile);
  printf("Closing File.\n");
  printf("Beginning Random Nested Loops...\n");
  #pragma omp parallel shared( randZ_LIST, randDEC_LIST, randRA_LIST, N_rand, deg_to_rad ,chunk) private (DSQ, logDSQ, r, rj, DEC_rad, DEC_radj, RA_rad, RA_radj, x1, y1, z1, x2, y2, z2, distSQ_index, i, j )
  {
    long int sum_local_counts[15];
    memset(sum_local_counts, 0, 15 * (sizeof(sum_local_counts[0])));
    #pragma omp for schedule(guided, chunk)
    for (i = 0; i < (N_rand - 1); ++i)
    {
      r = 2998. * randZ_LIST[i];
      DEC_rad = randDEC_LIST[i] * deg_to_rad;
      RA_rad = randRA_LIST[i] * deg_to_rad;
      x1 = (r * cos(DEC_rad)) * cos(RA_rad);
      y1 = (r * cos(DEC_rad)) * sin(RA_rad);
      z1 = r * sin(DEC_rad);
      for (j = 0; j < (N_rand - 1); ++j)
      {
        if (j != i)
        {
          rj = 2998. * randZ_LIST[j];
          DEC_radj = randDEC_LIST[j] * deg_to_rad;
          RA_radj = randRA_LIST[j] * deg_to_rad;
          x2 = (rj * cos(DEC_radj)) * cos(RA_radj);
          y2 = (rj * cos(DEC_radj)) * sin(RA_radj);
          z2 = rj * sin(DEC_radj);
          DSQ = (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))) + ((z1 - z2) * (z1 - z2));
          logDSQ = log10(DSQ);
          distSQ_index = (int) floor((logDSQ - logrSQ_min) * (15 / (logrSQ_max - logrSQ_min)));
          if ((distSQ_index >= 0) && (distSQ_index < 15))
          {
            if (distSQ_index >= 15)
              printf("YELLING!");

            sum_local_counts[distSQ_index] += 1;
          }

        }

      }

    }

    #pragma omp critical
    {
      for (i = 0; i < 15; ++i)
      {
        randdistance_counts[i] += sum_local_counts[i];
      }

    }
  }
  printf("FINISHED RANDOM NESTED LOOPS! \n");
  printf("Counts: ");
  for (i = 0; i < 15; ++i)
  {
    randdistance_counts[i] = (long long) floor(randdistance_counts[i] / 2.);
    printf("%ld ", randdistance_counts[i]);
  }

  printf("\n");
  printf("Calculating Mr21 Correlation Function...\n");
  printf("Nrand: %ld\n", N_rand);
  printf("Ndata: %ld\n", N_data);
  double ratio = (double) (N_rand / ((double) N_data));
  for (i = 0; i < 15; i++)
  {
    Xi_func[i] = ((ratio * ratio) * (((double) distance_counts[i]) / ((double) randdistance_counts[i]))) - 1.0;
    printf("%.2lf ", Xi_func[i]);
  }

  printf("\n");
  printf("Calculating Mr20 Correlation Function...\n");
  printf("Nrand: %ld\n", N_rand);
  printf("N20data: %ld\n", N20_data);
  ratio = (double) (((double) N_rand) / ((double) N20_data));
  for (i = 0; i < 15; i++)
  {
    Xi20_func[i] = ((ratio * ratio) * (((double) distance20_counts[i]) / ((double) randdistance_counts[i]))) - 1.0;
    printf("%.2lf ", Xi20_func[i]);
  }

  printf("\n");
  printf("Calculating Mr20z Correlation Function...\n");
  ratio = (double) (N_rand / ((double) N20z_data));
  for (i = 0; i < 15; i++)
  {
    Xi20z_func[i] = ((ratio * ratio) * (((double) distance20z_counts[i]) / ((double) randdistance_counts[i]))) - 1.0;
    printf("%.2lf ", Xi20z_func[i]);
  }

  printf("\n");
  printf("Saving Mr21r counts to file.\n");
  FILE *fp_out;
  fp_out = fopen("output_Mr21counts.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%ld \n", distance_counts[i]);
  }

  fclose(fp_out);
  printf("Saving Mr20r counts to file.\n");
  fp_out = fopen("output_Mr20counts.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%ld \n", distance20_counts[i]);
  }

  fclose(fp_out);
  printf("Saving Mr20z counts to file.\n");
  fp_out = fopen("output_Mr20zcounts.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%ld \n", distance20z_counts[i]);
  }

  fclose(fp_out);
  printf("Saving Random counts to file.\n");
  fp_out = fopen("output_counts_random.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%ld \n", randdistance_counts[i]);
  }

  fclose(fp_out);
  printf("Saving Xi21 to file.\n");
  fp_out = fopen("output_Xi_21r.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%f \n", Xi_func[i]);
  }

  fclose(fp_out);
  printf("Saving Xi20 to file.\n");
  fp_out = fopen("output_Xi_20r.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%f \n", Xi20_func[i]);
  }

  fclose(fp_out);
  printf("Saving Xi20z to file.\n");
  fp_out = fopen("output_Xi_20z.txt", "w");
  if (fp_out == 0)
  {
    printf("output_file.txt not opened, exiting...\n");
    exit(0);
  }

  for (i = 0; i < 15; i++)
  {
    fprintf(fp_out, "%f \n", Xi20z_func[i]);
  }

  fclose(fp_out);
  return 0;
}

