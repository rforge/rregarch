/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cStudentResiduals.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cStudentResiduals.h"
#include "cRegArchError.h"
#ifdef _RDLL_
#include <R.h>
#include <Rmath.h>
	#define gsl_ran_tdist(p, q) (rt(q))
	#define gsl_sf_gamma(p) (gammafn(p))
	#define gsl_sf_psi(p) (digamma(p))
#else
	#include <gsl/gsl_sf_gamma.h>
	#include <gsl/gsl_sf_psi.h>
#endif // _RDLL_

cStudentResiduals::cStudentResiduals(double theDof, bool theForSimul):cAbstResiduals(eStudent, NULL, theForSimul)
{
	mLawParam.ReAlloc(1) ;
	mLawParam[0] = (double)theDof ;
	MESS_CREAT("cStudentResiduals")
}

cStudentResiduals::cStudentResiduals(const cDVector* theLawParam, bool theForSimul):cAbstResiduals(eStudent, theLawParam, theForSimul)
{
	MESS_CREAT("cStudentResiduals")
}

cStudentResiduals::~cStudentResiduals()
{
	MESS_DESTR("cStudentResiduals")
}

void cStudentResiduals::Generate(int theT, cDVector &theYt) const
{
	theYt.ReAlloc(theT) ;
	if (mLawParam[0] <= 2.0)
		throw cRegArchError("wrong d.o.f.") ;

double myStd = sqrt(mLawParam[0]/(mLawParam[0]-2.0)) ;
	for (register int t = 0 ; t < theT ; t++)
		theYt[t] = gsl_ran_tdist(mtR, mLawParam[0])/myStd ;
}

void cStudentResiduals::Print(std::ostream &theOut) const
{
	theOut << "Conditional Student Distribution with " << mLawParam[0] << " d. o. f." << endl ;
}

static double StudentDensity(double theX, double theDof)
{
	return 1.0/sqrt(theDof*PI)*gsl_sf_gamma((theDof+1.0)/2.0)/gsl_sf_gamma(theDof/2.0)*exp(-(theDof+1.0)/2.0*log(1+theX*theX/theDof)) ;
}

static double StudentLogDensity(double theX, double theDof)
{
double myAux = -0.5*((theDof + 1)*log((theDof+theX*theX)/theDof) + log(theDof) + LOG_PI) ;
	return myAux + log(gsl_sf_gamma((theDof+1.0)/2.0)/gsl_sf_gamma(theDof/2)) ;
}


static void StudentGradLogDensity(double theX, double theDof, cDVector& theGrad)
{
double myt2 = theX * theX ;
double myAux1 = myt2+theDof ;
	theGrad[0] = -(theDof+1)*theX/myAux1 ;
double myAux2 = log(myAux1)-gsl_sf_psi((theDof+1)/2.0)-log(theDof)+gsl_sf_psi(theDof/2.0) ;
	theGrad[1] = -0.5*(myAux2 + (1 - myt2)/myAux1) ;
}

double cStudentResiduals::Density(double theX) const
{
double myStd = sqrt(mLawParam[0]/(mLawParam[0]-2.0)) ;
	return StudentDensity(theX*myStd, mLawParam[0])*myStd ;
}

double cStudentResiduals::LogDensity(double theX) const
{
double myStd = sqrt(mLawParam[0]/(mLawParam[0]-2.0)) ;
	return StudentLogDensity(theX*myStd, mLawParam[0]) + log(myStd) ;

}
uint cStudentResiduals::GetNParam(void) const
{
	return 1 ;
}

void cStudentResiduals::RegArchParamToVector(cDVector& theDestVect, uint theIndex) const
{
	if (theDestVect.GetSize() < theIndex - 1)
		throw cRegArchError("Wrong size") ;
	theDestVect[theIndex] = mLawParam[0] ;
}
void cStudentResiduals::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
	if (1 + theIndex > theSrcVect.GetSize())
		throw cRegArchError("Wrong size") ;
	mLawParam[0] = theSrcVect[theIndex] ;
}


void cStudentResiduals::GradLogDensity(double theX, cDVector& theGrad) const
{
double	myDof = mLawParam[0],
		myStd = sqrt(myDof/(myDof-2.0)) ;
	StudentGradLogDensity(theX*myStd, myDof, theGrad) ;

double	myAux1 = myDof - 2.0,
		myAux2 = myAux1 * myDof ;
	theGrad[1] -=  (theX * theGrad[0]/(myAux1*sqrt(myAux2)) + 1.0/myAux2) ;
	theGrad[0] *=  myStd ;

}

void cStudentResiduals::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData) const
{
	GradLogDensity(theValue.mEpst[theDate], theGradData.mCurrentGradDens) ;
}

/*
 * (2*sqrt(n-2)*gamma((n+1)/2))/(sqrt(PI)*(n-1)*gamma(n/2))
 */

double cStudentResiduals::ComputeEspAbsEps(void) const
{
	double myDof = mLawParam[0] ;
	return gsl_sf_gamma((myDof+1.0)/2.0)/gsl_sf_gamma(myDof/2.0)
		*2.0*sqrt(myDof-2.0)/(myDof-1.0)/SQRT_PI ;
}

/*
 *  [(n^2 - 3*n + 2)*(psi0((n+1)/2) - psi0(n/2)) - n + 3]/[sqrt(PI)*sqrt(n-2)*(n-1)^2]*gamma((n+1)/2)/gamma(n/2)
 */
void cStudentResiduals::ComputeGradBetaEspAbsEps(const cDVector& theGrad) const
{
double myDof = mLawParam[0],
		myAux = myDof*myDof-3*myDof+2 ;
	
	theGrad[0] = (myAux*gsl_sf_psi((myDof+1)/2.0)-myAux*gsl_sf_psi(myDof/2.0)- myDof + 3.0)
		*gsl_sf_gamma((myDof+1)/2.0)
		/(SQRT_PI*sqrt(myDof-2)*(myDof*myDof-2*myDof+1)*gsl_sf_gamma(myDof/2.0)) ;
}
