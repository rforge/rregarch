/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cConstCondVar.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cConstCondVar.h"

cConstCondVar::cConstCondVar(double theValue):cAbstCondVar(eCste)
{	mvCste = theValue ;
	MESS_CREAT("cConstCondVar");
}
cConstCondVar::~cConstCondVar()
{	MESS_DESTR("cConstCondVar");
}

void cConstCondVar::Print(ostream& theOut) const
{
	theOut << "Constant variance model:" << endl ;
	theOut << "Const=" << mvCste << endl ;
}
void cConstCondVar::ReAlloc(int theVal1, int theVal2)
{
}
void cConstCondVar::ReAlloc(const cDVector& theParam)
{
}

void cConstCondVar::Affect(const cDVector& thecDVector, int thePlace)
{
	mvCste = thecDVector[0] ;
}

void cConstCondVar::Affect(double theValue, int thePlace)
{
	mvCste = theValue ;
}

void cConstCondVar::Affect(cAbstCondVar& theSrc)
// theAbstCondVar cannot be const due to the dynamic_cast
{
cConstCondVar* myConstVar = dynamic_cast<cConstCondVar*>(&theSrc) ;
	if (myConstVar)
		mvCste = myConstVar->mvCste ;
	else
		throw cRegArchError("wrong conditional variance class") ;
}

double cConstCondVar::ComputeVar(int theDate, const cRegArchValue& theValue) const
{
	return mvCste ;
}


uint cConstCondVar::GetNParam(void) const
{
	return 1 ;
}
uint cConstCondVar::GetNLags(void) const
{
	return 0 ;
}

void cConstCondVar::RegArchParamToVector(cDVector& theDestVect, uint theIndex) 
{
	if (theDestVect.GetSize() < theIndex - 1)
		throw cRegArchError("Wrong size") ;
	theDestVect[theIndex] = mvCste;
}
void cConstCondVar::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
	if (1 + theIndex > theSrcVect.GetSize())
		throw cRegArchError("Wrong size") ;
	mvCste = theSrcVect[theIndex] ;
}

void cConstCondVar::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResids) const
{
	theGradData.mCurrentGradVar[theGradData.GetNMeanParam()] = 1.0 ;
}
