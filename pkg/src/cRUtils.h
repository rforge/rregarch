/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRUtils.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CRUTILS_H_
#define _CRUTILS_H_
#include "cGSLVector.h"
#include "cGSLMatrix.h"
#ifdef _RDLL_
#ifndef cDVector
	#define cDVector cGSLVector
	#define cDMatrix cGSLMatrix
#endif

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

#ifndef uint
	typedef unsigned int uint ;
#endif // uint

class cRUtil
{	private :
		int	mvNbProtect	;
	public :
		cRUtil(){mvNbProtect = 0 ;} ;
		void EndProtect(void){if (mvNbProtect > 0) {UNPROTECT(mvNbProtect); mvNbProtect = 0 ; }} ;
		~cRUtil(){mvNbProtect = 0 ;};
		/*
		 * Get a single value from a SEXP list at index theNum
		 */
		void GetValSexp(SEXP theSEXP, uint theNum, uint &theVal) ;
		void GetValSexp(SEXP theSEXP, uint theNum, int &theVal) ;
		void GetValSexp(SEXP theSEXP, uint theNum, double &theVal) ;
		void GetValSexp(SEXP theSEXP, uint theNum, char* theVal) ;
		void GetValSexp(SEXP theSEXP, uint theNum, SEXP &theVal) ;
		/*
		* Get a vector from a SEXP list at index theNum
		*/
		void GetVectSexp(SEXP theSEXP, uint theNum, uint theDim, double* theVal) ;
		void GetVectSexp(SEXP theSEXP, uint theNum, uint theDim, int* theVal) ;
		void GetVectSexp(SEXP theSEXP, uint theNum, uint theDim, uint* theVal) ;
		void GetVectSexp(SEXP theSEXP, uint theNum, cDVector& theVal) ;
		/*
		* Get a matrix from a SEXP list at index theNum
		*/
		void GetMatSexp(SEXP theSEXP, uint theNum, uint theRow, uint theCol, int** theMat) ;
		void GetMatSexp(SEXP theSEXP, uint theNum, uint theRow, uint theCol, uint** theMat) ;
		void GetMatSexp(SEXP theSEXP, uint theNum, uint theRow, uint theCol, double** theMat) ;
		void GetMatSexp(SEXP theSEXP, uint theNum, cDMatrix& theMat) ;
		/*
		* Get all values from a SEXP list of values
		*/
		void GetListValSexp(SEXP theSEXP, uint theNum, uint theNElt, int* theVal) ;
		void GetListValSexp(SEXP theSEXP, uint theNum, uint theNElt, uint* theVal) ;
		void GetListValSexp(SEXP theSEXP, uint theNum, uint theNElt, double* theVal) ;
		/*
		* Get all the vector sizes in a SEXP list of vectors
		*/
		void GetListVectSizesSexp(SEXP theSEXP, uint theNum, uint theNElt, uint* theSizes);
		/*
		* Get all vectors from a SEXP list of vectors
		*/
		void GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theDim, int** theVal) ;
		void GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theDim, uint** theVal) ;
		void GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theDim, double** theVal) ;
		void GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, cDVector* theVal) ;
		/*
		* Get a list of vectors and the name of each of them
		*/
		void GetListNamedVectSexp(SEXP theSEXP, uint theNum, uint theNElt, char** theNames, cDVector* theVal);
		/*
		* Get all matrices from a SEXP list of matrices
		*/
		void GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theRow, uint theCol, int*** theVal) ;
		void GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theRow, uint theCol, uint*** theVal) ;
		void GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theRow, uint theCol, double*** theVal) ;
		void GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, cDMatrix* theVal) ;
		
		/*
		 * Get all vectors from a SEXP list of lists of vectors
		 */
		void GetListListVectSexp(SEXP theSEXP, uint theNum, uint theNList1, uint theNList2, cDVector** theVect) ;

		/*
		 * Get all vectors from a SEXP list of lists of matrices
		 */
		void GetListListMatSexp(SEXP theSEXP, uint theNum, uint theNList1, uint theNList2, cDMatrix** theVect) ;

		/*
		* Fill a single value in a SEXP at index theNum
		*/
		void SetValSexp(int theVal, SEXP &theSEXP) ;
		void SetValSexp(uint theVal, SEXP &theSEXP) ;
		void SetValSexp(double theVal, SEXP &theSEXP) ;
		void SetValSexp(bool theVal, SEXP &theSEXP) ;
		/*
		* Fill a vector of size theDim in a SEXP
		*/
		void SetVectSexp(int *theVect, uint theDim, SEXP &theSEXP) ;
		void SetVectSexp(uint *theVect, uint theDim, SEXP &theSEXP) ;
		void SetVectSexp(double *theVect, uint theDim, SEXP &theSEXP) ;
		void SetVectSexp(cDVector& theVect, SEXP &theSEXP) ;
	   /*
	    * Fill a matrix of size theRow * theCol in a SEXP
		*/
		void SetMatSexp(int **theMat, uint theRow, uint theCol, SEXP &theSEXP) ;
		void SetMatSexp(uint **theMat, uint theRow, uint theCol, SEXP &theSEXP) ;
		void SetMatSexp(double **theMat, uint theRow, uint theCol, SEXP &theSEXP) ;
		void SetMatSexp(cDMatrix& theMat, SEXP &theSEXP) ;
		/*
		* Fill a list of theDim values in a SEXP
		*/
		void SetListValSexp(int* theVal, uint theDim, SEXP &theSEXP) ;
		void SetListValSexp(uint* theVal, uint theDim, SEXP &theSEXP) ;
		void SetListValSexp(double* theVal, uint theDim, SEXP &theSEXP) ;
		void SetListValSexp(cDVector& theVal,  SEXP &theSEXP) ;
		/*
		* Fill a list of theNElt vectors of size theDim in a SEXP
		*/
		void SetListVectSexp(int** theVal, uint theNElt, uint theDim, SEXP &theSEXP) ;
		void SetListVectSexp(uint** theVal, uint theNElt, uint theDim, SEXP &theSEXP) ;
		void SetListVectSexp(double** theVal, uint theNElt, uint theDim, SEXP &theSEXP) ;
		/*
		* Fill a list of theNElt vectors with sizes theDim[i] in a SEXP
		*/
		void SetListVectSexp(int** theVal, uint theNElt, uint* theDim, SEXP &theSEXP) ;
		void SetListVectSexp(uint** theVal, uint theNElt, uint *theDim, SEXP &theSEXP) ;
		void SetListVectSexp(double** theVal, uint theNElt, uint *theDim, SEXP &theSEXP) ;
		void SetListVectSexp(cDVector* theVal, uint theNElt, SEXP &theSEXP) ;
		/*
		* Set a list of theNElt vectors with names theNames[i] in a SEXP
		*/
		void SetListNamedVectSexp(cDVector* theVal, char** theNames, uint theNElt, SEXP &theSEXP);
		/*
		* Fill a list of theNElt matrices of size theRow * theCol in a SEXP
		*/
		void SetListMatSexp(int*** theVal, uint theNElt, uint theRow, uint theCol, SEXP &theSEXP) ;
		void SetListMatSexp(uint*** theVal, uint theNElt, uint theRow, uint theCol, SEXP &theSEXP) ;
		void SetListMatSexp(double*** theVal, uint theNElt, uint theRow, uint theCol, SEXP &theSEXP) ;
		/*
		* Fill a list of theNElt matrices with sizes theRow[i] * theCol[i] in a SEXP
		*/
		void SetListMatSexp(int*** theVal, uint theNElt, uint *theRow, uint *theCol, SEXP &theSEXP) ;
		void SetListMatSexp(uint*** theVal, uint theNElt, uint *theRow, uint *theCol, SEXP &theSEXP) ;
		void SetListMatSexp(double*** theVal, uint theNElt, uint *theRow, uint *theCol, SEXP &theSEXP) ;
		void SetListMatSexp(cDMatrix* theVal, uint theNElt, SEXP &theSEXP) ;

		/*
		* Fill a list of theNList1 lists of theNList2 vectors in a SEXP
		*/
		void SetListListVectSexp(cDVector** theVect, uint theNList1, uint theNList2, SEXP &theSEXP) ;

		/*
		* Fill a list of theNList1 lists of theNList2 matrices in a SEXP
		*/
		void SetListListMatSexp(cDMatrix** theMat, uint theNList1, uint theNList2, SEXP &theSEXP) ;
		void SetListListMatSexp(cDMatrix** theMat, uint theNList1, uint* theNList2, SEXP &theSEXP) ;

	} ;
#endif //_RDLL_
#endif // _CRUTILS_H_