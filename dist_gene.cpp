#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector fdg(NumericMatrix x) {

    int L = x.ncol();
    int n = x.nrow();
    long k = 0;

    NumericVector D(n * (n - 1) / 2);

    for (int i = 0; i < (n - 1); i++) {

        for (int j = (i + 1); j < n; j++) {

            LogicalVector y = x(i,_) != x(j,_);

            D[k] = sum(y);

            k++;
        }
    }

    D.attr("Size") = n;
    //D.attr("Labels") = clone(List(x.attr("dimnames")));
    D.attr("Diag") = false;
    D.attr("Upper") = false;
    D.attr("method") = "pairwise"; // temporary; todo add allow for percentage
    D.attr("class") = "dist";

    return D;
}
