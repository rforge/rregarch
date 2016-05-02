/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLOptim.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CGSLOPTIM_H_
#define _CGSLOPTIM_H_
#include "RegArchDef.h"
#include "cGSLVector.h"

typedef struct sParamOptimStruct
{	cRegArchParam*		mParam ;
	cRegArchValue*		mValue ;
}sParamOptimStruct, *pParamOptimPtr ;

#ifndef _GSL_
	double GslLLHFunction(int n, double *par, void *ex) ;
	void GslGradLLHFunction(int n, double *par, double *gr, void *ex);
#else
	double GslLLHFunction(const gsl_vector* theParam, void* theData) ;
	void GslGradLLHFunction(const gsl_vector* theParam, void* theData, gsl_vector* theGrad) ; 
	void GslLLHAndGradLLHFunction(const gsl_vector* theParam, void* theData, double* theLLH, gsl_vector* theGrad)  ;
#endif // _GSL_
#endif // _CGSLOPTIM_H_
