// Symbol.cpp: implementation of the CSymbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymbolData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymbolData::CSymbolData(CSymbol *symbol, 
						 unsigned short low_count, 
						 unsigned short high_count, 
						 unsigned short scale) :
		m_symbol(symbol),
		m_low_count(low_count), 
		m_high_count(high_count),
		m_scale(scale)
{

}

CSymbolData::~CSymbolData()
{
	delete m_symbol;

}

void CSymbolData::SetLowCount(unsigned short int new_low)
{
	ASSERT(FALSE); // Don't call
	m_low_count = new_low;
}

void CSymbolData::SetHighCount(unsigned short int new_high)
{
	ASSERT(FALSE); // Don't call
	m_high_count = new_high;
}

void CSymbolData::SetSymbol(CSymbol *new_symbol) 
{
	ASSERT(FALSE); // Don't call.
	m_symbol = new_symbol;
}

unsigned short int CSymbolData::GetHighCount() const
{
	return m_high_count;
}

unsigned short int CSymbolData::GetLowCount() const
{
	return m_low_count;
}

unsigned short int CSymbolData::GetScale() const
{
	return m_scale;
}

CSymbol *CSymbolData::GetSymbol() 
{
	return m_symbol;
}

