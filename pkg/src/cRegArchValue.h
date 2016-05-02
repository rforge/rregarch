/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchValue.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CREGARCHVALUE_H_
#define _CREGARCHVALUE_H_
#include "RegArchDef.h"
/*!
 * \file cRegArchValue.h
 * \brief Definition of the cRegArchValue class.
 * \par Details.
 * 
 * This class is used for computing the conditional mean, variance and
 * residuals for a regression ARCH model.
 *
 * \author Ollivier TARAMASCO
 * \date 2007-nov-22
*/


class cRegArchValue
{
public :
	cDVector	mYt	; ///< vector of data.
	cDMatrix	mXt	; ///< matrix of regressors if any.
	cDVector	mMt	; ///< vector of conditional mean.
	cDVector	mHt	; ///< vector of conditional variance.
	cDVector	mUt	; ///< vector of residuals.
	cDVector	mEpst ; ///< vector of standardized residuals.
public :
	cRegArchValue(uint theSize, cDMatrix* theXt=NULL) ; ///< a creator
	cRegArchValue(cDVector* theYt=NULL, cDMatrix* theXt=NULL) ;
	cRegArchValue(const cRegArchValue* theValue); //copy constructor
	virtual ~cRegArchValue() ;
	void ReAllocValue(uint theSize=0, bool theDataValuesExist=false) ;
	void ReAllocValue(cDVector& theYt) ;
	void ReAllocValue(cDVector& theYt, cDMatrix& theXt) ;
	void PrintValue(ostream& theOut=out, bool theHeader=true, char* theSep="\t") ;
};

extern ostream& operator <<(ostream &theOut, cRegArchValue &theSimul) ;

#endif //_CREGARCHVALUE_H_
