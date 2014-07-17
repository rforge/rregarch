/**************************************************************
 *** RRegArch version 0.8.0                                      
 ***                                                         
 *** File: RRegArch.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/03/30                                        
 ***                                                         
 **************************************************************/

#include "cRUtils.h"
#include "RegArchDef.h"
#include "RegArchMeanInclude.h"
#include "RegArchVarInclude.h"
#include "RegArchResidualsInclude.h"
#include "cRegArchParam.h"
#include "cRegArchValue.h"
#include "RegArchCompute.h"
#include "cRegArchGradient.h"

#ifdef WIN32
	#define DECL_DLL_EXPORT __declspec(dllexport) 
#else
	#define DECL_DLL_EXPORT 
#endif // WIN32

#ifndef BEG_EXTERN_C
	#define BEG_EXTERN_C extern "C" {
	#define END_EXTERN_C }
#endif //BEG_EXTERN_C

#ifdef _RDLL_
static void SexpToRegArchParam(SEXP theModel, cRegArchParam& theParam, cDMatrix* theMatX)
{
SEXP myCondMeanSEXP ;
cRUtil myRUtil ;
	myRUtil.GetValSexp(theModel, 0, myCondMeanSEXP) ;
int myNMean = length(myCondMeanSEXP) ;
SEXP myMeanCour ;
uint myMeanTypeInt ;
eCondMeanEnum myMeanType ;
	for (register int i = 0 ; i < myNMean ; i++)
	{	myRUtil.GetValSexp(myCondMeanSEXP, i, myMeanCour) ; 
		myRUtil.GetValSexp(myMeanCour, 0, myMeanTypeInt) ;
		myMeanType = (eCondMeanEnum)myMeanTypeInt ;
		switch (myMeanType)
		{	case eConst : // Const Mean
			{	
			double myVal ;
				myRUtil.GetValSexp(myMeanCour, 2, myVal) ;
			cConst myConst = cConst(myVal) ;
				theParam.AddOneMean(myConst) ;
			}
			break ;
			case eAr : // AR
			{	
			int myNAr ;
				myRUtil.GetValSexp(myMeanCour, 1, myNAr) ;
			cDVector myVectAr(myNAr) ;
				myRUtil.GetVectSexp(myMeanCour, 3, myVectAr) ;
			cAr myAr = cAr(myNAr) ;
				myAr.Affect(myVectAr) ;
				theParam.AddOneMean(myAr) ;
				}
			break ;
			case eMa : // MA
			{	
			int myNMa ;
				myRUtil.GetValSexp(myMeanCour, 1, myNMa) ;
			cDVector myVectMa(myNMa) ;
				myRUtil.GetVectSexp(myMeanCour, 3, myVectMa) ;
			cMa myMa = cMa(myNMa) ;
				myMa.Affect(myVectMa) ;
				theParam.AddOneMean(myMa) ;
			}
			break ;
			case eLinReg : // LinReg
			{	
			int myNBeta,
				myNObs	;
				myRUtil.GetValSexp(myMeanCour, 1, myNBeta) ;
				myRUtil.GetValSexp(myMeanCour, 2, myNObs) ;
			cDVector myVectBeta(myNBeta) ;
				myRUtil.GetVectSexp(myMeanCour, 4, myVectBeta) ;
				theMatX->ReAlloc(myNObs, myNBeta) ;
			myRUtil.GetMatSexp(myMeanCour, 5, *theMatX) ;
			cLinReg myLinReg = cLinReg(myNBeta) ;
				myLinReg.Affect(myVectBeta) ;
				theParam.AddOneMean(myLinReg) ;
			}
			break ;
			case eStdDevInMean : // StdDevInMean
			{
			double myDelta ;
				myRUtil.GetValSexp(myMeanCour, 2, myDelta) ;
				cStdDevInMean myStdDevInMean(myDelta) ;
				theParam.AddOneMean(myStdDevInMean) ;
			}
			break ;
			case eVarInMean : // VarInMean
			{
			double myDelta ;
				myRUtil.GetValSexp(myMeanCour, 2, myDelta) ;
				cVarInMean myVarInMean(myDelta) ;
				theParam.AddOneMean(myVarInMean) ;
			}
			break ;
		} // switch
	} // for
SEXP myCondVarSEXP ;
		myRUtil.GetValSexp(theModel, 1, myCondVarSEXP) ;
uint myTypeVarInt ;
eCondVarEnum myTypeVar ;
	myRUtil.GetValSexp(myCondVarSEXP, 0, myTypeVarInt) ;
	myTypeVar = (eCondVarEnum)myTypeVarInt ;
	switch (myTypeVar)
	{	case eCste :
		{
		double myVal ;
			myRUtil.GetValSexp(myCondVarSEXP, 2, myVal) ;
			cConstCondVar myConstVar(myVal) ;
			theParam.AddVar(myConstVar) ;
		}
		break ;
		case eArch :
		{	
		int myNArch ;
			myRUtil.GetValSexp(myCondVarSEXP, 1, myNArch) ;
		cDVector myVectArch(myNArch) ;
		double myConstVar ;
			myRUtil.GetValSexp(myCondVarSEXP, 3, myConstVar) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 4, myVectArch) ;
			cArch myArch = cArch(myNArch) ;
			myArch.Affect(myConstVar, 0) ;
			myArch.Affect(myVectArch, 1) ;
			theParam.AddVar(myArch) ;
		}
		break ;
		case eGarch :
		{	
		int myNArch,
			myNGarch ;
			myRUtil.GetValSexp(myCondVarSEXP, 1, myNArch) ;
			myRUtil.GetValSexp(myCondVarSEXP, 2, myNGarch) ;
		cDVector myVectArch(myNArch),
		  		 myVectGarch(myNGarch) ;
		double myConstVar ;
			myRUtil.GetValSexp(myCondVarSEXP, 4, myConstVar) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 5, myVectArch) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 6, myVectGarch) ;
			cGarch myGarch = cGarch(myNArch, myNGarch) ;
			myGarch.Affect(myConstVar, 0) ;
			myGarch.Affect(myVectArch, 1) ;
			myGarch.Affect(myVectGarch, 2) ;
			theParam.AddVar(myGarch) ;
		}
		break ;
		case eTarch :
		{	
		int myNArch ;
			myRUtil.GetValSexp(myCondVarSEXP, 1, myNArch) ;
		cDVector myVectArchPlus(myNArch),
				 myVectArchMinus(myNArch) ;
		double myConstVar ;
			myRUtil.GetValSexp(myCondVarSEXP, 3, myConstVar) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 4, myVectArchPlus) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 5, myVectArchMinus) ;
		cTarch myTarch = cTarch(myNArch) ;
			myTarch.Affect(myConstVar, 0) ;
			myTarch.Affect(myVectArchPlus, 1) ;
			myTarch.Affect(myVectArchMinus, 2) ;
			theParam.AddVar(myTarch) ;
		}
		break ;
		case eEgarch :
		{
		int myNArch,
			myNGarch ;
			myRUtil.GetValSexp(myCondVarSEXP, 1, myNArch) ;
			myRUtil.GetValSexp(myCondVarSEXP, 2, myNGarch) ;
		cDVector myVectArch(myNArch),
		  		 myVectGarch(myNGarch) ;
		double myConstVar,
			   myTeta,
			   myGamma	;
			myRUtil.GetValSexp(myCondVarSEXP, 4, myConstVar) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 5, myVectArch) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 6, myVectGarch) ;
			myRUtil.GetValSexp(myCondVarSEXP, 7, myTeta) ;
			myRUtil.GetValSexp(myCondVarSEXP, 8, myGamma) ;
		cEgarch myEgarch = cEgarch(myNArch, myNGarch) ;
			myEgarch.Affect(myConstVar, 1) ;
			myEgarch.Affect(myVectArch, 2) ;
			myEgarch.Affect(myVectGarch, 3) ;
			myEgarch.Affect(myTeta, 4) ;
			myEgarch.Affect(myGamma, 5) ;
			theParam.AddVar(myEgarch) ;
		}
		break ;
		case eAparch :
		{
		int myNArch,
			myNGarch ;
			myRUtil.GetValSexp(myCondVarSEXP, 1, myNArch) ;
			myRUtil.GetValSexp(myCondVarSEXP, 2, myNGarch) ;
		cDVector myVectArch(myNArch),
		  		 myVectGarch(myNGarch),
				 myVectGamma(myNArch) ;
		double myConstVar,
			   myDelta	;
			myRUtil.GetValSexp(myCondVarSEXP, 4, myConstVar) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 5, myVectArch) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 6, myVectGamma) ;
			myRUtil.GetVectSexp(myCondVarSEXP, 7, myVectGarch) ;
			myRUtil.GetValSexp(myCondVarSEXP, 8, myDelta) ;
		cAparch myAparch = cAparch(myNArch, myNGarch) ;
			myAparch.Affect(myConstVar, 0) ;
			myAparch.Affect(myDelta, 1) ;
			myAparch.Affect(myVectArch, 2) ;
			myAparch.Affect(myVectGamma, 3) ;
			myAparch.Affect(myVectGarch, 4) ;
			theParam.AddVar(myAparch) ;
		}
		break ;
	} // switch (myTypeVar)
SEXP myCondResidSEXP ;
	myRUtil.GetValSexp(theModel, 2, myCondResidSEXP) ;
uint myTypeResidInt ;
eDistrTypeEnum myTypeResid ;
	myRUtil.GetValSexp(myCondResidSEXP, 0, myTypeResidInt) ;
	myTypeResid = (eDistrTypeEnum)myTypeResidInt ;
	switch (myTypeResid)
	{
		case eNormal :
		{	theParam.AddResid(eNormal) ;
		}
		break ;
		case eStudent :
		{
		double myDof ;
			myRUtil.GetValSexp(myCondResidSEXP, 2, myDof) ;
		cDVector theParamResid(1, myDof) ;
			theParam.AddResid(eStudent, &theParamResid) ;
		}
		break ;
	}
}

BEG_EXTERN_C
DECL_DLL_EXPORT SEXP RRegArchSimul	(	SEXP theNSimul, 
										SEXP theModel
									)
{
cRUtil myRUtil			;
int myNSimul ;
	myNSimul = INTEGER(theNSimul)[0];
cDMatrix myMatX ;
cRegArchParam myParam ;
	SexpToRegArchParam(theModel, myParam, &myMatX) ;
cDMatrix *myMat ;
	if (myMatX.GetNRow() > 0)
		myMat = &myMatX ;
	else
		myMat = NULL ;
cRegArchValue myValue(myNSimul, myMat) ;
	RegArchSimul((uint)myNSimul, myParam, myValue) ;
SEXP myResSEXP,
	 myAuxSEXP[5] ;
	myRUtil.SetVectSexp(myValue.mYt, myAuxSEXP[0]) ;
	myRUtil.SetVectSexp(myValue.mMt, myAuxSEXP[1]) ;
	myRUtil.SetVectSexp(myValue.mHt, myAuxSEXP[2]) ;
	myRUtil.SetVectSexp(myValue.mUt, myAuxSEXP[3]) ;
	myRUtil.SetVectSexp(myValue.mEpst, myAuxSEXP[4]) ;

	PROTECT(myResSEXP = allocVector(VECSXP, 5)) ;
	for (register int i = 0 ; i < 5 ; i++)
		SET_VECTOR_ELT(myResSEXP, i, myAuxSEXP[i]) ;
	UNPROTECT(1) ;
	myRUtil.EndProtect() ;
	return(myResSEXP) ;
}
END_EXTERN_C


BEG_EXTERN_C
DECL_DLL_EXPORT SEXP RRegArchLLH	(	SEXP theNObs,
										SEXP theYt, 
										SEXP theModel
									)
{
cRUtil myRUtil ;
int myNObs = INTEGER(theNObs)[0];
cDVector myYt(myNObs) ;
	myRUtil.GetVectSexp(theYt, 0, myYt) ;

	cDMatrix myMatX ;
cRegArchParam myParam ;
	SexpToRegArchParam(theModel, myParam, &myMatX) ;


cDMatrix *myMat ;
	if ( (myMatX.GetNRow() > 0) && (myMatX.GetNCol() > 0) )
		myMat = &myMatX ;
	else
		myMat = NULL ;
cRegArchValue myValue = cRegArchValue(&myYt, myMat) ;

double myRes = RegArchLLH(myParam, myValue) ;

SEXP myResSEXP ;
	myRUtil.SetValSexp(myRes, myResSEXP) ;
	myRUtil.EndProtect() ;
	return(myResSEXP) ;
}
END_EXTERN_C

BEG_EXTERN_C
DECL_DLL_EXPORT SEXP RRegArchGradLLH	(	SEXP theNObs,
											SEXP theYt, 
											SEXP theModel
										)
{
cRUtil myRUtil ;
int myNObs = INTEGER(theNObs)[0];
cDVector myYt(myNObs) ;
	myRUtil.GetVectSexp(theYt, 0, myYt) ;

	cDMatrix myMatX ;
cRegArchParam myParam ;
	SexpToRegArchParam(theModel, myParam, &myMatX) ;


cDMatrix *myMat ;
	if ( (myMatX.GetNRow() > 0) && (myMatX.GetNCol() > 0) )
		myMat = &myMatX ;
	else
		myMat = NULL ;
cRegArchValue myValue = cRegArchValue(&myYt, myMat) ;
uint myNParam=myParam.GetNParam() ;
cDVector myGrad(myNParam) ;

	RegArchGradLLH(myParam, myValue, myGrad) ;

SEXP myResSEXP ;
	myRUtil.SetVectSexp(myGrad, myResSEXP) ;
	myRUtil.EndProtect() ;
	return(myResSEXP) ;
}
END_EXTERN_C

BEG_EXTERN_C
DECL_DLL_EXPORT SEXP RAsymptoticCovMat	(	SEXP theNObs,
											SEXP theYt, 
											SEXP theModel,
											SEXP theh
										)
{
cRUtil myRUtil ;
int myNObs = INTEGER(theNObs)[0] ;
double myh = REAL(theh)[0] ;
cDVector myYt(myNObs) ;
	myRUtil.GetVectSexp(theYt, 0, myYt) ;

	cDMatrix myMatX ;
cRegArchParam myParam ;
	SexpToRegArchParam(theModel, myParam, &myMatX) ;


cDMatrix *myMat ;
	if ( (myMatX.GetNRow() > 0) && (myMatX.GetNCol() > 0) )
		myMat = &myMatX ;
	else
		myMat = NULL ;


cRegArchValue myValue = cRegArchValue(&myYt, myMat) ;

cDMatrix myCovMat ;
	AsymptoticCovMat(myParam, myValue, myCovMat, myh) ;

SEXP myResSEXP ;
	myRUtil.SetMatSexp(myCovMat, myResSEXP) ;
	myRUtil.EndProtect() ;
	return(myResSEXP) ;
}
END_EXTERN_C
#endif // _RDLL_