/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cAbstResiduals.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CABSTRESIDUALS_H_
#define _CABSTRESIDUALS_H_

#include "RegArchDef.h"
#ifndef _GSL_
	#include "RGslRandistEquiv.h"
#else
	#include <gsl/gsl_randist.h>
#endif // _GSL_
#include <time.h>
#include <math.h>

class cRegArchValue ;
class cRegArchGradient ;

/**
 * Abstract class to implement a distribution for residuals
 */
class cAbstResiduals
{
private :
	eDistrTypeEnum	mvDistr	; ///< type of distribution
	bool			mvForSimul ; ///< true if created for simulations
#ifdef _GSL_
protected :
	gsl_rng* mtR ; ///< random generator
#endif // _GSL_
public :
	cDVector	mLawParam ; ///< parameters of the distribution (if any)
public :
	
	/** Constructor using the type of distribution, the parameters 
	 * and a flag on random generator initialization */
	cAbstResiduals(eDistrTypeEnum theDistr, const cDVector* theParam=NULL, bool theForSimul=true) ;
	virtual ~cAbstResiduals() ; ///< a simple destructor
	
	/** Return the distribution type */
	eDistrTypeEnum GetDistrType(void) const ;
	
	/** Return true iif instance contains a random generator */
	bool GetForSimul(void) const ;

	/** Affectation operator for cAbstResiduals */
	cAbstResiduals& operator =(const cAbstResiduals& theSrc) ;	
	void SetSimul(void) ; ///< change for simul and initialize mtR
	virtual void Print(ostream& theOut) const=0 ; ///< print the distribution type

	/** Draw a sample from residual distribution 
	 * \param int theT Sample size
	 * \param theYt Vector where the sample is stored */
	virtual void Generate(int theT, cDVector& theYt) const=0;
	
	virtual double Density(double theX) const=0 ; ///< density function
	virtual double LogDensity(double theX) const=0 ; ///< log density function
	virtual uint GetNParam(void) const=0 ; ///< Return number of parameters

	/** Conversion from a cAbstResiduals instance to a vector of parameters */
	virtual void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) const=0 ;

	/** Change parameter of cAbstResiduals instance according to given vector of parameters */	
	virtual void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0)=0 ;
	
	/** Compute the gradient of Log-density with respect to residual 
	 * and potentially, with respect to parameters. 
	 * \param theX Value for gradient computation
	 * \param theGrad Gradient value with residual (theGrad[0]) 
	 * and parameters (theGrad[i], i > 0) */
	virtual void GradLogDensity(double theX, cDVector& theGrad) const=0 ;

	/** Compute gradient of Log-density with respect to residual and parameters
	 * \param theDate Date of interest for the process 
	 * \parame theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradDens) */
	virtual void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData) const=0 ;
	
	virtual double ComputeEspAbsEps(void) const = 0 ;
	virtual void ComputeGradBetaEspAbsEps(const cDVector& theGrad) const = 0 ;
} ;

extern cAbstResiduals* CreateOneCondResiduals(eDistrTypeEnum theType, const cDVector* theParam, bool theForSimul) ;

#endif //_CABSTRESIDUALS_H_

