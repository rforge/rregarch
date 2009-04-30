/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cStdDevInMean.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CSTDDEVINMEAN_H_
#define _CSTDDEVINMEAN_H_

#include "cAbstCondMean.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

class cStdDevInMean : public cAbstCondMean
{
private :
	double mvStdDevInMean ;
public :
	cStdDevInMean(double theStdDevInMean = 0.0) ;
	~cStdDevInMean() ;
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

#endif // _CStdDevInMean_H_
