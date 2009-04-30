 ###############################################################
 #### RRegArch version 0.8.0                                      
 ####                                                         
 #### File: RRegArch.R 
 ####                                                         
 #### Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ####                                                         
 #### Date: 2009/03/30                                        
 ####                                                         
 ###############################################################

constMeanSet <- function(param)
{
    if (is.null(param))
    {   Res <- list(meanType=eConst, nParam = 1, Const=0.0)
    }
    else
    {   if (is.double(param))
        {   Res <- list(meanType=eConst, nParam = 1, Const=param)
        }
        else
        {    stop("wrong parameter type in constMeanSet\n")
        }
    }
    class(Res) <- "ConstMeanClass"
    return(Res)
}

aRSet <- function(param)
{
    if (is.integer(param))
    {    Res <- list(meanType=eAr, nAR=param, nParam = param, AR=rep(0, param))
    }
    else
    {  if (is.vector(param))
        {   nParam <- length(param)
            Res <- list(meanType=eAr, nAR = nParam, nParam=nParam, AR=param)
        }
        else
        {    stop("wrong parameter type in ARSet\n")
        }
    }
    class(Res) <- "ARClass"
    return(Res)
}

mASet <- function(param)
{
    if (is.integer(param))
    {    Res <- list(meanType=eMa, nMA=param, nParam=param, MA=rep(0, param))
    } 
    else
    {   if (is.vector(param))
        {   nParam <- length(param)
            Res <- list(meanType=eMa, nMA = nParam, nParam=nParam, MA=param)
        }   
        else
        {    stop("wrong parameter type in MASet\n")
        }
    }
    class(Res) <- "MAClass"
    return(Res)
}

linRegSet <- function(param)
{
    if (is.matrix(param))
    {   nObs <- as.integer(nrow(param))
        nBeta <- as.integer(ncol(param))
        Res <- list(meanType=eLinReg, nBeta=nBeta, nObs=nObs, nParam=nBeta, Beta=rep(0, nBeta), X=param)
    }
    else
    {   if (is.list(param))
        {   nBeta=length(param$Beta)
            Res <- list(meanType=eLinReg, nBeta=nBeta, nObs=nrow(param$X), nParam=nBeta, Beta=param$Beta, X=param$X)
        }
           else
        {    stop("wrong parameter type in linRegSet\n")
        }
    }
    class(Res) <- "LinRegClass"
    return(Res)
}     

stdInMeanSet <- function(param)
{
    if (is.null(param))
    {   Res <- list(meanType=eStdInmean, nParam=1, Delta=0.0)
    }
    else
    {   if (is.double(param))
        {   Res <- list(meanType=eStdInmean, nParam=1, Delta=param)
        }
        else
        {    stop("wrong parameter type in StdInMeanSet\n")
        }
    }
    class(Res) <- "StdInMeanClass"
    return(Res)
}

varInMeanSet <- function(param)
{
    if (is.null(param))
    {   Res <- list(meanType=eVarInMean, nParam=1, Delta=0.0)
    }
    else
    {   if (is.double(param))
        {   Res <- list(meanType=eVarInMean, nParam=1, Delta=param)
        }
        else
        {    stop("wrong parameter type in VarInMeanSet\n")
        }
    }
    class(Res) <- "VarInMeanClass"
    return(Res)
}

meanSet <- function(...)
{
    extras <- match.call(expand.dots = FALSE)$... 
    args <- list(...)
    argName <- NULL
    lextras <- length(extras)
    for (i in 1:lextras)
    {   argName <- c(argName, names(extras[i]))
    }    
    condMean <- rep(list(0), lextras)
    for (i in 1:lextras)
    {   Res<-switch(argName[i],
                    AR = aRSet(args[[i]]),
                    nAR = aRSet(as.integer(args[[i]])),
                    MA = mASet(args[[i]]),
                    nMA = mASet(as.integer(args[[i]])),
                    CONST = constMeanSet(args[[i]]), 
                    STDINMEAN = stdInMeanSet(args[[i]]),
                    VARINMEAN = varInMeanSet(args[[i]]),
                    LINREG = linRegSet(args[[i]])
                    )
        if (is.null(Res))
        {   mess <- sprintf("unknown '%s' argument in meanSet", argName[i])
            stop(mess)
        }
        condMean[[i]] <- Res 
    }
    class(condMean) <- "condMeanClass"
    return(condMean)
}        

print.condMeanClass <- function(x, ...)
{
    n<-length(x)
     for (i in 1:n)
        print(x[[i]])
}

namesParam <- function(object) UseMethod("namesParam")

namesParam.condMeanClass <- function(object)
{
    Res <- NULL
    n<-length(object)
    for (i in 1:n)
        Res<-c(Res, namesParam(object[[i]]))
    return(Res)
}
   
namesParam.ARClass <- function(object)
{   AuxNames <- NULL
    for (i in 1:object$nAR)
    {   AuxNames <- c(AuxNames, sprintf("AR[%d]", i))
    }
    return(AuxNames)
}

print.ARClass <- function(x, ...)
{
    cat(sprintf("\nAR[%d] model", x$nAR))
    Aux <- as.matrix(x$AR)
    row.names(Aux) <- namesParam(x)
    Aux1 <- as.data.frame(Aux)
    names(Aux1) <- " "
    print.data.frame(Aux1)
}

namesParam.MAClass <- function(object)
{   AuxNames <- NULL
    for (i in 1:object$nMA)
    {   AuxNames <- c(AuxNames, sprintf("MA[%d]", i))
    }
    return(AuxNames)
}
    
print.MAClass <- function(x, ...)
{
    cat(sprintf("\nMA[%d] model", x$nMA))
    Aux <- as.matrix(x$MA)
    row.names(Aux) <- namesParam(x)
    Aux1 <- as.data.frame(Aux)
    names(Aux1) <- " "
    print.data.frame(Aux1)
}


namesParam.ConstMeanClass <- function(object)
{   AuxNames <- "Const"
    return(AuxNames)
}

print.ConstMeanClass <- function(x, ...)
{
    cat(sprintf("\nConstant mean parameter"))
    Aux <- as.matrix(x$Const)
    row.names(Aux) <- namesParam(x)
     Aux1 <- as.data.frame(Aux)
    names(Aux1) <- " "
    print.data.frame(Aux1)

}

namesParam.StdInMeanClass <- function(object)
{   AuxNames <- "Delta"
    return(AuxNames)
}

print.StdInMeanClass <- function(x, ...)
{
    cat(sprintf("\nStandard deviation in mean Parameter"))
    Aux <- as.matrix(x$Delta)
    row.names(Aux) <- namesParam(x)
     Aux1 <- as.data.frame(Aux)
    names(Aux1) <- " "
    print.data.frame(Aux1)

}

namesParam.VarInMeanClass <- function(object)
{   AuxNames <- "Delta"
    return(AuxNames)
}

print.VarInMeanClass <- function(x, ...)
{
    cat(sprintf("\nVar In Mean Parameter"))
    Aux <- as.matrix(x$Delta)
    row.names(Aux) <- namesParam(x)
     Aux1 <- as.data.frame(Aux)
    names(Aux1) <- " "
    print.data.frame(Aux1)

}

namesParam.LinRegClass <- function(object)
{    AuxNames <- NULL
    for (i in 1:object$nBeta)
    {   AuxNames <- c(AuxNames, sprintf("Beta[%d]", i))
    }
 return(AuxNames)
}

print.LinRegClass <- function(x, ...)
{
    cat(sprintf("\nLinear regression parameters"))
    Aux <- as.matrix(x$Beta)
    row.names(Aux) <- namesParam(x)
    Aux1 <- as.data.frame(Aux)
    names(Aux1) <- " "
    print.data.frame(Aux1)

}

varSet <- function(...)
{
    extras <- match.call(expand.dots = FALSE)$...
    if (is.null(extras))
        stop('varSet must have one argument\n')
        
    args <- list(...)
    argName <- names(extras[1])
    arg <- args[[1]]
    Res<-switch(argName,
                    CONSTVAR = constVarSet(arg),
                    ARCH=aRCHSet(arg),
                    nARCH=aRCHSet(list(ConstVar=0.0, ARCH=rep(0, arg))),
                    GARCH=gARCHSet(arg),
                    nGARCH=gARCHSet(list(ConstVar=0.0, ARCH=rep(0, arg[1]), GARCH=rep(0, arg[2]))),
                    TARCH=tARCHSet(arg),
                    nTARCH=tARCHSet(list(ConstVar=0.0, ARCHPlus=rep(0, arg), ARCHMinus=rep(0, arg))),
                    EGARCH=eGARCHSet(arg),
                    nEGARCH=eGARCHSet(list(ConstVar=0.0, ARCH=rep(0, arg[1]), GARCH=rep(0, arg[2]), Teta=0, Gamma=0)),
                    APARCH=aPARCHSet(arg),
                    nAPARCH=aPARCHSet(list(ConstVar=0.0, ARCH=rep(0, arg[1]), Gamma=rep(0, arg[1]), GARCH=rep(0, arg[2]), Delta=2))
                )
     class(Res) <- c("condVarClass", class(Res))
     return(Res)
 }        

print.condVarClass <- function(x, ...)
{
    return(NextMethod("print", x)) 
}

namesParam.condVarClass <- function(object, ...)
{
    return(NextMethod("namesParam", object)) 
}

constVarSet <- function(Val)
{
    if (is.double(Val))
    {   Res <- list(varType=eConstVar, nParam=1, ConstVar=Val)
    }
    else
    {   if (is.list(Val))
            Res <- list(varType=eConstVar, nParam=1, ConstVar=Val[[1]])
    }
    class(Res) <- "ConstVarClass"
    return(Res)
}

namesParam.ConstVarClass <- function(object)
{   AuxNames <- "ConstVar"
    return(AuxNames)
}

print.ConstVarClass <- function(x, ...)
{
    cat(sprintf("Constant variance model\n"))
    Res <- rep(0, 1)
    Res[1] <- x$ConstVar
    names(Res) <- namesParam(x)
    Res1 <- as.data.frame(Res)
    names(Res1) <- " "
    print(Res1)
}

aRCHSet <- function(Param)
{   if (!is.list(Param))
        stop('Param must be a list (ConstVar="double", ARCH="vector of doubles")')
    if (length(Param) != 2)
        stop('Param must be a list (ConstVar="double", ARCH="vector of doubles")')
   
   if (is.null(Param$ConstVar))
        names(Param)[1] <- "ConstVar"
  
    if (is.null(Param$ARCH))
        names(Param)[2] <- "ARCH"
    
    if (!is.double(Param$ConstVar))
        stop('Param$ConstVar must be a double')
    
    if (!is.vector(Param$ARCH))
        stop('Param$ARCH must be a vector of doubles') 
            
    nARCH <- length(Param$ARCH)  
    Res <- list(varType=eARCH, nARCH = nARCH, nParam=nARCH+1, ConstVar=Param$ConstVar, ARCH=Param$ARCH)
    class(Res) <- "ARCHClass"
    return(Res)
}

namesParam.ARCHClass <- function(object)
{   AuxNames <- "ConstVar"
    for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("ARCH[%d]", i))
   return(AuxNames)
}

print.ARCHClass <- function(x, ...)
{
    cat(sprintf("ARCH(%d) model\n", x$nARCH))
    Res <- rep(0, x$nARCH+1)
    Res[1] <- x$ConstVar
    Res[2:(x$nARCH+1)] <- x$ARCH
    names(Res) <- namesParam(x)
    Res1 <- as.data.frame(Res)
    names(Res1) <- " "
    print(Res1)
}

       
gARCHSet <- function(Param)
{   if (!is.list(Param))
        stop('Param must be a list (ConstVar="double", ARCH="vector of doubles", GARCH="vector of doubles")')
    if (length(Param) != 3)
         stop('Param must be a list (ConstVar="double", ARCH="vector of doubles", GARCH="vector of doubles")')
  
   if (is.null(Param$ConstVar))
        names(Param)[1] <- "ConstVar"
  
    if (is.null(Param$ARCH))
        names(Param)[2] <- "ARCH"
    
    if (is.null(Param$GARCH))
        names(Param)[3] <- "GARCH"
 
    if (!is.double(Param$ConstVar))
        stop('Param$ConstVar must be a double')
    
    if (!is.vector(Param$ARCH))
        stop('Param$ARCH must be a vector of doubles') 

    if (!is.vector(Param$GARCH))
        stop('Param$ARCH must be a vector of doubles') 
            
    nARCH <- length(Param$ARCH)  
    nGARCH <- length(Param$GARCH)
    Res <- list(varType=eGARCH, nARCH = nARCH, nGARCH=nGARCH, nParam=nARCH+nGARCH+1, ConstVar=Param$ConstVar, ARCH=Param$ARCH, GARCH=Param$GARCH)
    class(Res) <- "GARCHClass"
    return(Res)
}

namesParam.GARCHClass <- function(object)
{   AuxNames <- "ConstVar"
    for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("ARCH[%d]", i))
     for (i in 1:object$nGARCH)
        AuxNames <- c(AuxNames, sprintf("GARCH[%d]", i))
   return(AuxNames)
}

print.GARCHClass <- function(x, ...)
{
    cat(sprintf("GARCH(%d, %d) model\n", x$nARCH, x$nGARCH))
    Res <- rep(0, x$nARCH+x$nGARCH+1)
    Res[1] <- x$ConstVar
    Res[2:(x$nARCH+1)] <- x$ARCH
    Res[(x$nARCH+2):(x$nARCH+x$nGARCH+1)] <- x$GARCH
    names(Res) <- namesParam(x)
    Res1 <- as.data.frame(Res)
    names(Res1) <- " "
    print(Res1)
}

tARCHSet <- function(Param)
{
   if (!is.list(Param))
        stop('Param must be a list (ConstVar="double", ARCHPlus="vector of doubles", ARCHMinus="vector of doubles")')
    if (length(Param) != 3)
         stop('Param must be a list (ConstVar="double", ARCHPlus="vector of doubles", ARCHMinus="vector of doubles")')
  
   if (is.null(Param$ConstVar))
        names(Param)[1] <- "ConstVar"
  
    if (is.null(Param$ARCHPlus))
        names(Param)[2] <- "ARCHPlus"
    
    if (is.null(Param$ARCHMinus))
        names(Param)[3] <- "ARCHMinus"
 
    if (!is.double(Param$ConstVar))
        stop('Param$ConstVar must be a double')
    
    if (!is.vector(Param$ARCHPlus))
        stop('Param$ARCHPlus must be a vector of doubles') 

    if (!is.vector(Param$ARCHMinus))
        stop('Param$ARCHMinus must be a vector of doubles') 
    
    if (length(Param$ARCHMinus) != length(Param$ARCHPlus))
        stop("Param$ARCHMinus and Param$ARCHPlus must have the same length")
           
    nARCH <- length(Param$ARCHPlus)  
    Res <- list(varType=eTARCH, nARCH = nARCH, nParam=2*nARCH+1, ConstVar=Param$ConstVar, ARCHPlus=Param$ARCHPlus, ARCHMinus=Param$ARCHMinus)
    class(Res) <- "TARCHClass"
    return(Res)
 }

namesParam.TARCHClass <- function(object)
{   AuxNames <- "ConstVar"
    for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("ARCHPlus[%d]", i))
     for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("ARCHMinus[%d]", i))
   return(AuxNames)
}

print.TARCHClass <- function(x, ...)
{
    cat(sprintf("TARCH(%d) model\n", x$nARCH))
    Res <- rep(0, 2*x$nARCH+1)
    Res[1] <- x$ConstVar
    Res[2:(x$nARCH+1)] <- x$ARCHPlus
    Res[(x$nARCH+2):(2*x$nARCH+1)] <- x$ARCHMinus
     names(Res) <- namesParam(x)
    Res1 <- as.data.frame(Res)
    names(Res1) <- " "
    print(Res1)
}

eGARCHSet <- function(Param)
{
    if (!is.list(Param))
        stop('Param must be a list (ConstVar="double", ARCH="vector of doubles", GARCH="vector of doubles", Teta="double", Gamma="Double")')
    if (length(Param) != 5)
        stop('Param must be a list (ConstVar="double", ARCH="vector of doubles", GARCH="vector of doubles", Teta="double", Gamma="Double")')
  
   if (is.null(Param$ConstVar))
        names(Param)[1] <- "ConstVar"
  
    if (is.null(Param$ARCH))
        names(Param)[2] <- "ARCH"
    
    if (is.null(Param$GARCH))
        names(Param)[3] <- "GARCH"
 
    if (is.null(Param$Teta))
        names(Param)[4] <- "Teta"
 
    if (is.null(Param$Gamma))
        names(Param)[5] <- "Gamma"
 
    if (!is.double(Param$ConstVar))
        stop('Param$ConstVar must be a double')
    
    if (!is.vector(Param$ARCH))
        stop('Param$ARCH must be a vector of doubles') 

    if (!is.vector(Param$GARCH))
        stop('Param$GARCH must be a vector of doubles') 
    
    if (!is.double(Param$Teta))
        stop('Param$Teta must be a double')
 
    if (!is.double(Param$Gamma))
        stop('Param$Gamma must be a double')
 
          
    nARCH <- length(Param$ARCH)  
    nGARCH <- length(Param$GARCH)
    Res <- list(varType=eEGARCH, nARCH = nARCH, nGARCH=nGARCH, nParam=nARCH+nGARCH+3, ConstVar=Param$ConstVar, ARCH=Param$ARCH, GARCH=Param$GARCH, Teta=Param$Teta, Gamma=Param$Gamma)
    class(Res) <- "EGARCHClass"
    return(Res)
}

namesParam.EGARCHClass <- function(object)
{   AuxNames <- "ConstVar"
    for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("ARCH[%d]", i))
     for (i in 1:object$nGARCH)
        AuxNames <- c(AuxNames, sprintf("GARCH[%d]", i))
     AuxNames <- c(AuxNames, "Teta", "Gamma")
   return(AuxNames)
}

print.EGARCHClass <- function(x, ...)
{
    cat(sprintf("EGARCH(%d, %d) model\n", x$nARCH, x$nGARCH))
    Res <- rep(0, x$nARCH+x$nGARCH+3)
    Res[1] <- x$ConstVar
    Res[2:(x$nARCH+1)] <- x$ARCH
    Res[(x$nARCH+2):(x$nARCH+x$nGARCH+1)] <- x$GARCH
    Res[x$nARCH+x$nGARCH+2] <- x$Teta
    Res[x$nARCH+x$nGARCH+3] <- x$Gamma
    names(Res) <- namesParam(x)
    Res1 <- as.data.frame(Res)
    names(Res1) <- " "
    print(Res1)
}

aPARCHSet <- function(Param)
{
     if (!is.list(Param))
        stop('Param must be a list (ConstVar="double", ARCH="vector of doubles", Gamma = "Vector of doubles", GARCH="vector of doubles", Delta="double")')
    if (length(Param) != 5)
         stop('Param must be a list (ConstVar="double", ARCH="vector of doubles", Gamma = "Vector of doubles", GARCH="vector of doubles", Delta="double")')
  
   if (is.null(Param$ConstVar))
        names(Param)[1] <- "ConstVar"
  
    if (is.null(Param$ARCH))
        names(Param)[2] <- "ARCH"
    
    if (is.null(Param$Gamma))
        names(Param)[3] <- "Gamma"
 
    if (is.null(Param$GARCH))
        names(Param)[4] <- "GARCH"
 
    if (is.null(Param$Delta))
        names(Param)[4] <- "Delta"
 
  
    if (!is.double(Param$ConstVar))
        stop('Param$ConstVar must be a double')
    
    if (!is.vector(Param$ARCH))
        stop('Param$ARCH must be a vector of doubles') 

    if (!is.vector(Param$Gamma))
        stop('Param$Gamma must be a double')
        
    if (length(Param$ARCH) != length(Param$Gamma))
        stop("Param$ARCH and Param$Gamma must have the same length")
 
    if (!is.vector(Param$GARCH))
        stop('Param$GARCH must be a vector of doubles') 
    
    if (!is.double(Param$Delta))
        stop('Param$Delta must be a double')
 
          
    nARCH <- length(Param$ARCH)  
    nGARCH <- length(Param$GARCH)
    Res <- list(varType=eAPARCH, nARCH = nARCH, nGARCH=nGARCH, nParam=2*nARCH+nGARCH+2, ConstVar=Param$ConstVar, ARCH=Param$ARCH, Gamma=Param$Gamma, GARCH=Param$GARCH, Delta=Param$Delta)
    class(Res) <- "APARCHClass"
    return(Res)
}

namesParam.APARCHClass <- function(object)
{   AuxNames <- "ConstVar"
    for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("ARCH[%d]", i))
     for (i in 1:object$nARCH)
        AuxNames <- c(AuxNames, sprintf("Gamma[%d]", i))
    for (i in 1:object$nGARCH)
        AuxNames <- c(AuxNames, sprintf("GARCH[%d]", i))
     AuxNames <- c(AuxNames, "Delta")
   return(AuxNames)
}

print.APARCHClass <- function(x, ...)
{
    cat(sprintf("APARCH(%d, %d) model\n", x$nARCH, x$nGARCH))
    Res <- rep(0, 2*x$nARCH+x$nGARCH+2)
    Res[1] <- x$ConstVar
    Res[2:(x$nARCH+1)] <- x$ARCH
    Res[(x$nARCH+2):(2*x$nARCH+1)] <- x$Gamma
    Res[(2*x$nARCH+2):(2*x$nARCH+x$nGARCH+1)] <- x$GARCH
    Res[2*x$nARCH+x$nGARCH+2] <- x$Delta
    
    names(Res) <- namesParam(x)
    Res1 <- as.data.frame(Res)
    names(Res1) <- " "
    print(Res1)
}

normalSet <- function()
{
    Res <- list(distrType=eNormal, nParam=0, distrParameter=NULL)
    class(Res) <-"normalClass"
    return(Res)
}

namesParam.condResidualsClass <- function(object, ...)
{
    return(NextMethod("namesParam", object)) 
}

print.condResidualsClass <- function(x, ...)
{
    return(NextMethod("print", x)) 
}

namesParam.normalClass<-function(object)
{
    return(NULL)
}

print.normalClass<-function(x, ...)
{
    cat(sprintf("Normal residuals\n"))
}

studentSet <- function(parameter)
{   if (!is.numeric(parameter))
        stop("parameter must be the number of d.o.f. for Student residuals\n")
        
    Res <- list(distrType=eStudent, nParam=1, distrParameter=parameter)
    class(Res) <- "studentClass"
    return(Res)
}

namesParam.studentClass<-function(object)
{
    return("dof")
}

print.studentClass <- function(x, ...)
{
    cat(sprintf("Student residuals with %f dof\n", x$distrParameter))
    
}

residualsSet<-function(condResiduals, parameter=NULL)
{
    if (is.na(match(condResiduals, c('NORMAL', 'STUDENT'))))
        stop("CondResid must be in ''NORMAL', 'STUDENT'\n")
 
    if (condResiduals == 'NORMAL')
    {   Res<-normalSet()
        class(Res) <- c("condResidualsClass", class(Res))
        return(Res)
    } 
    
    if (condResiduals == 'STUDENT')
    {   Res<-studentSet(parameter)
        class(Res) <- c("condResidualsClass", class(Res))
       return(Res)
    } 

}

modelSet <- function(condMean, condVar, condRes)
{
    Res <- list(condMean=condMean, condVar=condVar, condRes=condRes)
    class(Res)<-"RegArchModelClass"
    return(Res)
}

namesParam.RegArchModelClass<-function(object)
{
    return(c(namesParam(object$condMean), namesParam(object$condVar), namesParam(object$condRes)))
}

print.RegArchModelClass <- function(x, ...)
{
    if (!is.null(x$condMean))
    {   cat(sprintf("Conditional Mean Model:\n"))
        cat(sprintf("-----------------------"))
        print(x$condMean)
    }
    cat(sprintf("\nConditional Variance Model:\n"))
    cat(sprintf("---------------------------\n"))
    print(x$condVar)
    cat(sprintf("\nConditional Residuals Model:\n"))
    cat(sprintf("----------------------------\n"))
    print(x$condRes)
}

GetNParam<-function(object) UseMethod("GetNParam")
RegArchParamToVector <-function(object) UseMethod("RegArchParamToVector")
VectorToRegArchParam <- function(object, vect) UseMethod("VectorToRegArchParam")
GetNParam.default<-function(object)
{
    return(object$nParam)
}

GetNParam.RegArchModelClass <- function(object)
{
    if (!is.null(object$condMean))
    {   Res <- GetNParam(object$condMean) 
    }
    else
    {   Res <- 0
    }
    Res <- Res + GetNParam(object$condVar) + GetNParam(object$condRes)
    return(Res)
}

RegArchParamToVector.RegArchModelClass <- function(object)
{
    Res <- NULL
    if (!is.null(object$condMean))
    {   Res <- RegArchParamToVector(object$condMean) 
    }
    Res <- c(Res, RegArchParamToVector(object$condVar), RegArchParamToVector(object$condRes))
    return(Res)
}
    
VectorToRegArchParam.RegArchModelClass <- function(object, vect)
{
    Res <- object
    if (!is.null(object$condMean))
    {   Res$condMean <- VectorToRegArchParam(object$condMean, vect)   
        nParamMean <- GetNParam(object$condMean) 
    }
    else
    {   nParamMean <- 0
    }
    nParam <- GetNParam(object)
    vect1 <- vect[(nParamMean+1):nParam] 
    Res$condVar <- VectorToRegArchParam(object$condVar, vect1)
    nParamVar <- GetNParam(object$condVar)
    vect2 <- vect[(nParamMean+nParamVar+1):nParam] 
    Res$condRes <- VectorToRegArchParam(object$condRes, vect2)
    return(Res)
}


GetNParam.condMeanClass <- function(object)
{
    Res <- 0
    for (i in 1:length(object))
        Res <- Res+GetNParam(object[[i]])
    return(Res)
}

RegArchParamToVector.condMeanClass <- function(object)
{
    Res <- NULL
    for (i in 1:length(object))
    {   Res <- c(Res, RegArchParamToVector(object[[i]]))
    }
    return(Res)
}

VectorToRegArchParam.condMeanClass <- function(object, vect)
{   Res <- object
    j <- 1
    vect1 <- vect
    n <- length(vect)
    for (i in 1:length(object))
    {   Res[[i]] <- VectorToRegArchParam(object[[i]], vect1)
        j <- j + GetNParam(object[[i]])
        vect1 <- vect[j:n]
    }
    return(Res)
}

RegArchParamToVector.ConstMeanClass <- function(object)
{
    return(object$Const)
}

VectorToRegArchParam.ConstMeanClass <- function(object, vect)
{
    Res <- object
    Res$Const <- vect[1]
    return(Res)
}

RegArchParamToVector.ARClass <- function(object)
{
    return(object$AR)
}

VectorToRegArchParam.ARClass <- function(object, vect)
{
    Res <- object
    Res$AR <- vect[1:object$nAR]
    return(Res)
}

RegArchParamToVector.MAClass <- function(object)
{
    return(object$AR)
}

VectorToRegArchParam.MAClass <- function(object, vect)
{
    Res <- object
    Res$MA <- vect[1:object$nMA]
    return(Res)
}

RegArchParamToVector.StdInMeanClass <- function(object)
{
    return(object$Delta)
}

VectorToRegArchParam.StdInMeanClass <- function(object, vect)
{
    Res <- object
    Res$Delta <- vect[1]
    return(Res)
}

RegArchParamToVector.VarInMeanClass <- function(object)
{
    return(object$Delta)
}

VectorToRegArchParam.VarInMeanClass <- function(object, vect)
{
    Res <- object
    Res$Delta <- vect[1]
    return(Res)
}

RegArchParamToVector.LinRegClass <- function(object)
{
    return(object$Beta)
}

VectorToRegArchParam.LinRegClass <- function(object, vect)
{
    Res <- object
    Res$Beta <- vect[1:object$nBeta]
    return(Res)
}

RegArchParamToVector.condVarClass <- function(object)
{
    return(NextMethod(generic="RegArchParamToVector", object=object))
}

RegArchParamToVector.ConstVarClass <- function(object)
{
    return(object$ConstVar)
}

VectorToRegArchParam.ConstVarClass <- function(object, vect)
{
    Res <- object
    Res$ConstVar <- vect[1]
    return(Res)
}

RegArchParamToVector.ARCHClass <- function(object)
{
    return(c(object$ConstVar, object$ARCH))
}

VectorToRegArchParam.ARCHClass <- function(object, vect)
{
    Res <- object
    Res$ConstVar <- vect[1]
    Res$ARCH <- vect[2:(object$nARCH+1)]
    return(Res)
}

RegArchParamToVector.GARCHClass <- function(object)
{
    return(c(object$ConstVar, object$ARCH,  object$GARCH))
}

VectorToRegArchParam.GARCHClass <- function(object, vect)
{
    Res <- object
    Res$ConstVar <- vect[1]
    Res$ARCH <- vect[2:(object$nARCH+1)]
    Res$GARCH <- vect[(object$nARCH+2):(object$nARCH+object$nGARCH+1)]
    return(Res)
}

RegArchParamToVector.TARCHClass <- function(object)
{
    return(c(object$ConstVar, object$ARCHPlus,  object$ARCHMinus))
}

VectorToRegArchParam.TARCHClass <- function(object, vect)
{
    Res <- object
    Res$ConstVar <- vect[1]
    Res$ARCHPlus <- vect[2:(object$nARCH+1)]
    Res$ARCHMinus <- vect[(object$nARCH+2):(2*object$nARCH+1)]
    return(Res)
}

RegArchParamToVector.EGARCHClass <- function(object)
{
    return(c(object$ConstVar, object$ARCH,  object$GARCH, object$Teta, object$Gamma))
}

VectorToRegArchParam.EGARCHClass <- function(object, vect)
{
    Res <- object
    Res$ConstVar <- vect[1]
    Res$ARCH <- vect[2:(object$nARCH+1)]
    Res$GARCH <- vect[(object$nARCH+2):(object$nARCH+object$nGARCH+1)]
    Res$Teta <- vect[object$nARCH+object$nGARCH+2]
    Res$Gamma <- vect[object$nARCH+object$nGARCH+3]
    return(Res)
}

RegArchParamToVector.APARCHClass <- function(object)
{
    return(c(object$ConstVar, object$ARCH,  object$Gamma, object$GARCH, object$Delta ))
}

VectorToRegArchParam.APARCHClass <- function(object, vect)
{
    Res <- object
    Res$ConstVar <- vect[1]
    Res$ARCH <- vect[2:(object$nARCH+1)]
    Res$Gamma <- vect[(object$nARCH+2):(2*object$nARCH+1)]
    Res$GARCH <- vect[(2*object$nARCH+2):(2*object$nARCH+object$nGARCH+1)]
    Res$Delta <- vect[2*object$nARCH+object$nGARCH+2]
   return(Res)
}

GetNParam.condVarClass <- function(object)
{
    return(NextMethod(generic="GetNParam", object=object))
}

GetNParam.condResidualsClass <- function(object)
{
    return(NextMethod(generic="GetNParam", object=object))
}

RegArchParamToVector.normalClass <- function(object)
{
    return(NULL)
}

VectorToRegArchParam.normalClass <- function(object, vect)
{
    Res<-object
    return(Res)
}

RegArchParamToVector.studentClass <- function(object)
{
    return(object$distrParameter)
}

VectorToRegArchParam.studentClass <- function(object, vect)
{
    Res <- object
    Res$distrParameter <- vect[1]
    return(Res)
}

RegArchSim <- function(nSimul, model)
{   nSim <- as.integer(nSimul)
    if (class(model) != "RegArchModelClass")
    {   stop("model must be a RegArchModelClass parameter. See modelSet")
    }
    
    model1 <- setStorageMode(model)
    Res1 <- .Call("RRegArchSimul", nSim, model1)
    names(Res1) <- c("Yt", "mt", "ht", "ut", "Epst")  
    return(Res1)         
}

RegArchLLH <- function(Yt, model)
{
    if (!is.vector(Yt))
        stop("Yt must be a vector\n")
    if (class(model) != "RegArchModelClass")
    {   stop("model must be a RegArchModelClass parameter. See modelSet")
    }
    model1 <- setStorageMode(model)
    storage.mode(Yt) <- "double"
    Res1 <- .Call("RRegArchLLH", length(Yt), list(Yt), model1)
    return(Res1)
}
 
RegArchGradLLH <- function(Yt, model)
{
    if (!is.vector(Yt))
        stop("Yt must be a vector\n")
    if (class(model) != "RegArchModelClass")
    {   stop("model must be a RegArchModelClass parameter. See modelSet")
    }
    model1 <- setStorageMode(model)
    storage.mode(Yt) <- "double"
    Res1 <- .Call("RRegArchGradLLH", length(Yt), list(Yt), model1)
    return(Res1)
}

optimfn <- function(Teta, Yt, model)
{
    model1 <- VectorToRegArchParam(model, Teta)
    Res <- -RegArchLLH(Yt, model1)
    return(Res)
}

optimgr <- function(Teta, Yt, model)
{
    model1 <- VectorToRegArchParam(model, Teta)
    Res <- -RegArchGradLLH(Yt, model1)
    return(Res)
}

SetInitPoint <- function(Yt, model)
{
    nMean <- GetNParam(model$condMean)
    nVar <- GetNParam(model$condVar)
    nRes <- GetNParam(model$condRes)
    j1 <- 1
    jmean <- 0
    for (i in 1:length(model$condMean))
    {   if (model$condMean[[i]]$meanType == eConst)
        {    jmean <- j1
        }
        else
        {   j1 <- j1 + GetNParam(model$condMean[[i]])
        }
    }
    Teta <- rep(0, nMean+nVar+nRes)
    
    if (jmean > 0)
        Teta[jmean] <- mean(Yt)
    
    if (!is.na(match(model$condVar$varType,c(eConstVar, eARCH, eGARCH, eTARCH))))
        Teta[nMean+1] <- var(Yt)
    else
    {   if (model$condVar$varType == eEGARCH)
            Teta[nMean+1] <- log(var(Yt))
        else
        {   Teta[nMean+1] <- var(Yt)
            Teta[nMean+nVar] <- 2
        }
    }
    if (nRes > 0)
        Teta[nMean+nVar+1] <- 50
    return(Teta)
}

 AsymptoticCovMat <- function(Yt, model, hh)
 {  if (!is.vector(Yt))
        stop("Yt must be a vector\n")
    if (class(model) != "RegArchModelClass")
    {   stop("model must be a RegArchModelClass parameter. See modelSet")
    }
    model1 <- setStorageMode(model)
    storage.mode(Yt) <- "double"
    Res1 <- .Call("RAsymptoticCovMat", length(Yt), list(Yt), model1, hh)
    return(Res1)
}

RegArchFit <- function(Yt, model, initPoint=NULL, method=NULL, h=1e-3, control = list())
{
    if (is.null(initPoint))
    {   Teta <- SetInitPoint(Yt, model)
    }
    else
    {   if (class(initPoint) == 'RegArchModelClass')
            Teta <- RegArchParamToVector(initPoint)
        else
            Teta <- initPoint
    }
    
    if (is.null(method))
        method <- c("Nelder-Mead")
    
    Res0 <- optim(par=Teta, fn=optimfn, gr=optimgr, Yt=Yt, model=model,
            method = method, lower = -Inf, upper = Inf, control = control, hessian = FALSE)
    
    Res1 <- VectorToRegArchParam(model,Res0$par)
    matCov <- AsymptoticCovMat(Yt, Res1, h) 
    Res2 <- list(param=Res1,asymptCov=matCov, LLH=Res0$value, convergence=Res0$convergence)
    class(Res2) <- "RegArchFitClass"
    return(Res2)
}

print.RegArchFitClass <- function(x, ...)
{
    if (x$convergence != 0)
        cat(sprintf("No convergence\n"))
    print(x$param)
    cat(sprintf("LLH: %f\n", x$LLH))
}

summary.RegArchFitClass <- function(object, ...)
{
    ans = NULL
 
    label <- namesParam(object$param)
    asymptVar <- diag(object$asymptCov)
    se.coef <- sqrt(asymptVar)
    Value <- RegArchParamToVector(object$param)
    tval = Value/se.coef
    prob = 2 * (1 - pnorm(abs(tval)))
    
    Noms <- namesParam(object$param)
    ans$coef = cbind(Value, se.coef, tval, prob)
    dimnames(ans$coef) = list(Noms, c(" Estimate", 
        " Std. Error", " t value", "Pr(>|t|)"))
    class(ans) <- 'summary.RegArchFitClass'
    return(ans)
}

print.summary.RegArchFitClass <- function(x, ...)
{  
     cat("\nCoefficient(s):\n")
    cat("---------------\n")
    signif.stars = getOption("show.signif.stars")
    digits = max(4, getOption("digits") - 4)
    printCoefmat(x$coef, digits = digits, signif.stars = signif.stars, ...)
     
    invisible()
}

  
        
