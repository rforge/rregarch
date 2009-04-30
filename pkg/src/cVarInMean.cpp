/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cVarInMean.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cVarInMean.h"

cVarInMean::cVarInMean(double theVarInMean):cAbstCondMean(eVarInMean)
{
	mvVarInMean = theVarInMean ;
	MESS_CREAT("cVarInMean") ;
}

cVarInMean::~cVarInMean()
{
	MESS_DESTR("cVarInMean") ;
}

void cVarInMean::Delete(void)
{
	MESS_DESTR("cVarInMean") ;
}

void cVarInMean::Print(ostream& theOut) const
{
		theOut << "VarInMean = " << mvVarInMean << endl ;
}


void cVarInMean::Affect(const cDVector& theDVector) 
{
	mvVarInMean = theDVector[0] ;
}

void cVarInMean::Affect(double theValue) 
{
	mvVarInMean = theValue ;
}


void cVarInMean::Affect(cAbstCondMean* theSrc) 
{
cVarInMean* myVarInMean = dynamic_cast<cVarInMean*>(theSrc) ;
	mvVarInMean = myVarInMean->mvVarInMean ;
}


void cVarInMean::ReAlloc(const cDVector& theParam)
{
}

void cVarInMean::ReAlloc(uint theParam, uint theNumParam)
{
}

cAbstCondMean& cVarInMean::operator =(cAbstCondMean& theSrc)
{
cVarInMean* myVarInMean = dynamic_cast<cVarInMean *>(&theSrc) ;
	if (myVarInMean)
		mvVarInMean = myVarInMean->mvVarInMean ;
	return *this ;
} 

double cVarInMean::ComputeMean(int theDate, const cRegArchValue& theData) const
{
	return mvVarInMean * theData.mHt[theDate] ; 
}

uint cVarInMean::GetNParam(void) const
{
	return 1 ;
}
uint cVarInMean::GetNLags(void) const
{
	return 0 ;
}

void cVarInMean::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
	theDestVect[theIndex] = mvVarInMean ;
}

void  cVarInMean::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
	mvVarInMean = theSrcVect[theIndex] ;
}

void cVarInMean::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const
{
	theGradData.mCurrentGradMu[theBegIndex] += theValue.mHt[theDate] ;
	theGradData.mCurrentGradMu += mvVarInMean * theGradData.mCurrentGradVar ;
}