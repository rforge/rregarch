/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cArch.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cArch.h"

cArch::cArch(int theNArch):cAbstCondVar(eArch)
{
	mvCste = 0.0L ;
	mvArch.ReAlloc(theNArch) ;
	MESS_CREAT("cArch") ;
}

cArch::~cArch()
{
	mvArch.Delete() ;
  	MESS_DESTR("cArch") ;
}

void cArch::Print(ostream& theOut) const
{
	theOut << "ARCH(" << mvArch.GetSize() << ") model:" << endl ;
	theOut << "Const=" << mvCste << endl ;
	for (register uint i = 0 ; i < mvArch.GetSize() ; i++)
		theOut << "ARCH[" << i+1 << "]=" << mvArch[i] << endl ;
}
void cArch::ReAlloc(int theVal1, int theVal2)
{
	mvArch.ReAlloc(theVal1) ;
}
void cArch::ReAlloc(const cDVector& theParam)
{
	mvArch.ReAlloc((int)theParam[0]) ;
}
void cArch::Affect(const cDVector& thecDVector, int thePlace)
{
	if (thePlace == 0)
		mvCste = thecDVector[0] ;
	else
		mvArch = thecDVector ;
}

void cArch::Affect(double theValue, int thePlace)
{
	if (thePlace == 0)
		mvCste = theValue ;
	else
	{	if (thePlace <= (int)mvArch.GetSize())
			mvArch[thePlace-1] = theValue ;
		else
			throw cRegArchError("wrong place") ;
	}
}

void cArch::Affect(cAbstCondVar& theSrc)
{
// theSrc cannot be const due to the use of dynamic_cast
cArch* myArch = dynamic_cast<cArch*>(&theSrc) ;
	if (myArch)
	{	mvArch = myArch->mvArch ;
		mvCste = myArch->mvCste ;
	}
	else
		throw cRegArchError("wrong conditional variance class") ;
}

double cArch::ComputeVar(int theDate, const cRegArchValue& theValue) const
{
int myp = (int)mvArch.GetSize() ;
double myRes = mvCste ;
	for (register int i = 1 ; i <= MIN(myp, theDate) ; i++)
		myRes += mvArch[i-1] * theValue.mUt[theDate-i] * theValue.mUt[theDate-i] ;
	return myRes ;
}


uint cArch::GetNParam(void) const
{
	return 1 + mvArch.GetSize() ;
}


uint cArch::GetNLags(void) const
{
	return mvArch.GetSize() ;
}


void cArch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = GetNParam() ;
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("Wrong size") ;
	theDestVect[theIndex] = mvCste ;
	mvArch.SetSubVectorWithThis(theDestVect, theIndex+1) ;
}

void cArch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize() ;
	if (GetNParam() + theIndex > mySize)
		throw cRegArchError("Wrong size") ;
	mvCste = theSrcVect[theIndex] ;
	mvArch.SetThisWithSubVector(theSrcVect, theIndex+1) ;
}

void cArch::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const
{
int myp = (int)mvArch.GetSize() ;
	theGradData.mCurrentGradVar = 0.0L ;
int myBegIndex = (int)theGradData.GetNMeanParam() ;
	theGradData.mCurrentGradVar[myBegIndex] = 1.0 ;
register int i ;
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		theGradData.mCurrentGradVar[myBegIndex+i] = theValue.mUt[theDate - i]*theValue.mUt[theDate - i] ;
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		theGradData.mCurrentGradVar -= 2.0 * mvArch[i-1] * theValue.mUt[theDate - i] * theGradData.mGradMt[i-1] ;
}
