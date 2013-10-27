#ifndef definitions_h
#define definitions_h

typedef double (*function) (double *x, int n);

class info {
  public:
    info() : iters(0), fevals(0) {}
    ~info() {}
    int iters;
    int fevals;
};

#endif
