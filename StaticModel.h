// StaticModel.h: interface for the CStaticModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICMODEL_H__A7A32FB8_DF80_4C65_A80A_FBF63BA74ADF__INCLUDED_)
#define AFX_STATICMODEL_H__A7A32FB8_DF80_4C65_A80A_FBF63BA74ADF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"

class CStaticModel : public CModel  
{
public:
	CStaticModel();
	virtual ~CStaticModel();

	void MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale,
		CSymbolData &symboldata /* OUT */);
	void MakeSymbolDataFromWord(const WORD symbolcode,
		CSymbolData &symboldata /* OUT */);
	void UpdateWithWord(const WORD symbolcode);
	unsigned short int GetScale() const;
};

#endif // !defined(AFX_STATICMODEL_H__A7A32FB8_DF80_4C65_A80A_FBF63BA74ADF__INCLUDED_)
