#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector localflowCpp(NumericVector x, std::size_t ni, std::size_t nw) {
  NumericVector out(ni);
  if (nw == 0) return out;            // nothing to do

  std::size_t start = 0;
  const std::size_t center_offset = (nw - 1) / 2; // window size is odd in focal

  for (std::size_t i = 0; i < ni; ++i) {
    std::size_t end = start + nw;

    double center = x[start + center_offset];
    int greater_count = 0;
    int smaller_count = 0;

    if (!NumericVector::is_na(center)) {
      for (std::size_t j = start; j < end; ++j) {
        double v = x[j];
        if (NumericVector::is_na(v)) continue;
        if (v > center)      ++greater_count;
        else if (v < center) ++smaller_count;
      }
    }
    // if center is NA, both counts stay 0 — same as R's na.rm=TRUE behavior
    out[i] = static_cast<double>(greater_count - smaller_count);
    start = end;
  }
  return out;
}
