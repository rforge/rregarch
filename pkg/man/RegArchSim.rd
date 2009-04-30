\name{RegArchSim}
\alias{RegArchSim}
\title{Simulation of the model }
\description{
  This function returns a simulation of the model.
}
\usage{
    RegArchSim(nSimul, model)
}
\arguments{
  \item{nSimul}{integer : number of observations generated }
  \item{model}{a RegArchModelClass object describing the model. See \bold{modelSet} }
}
\value{ A list with:
    \item{Yt}{The vector of objervations}
    \item{mt}{The vector of conditional means}
    \item{ht}{The vector of conditional variances}
    \item{ut}{The vector of conditional residuals}
    \item{Epst}{The vector of standardized conditional residuals}
}
\examples{
 # AR2 model with constant
    mm1 <- meanSet(AR=c(0.1,0.2), CONST=2.0)
 # GARCH(2,1) model 
    hh2 <- varSet(GARCH=list(ConstVar=.1, ARCH=c(.1, .2), GARCH=c(.6)))
 # set Student with 10 dof conditional distribution
    rr2 <- residualsSet('STUDENT', 10)
 #set AR2 - GARCH(2,1) model with Student residuals
    model1 <- modelSet(mm1, hh2, rr2)
 # Simulation of the model
    Value <- RegArchSim(nSimul=1000, model1)
}
