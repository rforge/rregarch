/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cStdDevInMean.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cStdDevInMean.h"

cStdDevInMean::cStdDevInMean(double theStdDevInMean):cAbstCondMean(eStdDevInMean)
{
	mvStdDevInMean = theStdDevInMean ;
	MESS_CREAT("cStdDevInMean") ;
}

cStdDevInMean::~cStdDevInMean()
{
	MESS_DESTR("cStdDevInMean") ;
}

void cStdDevInMean::Delete(void)
{
	MESS_DESTR("cStdDevInMean") ;
}

void cStdDevInMean::Print(ostream& theOut) const
{
		theOut << "StdDevInMean = " << mvStdDevInMean << endl ;
}


void cStdDevInMean::Affect(const cDVector& theDVector) 
{
	mvStdDevInMean = theDVector[0] ;
}

void cStdDevInMean::Affect(double theValue) 
{
	mvStdDevInMean = theValue ;
}


void cStdDevInMean::Affect(cAbstCondMean* theSrc) 
{
cStdDevInMean* myStdDevInMean = dynamic_cast<cStdDevInMean*>(theSrc) ;
	mvStdDevInMean = myStdDevInMean->mvStdDevInMean ;
}


void cStdDevInMean::ReAlloc(const cDVector& theParam)
{
}

void cStdDevInMean::ReAlloc(uint theParam, uint theNumParam)
{
}

cAbstCondMean& cStdDevInMean::operator =(cAbstCondMean& theSrc)
{
cStdDevInMean* myStdDevInMean = dynamic_cast<cStdDevInMean *>(&theSrc) ;
	if (myStdDevInMean)
		mvStdDevInMean = myStdDevInMean->mvStdDevInMean ;
	return *this ;
} 

double cStdDevInMean::ComputeMean(int theDate, const cRegArchValue& theData) const
{
	return mvStdDevInMean * sqrt(theData.mHt[theDate]) ; 
}

uint cStdDevInMean::GetNParam(void) const
{
	return 1 ;
}
uint cStdDevInMean::GetNLags(void) const
{
	return 0 ;
}

void cStdDevInMean::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
	theDestVect[theIndex] = mvStdDevInMean ;
}

void  cStdDevInMean::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
	mvStdDevInMean = theSrcVect[theIndex] ;
}

void cStdDevInMean::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const
{
	theGradData.mCurrentGradMu[theBegIndex] += sqrt(theValue.mHt[theDate]) ;
	theGradData.mCurrentGradMu += mvStdDevInMean * theGradData.mCurrentGradSigma ;
}