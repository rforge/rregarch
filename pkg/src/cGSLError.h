/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLError.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2015/12/13                                        
 ***                                                         
 **************************************************************/

#ifdef _GSL_
#ifdef _RDLL_
#include <sstream>
#include <R.h>
#endif //_RDLL_

#include "RegArchDef.h"
#include "gsl/gsl_errno.h"

static gsl_error_handler_t mvGSLErrHandler;
static gsl_error_handler_t* mvPrevErrHandler = gsl_set_error_handler(mvGSLErrHandler);
#endif //_GSL_