#include <iostream>
#include "nelder_mead.h"
#include <cmath>
extern "C" {
#include "cutest.h"
}

using namespace std;

double fun (double *x, int n) {
  double f;
  int status;

  CUTEST_ufn(&status, &n, x, &f);

  return f;
}

int MAINENTRY () {
  char fname[10] = "OUTSDIF.d";
  int nvar = 0, ncon = 0;
  int funit = 42, ierr = 0, fout = 6, io_buffer = 11, status;

  FORTRAN_open(&funit, fname, &ierr);
  CUTEST_cdimen(&status, &funit, &nvar, &ncon);
 
  double x[nvar], bl[nvar], bu[nvar];

  if (ncon > 0) {
    cerr << "Does not work for constrained problem" << endl;
    return 1;
  }

  CUTEST_usetup(&status, &funit, &fout, &io_buffer, &nvar, x, bl, bu);

  Info info;

  nelder_mead(&fun, x, nvar, info);

  doublereal calls[7], time[2];
  CUTEST_creport(&status, calls, time);
  std::cout << "Objective value = " << fun(x,nvar) << std::endl;
  std::cout << "Setup time: " << time[0] << std::endl
    << "Solve time: " << time[1] << std::endl;
  cout << "Number of Function Evaluations = " << info.fevals << endl;

  FORTRAN_close(&funit, &ierr);

  return 0;
}
