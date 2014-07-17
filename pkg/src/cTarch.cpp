/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cTarch.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cTarch.h"

cTarch::cTarch(int theNTarch):cAbstCondVar(eTarch)
{
	mvCste = 0.0L ;
	mvArchPos.ReAlloc(theNTarch) ;
	mvArchNeg.ReAlloc(theNTarch) ;
	MESS_CREAT("cTarch") ;
}

cTarch::~cTarch()
{
	mvArchPos.Delete() ;
  	mvArchNeg.Delete() ;
  	MESS_DESTR("cTarch") ;
}

void cTarch::Print(ostream& theOut) const
{
	theOut << "TARCH(" << mvArchPos.GetSize() << ") model:" << endl ;
	theOut << "Const=" << mvCste << endl ;
	for (register uint i = 0 ; i < mvArchPos.GetSize() ; i++)
		theOut << "ARCH+[" << i+1 << "]=" << mvArchPos[i] << endl ;
	for (register uint i = 0 ; i < mvArchNeg.GetSize() ; i++)
		theOut << "ARCH-[" << i+1 << "]=" << mvArchNeg[i] << endl ;
}
void cTarch::ReAlloc(int theVal1, int theVal2)
{
	mvArchPos.ReAlloc(theVal1) ;
	mvArchNeg.ReAlloc(theVal1) ;
}
void cTarch::ReAlloc(const cDVector& theParam)
{
	mvArchPos.ReAlloc((int)theParam[0]) ;
	mvArchNeg.ReAlloc((int)theParam[0]) ;
}
void cTarch::Affect(const cDVector& thecDVector, int thePlace)
{
	if (thePlace == 0)
		mvCste = thecDVector[0] ;
	else
		if (thePlace == 1)
			mvArchPos = thecDVector ;
		else
			mvArchNeg = thecDVector ;
}

void cTarch::Affect(double theValue, int thePlace)
{
switch (thePlace)
	{	case 0 :
			mvCste = theValue ;
		break ;
		case 1 :
		{	mvArchPos.ReAlloc(1) ;
			mvArchPos[0]= theValue ;
		}
		break ;
		default :
		{	mvArchNeg.ReAlloc(1);
			mvArchNeg[0] = theValue ;
		}
		break ;
	}
}

void cTarch::Affect(cAbstCondVar& theSrc)
{
// theSrc cannot be const due to the use of dynamic_cast
cTarch* myTarch = dynamic_cast<cTarch*>(&theSrc) ;
	if (myTarch)
	{	mvArchPos = myTarch->mvArchPos ;
		mvArchNeg = myTarch->mvArchNeg ;
		mvCste = myTarch->mvCste ;
	}
	else
		throw cRegArchError("wrong conditional variance class") ;
}

double cTarch::ComputeVar(int theDate, const cRegArchValue& theValue) const
{
int myp = (int)mvArchPos.GetSize() ;
double myRes = mvCste ;
	for (register int i = 1 ; i <= MIN(myp, theDate) ; i++)
		if (theValue.mUt[theDate-i] > 0)
			myRes += mvArchPos[i-1] * theValue.mUt[theDate-i] * theValue.mUt[theDate-i] ;
		else
			myRes += mvArchNeg[i-1] * theValue.mUt[theDate-i] * theValue.mUt[theDate-i] ;

	return myRes ;
}


uint cTarch::GetNParam(void) const
{
	return 1 + 2*mvArchPos.GetSize() ;
}


uint cTarch::GetNLags(void) const
{
	return mvArchPos.GetSize() ;
}


void cTarch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = GetNParam() ;
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("wrong size") ;
	theDestVect[theIndex] = mvCste ;
	mvArchPos.SetSubVectorWithThis(theDestVect, theIndex+1) ;
	mvArchNeg.SetSubVectorWithThis(theDestVect, theIndex+1+mvArchPos.GetSize()) ;

}

void cTarch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize() ;
	if (GetNParam() + theIndex > mySize)
		throw cRegArchError("wrong size") ;
	mvCste = theSrcVect[theIndex] ;
	mvArchPos.SetThisWithSubVector(theSrcVect, theIndex+1) ;
	mvArchNeg.SetThisWithSubVector(theSrcVect, theIndex+1+mvArchPos.GetSize()) ;
}

void cTarch::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const
{
int myp = (int)mvArchPos.GetSize() ;
	theGradData.mCurrentGradVar = 0.0L ;
int myBegIndex = (int)theGradData.GetNMeanParam() ;
	theGradData.mCurrentGradVar[myBegIndex] = 1.0 ;
register int i ;
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		if (theValue.mUt[theDate-i] > 0)
			theGradData.mCurrentGradVar[myBegIndex+i] = theValue.mUt[theDate - i]*theValue.mUt[theDate - i] ;
		else
			theGradData.mCurrentGradVar[myBegIndex+myp+i] = theValue.mUt[theDate - i]*theValue.mUt[theDate - i] ;

	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		if (theValue.mUt[theDate-i] > 0)
			theGradData.mCurrentGradVar -= 2.0 * mvArchPos[i-1] * theValue.mUt[theDate - i] * theGradData.mGradMt[i-1] ;
		else
			theGradData.mCurrentGradVar -= 2.0 * mvArchNeg[i-1] * theValue.mUt[theDate - i] * theGradData.mGradMt[i-1] ;

}
