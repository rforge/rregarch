/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cCondMean.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CCONDMEAN_H_
#define _CCONDMEAN_H_

#include "RegArchDef.h"
#include "cAbstCondMean.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/**
 * Class to implement the model conditional mean
 */
class cCondMean
{
private :
	uint			mvNCondMean	;  ///< number of mean components
	cAbstCondMean**	mvCondMean	; ///< array of *cAbstCondMean
public :
	cCondMean(uint theNCondMean = 0) ; ///< a simple constructor
	
	/** Constructor using the number and types of conditional means.
	 * \param theCode Array of mean types 
	 * \param theNCondMean Number of mean components */
	cCondMean(const eCondMeanEnum* theCode, uint theNCondMean) ;
	
	/** Copy constructor
	 * theCondMean cannot be const due to the use of operator= on components */
	cCondMean(cCondMean& theCondMean) ;
	void Delete(void) ; ///< delete

	/** Change number of mean components.
	 * \param theNCondMean New number of mean components */	
	void ReAlloc(uint theNCondMean) ;
	
	/** Return number of mean components.*/
	uint GetSize(void) const ;
	
	/** Set the type of a given mean component. 
	 * \param theWhatMean Index of component to be set
	 * \param theCode Type of component */
	void AllocOneMean(uint theWhatMean, eCondMeanEnum theCode) ;
	
	/* Return a given component */
	cAbstCondMean* GetOneMean(uint theIndex) const ;
	
	void Print(ostream& theOut=cout) const ;
	friend ostream& operator <<(ostream& theOut, const cCondMean& theCondMean) ;
	virtual ~cCondMean() ; ///< a simple destructor
	
	/** Return in theCodeType the type of each mean component */
	void GetCondMeanType(eCondMeanEnum* theCodeType) const ;
	
	void ReAllocOneMean(int theWhatMean, cDVector& theParam) ;
	/**	Change (unique) component for conditional mean
	 * theAbsCondMean cannot be const due to operator= */
	void AffectOneMean(int theWhatMean, cAbstCondMean* theAbstCondMean) ;
	/** Affectation operator for cCondMean
	 * theSrc cannot be const due to use of operator= on components */
	cCondMean& operator =(cCondMean& theSrc) ;

	/** Return conditional mean.
	 * \param theDate Date for conditional mean computation
	 * \param theData Instance where the dataset is stored */
	double ComputeMean(int theDate, const cRegArchValue& theData) const ;

	uint GetNParam(void) const ; ///< Return number of parameters
	
	/** Return the number of steps in the past required, 
	 * \e e.g., for likelihood computation */
	uint GetNLags(void) const ;

	/** Conversion from a cCondMean instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) const ;
	
	/** Change parameter of cCondMean instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0);
	
	/** Compute gradient of conditional mean with respect to parameters
	 * \param theDate Date of interest for the process 
	 * \parame theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradVar)
	 * \param theResids conditional distribution used only for non normal EGARCH models
	 */
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResids) const ;

} ;
#endif // _CCONDMEAN_H_

