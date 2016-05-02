/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cStudentResiduals.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CSTUDENTRESIDUALS_H_
#define _CSTUDENTRESIDUALS_H_
#include "cAbstResiduals.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/*!
 \file cStudentResiduals.h
 \brief Definition of the class for Student conditional distribution.

 \author Ollivier TARAMASCO
 \date dec-18-2006
*/


/**
 * Class to implement a Student distribution with unitary variance for residuals
 */
class cStudentResiduals:public cAbstResiduals
{
public :
	/** Constructor using the parameter value 
	 * and a flag  on random genrator initialization */
	cStudentResiduals(double theDof, bool theForSimul=true) ;

	/** Constructor using vector of parameters 
	 * and a flag  on random genrator initialization */
	cStudentResiduals(const cDVector* theLawParam=NULL, bool theForSimul=true) ;	
	virtual ~cStudentResiduals() ; ///< a simple destructor
	void Print(ostream& theOut) const ; ///< print the distribution type

	/** Draw a sample from residual distribution 
	 * \param int theT Sample size
	 * \param theYt Vector where the sample is stored */
	void Generate(int theT, cDVector& theYt) const;

	double Density(double theX) const ; ///< density function
	double LogDensity(double theX) const ; ///< log density function
	uint GetNParam(void) const ; ///< Return number of parameters

	/** Conversion from a cStudentResiduals instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) const ;

	/** Change parameter of cStudentResiduals instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;

	/** Compute the gradient of Log-density with respect to residual 
	 * and with respect to parameters. 
	 * \param theX Value for gradient computation
	 * \param theGrad Gradient value with residual (theGrad[0]) 
	 * and parameters (theGrad[i], i > 0) */
	void GradLogDensity(double theX, cDVector& theGrad) const ;

	/** Compute gradient of Log-density with respect to residual and parameters
	 * \param theDate Date of interest for the process 
	 * \param theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradDens) */
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData) const ;
	double ComputeEspAbsEps(void) const ;
	void ComputeGradBetaEspAbsEps(const cDVector& theGrad) const ;
} ;

#endif //_CSTUDENTRESIDUALS_H_

