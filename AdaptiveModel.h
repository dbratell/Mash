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

	CSymbolData *MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale);
	CSymbolData *MakeSymbolDataFromWord(const WORD symbolcode);
	void UpdateWithWord(const WORD symbolcode);
	unsigned short int GetScale() const;
	
	//void AddSymbolToCount(CSymbol &new_symbol);
	//void PrintSymbolCounts();
	//void ConstructModelFromCounts();
private:
	unsigned short m_totalcount;
	CMapWordToPtr m_symbolcountmap;
//	CList<CSymbolData,CSymbolData&> m_symboldatalist;
	list<CSymbolCount*> m_symbolcountlist;
};

#endif // !defined(ADAPTIVEMODEL_H)
