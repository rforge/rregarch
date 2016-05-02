/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchParam.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

/**
 * \file tutorial.h
 * \author O. Taramasco & J.-B. Durand
 * \date 11-12-08
 */
#ifndef _CREGARCHPARAM_H_
#define _CREGARCHPARAM_H_
#include <math.h>
#include "cCondMean.h"
#include "cAbstCondVar.h"
#include "cAbstResiduals.h"
#include "RegArchVarInclude.h"

/**
 * Class to implement ARMA/GARCH models
 */

class cRegArchParam
{
public :
	cCondMean*		mMean	;
	cAbstCondVar*	mVar	;
	cAbstResiduals*	mResids	;
public :
	/** Constructor using a model for the conditional mean, one for the conditional variance
	 * and one for the distribution of residuals.
	 * theMean and theVar cannot be const due to the use of AddMean and AddVar */
	cRegArchParam(cCondMean* theMean=NULL, cAbstCondVar* theVar=NULL, const cAbstResiduals* theResiduals=NULL) ;
	
	/** Copy constructor */
	cRegArchParam(const cRegArchParam* theParam) ;
	
	/** Destructor */
	virtual ~cRegArchParam() ;
	
	/** Change the number of components for conditional mean */
	void ReAllocMean(int theNewSize) ;
	
	/** Change all components for conditional mean
	 * theCondMean cannot be const due to the use of operator= */
	void AddMean(cCondMean& theCondMean) ;
	
	/** Add one component for conditional mean
	 * theOneMean cannot be const due to the use of operator= */
	void AddOneMean(cAbstCondMean& theOneMean) ;
	
	/** Add (unique) component for conditional mean */
	void AddVar(cAbstCondVar& theCondVar) ;
	
	/** Add (unique) distribution for the distribution of residuals
		 \param theDistrType Type of distribution
		 \param theParam Value of the parameter (if any)
		 \param theForSimul If true, create a gsl object for simulation of residuals
	 * theCondVar cannot be const due to the use of operator= */
	void AddResid(eDistrTypeEnum theDistrType, const cDVector* theParam=NULL, bool theForSimul=true) ;
	
	/** Change all the specification of the distribution of residuals */
	void AddResid(const cAbstResiduals& theCondResids) ;
	
	/** Print model for conditional mean */
	void PrintMean(ostream& theOut=out) const;
	
	/** Print model for conditional variance */
	void PrintVar(ostream& theOut=out) const;
	
	/** Print model for residuals */
	void PrintResiduals(ostream& theOut=out) const;
	
	/** Print the whole ARMA/GARCH model */
	void PrintParam(ostream& theOut=out) const;
	
	/** Return the number of model parameters */
	uint GetNParam(void) const;
	
	/** Return the maximal number of steps in the past necessary,
	 * \e e.g., for likelihood computation */
	uint GetNLags(void) const;
	
	/** Conversion from a cRegArchParam instance to a vector of parameters */
	void RegArchParamToVector(cDVector& theDestVect) const;
	
	/** Change parameter of cRegArchParam instance according to given vector of parameters */
	void VectorToRegArchParam(const cDVector& theSrcVect);
} ;

#endif // _CREGARCHPARAM_H_
