/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RegArchDef.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _REGARCHDEF_H_
#define _REGARCHDEF_H_
/*!
	\file RegArchDef.h
	\brief Common definitions for all the classes.
	
	\par Details.
	\par 
	uses the STL vector class and standard C++ I/O classes.
	\author Ollivier TARAMASCO 
	\date dec-18-2006
*/

#include <math.h>
#include "cRegArchError.h"
#include "cRegArchStream.h"
#include "cGSLVector.h"
#include "cGSLMatrix.h"
typedef cGSLVector cDVector ;
typedef cGSLMatrix cDMatrix ;

using namespace RegArchStream;

#ifndef MIN
	#define MIN(p, q) ( (p) < (q) ? (p) : (q) ) ///< Definition of MIN if doesn't exist.
#endif // MIN

#ifndef MAX
	#define MAX(p, q) ( (p) > (q) ? (p) : (q) ) ///< Definition of MAX if doesn't exist.
#endif // MAX

#ifndef SIGN
	#define SIGN(p) ( (p) > 0 ? 1 : -1 )
#endif // SIGN

#ifndef PI
#define PI 3.1415926535897931159979634685
#endif //PI

#ifndef SQRT_PI
	#define SQRT_PI 1.7724538509055161039640324816
#endif // SQRT_PI

#ifndef SQRT_2_PI
	#define SQRT_2_PI 2.50662827463100050241576528481 ///< useful value
#endif //SQRT_2_PI

#ifndef LOG_SQRT_2_PI
#define LOG_SQRT_2_PI 0.918938533204672741780329736406
#endif // LOG_SQRT_2_PI

#ifndef LOG_PI
#define LOG_PI 1.1447298858494001638774761886
#endif // LOG_PI

/*!
 *	\enum eCondMeanEnum
 *	\brief different type of conditional means.
 */
typedef enum eCondMeanEnum
{
	eUnknown = 0,
	eConst = 1,
	eAr = 2,
	eMa = 4,
	eLinReg = 8, // + X(t)*beta
	eStdDevInMean=16, // + lambda * Sigma(t)
	eVarInMean=32 // + Lambda * Sigma(t)^2
}eCondMeanEnum ;


/*!
 *	\enum eCondVarEnum
 *	\brief different type of conditional variances.
 */
typedef enum eCondVarEnum
{	eNotKnown = 0,
	eCste = 1,
	eArch=2,
	eGarch=4,
	eEgarch=8,
	eAparch=16,
	eTarch=32
}eCondVarEnum ;

/*!
 *	\enum eDistrTypeEnum
 *	\brief different type of conditional distribution.
 */

typedef enum eDistrTypeEnum
{
	eNormal=1,
	eStudent=2,
	eGed=4, // Generalized error distribution http://en.wikipedia.org/wiki/Exponential_power_distribution
	eSkewT=8	// Skewed Student-t http://cran.r-project.org/doc/packages/skewt.pdf
}eDistrTypeEnum ;

// POUR DEBOGUER
#ifndef MESS_CREAT
	#ifdef _DEBUG1
		#define MESS_CREAT(p) out << "creating " << p << endl ;
		#define MESS_DESTR(p) out << "destructing " << p << endl ;
	#else
		#define MESS_CREAT(p) ///< used for debugging 
		#define MESS_DESTR(p) ///< used for debugging
	#endif //_DEBUG1
#endif //MESS_CREAT



#endif // _REGARCHDEF_H_
