// AdaptiveModel.h: interface for the CAdaptiveModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ADAPTIVEMODEL_H)
#define ADAPTIVEMODEL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Symbol.h"
#include "SymbolData.h"
#include "SymbolCount.h"
#include <afxtempl.h>
#include <list>
#include "Model.h"

using namespace std;

class CAdaptiveModel : public CModel
{
public:
	CAdaptiveModel();
	virtual ~CAdaptiveModel();

	void MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale,
		CSymbolData &symboldata /* OUT */);
	void MakeSymbolDataFromWord(const WORD symbolcode,
				CSymbolData &symboldata /* OUT */);
	void UpdateWithWord(const WORD symbolcode);
	unsigned short int GetScale() const;
	void ScaleModel();
	int GetTotalEntries();
	int GetDifferentEntries();
#ifdef DEBUG
	void Dump();
#endif
	
private:
	unsigned short int m_totalcount;
	list<CSymbolCount*> m_symbolcountlist;
};

#endif // !defined(ADAPTIVEMODEL_H)
