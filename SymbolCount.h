// SymbolCount.h: interface for the CSymbolCount class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMBOLCOUNT_H__A32948CC_7E75_49CE_98BC_9E77A9822C1B__INCLUDED_)
#define AFX_SYMBOLCOUNT_H__A32948CC_7E75_49CE_98BC_9E77A9822C1B__INCLUDED_

#include "Symbol.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSymbolCount  
{
public:
	CSymbol* GetSymbol() {return m_symbol;}
	void SetSymbol(CSymbol *new_symbol);
	unsigned short int GetCount() {return m_count;}
	void SetCount(unsigned short int new_count);
	void AddToCount(unsigned short int inc);
	CSymbolCount();
	virtual ~CSymbolCount();

private:
	CSymbol *m_symbol;
	unsigned short int m_count;
};

#endif // !defined(AFX_SYMBOLCOUNT_H__A32948CC_7E75_49CE_98BC_9E77A9822C1B__INCLUDED_)
