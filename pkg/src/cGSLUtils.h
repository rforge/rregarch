/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cGSLUtil.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/01/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CGSLUTILS_H_
#define _CGSLUTILS_H_
#ifdef _GSL_

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

class cGSLUtil
{
	public:
		/* Multivariate normal distribution random number generator
		 *
		 *	n	dimension of the random vetor
		 *	mean	vector of means of size n
		 *	var	variance matrix of dimension n x n
		 *	result	output variable with a single normally-distributed random vector
		 */
		int RandomMultivariateNorm(const gsl_rng *theRng, const int theN, const gsl_vector *theMean, const gsl_matrix *theVar, gsl_vector *theResult);
};
#endif //_GSL_
#endif //_CGSLUTILS_H_