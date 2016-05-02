/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchOptim.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2015/12/05                                        
 ***                                                         
 **************************************************************/

#ifndef _REGARCHOPTIM_H_
#define _REGARCHOPTIM_H_
#ifdef _RDLL_
#ifdef _GSL_
#include "cRegArchParam.h"
#include "cRegArchValue.h"
#include "RegArchOptimParams.h"
#include "cGSLMultiMin.h"
#include "cGSLOptim.h"
#include "cGSLSiman.h"
#include <string.h>

/*
* mPar			The best set of parameters found
* mValue		The value of the LLH corresponding to mPar
* mConvergence	An integer code. 0 indicates successful completion (which is always the case for "SANN" and "Brent"). 
*				Possible error codes are:
*					1	indicates that the iteration limit maxit had been reached.
*					10	indicates degeneracy of the Nelder–Mead simplex.
*					51	indicates a warning from the "L-BFGS-B" method; see component message for further details.
*					52	indicates an error from the "L-BFGS-B" method; see component message for further details.
*/
typedef struct sRegArchOptimResult
{
	cDVector mPar;
	double mValue;
	int mConvergence;
};

sRegArchOptimResult RegArchOptimize(cDVector& theInitPar, cRegArchParam& theParam, cRegArchValue& theValue, RegArchOptimParams& theOptimParams);
int DeriveConvergenceCode(bool theConvergence, bool theMaxIterReached, eGSLMultiMinAlgo theGSLMultiMinAlgo);

#endif //_GSL_
#endif //_RDLL_
#endif //_REGARCHOPTIM_H_