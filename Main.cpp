#include <iostream>
#include <cmath>
#include <time.h>
#include "myexp.hpp"
#include "Matrix.hpp"
# include "r8lib.h"
# include "r8mat_expm1.h"
using namespace std;

void  calc_results(double*,Matrix,int);

int main(){
    cout <<scientific;
    cout << "x\tseries(x)\texp(x)"<<endl;
    cout << -10<<"\t"<<myexp(-10) <<"\t"<<exp(-10) << endl;
    cout << 10<<"\t"<<myexp(10) <<"\t"<<exp(10) << endl;
    cout << 100<<"\t"<<myexp(100) <<"\t"<<exp(100) << endl;
    cout << 1000<<"\t"<<myexp(1000) <<"\t"<<exp(1000) << endl;
    
    srand (time(NULL));
    int dim = 2;
    Matrix imp_mat = Matrix(dim);
    
    imp_mat.setElem(.01,0,0);
    imp_mat.setElem(.02,1,0);
    imp_mat.setElem(.03,0,1);
    imp_mat.setElem(.04,1,1);
    double ref_mat[] = {.01, .02, .03, .04};
    int fact = 10;
    
    //Run the calculations a bunch of times for various norms of matrices
    for(int k = 1; k<5; k++){
        calc_results(ref_mat,imp_mat,dim);
        imp_mat*=10;
        for (int i = 0; i<dim*dim; i++)
        {
            ref_mat[i]*=fact;
        }
    }
    calc_results(ref_mat,imp_mat,dim);
    
    return 0;
}

void calc_results(double* ref_mat, Matrix imp_mat, int dim)
{
    cout << endl<<"Calculating exponential of the matrix"<< endl;
    imp_mat.printMatrix();
    double* ref_result;
    ref_result = r8mat_expm1(dim, ref_mat);
    cout<<"r8lib reference" << endl;
    for (int i = 0; i<dim; i++){
        for (int j = 0; j<dim; j++){
            cout << ref_result[i+j*dim]<<" ";
        }
        cout << endl;
    }
    cout<< "custom implementation" << endl;
    Matrix imp_result = imp_mat.Mexp();
    imp_result.printMatrix();
    cout<<"Relative difference"<< endl;
    double reldif;
    for (int i = 0; i<dim; i++){
        for (int j = 0; j<dim; j++){
            reldif = (ref_result[i+j*dim]-imp_result(i,j))/ref_result[i+j*dim];
            cout << reldif << " ";
        }
        cout << endl;
    }
}