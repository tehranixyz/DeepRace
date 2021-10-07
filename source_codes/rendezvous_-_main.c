struct printer
{
  int id;
  int ink;
};
printer pnt_main = {1, 5};
printer pnt_backup = {2, 5};
const char *humpty[] = {"Humpty Dumpty sat on a wall.", "Humpty Dumpty had a great fall.", "All the king's horses and all the king's men,", "Couldn't put Humpty together again."};
const char *goose[] = {"Old Mother Goose,", "When she wanted to wander,", "Would ride through the air,", "On a very fine gander.", "Jack's mother came in,", "And caught the goose soon,", "And mounting its back,", "Flew up to the moon."};
int main()
{
  int i;
  int j;
  int len;
  const char *msg;
  const char **text;
  omp_set_num_threads(2);
  #pragma omp parallel for
  for (i = 0; i < 2; i++)
  {
    text = (i) ? (goose) : (humpty);
    len = ((i) ? (sizeof(goose)) : (sizeof(humpty))) / (sizeof(const char *));
    for (j = 0; j < len; j++)
    {
      usleep(100000);
      if (print(text[j], &msg))
      {
        fprintf(stderr, "Error: %s\n", msg);
        break;
      }

    }

  }

  return 0;
}

