/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cRegArchParam.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cRegArchParam.h"

cRegArchParam::cRegArchParam(cCondMean* theMean, cAbstCondVar* theVar, const cAbstResiduals* theResiduals)
// theMean and theVar cannot be const due to the use of AddMean and AddVar
{	mMean = NULL ;
	mVar = NULL ;
	mResids = NULL ;
	if (theMean != NULL)
		AddMean(*theMean) ;
	if (theVar != NULL)
		AddVar(*theVar) ;
	if (theResiduals != NULL)
		AddResid(*theResiduals) ;

 	MESS_CREAT("cRegArchParam") ;
}
cRegArchParam::cRegArchParam(const cRegArchParam* theParam)
{
	mMean = NULL ;
	mVar = NULL ;
	mResids = NULL ;
	if (theParam != NULL)
	{	AddMean(*(theParam->mMean)) ;
		AddVar(*(theParam->mVar)) ;
		AddResid(theParam->mResids->GetDistrType(), &(theParam->mResids->mLawParam), theParam->mResids->GetForSimul()) ;
	}
 	MESS_CREAT("cRegArchParam") ;
}

cRegArchParam::~cRegArchParam()
{
	if (mMean != NULL)
	{	mMean->Delete() ;
		delete mMean ;
	}
	if (mVar != NULL)
		delete mVar ;
	if (mResids != NULL)
		delete mResids ;
	MESS_DESTR("cRegArchParam") ;
}


void cRegArchParam::AddMean(cCondMean& theCondMean)
// theCondMean cannot be const due to the use of operator=
{
	if (mMean == NULL)
		mMean = new cCondMean(theCondMean) ;
	else
		*mMean = theCondMean ;
}

void cRegArchParam::AddOneMean(cAbstCondMean& theOneMean)
// theOneMean cannot be const due to the use of AffectOneMean
{
int myWhere ;
	if (mMean == NULL)
	{	mMean = new cCondMean(1) ;
		myWhere = 0 ;
	}
	else
	{	myWhere = (int)mMean->GetSize() ;
		mMean->ReAlloc(myWhere+1) ;
	}
	mMean->AffectOneMean(myWhere, &theOneMean) ;
}
void cRegArchParam::PrintMean(ostream& theOut) const
{
	if (mMean != NULL)
		mMean->Print(theOut) ;
}

void cRegArchParam::AddVar(cAbstCondVar& theCondVar)
{
eCondVarEnum myCondVarType = theCondVar.GetCondVarType() ;
	mVar = CreateOneCondVar(myCondVarType) ;
	mVar->Affect(theCondVar) ;
}


void cRegArchParam::PrintVar(ostream& theOut) const
{
	mVar->Print(theOut) ;
}

void cRegArchParam::AddResid(eDistrTypeEnum theDistrType, const cDVector* theLawParam, bool theForSimul)
{
	if (mResids != NULL)
		delete mResids ;

	mResids = CreateOneCondResiduals(theDistrType, theLawParam, theForSimul) ;
}
void cRegArchParam::AddResid(const cAbstResiduals& theCondResiduals)
{
	AddResid(theCondResiduals.GetDistrType(), &theCondResiduals.mLawParam, theCondResiduals.GetForSimul()) ;
}


void cRegArchParam::PrintResiduals(std::ostream &theOut) const
{
	mResids->Print(theOut) ;
}

void cRegArchParam::PrintParam(std::ostream &theOut) const
{
	theOut << "Regression with ARCH type residuals parameters:" << endl ;
	theOut << "-----------------------------------------------" << endl ;
	PrintResiduals(theOut) ;
	theOut << endl ;
	PrintMean(theOut) ;
	theOut << endl ;
	theOut << "Conditional variance parameters:" << endl ;
	theOut << "--------------------------------" << endl ;
	PrintVar(theOut) ;
	theOut << endl ;
}


uint cRegArchParam::GetNParam(void) const
{
uint myRes = 0 ;
	if (mMean != NULL)
		myRes = mMean->GetNParam() ;
	myRes +=  mVar->GetNParam() + mResids->GetNParam() ;
return myRes ;
}

uint cRegArchParam::GetNLags(void) const
{
uint myRes = 0 ;
	if (mMean != NULL)
		myRes = mMean->GetNLags() ;
	return(MAX(myRes, mVar->GetNLags())) ;
}

void cRegArchParam::RegArchParamToVector(cDVector& theDestVect) const
{
uint myIndex = 0 ;
	if (mMean != NULL)
	{	mMean->RegArchParamToVector(theDestVect, myIndex) ;
		myIndex += mMean->GetNParam() ;
	}
	mVar->RegArchParamToVector(theDestVect, myIndex) ;
	myIndex += mVar->GetNParam() ;
	mResids->RegArchParamToVector(theDestVect, myIndex) ;
}

void cRegArchParam::VectorToRegArchParam(const cDVector& theSrcParam)
{
uint myIndex = 0 ;
	if (mMean != NULL)
	{	mMean->VectorToRegArchParam(theSrcParam, myIndex) ;
		myIndex += mMean->GetNParam() ;
	}
	mVar->VectorToRegArchParam(theSrcParam, myIndex) ;
	myIndex += mVar->GetNParam() ;
	mResids->VectorToRegArchParam(theSrcParam, myIndex) ;

	if ((mVar->GetCondVarType() == eEgarch) && (mResids->GetNParam() > 0))
	{	
	cEgarch* myVar = dynamic_cast<cEgarch *>(mVar) ;
		if (myVar != NULL)
		{	
		double myAux = mResids->ComputeEspAbsEps() ;
			myVar->SetEspAbsEps(myAux) ;
		}
	}
}
