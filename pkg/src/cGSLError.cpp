/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLError.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2015/12/13                                        
 ***                                                         
 **************************************************************/

#include "cGSLError.h"
/*! 
	\file cGSLError.cpp
	\brief cGSLError functions declaration
*/
/*!
 \fn mvRErrHandler
 \param char* theReason
 \param char* theFile
 \param int theLine
 \param int theGslErrno
 \brief prints the error and exits the program
*/
#ifdef _GSL_
#ifdef _RDLL_
void mvGSLErrHandler(const char* theReason, const char* theFile, int theLine, int theGslErrno)
{
	stringstream err;
	err << theReason << endl << "    at " << theFile << ":" << theLine << " [GSL_ERRNO=" << theGslErrno << "]" << endl;
	error(err.str().c_str());
}
#else
void mvGSLErrHandler(const char* theReason, const char* theFile, int theLine, int theGslErrno)
{
	cerr << theReason << endl << "    at " << theFile << ":" << theLine << " [GSL_ERRNO=" << theGslErrno << "]" << endl;
	exit(1);
}
#endif // _RDLL_
#endif // _GSL_