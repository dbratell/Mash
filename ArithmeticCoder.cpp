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

#ifdef DEBUG
//#define DEBUG_CALCULATIONS
//#define DEBUG_UNDERFLOW_CALCULATIONS
//#define DEBUG_BITS
//#define DEBUG_LOW_HIGH
//#define DEBUG_IN_OUT
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Default constructor.
 */
CArithmeticCoder::CArithmeticCoder()
{
	m_context = new CContext(2);

}

/**
 * Destructor
 */
CArithmeticCoder::~CArithmeticCoder()
{
	delete m_context;
}


/**
 *  Codes the infile into the outfile
 * 
 *  XXX: Errorhandling?
 */
void CArithmeticCoder::EncodeFile(CFile &infile, CFile &outfile)
{
	CSymbolData symboldata;
	unsigned char buffer;

	InitializeArithmeticEncoder();

	int context = 0;

	WORD symbolcode_to_send;

	int backoff = 0;
	while(true)
	{
		backoff = 0;

		if(infile.Read(&buffer,1))
		{
			symbolcode_to_send = buffer;
			m_inbits += 8;
		}
		else
		{
			symbolcode_to_send = END_OF_STREAM_SYMBOLCODE;
		}


#ifdef DEBUG_IN_OUT
		if(END_OF_STREAM_SYMBOLCODE != symbolcode_to_send)
		{
			cout << "\nIn: '" << buffer << "'\n" << "Out: ";
		}
		else
		{
			cout << "\nIn: EOF\nOut: ";
		}
#endif
		bool escapesymbol = false;

		do
		{
			CModel *model = m_context->GetModel(backoff);
			model->MakeSymbolDataFromWord(
				static_cast<WORD>(symbolcode_to_send),
				symboldata);
#ifdef DEBUG_CALCULATIONS
			cout << "(sd:"<<symboldata->GetLowCount()<<"-"<<
				symboldata->GetHighCount()<<")"<<endl;
#endif
			EncodeSymbol(outfile, symboldata);
			// Was it an escape symbol?
			if(ESCAPE_SYMBOLCODE == symboldata.GetSymbol()->GetCode())
			{
#ifdef DEBUG_IN_OUT
				cout << "+";
#endif
				escapesymbol = true;
				backoff--;
			}
			else
			{
				escapesymbol = false;
			}
		} while(escapesymbol);

		if(END_OF_STREAM_SYMBOLCODE == symbolcode_to_send)
		{
			break;
		}
		// Update all used models
		for(int i=backoff; i<=0; i++)
		{
			CModel *realmodel = m_context->GetModel(i);
			realmodel->UpdateWithWord(context);
		}
		m_context->AddHistory(symbolcode_to_send);

	}

	FlushArithmeticEncoder(outfile);
#ifdef DEBUG_IN_OUT
	cout << "ZEROES";
#endif
	OutputBits(outfile, 0L, 16);

}

/**
 *  Assumes that the in file is coded using Mash and fills the outfile
 *  with the decoded data.
 * 
 *  XXX: Errorhandling?
 */
void CArithmeticCoder::DecodeFile(CFile &in, CFile &out)
{
	CSymbolData symboldata;

	InitializeArithmeticDecoder(in);

	int context = 0;
	int backoff = 0;

	while(true)
	{
#ifdef DEBUG_IN_OUT
		cout << "\nIn: ";
#endif
		bool escapesymbol = false;
		backoff = 0;
		do
		{
			CModel *model = m_context->GetModel(backoff);
			unsigned short int scale = model->GetScale();
			unsigned short int count = GetCurrentCount(scale);

			model->MakeSymbolDataFromCode(count,scale,symboldata);
#ifdef DEBUG_CALCULATIONS
			cout << "(sd:"<<symboldata->GetLowCount()<<"-"<<
				symboldata->GetHighCount()<<")"<<endl;
#endif
			context = symboldata.GetSymbol()->GetCode();
			if(END_OF_STREAM_SYMBOLCODE == context)
			{
				return;
			}
			RemoveSymbolFromStream(in, symboldata);
			if(ESCAPE_SYMBOLCODE == context)
			{
#ifdef DEBUG_IN_OUT
				cout << "+";
#endif
				escapesymbol = true;
				backoff--;
//				context = ESCAPE_SYMBOLCODE;
			}
			else
			{
				escapesymbol = false;
				// Update all used models
				for(int i=backoff; i<=0; i++)
				{
					CModel *realmodel = m_context->GetModel(i);
					realmodel->UpdateWithWord(context);
				}
				m_context->AddHistory(context);
			}
		} while(escapesymbol);

		ASSERT(context>=0 && context<256);
		char buffer[1];
		buffer[0] = static_cast<char>(context);
		out.Write(buffer,1);
#ifdef DEBUG_IN_OUT
		cout << "\nOut: " << buffer[0]<<endl;
#endif
		m_outbits += 8;

	}

}

/**
 * Initializes the encoder part of the coder. Must be called
 * before starting encoding.
 */
void CArithmeticCoder::InitializeArithmeticEncoder()
{
	// XXX: Move to the constructor?
	m_inbits = 0;
	m_outbits = 0;

	m_low = 0;
	m_high = 0xFFFF;
	m_underflow_bits = 0;
}

/**
 * Initializes the decoder part of the coder. Must be called
 * before starting decoding.
 */
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

/**
 * Convert a symbol to bits which are sent to the outfile.
 */
void CArithmeticCoder::EncodeSymbol(CFile &outfile, CSymbolData &symboldata)
{
	ASSERT(m_high > m_low);
	// Calculate new range
	long range = (m_high-m_low)+1;
	m_high = m_low + (unsigned short int)
		(( range * symboldata.GetHighCount()) / symboldata.GetScale() -1);
#ifdef DEBUG_CALCULATIONS
	cout << "(L = "<<m_low<<"+"<<range<<"*"<<symboldata.GetLowCount();
	cout << "/"<< symboldata.GetScale()<<")"<<endl;
	cout << "(H = "<<m_low<<"+"<<range<<"*"<<symboldata.GetHighCount();
	cout << "/"<< symboldata.GetScale()<<"-1)"<<endl;
#endif
	m_low = m_low + (unsigned short int)
		(( range * symboldata.GetLowCount()) / symboldata.GetScale());
	ASSERT(m_high >= m_low); // XXX: Got Assertions with strict inequality

	// Output data if we can

	while(true)
	{
#ifdef DEBUG_LOW_HIGH
			cout << "(" << m_low << "-" << m_high << ")";
#endif
		if((m_high & 0x8000) == (m_low & 0x8000))
		{
			// Same top bit
			OutputBits(outfile,
				m_high & 0x8000,
				1);
			while(m_underflow_bits>0) {
				// Output all stored underflow bits
				OutputBits(outfile,
					(~m_high) & 0x8000,
					1);
				m_underflow_bits--;
#ifdef DEBUG_UNDERFLOW_CALCULATIONS
				cout << "(u--="<<m_underflow_bits<<")";
#endif
			}
		} 
		else if((m_low & 0x4000) && !(m_high & 0x4000))
		{
			m_underflow_bits++;
#ifdef DEBUG_UNDERFLOW_CALCULATIONS
			cout << "(u++="<<m_underflow_bits<<")";
#endif
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

/**
 * Empty the registers used during coding.
 */
void CArithmeticCoder::FlushArithmeticEncoder(CFile &outfile)
{
#ifdef DEBUG_IN_OUT
	cout << "FLUSH";
#endif

	OutputBits(outfile, (m_low & 0x4000)<<1, 1);
#ifdef DEBUG_LOW_HIGH
	cout << "(" << m_low << "-" << m_high << ")";
#endif
	m_underflow_bits++;
#ifdef DEBUG_UNDERFLOW_CALCULATIONS
		cout << "(u++="<<m_underflow_bits<<")";
#endif
	while(m_underflow_bits-- > 0)
	{
#ifdef DEBUG_UNDERFLOW_CALCULATIONS
		cout << "(u--="<<m_underflow_bits<<")";
#endif
		OutputBits(outfile, (~m_low & 0x4000)<<1,1 );
#ifdef DEBUG_LOW_HIGH
	cout << "(" << m_low << "-" << m_high << ")";
#endif
	}
}

/**
 * Output bits to the file. The bits are taken from the Most significant
 * bits first.
 * // XXX: Writes chars '0' and '1' instead of real bits
 */
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
#ifdef DEBUG_BITS
			cout << "1";
#endif
		}
		else
		{
			buffer[0]='0';
			outfile.Write(buffer,1);
#ifdef DEBUG_BITS
			cout << "0";
#endif
		}
		bits <<= 1;
		no_of_bits--;
		m_outbits++; // Could move out of loop
	}
	
	outfile.Flush();

}

/**
 * Reads bits from the input. 
 * // XXX: Reads chars '0' and '1' instead of real bits
 */
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
		if(!infile.Read(buffer,1))
		{
#ifdef DEBUG
			cout << "ERROR! SHOULD HAVE RECEIVED END_OF_STREAM_SYMBOLCODE BEFORE END OF FILE"<<endl;
#endif
			ASSERT(FALSE);
			return 0;
		}
		switch(buffer[0])
		{
		case '0':
			result+=0;
#ifdef DEBUG_BITS
			cout << "0";
#endif
			break;
		case '1':
			result +=1;
#ifdef DEBUG_BITS
			cout << "1";
#endif
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


unsigned short int CArithmeticCoder::GetCurrentCount(unsigned short int scale) const
{
#ifdef DEBUG_CALCULATIONS
//	cout << "Scale: "<<scale;
#endif
	long range;

	unsigned short int count;

	range = (long)(m_high-m_low) + 1;
#ifdef DEBUG_CALCULATIONS
//	cout << ", range: "<<range;
#endif
	count = (unsigned short int)
		((((long) (m_code - m_low) +1 ) * scale - 1) / range );
#ifdef DEBUG_CALCULATIONS
	cout << ", count = (("<< m_code <<"-"<< m_low<<"+1)*"<<scale<<"-1)/"<<range<<")\n";
	cout << "(count="<<count<<")\n";
#endif
	return count;
}

void CArithmeticCoder::RemoveSymbolFromStream(CFile &in, CSymbolData &symboldata)
{
	long range;

	range = (long)(m_high - m_low) +1;
	m_high = m_low + (unsigned short int) 
		((range * symboldata.GetHighCount()) / symboldata.GetScale() -1);
#ifdef DEBUG_CALCULATIONS
	cout << "(L = "<<m_low<<"+"<<range<<"*"<<symboldata.GetLowCount();
	cout << "/"<< symboldata.GetScale()<<")"<<endl;
	cout << "(H = "<<m_low<<"+"<<range<<"*"<<symboldata.GetHighCount();
	cout << "/"<< symboldata.GetScale()<<"-1)"<<endl;
#endif
	m_low = m_low + (unsigned short int) 
		((range * symboldata.GetLowCount()) / symboldata.GetScale());

	while(true)
	{
#ifdef DEBUG_LOW_HIGH
		cout << "(" << m_low << "-" << m_high << ")";
#endif
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

		m_low <<= 1;
		m_high <<= 1;
		m_high |= 1;
		m_code <<= 1;
		m_code += InputBits(in,1);
	}

}
