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


typedef struct matrix_s {
         char *file_name;
         int32_t rows;
         int32_t cols;
         int32_t *data;
} matrix_t;