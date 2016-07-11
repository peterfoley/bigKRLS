# bigKRLS
Kernel Regularized Least Squares (KRLS) is a kernel-based, complexity-penalized method developed by [Hainmueller and Hazlett (2013)](http://pan.oxfordjournals.org/content/22/2/143), and designed to minimize parametric assumptions while maintaining interpretive clarity. Here, we introduce *bigKRLS*, an updated version of the original [KRLS R package](https://cran.r-project.org/web/packages/KRLS/index.html) with algorithmic and implementation improvements designed to optimize speed and memory usage. These improvements allow users to straightforwardly fit KRLS models to medium and large datasets (N > ~2500). 

# Major Updates

1. C++ integration. We re-implement most major computations in the model in C++ via [Rcpp](https://cran.r-project.org/web/packages/Rcpp/index.html) and [RcppArmadillo](https://cran.r-project.org/web/packages/RcppArmadillo/index.html). These changes produce up to a 50% runtime decrease compared to the original R implementation.

2. Leaner algorithm. Because of the Tikhonov regularization and parameter tuning strategies used in KRLS, the model is inherently memory-heavy (O(N<sup>2</sup>)), making marginal memory savings important even in small- and medium-sized applications. We develop and implement a new local derivatives algorithm, which reduces peak memory usage by approximately an order of magnitude.

3. Improved memory management. Base R often hits limits or just performs poorly in memory-intensive applications. We use a series of packages in the [bigmemory](https://cran.r-project.org/web/packages/bigmemory/index.html) environment to ease constraints and handle larger datasets more smoothly.

# Installation
bigKRLS is under active development, and currently requires R version 3.3.0 or later. To install, use the standard devtools syntax:

```
install.packages("devtools")
library(devtools)
install_github('rdrr1990/bigKRLS')

library(bigKRLS)
```

Alternatively, users can employ one of two other strategies:
+ [RStudio](https://www.rstudio.com/) package builder. See [documentation](https://support.rstudio.com/hc/en-us/articles/200486088-Using-Rcpp-with-RStudio) for instructions on using Rcpp with RStudio. 
+ Build from source. Download the tar file included in the package, and use the following syntax:
```
install.packages('/path/to/bigKRLS_1.4.tar.gz', repos = NULL, type="source")
```
# Dependencies
bigKRLS requires Rcpp and RcppArmadillo, as well as a series of packages in the bigmemory environment. If you encounter difficulties with these packages, see [here](https://sites.google.com/site/petemohanty/software) for detailed installation notes.

# License 
Code released under GPL (>= 2).


