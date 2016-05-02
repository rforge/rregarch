/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cCondMean.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cCondMean.h"

cCondMean::cCondMean(uint theNCondMean)
{
	mvNCondMean = theNCondMean ;
	if (theNCondMean > 0)
	{	mvCondMean = new cAbstCondMean*[theNCondMean] ;
		for (register uint i = 0 ; i < mvNCondMean ; i++)
			mvCondMean[i] = (cAbstCondMean *)NULL ;
	}
	else
		mvCondMean = NULL ;

	MESS_CREAT("cCondMean") ;
}

cCondMean::cCondMean(const eCondMeanEnum* theCode, uint theNCondMean)
{
	mvCondMean = NULL;
	ReAlloc(theNCondMean) ;

	for (register uint i = 0 ; i < theNCondMean ; i++)
		AllocOneMean(i, theCode[i]) ;
}

cCondMean::cCondMean(cCondMean& theCondMean)
// theCondMean cannot be const due to the use of operator= on components
{
	mvNCondMean = theCondMean.GetSize() ;
	if (mvNCondMean > 0)
	{	mvCondMean = new cAbstCondMean*[mvNCondMean] ;
		for (register uint i = 0 ; i < mvNCondMean ; i++)
		{
		cAbstCondMean* myMean = theCondMean.GetOneMean(i) ;

			AllocOneMean(i, myMean->GetCondMeanType()) ;
			mvCondMean[i]->Affect(myMean) ;
		}
	}
	else
		mvCondMean = NULL ;
	MESS_CREAT("cCondMean") ;
}

cCondMean::~cCondMean()
{

	Delete() ;
	MESS_DESTR("cCondMean") ;
}

void cCondMean::Delete(void)
{
	if (mvNCondMean > 0)
	{	for (register uint i = 0 ; i < mvNCondMean ; i++)
			if (mvCondMean[i] != NULL)
				delete mvCondMean[i] ;
		delete[] mvCondMean ;
	}
	mvNCondMean = 0 ;
	mvCondMean = NULL ;
}

void cCondMean::AllocOneMean(uint theWhatMean, eCondMeanEnum theCodeType)
{

	mvCondMean[theWhatMean] = CreateOneCondMean(theCodeType) ;
}

cAbstCondMean* cCondMean::GetOneMean(uint theIndex) const
{
	if (theIndex < mvNCondMean)
		return mvCondMean[theIndex] ;
	else
		throw cRegArchError("bad index") ;
}
uint cCondMean::GetSize(void) const
{	return mvNCondMean ;
}

void cCondMean::ReAlloc(uint theNCondMean)
{

cAbstCondMean**	myMean ;

	if (theNCondMean > 0)
		myMean = new cAbstCondMean*[theNCondMean] ;
	else
		myMean = NULL ;
register uint i ;
	if (mvCondMean == NULL)
		mvNCondMean = 0 ;
	for (i = 0 ; i < MIN(theNCondMean, mvNCondMean) ; i++)
		myMean[i] = mvCondMean[i] ; /// adress copy
	for (i = theNCondMean ; i < mvNCondMean ; i++)
		mvCondMean[i]->Delete() ;
	for (i = mvNCondMean ; i < theNCondMean ; i++)
		myMean[i] = (cAbstCondMean *)NULL ;
	mvNCondMean = theNCondMean ;
	delete[] mvCondMean;
	mvCondMean = myMean ;
}

void cCondMean::GetCondMeanType(eCondMeanEnum* theCodeType) const
{
	for (register uint i = 0 ; i < mvNCondMean ; i++)
		theCodeType[i] = mvCondMean[i]->GetCondMeanType()  ;
}
void cCondMean::Print(ostream& theOut) const
{
	theOut << "Conditional mean parameters:" << endl ;
	theOut << "----------------------------" << endl ;
	for (register uint i = 0 ; i < mvNCondMean ; i++)
		mvCondMean[i]->Print(theOut) ;
}

ostream& operator <<(ostream& theOut, const cCondMean& theCondMean)
{
	for (register uint i = 0 ; i < theCondMean.mvNCondMean ; i++)
	{	theCondMean.mvCondMean[i]->Print(theOut) ;
		theOut << endl ;
	}
	return theOut ;
}

cCondMean& cCondMean::operator =(cCondMean& theSrc)
// theSrc cannot be const due to use of operator= on components
{
	Delete() ;
cAbstCondMean** myCondMean ;
	if (theSrc.mvNCondMean > 0)
	{	mvNCondMean = theSrc.mvNCondMean ;
		myCondMean = new cAbstCondMean*[mvNCondMean] ;

		for (register uint i = 0 ; i < mvNCondMean ; i++)
		{
			myCondMean[i] = theSrc.GetOneMean(i)  ;
		}

		mvCondMean = myCondMean ;
	}
	else
		mvCondMean = NULL ;
	return *this ;
}



void cCondMean::AffectOneMean(int theWhatMean, cAbstCondMean* theAbstCondMean)
// theAbsCondMean cannot be const due to operator=
{
	if (mvCondMean[theWhatMean] == NULL)
		AllocOneMean(theWhatMean, theAbstCondMean->GetCondMeanType()) ;

	mvCondMean[theWhatMean]->Affect(theAbstCondMean) ;
}

double cCondMean::ComputeMean(int theDate, const cRegArchValue& theData) const
{
double myMean = 0.0 ;

	for (register uint i = 0 ; i < mvNCondMean ; i++)
		myMean += mvCondMean[i]->ComputeMean(theDate, theData) ;
	return myMean ;
}

uint cCondMean::GetNParam(void) const
{
uint myNParam = 0 ;
	for (register uint i = 0 ; i < mvNCondMean ; i++)
		myNParam += mvCondMean[i]->GetNParam() ;
	return myNParam ;
}

uint cCondMean::GetNLags(void) const
{
uint myNLags = 0 ;
	for (register uint i = 0 ; i < mvNCondMean ; i++)
		myNLags = MAX(myNLags, mvCondMean[i]->GetNLags());
	return myNLags ;
}

void cCondMean::RegArchParamToVector(cDVector& theDestVect, uint theIndex) const
{
uint myIndexCour = theIndex ;
	for (register uint i = 0 ; i < mvNCondMean ; i++)
	{	mvCondMean[i]->RegArchParamToVector(theDestVect, myIndexCour) ;
		myIndexCour += mvCondMean[i]->GetNParam() ;
	}
}

void cCondMean::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint myIndexCour = theIndex ;
	for (register uint i = 0 ; i < mvNCondMean ; i++)
	{	mvCondMean[i]->VectorToRegArchParam(theSrcVect, myIndexCour) ;
		myIndexCour += mvCondMean[i]->GetNParam() ;
	}
}

void cCondMean::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResids) const
{
uint myIndex = 0 ;
	theGradData.mCurrentGradMu = 0.0L ;
	for (register uint i = 0 ; i < mvNCondMean ; i++)
	{	mvCondMean[i]->ComputeGrad(theDate, theValue, theGradData, myIndex, theResids) ;
		myIndex += mvCondMean[i]->GetNParam() ;
	}
}
