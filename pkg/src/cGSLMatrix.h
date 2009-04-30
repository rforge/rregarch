/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cGSLMatrix.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _cGSLMatrix_H_
#define _cGSLMatrix_H_
/*!
	\file cGSLMatrix.h
	\brief Header fo C++ encapsulation of GSL matrix definitions and functions.
	
	\par Details.
	\par uses gsl_matrix.
	\author Ollivier TARAMASCO 
	\date oct-09-2008
*/
#include "cRegArchError.h"
#include "cGSLVector.h"
#ifdef _RDLL_
	#include "RGslMatrixEquiv.h"
#else
	#include <iostream>
	#include <cmath>
	#include <gsl/gsl_matrix.h>
	#include <gsl/gsl_linalg.h> 
#endif //_RDLL_
#ifndef MIN_DBLE
	#define MIN_DBLE 1e-16L
#endif //MIN_DBLE

/*!
	\brief class cGSLMatrix
	\par
	1) Encapsulation of the "C" gsl structure gsl_matrix \par
	2) Standard and usefull matrix operations declarations
*/	
class cGSLMatrix
{
private :
	gsl_matrix*		mvMat ; ///< data
public :
	cGSLMatrix(uint theNRow=0, uint theNCol=0, double theVal = 0.0L) ; ///< standard constructor
	cGSLMatrix(const cGSLVector& theVect) ; ///< constructor
	cGSLMatrix(const cGSLMatrix& theMat) ; ///< constructor
	virtual ~cGSLMatrix() ; ///< standard destructor
	uint GetNRow(void) const ; ///< returns matrix number of rows
	uint GetNCol(void) const ; ///< returns matrix number of columns
	gsl_matrix* GetMat(void) {return mvMat ;}
	void Delete(void) ; ///< Deletes matrix
	void ReAlloc(uint theNRow, uint theNCol, double theVal = 0.0L) ; ///< Reallocates matrix
	void ReAlloc(const cGSLVector& theVect) ; ///< Reallocates matrix
	void ReAlloc(const cGSLMatrix& theMat) ; ///< Reallocates matrix
	double* operator[](uint theNRow) const ; ///< Returns address of matrix[theNRow]
	cGSLMatrix& operator =(const cGSLMatrix& theSrcMat) ; ///< Standard matrix affectation
	cGSLMatrix& operator =(const cGSLVector& theVect) ; ///< one column matrix affectation
	cGSLMatrix& operator =(double theVal) ; ///< matrix[i,j] = theVal
	cGSLMatrix& operator +=(const cGSLMatrix& theMatrix) ; ///< Standard += operation
	cGSLMatrix& operator +=(double theVal) ; ///< matrix[i,j] += theVal
	cGSLMatrix& operator -=(const cGSLMatrix& theMatrix) ; ///< Standard -= operation
	cGSLMatrix& operator -=(double theVal) ; ///< matrix[i,j] -= theVal
	cGSLMatrix& operator *=(const cGSLMatrix& theRight) ; ///< Standard *= operation
	cGSLMatrix& operator *=(double theLambda) ; ///< matrix[i,j] *= theVal
	cGSLMatrix& operator /=(double theLambda) ; ///< matrix[i,j] /= theVal
#ifndef _GNU_ ///< Works with MS VS 2008 - Not with MSYS
	friend cGSLMatrix operator +(const cGSLMatrix& theLeft, const cGSLMatrix &theRight) ; ///< Standard + operation
	friend cGSLMatrix operator +(double theVal, const cGSLMatrix &theRight) ;
	friend cGSLMatrix operator +(const cGSLMatrix &theLeft, double theVal) ;
	friend cGSLMatrix operator -(const cGSLMatrix& theLeft, const cGSLMatrix &theRight) ;
	friend cGSLMatrix operator -(double theVal, const cGSLMatrix &theRight) ;
	friend cGSLMatrix operator -(const cGSLMatrix &theLeft, double theVal) ;
	friend cGSLMatrix operator *(const cGSLMatrix& theLeft, const cGSLMatrix &theRight) ;
	friend cGSLVector operator *(const cGSLMatrix& theLeft, const cGSLVector& theVect) ;
	friend cGSLMatrix operator *(const cGSLVector& theVect, const cGSLMatrix& theRight) ;
	friend cGSLMatrix operator *(const cGSLMatrix& theMat, double theLambda) ;
	friend cGSLMatrix operator *(double theLambda, const cGSLMatrix& theMat) ;
	friend cGSLMatrix operator /(const cGSLMatrix& theMat, double theLambda) ;
	friend cGSLMatrix Zeros(uint theN, uint theP) ;
	friend cGSLMatrix Identity(uint theN) ;
	friend cGSLMatrix Diag(const cGSLVector& theVect) ;
#ifdef _RDLL_
	friend void LapackInvAndDet(const cGSLMatrix &theMatrix, cGSLMatrix &theInvMatrix, double& theDet) ;
#else
	friend void Svd(const cGSLMatrix& theMatrix, cGSLMatrix& theU, cGSLVector& theS, cGSLMatrix& theV) ;
#endif // _RDLL_
	friend cGSLMatrix Inv(const cGSLMatrix &theMatrix) ;
	friend void ClearMatrix(cGSLMatrix& theMatrix) ;
	friend std::ostream& operator <<(std::ostream& theStream, const cGSLMatrix& theMat) ;
	friend cGSLMatrix Transpose(const cGSLMatrix& theMatrix) ;
	friend cGSLMatrix Transpose(const cGSLVector& theVector) ;
#endif //_GNU_
} ;

#ifdef _GNU_ ///< Works with MSYS - No Need for MS VS 2008 - Define _GNU_ in MSYS or LINUX makefile
extern cGSLMatrix operator +(const cGSLMatrix& theLeft, const cGSLMatrix &theRight) ;
extern cGSLMatrix operator +(double theVal, const cGSLMatrix &theRight) ;
extern cGSLMatrix operator +(const cGSLMatrix &theLeft, double theVal) ;
extern cGSLMatrix operator -(const cGSLMatrix& theLeft, const cGSLMatrix &theRight) ;
extern cGSLMatrix operator -(double theVal, const cGSLMatrix &theRight) ;
extern cGSLMatrix operator -(const cGSLMatrix &theLeft, double theVal) ;
extern cGSLMatrix operator *(const cGSLMatrix& theLeft, const cGSLMatrix &theRight) ;
extern cGSLVector operator *(const cGSLMatrix& theLeft, const cGSLVector& theVect) ;
extern cGSLMatrix operator *(const cGSLVector& theVect, const cGSLMatrix& theRight) ;
extern cGSLMatrix operator *(const cGSLMatrix& theMat, double theLambda) ;
extern cGSLMatrix operator *(double theLambda, const cGSLMatrix& theMat) ;
extern cGSLMatrix operator /(const cGSLMatrix& theMat, double theLambda) ;
extern cGSLMatrix Zeros(uint theN, uint theP) ;
extern cGSLMatrix Identity(uint theN) ;
extern cGSLMatrix Diag(const cGSLVector& theVect) ;
extern void Svd(const cGSLMatrix& theMatrix, cGSLMatrix& theU, cGSLVector& theS, cGSLMatrix& theV) ;
extern cGSLMatrix Inv(const cGSLMatrix &theMatrix) ;
extern void ClearMatrix(cGSLMatrix& theMatrix) ;
extern std::ostream& operator <<(std::ostream& theStream, const cGSLMatrix& theMat) ;
extern cGSLMatrix Transpose(const cGSLMatrix& theMatrix) ;
extern cGSLMatrix Transpose(const cGSLVector& theVector) ;
#endif //_GNU_

#endif // _cGSLMatrix_H_

