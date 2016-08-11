#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 64

void mmerge(int * x, int n, int * tmp);


/**
 * openmp implementation of mergesort
 */
void mmergesort (int * X, int n, int * tmp)
{
  if (n < 2) return;

  /* concurrently sort each half of list */
  #pragma omp task firstprivate(x, n, tmp)
  mmergesort(X, n/2, tmp);

  #pragma omp task firstprivate(X, n, tmp)
  mmergesort(X+(n/2), n-(n/2), tmp);

  /* wait for both threads to finish */
  #pragma omp taskwait

  /* merge sorted halves into sorted list */
  mmerge(X, n, tmp);
}


/**
 * main for openmp implementation of mergesort case study
 */
int main(int argc, char* argv[])
{
   int i, j, size;
   int nthreads = 2;
   int data[MAX_SIZE], tmp[MAX_SIZE];

   size = MAX_SIZE;

   if (argc > 1) {
      nthreads = (int) strtol(argv[1], (char **)NULL, 10);
   }
   omp_set_num_threads(nthreads);

   #pragma omp parallel
   {
      nthreads = omp_get_num_threads();
      if (omp_get_thread_num() == 0) {
         printf("\n");
         printf("Running %d openmp threads\n", nthreads);
      }
   }

   srand(10000);
   for (i = 0; i < size; i++) {
      int val = size * ((double) rand() / ((double) RAND_MAX + (double) 1));
      data[i] = val;
   }   

   printf("\n");
   printf("Unsorted data:\n  ");

   for (i = 0; i < size; i += 8) {
      for (j = 0; j < 8; j++) {
         printf("%3d ", data[i+j]);
      }
      printf("\n  ");
   }
   printf("\n");

   mmergesort(data, size, tmp);

   printf("Sorted data:\n  ");

   for (i = 0; i < size; i += 8) {
      for (j = 0; j < 8; j++) {
         printf("%3d ", data[i+j]);
      }
      printf("\n  ");
   }
   printf("\n");

   return 0;
}
