#include <iostream>
#include "nelder_mead.h"
#include <cmath>

using namespace std;

double fun (double *x, int n) {
  double f = 0.0;
  for (int i = 0; i < n; i++)
    f += 3.14*pow(x[i] - 0.7071, 2);

  return f;
}

int main () {
  int n = 4;
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
