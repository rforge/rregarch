\name{modelSet}
\alias{modelSet}
\alias{RegArchModelClass}
\alias{print.RegArchModelClass}
\title{Set model for general regression with ARCH type residuals}
\description{This function returns a RegArchModelClass object describing the model.}
\usage{
    modelSet(condMean, condVar, condRes)
   \method{print}{RegArchModelClass}(x, ...)
}

\arguments{
   \item{condMean}{a CondMeanClass object describing the conditional mean of the model. See \bold{meanSet}}
   \item{condVar}{a CondVarClass object describing the conditional variance of the model. See \bold{varSet}}
   \item{condRes}{a CondResidualsClass object describing the conditional resididuals of the model. See \bold{residualsSet}}
}

\usage{
}   
\examples{
 # AR2 model with constant
    mm1 <- meanSet(AR=c(0.1,0.2), CONST=2.0)
    # GARCH(2,1) model 
    hh2 <- varSet(nGARCH=c(2,1))
  # set Student with 10 dof conditional distribution
    rr2 <- residualsSet('STUDENT', 10)
  #set AR2 - GARCH(2,1) model with Student residuals
    model1 <- modelSet(mm1, hh2, rr2)
  } 
