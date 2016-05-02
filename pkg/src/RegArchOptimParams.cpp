/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchOptimParams.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/03/13                                        
 ***                                                         
 **************************************************************/

#include "RegArchOptimParams.h"

#ifdef _RDLL_
#ifdef _GSL_
RegArchOptimParams::RegArchOptimParams(SEXP theSEXP, uint theNRegArchParam, const char* theMethod, double theLower, double theUpper)
{	mvMethod = new char[strlen(theMethod)+1];
	strcpy(mvMethod, theMethod);
	mvLower = theLower;
	mvUpper = theUpper;

	cRUtil myRUtil;
	uint myParamNumber = length(theSEXP);
	char** myNames = new char*[myParamNumber];
	for (register uint i = 0; i < myParamNumber; i++)
		myNames[i] = new char[16]; // Should be enough to store any parameter name
	cDVector* myVal = new cDVector[myParamNumber];
	uint* mySizes = new uint[myParamNumber];
	myRUtil.GetListVectSizesSexp(theSEXP, 0, myParamNumber, mySizes);
	for (register uint i = 0; i < myParamNumber; i++)
		myVal[i] = cDVector(mySizes[i]);
	myRUtil.GetListNamedVectSexp(theSEXP, 0, myParamNumber, myNames, myVal);

	FetchParameters(myParamNumber, myNames, myVal, theNRegArchParam);

	for (register uint i = 0; i < myParamNumber; i++)
		delete[] myNames[i];
	delete[] myNames;
	delete[] myVal;
	delete[] mySizes;
}

RegArchOptimParams::~RegArchOptimParams()
{	delete[] mvMethod;
	delete mvSimanParams;
	delete mvStepSize;
}

char* RegArchOptimParams::GetMethod() const
{
	return mvMethod;
}
	
double RegArchOptimParams::GetLower() const
{
	return mvLower;
}

double RegArchOptimParams::GetUpper() const
{
	return mvUpper;
}

gsl_siman_params_t* RegArchOptimParams::GetSimanParams() const
{
	return mvSimanParams;
}

double RegArchOptimParams::GetStopValue() const
{
	return mvStopValue;
}

int RegArchOptimParams::GetMaxIter() const
{
	return mvMaxIter;
}

bool RegArchOptimParams::GetVerbose() const
{
	return mvVerbose;
}

cDVector* RegArchOptimParams::GetStepSize() const
{
	return mvStepSize;
}

double RegArchOptimParams::GetTol() const
{
	return mvTol;
}

eGSLMultiMinAlgo RegArchOptimParams::GetConjugateGradientType() const
{
	return mvConjugateGradientType;
}

void RegArchOptimParams::FetchParameters(uint theNElt, char** theNames, cDVector* theVal, uint theNRegArchParam)
{	//Setting the defaults
	if (!strcmp("Nelder-Mead", mvMethod))
		mvMaxIter = 500;
	else if (!strcmp("SANN", mvMethod))
		mvMaxIter = 10000;
	else
		mvMaxIter = 100;
	double myTemp = 10;
	double myTmin = 1e-4;
	mvSimanParams = new gsl_siman_params_t();
	mvSimanParams->n_tries = 0;
	mvSimanParams->iters_fixed_T = 10;
	mvSimanParams->k = GSL_CONST_MKSA_BOLTZMANN;
	mvSimanParams->t_min = myTmin;

	mvStopValue = 9.9999999999999e-007;
	mvVerbose = false;
	mvStepSize = new cDVector(theNRegArchParam, 1e-3);
	mvTol = 1e-8;
	mvConjugateGradientType = eConjugateFR;
	
	//Fetching from user's settings
	for (register uint i = 0; i < theNElt; i++)
	{	char* myName = theNames[i];
		cDVector myValue = theVal[i];
		if (!strcmp("trace", myName))
			mvVerbose = myValue[0] > 0;
		else if (!strcmp("ndeps", myName))
			mvStepSize->ReAlloc(myValue);
		else if (!strcmp("maxit", myName))
			mvMaxIter = myValue[0];
		else if (!strcmp("abstol", myName))
			mvStopValue = myValue[0];
		else if (!strcmp("reltol", myName))
			mvTol = myValue[0];
		else if (!strcmp("type", myName))
		{	switch ((int) myValue[0])
			{	case 1:
					mvConjugateGradientType = eConjugateFR;
					break;
				case 2:
					mvConjugateGradientType = eConjugatePR;
					break;
				case 3:
					warning("Beale-Sorenson update for conjugate gradient not available. Defaulting to Fletcher-Reeves");
					break;
				default:
					warning("unrecognized conjugate gradient update. Defaulting to Fletcher-Reeves");
			}
		}
		else if (!strcmp("factr", myName))
			mvTol = myValue[0];
		else if (!strcmp("pgtol", myName))
			mvStopValue = myValue[0];
		else if (!strcmp("temp", myName))
			myTemp = myValue[0];
		else if (!strcmp("tmax", myName))
			mvSimanParams->iters_fixed_T = myValue[0];
		else if (!strcmp("fnscale", myName) || !strcmp("parscale", myName) || !strcmp("alpha", myName) 
			|| !strcmp("beta", myName) || !strcmp("gamma", myName) || !strcmp("REPORT", myName) || !strcmp("lmm", myName))
			warning("parameter '%s' cannot be used with an embedded GSL", myName);
		else
			warning("unrecognized parameter '%s', ignoring", myName);
	}

	// Deriving the remaining parameters
	mvSimanParams->step_size = (myTemp + myTmin) / 2;
	mvSimanParams->t_initial = myTemp;
	mvSimanParams->mu_t = pow(myTemp / myTmin, 1.0/mvMaxIter) + DBL_EPSILON;
}
#endif //_GSL_
#endif //_RDLL_