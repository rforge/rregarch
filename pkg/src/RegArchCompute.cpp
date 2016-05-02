/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchCompute.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "RegArchCompute.h"
#include <omp.h>
#include <sstream>

void RegArchSimul(uint theNSample, cRegArchParam& theParam, cRegArchValue& theValue)
{
	theParam.mResids->Generate(theNSample, theValue.mEpst) ;
	for (register uint t = 0 ; t < theNSample ; t++)
	{	theValue.mHt[t] = theParam.mVar->ComputeVar(t, theValue) ;
		if (theParam.mMean != NULL)
			theValue.mMt[t] = theParam.mMean->ComputeMean(t, theValue) ;
		theValue.mUt[t] = sqrt(theValue.mHt[t])*theValue.mEpst[t] ;
		theValue.mYt[t] = theValue.mMt[t] + theValue.mUt[t] ;
	}
}

void RegArchSimul(uint theNSample, cRegArchParam& theParam, cDVector& theYt)
{
cRegArchValue myValue(theNSample) ;
	RegArchSimul(theNSample, theParam, myValue) ;
	theYt = myValue.mYt ;
}

double RegArchLLH(cRegArchParam& theParam, cRegArchValue& theValue)
{
int mySize = (int)theValue.mYt.GetSize() ;
double myRes = 0 ;
	theValue.mEpst = theValue.mHt = theValue.mMt = theValue.mUt = 0.0 ;
	for(register int t=0 ; t < mySize ; t++)
	{	theValue.mHt[t] = theParam.mVar->ComputeVar(t, theValue) ;
		if (theParam.mMean != NULL)
			theValue.mMt[t] = theParam.mMean->ComputeMean(t, theValue) ;
		theValue.mUt[t] = theValue.mYt[t] - theValue.mMt[t] ;
		theValue.mEpst[t] = theValue.mUt[t]/sqrt(theValue.mHt[t]) ;
		myRes += -0.5*log(theValue.mHt[t]) + theParam.mResids->LogDensity(theValue.mEpst[t]) ; 
	}
	return myRes ;
}

double RegArchLLH(cRegArchParam& theParam, cDVector* theYt, cDMatrix* theXt) 
{
cRegArchValue myValue(theYt, theXt) ;
	return RegArchLLH(theParam, myValue) ;
}
void RegArchGradLt(int theDate, cRegArchParam& theParam, cRegArchValue& theValue, cRegArchGradient& theGradData, cDVector& theGradlt)
{
	theGradlt = 0.0 ;
	theValue.mHt[theDate] = theParam.mVar->ComputeVar(theDate, theValue) ;
	if (theParam.mMean != NULL)
		theValue.mMt[theDate] = theParam.mMean->ComputeMean(theDate, theValue) ;
	theValue.mUt[theDate] = theValue.mYt[theDate] - theValue.mMt[theDate] ;
double mySigmat = sqrt(theValue.mHt[theDate]) ;
	theValue.mEpst[theDate] = theValue.mUt[theDate]/mySigmat ;
	theParam.mVar->ComputeGrad(theDate, theValue, theGradData, theParam.mResids) ;
	if (theParam.mMean != NULL)
		theParam.mMean->ComputeGrad(theDate, theValue, theGradData, theParam.mResids) ;
	theParam.mResids->ComputeGrad(theDate, theValue, theGradData) ;
	theGradData.mCurrentGradSigma = theGradData.mCurrentGradVar / (2.0 * mySigmat) ;
	theGradData.mCurrentGradEps = -1.0*(theValue.mEpst[theDate] * theGradData.mCurrentGradSigma + theGradData.mCurrentGradMu)/ mySigmat ;
	theGradlt =  (-1.0/mySigmat) * theGradData.mCurrentGradSigma  + theGradData.mCurrentGradDens[0] * theGradData.mCurrentGradEps ;
uint myNLawParam = theGradData.GetNLawParam() ;
uint myIndex = theGradData.GetNMeanParam() + theGradData.GetNVarParam() ;	
	for (register uint i =  1 ; i <= myNLawParam ; i++)
		theGradlt[i+myIndex-1] += theGradData.mCurrentGradDens[i] ;
		// Update
	theGradData.Update() ;
}

void RegArchLtAndGradLt(int theDate, cRegArchParam& theParam, cRegArchValue& theValue, cRegArchGradient& theGradData, double& theLt, cDVector& theGradlt)
{
	theGradlt = 0.0 ;
	theValue.mHt[theDate] = theParam.mVar->ComputeVar(theDate, theValue) ;
	if (theParam.mMean != NULL)
		theValue.mMt[theDate] = theParam.mMean->ComputeMean(theDate, theValue) ;
	theValue.mUt[theDate] = theValue.mYt[theDate] - theValue.mMt[theDate] ;
double mySigmat = sqrt(theValue.mHt[theDate]) ;
	theValue.mEpst[theDate] = theValue.mUt[theDate]/mySigmat ;
	theParam.mVar->ComputeGrad(theDate, theValue, theGradData, theParam.mResids) ;
	if (theParam.mMean != NULL)
		theParam.mMean->ComputeGrad(theDate, theValue, theGradData, theParam.mResids) ;
	theParam.mResids->ComputeGrad(theDate, theValue, theGradData) ;
	theGradData.mCurrentGradSigma = theGradData.mCurrentGradVar / (2.0 * mySigmat) ;
	theGradData.mCurrentGradEps = -1.0*(theValue.mEpst[theDate] * theGradData.mCurrentGradSigma + theGradData.mCurrentGradMu)/ mySigmat ;
	theGradlt =  (-1.0/mySigmat) * theGradData.mCurrentGradSigma  + theGradData.mCurrentGradDens[0] * theGradData.mCurrentGradEps ;
uint myNLawParam = theGradData.GetNLawParam() ;
uint myIndex = theGradData.GetNMeanParam() + theGradData.GetNVarParam() ;	
	for (register uint i =  1 ; i <= myNLawParam ; i++)
		theGradlt[i+myIndex-1] += theGradData.mCurrentGradDens[i] ;
		// Update
	theGradData.Update() ;
	theLt = -0.5*log(theValue.mHt[theDate]) + theParam.mResids->LogDensity(theValue.mEpst[theDate]) ; 
}

void RegArchGradLLH(cRegArchParam& theParam, cRegArchValue& theValue, cDVector& theGradLLH)
{

cRegArchGradient myGradData(&theParam) ;
cDVector myGradlt(myGradData.GetNParam()) ;
	theGradLLH = 0.0L ;
	for (register int t = 0 ; t < (int)theValue.mYt.GetSize() ; t++)
	{	RegArchGradLt(t, theParam, theValue, myGradData, myGradlt) ;
		theGradLLH += myGradlt ;
	}
}

void RegArchLLHAndGradLLH(cRegArchParam& theParam, cRegArchValue& theValue, double& theLLH, cDVector& theGradLLH)
{
cRegArchGradient myGradData(&theParam) ;
cDVector myGradlt(myGradData.GetNParam()) ;
double myLt ;
	theGradLLH = 0.0L ;
	theLLH = 0.0 ;
	for (register int t = 0 ; t < (int)theValue.mYt.GetSize() ; t++)
	{	RegArchLtAndGradLt(t, theParam, theValue, myGradData, myLt, myGradlt) ;
		theGradLLH += myGradlt ;
		theLLH += myLt ;
	}
}


void NumericRegArchGradLLH(cRegArchParam& theParam, cRegArchValue& theValue, cDVector& theGradLLH, double theh)
{
double myLLH0 = RegArchLLH(theParam, theValue) ;
int myNParam = (int)theGradLLH.GetSize() ;
int myNLawParam = (int)theParam.mResids->GetNParam() ;
eCondVarEnum myVarType = theParam.mVar->GetCondVarType() ;

cDVector myVectParam(myNParam), myVect0(myNParam) ;
	
	theParam.RegArchParamToVector(myVectParam) ;
	myVect0 = myVectParam ;
	for (register int i = 0 ; i < myNParam ; i++)
	{
	double myhh = fabs(theh * myVectParam[i]) ;
		if (myhh < MIN_DBLE)
			myhh = theh ;
		myVectParam[i] += myhh ;
		theParam.VectorToRegArchParam(myVectParam) ;

		
	double myLLH1 = RegArchLLH(theParam, theValue) ;
		theGradLLH[i] = (myLLH1 - myLLH0)/myhh ;
		myVectParam[i] -= myhh ;
	}
	theParam.VectorToRegArchParam(myVect0) ;
}

void NumericRegArchHessLLH(cRegArchParam& theParam, cRegArchValue& theValue, cDMatrix& theHessLLH, double theh)
{
int myNParam = (int)theParam.GetNParam() ;
cDVector myGrad0(myNParam), myGradij(myNParam), myVect(myNParam), myVect0(myNParam) ;
	theHessLLH.ReAlloc(myNParam, myNParam) ;
	
	theParam.RegArchParamToVector(myVect) ;
	myVect0 = myVect ;
	RegArchGradLLH(theParam, theValue, myGrad0) ; 	

	for (register int i = 0 ; i < myNParam ; i++)
	{	double myhhi = fabs(theh*myGrad0[i]) ;
			if (myhhi < MIN_DBLE)
				myhhi = theh ;
			myVect[i] += myhhi ;
			theParam.VectorToRegArchParam(myVect) ;
			RegArchGradLLH(theParam, theValue, myGradij) ;
			myVect[i] -= myhhi ;
			for (register int j = 0 ; j < myNParam ; j++)
				theHessLLH[i][j] = (myGradij[j] - myGrad0[j])/myhhi ;
	}
	theParam.VectorToRegArchParam(myVect0) ;
	for (register int i = 0 ; i < myNParam-1 ; i++)
		for (register int j = i+1 ; j < myNParam ; j++)
			theHessLLH[i][j] = theHessLLH[j][i] = (theHessLLH[i][j] + theHessLLH[j][i])/2.0 ;
}		
void AsymptoticCovMat(cRegArchParam& theParam, cRegArchValue& theValue, cDMatrix& theAsymptCov, double theh)
{
int myNParam = (int)theParam.GetNParam() ;
cRegArchGradient myGradData(&theParam) ;
cDVector myGrad0(myNParam), myGradij(myNParam), myVect(myNParam), myVect0(myNParam) ;
	
	theParam.RegArchParamToVector(myVect) ;
	myVect0 = myVect ;
	RegArchGradLLH(theParam, theValue, myGrad0) ; 	
cDMatrix myJ(myNParam, myNParam) ;
	for (register int i = 0 ; i < myNParam ; i++)
	{	double myhhi = fabs(theh*myGrad0[i]) ;
			if (myhhi < MIN_DBLE)
				myhhi = theh ;
			myVect[i] += myhhi ;
			theParam.VectorToRegArchParam(myVect) ;
			RegArchGradLLH(theParam, theValue, myGradij) ;
			myVect[i] -= myhhi ;
			for (register int j = 0 ; j < myNParam ; j++)
				myJ[i][j] = (myGradij[j] - myGrad0[j])/myhhi ;
	}
	theParam.VectorToRegArchParam(myVect0) ;
	for (register int i = 0 ; i < myNParam-1 ; i++)
		for (register int j = i+1 ; j < myNParam ; j++)
			myJ[i][j] = myJ[j][i] = (myJ[i][j] + myJ[j][i])/2.0 ;
cDMatrix myInvJ = Inv(myJ) ;
cDMatrix myI(myNParam, myNParam) ;
	for (register int t = 0 ; t < (int)theValue.mYt.GetSize() ; t++)
	{	RegArchGradLt(t, theParam, theValue, myGradData, myGrad0) ;
		myI += myGrad0 * Transpose(myGrad0) ;
	}
	theAsymptCov.ReAlloc(myNParam, myNParam) ;
	theAsymptCov = myInvJ * myI * myInvJ  ;
}
