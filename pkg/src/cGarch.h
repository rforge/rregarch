/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cGarch.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CGARCH_H_
#define _CGARCH_H_

#include "cAbstCondVar.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/**
 * Class to implement GARCH conditional variance
 * (including ARCH and additive constant)
 */
class cGarch : public cAbstCondVar
{
private :
	double	mvCste ; ///< constant component of conditional variance
	cDVector mvArch ; ///< vector of ARCH coefficients.
	cDVector mvGarch ; ///< vector of GARCH coefficients.
public :
	cGarch(int theNArch = 0, int theNGarch=0) ; ///< a simple constructor
	
	/** Constructor using the orders of ARCH and GARCH models.
	 * \param thePAndQ thePAndQ[0] is the order of the ARCH model
	 * \param thePAndQ thePAndQ[1] is the order of the GARCH model */
	cGarch(cDVector& thePAndQ) ;
	~cGarch() ; ///< a simple destructor
	void Print(ostream& theOut=cout) const ; ///< print the parameters

	/** Change model parameters.
	 * Vector of parameters is resized to size theParam[0] */
	void ReAlloc(const cDVector& theParam) ;

	/** Change model parameters.
	 * Vector of ARCH parameters is resized to size theVal1 
	 * Vector of ARCH parameters is resized to size theVal2 */	
	void ReAlloc(int theVal1, int theVal2=0) ;

	/** Change the components for conditional variance.
	 theSrc cannot be const due to the dynamic_cast */
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
	double ComputeVar(int theDate, const cRegArchValue& theValue) const;	
	
	uint GetNParam(void) const ; ///< Return number of parameters
	
	/** Return the number of steps in the past required, 
	 * \e e.g., for likelihood computation */
	uint GetNLags(void) const ;

	/** Conversion from a cGarch instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) ;

	/** Change parameter of cGarch instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;

	/** Compute gradient of conditional variance with respect to parameters
	 * \param theDate Date of interest for the process 
	 * \parame theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradVar 
	 * \param theResids conditional distribution used only for non normal EGARCH models
	 */
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const ;
} ;

#endif // _CGARCH_H_
