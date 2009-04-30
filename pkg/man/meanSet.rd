\name{meanSet}
\alias{meanSet}
\alias{condMeanClass}
\alias{print.condMeanClass}
\title{Set model conditional mean}
\description{This function returns a condMeanClass object describing the conditional mean of the model.}
\synopsis{
    \meanSet(...)
}

\usage{
    meanSet(CONST=0)
    meanSet(AR=c(0))
    meanSet(nAR=1)
    meanSet(MA=c(0))
    meanSet(STDINMEAN=0)
    meanSet(VARINMEAN=0)
    meanSet(LINREG=list(Beta=c(0), X=matrix(0,1,1)))
    meanSet(CONST=0, AR=c(0))
    \ldots
   \method{print}{condMeanClass}(x, ...)
}
\arguments{
   \item{AR}{A vector of autoregressive coefficients.}
   \item{nAR}{Number of AR lags.}
   \item{MA}{A vector of moving average coefficients.}
   \item{nMA}{Number of MA lags.}
   \item{CONST}{A double, value of the constant part of the conditional mean}
   \item{STDINMEAN}{A double, value of the standard deviation in mean coefficient}
   \item{VARINMEAN}{A double, value of the variance in mean coefficient}
   \item{LINREG}{a list with Beta : a vector of regression coefficients and X the matrix of independent variables.}
  
 }
\value{ a condMeanClass object which is the list of all parts of the conditional mean}



\examples{
    # AR2 model with constant
    mm1 <- meanSet(AR=c(0.1,0.2), CONST=2.0)
    
    # Var in mean model + MA(3) model 
    mm2 <- meanSet(VARINMEAN=1.0, nMA=3)
    
    # Linear regression model
    X <- matrix(seq(1,20), ncol=2)
    Beta <- c(1, 2)
    mm3 <- meanSet(LINREG=list(Beta=Beta, X=X))
 }
