/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RRegArchDynload.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2014/07/20                                        
 ***                                                         
 **************************************************************/

#include <R_ext/Rdynload.h>

#include "RRegArch.h"

#ifndef BEG_EXTERN_C
	#define BEG_EXTERN_C extern "C" {
	#define END_EXTERN_C }
#endif //BEG_EXTERN_C

#ifdef _RDLL_
//Register routines, allocate resources.
BEG_EXTERN_C void R_init_RRegArch(DllInfo *info)
{
	R_CallMethodDef callMethods[]  = {
		{"IsGSLAvailable", (DL_FUNC) &IsGSLAvailable, 0},
		{"RRegArchSimul", (DL_FUNC) &RRegArchSimul, 2},
		{"RRegArchLLH", (DL_FUNC) &RRegArchLLH, 3},
		{"RRegArchGradLLH", (DL_FUNC) &RRegArchGradLLH, 3},
		{"RAsymptoticCovMat", (DL_FUNC) &RAsymptoticCovMat, 4},
		{"RRegArchFit", (DL_FUNC) &RRegArchFit, 8},
		{NULL, NULL, 0}
	};
	R_registerRoutines(info, NULL, callMethods, NULL, NULL);
}
END_EXTERN_C

// Release resources.
BEG_EXTERN_C void R_unload_RRegArch(DllInfo *info)
{
}
END_EXTERN_C
#endif