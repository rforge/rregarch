/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cAbstCondVar.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CABSTCONDVAR_H_
#define _CABSTCONDVAR_H_
#include "RegArchDef.h"
class cRegArchValue ;
class cRegArchGradient ;
class cAbstResiduals ;

/**
 * Abstract class to implement a model for conditional variance
 */
class cAbstCondVar
{
private :
	eCondVarEnum	mvCondVar ; ///< to determinate the variance type
public :
	cAbstCondVar(eCondVarEnum theCodeVar = eNotKnown){mvCondVar=theCodeVar ;} ; ///< a simple constructor
	virtual ~cAbstCondVar(){} ;  ///< a simple destructor
	
	/** Return the variance type */
	virtual inline eCondVarEnum GetCondVarType(void) const {return mvCondVar ;} ;
	virtual void Print(ostream& theOut=out) const = 0 ;  ///< print the parameters

	/** Change model parameters.
	 * Vector of parameters is resized to size theParam[0] */
	virtual void ReAlloc(const cDVector& theParam)=0 ;
	
	/** Change model parameters.
	 * Vector of parameters is resized to size theVal1 */	
	virtual void ReAlloc(int theVal1, int theVal2=0)=0 ;

	/** Change the components for conditional variance.
	 theSrc cannot be const due to the dynamic_cast */
	virtual void Affect(cAbstCondVar& theCondVarSrc)=0 ;
	
	/** Change model parameters.
	 * \param theDVector New value of parameter */
	virtual void Affect(const cDVector& theDVector, int thePlace = 0)=0 ;

	/** Change model parameters.
	 * \param theValue New value of parameter 
	 * \param thePlace Index of parameter to be changed */
	virtual void Affect(double theValue, int thePlace = 0)=0 ;

	/** Return conditional variance.
	 * \param theDate Date for conditional variance computation
	 * \param theValue Instance where the dataset is stored */
	virtual double ComputeVar(int theDate, const cRegArchValue& theValue) const=0 ;
	
	virtual uint GetNParam(void) const=0 ;  ///< Return number of parameters

	/** Return the number of steps in the past required, 
	 * \e e.g., for likelihood computation */
	virtual uint GetNLags(void) const=0 ;
	
	/** Conversion from a cAbstCondVar instance to a vector of parameters */
	virtual void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0)=0 ;
	
	/** Change parameter of cAbstCondVar instance according to given vector of parameters */
	virtual void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0)=0 ;

	/** Compute gradient of conditional variance with respect to parameters
	 * except those of the conditional distribution
	 * \param theDate Date of interest for the process 
	 * \param theValue Instance where the dataset is stored
	 * \param theGradData Instance where the result is stored (in theGradData.mCurrentGradVar 
	 * \param cAbstResiduals* theResiduals conditionnal distribution used only in EGARCH model 
	 */
	
	virtual void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const = 0 ;
} ;

extern cAbstCondVar* CreateOneCondVar(eCondVarEnum theType) ;

#endif // _CABSTCONDVAR_H_
