/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRUtils.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifdef _RDLL_
#include "cRUtils.h"
/*
 * Get a single value from a SEXP list at position theNum
 */
void cRUtil::GetValSexp(SEXP theSEXP, uint theNum, uint &theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	theVal = INTEGER(myAux)[0] ;
}

void cRUtil::GetValSexp(SEXP theSEXP, uint theNum, int &theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	theVal = INTEGER(myAux)[0] ;
}

void cRUtil::GetValSexp(SEXP theSEXP, uint theNum, double &theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	theVal = REAL(myAux)[0] ;
}

void cRUtil::GetValSexp(SEXP theSEXP, uint theNum, char* theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	sprintf(theVal, CHAR(STRING_ELT(myAux, 0))) ;
}
void cRUtil::GetValSexp(SEXP theSEXP, uint theNum, SEXP &theVal)
{
	theVal = VECTOR_ELT(theSEXP, theNum) ;
}

/*
 * Get a vector from a SEXP list at position theNum
 */
void cRUtil::GetVectSexp(SEXP theSEXP, uint theNum, uint theDim, int* theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theDim ; i++)
		theVal[i] = INTEGER(myAux)[i] ;
}
void cRUtil::GetVectSexp(SEXP theSEXP, uint theNum, uint theDim, uint* theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theDim ; i++)
		theVal[i] = INTEGER(myAux)[i] ;
}

void cRUtil::GetVectSexp(SEXP theSEXP, uint theNum, uint theDim, double* theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theDim ; i++)
		theVal[i] = REAL(myAux)[i] ;
}
void cRUtil::GetVectSexp(SEXP theSEXP, uint theNum, cDVector& theVal)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theVal.GetSize() ; i++)
		theVal[i] = REAL(myAux)[i] ;
}
/*
 * Get a matrix from a SEXP list at position theNum
 */
void cRUtil::GetMatSexp(SEXP theSEXP, uint theNum, uint theRow, uint theCol, int** theMat)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theRow ; i++)
		for (register uint j = 0 ; j < theCol ; j++)
			theMat[i][j] = INTEGER(myAux)[i+j*theRow] ;
}
void cRUtil::GetMatSexp(SEXP theSEXP, uint theNum, uint theRow, uint theCol, uint** theMat)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theRow ; i++)
		for (register uint j = 0 ; j < theCol ; j++)
			theMat[i][j] = INTEGER(myAux)[i+j*theRow] ;
}
void cRUtil::GetMatSexp(SEXP theSEXP, uint theNum, uint theRow, uint theCol, double** theMat)
{
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < theRow ; i++)
		for (register uint j = 0 ; j < theCol ; j++)
			theMat[i][j] = REAL(myAux)[i+j*theRow] ;
}

void cRUtil::GetMatSexp(SEXP theSEXP, uint theNum, cDMatrix& theMat)
{
uint myNRow = theMat.GetNRow(),
	 myNCol = theMat.GetNCol() ;
SEXP myAux = VECTOR_ELT(theSEXP, theNum) ;
	for (register uint i = 0 ; i < myNRow ; i++)
		for (register uint j = 0 ; j < myNCol ; j++)
			theMat[i][j] = REAL(myAux)[i+j*myNRow] ;
}
/*
 * Get all the numbers in a SEXP list of numbers
 */
void cRUtil::GetListValSexp(SEXP theSEXP, uint theNum, uint theNElt, int* theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetValSexp(myAux, i, theVal[i]) ;
}
void cRUtil::GetListValSexp(SEXP theSEXP, uint theNum, uint theNElt, uint* theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetValSexp(myAux, i, theVal[i]) ;
}

void cRUtil::GetListValSexp(SEXP theSEXP, uint theNum, uint theNElt, double* theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetValSexp(myAux, i, theVal[i]) ;
}

/*
 * Get all the vector sizes in a SEXP list of vectors
 */
void cRUtil::GetListVectSizesSexp(SEXP theSEXP, uint theNum, uint theNElt, uint* theSizes)
{	for (register uint i = 0 ; i < theNElt ; i++)
		theSizes[i] = length(VECTOR_ELT(theSEXP, i));
}

/*
 * Get all the vectors in a SEXP list of vectors
 */
void cRUtil::GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theDim, int** theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetVectSexp(myAux, i, theDim, theVal[i]) ;
}
void cRUtil::GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theDim, uint** theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetVectSexp(myAux, i, theDim, theVal[i]) ;
}
void cRUtil::GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theDim, double** theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetVectSexp(myAux, i, theDim, theVal[i]) ;
}
void cRUtil::GetListVectSexp(SEXP theSEXP, uint theNum, uint theNElt, cDVector* theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	GetVectSexp(myAux, i, theVal[i]) ;
	}
}

/*
* Get a list of vectors and the name of each of them
*/
void cRUtil::GetListNamedVectSexp(SEXP theSEXP, uint theNum, uint theNElt, char** theNames, cDVector* theVal)
{	SEXP myNames = getAttrib(theSEXP, R_NamesSymbol);
	for (register uint i = 0; i < theNElt; i++)
	{	sprintf(theNames[i], CHAR(STRING_ELT(myNames, i)));
		GetVectSexp(theSEXP, i, theVal[i]);
	}
}

/*
 * Get all the matrices in a SEXP list of matrices
 */
void cRUtil::GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theRow, uint theCol, int*** theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetMatSexp(myAux, i, theRow, theCol, theVal[i]) ;
}

void cRUtil::GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theRow, uint theCol, uint*** theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetMatSexp(myAux, i, theRow, theCol, theVal[i]) ;
}

void cRUtil::GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, uint theRow, uint theCol, double*** theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetMatSexp(myAux, i, theRow, theCol, theVal[i]) ;
}

void cRUtil::GetListMatSexp(SEXP theSEXP, uint theNum, uint theNElt, cDMatrix* theVal)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNElt ; i++)
		GetMatSexp(myAux, i, theVal[i]) ;
}

/*
 * Get all the vectors in a SEXP list of lists of vectors
 */
void cRUtil::GetListListVectSexp(SEXP theSEXP, uint theNum, uint theNList1, uint theNList2, cDVector** theVect)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNList1 ; i++)
	{	GetListVectSexp(myAux, i, theNList2, theVect[i]) ;
	}
}

/*
 * Get all the matrices in a SEXP list of lists of matrices
 */
void cRUtil::GetListListMatSexp(SEXP theSEXP, uint theNum, uint theNList1, uint theNList2, cDMatrix** theMat)
{
SEXP myAux ;
	GetValSexp(theSEXP, theNum, myAux) ;
	for (register uint i = 0 ; i < theNList1 ; i++)
		GetListMatSexp(myAux, i, theNList2, theMat[i]) ;

}

/*
 * Fill a unique value in a SEXP at position theNum
 */
void cRUtil::SetValSexp(int theVal, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(REALSXP, 1)) ;
	INTEGER(theSEXP)[0] = theVal ;
}
void cRUtil::SetValSexp(uint theVal, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(REALSXP, 1)) ;
	INTEGER(theSEXP)[0] = theVal ;
}
void cRUtil::SetValSexp(double theVal, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(REALSXP, 1)) ;
	REAL(theSEXP)[0] = theVal ;
}
void cRUtil::SetValSexp(bool theVal, SEXP &theSEXP)
{   mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(LGLSXP, 1)) ;
	LOGICAL(theSEXP)[0] = theVal ;
}
/*
 * Fill a vector of size theDim in a SEXP
 */
void cRUtil::SetVectSexp(int *theVect, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP=allocVector(INTSXP, theDim)) ;
	for (register uint i = 0 ; i < theDim ; i++)
		INTEGER(theSEXP)[i] = theVect[i] ;
}

void cRUtil::SetVectSexp(uint *theVect, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP=allocVector(INTSXP, theDim)) ;
	for (register uint i = 0 ; i < theDim ; i++)
		INTEGER(theSEXP)[i] = theVect[i] ;
}

void cRUtil::SetVectSexp(double *theVect, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP=allocVector(REALSXP, theDim)) ;
	for (register uint i = 0 ; i < theDim ; i++)
		REAL(theSEXP)[i] = theVect[i] ;
}
void cRUtil::SetVectSexp(cDVector& theVect, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP=allocVector(REALSXP, theVect.GetSize())) ;
	for (register uint i = 0 ; i < theVect.GetSize() ; i++)
		REAL(theSEXP)[i] = theVect[i] ;
}


/*
 * Fill a matrix of size theRow * theCol in a SEXP
*/
void cRUtil::SetMatSexp(int **theMat, uint theRow, uint theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocMatrix(INTSXP, theRow, theCol)) ;
	for (register uint i = 0 ; i < theRow ; i++)
		for (register uint j = 0 ; j < theCol ; j++)
			INTEGER(theSEXP)[i+j*theRow] = theMat[i][j] ;
}

void cRUtil::SetMatSexp(uint **theMat, uint theRow, uint theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocMatrix(INTSXP, theRow, theCol)) ;
	for (register uint i = 0 ; i < theRow ; i++)
		for (register uint j = 0 ; j < theCol ; j++)
			INTEGER(theSEXP)[i+j*theRow] = theMat[i][j] ;
}

void cRUtil::SetMatSexp(double** theMat, uint theRow, uint theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocMatrix(REALSXP, theRow, theCol)) ;
	for (register uint i = 0 ; i < theRow ; i++)
		for (register uint j = 0 ; j < theCol ; j++)
			REAL(theSEXP)[i+j*theRow] = theMat[i][j] ;
}

void cRUtil::SetMatSexp(cDMatrix& theMat, SEXP &theSEXP)
{
gsl_matrix* myMat = theMat.GetMat() ;
uint	myNRow = theMat.GetNRow(),
		myNCol = theMat.GetNCol() ;
	mvNbProtect++ ;
	PROTECT(theSEXP = allocMatrix(REALSXP, myNRow, myNCol)) ;
	for (register uint i = 0 ; i < myNRow ; i++)
		for (register uint j = 0 ; j <  myNCol ; j++)
			#ifdef _GSL_
				REAL(theSEXP)[i+j*myNRow] = myMat->data[i+j*myNRow] ;
			#else
				REAL(theSEXP)[i+j*myNRow] = myMat->mData[i+j*myNRow] ;
			#endif
}

/*
 * Fill a list of theDim numbers in a SEXP
 */
void cRUtil::SetListValSexp(int* theVal, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theDim)) ;
	for (register uint i = 0 ; i < theDim ; i++)
	{	SEXP myAux ;
		SetValSexp(theVal[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListValSexp(uint* theVal, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theDim)) ;
	for (register uint i = 0 ; i < theDim ; i++)
	{	SEXP myAux ;
		SetValSexp(theVal[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListValSexp(double* theVal, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theDim)) ;
	for (register uint i = 0 ; i < theDim ; i++)
	{	SEXP myAux ;
		SetValSexp(theVal[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
void cRUtil::SetListValSexp(cDVector& theVal, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theVal.GetSize())) ;
	for (register uint i = 0 ; i < theVal.GetSize() ; i++)
	{	SEXP myAux ;
		SetValSexp(theVal[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

/*
 * Fill a list of theNElt vectors of size theDim in a SEXP
 */
void cRUtil::SetListVectSexp(int** theVal, uint theNElt, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetVectSexp(theVal[i], theDim, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListVectSexp(uint** theVal, uint theNElt, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetVectSexp(theVal[i], theDim, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListVectSexp(double** theVal, uint theNElt, uint theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux  ;
		SetVectSexp(theVal[i], theDim, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
/*
 * Fill a list of theNElt vectors of sizes given by theDim in a SEXP
 */
void cRUtil::SetListVectSexp(int** theVal, uint theNElt, uint *theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetVectSexp(theVal[i], theDim[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListVectSexp(uint** theVal, uint theNElt, uint *theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetVectSexp(theVal[i], theDim[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListVectSexp(double** theVal, uint theNElt, uint *theDim, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux  ;
		SetVectSexp(theVal[i], theDim[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}


void cRUtil::SetListVectSexp(cDVector* theVal, uint theNElt, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux  ;
		SetVectSexp(theVal[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

/*
* Fill a list of theNElt vectors of names given by theNames in a SEXP
*/
void cRUtil::SetListNamedVectSexp(cDVector* theVal, char** theNames, uint theNElt, SEXP &theSEXP)
{	mvNbProtect++;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt));
	for (register uint i = 0; i < theNElt; i++)
	{	SEXP myAux;
		SetVectSexp(theVal[i], myAux);
		SET_VECTOR_ELT(theSEXP, i, myAux);
	}

	mvNbProtect++;
	SEXP myNames = PROTECT(allocVector(STRSXP, theNElt));
	for (register uint i = 0; i < theNElt; i++)
	{	SET_STRING_ELT(myNames, i, mkChar(theNames[i]));
	}
	setAttrib(theSEXP, R_NamesSymbol, myNames);
}

/*
 * Fill a list of theNElt matrices of size theRow * theCol in a SEXP
 */
void cRUtil::SetListMatSexp(int*** theVal, uint theNElt, uint theRow, uint theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], theRow, theCol, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
void cRUtil::SetListMatSexp(uint*** theVal, uint theNElt, uint theRow, uint theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], theRow, theCol, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
void cRUtil::SetListMatSexp(double*** theVal, uint theNElt, uint theRow, uint theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], theRow, theCol, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
/*
 * Fill a list of theNElt matrices of sizes given by theRow and theCol in a SEXP
 */
void cRUtil::SetListMatSexp(int*** theVal, uint theNElt, uint *theRow, uint *theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], theRow[i], theCol[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
void cRUtil::SetListMatSexp(uint*** theVal, uint theNElt, uint *theRow, uint *theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], theRow[i], theCol[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}
void cRUtil::SetListMatSexp(double*** theVal, uint theNElt, uint *theRow, uint *theCol, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], theRow[i], theCol[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}


void cRUtil::SetListMatSexp(cDMatrix* theVal, uint theNElt, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNElt)) ;
	for (register uint i = 0 ; i < theNElt ; i++)
	{	SEXP myAux ;
		SetMatSexp(theVal[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

/*
* Fill a list of theNList1 lists of theNList2 vectors in a SEXP
*/
void cRUtil::SetListListVectSexp(cDVector** theVect, uint theNList1, uint theNList2, SEXP &theSEXP)
{
	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNList1)) ;
	for (register uint i = 0 ; i < theNList1 ; i++)
	{	SEXP myAux ;
		SetListVectSexp(theVect[i], theNList2, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

/*
* Fill a list of theNList1 lists of theNList2 matrices in a SEXP
*/
		
void cRUtil::SetListListMatSexp(cDMatrix** theMat, uint theNList1, uint theNList2, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNList1)) ;
	for (register uint i = 0 ; i < theNList1 ; i++)
	{	SEXP myAux ;
		SetListMatSexp(theMat[i], theNList2, myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

void cRUtil::SetListListMatSexp(cDMatrix** theMat, uint theNList1, uint* theNList2, SEXP &theSEXP)
{	mvNbProtect++ ;
	PROTECT(theSEXP = allocVector(VECSXP, theNList1)) ;
	for (register uint i = 0 ; i < theNList1 ; i++)
	{	SEXP myAux ;
		SetListMatSexp(theMat[i], theNList2[i], myAux) ;
		SET_VECTOR_ELT(theSEXP, i, myAux) ;
	}
}

#endif // _RDLL_