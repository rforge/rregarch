/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLMultiMin.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CGSLMULTIMIN_H_
#define _CGSLMULTIMIN_H_
#ifdef _GSL_
#include "RegArchDef.h"
#include "cGSLVector.h"
#include "cRegArchStream.h"
#include <gsl/gsl_multimin.h>

typedef enum eGSLMultiMinAlgo
{	eConjugateFR=1, ///< Fletcher-Reeves conjugate gradient algorithm
	eConjugatePR=2, ///< Polak-Ribiere conjugate gradient algorithm
	eBFGS=3, ///< vector Broyden-Fletcher-Goldfarb-Shanno (BFGS) algorithm
	eBFGSTwo=4, ///< the most efficient vector Broyden-Fletcher-Goldfarb-Shanno BFGS algorithm
	eSteepest=5, ///< the steepest descent algorithm 
	eSimplexNM=6 ///< Simplex algorithm of Nelder and Mead
}eGSLMultiMinAlgo ;

typedef struct sGSLMultiMinResult
{
	uint		mNIter			;
	bool		mConvergence	;
	double		mCritValue		;
	cDVector	mGrad			;
	double		mFunctValue		;
}sGSLMultiMinResult ;

typedef double (*GSLMultiMinF)(const gsl_vector * x, void * params)  ;
typedef void (*GSLMultiMinDf)(const gsl_vector * x, void * params, gsl_vector * g)  ;
typedef void (*GSLMultiMinFdf)(const gsl_vector * x, void * params, double * f, gsl_vector * g) ;


class cGSLMultiMin
{
	private :
		cDVector mvInitPoint ;
		bool mvFdf ;
		union uType
		{	const gsl_multimin_fdfminimizer_type* mvTypeFdf ;
			const gsl_multimin_fminimizer_type* mvTypeF ;
		}mvType ;	
		union uMinimizer
		{	gsl_multimin_fdfminimizer* mvStateFdf ;
			gsl_multimin_fminimizer* mvStateF ;
		}mvState ;
		union uFunct
		{	gsl_multimin_function_fdf mvFunctFdf ;
			gsl_multimin_function mvFunctF ;
		} mvFunct ;
		union uStepSize
		{	double mvStepDouble ;
			cDVector* mvStepVect ;
		}mvStepSize ;
		double mvTol ;
		
	public :
		cGSLMultiMin() ;
		cGSLMultiMin(cDVector& theX0, eGSLMultiMinAlgo theTypeAlgo, gsl_multimin_function_fdf* theFunction = NULL, cDVector theStepSize = cDVector(1, 1e-3), double theTol=1e-4) ;
		cGSLMultiMin(cDVector& theX0, eGSLMultiMinAlgo theTypeAlgo, gsl_multimin_function* theFunction, cDVector theStepSize= cDVector(1, 1e-3)) ;
		void SetInitPoint(cDVector& theX0) ;
		void SetTypeAlgo(eGSLMultiMinAlgo theTypeAlgo) ;
		void SetFunction(gsl_multimin_function_fdf* theFunction) ;
		void SetFunction(gsl_multimin_function* theFunction) ;
		void SetFunction(GSLMultiMinF theF, GSLMultiMinDf theDf, GSLMultiMinFdf theFdf, size_t theNParam, void* theOtherParam) ;
		void SetFunction(GSLMultiMinF theF, size_t theNParam, void* theOtherParam) ;
		void SetStepSize(cDVector theStepSize) ;
		void SetTol(double theTol) ;
		void GSLOptim(cDVector& theX, sGSLMultiMinResult& theResStruct, double theStopValue=1e-6, int theMaxIter = 100, bool theVerbose = false) ;
		virtual ~cGSLMultiMin() ;
};
#endif // _GSL_
#endif //_CGSLMULTIMIN_H_
