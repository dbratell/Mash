// Symbol.cpp: implementation of the CSymbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Symbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymbol::CSymbol()
{

}

CSymbol::CSymbol(const CSymbol &other)
{
	m_code = other.m_code;
	m_description = other.m_description;
}

CSymbol::~CSymbol()
{

}

WORD CSymbol::GetCode()
{
	return m_code;
}

void CSymbol::SetCode(WORD new_code)
{
	m_code = static_cast<WORD>(new_code);
}
