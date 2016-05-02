/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLSiman.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/01/17                                        
 ***                                                         
 **************************************************************/

#include "cGSLSiman.h"
#ifdef _GSL_

cGSLSiman::cGSLSiman()
{
	mvCurrParams.Delete();
	mvEfunc = cGSLSiman::LLHEnergyFunction;
	mvStep = cGSLSiman::StepFunction;
	mvMetric = cGSLSiman::Metric;
	mvPrint = cGSLSiman::Print;
	mvCopy = cGSLSiman::Copy;
	mvCopyConstruct = cGSLSiman::CopyConstruct;
	mvDestroy = cGSLSiman::Destroy;
}

cGSLSiman::cGSLSiman(cDVector &theX0)
{
	mvCurrParams.ReAlloc(theX0);
	mvEfunc = cGSLSiman::LLHEnergyFunction;
	mvStep = cGSLSiman::StepFunction;
	mvMetric = cGSLSiman::Metric;
	mvPrint = cGSLSiman::Print;
	mvCopy = cGSLSiman::Copy;
	mvCopyConstruct = cGSLSiman::CopyConstruct;
	mvDestroy = cGSLSiman::Destroy;
}

double cGSLSiman::LLHEnergyFunction(void *theParamOptimPtr)
{
	pParamOptimPtr myParamOptim = (pParamOptimPtr)theParamOptimPtr;
	cRegArchParam *myParam = myParamOptim->mParam;
	cRegArchValue *myValue = myParamOptim->mValue;

	return -1.0*RegArchLLH(*myParam, *myValue);
}

/*
 * We chose to update via an inhomogeneous Gaussian Markov kernel with independent
 * components, mean the previous vector and scale parameter proportional to theStepSize
 * for all components.
 */
void cGSLSiman::StepFunction(const gsl_rng *theR, void *theParamOptimPtr, double theStepSize)
{
	pParamOptimPtr myParamOptim = (pParamOptimPtr)theParamOptimPtr;
	int myNParam = myParamOptim->mParam->GetNParam();
	cGSLVector myOldParam(myNParam);
	myParamOptim->mParam->RegArchParamToVector(myOldParam);
	cGSLVector myNewParam(myNParam);
	
	gsl_vector* myTmpVect = gsl_vector_alloc(myNParam);
	gsl_matrix *myVar = gsl_matrix_alloc(myNParam, myNParam);
	gsl_matrix_set_identity(myVar);
	//3 std dev rule so that we have 99.7% probability that ||myNewParam - myOldParam|| < theStepSize
	gsl_matrix_scale(myVar, 1 / (9.0 * myNParam) * theStepSize * theStepSize);

	cGSLUtil myGSLUtil;
	do 
	{
		myGSLUtil.RandomMultivariateNorm(theR, myNParam, myOldParam.GetGSLVector(), myVar, myTmpVect);
		myNewParam.ReAlloc(myTmpVect);
	} while (Distance(myOldParam, myNewParam) > theStepSize);

	myParamOptim->mParam->VectorToRegArchParam(myNewParam);

	gsl_vector_free(myTmpVect);
	gsl_matrix_free(myVar);
}

double cGSLSiman::Metric(void *theParamOptimPtr1, void *theParamOptimPtr2)
{
	pParamOptimPtr myParamOptim1 = (pParamOptimPtr)theParamOptimPtr1;
	pParamOptimPtr myParamOptim2 = (pParamOptimPtr)theParamOptimPtr2;

	cDVector myParam1(myParamOptim1->mParam->GetNParam());
	cDVector myParam2(myParamOptim2->mParam->GetNParam());

	myParamOptim1->mParam->RegArchParamToVector(myParam1);
	myParamOptim2->mParam->RegArchParamToVector(myParam2);

	return Distance(myParam1, myParam2);
}

void cGSLSiman::Print(void *theParamOptimPtr)
{
	pParamOptimPtr myParamOptim = (pParamOptimPtr)theParamOptimPtr;

	myParamOptim->mParam->PrintParam();
	myParamOptim->mValue->PrintValue();
}

void cGSLSiman::Copy(void *theSourceParamOptimPtr, void *theDestParamOptimPtr)
{
	pParamOptimPtr mySourceParamOptim = (pParamOptimPtr)theSourceParamOptimPtr;
	pParamOptimPtr myDestParamOptim = (pParamOptimPtr)theDestParamOptimPtr;

	delete myDestParamOptim->mParam;
	delete myDestParamOptim->mValue;
	myDestParamOptim->mParam = new cRegArchParam(mySourceParamOptim->mParam);
	myDestParamOptim->mValue = new cRegArchValue(mySourceParamOptim->mValue);
}

void *cGSLSiman::CopyConstruct(void *theParamOptimPtr)
{
	pParamOptimPtr myParamOptim = (pParamOptimPtr)theParamOptimPtr;
	pParamOptimPtr myNewParamOptim = new sParamOptimStruct();
	myNewParamOptim->mParam = new cRegArchParam(myParamOptim->mParam);
	myNewParamOptim->mValue = new cRegArchValue(myParamOptim->mValue);
	return myNewParamOptim;
}

void cGSLSiman::Destroy(void *theParamOptimPtr)
{
	delete ((pParamOptimPtr)theParamOptimPtr)->mParam;
	delete ((pParamOptimPtr)theParamOptimPtr)->mValue;
	delete (pParamOptimPtr)theParamOptimPtr;
}

void cGSLSiman::SetCurrParams(cDVector &theX0)
{
	mvCurrParams = theX0;
}

void cGSLSiman::SetEfunc(gsl_siman_Efunc_t theEfunc)
{
	mvEfunc = theEfunc;
}

void cGSLSiman::SetStep(gsl_siman_step_t theStep)
{
	mvStep = theStep;
}

void cGSLSiman::SetMetric(gsl_siman_metric_t theMetric)
{
	mvMetric = theMetric;
}

void cGSLSiman::SetPrint(gsl_siman_print_t thePrint)
{
	mvPrint = thePrint;
}

void cGSLSiman::SetCopy(gsl_siman_copy_t theCopy)
{
	mvCopy = theCopy;
}

void cGSLSiman::SetCopyConstruct(gsl_siman_copy_construct_t theCopyConstruct)
{
	mvCopyConstruct = theCopyConstruct;
}

void cGSLSiman::SetDestroy(gsl_siman_destroy_t theDestroy)
{
	mvDestroy = theDestroy;
}

cGSLSiman::~cGSLSiman()
{
	mvCurrParams.Delete();
}

double cGSLSiman::SimanOptim(pParamOptimPtr theParamOptim, gsl_siman_params_t theParam, bool theVerbose)
{
	const gsl_rng_type * T;
	gsl_rng * r;

	gsl_rng_env_setup();

	T = gsl_rng_default;
	r = gsl_rng_alloc(T);

	gsl_siman_print_t myPrintFunct = theVerbose ? mvPrint : NULL;

	theParamOptim->mParam->VectorToRegArchParam(mvCurrParams);
	void *myParamOptimTmp = CopyConstruct(theParamOptim);
	gsl_siman_solve(r, myParamOptimTmp, mvEfunc, mvStep, mvMetric, myPrintFunct,
		mvCopy, mvCopyConstruct, mvDestroy, 0, theParam);

	((pParamOptimPtr)myParamOptimTmp)->mParam->RegArchParamToVector(mvCurrParams);
	theParamOptim->mParam->VectorToRegArchParam(mvCurrParams);

	gsl_rng_free (r);
	Destroy(myParamOptimTmp);

	return mvEfunc(theParamOptim);
}

#endif // _GSL_