/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cAbstResiduals.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cAbstResiduals.h"
#include "RegArchResidualsInclude.h"
/*!
 \file cAbstResiduals.cpp
 \brief sources for abstract class cAbstResiduals methods.

 \author Ollivier TARAMASCO
 \date dec-18-2006 - Last change dec-18-2007
*/

/*!
 * \fn cAbstResiduals
 * \brief constructor.
 * \param eDistrTypeEnum theDistr: code for the conditional distribution.
 */
cAbstResiduals::cAbstResiduals(eDistrTypeEnum theDistr, const cDVector* theParam, bool theForSimul)
{
	mvDistr = theDistr ;
	mvForSimul = theForSimul ;
	if (mvForSimul)
#ifndef _GSL_
	GetRNGstate();
#else
	{	//Does not seem to have access to library
		//variable gsl_rng_default
		//gsl_rng_env_setup() ;
		//const gsl_rng_type* myT ;
		//myT = gsl_rng_default ;
		const gsl_rng_type* myT = gsl_rng_env_setup();
		mtR = gsl_rng_alloc(myT) ;
	#ifndef _DEBUG
		gsl_rng_set(mtR, (unsigned long int)time(NULL)) ;
	#else
		gsl_rng_set(mtR, 0) ; // To keep the same simulated serie while testing
	#endif // _DEBUG
	}
	else
		mtR = NULL ;
#endif // _GSL_
	if (theParam != NULL)
		mLawParam = *theParam ;
	MESS_CREAT("cAbstResiduals") ;
}

/*!
 * \fn ~cAbstResiduals
 * \brief destructor.
 * \param eDistrTypeEnum theDistr: code for the conditional distribution.
 */
cAbstResiduals::~cAbstResiduals()
{
	mLawParam.Delete() ;
	if (mvForSimul)
#ifndef _GSL_
	PutRNGstate();
#else		
	gsl_rng_free(mtR) ;
#endif //_GSL_
	MESS_DESTR("cAbstResiduals") ;
}

/*!
 * \fn SetSimul
 * \brief Change for simulation type. Set mtR.
 * \param none
 */
void cAbstResiduals::SetSimul(void)
{
	mvForSimul = true ;
#ifndef _GSL_
	GetRNGstate();
#else
	//Does not seem to have access to library
	//variable gsl_rng_default
	//gsl_rng_env_setup() ;
	//const gsl_rng_type* myT ;
	//myT = gsl_rng_default ;
	const gsl_rng_type* myT = gsl_rng_env_setup();
	mtR = gsl_rng_alloc(myT) ;
#ifndef _DEBUG
	gsl_rng_set(mtR, (unsigned long int)time(NULL)) ;
#else
	gsl_rng_set(mtR, 0) ; // To keep the same simulated serie while testing
#endif // _DEBUG
#endif // _GSL_
}

cAbstResiduals& cAbstResiduals::operator =(const cAbstResiduals& theSrc)
{
	mvDistr = theSrc.mvDistr ;
	mvForSimul = theSrc.mvForSimul ;
#ifdef _GSL_
	*mtR = *(theSrc.mtR) ;
#endif // _GSL_
	mLawParam = theSrc.mLawParam ;
	return *this ;
}
eDistrTypeEnum cAbstResiduals::GetDistrType(void) const
{	return mvDistr ;
}
bool cAbstResiduals::GetForSimul(void) const
{	return mvForSimul ;
}

/*!
 * \fn template<class T>  static T* TemplateCreateOneCondResiduals(void)
 * template function used by CreateOneCondResiduals
 */
template<class T>
static T* TemplateCreateOneCondResiduals(const cDVector* theParam, bool theForSimul)
{
T*	myCondResiduals = new T(theParam, theForSimul) ;
	return myCondResiduals ;
}

/*!
 * \fn cAbstResiduals* CreateOneCondResiduals(eDistrTypeEnum theType)
 * \brief returns a pointer on a cAbstResiduals Class.
 * \param theType: type of conditional residuals.
 * \par Details.
 * This function has to be changed when adding a new conditional residuals type.
 */

cAbstResiduals* CreateOneCondResiduals(eDistrTypeEnum theType, const cDVector* theParam=NULL, bool theForSimul=true)
{
	switch (theType)
	{
		case eNormal :
			return TemplateCreateOneCondResiduals<cNormResiduals>(theParam, theForSimul) ;
		break ;
		case eStudent :
			if (theParam == NULL)
			{
			cDVector myParam = cDVector(1,0.0) ;
				return TemplateCreateOneCondResiduals<cStudentResiduals>(&myParam, theForSimul) ;
			}
			else
				return TemplateCreateOneCondResiduals<cStudentResiduals>(theParam, theForSimul) ;
		break ;
		default :
			throw cRegArchError("unknown conditional distribution type") ;
		break ;
	}
}


