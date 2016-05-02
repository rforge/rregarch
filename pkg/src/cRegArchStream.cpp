/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchStream.cpp 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/03/20                                        
 ***                                                         
 **************************************************************/

#include "cRegArchStream.h"

cRegArchStreamBuf mvStreamBuf;

namespace RegArchStream {
	cRegArchStream out(&mvStreamBuf);
}

cRegArchStreamBuf::cRegArchStreamBuf()
{	mvBuffer = new char[mvBufSize];
	char* base = mvBuffer;
	setp(base, base + mvBufSize - 1); // -1 to make overflow() easier
}

cRegArchStreamBuf::~cRegArchStreamBuf()
{	delete[] mvBuffer;
}

cRegArchStreamBuf::int_type cRegArchStreamBuf::overflow(int_type ch)
{	if (ch != traits_type::eof())
	{	assert(std::less_equal<char*>()(pptr(), epptr()));
		*pptr() = ch;
		pbump(1);
		if (flush())
			return ch;
	}
	return traits_type::eof();
}

int cRegArchStreamBuf::sync()
{	return flush() ? 0 : -1;
}

#ifdef _RDLL_
bool cRegArchStreamBuf::flush()
{	std::ptrdiff_t n = pptr() - pbase();
	pbump(-n);
	char myBuf[mvBufSize] = {0};
	strncpy(myBuf, mvBuffer, n);
	Rprintf(myBuf);
	return true;
}
#else
bool cRegArchStreamBuf::flush()
{	std::ptrdiff_t n = pptr() - pbase();
    pbump(-n);
    return std::cout.write(pbase(), n);
}
#endif //_RDLL_