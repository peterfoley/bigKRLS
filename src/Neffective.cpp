#define ARMA_NO_DEBUG

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo, BH, bigmemory)]]

using namespace Rcpp;
using namespace arma;

#include <bigmemory/BigMatrix.h>

// [[Rcpp::plugins(cpp11)]]

template <typename T>
double xBigNeffective(const Mat<T>& X) {
  
  Rprintf("Accumulating absolute pairwise correlations within X to correct p-values (recommended, especially for observational data).\n\n");
  
  int N = X.n_rows;
  int P = X.n_cols;
  
  std::vector<double> rowMeans(N);
  NumericMatrix Z(N, P); // Z will contain standardized rows
  double r = 0; // sum up correlation between X[i,] and X[j,]

  for(int i = 0; i < N; ++i){
    rowMeans[i] = sum(X.row(i))/P;
    if(i % 501 == 0){
      Rcpp::checkUserInterrupt();
      Rprintf("*");
    }
  }
  Rprintf("\n");
  
  double ss;
  
  for(int i = 0; i < N; ++i){
    
    for(int j = 0; j < P; ++j){
      Z(i, j) = X(i, j) - rowMeans[i]; // de-mean
    }
    
    ss = 0; // sum of squares for observation i
    for(int j = 0; j < P; ++j){
      ss += pow(Z(i,j), 2);
    }
    Z.row(i) = Z.row(i)/sqrt(ss);
    
    if(i % 501 == 0){
      Rcpp::checkUserInterrupt();
      Rprintf("*");
    }
  }
  Rprintf("\n");
  
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < i; ++j){
      r += abs(sum(Z.row(i) * Z.row(j)));
      // accumulate pairwise absolute correlations between obs
    }
    if(i % 501 == 0){
      Rcpp::checkUserInterrupt();
      Rprintf("*");
    }
  }
  Rprintf("\n");
  double MeanAbsPairwiseCor = 2*r/pow(N, 2);   
  // r reflects total of elements in lower triangle
  double Neffective = N*(1 - MeanAbsPairwiseCor) + 1; 
  return(Neffective);
}

// [[Rcpp::export]]
double BigNeffective(SEXP pX) {
  
  XPtr<BigMatrix> pXMat(pX);
  double Neff = xBigNeffective(
    arma::Mat<double>((double *)pXMat->matrix(), 
                      pXMat->nrow(), pXMat->ncol(), false)
  );
  return(Neff);
}
