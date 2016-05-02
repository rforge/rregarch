/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchOptim.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2015/12/05                                        
 ***                                                         
 **************************************************************/

#ifdef _RDLL_
#ifdef _GSL_
#include "RegArchOptim.h"

sRegArchOptimResult RegArchOptimize(cDVector& theInitPar, cRegArchParam& theParam, cRegArchValue& theValue, RegArchOptimParams& theOptimParams)
{
	cDVector myPar(theInitPar);
	sRegArchOptimResult myResult = {myPar, 0.0, 0};
	sParamOptimStruct myParOptim = {&theParam, &theValue};
	const char* myMethod = theOptimParams.GetMethod();
	if (!strcmp("SANN", myMethod))
	{
		cGSLSiman mySiman(myPar);
		myResult.mValue = mySiman.SimanOptim(&myParOptim, *theOptimParams.GetSimanParams(), theOptimParams.GetVerbose());
		myParOptim.mParam->RegArchParamToVector(myPar);
	}
	else if (!strcmp("Brent", myMethod)) throw cRegArchError("using Brent method to optimize a multi-parameter model");
	else
	{
		sGSLMultiMinResult myMultiMinResult;
		eGSLMultiMinAlgo myGSLMultiMinAlgo;
		if (!strcmp("Nelder-Mead", myMethod))
		{
			gsl_multimin_function myF = {&GslLLHFunction, myPar.GetSize(), &myParOptim};
			myGSLMultiMinAlgo = eSimplexNM;
			cGSLMultiMin myMultiMin(myPar, myGSLMultiMinAlgo, &myF, *theOptimParams.GetStepSize());
			myMultiMin.GSLOptim(myPar, myMultiMinResult, theOptimParams.GetStopValue(), theOptimParams.GetMaxIter(), theOptimParams.GetVerbose());
		} else
		{
			gsl_multimin_function_fdf myFdf = {&GslLLHFunction, &GslGradLLHFunction, &GslLLHAndGradLLHFunction, myPar.GetSize(), &myParOptim};		
			
			if (!strcmp("L-BFGS-B", myMethod)) myGSLMultiMinAlgo = eBFGSTwo;
			else if (!strcmp("CG", myMethod)) myGSLMultiMinAlgo = theOptimParams.GetConjugateGradientType();
			else if (!strcmp("BFGS", myMethod))
			{
				warning("the GSL does not have any implementation of the plain BFGS method. Using L-BFGS instead");
				myGSLMultiMinAlgo = eBFGSTwo;
			} else
				throw cRegArchError("unknown optimisation method");
			
			cGSLMultiMin myMultiMin(myPar, myGSLMultiMinAlgo, &myFdf, *theOptimParams.GetStepSize(), theOptimParams.GetTol());
			myMultiMin.GSLOptim(myPar, myMultiMinResult, theOptimParams.GetStopValue(), theOptimParams.GetMaxIter(), theOptimParams.GetVerbose());
		}
		myResult.mValue = myMultiMinResult.mFunctValue;
		myResult.mConvergence = DeriveConvergenceCode(myMultiMinResult.mConvergence, myMultiMinResult.mNIter >= theOptimParams.GetMaxIter(), myGSLMultiMinAlgo);
	}
	myResult.mPar = myPar;
	return myResult;
}

int DeriveConvergenceCode(bool theConvergence, bool theMaxIterReached, eGSLMultiMinAlgo theGSLMultiMinAlgo)
{	if (theConvergence)
		return 0;
	else if (theMaxIterReached)
		return 1;
	else
	{	switch (theGSLMultiMinAlgo)
		{	case eSimplexNM:
				return 10;
			case eBFGSTwo:
				return 52;
			default:
				return -1;
		}
	}
}

#endif //_GSL_
#endif //_RDLL_