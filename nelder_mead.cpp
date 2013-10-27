#include "nelder_mead.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <list>

void print (std::list<double*>& X, std::list<double>& F, int n) {
  std::list<double*>::const_iterator iter_x, iter_xend = X.end();
  std::list<double>::const_iterator iter_f, iter_fend = F.end();

  for (iter_x = X.begin(), iter_f = F.begin(); 
      iter_x != iter_xend; iter_x++, iter_f++) {
    std::cout << "x = ";
    for (int i = 0; i < n; i++) {
      std::cout << std::setw(6) << std::setiosflags(std::ios::fixed) <<
        std::setprecision(4) << (*iter_x)[i] << ' ';
    }
    std::cout << "    f = " << std::setw(6) << std::setprecision(4) 
      << *iter_f << std::endl;
  }
}

void sort (std::list<double*>& X, std::list<double>& F) {
  std::list<double*>::iterator iter_xhead, iter_x, iter_xend;
  std::list<double>::iterator iter_fhead, iter_f, iter_fend;

  iter_xhead = X.begin();
  iter_xend  = X.end();
  iter_fhead = F.begin();
  iter_fend  = F.end();

  while (iter_xhead != iter_xend) {
    std::list<double*>::iterator iter_xmax = iter_xhead;
    std::list<double>::iterator iter_fmax = iter_fhead;
    iter_x = iter_xhead; 
    iter_f = iter_fhead;
    for (iter_x++, iter_f++; 
        iter_x != iter_xend; 
        iter_x++, iter_f++) {
      if (*iter_f < *iter_fmax) {
        iter_xmax = iter_x;
        iter_fmax = iter_f;
      }
    }
    if (iter_xmax != iter_xhead) {
      double *tmpx = *iter_xhead;
      *iter_xhead = *iter_xmax;
      *iter_xmax = tmpx;
      double tmpf = *iter_fhead;
      *iter_fhead = *iter_fmax;
      *iter_fmax = tmpf;
    }
    iter_xhead++;
    iter_fhead++;
  }

}

void shrink (std::list<double*>& X, std::list<double>& F, function f, int n, Info & info) {
  std::list<double*>::iterator iter_x = X.begin(), iter_xend = X.end();
  std::list<double>::iterator iter_f = F.begin(), iter_fend = F.end();
  double *x0 = *iter_x;
  iter_x++;
  iter_f++;

  while (iter_x != iter_xend) {
    for (int i = 0; i < n; i++) {
      (*iter_x)[i] = ( (*iter_x)[i] + x0[i] )/2;
    }
    *iter_f = (*f)(*iter_x,n);
    info.fevals++;
    iter_x++;
    iter_f++;
  }
}

double dist (double *x, double *y, int n) {
  double d = 0.0;
  for (int i = 0; i < n; i++) {
    double tmp = fabs(x[i] - y[i]);
    if (tmp > d)
      d = tmp;
  }
  return d;
}

double calc_diameter (std::list<double*>& X, int n) {
  double diameter = 0;
  double *x;

  std::list<double*>::const_iterator iter = X.begin(), iter_end = X.end();
  x = *iter;
  for (iter++; iter != iter_end; iter++) {
    double tmp = dist(x, *iter, n);
    if (tmp > diameter)
      diameter = tmp;
  }

  return diameter;
}

void nelder_mead (function f, double *x, int n, Info & info) {
  std::list < double * > X;
  std::list < double > F;

  double diameter = 1;

  X.push_back(new double[n]);
  for (int i = 0; i < n; i++)
    X.front()[i] = x[i];
  F.push_back((*f)(x,n));
  info.fevals++;
  for (int i = 0; i < n; i++) {
    double *y = new double[n];
    X.push_back(y);
    for (int j = 0; j < n; j++)
      y[j] = x[j];
    y[i] += diameter;
    F.push_back((*f)(y,n));
    info.fevals++;
  }

  std::list<double*>::const_iterator iter_x, iter_xend = X.end();
  std::list<double>::const_iterator iter_f, iter_fend = F.end();

  sort(X,F);
  diameter = calc_diameter(X, n);

  while (diameter > 1e-12) {
    std::list<double*>::const_iterator iter_x = X.begin(), iter_end = X.end();
    double *xm = new double[n];

    for (int i = 0; i < n; i++) xm[i] = 0;

    iter_x = X.begin();
    iter_end--;
    while (iter_x != iter_end) {
      for (int i = 0; i < n; i++)
        xm[i] += (*iter_x)[i];
      iter_x++;
    }
    for (int i = 0; i < n; i++)
      xm[i] /= n;


    double *xnew = *iter_end;
    double *v = new double[n];
    for (int i = 0; i < n; i++)
      v[i] = xm[i] - xnew[i];

    std::list<double>::const_iterator iter_f = F.begin();
    double fb = *iter_f;
    iter_f = F.end();
    iter_f--;
    double fw = *iter_f;
    iter_f--;
    double fs = *iter_f;
    double fnew;

    // Reflection
    for (int i = 0; i < n; i++)
      xnew[i] = xm[i] + v[i];
    fnew = (*f)(xnew,n);
    info.fevals++;
    if (fb <= fnew && fnew < fs) {
      F.back() = fnew;
    } else if (fnew < fb) {
      // Expansion
      for (int i = 0; i < n; i++)
        xnew[i] += v[i];
      double fe = (*f)(xnew,n);
      info.fevals++;
      if (fnew < fe) {
        for (int i = 0; i < n; i++)
          xnew[i] -= v[i];
      } else {
        fnew = fe;
      }
      F.back() = fnew;
    } else {
      // Contraction
      for (int i = 0; i < n; i++)
        xnew[i] = xm[i] - 0.5*v[i];
      fnew = (*f)(xnew,n);
      info.fevals++;
      if (fnew < fw) {
        F.back() = fnew;
      } else {
        shrink(X,F,f,n,info);
      }
    }

    sort(X,F);
    diameter = calc_diameter(X,n);

    delete []xm;
    delete []v;
  }

  for (int i = 0; i < n; i++) {
    x[i] = X.front()[i];
  }
  info.fx = F.front();
  while (X.begin() != X.end()) {
    delete [] (X.front());
    X.pop_front();
  }
}
