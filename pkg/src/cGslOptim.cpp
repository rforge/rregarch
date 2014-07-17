/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cGslOptim.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cRegArchParam.h"
#include "cRegArchValue.h"
#include "RegArchCompute.h"
#include "cGslOptim.h"

#ifndef _GSL_
double GslLLHFunction(int n, double *par, void *ex)
{
pParamOptimPtr myParamOptim = (pParamOptimPtr)ex ;
cRegArchParam* myParam = myParamOptim->mParam ;
cRegArchValue* myValue = myParamOptim->mValue ;

cDVector myTeta = cDVector(n, par) ;

	myParam->VectorToRegArchParam(myTeta) ;
	return -1.0*RegArchLLH(*myParam, *myValue) ;
}
#else
double GslLLHFunction(const gsl_vector* theParam, void* theData) 
{
pParamOptimPtr myParamOptim = (pParamOptimPtr)theData ;
cRegArchParam* myParam = myParamOptim->mParam ;
cRegArchValue* myValue = myParamOptim->mValue ;

cDVector myTeta(theParam) ;

	myParam->VectorToRegArchParam(myTeta) ;
	return -1.0*RegArchLLH(*myParam, *myValue) ;
}
#endif // _GSL_

#ifndef _GSL_
void GslGradLLHFunction(int n, double *par, double *gr, void *ex)
{
pParamOptimPtr myParamOptim = (pParamOptimPtr)ex ;
cRegArchParam* myParam = myParamOptim->mParam ;
cRegArchValue* myValue = myParamOptim->mValue ;

cDVector myTeta(n, par) ;
cDVector myGradLLH(n, gr) ;

	myParam->VectorToRegArchParam(myTeta) ;
	RegArchGradLLH(*myParam, *myValue, myGradLLH) ;
	for (register int i = 0 ; i < n ; i++)
		gr[i] = -myGradLLH[i] ;
}
#else
void GslGradLLHFunction(const gsl_vector* theParam, void* theData, gsl_vector* theGrad)
{
pParamOptimPtr myParamOptim = (pParamOptimPtr)theData ;
cRegArchParam* myParam = myParamOptim->mParam ;
cRegArchValue* myValue = myParamOptim->mValue ;

cDVector myTeta(theParam) ;
cDVector myGradLLH(theGrad) ;

	myParam->VectorToRegArchParam(myTeta) ;
	RegArchGradLLH(*myParam, *myValue, myGradLLH) ;
	for (register int i = 0 ; i < (int)theGrad->size ; i++)
		gsl_vector_set(theGrad, i, -myGradLLH[i]) ;
}

void GslLLHAndGradLLHFunction(const gsl_vector* theParam, void* theData, double* theLLH, gsl_vector* theGrad) 
{
pParamOptimPtr myParamOptim = (pParamOptimPtr)theData ;
cRegArchParam* myParam = myParamOptim->mParam ;
cRegArchValue* myValue = myParamOptim->mValue ;

cDVector myTeta(theParam) ;
cDVector myGradLLH(theGrad) ;

	myParam->VectorToRegArchParam(myTeta) ;
	RegArchLLHAndGradLLH(*myParam, *myValue, *theLLH, myGradLLH) ;
	for (register int i = 0 ; i < (int)theGrad->size ; i++)
		gsl_vector_set(theGrad, i, -myGradLLH[i]) ;
	*theLLH *= -1.0 ;
}
#endif // _GSL_