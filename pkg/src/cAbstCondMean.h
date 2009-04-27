/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cAbstCondMean.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CABSTCONDMEAN_H_
#define _CABSTCONDMEAN_H_
#include "RegArchDef.h"


/**
* \file cAbstCondMean.h
* \brief Definition of the abstract class for conditional mean.
*
* \author Ollivier TARAMASCO
* \date nov-22-2007
*/
class cRegArchValue ;
class cRegArchGradient ;
class cAbstResiduals ;

/**
 * Abstract class to implement a model for conditional mean
 */
class cAbstCondMean
{
private :
	eCondMeanEnum	mvCondMeanType ; ///< to determinate the mean type
public :
	/** Return the mean type */
	eCondMeanEnum GetCondMeanType(void) const {return mvCondMeanType;} ;
	cAbstCondMean(eCondMeanEnum theType=eUnknown){mvCondMeanType = theType ;} ; ///< a simple constructor
	virtual ~cAbstCondMean() ; ///< a simple destructor	
	virtual void Delete(void) = 0 ; ///< delete
	virtual void Print(ostream& theOut=cout) const = 0 ; ///< print the parameters

	/** Change model parameters.
	 * \param theDVector New value of parameter */
	virtual void Affect(const cDVector& theDVector)=0 ;
	
	/** Change model parameters.
	 * Vector of parameters is resized to size 1
	 * \param theValue New value of parameter */
	virtual void Affect(double theValue) = 0 ;
	
	/** Change the components for conditional mean.
	 theSrc cannot be const due to the dynamic_cast */
	virtual void Affect(cAbstCondMean* theSrc) = 0 ;
	
	/** Change model parameters.
	 * Vector of parameters is resized to size theParam[0] */
	virtual void ReAlloc(const cDVector& theParam) = 0 ;

	/** Change model parameters.
	 * Vector of parameters is resized to size theParam */	
	virtual void ReAlloc(uint theParam, uint theNumParam=0) = 0 ;
	
	/** Affectation operator for cAbstCondMean
	 * theSrc cannot be const due to the dynamic_cast */
	virtual cAbstCondMean& operator=(cAbstCondMean& theSrc)=0 ;
	
	/** Return conditional mean.
	 * \param theDate Date for conditional mean computation
	 * \param theData Instance where the dataset is stored */	
	virtual double ComputeMean(int theDate, const cRegArchValue& theData) const=0 ;
	
	virtual uint GetNParam(void) const = 0 ; ///< Return number of parameters

	/** Return the number of steps in the past required, 
	 * \e e.g., for likelihood computation */
	virtual uint GetNLags(void) const = 0 ;
	
	/** Conversion from a cAbstCondMean instance to a vector of parameters */
	virtual void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0)=0 ;
	
	/** Change parameter of cAbstCondMean instance according to given vector of parameters */	
	virtual void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0)=0 ;
	
	/** Compute gradient of conditional mean with respect to parameters
	 * \param theDate Date of interest for the process 
	 * \parame theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradMu 
	 * \param theBegIndex First index for storage in theGradData.mCurrentGradMu 
	 * \param theResids conditional distribution used only for non normal EGARCH models
	 */
	virtual void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const=0 ;
} ;
/**
* \fn cAbstCondMean* CreateOneCondMean(eCondMeanEnum theType)
* \param theType: type of conditional mean
* \par Details.
* This fonction creates a pointer on a conditional mean class.
*
*/
extern cAbstCondMean* CreateOneCondMean(eCondMeanEnum theType) ;
#endif // _CABSTCONDMEAN_H_

