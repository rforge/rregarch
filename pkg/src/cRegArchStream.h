/**************************************************************
 *** RRegArch version 1.0.0                                      
 ***                                                         
 *** File: cRegArchStream.h 
 ***                                                         
 *** Author: Franck Bitard <franck.bitard@gmail.com> 
 ***                                                         
 *** Date: 2016/03/20                                        
 ***                                                         
 **************************************************************/

#ifndef _CREGARCHSTREAM_H_
#define _CREGARCHSTREAM_H_
#include <iostream>
#include <cassert>
#include <functional>

#ifdef _RDLL_
#include <R.h>
#endif //_RDLL_

class cRegArchStream : public std::ostream 
{	public:
		cRegArchStream(std::streambuf* theStreamBuf) : std::ostream(theStreamBuf) {};
};

namespace RegArchStream {
	using namespace std;
	extern cRegArchStream out;
}

class cRegArchStreamBuf : public std::streambuf
{	public:
        cRegArchStreamBuf();
		~cRegArchStreamBuf();

    protected:
        bool flush();

    private:
		static const std::size_t mvBufSize = 256;
		char* mvBuffer;

        int_type overflow(int_type ch);
        int sync();
};

#endif //_CREGARCHSTREAM_H_