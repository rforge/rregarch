/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cAparch.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cAparch.h"
cAparch::cAparch(int theNArch, int theNGarch):cAbstCondVar(eAparch)
{
	mvCste = 0.0L ;
	mvDelta = 0.0L ;
	mvArch.ReAlloc(theNArch) ;
	mvGamma.ReAlloc(theNArch) ;
	mvGarch.ReAlloc(theNGarch) ;
	MESS_CREAT("cAparch") ;
}

cAparch::~cAparch()
{
	mvArch.Delete() ;
	mvGamma.Delete() ;
	mvGarch.Delete() ;
	MESS_DESTR("cAparch") ;
}

void cAparch::Delete(void)
{
	mvArch.Delete() ;
	mvGamma.Delete() ;
	mvGarch.Delete() ;
}

void cAparch::Print(ostream& theOut) const
{
	theOut << "APARCH(" << mvArch.GetSize() << ", " << mvGarch.GetSize() << ") model:" << endl ;
	theOut << "Const=" << mvCste << endl ;
	theOut << "Delta=" << mvDelta << endl ;
register uint i ;
	for (i = 0 ; i < mvArch.GetSize() ; i++)
		theOut << "Arch[" << i+1 << "]=" << mvArch[i] << endl ;
	for (i = 0 ; i < mvGamma.GetSize() ; i++)
		theOut << "Gamma[" << i+1 << "]=" << mvGamma[i] << endl ;
	for (i = 0 ; i < mvGarch.GetSize() ; i++)
		theOut << "Garch[" << i+1 << "]=" << mvGarch[i] << endl ;
}

void cAparch::ReAlloc(int theNArch, int theNGarch)
{
	mvArch.ReAlloc(theNArch) ;
	mvGamma.ReAlloc(theNArch) ;
	mvGarch.ReAlloc(theNGarch) ;
}

	
void cAparch::ReAlloc(const cDVector& theParam)
{
	mvArch.ReAlloc((int)theParam[0]) ;
	mvGamma.ReAlloc((int)theParam[0]) ;
	mvGarch.ReAlloc((int)theParam[1]) ;
}

void cAparch::Affect(const cDVector& theDVector, int thePlace) 
{
	switch (thePlace)
	{	case 0 :
			mvCste = theDVector[0] ;
		break ;
		case 1 :
			mvDelta = theDVector[0] ;
		break ;
		case 2:
			mvArch = theDVector ;
		case 3:
			mvGamma = theDVector;
		case 4 :
			mvGarch = theDVector;
		break ;
	}
}

void cAparch::Affect(double theValue, int thePlace) 
{	switch (thePlace)
	{	
		case 0 :
			mvCste = theValue ;
		break ;
		case 1 :
			mvDelta = theValue ;
		break ;
		case 2 :
		{	mvArch.ReAlloc(1);
			mvArch[0] = theValue ;
		}
		case 3 :
		{	mvGamma.ReAlloc(1);
			mvGamma[0] = theValue ;
		}
		default:
		{	mvGarch.ReAlloc(1);
			mvGarch[0] = theValue ;
		}
		break ;
	}
}


void cAparch::Affect(cAbstCondVar& theSrc) 
{
cAparch* myAparch = (cAparch*)(&theSrc) ;
	if (myAparch)
	{	
		mvCste = myAparch->mvCste ;
		mvDelta = myAparch->mvDelta ;
		mvArch = myAparch->mvArch ;
		mvGamma = myAparch->mvGamma ;
		mvGarch = myAparch->mvGarch ;
	}
}


double cAparch::ComputeVar(int theDate, const cRegArchValue& theValue) const
{
int myp = (int)mvArch.GetSize() ;
int	myq = (int)mvGarch.GetSize() ;

double	myRes = mvCste,
		myTemp = 0.0,
		myDeltaDiv2 = mvDelta/2.0 ;
	
	for (register int i = 1 ; i <= MIN(myp, theDate) ; i++)
	{	myTemp = abs(theValue.mUt[theDate-i]) - mvGamma[i-1] * theValue.mUt[theDate-i];
		myRes += mvArch[i-1] * pow(myTemp, mvDelta) ;
	}

	for (register int i = 1 ; i <= MIN(myq, theDate) ; i++)
		myRes += mvGarch[i-1] * pow(theValue.mHt[theDate-i], myDeltaDiv2) ;

	return pow(myRes, 1.0/myDeltaDiv2) ;
}


uint cAparch::GetNParam(void) const
{
	return (2*(int)mvArch.GetSize() + (int)mvGarch.GetSize() + 2) ;
}

uint cAparch::GetNLags(void) const
{
	return MAX(mvArch.GetSize(), mvGarch.GetSize()) ;
}


void cAparch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint	mySize = GetNParam(),
		myIndex = theIndex		;
	
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("wrong size") ;
	theDestVect[myIndex++] = mvCste ;
	theDestVect[myIndex++] = mvDelta ;
	mvArch.SetSubVectorWithThis(theDestVect, myIndex) ;
	myIndex += mvArch.GetSize() ;
	mvGamma.SetSubVectorWithThis(theDestVect, myIndex) ;
	myIndex += mvGamma.GetSize() ;
	mvGarch.SetSubVectorWithThis(theDestVect, myIndex) ;
}

void cAparch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{uint	mySize = theSrcVect.GetSize(),
		myIndex = theIndex ;
	if (GetNParam() + theIndex > mySize)
		throw cRegArchError("wrong size") ;
	mvCste = theSrcVect[myIndex++] ;
	mvDelta = theSrcVect[myIndex++] ;
	mvArch.SetThisWithSubVector(theSrcVect,myIndex) ;
	myIndex += mvArch.GetSize() ;
	mvGamma.SetThisWithSubVector(theSrcVect,myIndex) ;
	myIndex += mvGamma.GetSize() ;
	mvGarch.SetThisWithSubVector(theSrcVect,myIndex) ;
}

void cAparch::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const
{
int myp = (int)mvArch.GetSize(),
	myq = (int)mvGarch.GetSize()	;
	theGradData.mCurrentGradVar = 0.0L ;
int myBegIndex = (int)theGradData.GetNMeanParam() ;
double myDeltaDiv2 = mvDelta/2.0 ;
	
/* derivative with respect to the constant */
	theGradData.mCurrentGradVar[myBegIndex++] = 1.0 ;
register int i ;

/* derivative with respect to Delta */
	theGradData.mCurrentGradVar[myBegIndex] = 0.0 ;
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
	{	
	double	myTemp1 = abs(theValue.mUt[theDate-i]) - mvGamma[i-1]*theValue.mUt[theDate-i],
			myTemp2 = pow(myTemp1, mvDelta) ;
		theGradData.mCurrentGradVar[myBegIndex] += mvArch[i-1]* log(myTemp1) * myTemp2 ;
	}
	for (i = 1 ; i <= MIN(myq, theDate) ; i++)
	{	
	double	myTemp1 = pow(theValue.mHt[theDate-i], myDeltaDiv2) ;
		theGradData.mCurrentGradVar[myBegIndex] += mvGarch[i-1] * myTemp1 * log(theValue.mHt[theDate-i])/2.0 ;
	}

/* derivative with respect to Arch */
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
	{	
	double	myTemp1 = abs(theValue.mUt[theDate-i]) - mvGamma[i-1]*theValue.mUt[theDate-i],
			myTemp2 = pow(myTemp1, mvDelta) ;
		theGradData.mCurrentGradVar[myBegIndex+i] = myTemp2 ;
	}

/* derivative with respect to Gamma */
	myBegIndex += myp ;
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
	{	
	double	myTemp1 = abs(theValue.mUt[theDate-i]) - mvGamma[i-1]*theValue.mUt[theDate-i],
			myTemp2 = pow(myTemp1, mvDelta) ;
		theGradData.mCurrentGradVar[myBegIndex+i] = -mvArch[i-1] * mvDelta * theValue.mUt[theDate-i] * myTemp2/myTemp1 ;
	}

/* derivative with respect to Garch */
	myBegIndex += myp ;
	for (i = 1 ; i <= MIN(myq, theDate) ; i++)
		theGradData.mCurrentGradVar[myBegIndex+i] = pow(theValue.mHt[theDate-i], myDeltaDiv2) ;
	
/* Need now to add the derivatives with respect to u(t-i) and h(t-j) */
	for ( i = 1 ; i <= MIN(myp, theDate) ; i++)
	{
	double myTemp1 = abs(theValue.mUt[theDate-i])/theValue.mUt[theDate-i] - mvGamma[i-1],
			myTemp2 = pow(myTemp1, mvDelta-1) ;
	theGradData.mCurrentGradVar -= mvArch[i-1] * mvDelta * myTemp1 * theGradData.mGradMt[i-1] ; 
	}
	
	for ( i = 1 ; i <= MIN(myq, theDate) ; i++)
	{
	double myTemp1 = mvGarch[i-1] * myDeltaDiv2 * pow(theValue.mHt[theDate-i], myDeltaDiv2 - 1.0) ;
		theGradData.mCurrentGradVar += myTemp1 * theGradData.mGradHt[i-1] ; 
	}

	/* we computed d(ht^Delta/2)/dTheta, we need to compute dht.dTheta */
	myBegIndex = (int)theGradData.GetNMeanParam() + 1 ; // We get the index of Delta
double myAux = theGradData.mCurrentGradVar[myBegIndex] ;
	/* Correct formula for all parameters except Delta */
double myTemp = pow(theValue.mHt[theDate], myDeltaDiv2-1) ;
	theGradData.mCurrentGradVar /= myDeltaDiv2 * myTemp  ;
	/* For Delta */
	theGradData.mCurrentGradVar[myBegIndex] = (myAux - 0.5*log(theValue.mHt[theDate]) * myTemp * theValue.mHt[theDate])/(myDeltaDiv2 * myTemp) ;
}

