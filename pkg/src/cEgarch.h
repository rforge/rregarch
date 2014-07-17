/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: cEgarch.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#ifndef _CEGARCH_H_
#define _CEGARCH_H_

#include "cAbstCondVar.h"
#include "cRegArchValue.h"
#include "cRegArchGradient.h"
#include "RegArchResidualsInclude.h"
/**
 * EGARCH(p, q) model
 *
 * ln h(t) = Cste + Sum_{i=1 to p} Arch(i)*(Teta*Eps(t-i) + Gamma*(abs(Eps(t-i)-E|Esp(t-i)|) 
 *				+ Sum_{j=1 to q} Garch(j)* ln h(t-j)
 *
 */

class cEgarch : public cAbstCondVar
{
private :
	double		mvEspAbsEpsilont ;
	double		mvCste ;
	cDVector	mvArch ;
	cDVector	mvGarch ;
	double		mvTeta ;
	double		mvGamma ;
public :
	cEgarch(int theNArch = 0, int theNGarch=0) ;
	cEgarch(cAbstResiduals* theResiduals, int theNArch = 0, int theNGarch=0) ;
	~cEgarch() ;
	void Print(ostream& theOut) const ;
	void ReAlloc(const cDVector& theParam) ;
	void ReAlloc(int theVal1, int theVal2=0) ;
	void Affect(cAbstCondVar& theCondVarSrc) ;
	void Affect(const cDVector& theDVector, int thePlace=0) ;
	void Affect(double theValue, int thePlace = 0) ;
	double ComputeVar(int theDate, const cRegArchValue& theValue) const ;
	uint GetNParam(void) const ;
	uint GetNLags(void) const ;
	void RegArchParamToVector(cDVector& theDestVect, uint theIndex = 0) ;
	void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) ;
	void ComputeGrad(int theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals) const ;
	void SetEspAbsEps(double theEspAbsEps) ;
} ;

#endif // _CEGARCH_H_
