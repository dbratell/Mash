// SymbolCount.cpp: implementation of the CSymbolCount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymbolCount.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymbolCount::CSymbolCount() : m_symbol(NULL)
{

}

CSymbolCount::~CSymbolCount()
{
	delete m_symbol;

}

void CSymbolCount::AddToCount(unsigned short int inc)
{
	ASSERT(((int)m_count + (int)inc) <= 0xFFFF);
	m_count=static_cast<unsigned short int>(m_count + inc);
}

void CSymbolCount::SetCount(unsigned short int new_count)
{
	m_count=new_count;
}

/**
 * Will own the symbol.
 */
void CSymbolCount::SetSymbol(CSymbol *new_symbol)
{ 
	delete m_symbol;
	m_symbol = new_symbol; 
}

unsigned short int CSymbolCount::GetCount() 
{
	return m_count;
}
