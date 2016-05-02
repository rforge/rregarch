/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLSiman.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/01/17                                        
 ***                                                         
 **************************************************************/

#ifndef _CGSLSIMAN_H_
#define _CGSLSIMAN_H_
#ifdef _GSL_
#include "RegArchDef.h"
#include "RegArchCompute.h"
#include "cGSLOptim.h"
#include "cGSLUtils.h"
#include <gsl/gsl_siman.h>
#include <gsl/gsl_const_mksa.h>

class cGSLSiman
{
	private:
		cDVector mvCurrParams;
		gsl_siman_Efunc_t mvEfunc;
		gsl_siman_step_t mvStep;
		gsl_siman_metric_t mvMetric;
		gsl_siman_print_t mvPrint;
		gsl_siman_copy_t mvCopy;
		gsl_siman_copy_construct_t mvCopyConstruct;
		gsl_siman_destroy_t mvDestroy;
	public:
		cGSLSiman();
		cGSLSiman(cDVector &theX0);
		double static LLHEnergyFunction(void *theParamOptimPtr);
		void static StepFunction(const gsl_rng *theR, void *theParamOptimPtr, double theStepSize);
		double static Metric(void *theParamOptimPtr1, void *theParamOptimPtr2);
		void static Print(void *theParamOptimPtr);
		void static Copy(void *theSourceParamOptimPtr, void *theDestParamOptimPtr);
		void static *CopyConstruct(void *theParamOptimPtr);
		void static Destroy(void *theParamOptimPtr);
		void SetCurrParams(cDVector &theX0);
		void SetEfunc(gsl_siman_Efunc_t theEfunc);
		void SetStep(gsl_siman_step_t theStep);
		void SetMetric(gsl_siman_metric_t theMetric);
		void SetPrint(gsl_siman_print_t thePrint);
		void SetCopy(gsl_siman_copy_t theCopy);
		void SetCopyConstruct(gsl_siman_copy_construct_t theCopyConstruct);
		void SetDestroy(gsl_siman_destroy_t theDestroy);
		double SimanOptim(pParamOptimPtr theParamOptim, gsl_siman_params_t theParam, bool theVerbose = false);
		virtual ~cGSLSiman();
};
#endif // _GSL_
#endif //_CGSLSANN_H_