\name{ARGARCHData}
\docType{data}
\alias{ARGARCHData}
\title{A sample of 1000 AR-GARCH observations}
\description{A file of 1000 CONST + AR(2) - GARCH(1,1) with 19 d.o.f. Student conditional residuals successive observations}
\details{
    File 'ARGARCHData' contains the vector 'ARGARCHData'.\cr
    The model parameters are:\cr
    Conditional Mean Model:\cr
    -----------------------\cr
    AR[1] = 0.1\cr
    AR[2] = 0.2\cr
    Const = 2\cr

    Conditional Variance Model:\cr
    ---------------------------\cr
    ConstVar 0.1\cr
    ARCH[1]  0.1\cr
    ARCH[2]  0.2\cr
    GARCH[1] 0.6\cr

    Conditional Residuals Model:\cr
    ----------------------------\cr
   Student residuals with 10 d.o.f.
    
}

\usage{data(ARGARCHData)}
\format{RData file}

\keyword{datasets}
