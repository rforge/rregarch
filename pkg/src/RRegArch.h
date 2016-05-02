/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RRegArch.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2014/07/20                                        
 ***                                                         
 **************************************************************/

#include "cRUtils.h"
#include "RegArchDef.h"
#include "RegArchMeanInclude.h"
#include "RegArchVarInclude.h"
#include "RegArchResidualsInclude.h"
#include "cRegArchParam.h"
#include "cRegArchValue.h"
#include "RegArchCompute.h"
#include "cRegArchGradient.h"
#include "RegArchOptim.h"
#include "RegArchOptimParams.h"

#ifdef WIN32
	#define DECL_DLL_EXPORT __declspec(dllexport) 
#else
	#define DECL_DLL_EXPORT 
#endif // WIN32

#ifndef BEG_EXTERN_C
	#define BEG_EXTERN_C extern "C" {
	#define END_EXTERN_C }
#endif //BEG_EXTERN_C

#ifdef _RDLL_
	BEG_EXTERN_C
		DECL_DLL_EXPORT SEXP IsGSLAvailable();
		DECL_DLL_EXPORT SEXP RRegArchSimul(SEXP theNSimul, SEXP theModel);
		DECL_DLL_EXPORT SEXP RRegArchLLH(SEXP theNObs, SEXP theYt, SEXP theModel);
		DECL_DLL_EXPORT SEXP RRegArchGradLLH(SEXP theNObs, SEXP theYt, SEXP theModel);
		DECL_DLL_EXPORT SEXP RAsymptoticCovMat(SEXP theNObs, SEXP theYt, SEXP theModel, SEXP theh);
		DECL_DLL_EXPORT SEXP RRegArchFit(SEXP theInitPar, SEXP theNObs, SEXP theYt, SEXP theModel, SEXP theMethod, SEXP theLower, SEXP theUpper, SEXP theControl);
	END_EXTERN_C
#endif