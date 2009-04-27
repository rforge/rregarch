/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cVarInMean.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CVARINMEAN_H_
#define _CVARINMEAN_H_

#include "cAbstCondMean.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

/*!
 \file cVarInMean.h
 \brief header for class cVarInMean.

 \author Ollivier TARAMASCO
 \date dec-18-2006 - Last change mar-02-2009
*/
class cVarInMean : public cAbstCondMean
{
private :
	double mvVarInMean ;
public :
	cVarInMean(double theVarInMean = 0.0) ;
	~cVarInMean() ;
	void Delete(void) ;
	void Print(ostream& theOut=cout) const ;
	void Affect(const cDVector& theDVector) ;
	void Affect(double theValue) ;
	void Affect(int theIndex, double theValue) ;
	void Affect(cAbstCondMean* theSrc) ;
	void ReAlloc(const cDVector& theParam) ;
	void ReAlloc(uint theParam, uint theNumParam=0) ;
	cAbstCondMean& operator=(cAbstCondMean& theSrc) ;
	double ComputeMean(int theDate, const cRegArchValue& theData) const ;
	uint GetNParam(void) const ; ///< Return number of parameters
	uint GetNLags(void) const ;
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) ;
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const ;
} ;

#endif // _CVARINMEAN_H_
