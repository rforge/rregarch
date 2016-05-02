/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchCompute.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _REGARCHCOMPUTE_H_
#define _REGARCHCOMPUTE_H_
#include "cRegArchParam.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/** Simulation of a model defined by theParam */
void RegArchSimul(uint theNSample, cRegArchParam& theParam, cDVector& theYt) ;
/** Simulation of a model defined by theParam */
void RegArchSimul(uint theNSample, cRegArchParam& theParam, cRegArchValue& theValue) ;
/** Log-likelihood computation */
double RegArchLLH(cRegArchParam& theParam, cDVector* theYt, cDMatrix* theXt=NULL) ;
/** Log-likelihood computation */
double RegArchLLH(cRegArchParam& theParam, cRegArchValue& theValue) ;
/** Gradient of the Log-likelihood with respect to parameters */
void RegArchGradLLH(cRegArchParam& theParam, cRegArchValue &theValue, cDVector& theGradLLH) ;
/** Log-likelihood and its gradient */
void RegArchLLHAndGradLLH(cRegArchParam& theParam, cRegArchValue &theValue, double& theLLH, cDVector& theGradLLH) ;
/** Numeric approximation of Log-likelihoodnd gradient */
void NumericRegArchGradLLH(cRegArchParam& theParam, cRegArchValue& theValue, cDVector& theGradLLH, double theh = 1e-3) ;
/** Numeric approximation of Log-likelihoodnd Hessian matrix */
void NumericRegArchHessLLH(cRegArchParam& theParam, cRegArchValue& theValue, cDMatrix& theHessLLH, double theh = 1e-3) ;
/** Asymptotic covariance matrix */
void AsymptoticCovMat(cRegArchParam& theParam, cRegArchValue& theValue, cDMatrix& theAsymptoticCov, double theh = 1e-3) ;
#endif //_REGARCHCOMPUTE_H_
