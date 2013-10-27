#ifndef direct_search_h
#define direct_search_h

typedef double (*function) (double *x, int n);

void direct_search (function f, double *x, int n);

#endif
