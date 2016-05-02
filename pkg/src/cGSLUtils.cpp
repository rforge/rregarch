/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLUtils.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/01/30                                        
 ***                                                         
 **************************************************************/

#include "cGSLUtils.h"
#ifdef _GSL_

int cGSLUtil::RandomMultivariateNorm(const gsl_rng *theRng, const int theN, const gsl_vector *theMean, const gsl_matrix *theVar, gsl_vector *theResult)
{
	int myK;
	gsl_matrix *myWork = gsl_matrix_alloc(theN, theN);

	gsl_matrix_memcpy(myWork, theVar);
	gsl_linalg_cholesky_decomp(myWork);

	for(myK = 0; myK < theN; myK++)
		gsl_vector_set(theResult, myK, gsl_ran_ugaussian(theRng));

	gsl_blas_dtrmv(CblasLower, CblasNoTrans, CblasNonUnit, myWork, theResult);
	gsl_vector_add(theResult, theMean);

	gsl_matrix_free(myWork);

	return 0;
}

#endif // _GSL_