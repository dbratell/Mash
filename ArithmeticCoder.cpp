// ArithmeticCoder.cpp: implementation of the CArithmeticCoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArithmeticCoder.h"
#include "StaticModel.h"
#include "AdaptiveModel.h"
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArithmeticCoder::CArithmeticCoder()
{
	m_staticmodel = new CStaticModel;
	m_adaptivemodel = new CAdaptiveModel;

}

CArithmeticCoder::~CArithmeticCoder()
{
	delete m_staticmodel;
	delete m_adaptivemodel;

}


void CArithmeticCoder::EncodeFile(CFile &infile, CFile &outfile)
{
	unsigned char buffer;

	InitializeArithmeticEncoder();

	int context = 0;
	int realcontext = 0;

	while(infile.Read(&buffer,1))
	{
		m_inbits += 8;

		cout << "\nIn: '" << buffer << "'\n" << "Out: ";
		bool escapesymbol = false;

		do
		{
			CModel *model = GetModel(context);
			CSymbolData *symboldata = model->MakeSymbolDataFromWord(
				static_cast<WORD>(buffer));
			EncodeSymbol(outfile, *symboldata);
			// Was it an escape symbol?
			if(ESCAPE_SYMBOLCODE == symboldata->GetSymbol()->GetCode())
			{
				cout << "+";
				escapesymbol = true;
				context = ESCAPE_SYMBOLCODE;
			}
			else
			{
				escapesymbol = false;
			}
			delete symboldata;

		} while(escapesymbol);

		CModel *model = GetModel(realcontext);
		model->UpdateWithWord(buffer);

		context = realcontext = buffer;

	}

	CModel *model = GetModel(context);
	CSymbolData *symboldata = model->MakeSymbolDataFromWord(
		END_OF_STREAM_SYMBOLCODE);
	EncodeSymbol(outfile, *symboldata);
	delete symboldata;

	FlushArithmeticEncoder(outfile);
	OutputBits(outfile, 0L, 16);


}

void CArithmeticCoder::DecodeFile(CFile &in, CFile &out)
{

	InitializeArithmeticDecoder(in);

	int context = 0;
	int realcontext = 0;

	while(true)
	{
		bool escapesymbol = false;

		do
		{
			CModel *model = GetModel(context);
			unsigned short int scale = model->GetScale();
			unsigned short int count = GetCurrentCount(scale);
			CSymbolData *symboldata = model->MakeSymbolDataFromCode(count,scale);
			context = symboldata->GetSymbol()->GetCode();
			if(END_OF_STREAM_SYMBOLCODE == context)
			{
				return;
			}
			RemoveSymbolFromStream(in, *symboldata);
			if(ESCAPE_SYMBOLCODE == context)
			{
#ifdef DEBUG
				cout << "+";
#endif
				escapesymbol = true;
//				context = ESCAPE_SYMBOLCODE;
			}
			else
			{
#ifdef DEBUG
				cout << (char)context;
#endif
				escapesymbol = false;
				CModel *realmodel = GetModel(realcontext);
				realmodel->UpdateWithWord(context);
				realcontext = context;
			}
			delete symboldata;
		} while(escapesymbol);

		ASSERT(context>=0 && context<256);
		char buffer[1];
		buffer[0] = static_cast<char>(context);
		out.Write(buffer,1);

	}

}

void CArithmeticCoder::InitializeArithmeticEncoder()
{
	m_low = 0;
	m_high = 0xFFFF;
	m_underflow_bits = 0;

	// XXX: Move to the constructor?
	m_inbits = 0;
	m_outbits = 0;
}

void CArithmeticCoder::InitializeArithmeticDecoder(CFile &infile)
{
	// XXX: Move to the constructor?
	m_inbits = 0;
	m_outbits = 0;

	m_low = 0;
	m_high = 0xFFFF;
	m_code = 0;
	for(int i = 0; i<16; i++)
	{
		m_code <<= 1;
		m_code += InputBits(infile,1);
	}

}

void CArithmeticCoder::EncodeSymbol(CFile &outfile, CSymbolData &symboldata)
{
	ASSERT(m_high > m_low);
	// Calculate new range
	long range = (m_high-m_low)+1;
	m_high = m_low + (unsigned short int)
		(( range * symboldata.GetHighCount()) / symboldata.GetScale() -1);
	m_low = m_low + (unsigned short int)
		(( range * symboldata.GetLowCount()) / symboldata.GetScale());
	ASSERT(m_high > m_low);

	// Output data if we can

	while(true)
	{
		if((m_high & 0x8000) == (m_low & 0x8000))
		{
			// Same top bit
			OutputBits(outfile,m_high,1);
			while(m_underflow_bits>0) {
				// Output all stored underflow bits
				OutputBits(outfile, ~m_high,1);
				m_underflow_bits--;
			}
		} 
		else if((m_low & 0x4000) && !(m_high & 0x4000))
		{
			m_underflow_bits++;
			m_low &=0x3FFF;
			m_high |=0x4000;
		}
		else
		{
			return;
		}

		// Shift the rest if the bits
		m_low <<= 1;
		m_high <<= 1;
		// Set the low bit on the high number
		m_high |= 1;

		ASSERT(m_high > m_low);
	}

}


void CArithmeticCoder::FlushArithmeticEncoder(CFile &outfile)
{
	OutputBits(outfile, m_low & 0x400, 1);
	m_underflow_bits++;
	while(m_underflow_bits-- > 0)
	{
		OutputBits(outfile, ~m_low & 0x4000 );
	}
}

void CArithmeticCoder::OutputBits(CFile &outfile, 
								  unsigned short int bits, 
								  unsigned int no_of_bits /* = 1 */) 
{
	char buffer[10];
	ASSERT(no_of_bits >=0);
	ASSERT(no_of_bits <= (sizeof(unsigned short int)*8));

	while(no_of_bits)
	{
		if(bits & 0x8000) 
		{
			buffer[0]='1';
			outfile.Write(buffer,1);
			cout << "1";
		}
		else
		{
			buffer[0]='0';
			outfile.Write(buffer,1);
			cout << "0";
		}
		bits <<= 1;
		no_of_bits--;
		m_outbits++; // Could move out of loop
	}
	
	outfile.Flush();

}

unsigned short int CArithmeticCoder::InputBits(CFile &infile, 
								  unsigned int no_of_bits /* = 1 */) 
{
	char buffer[10];
	ASSERT(no_of_bits >=0);
	ASSERT(no_of_bits <= (sizeof(unsigned short int)*8));
	unsigned short int result=0;

	while(no_of_bits)
	{
		result <<= 1;
		infile.Read(buffer,1);
		switch(buffer[0])
		{
		case '0':
			result+=0;
			break;
		case '1':
			result +=1;
			break;
		default:
			ASSERT(FALSE);
			// This shouldn't happen!
		}
		no_of_bits--;
		m_inbits++; // Could move out of loop
	}

	return result;
}


CModel *CArithmeticCoder::GetModel(int context)
{
	if(ESCAPE_SYMBOLCODE == context)
		return m_staticmodel;

	return m_adaptivemodel;
}

unsigned short int CArithmeticCoder::GetCurrentCount(unsigned short scale) const
{
	long range;

	unsigned short int count;

	range = (long)(m_high-m_low) + 1;
	count = (unsigned short int)((((long) (m_code - m_low) +1 ) * scale - 1) / range );
	return count;
}

void CArithmeticCoder::RemoveSymbolFromStream(CFile &in, CSymbolData &symboldata)
{
	long range;

	range = (long)(m_high - m_low) +1;
	m_high = m_low + (unsigned short int) 
		((range * symboldata.GetHighCount()) / symboldata.GetScale() -1);
	m_low = m_low + (unsigned short int) 
		((range * symboldata.GetLowCount()) / symboldata.GetScale());

	while(true)
	{
		if( (m_high & 0x8000) == (m_low & 0x8000) )
		{
		}
		else if( (m_low & 0x4000) == 0x4000 && 
			(m_high & 0x4000) == 0) // XXX: Can be written shorter
		{
			m_code ^= 0x4000;
			m_low &= 0x3fff; // XXX: book had 0x3ffff
			m_high |= 0x4000;
		}
		else
		{
			return;
		}
#ifdef DEBUG
		if(m_code&0x8000)
			cout << "1";
		else
			cout << "0";
#endif

		m_low <<= 1;
		m_high <<= 1;
		m_high |= 1;
		m_code <<= 1;
		m_code += InputBits(in,1);
	}

}
