#include <iostream>
#include "nelder_mead.h"
#include <cmath>

using namespace std;

double fun (double *x, int) {
  return pow(x[0] - 1,2) + 100*pow(x[1]-x[0]*x[0],2);
}

int main () {
  int n = 2;
  double *x = new double[n];
  Info info;

  for (int i = 0; i < n; i++)
    x[i] = 0.0;

  cout << "f0 = " << fun(x,n) << endl;
  cout << "x0 = ";
  for (int i = 0; i < n; i++)
    cout << x[i] << ' ';
  cout << endl;

  nelder_mead(&fun, x, n, info);

  cout << "f = " << fun(x,n) << endl;
  cout << "x = ";
  for (int i = 0; i < n; i++)
    cout << x[i] << ' ';
  cout << endl;
  cout << "fevals = " << info.fevals << endl;

  return 0;
}
