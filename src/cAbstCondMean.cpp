/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cAbstCondMean.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cAbstCondMean.h"
#include "RegArchMeanInclude.h"

/*!
 \file cAbstCondMean.cpp
 \brief sources for abstract class cAbstCondMean methods.

 \author Ollivier TARAMASCO
 \date dec-18-2006 - - Last change jan-20-2007
*/

/*!
 * \fn ~cAbstCondMean()
 * \brief destructor.
 * \param none.
 * This function has to be changed when adding a new condtional mean type.
 */
cAbstCondMean::~cAbstCondMean()
{
	mvCondMeanType = eUnknown ;
  	MESS_DESTR("cAbstCondMean")
}



/*!
 * \fn template<class T>  static T* TemplateCreateOneCondMean(void)
 * template function used by CreateOneCondMean
 */
template<class T> 
static T* TemplateCreateOneCondMean(void)
{
T*	myCondMean = new T ;
	return myCondMean ;
}

/*!
 * \fn cAbstCondMean* CreateOneCondMean(eCondMeanEnum theType)
 * \brief returns a pointer on a cAbstCondMeanClass.
 * \param theType: type of conditional mean.
 * \par Details.
 * This function has to be changed when adding a new conditional mean type.
 */

cAbstCondMean* CreateOneCondMean(eCondMeanEnum theType)
{
	switch (theType)
	{	
		case eConst :
			return TemplateCreateOneCondMean<cConst>() ;
		break ;
		case eAr :
			return TemplateCreateOneCondMean<cAr>() ;
		break ;
		case eMa :
			return TemplateCreateOneCondMean<cMa>() ;
		break ;
		case eLinReg :
			return TemplateCreateOneCondMean<cLinReg>() ;
		break ;
		case eStdDevInMean :
			return TemplateCreateOneCondMean<cStdDevInMean>() ;
		break ;
		case eVarInMean :
			return TemplateCreateOneCondMean<cVarInMean>() ;
		break ;
		case eUnknown :
		default :
			throw cRegArchError("unknown conditional mean type") ;
		break ;
	}
}


