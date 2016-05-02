 ###############################################################
 #### RRegArch version 1.0.0                                      
 ####                                                         
 #### File: RRegArchInternals.R 
 ####                                                         
 #### Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ####                                                         
 #### Date: 2009/03/30                                        
 ####                                                         
 ###############################################################

#means
eConst<-as.integer(1)
eAr <- as.integer(2)
eMa <- as.integer(4)
eLinReg <- as.integer(8)
eStdInmean <- as.integer(16)
eVarInMean <- as.integer(32)
#variances
eConstVar <- as.integer(1)
eARCH <- as.integer(2)
eGARCH <- as.integer(4)
eEGARCH <- as.integer(8)
eAPARCH <- as.integer(16)
eTARCH <- as.integer(32)
#Residuals
eNormal <- as.integer(1)
eStudent <- as.integer(2)
eGed <- as.integer(4)
eSkewT<-as.integer(8)

setStorageMode <- function(object) UseMethod("setStorageMode")

setStorageMode.RegArchModelClass <- function(object)
{
    y <- object
    y$condMean <- setStorageMode(object$condMean) 
    y$condVar <- setStorageMode(object$condVar)
    y$condRes <- setStorageMode(object$condRes)   
    storage.mode(y) <- "list"    
    return(y)
}

setStorageMode.condMeanClass <- function(object)
{
    y <- object
    for (i in 1:length(object))
        y[[i]] <- setStorageMode(object[[i]])
    storage.mode(y) <- "list"
    return(y)
}

setStorageMode.ARClass <- function(object)
{   x <- object
    storage.mode(x$meanType) <- "integer"
    storage.mode(x$nParam) <- "integer"
    storage.mode(x$nAR) <- "integer"
    storage.mode(x$AR) <- "double"
    return(x)
}

setStorageMode.MAClass <- function(object)
{   x <- object
    storage.mode(x$meanType) <- "integer"
    storage.mode(x$nMA) <- "integer"
    storage.mode(x$nParam) <- "integer"
    storage.mode(x$MA) <- "double"
    return(x)
}

setStorageMode.VarInMeanClass <- function(object)
{   x <- object
    storage.mode(x$meanType) <- "integer"
    storage.mode(x$nParam) <- "integer"
    storage.mode(x$Delta) <- "double"
    return(x)
}   

setStorageMode.StdInMeanClass <- function(object)
{   x <- object
    storage.mode(x$meanType) <- "integer"
    storage.mode(x$nParam) <- "integer"
    storage.mode(x$Delta) <- "double"
    return(x)
}

setStorageMode.LinRegClass <- function(object)
{   x <- object
    storage.mode(x$meanType) <- "integer"
    storage.mode(x$nBeta) <- "integer"
    storage.mode(x$nObs) <- "integer"
    storage.mode(x$nParam) <- "integer"
    storage.mode(x$Beta) <- "double"
    storage.mode(x$X) <- "double"
    return(x)
}

setStorageMode.ConstMeanClass <- function(object)
{   x <- object
    storage.mode(x$meanType) <- "integer"
    storage.mode(x$Const) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.CondVarClass <- function(object)
{
    return(NextMethod("setStorageMode", object))
}

setStorageMode.ConstVarClass <- function(object)
{   x <- object
    storage.mode(x$varType) <- "integer"
    storage.mode(x$ConstVar) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}
setStorageMode.ARCHClass <- function(object)
{   x <- object
    storage.mode(x$varType) <- "integer"
    storage.mode(x$ConstVar) <- "double"
    storage.mode(x$ARCH) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.GARCHClass <- function(object)
{   x <- object
    storage.mode(x$varType) <- "integer"
    storage.mode(x$ConstVar) <- "double"
    storage.mode(x$ARCH) <- "double"
    storage.mode(x$GARCH) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.TARCHClass <- function(object)
{   x <- object
    storage.mode(x$varType) <- "integer"
    storage.mode(x$ConstVar) <- "double"
    storage.mode(x$ARCHPlus) <- "double"
    storage.mode(x$ARCHMinus) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.EGARCHClass <- function(object)
{   x <- object
    storage.mode(x$varType) <- "integer"
    storage.mode(x$ConstVar) <- "double"
    storage.mode(x$ARCH) <- "double"
    storage.mode(x$GARCH) <- "double"
    storage.mode(x$Theta) <- "double"
    storage.mode(x$Gamma) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.APARCHClass <- function(object)
{   x <- object
    storage.mode(x$varType) <- "integer"
    storage.mode(x$ConstVar) <- "double"
    storage.mode(x$ARCH) <- "double"
    storage.mode(x$GARCH) <- "double"
    storage.mode(x$Delta) <- "double"
    storage.mode(x$Gamma) <- "double"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.RegArchResidualsClass <- function(object)
{
    return(NextMethod("setStorageMode", object))
}

setStorageMode.normalClass <- function(object)
{   x <- object
    storage.mode(x$distrType) <- "integer"
    storage.mode(x$nParam) <- "integer"
    return(x)
}

setStorageMode.studentClass <- function(object)
{
    x<-object
    storage.mode(x$distrType) <- "integer"
    storage.mode(x$nParam) <- "integer"
    storage.mode(x$paramLaw) <- "double"
    return(x)
}
