/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: RGslMatrixEquiv.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "RGslMatrixEquiv.h"

gsl_matrix* ourTempMatrixE = NULL ;

gsl_matrix::gsl_matrix(int theNRow, int theNCol)
{
	if ( (theNRow == 0) && (theNCol == 0) )
	{	mData = NULL ;
		mNRow = mNCol = 0 ;
	}
	else
	{	if ( (theNRow >= 0) && (theNCol >= 0))
		{	if ( (mData = Calloc(theNRow*theNCol, double)) == NULL)
				throw cRegArchError("memory problem in gsl_matrix()") ;
			mNRow = (uint)theNRow ;
			mNCol = (uint)theNCol ;
		}
		else
			throw cRegArchError("bad number of rows or columns") ;
	}
}

gsl_matrix::~gsl_matrix()
{
	if (mData != NULL)
	{	mNRow = mNCol = 0 ;
		Free(mData) ;
		mData = NULL ;
	}
}

gsl_matrix* gsl_matrix_alloc(uint theNRow, uint theNCol)
{
	ourTempMatrixE = new gsl_matrix(theNRow, theNCol) ;
	return ourTempMatrixE ;
}

gsl_matrix* gsl_matrix_realloc(uint theNRow, uint theNCol)
{
	if (ourTempMatrixE != NULL)
		gsl_matrix_free(ourTempMatrixE) ;
	ourTempMatrixE = gsl_matrix_alloc(theNRow, theNCol) ;
	return ourTempMatrixE ;
}

void gsl_matrix_set_all(gsl_matrix* theMat, double theVal)
{
	if (theMat != NULL)
	{	
	int k = 0 ;
		for (register uint i = 0 ; i < theMat->mNRow ; i++)
			for (register uint j = 0 ; j < theMat->mNCol ; j++)
				theMat->mData[k++] = theVal ;
	}
	else
		throw cRegArchError("null matrix") ;
}

void gsl_matrix_set(gsl_matrix* theMat, uint theRow, uint theCol, double theVal)
{
	if (theMat != NULL)
	{	if ( (theCol < theMat->mNCol) && (theRow < theMat->mNRow) )
			theMat->mData[theRow*theMat->mNCol+theCol] = theVal;
		else
			throw cRegArchError("wrong row or column number") ;
	}
	else
		throw cRegArchError("null matrix") ;
}

void gsl_matrix_free(gsl_matrix* theMat)
{
	if (theMat != NULL)
	{	theMat->mNCol = theMat->mNRow = 0 ;
		Free(theMat->mData) ;
	}
}

double gsl_matrix_get(gsl_matrix* theMat, uint theRow, uint theCol)
{
	if (theMat == NULL)
		throw cRegArchError("null matrix") ;
	else
	{	if ( (theRow < theMat->mNRow) && (theCol < theMat->mNCol))
			return theMat->mData[theRow*theMat->mNCol+theCol] ;
		else
			throw cRegArchError("wrong number of row or column") ;
	}
}
