/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cLinReg.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cLinReg.h"

cLinReg::cLinReg(int theNLinReg):cAbstCondMean(eLinReg)
{
	mvBeta.ReAlloc(theNLinReg) ;
	MESS_CREAT("cLinReg") ;
}

cLinReg::~cLinReg()
{
	mvBeta.Delete() ;
	MESS_DESTR("cLinReg") ;
}
void cLinReg::Delete(void)
{
	mvBeta.Delete() ;
}

void cLinReg::Print(ostream& theOut) const
{
	for (register uint i = 0 ; i < mvBeta.GetSize() ; i++)
			theOut << "LinReg[" << i+1 << "] = " << mvBeta[i] << endl ;
}


void cLinReg::Affect(const cDVector& theDVector) 
{
	mvBeta = theDVector ;
}

void cLinReg::Affect(double theValue) 
{
	mvBeta.ReAlloc(1) ;
	mvBeta[0] = theValue ;
}



void cLinReg::Affect(cAbstCondMean* theSrc) 
{
cLinReg* myLinReg = dynamic_cast<cLinReg*>(theSrc) ;
	mvBeta = myLinReg->mvBeta ;
}


void cLinReg::ReAlloc(const cDVector& theParam)
{
	mvBeta.ReAlloc((int)theParam[0]) ;
}

void cLinReg::ReAlloc(uint theParam, uint theNumParam)
{
	mvBeta.ReAlloc(theParam) ;
}

cAbstCondMean& cLinReg::operator =(cAbstCondMean &theSrc)
{
	cLinReg* myLinReg = dynamic_cast<cLinReg *>(&theSrc) ;
	if (myLinReg)
		mvBeta = myLinReg->mvBeta ;
	return *this ;
} 

double cLinReg::ComputeMean(int theDate, const cRegArchValue& theData) const
{
	int myp = (int)mvBeta.GetSize() ;
	if (myp > 0)
	{	
		double myRes = 0.0 ;
			for (register int i = 0 ; i < myp ; i++)
					myRes += mvBeta[i] * theData.mXt[theDate][i] ; 
			return myRes ;
	}
	else 
		return 0.0 ;
}

uint cLinReg::GetNParam(void) const
{
	return (int)mvBeta.GetSize() ;
}

uint cLinReg::GetNLags(void) const
{
	return 0 ;
}

void cLinReg::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = mvBeta.GetSize() ;
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("wrong size") ;
	mvBeta.SetSubVectorWithThis(theDestVect, theIndex) ;
}

void cLinReg::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize() ;
	if (mvBeta.GetSize() + theIndex > mySize)
		throw cRegArchError("wrong size") ;
	mvBeta.SetThisWithSubVector(theSrcVect, theIndex) ;
}

void cLinReg::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData,  uint theBegIndex, cAbstResiduals* theResids) const
{
	for (register int i = 1 ; i <= (int)mvBeta.GetSize()  ; i++)
		theGradData.mCurrentGradMu[theBegIndex+i-1] += theValue.mXt[i][theDate] ;
}

