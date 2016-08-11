#include <string.h>

void mmerge(int * X, int n, int * tmp) {
  int i = 0;
  int j = n/2;
  int ti = 0;

  while (i<n/2 && j<n) {
    if (X[i] < X[j]) {
      tmp[ti] = X[i];
      ti++; i++;
    } else {
      tmp[ti] = X[j];
      ti++; j++;
    }
  }
  while (i<n/2) { /* finish up lower half */
    tmp[ti] = X[i];
    ti++; i++;
  }
  while (j<n) {   /* finish up upper half */
    tmp[ti] = X[j];
    ti++; j++;
  }

  memcpy(X, tmp, n*sizeof(int));
}
