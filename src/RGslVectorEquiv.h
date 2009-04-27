/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: RGslVectorEquiv.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _RGSLVVECTOREQUIV_H_
#define _RGSLVVECTOREQUIV_H_
#include <R.h>
#include "cRegArchError.h"

#ifndef uint
	typedef unsigned int uint ;
#endif // uint


class gsl_vector
{
public :
	uint	size ;
	double*	mData ;
public :
	gsl_vector(int theSize=0, double theVal=0.0) ;
	~gsl_vector() ;
#ifndef _GNU_
	friend gsl_vector* gsl_vector_alloc(size_t theSize) ;
	friend void gsl_vector_set_all(gsl_vector* theVect, double theVal) ;
	friend void gsl_vector_set(gsl_vector* theVect, size_t theIndex, double theVal) ;
	friend double gsl_vector_get(const gsl_vector* theVect, int theIndex) ;
	friend void gsl_vector_free(gsl_vector* theVect) ;
	friend double* gsl_vector_ptr(gsl_vector* theVect, size_t theIndex) ;
	friend void gsl_vector_scale(gsl_vector* theVect, double theVal) ;	
#endif // _GNU_
} ;
#ifdef _GNU_
	extern gsl_vector* gsl_vector_alloc(size_t theSize) ;
	extern void gsl_vector_set_all(gsl_vector* theVect, double theVal) ;
	extern void gsl_vector_set(gsl_vector* theVect, size_t theIndex, double theVal) ;
	extern double gsl_vector_get(const gsl_vector* theVect, int theIndex) ;
	extern void gsl_vector_free(gsl_vector* theVect) ;
	extern double* gsl_vector_ptr(gsl_vector* theVect, size_t theIndex) ;
	extern void gsl_vector_scale(gsl_vector* theVect, double theVal) ;	
#endif // _GNU_
#endif // _RGSLVVECTOREQUIV_H_
