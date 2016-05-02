/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchError.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CREGARCHERROR_H_
#define _CREGARCHERROR_H_
/*!
	\file cRegArchError.h
	\brief Header for error class declarations
*/
#ifdef _RDLL_
	#include <R.h>
#else
	#include <cstdlib>
	#include <cstring>
#endif //_RDLL_

#include "cRegArchStream.h"
using namespace RegArchStream;

#ifndef NULL
	#define NULL 0
#endif // NULL

#ifndef uint
	typedef unsigned int uint ;
#endif // uint

/*!
	\class cRegArchError
	\brief Only used to exit program with an output message
*/

class cRegArchError
{
	public :
	#ifdef _RDLL_
		cRegArchError(char* theMess) ;
	#else
		cRegArchError(const string& theMess) ;
	#endif // _RDLL_
} ;

#endif //_CREGARCHERROR_H_

