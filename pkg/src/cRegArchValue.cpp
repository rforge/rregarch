/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchValue.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

/*!
 * \file cRegArchValue.cpp
 * \brief declaration of the cRegArchValue class methods.
 * \par Details.
 * 
 * This class is used for computing the conditional mean, variance and
 * residuals for a regression ARCH model.
 *
 * \author Ollivier TARAMASCO
 * \date 2007-nov-22
*/

#include "cRegArchValue.h" 

cRegArchValue::cRegArchValue(uint theSampleSize, cDMatrix* theXt)
{
	if (theSampleSize > 0)
	{	mYt.ReAlloc(theSampleSize) ;
		if ( (theXt == NULL) || (theXt->GetMat() == NULL) )
			ClearMatrix(mXt) ;
		else
			mXt = *theXt ;
		mMt.ReAlloc(theSampleSize) ;
		mHt.ReAlloc(theSampleSize) ;
		mUt.ReAlloc(theSampleSize) ;
		mEpst.ReAlloc(theSampleSize) ;
	}
	else
	{	mYt.Delete();
		ClearMatrix(mXt) ;
		mMt.Delete() ;
		mHt.Delete() ;
		mUt.Delete() ;
		mEpst.Delete() ;
	}
	MESS_CREAT("cRegArchValue") ;
}

void cRegArchValue::PrintValue(ostream& theOut, bool theHeader, char* theSep)
{
int mySize = (int)mYt.GetSize() ;
uint	myNbCol = 0 ;
	if (theHeader)
	{	theOut << "Yt" << theSep ;
		if (mXt.GetNRow() > 0)
		{	myNbCol = mXt.GetNCol() ;
			for (register uint j = 0 ; j < myNbCol ; j++)
				theOut << "Xt[ ," << j+1 << "]" << theSep ;
		}
		theOut << "Mt" << theSep << "Ht" << theSep << "Ut" << theSep << "Epst" << endl ;
	}			
	for (register int t = 0 ; t < mySize ; t++)
	{	theOut << mYt[t] << theSep ;
		for (register uint j = 0 ; j < myNbCol ; j++)
			theOut << mXt[t][j] << theSep ;
		theOut << mMt[t] << theSep << mHt[t] << theSep << mUt[t] << theSep << mEpst[t] << endl ;
	}
}

ostream& operator <<(ostream& theOut, cRegArchValue& theValue)
{
	theValue.PrintValue(theOut) ;
	return theOut ;

}

cRegArchValue::cRegArchValue(cDVector* theYt, cDMatrix* theXt) // Xt T rows, p columns
{
	if (theYt == NULL)
	{	mYt.Delete() ;
		ClearMatrix(mXt) ;
		mMt.Delete() ;
		mHt.Delete() ;
		mUt.Delete() ;
		mEpst.Delete() ;
	}
	else
	{	mYt = *theYt ;
	uint mySampleSize = mYt.GetSize() ;
		mMt.ReAlloc(mySampleSize) ;
		mHt.ReAlloc(mySampleSize) ;
		mUt.ReAlloc(mySampleSize) ;
		mEpst.ReAlloc(mySampleSize) ;		
		if (theXt == NULL)
			ClearMatrix(mXt) ;
		else
			mXt = *theXt ;
	}
	MESS_CREAT("cRegArchValue") ;
}

cRegArchValue::cRegArchValue(const cRegArchValue* theValue)
{
	mYt.ReAlloc(theValue->mYt);
	mXt.ReAlloc(theValue->mXt);
	mMt.ReAlloc(theValue->mMt);
	mHt.ReAlloc(theValue->mHt);
	mUt.ReAlloc(theValue->mUt);
	mEpst.ReAlloc(theValue->mEpst);
	MESS_CREAT("cRegArchValue");
}

cRegArchValue::~cRegArchValue()
{
	mYt.Delete();
	ClearMatrix(mXt) ;
	mMt.Delete() ;
	mHt.Delete() ;
	mUt.Delete() ;
	mEpst.Delete() ;
	MESS_DESTR("cRegArchValue") ;
}
void cRegArchValue::ReAllocValue(uint theSize, bool theDataValueExists)
{
	if (theSize > 0)
	{	if (!theDataValueExists)
		{	mYt.ReAlloc(theSize) ;
			ClearMatrix(mXt) ;
		}
		mMt.ReAlloc(theSize) ;
		mHt.ReAlloc(theSize) ;
		mUt.ReAlloc(theSize) ;
		mEpst.ReAlloc(theSize) ;
	}
	else
	{	mYt.Delete() ;
		ClearMatrix(mXt) ;
		mMt.Delete() ;
		mHt.Delete() ;
		mUt.Delete() ;
		mEpst.Delete() ;
	}
}

void cRegArchValue::ReAllocValue(cDVector& theYt)
{
int mySize = (int)theYt.GetSize() ;
	ClearMatrix(mXt) ;
	if (mySize > 0)
	{	mYt = theYt ;
		mMt.ReAlloc(mySize) ;
		mHt.ReAlloc(mySize) ;
		mUt.ReAlloc(mySize) ;
		mEpst.ReAlloc(mySize) ;
	}
	else
	{	mYt.Delete() ;
		mMt.Delete() ;
		mHt.Delete() ;
		mUt.Delete() ;
		mEpst.Delete() ;
	}
}

void cRegArchValue::ReAllocValue(cDVector& theYt, cDMatrix& theXt) // Xt T rows, p columns
{
uint mySize = theYt.GetSize() ;
	if ( (mySize > 0)&& (mySize == theXt.GetNRow()) )
	{	mYt = theYt ;
		mXt = theXt ;
		mMt.ReAlloc(mySize) ;
		mHt.ReAlloc(mySize) ;
		mUt.ReAlloc(mySize) ;
		mEpst.ReAlloc(mySize) ;
	}
	else
	{	mYt.Delete();
		ClearMatrix(mXt) ;
		mMt.Delete() ;
		mHt.Delete() ;
		mUt.Delete() ;
		mEpst.Delete() ;
		throw cRegArchError("incompatibility beetwen Yt and Xt") ;
	}
}

