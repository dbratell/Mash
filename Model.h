// Model.h: interface for the CModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_H__886F0E8D_4647_4512_8785_69F210CC584B__INCLUDED_)
#define AFX_MODEL_H__886F0E8D_4647_4512_8785_69F210CC584B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SymbolData.h"

class CModel  
{
public:
	CModel();
	virtual ~CModel();

	virtual	CSymbolData *MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale)=0;
	virtual CSymbolData *MakeSymbolDataFromWord(const WORD symbolcode)=0;
	virtual void UpdateWithWord(const WORD symbolcode)=0;
	virtual unsigned short int GetScale() const=0;
	
};

#endif // !defined(AFX_MODEL_H__886F0E8D_4647_4512_8785_69F210CC584B__INCLUDED_)
