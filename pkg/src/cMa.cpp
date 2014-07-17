/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cMa.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cMa.h"

cMa::cMa(int theNMa):cAbstCondMean(eMa)
{
	mvMa.ReAlloc(theNMa) ;
	MESS_CREAT("cMA") ;
}

cMa::~cMa()
{
	mvMa.Delete() ;
	MESS_DESTR("cMA") ;
}

void cMa::Delete(void)
{
	mvMa.Delete() ;
	MESS_DESTR("cMA") ;
}

void cMa::Print(ostream& theOut) const
{
	for (register uint i = 0 ; i < mvMa.GetSize() ; i++)
		theOut << "MA[" << i+1 << "]=" << mvMa[i] << endl ;
}


void cMa::Affect(const cDVector& theDVector)
{
	mvMa = theDVector ;
}

void cMa::Affect(double theValue)
{
	mvMa.ReAlloc(1) ;
	mvMa[0] = theValue ;
}



void cMa::Affect(int theIndex, double theValue)
{
	if (theIndex < (int)mvMa.GetSize())
		mvMa[theIndex] = theValue ;
	else
		throw cRegArchError("bad index") ;
}



void cMa::Affect(cAbstCondMean* theSrc)
{
cMa* myMa = dynamic_cast<cMa*>(theSrc) ;
	mvMa = myMa->mvMa ;
}


void cMa::ReAlloc(const cDVector& theParam)
{
	mvMa.ReAlloc((int)theParam[0]) ;
}

void cMa::ReAlloc(uint theParam, uint theNumParam)
{
	mvMa.ReAlloc(theParam) ;
}

cAbstCondMean& cMa::operator =(cAbstCondMean &theSrc)
 // theSrc cannot be const due to the dynamic_cast
{
cMa* myMa = dynamic_cast<cMa *>(&theSrc) ;
	if (myMa)
		mvMa = myMa->mvMa ;
	return *this ;
}

double cMa::ComputeMean(int theDate, const cRegArchValue& theValue) const
{
int myq = (int)mvMa.GetSize() ;

double myRes = 0.0 ;
	for (register int i = 1 ; i <= MIN(myq, theDate) ; i++)
		myRes += mvMa[i-1] * theValue.mUt[theDate-i] ;
	return myRes ;
}

uint cMa::GetNParam(void) const
{
	return mvMa.GetSize() ;
}
uint cMa::GetNLags(void) const
{
	return mvMa.GetSize() ;
}
void cMa::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = mvMa.GetSize() ;
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("wrong size") ;
	mvMa.SetSubVectorWithThis(theDestVect, theIndex) ;
}

void cMa::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize() ;
	if (mvMa.GetSize() + theIndex > mySize)
		throw cRegArchError("wrong size") ;
	mvMa.SetThisWithSubVector(theSrcVect, theIndex) ;
}

void cMa::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const
{
int myq = (int)mvMa.GetSize() ;
register int i ;
	for (i = 1 ; i <= MIN(myq, theDate) ; i++)
		theGradData.mCurrentGradMu[theBegIndex+i-1] += theValue.mUt[theDate - i] ;
	for (i = 1 ; i <= MIN(myq, theDate) ; i++)
		theGradData.mCurrentGradMu -=  mvMa[i-1] * theGradData.mGradMt[i-1] ;

}
