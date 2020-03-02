#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <xlocale.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1000
#define MAX_LINE 80


int main(int argc, char *argv[]){


  char *filename = NULL;
  FILE *iFile = stdin;
  int c;
  int threadCount;
  int processCount;
  char *outname;
  int outfile = STDOUT_FILENO;
  

  while ((c = getopt(argc, argv, "t:p:hvl:r:o:")) != -1)
  {
    switch (c)
    {
    case 't':
      threadCount = optarg;
      
      if (optarg == NULL)
      {
        threadCount == 1;
      }
      exit(2);
      break;
    case 'p':
      processCount = optarg;
      
      if (optarg == NULL)
      {
        processCount == 1;
      }

      break;
    case 'h':
      //cvalue = optarg;

      {
        printf("t: number of threads \n");
        printf("p: number of processes \n");
        printf("h: shows the help commands \n");
        printf("v: verbose mode \n");
        printf("l: name of left matrix \n");
        printf("r: name of right matrix \n");
        printf("o: name of file to use as the output \n");

      }
      break;

    case 'v':
      printf("v flag enabled \n");
      break;

    case 'l':
        break;

    case 'r':
        break;

    case 'o':
        break;        


    case '?':
      fprintf(stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
      return 1;
    default:
      exit(2);
    }/* Ç */
  }
  {
    char buff[BUFFER_SIZE] = {0};
    char *token = NULL;
    char delims[] = ",\n";

    fgets(buff, BUFFER_SIZE, iFile);
    while (fgets(buff, BUFFER_SIZE, iFile) != NULL)
    {
      memset(&s, 0, sizeof(s));size_t

      token = strtok(buff, delims);
      strcpy(s.id, token);

      token = strtok(NULL, delims);
      strcpy(s.fname, token);

      token = strtok(NULL, delims);
      strcpy(s.mname, token);

      token = strtok(NULL, delims);
      strcpy(s.lname, token);

      token = strtok(NULL, delims);
      strcpy(s.street, token);

      token = strtok(NULL, delims);
      strcpy(s.city, token);

      token = strtok(NULL, delims);
      strcpy(s.zip, token);

      token = strtok(NULL, delims);
      strcpy(s.country_code, token);

      token = strtok(NULL, delims);
      strcpy(s.email, token);

      token = strtok(NULL, delims);
      strcpy(s.phone, token);

      write(outfile, &s, sizeof(s));
    }
  }
  if (filename == NULL)
  {
    iFile = stdin;
  }
  else
  {
    iFile = fopen(filename, "r");
    if (iFile == NULL)
    {
      fprintf(stderr, "File not opened. Input valid filename!");
      exit(2);
    }
  }

  return 0;

}

