// ArithmeticCoder.h: interface for the CArithmeticCoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARITHMETICCODER_H__F09719DB_0196_4157_A793_0790CB0A016C__INCLUDED_)
#define AFX_ARITHMETICCODER_H__F09719DB_0196_4157_A793_0790CB0A016C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Coder.h"
#include "Symbol.h"
#include "Model.h"
#include "Context.h"

class CArithmeticCoder : public CCoder  
{
public:
	long m_outbits;
	long m_inbits;
	CArithmeticCoder();
	virtual ~CArithmeticCoder();
	void EncodeFile(CFile &in, CFile &out);
	void DecodeFile(CFile &in, CFile &out);
private:
//	long m_current_blocksize;
	unsigned short int m_code;
	unsigned short int m_low;
	unsigned short int m_high;
	long m_underflow_bits;
	CContext *m_context;

	void InitializeArithmeticEncoder();
	void InitializeArithmeticDecoder(CFile &infile);
	int EncodeSymbol(CFile &outfile, CSymbolData &symboldata);
	void FlushArithmeticEncoder(CFile &outfile);
	void OutputBits(CFile &outfile, 
		unsigned short int bits, 
		unsigned int no_of_bits=1);
	unsigned short int InputBits(CFile &infile, 
		unsigned int no_of_bits= 1);
	unsigned short int GetCurrentCount(unsigned short int scale) const;
	void RemoveSymbolFromStream(CFile &in, CSymbolData &symboldata);

};

#endif // !defined(AFX_ARITHMETICCODER_H__F09719DB_0196_4157_A793_0790CB0A016C__INCLUDED_)
