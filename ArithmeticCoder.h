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
	unsigned short int m_code;
	//CModel m_model;
	unsigned short int m_low;
	unsigned short int m_high;
	long m_underflow_bits;

//	void BuildModel(CFile &input/*, CFile &output*/);
	void InitializeArithmeticEncoder();
	void InitializeArithmeticDecoder(CFile &infile);
	void EncodeSymbol(CFile &outfile, CSymbolData &symboldata);
	void FlushArithmeticEncoder(CFile &outfile);
	void OutputBits(CFile &outfile, 
		unsigned short int bits, 
		unsigned int no_of_bits=1);
	unsigned short int InputBits(CFile &infile, 
		unsigned int no_of_bits= 1);
	unsigned short int GetCurrentCount(unsigned short scale) const;
	void RemoveSymbolFromStream(CFile &in, CSymbolData &symboldata);

	CModel *GetModel(int context);

	CModel *m_staticmodel;
	CModel *m_adaptivemodel;



};

#endif // !defined(AFX_ARITHMETICCODER_H__F09719DB_0196_4157_A793_0790CB0A016C__INCLUDED_)
