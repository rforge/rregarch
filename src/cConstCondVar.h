/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cConstCondVar.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CCONSTCONDVAR_H_
#define _CCONSTCONDVAR_H_

#include "cAbstCondVar.h"
#include "cRegArchGradient.h"


/**
 * Class to implement constant conditional variance
 */
class cConstCondVar : public cAbstCondVar
{
private :
	double mvCste ; //< value of constant variance
public :
	cConstCondVar(double theValue=1.0) ; ///< a simple constructor
	virtual ~cConstCondVar() ; ///< a simple destructor
	void Print(ostream& theOut) const ; ///< print the parameters

	/** Change number of parameter (not useful here) */
	void ReAlloc(const cDVector& theParam) ;

	/** Change number of parameter (not useful here) */	
	void ReAlloc(int theVal1, int theVal2) ;
	
	/** Change the components for conditional variance.
	* theSrc cannot be const due to the dynamic_cast */
	void Affect(cAbstCondVar& theCondVarSrc) ;

	/** Change model parameters.
	 * \param theDVector New value of parameter */
	void Affect(const cDVector& theDVector, int thePlace=0) ;

	/** Change model parameters.
	 * \param theValue New value of parameter 
	 * \param thePlace Index of parameter to be changed */
	void Affect(double theValue, int thePlace = 0) ;

	/** Return conditional variance.
	 * \param theDate Date for conditional variance computation
	 * \param theValue Instance where the dataset is stored */
	double ComputeVar(int theDate, const cRegArchValue& theValue) const ;

	uint GetNParam(void) const ; ///< Return number of parameters
	
	/** Return the number of steps in the past necessary, 
	 * \e e.g., for likelihood computation */
	uint GetNLags(void) const ;
	
	/** Conversion from a cConstCondVar instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) ;

	/** Change parameter of cConstCondVar instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;

	/** Compute gradient of conditional variance with respect to parameters
	 * \param theDate Date of interest for the process 
	 * \parame theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradVar 
	 * \param theResids conditional distribution used only for non normal EGARCH models
     */
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const ;

} ;
#endif //_CCONSTCONDVAR_H_
