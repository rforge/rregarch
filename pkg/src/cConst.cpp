/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cConst.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cConst.h"
/*!
 \file cAbstCondMean.cpp
 \brief sources for abstract class cConst methods.

 \author Ollivier TARAMASCO
 \date nov-11-2007 - - Last change nov-26-2007
*/

/*!
 * \fn cConst::cConst
 * \brief constructor.
 * \param int theVal: constant value, default 0.0L.
 */

cConst::cConst(double theVal):cAbstCondMean(eConst)
{
	mvConst = theVal ;
	MESS_CREAT("cConst") ;
}

/*!
 * \fn cConst::~cConst
 * \brief destructor. Nothing to do.
 * \param none.
 */
cConst::~cConst()
{
	MESS_DESTR("cConst") ;
}


/*!
 * \fn cConst::Delete
 * \brief Delete. Nothing to do.
 * \param none.
 */
void cConst::Delete(void)
{
	MESS_DESTR("cConst") ;
}
/*!
 * \fn cConst::Print
 * \brief Print the constant.
 * \param ostream&theOut. The stream.
 */
void cConst::Print(ostream& theOut) const
{
	theOut << "Constant=" << mvConst << endl ;
}


/*!
 * \fn cConst::Affect
 * \brief Affect a value to mvConst.
 * \param cDVector& theDVector: mvConst = theDVector[0]
 */
void cConst::Affect(const cDVector& theDVector)
{
	mvConst = theDVector[0] ;
}

/*!
 * \fn cConst::Affect
 * \brief Affect a value to mvConst.
 * \param double theValue: mvConst = theValue
 */

void cConst::Affect(double theValue)
{	mvConst = theValue ;
}

/*!
 * \fn cConst::Affect
 * \brief Affect a value to mvConst.
 * \param cAbstCondMean* theSrc: mvConst = *(cConst *)theValue
 */
void cConst::Affect(cAbstCondMean* theSrc)
{
// theSrc cannot be const due to the use of dynamic_cast
cConst*	myConst = dynamic_cast<cConst *>(theSrc) ;
	mvConst = myConst->mvConst ;
}

/*!
 * \fn cConst::ReAlloc
 * \brief Nothing to do. Never called.
 * \param cDVector& theParam.
 */
void cConst::ReAlloc(const cDVector& theParam)
{
}

/*!
 * \fn cConst::ReAlloc
 * \brief Nothing to do. Never called.
 * \param int theParam, int theNumParam.
 */
void cConst::ReAlloc(uint theParam, uint theNumParam)
{
}

/*!
 * \fn cConst::operator =
 * \brief this = (cConst *)theSrc
 * \param cAbstCondMean &theSrc
 */

cAbstCondMean& cConst::operator =(cAbstCondMean &theSrc)
{
// theSrc cannot be const due to the dynamic_cast
cConst* myConst = dynamic_cast<cConst *>(&theSrc) ;
	if (myConst)
		mvConst = myConst->mvConst ;
	else
		throw cRegArchError("wrong conditional mean class") ;
	return *this ;
}

/*!
 * \fn cConst::ComputeMean
 * \brief Compute conditionnal mean for an const mean model:
 * \param int theDate: compute m[theDate]. m[theDate] = mvConst
 * \param cRegArchValue& theRes: the data. theRes is not update here.
 */

double cConst::ComputeMean(int theDate, const cRegArchValue& theData) const
{
	return mvConst ;
}

uint cConst::GetNParam(void) const
{	return 1 ;
}
uint cConst::GetNLags(void) const
{	return 0 ;
}

void cConst::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
{
	if ((int)theDestVect.GetSize() + 1 < (int)theIndex)
		throw cRegArchError("wrong size") ;
	theDestVect[theIndex] = mvConst ;
}
void cConst::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
{
	if (1 + theIndex > theSrcVect.GetSize())
		throw cRegArchError("wrong size") ;
	mvConst = theSrcVect[theIndex] ;
}

void cConst::ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex, cAbstResiduals* theResids) const
{
	theGradData.mCurrentGradMu[theBegIndex] += 1.0 ;
}
