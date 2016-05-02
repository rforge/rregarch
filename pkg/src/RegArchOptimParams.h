/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchOptimParams.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/03/13                                        
 ***                                                         
 **************************************************************/

#ifndef _REGARCHOPTIMPARAMS_H_
#define _REGARCHOPTIMPARAMS_H_
#ifdef _RDLL_
#ifdef _GSL_
#include "cRUtils.h"
#include "cGSLMultiMin.h"
#include "cGSLSiman.h"

class RegArchOptimParams
{
private:
	char* mvMethod;
	double mvLower;
	double mvUpper;
	gsl_siman_params_t* mvSimanParams;
	double mvStopValue;
	int mvMaxIter;
	bool mvVerbose;
	cDVector* mvStepSize;
	double mvTol;
	eGSLMultiMinAlgo mvConjugateGradientType;

	void FetchParameters(uint theNElt, char** theNames, cDVector* theVal, uint theNRegArchParam);
public:
	RegArchOptimParams(SEXP theControl, uint theNRegArchParam, const char* theMethod, double theLower, double theUpper);
	virtual ~RegArchOptimParams();

	char* GetMethod() const;
	double GetLower() const;
	double GetUpper() const;
	gsl_siman_params_t* GetSimanParams() const;
	double GetStopValue() const;
	int GetMaxIter() const;
	bool GetVerbose() const;
	cDVector* GetStepSize() const;
	double GetTol() const;
	eGSLMultiMinAlgo GetConjugateGradientType() const;
};
#endif //_GSL_
#endif //_RDLL_
#endif //_REGARCHOPTIMPARAMS_H_