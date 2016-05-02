/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGarch.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cGarch.h"

cGarch::cGarch(int theNArch, int theNGarch):cAbstCondVar(eGarch)
{
	mvCste = 0.0L ;
	mvArch.ReAlloc(theNArch) ;
	mvGarch.ReAlloc(theNGarch) ;
	MESS_CREAT("cGarch") ;
}

cGarch::cGarch(cDVector& thePAndQ):cAbstCondVar(eGarch)
{
	mvCste = 0.0L ;
	mvArch.ReAlloc((int)thePAndQ[0]) ;
	mvGarch.ReAlloc((int)thePAndQ[1]) ;
	MESS_CREAT("cGarch") ;
}

cGarch::~cGarch()
{
	mvArch.Delete() ;
	mvGarch.Delete() ;
	MESS_DESTR("cGarch") ;
}

void cGarch::Print(ostream& theOut) const
{
	theOut << "GARCH(" << mvArch.GetSize() << ", " << mvGarch.GetSize() << ") model:" << endl ;
	theOut << "Const=" << mvCste << endl ;
register uint i ;
	for (i = 0 ; i < mvArch.GetSize() ; i++)
		theOut << "ARCH[" << i+1 << "]=" << mvArch[i] << endl ;
	for (i = 0 ; i < mvGarch.GetSize() ; i++)
		theOut << "GARCH[" << i+1 << "]=" << mvGarch[i] << endl ;
}

void cGarch::ReAlloc(int theVal1, int theVal2)
{
	mvArch.ReAlloc(theVal1) ;
	mvGarch.ReAlloc(theVal2) ;
}
void cGarch::ReAlloc(const cDVector& theParam)
{
	mvArch.ReAlloc((int)theParam[0]) ;
	mvGarch.ReAlloc((int)theParam[1]) ;
}

void cGarch::Affect(const cDVector& theDVector, int thePlace)
{
	switch (thePlace)
	{	case 0 :
			mvCste = theDVector[0] ;
		break ;
		case 1 :
			mvArch = theDVector ;
		break ;
		default :
			mvGarch = theDVector ;
		break ;
	}
}

void cGarch::Affect(double theValue, int thePlace)
{	switch (thePlace)
	{	case 0 :
			mvCste = theValue ;
		break ;
		case 1 :
		{	mvArch.ReAlloc(1) ;
			mvArch[0]= theValue ;
		}
		break ;
		default :
		{	mvGarch.ReAlloc(1);
			mvGarch[0] = theValue ;
		}
		break ;
	}
}

void cGarch::Affect(cAbstCondVar& theSrc)
{
// theSrc cannot be const due to the use of dynamic_cast
cGarch* myGarch = dynamic_cast<cGarch*>(&theSrc) ;
	if (myGarch)
	{	mvArch = myGarch->mvArch ;
		mvGarch = myGarch->mvGarch ;
		mvCste = myGarch->mvCste ;
	}
}


double cGarch::ComputeVar(int theDate, const cRegArchValue& theValue) const 
{
int myp = (int)mvArch.GetSize(),
	myq = (int)mvGarch.GetSize() ;
double myRes = mvCste ;
	for (register int i = 1 ; i <= MIN(myp, theDate) ; i++)
		myRes += mvArch[i-1] * theValue.mUt[theDate-i] * theValue.mUt[theDate-i] ;
	for (register int j = 1 ; j <= MIN(myq, theDate) ; j++)
		myRes += mvGarch[j-1] * theValue.mHt[theDate-j] ;

	return myRes ;
}

uint cGarch::GetNParam(void) const
{
	return 1 + mvArch.GetSize() + mvGarch.GetSize() ;
}


uint cGarch::GetNLags(void) const
{
	return  MAX(mvArch.GetSize(), mvGarch.GetSize()) ;
}


void cGarch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = GetNParam() ;
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("wrong size") ;
	theDestVect[theIndex] = mvCste ;
	mvArch.SetSubVectorWithThis(theDestVect, theIndex + 1) ;
	mvGarch.SetSubVectorWithThis(theDestVect, theIndex + 1 + mvArch.GetSize()) ;
}

void cGarch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize() ;
	if (GetNParam() + theIndex > mySize)
		throw cRegArchError("wrong size") ;
	mvCste = theSrcVect[theIndex] ;
	mvArch.SetThisWithSubVector(theSrcVect, theIndex+1) ;
	mvGarch.SetThisWithSubVector(theSrcVect, theIndex + 1 + mvArch.GetSize()) ;
}

void cGarch::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const
{
int myp = (int)mvArch.GetSize(),
	myq = (int)mvGarch.GetSize(),
	myBegIndex = (int)theGradData.GetNMeanParam() ;
register int i, j ;
	theGradData.mCurrentGradVar = 0.0L ;
	theGradData.mCurrentGradVar[myBegIndex] = 1.0 ;
	for (i = 1 ; i <=  MIN(myp, theDate) ; i++)
		theGradData.mCurrentGradVar[myBegIndex+i] = theValue.mUt[theDate-i]*theValue.mUt[theDate-i] ;
	for (j = 1 ; j <= MIN(myq, theDate) ; j++)
		theGradData.mCurrentGradVar[myBegIndex+myp+j] += theValue.mHt[theDate-j] ;
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		theGradData.mCurrentGradVar -= 2.0 * mvArch[i-1] * theValue.mUt[theDate-i] * theGradData.mGradMt[i-1] ;
	for (j = 1 ; j <= MIN(myq, theDate) ; j++)
		theGradData.mCurrentGradVar += mvGarch[j-1] * theGradData.mGradHt[j-1] ;
}
