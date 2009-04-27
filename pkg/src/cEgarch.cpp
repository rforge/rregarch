/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cEgarch.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cEgarch.h"

cEgarch::cEgarch(int theNArch, int theNGarch):cAbstCondVar(eEgarch)
{
	mvEspAbsEpsilont = 2/SQRT_2_PI  ; // Bon seulement pour la loi normale
	mvCste = 0.0L ;
	mvArch.ReAlloc(theNArch) ;
	mvGarch.ReAlloc(theNGarch) ;
	mvTeta=0;
	mvGamma=0;
	MESS_CREAT("cEgarch") ;
}

cEgarch::cEgarch(cAbstResiduals* theResiduals, int theNArch, int theNGarch):cAbstCondVar(eEgarch)
{
	if (theResiduals != NULL)
		mvEspAbsEpsilont = theResiduals->ComputeEspAbsEps() ;
	mvCste = 0.0L ;
	mvArch.ReAlloc(theNArch) ;
	mvGarch.ReAlloc(theNGarch) ;
	mvTeta=0;
	mvGamma=0;
	MESS_CREAT("cEgarch") ;
}

cEgarch::~cEgarch()
{
	mvArch.Delete() ;
	mvGarch.Delete() ;
	MESS_DESTR("cEgarch") ;
}

void cEgarch::ReAlloc(int theVal1, int theVal2)
{
	mvArch.ReAlloc(theVal1) ;
	mvGarch.ReAlloc(theVal2) ;
}
void cEgarch::ReAlloc(const cDVector& theParam)
{
	mvArch.ReAlloc((int)theParam[0]) ;
	mvGarch.ReAlloc((int)theParam[1]) ;
}

void cEgarch::Print(ostream& theOut) const
{
	theOut << "EGARCH(" << mvArch.GetSize() << ", " << mvGarch.GetSize() << ") model:" << endl ;
	theOut << "Const=" << mvCste << endl ;
register size_t i ;
	for (i = 0 ; i < mvArch.GetSize() ; i++)
		theOut << "ARCH[" << i+1 << "]=" << mvArch[i] << endl ;
	for (i = 0 ; i < mvGarch.GetSize() ; i++)
		theOut << "GARCH[" << i+1 << "]=" << mvGarch[i] << endl ;
	theOut << "Teta=" << mvTeta << endl ;
	theOut << "Gamma=" << mvGamma << endl ;
}



void cEgarch::Affect(const cDVector& theDVector, int thePlace) 
{
	switch (thePlace)
	{	case 0 :
			mvEspAbsEpsilont = theDVector[0] ;
		break ;
		case 1 :
			mvCste = theDVector[0] ;
		break ;
		case 2 :
			mvArch = theDVector ;
		break ;
		case 3:
			mvGarch = theDVector ;
		case 4:
			mvTeta = theDVector[0];
		default :
			mvGamma = theDVector[0];
		break ;
	}
}

void cEgarch::Affect(double theValue, int thePlace) 
{	switch (thePlace)
{		case 0 :
			mvEspAbsEpsilont = theValue ;
		break ;
		case 1 :
			mvCste = theValue ;
		break ;
		case 2 :
		{	mvArch.ReAlloc(1) ;
			mvArch[0]= theValue ;
		}
		break ;
		case 3 :
		{
			mvGarch.ReAlloc(1);
			mvGarch[0] = theValue ;
		}
		case 4:
			mvTeta = theValue ;
		break ;

		case 5:
			mvGamma = theValue;
		break ;

		default :
		break ;
	}
}

void cEgarch::Affect(cAbstCondVar& theSrc) 
{
cEgarch* myEgarch = dynamic_cast<cEgarch*>(&theSrc) ; 
	if (myEgarch)
	{	mvEspAbsEpsilont = myEgarch->mvEspAbsEpsilont ;
		mvArch = myEgarch->mvArch ;
		mvGarch = myEgarch->mvGarch ;
		mvCste = myEgarch->mvCste ;
		mvTeta = myEgarch->mvTeta ;
		mvGamma = myEgarch->mvGamma ;
	}
}



double cEgarch::ComputeVar(int theDate, const cRegArchValue& theValue) const
{
int myp = (int)mvArch.GetSize(),
	myq = (int)mvGarch.GetSize() ;
double myRes = mvCste ;
	for (register int i = 1 ; i <= MIN(myp, theDate) ; i++)
		myRes += mvArch[i-1] *( mvTeta*theValue.mEpst[theDate-i] + mvGamma * (fabs(theValue.mEpst[theDate-i])- mvEspAbsEpsilont)) ;
	for (register int j = 1 ; j <= MIN(myq, theDate) ; j++)
		myRes += mvGarch[j-1] * log(theValue.mHt[theDate-j]) ;

	return exp(myRes) ;
}

uint cEgarch::GetNParam(void) const 
{
	return mvArch.GetSize() + mvGarch.GetSize() + 3 ;
}

uint cEgarch::GetNLags(void) const
{
	return max(mvArch.GetSize(), mvGarch.GetSize()) ;
}


void cEgarch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = GetNParam(),
	 k = theIndex ;

	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("Wrong size") ;
	theDestVect[k++] = mvCste ;
	mvArch.SetSubVectorWithThis(theDestVect, k) ;
	k += mvArch.GetSize() ;
	mvGarch.SetSubVectorWithThis(theDestVect, k) ;
	k += mvGarch.GetSize() ;
	theDestVect[k++] = mvTeta	;
	theDestVect[k] = mvGamma	;
}

void cEgarch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize(),
	k = theIndex					;
	if (GetNParam() + theIndex > mySize)
		throw cRegArchError("Wrong size") ;
	mvCste = theSrcVect[k++] ;
	mvArch.SetThisWithSubVector(theSrcVect, k) ;
	k += mvArch.GetSize() ;
	mvGarch.SetThisWithSubVector(theSrcVect, k) ;
	k += mvGarch.GetSize() ;
	mvTeta = theSrcVect[k++] ;
	mvGamma = theSrcVect[k] ;
}

void cEgarch::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const
{
int myp = (int)mvArch.GetSize(),
	myq = (int)mvGarch.GetSize(),
	myBegIndex = (int)theGradData.GetNMeanParam() ;
register int i, j ;
	theGradData.mCurrentGradVar = 0.0L ;
// CSTE
	theGradData.mCurrentGradVar[myBegIndex] = 1.0 ;
// ARCH
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		theGradData.mCurrentGradVar[myBegIndex+i] = mvTeta*theValue.mEpst[theDate-i] + mvGamma*(abs(theValue.mEpst[theDate-i]) - mvEspAbsEpsilont) ;
	myBegIndex += myp ;
// GARCH
	for (j = 1 ; j <= MIN(myq, theDate) ; j++)
		theGradData.mCurrentGradVar[myBegIndex+j] = log(theValue.mHt[theDate-j]) ;
	myBegIndex += myq ;
// Teta et Gamma
	for ( i = 1 ; i <= MIN(myp, theDate) ; i++)
	{	theGradData.mCurrentGradVar[myBegIndex+1] += mvArch[i-1] * theValue.mEpst[theDate-i] ;
		theGradData.mCurrentGradVar[myBegIndex+2] += mvArch[i-1] * (fabs(theValue.mEpst[theDate-i]) - mvEspAbsEpsilont) ;
	}

// Et la suite
	for (i = 1 ; i <= MIN(myp, theDate) ; i++)
		theGradData.mCurrentGradVar += mvArch[i-1]*
		(mvTeta + mvGamma*SIGN(theValue.mEpst[theDate-i])) 
			* theGradData.mGradEpst[i-1] ;

	for (j = 1 ; j <= MIN(myq, theDate) ; j++)
		theGradData.mCurrentGradVar += mvGarch[j-1] / theValue.mHt[theDate-j] * theGradData.mGradHt[j-1] ;

	// Et maintenant le gradient par rapport au(x) param�tre(s) du r�sidu

int myNLawParam = (int)theGradData.GetNLawParam() ;
	if (myNLawParam > 0)
	{
	double myAux = -mvGamma * Sum(mvArch) ;
	cDVector myAuxGrad(myNLawParam) ;

		theResiduals->ComputeGradBetaEspAbsEps(myAuxGrad) ;
		myBegIndex = theGradData.GetNParam() - myNLawParam ;
		for (int i = 0 ; i < myNLawParam ; i++)
			theGradData.mCurrentGradVar[myBegIndex+i] += myAuxGrad[i]*myAux ;
	}

// On a calcul�  grad Nu = grad(Log h), il faut calculer grad h	
	
	theGradData.mCurrentGradVar *= theValue.mHt[theDate] ; 
}

void cEgarch::SetEspAbsEps(double theEspAbsEps)
{
	mvEspAbsEpsilont = theEspAbsEps ;
}


