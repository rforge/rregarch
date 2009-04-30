\name{RegArchFit}
\alias{RegArchFit}
\alias{RegArchFitClass}
\alias{print.RegArchFitClass}
\alias{summary.RegArchFitClass}
\alias{print.summary.RegArchFitClass}
\title{Fit the parameters of a general regression with ARCH type residuals}
\description{This function returns a RegArchFitClass object giving the estimators of the model.}

\usage{
    modelSet(Yt, model, initPoint=NULL, method=NULL, h=1e-3, control = list())
   \method{print}{RegArchFitClass}(x, ...)
   \method{summary}{RegArchFitClass}(object, ...)
   \method{print}{summary.RegArchFitClass}(x, ...)
}

\arguments{
   \item{Yt}{a vector of doubles: the time serie observations}
   \item{model}{a RegArchModelClass object describing the model. See \bold{modelSet}}
   \item{initPoint}{a RegArchModelClass object: initial point of the optim function.}
   \item{method}{optim function 'method' parameter. See \bold{optim}}
   \item{h}{a double: relative step used to compute the hessian matrix}
   \item{control}{optim 'control' parameter. See \bold{optim}}
}
   
   
\value{
    \item{param}{a RegArchModelClass of the fitted parameters.}
    \item{asymptCov}{the estimated asymptotic covariance matrix of the estimates}
    \item{LLH}{the log-likelihood value}
    \item{convergence}{optim 'convergence' value. See \bold{optim}}
}

  \seealso{
            \code{\link{optim}}
          }
       
\examples{
    mm1 <- meanSet(CONST=1)
    hh1 <- varSet(CONSTVAR=1)
    rr1 <- residualsSet('NORMAL')
    model1 <- modelSet(mm1, hh1, rr1)
    data(NormData)
    Res1<-RegArchFit(NormData, model=model1)
    summary(Res1)
    
    mm2 <- meanSet(nAR=2, CONST=2)
    hh2 <- varSet(nGARCH=c(1,1))
    rr2 <- residualsSet('STUDENT', 10)
    model2 <- modelSet(mm2, hh2, rr2)
    data(ARGARCHData)
    Res2<-RegArchFit(ARGARCHData, model=model2, control=list(maxit=5000))
    summary(Res2)
    
    
  } 
