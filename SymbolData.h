// Symbol.h: interface for the CSymbol class.
//
//////////////////////////////////////////////////////////////////////
#ifndef SYMBOL_DATA_H
#define SYMBOL_DATA_H

#pragma once

#include "Symbol.h"

class CSymbolData
{
public:
	CSymbolData(CSymbol *symbol=NULL, 
				 unsigned short int low_count=0, 
				 unsigned short int high_count=0, 
				 unsigned short int scale=0);
	virtual ~CSymbolData();

	unsigned short int GetHighCount() const;
	unsigned short int GetLowCount() const;
	unsigned short int GetScale() const;
	void SetScale(unsigned short int new_scale);
	void SetLowCount(unsigned short int new_low);
	void SetHighCount(unsigned short int new_high);
	CSymbol *GetSymbol();
	void SetSymbol(CSymbol *new_symbol);

private:
	CSymbol *m_symbol;
	unsigned short int m_low_count;
	unsigned short int m_high_count;
	unsigned short int m_scale;
};

#endif