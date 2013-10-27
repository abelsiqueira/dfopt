#ifndef definitions_h
#define definitions_h

typedef double (*function) (double *x, int n);

class Info {
  public:
    Info() : fevals(0) {}
    ~Info() {}
    int fevals;
    double fx;
};

#endif
