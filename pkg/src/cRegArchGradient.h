/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchGradient.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CREGARCHGRADIENT_H_
#define _CREGARCHGRADIENT_H_

class cRegArchParam ;
class cRegArchGradient
{
private :
	uint		mvNPast ; ///< number of past lags
	uint		mvNParam ; ///< number of parameters
	uint		mvNMeanParam ; ///< number of conditional mean parameters
	uint		mvNVarParam ; ///< number of conditional variance parameters
	uint		mvNLawParam ; ///< number of conditional distribution parameters
public :
	cDVector*	mGradMt	; ///< matrix of past gradients of conditional mean.
	cDVector*	mGradHt	; ///< matrix of past gradients of conditional variance.
	cDVector*	mGradEpst ; ///< matrix of past gradients of standardized residuals.
	cDVector	mCurrentGradVar ; ///< Current gradient of conditional variance
	cDVector	mCurrentGradSigma ; ///< Current gradient of conditional standard deviation
	cDVector	mCurrentGradMu ; ///< Current gradient of conditional mean
	cDVector	mCurrentGradDens ; ///< Currend gradient of conditional log density. Size 1 + number of distribution parameters
	cDVector	mCurrentGradEps ; // Current gradient of conditional standardized residuals
public :
	cRegArchGradient(uint theNPast = 0, uint theNMeanParam = 0, uint theNVarParam = 0, uint theNLawParam = 0) ; ///< a creator
	cRegArchGradient(cRegArchParam* theParam) ; ///< a creator
	void Delete(void) ;
	void ReAlloc(uint theNPast, uint theNMeanParam, uint theNVarParam, uint theNLawParam) ;
	void ReAlloc(cRegArchParam* theParam) ;
	virtual ~cRegArchGradient() ;
	uint GetNPast(void) ;
	uint GetNParam(void) ;
	uint GetNMeanParam(void) ;
	uint GetNVarParam(void) ;
	uint GetNLawParam(void) ;
	/** Shift stored values of past gradients towards future (right shift of indices) */
	void Push(void) ;
	/** Update gradient at current date 
	    and shift stored values of past gradients towards future (right shift of indices) */
	void Update(void) ;
};

#endif // _CREGARCHGRADIENT_H_
