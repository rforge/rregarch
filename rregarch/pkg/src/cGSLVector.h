/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cGSLVector.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _cGSLVector_H_
#define _cGSLVector_H_
/*!
	\file cGSLVector.h
	\brief header for C++ encapsulation of GSL vectors definitions and functions.
	\author Ollivier TARAMASCO 
	\date oct-09-2008
*/

#include <iostream>
#include <ostream>
#include <cmath>
#ifndef _RDLL_
	#include <gsl/gsl_vector.h>
#else
	#include "RGslVectorEquiv.h"
#endif _RDLL_
#include "cRegArchError.h"


#ifndef uint
	typedef unsigned int uint ; 
#endif //uint

// POUR DEBOGUER
#ifndef MESS_CREAT
	#ifdef _DEBUG1
		#define MESS_CREAT(p) std::cout << "creation de " << p << std::endl ;
		#define MESS_DESTR(p) std::cout << "destruction de " << p << std::endl ;
	#else
		#define MESS_CREAT(p) ///< used for debugging 
		#define MESS_DESTR(p) ///< used for debugging
	#endif //_DEBUG1
#endif //MESS_CREAT

class cGSLMatrix ;
/*!
	\brief class cGSLVector
	\par
	1) Encapsulation of the "C" gsl structure gsl_vector
	2) Standard and usefull vector operations declarations
*/	

class cGSLVector
{
private :
		gsl_vector* mvVect ; ///< data
public :
	cGSLVector(int theSize = 0, double theVal = 0.0) ; ///< standard constructor
	cGSLVector(int theSize, double* theVect) ;///< mVect := theVect
	cGSLVector(const gsl_vector* theVect) ;///< mVect := theVect
	cGSLVector(const cGSLVector& theVect) ;///< mVect := theVect
	virtual ~cGSLVector() ;///< std destructor
	double& operator[](int theIndex) const ;///< returns mvect[theIndex]
	uint GetSize(void) const ;///< size of mVect
	gsl_vector* GetGSLVector(void) const ;///< returns mVect
	gsl_vector* GetVector(void) const ; ///< returns mVect
	void Delete(void) ;///< Destructor
	void ReAlloc(int theSize, double theVal=0.0) ;///< Reallocation and initialisation of mVect
	void ReAlloc(int theSize, double* theVect) ;///< Reallocation and initialisation of mVect
	void ReAlloc(const cGSLVector& theVect) ;///< Reallocation and initialisation of mVect
	void ReAlloc(const gsl_vector* theVect) ;///< Reallocation and initialisation of mVect
	cGSLVector& operator =(const cGSLVector& theSrcVect) ; ///< *this = theSrcVect
	cGSLVector& operator =(double theVal) ;///< *this[i] = theVal for all i 
	cGSLVector& operator =(double* theSrcVect) ;///< *this = theSrcVect
	cGSLVector& operator +=(const cGSLVector& theSrcVect) ;///< *this += theSrcVect
	cGSLVector& operator +=(double theVal) ;///< *this[i] += theVal for all i 
	cGSLVector& operator +=(double* theSrcVect) ;///<*this[i] += theSrcVect[i] for all i 
	cGSLVector& operator -=(const cGSLVector& theSrcVect) ;///< *this -= theSrcVect
	cGSLVector& operator -=(double theVal) ;///< *this[i] -= theVal for all i 
	cGSLVector& operator -=(double* theSrcVect) ;///< *this -= theSrcVect
	cGSLVector& operator *=(double theVal) ;///< *this *= theVal
	cGSLVector& operator /=(double theVal) ;///< *this /= theVal
	void SetThisWithSubVector(const cGSLVector& theSrcVect, const uint theBegIndex) ;///< *this[i] = theSrcVect[i+theBegIndex] for all i
	void SetSubVectorWithThis(cGSLVector& theDestVect, const uint theBegIndex) ;///< theDestVect[i+theBegIndex]=*this[i] for all i
	cGSLVector& operator =(const cGSLMatrix& theMatrix) ; ///< *this = theMatrix (one column matrix)
#ifndef _GNU_ // Works with MS VS 2008 - Not with MSYS
	friend std::ostream& operator <<(std::ostream& theStream, const cGSLVector& theVect) ; ///< prints mVect
	friend cGSLVector operator +(const cGSLVector& theVect, double theVal) ;///< returns theVect[i]+theVal for all i
	friend cGSLVector operator +(double theVal, const cGSLVector& theVect) ;///< returns theVect[i]+theVal for all i
	friend cGSLVector operator +(const cGSLVector& theVect1, double* theVect2) ;///< returns theVect1 + theVect2
	friend cGSLVector operator +(double* theVect1, const cGSLVector& theVect2) ;///< returns theVect1 + theVect2
	friend cGSLVector operator +(const cGSLVector& theVect1, const cGSLVector& theVect2) ;///< returns theVect1 + theVect2	
	friend cGSLVector operator -(const cGSLVector& theVect, double theVal) ;///< returns theVect[i]-theVal for all i
	friend cGSLVector operator -(double theVal, const cGSLVector& theVect) ;///< returns theVal-theVect[i] for all i
	friend cGSLVector operator -(const cGSLVector& theVect1, double* theVect2) ;///< returns theVect1 - theVect2
	friend cGSLVector operator -(double* theVect1, const cGSLVector& theVect2) ;///< returns theVect1 - theVect2
	friend cGSLVector operator -(const cGSLVector& theVect1, const cGSLVector& theVect2) ;///< returns theVal*theVect
	friend cGSLVector operator *(double theVal, const cGSLVector& theVect) ;///< returns theVal*theVect
	friend cGSLVector operator *(const cGSLVector& theVect, double theVal) ;///< returns theVect/theVal
	friend cGSLVector operator /(double theVal, const cGSLVector& theVect) ;/// returns theVal/theVect[i] for all i
	friend cGSLVector operator /(const cGSLVector& theVect, double theVal) ;///< returns theVect/theVal
	friend double Norm(const cGSLVector& theVect) ;///< euclidian norm
	friend double Sum(const cGSLVector& theVect) ; ///< sum
#endif // _GNU_
} ;

#ifdef _GNU_ // Works with MSYS - No Need for MS VS 2008 - Define _GNU_ in MSYS or LINUX makefile
extern std::ostream& operator <<(std::ostream& theStream, const cGSLVector& theVect) ; ///< prints mVect
extern cGSLVector operator +(const cGSLVector& theVect, double theVal) ;///< returns theVect[i]+theVal for all i
extern cGSLVector operator +(double theVal, const cGSLVector& theVect) ;///< returns theVect[i]+theVal for all i
extern cGSLVector operator +(const cGSLVector& theVect1, double* theVect2) ;///< returns theVect1 + theVect2
extern cGSLVector operator +(double* theVect1, const cGSLVector& theVect2) ;///< returns theVect1 + theVect2
extern cGSLVector operator +(const cGSLVector& theVect1, const cGSLVector& theVect2) ;///< returns theVect1 + theVect2	
extern cGSLVector operator -(const cGSLVector& theVect, double theVal) ;///< returns theVect[i]-theVal for all i
extern cGSLVector operator -(double theVal, const cGSLVector& theVect) ;///< returns theVal-theVect[i] for all i
extern cGSLVector operator -(const cGSLVector& theVect1, double* theVect2) ;///< returns theVect1 - theVect2
extern cGSLVector operator -(double* theVect1, const cGSLVector& theVect2) ;///< returns theVect1 - theVect2
extern cGSLVector operator -(const cGSLVector& theVect1, const cGSLVector& theVect2) ;///< returns theVal*theVect
extern cGSLVector operator *(double theVal, const cGSLVector& theVect) ;///< returns theVal*theVect
extern cGSLVector operator *(const cGSLVector& theVect, double theVal) ;///< returns theVect/theVal
extern cGSLVector operator /(double theVal, const cGSLVector& theVect) ;/// returns theVal/theVect[i] for all i
extern cGSLVector operator /(const cGSLVector& theVect, double theVal) ;///< returns theVect/theVal
extern double Norm(const cGSLVector& theVect) ;///< euclidian norm
extern double Sum(const cGSLVector& theVect) ;///< sum
#endif // _GNU_
#endif //_cGSLVector_H_
