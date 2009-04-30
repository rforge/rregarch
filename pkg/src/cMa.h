/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cMa.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CMA_H_
#define _CMA_H_

#include "cAbstCondMean.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/**
 * Class to implement MA conditional means
 */
class cMa : public cAbstCondMean
{
private :
	cDVector mvMa ;
public :
	cMa(int theNMa = 0) ; ///< a simple constructor
	virtual ~cMa() ; ///< a simple destructor
	void Delete(void) ; ///< delete
	void Print(ostream& theOut=cout) const ; ///< print the parameters

	/** Change model parameters.
	 * \param theDVector New value of parameter */
	void Affect(const cDVector& theDVector) ; 
	
	/** Change model parameters.
	 * Vector of parameters is resized to size 1
	 * \param theValue New value of parameter */
	void Affect(double theValue) ;

	/** Change one model parameter.
	 * \param theIndex Index of parameter to change
	 * \param theValue New value of parameter */
	void Affect(int theIndex, double theValue) ;
	
	/** Change the components for conditional mean.
	 theSrc cannot be const due to the dynamic_cast */
	void Affect(cAbstCondMean* theSrc) ;

	/** Change model parameters.
	 * Vector of parameters is resized to size theParam[0] */
	void ReAlloc(const cDVector& theParam) ;

	/** Change model parameters.
	 * Vector of parameters is resized to size theParam */	
	void ReAlloc(uint theParam, uint theNumParam=0) ;
	
	/** Affectation operator for cMa
	 theSrc cannot be const due to the dynamic_cast */
	cAbstCondMean& operator=(cAbstCondMean& theSrc) ;

	/** Return conditional mean.
	 * \param theDate Date for conditional mean computation
	 * \param theData Instance where the dataset is stored */	
	double ComputeMean(int theDate, const cRegArchValue& theData) const ;

	uint GetNParam(void) const ; ///< Return number of parameters

	/** Return the number of steps in the past necessary, 
	 * \e e.g., for likelihood computation */
	uint GetNLags(void) const ;
	
	/** Conversion from a cAbstCondMean instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) ;

	/** Change parameter of cAbstCondMean instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;
	
	/** Compute gradient of conditional mean with respect to parameters
	 * \param theDate Date of interest for the process 
	 * \parame theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradMu 
	 * \param theBegIndex First index for storage in theGradData.mCurrentGradMu 
	 * \param theResids conditional distribution used only for non normal EGARCH models
	 */
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const ;

} ;

#endif // _M_AR_H_
