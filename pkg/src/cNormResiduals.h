/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cNormResiduals.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CNORMRESIDUALS_H_
#define _CNORMRESIDUALS_H_
#include "cAbstResiduals.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/*!
 \file cNormResiduals.h
 \brief Definition of the class for N(0, 1) conditional distribution.

 \author Ollivier TARAMASCO
 \date dec-18-2006
*/


/**
 * Class to implement a normal distribution for residuals
 */
class cNormResiduals:public cAbstResiduals
{
public :
	/** Constructor using parameters (not useful) 
	 * and a flag  on random genrator initialization */
	cNormResiduals(const cDVector* theLawParam=NULL, bool theForSimul=true) ;
	virtual ~cNormResiduals() ; ///< a simple destructor
	void Print(ostream& theOut) const ; ///< print the distribution type

	/** Draw a sample from residual distribution 
	 * \param int theT Sample size
	 * \param theYt Vector where the sample is stored */
	void Generate(int theT, cDVector& theYt) const ;
	
	double Density(double theX) const ;  ///< density function
	double LogDensity(double theX) const ; ///< log density function
	uint GetNParam(void) const ; ///< Return number of parameters

	/** Conversion from a cNormResiduals instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) const ;

	/** Change parameter of cNormResiduals instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;

	/** Compute the gradient of Log-density with respect to residual  
	 * \param theX Value for gradient computation
	 * \param theGrad Gradient value with residual (theGrad[0])*/
	void GradLogDensity(double theX, cDVector& theGrad) const ;

	/** Compute gradient of Log-density with respect to residual
	 * \param theDate Date of interest for the process 
	 * \param theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradDens) */
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData) const ; 
	double ComputeEspAbsEps(void) const ;
	void ComputeGradBetaEspAbsEps(const cDVector& theGrad) const ;
} ;

#endif //_CNORMRESIDUALS_H_

