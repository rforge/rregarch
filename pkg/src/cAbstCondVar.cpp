/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cAbstCondVar.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cAbstCondVar.h"
#include "RegArchVarInclude.h"

/*!
 * \fn template<class T>  static T* TemplateCreateOneCondVar(void)
 * template function used by CreateOneCondVar
 */
template<class T> 
static T* TemplateCreateOneCondVar(void)
{
T*	myCondVar = new T ;
	return myCondVar ;
}

/*!
 * \fn CreateOneCondVar* CreateOneCondVar(eCondVarEnum theType)
 * \brief returns a pointer on a cAbstCondVar Class.
 * \param theType: type of conditional variance.
 * \par Details.
 * This function has to be changed when adding a new conditional variance type.
 */

cAbstCondVar* CreateOneCondVar(eCondVarEnum theType)
{
	switch (theType)
	{	
		case eCste :
			return TemplateCreateOneCondVar<cConstCondVar>() ;
		break ;
		case eArch :
			return TemplateCreateOneCondVar<cArch>() ;
		break ;
		case eGarch :
			return TemplateCreateOneCondVar<cGarch>() ;
		break ;
		case eEgarch :
			return TemplateCreateOneCondVar<cEgarch>() ;
		break ;
		case eTarch :
			return TemplateCreateOneCondVar<cTarch>() ;
		break ;
		case eAparch :
			return TemplateCreateOneCondVar<cAparch>() ;
		break ;
		case eNotKnown : 
		default :
			throw cRegArchError("unknown conditional variance type") ;
		break ;
	}
}


