/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cAr.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cAr.h"
/*!
 \file cAr.cpp
 \brief sources for class cAr methods.

 \author Ollivier TARAMASCO
 \date dec-18-2006 - Last change jan-30-2007
*/

/*!
 * \fn cAr::cAr
 * \brief constructor.
 * \param int theNAr: number of lags.
 */

cAr::cAr(int theNAr):cAbstCondMean(eAr)
{
	mvAr.ReAlloc(theNAr) ;
	MESS_CREAT("cAR") ;
}

/*!
 * \fn cAr::~cAr
 * \brief destructor.
 * \param none.
 */
cAr::~cAr()
{
	mvAr.Delete() ;
	MESS_DESTR("cAR") ;
}

void cAr::Delete(void)
{
	mvAr.Delete() ;
	MESS_DESTR("cAR") ;
}

/*!
 * \fn cAr::Print
 * \brief destructor.
 * \param ostream& theOut: the output stream, default out.
 */
void cAr::Print(ostream& theOut) const
{
	for (register uint i = 0 ; i < mvAr.GetSize() ; i++)
		theOut << "AR[" << i+1 << "]=" << mvAr[i] << endl ;
}


/*!
 * \fn cAr::Affect
 * \brief Fill mvAr.
 * \param cDVector& theDVector: mvAr = theDVector.
 */
void cAr::Affect(const cDVector& theDVector)
{
	mvAr = theDVector ;
}

/*!
 * \fn cAr::Affect
 * \brief Fill mvAr.
 * \param double theValue: mvAr[0] = theValue. mvAr is resized.
 */
void cAr::Affect(double theValue)
{
	mvAr.ReAlloc(1, theValue) ;
}

/*!
 * \fn cAr::Affect
 * \brief Fill mvAr.
 * \param int theIndex, double theValue: mvAr[theIndex] = theValue.
 */
void cAr::Affect(int theIndex, double theValue)
{
	if (theIndex < (int)mvAr.GetSize())
		mvAr[theIndex] = theValue ;
	else
		throw cRegArchError("bad index") ;
}

/*!
 * \fn cAr::Affect
 * \brief Fill mvAr.
 * \param cAbstCondMean* theSrc: mvAr = (cAr *)theSrc.
 */

void cAr::Affect(cAbstCondMean* theSrc)
{
// theSrc cannot be const due to the dynamic cast
cAr* myAr = dynamic_cast<cAr*>(theSrc) ;
	if (myAr)
		mvAr = myAr->mvAr ;
}

/*!
 * \fn cAr::ReAlloc
 * \brief ReAlloc mvAr.
 * \param cDVector& theParam: size of mvAr = (int)theParam[0]
 */

void cAr::ReAlloc(const cDVector& theParam)
{
	mvAr.ReAlloc((uint)theParam[0]) ;
}

/*!
 * \fn ReAlloc
 * \brief ReAlloc mvAr.
 * \param uint theParam, uint theNumParam: size of mvAr = (int)theParam[0]. theNumParam is not used for cAR Class.
 */
void cAr::ReAlloc(uint theParam, uint theNumParam)
{
	mvAr.ReAlloc(theParam) ;
}

/*!
 * \fn cAr::operator =
 * \brief redefine operator = for cAr Class
 * \param cAbstCondMean &theSrc: *this = (cAr *)theSrc
 */

cAbstCondMean& cAr::operator =(cAbstCondMean &theSrc)
// theSrc cannot be const due to the dynamic_cast
{
cAr* myAr = dynamic_cast<cAr *>(&theSrc) ;
	if (myAr)
		mvAr = myAr->mvAr ;
	else
		throw cRegArchError("wrong conditional mean class") ;
	return *this ;
}

/*!
 * \fn cAr::ComputeMean
 * \brief Compute conditionnal mean for an AR model
 * \param int theDate: compute m[theDate]
 * \param cRegArchValue& theRes: the data. theRes is not update here.
 */
double cAr::ComputeMean(int theDate, const cRegArchValue& theData) const
{
int myp = (int)mvAr.GetSize() ;

double myRes = 0.0 ;
	for (register int i = 1 ; i <= MIN(myp, theDate) ; i++)
		myRes += mvAr[i-1] * theData.mYt[theDate-i] ;
	return myRes ;
}

uint cAr::GetNParam(void) const
{
	return mvAr.GetSize() ;
}
uint cAr::GetNLags(void) const
{
	return 0 ;
}

void cAr::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
uint mySize = mvAr.GetSize() ;
	if (theDestVect.GetSize() < mySize + theIndex)
		throw cRegArchError("wrong size") ;
	mvAr.SetSubVectorWithThis(theDestVect, theIndex) ;
}

void cAr::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
uint mySize = theSrcVect.GetSize() ;
	if (mvAr.GetSize() + theIndex > mySize)
		throw cRegArchError("wrong size") ;
	mvAr.SetThisWithSubVector(theSrcVect, theIndex) ;
}

void cAr::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData,  uint theBegIndex, cAbstResiduals* theResids) const
{
	for (register int i = 1 ; i <= MIN((int)mvAr.GetSize(), theDate) ; i++)
		theGradData.mCurrentGradMu[theBegIndex+i-1] += theValue.mYt[theDate - i] ;
}
