/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cNormResiduals.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cNormResiduals.h"
#ifndef _GSL_
#include <R.h>
#include <Rmath.h>
	#define gsl_ran_ugaussian(p) (rnorm(0.0, 1.0))
#else
	//#include <gsl/gsl_ntuple.h>
	//#include <gsl/gsl_rng.h>
	#include <gsl/gsl_randist.h>
#endif // _GSL_


cNormResiduals::cNormResiduals(const cDVector* theLawParam, bool theForSimul):cAbstResiduals(eNormal, theLawParam, theForSimul)
{
	mLawParam.Delete() ;
	MESS_CREAT("cNormResiduals")
}

cNormResiduals::~cNormResiduals()
{
	MESS_DESTR("cNormResiduals")
}

double cNormResiduals::Density(double theX) const
{
	return((1.0/SQRT_2_PI)*exp(-theX*theX/2.0)) ;
}

double cNormResiduals::LogDensity(double theX) const
{
	return(-log(SQRT_2_PI) - theX*theX/2.0) ;
}

void cNormResiduals::Generate(int theT, cDVector& theYt) const 
{
	theYt.ReAlloc(theT) ;

	for (register int t = 0 ; t < theT ; t++)
		theYt[t] = gsl_ran_ugaussian(mtR) ;
}

void cNormResiduals::Print(ostream &theOut) const
{
	theOut << "Conditional Normal Distribution" << endl ;
}

uint cNormResiduals::GetNParam(void) const
{
	return 0 ;
}
void cNormResiduals::RegArchParamToVector(cDVector& theDestVect, uint theIndex) const
{
}
void cNormResiduals::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
}

void cNormResiduals::GradLogDensity(double theX, cDVector& theGrad) const
{
	theGrad[0] = -theX ;
}
void cNormResiduals::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData) const
{
	GradLogDensity(theValue.mEpst[theDate], theGradData.mCurrentGradDens) ;
}

double cNormResiduals::ComputeEspAbsEps(void) const
{
	return 2.0/SQRT_2_PI ;
}

void cNormResiduals::ComputeGradBetaEspAbsEps(const cDVector& theGrad) const
{
}
