/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cRegArchError.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cRegArchError.h"
/*! 
	\file cRegarchError.cpp
	\brief cRegArchError class functions declaration
*/
/*!
 \fn cRegArchError
 \param char* theMess
 \brief prints theMess and exits program
*/
#ifdef _RDLL_
cRegArchError::cRegArchError(char* theMess)
{
	error(theMess) ;
}
#else
cRegArchError::cRegArchError(const string& theMess)
{
	if (theMess.length() != 0) 
		cout << theMess.c_str() << endl ;
	exit(0) ;
}
#endif _RDLL_

