#ifndef nelder_mead_h
#define nelder_mead_h

typedef double (*function) (double *x, int n);

void nelder_mead (function f, double *x, int n);

class info {
  public:
    info() { };
  private:
    int iters;
    int fevals;
};

#endif
