\name{residualsSet}
\alias{residualsSet}
\alias{condResidualsClass}
\alias{print.condResidualsClass}
\title{Set conditional residuals for the model}
\description{This function returns a condResidualsClass object describing the conditional residuals of the model.}
\synopsis{
    residualsSet(condResiduals, parameter=NULL)
}
\usage{
   residualsSet(condResiduals='NORMAL')
   residualsSet(condResiduals='STUDENT', parameter=0)
  \method{print}{condResidualsClass}(x, ...)
 }
\arguments{
   \item{condResiduals}{A string. Name of the conditional distribution of the model. In 'NORMAL', 'STUDENT'}
   \item{parameter}{A double. Parameter of the distribution. Default NULL}
   }
\value{ a condResidualsClass object:
    \item{distrType}{An integer (eNormal=1 for normal conditional residuals, eStudent=2 for Student conditional residuals.)}
    \item{nParam}{An integer. Number of poarameters of the conditional distribution.}
    \item{distrParameter}{A double or a vector. Value of the parameter(s) of the conditional distribution.}
    }
\examples{
# set Normal conditional distribution
    rr1 <- residualsSet('NORMAL')
# set Student with 10 dof conditional distribution
    rr2 <- residualsSet('STUDENT', 10)
    }    
