/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: RGslVectorEquiv.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "RGslVectorEquiv.h"
gsl_vector* ourTempVectorE = NULL ;

gsl_vector::gsl_vector(int theSize, double theVal)
{
	if (theSize == 0)
	{	mData = NULL ;
		size = 0 ;
	}
	else
	{	if (theSize > 0)
		{	if ( (mData = Calloc(theSize, double)) == NULL)
				error("memory error in gsl_vector()") ;
			size = theSize ;
			for (register int i = 0 ; i < theSize ; i++)
				mData[i] = theVal ;
		}
		else
			error("size of vector must be positive") ;
	}
}
gsl_vector::~gsl_vector()
{
	if (mData != NULL)
	{	Free(mData) ;
		size = 0 ;
		mData = NULL ;
	}
}

gsl_vector* gsl_vector_alloc(size_t theSize)
{
	ourTempVectorE = new gsl_vector(theSize) ;
	return ourTempVectorE ;
}

void gsl_vector_set_all(gsl_vector* mvVect, double theVal)
{
	for (register int i = 0 ; i < (int)mvVect->size ; i++)
		mvVect->mData[i] = theVal ;
}

void gsl_vector_set(gsl_vector* theVect, size_t theIndex, double theVal)
{
	if ( (theIndex >= 0) && (theIndex < theVect->size) )
		theVect->mData[theIndex] = theVal ;
	else
		throw cRegArchError("bad index") ;
}


double gsl_vector_get(const gsl_vector* theVect, int theIndex)
{
	if ( (theIndex >= 0) && (theIndex < (int)theVect->size) )
		return theVect->mData[theIndex];
	else
		throw cRegArchError("bad index") ;
}

void gsl_vector_free(gsl_vector* theVect)
{
	if (theVect != NULL)
	{	Free(theVect->mData) ;
		theVect->size = 0 ;
	}
}

double* gsl_vector_ptr(gsl_vector* theVect, size_t theIndex)
{
	if (theVect == NULL)
		error("null vector") ;
	
	if ((theIndex >= 0) && (theIndex < theVect->size))
		return &(theVect->mData[theIndex]) ;
	else
		error("bad index") ;
}

void gsl_vector_scale(gsl_vector* theVect, double theVal)
{
	if (theVect == NULL)
		error("null vector") ;
	else
		for (register int i = 0 ; i < (int)theVect->size ; i++)
			theVect->mData[i] *= theVal ;
}
