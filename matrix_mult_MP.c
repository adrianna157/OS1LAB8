#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <xlocale.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <libgen.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "matrix_mult_MP.h"
#define BUFFER_SIZE 1000
#define MAX_LINE 80
#define DEFAULT_THREAD_COUNT 1
#define DEFAULT_PROCESS_COUNT 1

matrix_t left = {NULL, 0, 0, NULL};
matrix_t right = {NULL, 0, 0, NULL};
matrix_t output = {NULL, 0, 0, NULL};

int threadCount = DEFAULT_THREAD_COUNT;
int processCount = DEFAULT_PROCESS_COUNT;

void readFile(matrix_t *mat);
void *oneDim(void *arg);
void goMommaThreads(void);

//Create Thread function
//Pass -t, split threads (look at dot matrix)

//Create Processing function

//shm_array.c this helps with multiprocesseing, shmopen, ftruncate, nmap
//does serial calculation

void goMommaThreads(void)
{
  pthread_t *wthreads = calloc(threadCount, sizeof(pthread_t));
  int tid;

  for (tid = 0; tid < threadCount; tid++)
  {
    pthread_create(&wthreads[tid], NULL, oneDim, (void*)(size_t)tid);
  }
  for (tid = 0; tid < threadCount; tid++)
  {
    pthread_join(wthreads[tid], NULL);
  }
  free(wthreads);
}

void *oneDim(void *arg)
{
  int i;
  int j;
  int k;
  long tid = (long)arg;
  

  for (i = tid; i < left.rows; i+=threadCount)
  {
    for (j = 0; j < left.cols; ++j)
    {
      for (k = 0; k < left.cols; ++k)
      {
        output.data[right.cols * i + j] += left.data[left.cols * i + k] * right.data[right.cols * k + j];
      }
    }
  }

  pthread_exit(EXIT_SUCCESS);


};

//Reading in a file
void readFile(matrix_t *mat)
{
  int i;
  int j;
  FILE *file = NULL;
  char *dot = strrchr(mat->file_name, '.');
  short inputFilesZipped = false;
  inputFilesZipped = strcmp(dot, ".gz") == 0;
  if (inputFilesZipped)
  {
    char cmd[200];
    sprintf(cmd, "gunzip -c %s", mat->file_name);
    file = popen(cmd, "r");
  }
  else
  {
    file = fopen(mat->file_name, "r");
  }
  fscanf(file, "%d %d", &mat->rows, &mat->cols);
  mat->data = malloc(mat->rows * mat->cols * sizeof(int32_t));
  for (i = 0; i < mat->rows; i++)
  {
    for (j = 0; j < mat->cols; j++)
    {
      fscanf(file, "%d ", &mat->data[(i * mat->cols) + j]);
    }
  }

  if (inputFilesZipped)
  {
    pclose(file);
  }
  else
  {
    pclose(file);
  }
}

int main(int argc, char *argv[])
{
  int c;

  while ((c = getopt(argc, argv, "t:p:hvl:r:o:")) != -1)
  {
    switch (c)
    {
    case 't':

      threadCount = atoi(optarg);

      break;
    case 'p':
      processCount = atoi(optarg);

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
      exit(2);
      break;

    case 'v':
      printf("v flag enabled \n");
      break;

    case 'l':
      left.file_name = optarg;

      break;

    case 'r':
      right.file_name = optarg;
      break;

    case 'o':
      output.file_name = optarg;
      break;

    case '?':
      fprintf(stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
      return 1;
    default:
      exit(2);
    }
  }

  //read file that is passed in the command line
  readFile(&left);
  readFile(&right);
  goMommaThreads();
  return 0;
}
