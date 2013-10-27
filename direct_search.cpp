#include "direct_search.h"
#include <iostream>

void direct_search (function f, double *x, int n, Info & info) {
  double step_size = 1.0;
  double fx = (*f)(x,n);
  info.fevals++;

  while (step_size > 1e-12) {
    int mini = 0;
    double minf = fx;
    double fi;

    for (int i = 0; i < n; i++) {
      double oldxi = x[i];
      x[i] += step_size;
      fi = (*f)(x,n);
      info.fevals++;
      if (fi < minf) {
        minf = fi;
        mini = i+1;
      }
      x[i] = oldxi - step_size;
      fi = (*f)(x,n);
      info.fevals++;
      if (fi < minf) {
        minf = fi;
        mini = -(i+1);
      }
      x[i] = oldxi;
    }
    if (mini != 0) {
      if (mini > 0)
        x[mini-1] += step_size;
      else
        x[-mini-1] -= step_size;
      fx = minf;
    } else {
      step_size /= 2;
    }
  }
}
