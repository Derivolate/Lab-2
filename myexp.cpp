#include <cmath>
#include <limits>
#include "myexp.hpp"

double myexp(double x, double tol = 1e-10){
    double T = 1;
    int n = 1;
    double err = 1;
    while(fabs(err)>tol){ 
        err = err*x/n;
        n=n+1;
        T=T+err;
        if (n>1000)
        {
            std::cout << "Returning after too many itterations"<<std::endl;
            return std::numeric_limits<double>::quiet_NaN();
        }
    }
    return T;
}