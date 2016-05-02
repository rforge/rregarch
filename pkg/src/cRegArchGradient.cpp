/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchGradient.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cRegArchParam.h"
#include "cRegArchGradient.h"

cRegArchGradient::cRegArchGradient(uint theNPast, uint theNMeanParam, uint theNVarParam, uint theNLawParam)
{
	mvNPast = theNPast ;
	mGradHt = new cDVector[theNPast] ;
	mGradMt = new cDVector[theNPast] ;
	mGradEpst = new cDVector[theNPast] ;
	mvNParam = theNMeanParam + theNVarParam + theNLawParam ;
	mvNMeanParam = theNMeanParam ;
	mvNVarParam = theNVarParam ;
	mvNLawParam = theNLawParam ;
	for (register uint i = 0 ; i < theNPast ; i++)
	{	mGradHt[i].ReAlloc(mvNParam) ;
		mGradMt[i].ReAlloc(mvNParam) ;
		mGradEpst[i].ReAlloc(mvNParam) ;
	}
	mCurrentGradVar.ReAlloc(mvNParam) ;
	mCurrentGradSigma.ReAlloc(mvNParam) ;
	mCurrentGradMu.ReAlloc(mvNParam) ;
	mCurrentGradDens.ReAlloc(mvNLawParam + 1) ;
	mCurrentGradEps.ReAlloc(mvNParam) ;
}

cRegArchGradient::cRegArchGradient(cRegArchParam* theParam)
{
	mvNPast = mvNParam = 0 ;
	if (theParam != NULL)
	{	mvNPast = theParam->GetNLags() ;
		if ( theParam->mMean != NULL)
			mvNMeanParam = theParam->mMean->GetNParam() ;
		else
			mvNMeanParam = 0 ;
		mvNVarParam = theParam->mVar->GetNParam() ;
		mvNLawParam = theParam->mResids->GetNParam() ;
		mvNParam = mvNMeanParam + mvNVarParam + mvNLawParam ;
	}
	mGradHt = new cDVector[mvNPast] ;
	mGradMt = new cDVector[mvNPast] ;
	mGradEpst = new cDVector[mvNPast] ;
	for (register uint i = 0 ; i < mvNPast ; i++)
	{	mGradHt[i].ReAlloc(mvNParam) ;
		mGradMt[i].ReAlloc(mvNParam) ;
		mGradEpst[i].ReAlloc(mvNParam) ;
	}
	mCurrentGradVar.ReAlloc(mvNParam) ;
	mCurrentGradSigma.ReAlloc(mvNParam) ;
	mCurrentGradMu.ReAlloc(mvNParam) ;
	mCurrentGradDens.ReAlloc(mvNLawParam + 1) ;
	mCurrentGradEps.ReAlloc(mvNParam) ;
}


cRegArchGradient::~cRegArchGradient()
{
	for (register uint i = 0 ; i < mvNPast ; i++)
	{	mGradHt[i].Delete() ;
		mGradMt[i].Delete() ;
		mGradEpst[i].Delete() ;
	}
	delete [] mGradHt ;
	delete [] mGradMt ;
	delete [] mGradEpst ;
	mvNPast = 0 ;
	mCurrentGradVar.Delete() ;
	mCurrentGradSigma.Delete() ;
	mCurrentGradMu.Delete() ;
	mCurrentGradDens.Delete() ;
	mCurrentGradEps.Delete() ;
	mvNMeanParam =  mvNVarParam = mvNLawParam = mvNParam = 0 ;
}

void cRegArchGradient::Delete(void)
{
	for (register uint i = 0 ; i < mvNPast ; i++)
	{	mGradHt[i].Delete() ;
		mGradMt[i].Delete() ;
		mGradEpst[i].Delete() ;
	}
	delete [] mGradHt ;
	delete [] mGradMt ;
	delete [] mGradEpst ;
	mvNPast = 0 ;
	mCurrentGradVar.Delete() ;
	mCurrentGradSigma.Delete() ;
	mCurrentGradMu.Delete() ;
	mCurrentGradDens.Delete() ;
	mCurrentGradEps.Delete() ;
	mvNMeanParam =  mvNVarParam = mvNLawParam = mvNParam = 0 ;
}

void cRegArchGradient::ReAlloc(uint theNPast, uint theNMeanParam, uint theNVarParam, uint theNLawParam) 
{
	Delete() ;
	mvNPast = theNPast ;
	mGradHt = new cDVector[theNPast] ;
	mGradMt = new cDVector[theNPast] ;
	mGradEpst = new cDVector[theNPast] ;
	mvNParam = theNMeanParam + theNVarParam + theNLawParam ;
	mvNMeanParam = theNMeanParam ;
	mvNVarParam = theNVarParam ;
	mvNLawParam = theNLawParam ;
	for (register uint i = 0 ; i < theNPast ; i++)
	{	mGradHt[i].ReAlloc(mvNParam) ;
		mGradMt[i].ReAlloc(mvNParam) ;
		mGradEpst[i].ReAlloc(mvNParam) ;
	}
	mCurrentGradVar.ReAlloc(mvNParam) ;
	mCurrentGradSigma.ReAlloc(mvNParam) ;
	mCurrentGradMu.ReAlloc(mvNParam) ;
	mCurrentGradDens.ReAlloc(mvNLawParam + 1) ;
	mCurrentGradEps.ReAlloc(mvNParam) ;
}

void cRegArchGradient::ReAlloc(cRegArchParam* theParam)
{
	mvNPast = mvNParam = 0 ;
	if (theParam != NULL)
	{	mvNPast = theParam->GetNLags() ;
		mvNMeanParam = theParam->mMean->GetNParam() ;
		mvNVarParam = theParam->mVar->GetNParam() ;
		mvNLawParam = theParam->mResids->GetNParam() ;
		mvNParam = mvNMeanParam + mvNVarParam + mvNLawParam ;
	}
	mGradHt = new cDVector[mvNPast] ;
	mGradMt = new cDVector[mvNPast] ;
	mGradEpst = new cDVector[mvNPast] ;
	for (register uint i = 0 ; i < mvNPast ; i++)
	{	mGradHt[i].ReAlloc(mvNParam) ;
		mGradMt[i].ReAlloc(mvNParam) ;
		mGradEpst[i].ReAlloc(mvNParam) ;
	}
	mCurrentGradVar.ReAlloc(mvNParam) ;
	mCurrentGradSigma.ReAlloc(mvNParam) ;
	mCurrentGradMu.ReAlloc(mvNParam) ;
	mCurrentGradDens.ReAlloc(mvNLawParam + 1) ;
	mCurrentGradEps.ReAlloc(mvNParam) ;
}

uint cRegArchGradient::GetNPast(void)
{
	return mvNPast ;
}

uint cRegArchGradient::GetNParam(void)
{
	return mvNParam ;
}

uint cRegArchGradient::GetNMeanParam(void)
{
	return mvNMeanParam ;
}

uint cRegArchGradient::GetNVarParam(void)
{
	return mvNVarParam ;
}

uint cRegArchGradient::GetNLawParam(void)
{
	return mvNLawParam ;
}

void cRegArchGradient::Push(void)
{
	for (register int i = (int)mvNPast - 1 ; i > 0 ; i--)
	{	mGradHt[i] = mGradHt[i-1] ;
		mGradMt[i] = mGradMt[i-1] ;
		mGradEpst[i] = mGradEpst[i-1] ;
	}
}

void cRegArchGradient::Update(void)
{
	if (mvNPast > 0)
	{	Push() ;
		mGradMt[0] = mCurrentGradMu  ;
		mGradHt[0] = mCurrentGradVar ;
		mGradEpst[0] = mCurrentGradEps;
	}
}
