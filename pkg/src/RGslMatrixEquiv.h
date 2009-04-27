/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: RGslMatrixEquiv.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _RGSLMATRIXEQUIV_H_
#define _RGSLMATRIXEQUIV_H_

#include <R.h>
#include "R_ext/Lapack.h"

#include "cRegArchError.h"
#include "RGslVectorEquiv.h"


#ifndef uint
	typedef unsigned int uint ;
#endif // uint

class gsl_matrix
{
public :
	uint	mNRow ;
	uint	mNCol ;
	double	*mData ;
public :
	gsl_matrix(int theNRow=0, int theNCol=0) ;
	~gsl_matrix() ;
#ifndef _GNU_
	friend gsl_matrix* gsl_matrix_alloc(uint theNRow, uint theNCol) ;
	friend gsl_matrix* gsl_matrix_realloc(uint theNRow, uint theNCol) ;
	friend void gsl_matrix_set_all(gsl_matrix* theMat, double theVal) ;
	friend void gsl_matrix_set(gsl_matrix* theMat, uint theRow, uint theCol, double theVal) ;
	friend void gsl_matrix_free(gsl_matrix* theMat) ;
	friend double gsl_matrix_get(gsl_matrix* theMat, uint theRow, uint theCol) ;
#endif // _GNU_
} ;
#ifdef _GNU_
	extern gsl_matrix* gsl_matrix_alloc(uint theNRow, uint theNCol) ;
	extern gsl_matrix* gsl_matrix_realloc(uint theNRow, uint theNCol) ;
	extern void gsl_matrix_set_all(gsl_matrix* theMat, double theVal) ;
	extern void gsl_matrix_set(gsl_matrix* theMat, uint theRow, uint theCol, double theVal) ;
	extern void gsl_matrix_free(gsl_matrix* theMat) ;
	extern double gsl_matrix_get(gsl_matrix* theMat, uint theRow, uint theCol) ;
#endif // _GNU_
#endif // _RGSLMATRIXEQUIV_H_
