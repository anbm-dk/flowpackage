#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// [[Rcpp::export]]
double chordAngleCpp(NumericVector x) {
  if (x.size() < 6) stop("Input vector must have at least 6 elements.");

  double x1 = x[0], x2 = x[1], x3 = x[2],
                                     x4 = x[3], x5 = x[4], x6 = x[5];

  if (NumericVector::is_na(x1) || NumericVector::is_na(x2) ||
      NumericVector::is_na(x3) || NumericVector::is_na(x4) ||
      NumericVector::is_na(x5) || NumericVector::is_na(x6)) {
    return NA_REAL;
  }

  double t1 = x1 * x3 - x4 * x6;
  double t2 = x2 * x3 - x5 * x6;
  double crd = std::sqrt(t1 * t1 + t2 * t2);

  double arg = crd / 2.0;
  if (arg > 1.0) arg = 1.0;
  if (arg < -1.0) arg = -1.0;

  return 2.0 * std::asin(arg);
}
