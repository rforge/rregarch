\name{varSet}
\alias{varSet}
\alias{condVarClass}
\alias{print.condVarClass}
\title{Set conditional variance for general regression with ARCH type residuals}
\description{This function returns a condVarClass object describing the conditional variance of the model.}

\usage{
    varSet(CONSTVAR=0)
    varSet(nARCH=1)
    varSet(ARCH=list(ConstVar=0, ARCH=c(0)))
    varSet(nGARCH=c(1, 1))
    varSet(GARCH=list(ConstVar=0, ARCH=c(0), GARCH=c(0)))
    varSet(nTARCH=1)
    varSet(TARCH=list(TARCHPlus=c(0), TARCHMinus=c(0)))
    varSet(nEGARCH=c(1, 1))
    varSet(EGARCH=list(ConstVar=0, ARCH=c(0), GARCH=c(0), Teta=0, Gamma=0))
    varSet(nAPARCH=c(1, 1))
    varSet(APARCH=list(ConstVar=0, ARCH=c(0), Gamma=c(0), GARCH=c(0), Delta=2)
    \method{print}{condVarClass}(x, ...)
}
\arguments{
   \item{CONSTVAR}{A double: value of the constant variance for a constant variance model.}
   \item{ARCH}{A list with:\itemize{
        \item{ConstVar}{ the value of the constant of the ARCH(p) model.}
        \item{ARCH}{ a vector of ARCH coefficients.}
        }
   }
   \item{nARCH}{An integer: number of ARCH lags.}
   \item{GARCH}{A list with:\itemize{
        \item{ConstVar}{ the value of the constant of the GARCH(p, q) model.}
        \item{ARCH}{ a vector of ARCH coefficients.}
        \item{GARCH}{ a vector of GARCH coefficients.}
        }
   }
   \item{nGARCH}{a 2-dimensional vector with ARCH and GARCH lags.}
   \item{TARCH}{A list with:\itemize{
        \item{TARCHPlus}{ a vector of TARCH+ coefficients.}
        \item{TARCHMinus}{ a vector of TARCH- coefficients.}
        }
   }
   \item{nTARCH}{An integer: number of ARCH lags.}
   \item{EGARCH}{A list with:\itemize{
        \item{ConstVar}{ the value of the constant of the EGARCH(p, q) model.}
        \item{ARCH}{ a vector of ARCH coefficients.}
        \item{GARCH}{ a vector of GARCH coefficients.}
        \item{Teta}{ a double, value of Teta coefficient.}
        \item{Gamma}{ a double, value of Gamma coefficient.}
        }
   }
   \item{nEGARCH}{a 2-dimensional vector with ARCH and GARCH lags.}
   \item{APARCH}{A list with:\itemize{
        \item{ConstVar}{ the value of the constant of the EGARCH(p, q) model.}
        \item{ARCH}{ a vector of ARCH coefficients.}
        \item{Gamma}{ a vector of Gamma coefficients.}
        \item{GARCH}{ a vector of GARCH coefficients.}
        \item{Delta}{ a double, value of Delta coefficient.}
            }
    }
   \item{nAPARCH}{a 2-dimensional vector with ARCH and GARCH lags.}  
 }
\value{ a condVarClass object which describes the conditional variance model.
    \item{varType}{an integer \itemize{
        \item{eConstVar=1}{ Constant conditional variance model} 
        \item{eARCH=2}{ ARCH(p) model}
        \item{eGARCH=4}{ GARCH(p,q) model}
        \item{eEGARCH=8}{ EGARCH(p,q) model}
        \item{eAPARCH=16}{ APARCH(p,q) model}
        \item{eTARCH=32}{ TARCH(p) model}
            }
        }
    \item{nParam}{An integer. Number of parameters in the conditional variance model.}
    \item{ConstVar}{A double. Value of the constant part of the conditional variance (all models).}
    \item{nARCH}{An integer. Number of ARCH lags (all model except Constant conditional variance model).}
    \item{ARCH}{A vector. ARCH parameters (all model except Constant conditional variance and TARCH models).}
    \item{nGARCH}{An integer. Number of GARCH lags (all model except Constant conditional variance and TARCH models).}
    \item{GARCH}{A vector. GARCH parameters (all model except Constant conditional variance and TARCH models).}
    \item{ARCHPlus}{A vector. ARCH+ parameters for TARCH model.}
    \item{ARCHMinus}{A vector. ARCH- parameters for TARCH model.}
    \item{Teta}{A double. Teta parameter of EGARCH model.}
    \item{Gamma}{A double for EGARCH model, a vector for APARCH model. Gamma parameter for these models.}
    \item{Delta}{A double. Delta parameter for APARCH model.}
    }
 
 
\note{models
 Let \eqn{h(t)}{h(t)} the value of the conditional variance at date t. We have:\cr
    \eqn{h(t)=ConstVar}{h(t)=ConstVar} for constant conditional variance model.\cr
    \eqn{h(t)=ConstVar + \sum_{i=1}^{nARCH}{ARCH[i] u(t-i)}}{h(t)=ConstVar + \sum_{i=1}^{nARCH}{ARCH[i] u(t-i)}} for ARCH model.
}


\examples{
    # ARCH2 model
    hh1 <- varSet(ARCH=list(ARCH=c(0.1,0.8), ConstVar=0.1))
    
    # GARCH(2,1) model 
    hh2 <- varSet(nGARCH=c(2,1))
    
    # APARCH model
    hh3 <- varSet(APARCH=list(.1, ARCH=.1, Gamma=.2, GARCH=.2, Delta=1.8))
    
   }
