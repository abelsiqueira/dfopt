#include <iostream>
#include "direct_search.h"
#include <cmath>
extern "C" {
#include "cuter.h"
}

using namespace std;

double fun (double *x, int n) {
  double f;

  UFN(&n, x, &f);

  return f;
}

int MAINENTRY () {
  char fname[10] = "OUTSDIF.d";
  int nvar = 0, ncon = 0;
  int funit = 42, ierr = 0, fout = 6;

  FORTRAN_OPEN(&funit, fname, &ierr);
  CDIMEN(&funit, &nvar, &ncon);

  double x[nvar], bl[nvar], bu[nvar];

  if (ncon > 0) {
    cerr << "Does not work for constrained problem" << endl;
    return 1;
  }

  USETUP(&funit, &fout, &nvar, x, bl, bu, &nvar);

  Info info;

  direct_search(&fun, x, nvar, info);

  real calls[7], time[2];
  CREPRT(calls, time);
  std::cout << "Objective value = " << fun(x,nvar) << std::endl;
  std::cout << "Setup time: " << time[0] << std::endl
    << "Solve time: " << time[1] << std::endl;
  cout << "Number of Function Evaluations = " << info.fevals << endl;

  FORTRAN_CLOSE(&funit, &ierr);

  return 0;
}
