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
}

CSymbol::~CSymbol()
{

}

