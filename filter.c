/*******************************************************************************
*
*  Filter a large array based on the values in a second array.
*
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <omp.h>
#include <math.h>
#include <assert.h>

/* Example filter sizes */
#define DATA_LEN  512*512*8
#define FILTER_LEN  512

/* Subtract the `struct timeval' values X and Y,
    storing the result in RESULT.
    Return 1 if the difference is negative, otherwise 0. */
int timeval_subtract (struct timeval * result, struct timeval * x, struct timeval * y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
    
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

/* Function to apply the filter with the filter list in the outside loop */
void serialFilterFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the filter */ 
  for (int y=0; y<filter_len; y++) { 
    /* for all elements in the data */
    for (int x=0; x<data_len; x++) {
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  
  printf ("Sff, %lu, %lu, %d\n", tresult.tv_sec, tresult.tv_usec, filter_len );

}

/* Optimized data first method to filter an array */
void optimizedDataFirst( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );
  /* for all elements in the data */
  //schedule(static, 512*512
  #pragma omp parallel for
  for ( int x=0; x<data_len; x++ ) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y+=16) { 
      /* it the data element matches the filter */ 
     //TODO
      if (input_array[x] == filter_list[y]) {
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+1]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+2]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+3]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+4]) {
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+5]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+6]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+7]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+8]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+9]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+10]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+11]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+12]) {
        output_array[x] = input_array[x];
      }

      if (input_array[x] == filter_list[y+13]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+14]) {
        output_array[x] = input_array[x];
      }
      if (input_array[x] == filter_list[y+15]) {
        output_array[x] = input_array[x];
      }

    }
  
  }

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("odf, %lu, %lu, %d\n", tresult.tv_sec, tresult.tv_usec, filter_len );

}



/* Function to apply the filter with the filter list in the outside loop */
void serialDataFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the data */
  for (int x=0; x<data_len; x++) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y++) { 
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("Sdf, %lu, %lu, %d\n", tresult.tv_sec, tresult.tv_usec, filter_len );

}

/* Function to apply the filter with the filter list in the outside loop */
void parallelFilterFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the filter */ 
  #pragma omp parallel for
  for (int y=0; y<filter_len; y++) { 
    /* for all elements in the data */
    for (int x=0; x<data_len; x++) {
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("pff, %lu, %lu, %d\n", tresult.tv_sec, tresult.tv_usec, filter_len );
}


/* Function to apply the filter with the filter list in the outside loop */
void parallelDataFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the data */
  #pragma omp parallel for
  for (int x=0; x<data_len; x++) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y++) { 
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );
  printf ("pdf, %lu, %lu, %d\n", tresult.tv_sec, tresult.tv_usec, filter_len );
}


void checkData ( unsigned int * serialarray, unsigned int * parallelarray, int data_mult )
{
  for (int i=0; i<DATA_LEN * data_mult; i++)
  {
    if (serialarray[i] != parallelarray[i])
    {
      printf("Data check failed offset %d\n", i );
      return;
    }
  }
}


int main( int argc, char** argv )
{
  int filter_min = atoi(argv[1]);
  int filter_max = atoi(argv[2]);
  int data_mult = atoi(argv[3]);
  int threads = atoi(argv[4]);
  omp_set_num_threads(threads);
  
  /* loop variables */
  int x,y;

  /* Create matrixes */
  unsigned int * input_array;
  unsigned int * serial_array;
  unsigned int * output_array;
  unsigned int * filter_list;

  /* Initialize the data. Values don't matter much. */
  posix_memalign ( (void**)&input_array, 4096, data_mult * DATA_LEN * sizeof(unsigned int));
//  input_array = (unsigned int*) posix_memalign ( DATA_LEN * sizeof(unsigned int), 4096);
  for (x=0; x<data_mult * DATA_LEN; x++)
  {
    input_array[x] = x % 2048;
  }

  /* start with an empty *all zeros* output array */
  posix_memalign ( (void**)&output_array, 4096, data_mult * DATA_LEN * sizeof(unsigned int));
  memset ( output_array, 0, DATA_LEN );
  posix_memalign ( (void**)&serial_array, 4096, data_mult * DATA_LEN * sizeof(unsigned int));
  memset ( serial_array, 0, data_mult * DATA_LEN );

  /* Initialize the filter. Values don't matter much. */
  filter_list = (unsigned int*) malloc ( filter_max * sizeof(unsigned int));
  for (y=0; y<filter_max; y++)
  {
    filter_list[y] = y;
  }

  /* Execute at a variety of filter lengths */
  for ( int filter_len = filter_min; filter_len<=filter_max; filter_len*=2) 
  {
 
  serialDataFirst ( DATA_LEN * data_mult, input_array, serial_array, filter_len, filter_list );
    memset ( output_array, 0, DATA_LEN * data_mult );

    serialFilterFirst ( DATA_LEN * data_mult, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array, data_mult );
    memset ( output_array, 0, DATA_LEN * data_mult);


    parallelFilterFirst ( DATA_LEN * data_mult, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array, data_mult );
    memset ( output_array, 0, DATA_LEN * data_mult);

    parallelDataFirst ( DATA_LEN * data_mult, input_array, output_array, filter_len, filter_list );
    checkData ( serial_array, output_array, data_mult );
    memset( output_array, 0, DATA_LEN * data_mult);

    if ( argc >= 6 && strcmp(argv[5], "o") == 0) { 
      optimizedDataFirst ( DATA_LEN * data_mult, input_array, output_array, filter_len, filter_list );
      checkData ( serial_array, output_array, data_mult );
      memset ( output_array, 0, DATA_LEN * data_mult );
    } 
  }
}

