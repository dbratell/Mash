// AdaptiveModel.cpp: implementation of the CAdaptiveModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdaptiveModel.h"
#include "Symbol.h"
#include "SymbolCount.h"
#include "SymbolData.h"
#include <algorithm>
#include <math.h>
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdaptiveModel::CAdaptiveModel()
{
	// Only symbol from the beginning is the ESCAPE symbol

	CSymbol *escape = new CSymbol();
	escape->SetCode(ESCAPE_SYMBOLCODE);
	CString description("ESCAPESYMBOL");
	escape->SetDescription(description);
	CSymbolCount *sc = new CSymbolCount();

	sc->SetSymbol(escape);
	sc->SetCount(1);
	m_symbolcountlist.push_front(sc);
	m_totalcount=1;
	

//	m_symbolcountlist.

}

CAdaptiveModel::~CAdaptiveModel()
{
	POSITION pos;
	WORD w;
	void *pointer;
	CSymbolCount *sc;
	// Clean up m_symbolcountmap
	pos = m_symbolcountmap.GetStartPosition();
	while(pos != NULL)
	{
		m_symbolcountmap.GetNextAssoc(pos, w, pointer);
		sc = reinterpret_cast<CSymbolCount *>(pointer);
		CSymbol *symbol = sc->GetSymbol();
		// printf("Delete %d\n", symbol->GetCode());
		delete symbol;
		delete sc;
	}
	m_symbolcountmap.RemoveAll();

	while(!m_symbolcountlist.empty())
	{
		CSymbolCount *sc = m_symbolcountlist.front();
		m_symbolcountlist.pop_front();
		delete sc;
	}
}

unsigned short int CAdaptiveModel::GetScale() const
{
	return m_totalcount;
}


/**
 * We will own the symbol.
 */
/*void CAdaptiveModel::AddSymbolToCount(CSymbol &new_symbol)
{
	CSymbolCount *symbolcount_in_map;
	void *pointer;

	if(m_symbolcountmap.Lookup(new_symbol.GetCode(),pointer))
	{
		symbolcount_in_map = reinterpret_cast<CSymbolCount *>(pointer);
		// Already in map
		symbolcount_in_map->AddToCount(1);
	} 
	else
	{
		// Not in map yet
		CSymbolCount *sc = new CSymbolCount();
		sc->SetSymbol(&new_symbol);
		sc->SetCount(1);
		m_symbolcountmap.SetAt(new_symbol.GetCode(),sc);
	}

	m_totalcount ++;
}
*/
/**
 * Returns a reference to the symbol attached to the given code. 
 */ 
CSymbolData *CAdaptiveModel::MakeSymbolDataFromWord(const WORD symbolcode)
{
	unsigned short top_value=0, bottom_value=0,range_value=0;

	list<CSymbolCount*>::iterator it; // = m_symbolcountlist.iterator;

	it = m_symbolcountlist.begin();

	while(it != m_symbolcountlist.end())
	{
		CSymbolCount &sc = **it;

		if(symbolcode == sc.GetSymbol()->GetCode())
		{
			top_value = sc.GetCount();
			it++;
			if(it == m_symbolcountlist.end()) 
				bottom_value = 0; // not necessary
			else
				bottom_value = (*it)->GetCount();

			CSymbolData *sd = new CSymbolData(new CSymbol(*sc.GetSymbol()),
				bottom_value,
				top_value,
				m_totalcount);
			ASSERT(sd->GetLowCount() < sd->GetHighCount());
#ifdef DEBUG
			float probability = ((float)(top_value-bottom_value))/m_totalcount;
			cout << " (" << probability;
			cout << " = " << -log(probability)/log(2) << ")" ;
#endif
			return sd;
		}
		it++;
	}

	// Let's use the escape symbol
	while(it != m_symbolcountlist.begin())
	{
		it--;
		CSymbolCount &sc = **it;
		if(ESCAPE_SYMBOLCODE == sc.GetSymbol()->GetCode())
		{
			top_value = sc.GetCount();
			it++;
			if(it != m_symbolcountlist.end()) 
				bottom_value = (*it)->GetCount();
			else
				bottom_value = 0; // not necessary

			CSymbolData *sd = new CSymbolData(new CSymbol(*sc.GetSymbol()),
				bottom_value,
				top_value,
				m_totalcount);
			ASSERT(sd->GetLowCount() < sd->GetHighCount());
#ifdef DEBUG
			float probability = ((float)(top_value-bottom_value))/m_totalcount;
			cout << " (" << probability;
			cout << " = " << -log(probability)/log(2) << ")" ;
#endif
			return sd;
		}
	}

	ASSERT(FALSE); // Shouldn't be possible since the list must contain a escape symbol

	// Silence compiler
	return new CSymbolData(new CSymbol(),0,0,0);


	// First check if we already know this symbol
/*	CSymbolCount *symbolcount_in_map;
	void *pointer;
	if(m_symbolcountmap.Lookup(symbolcode,pointer))
	{
		symbolcount_in_map = reinterpret_cast<CSymbolCount *>(pointer);
		return *new CSymbolData(NULL, 0,0,0); // symbolcount_in_map->GetSymbol();  // XXX
	} 
	else 
	{
		CSymbol *s = new CSymbol();
		s->SetCode(symbolcode);
		if(symbolcode>0 && symbolcode<256 && isprint(symbolcode))
		{
			char c[2], *ch;
			c[0] = static_cast<char>(symbolcode);
			c[1] = '\0';
			ch = c;
			CString str(ch);
			s->SetDescription(str);
		}
		else
		{
			CString desc;
			desc.Format("<%d>",symbolcode);
			s->SetDescription(desc);
		}
		// Not in map yet
		CSymbolCount *sc = new CSymbolCount();
		sc->SetSymbol(s);
		sc->SetCount(0);
		m_symbolcountmap.SetAt(s->GetCode(),sc);
//		return *new CSymbolData(NULL, 0,0,0); // symbolcount_in_map->GetSymbol();  // XXX
//		return NULL; // XXX: s;
	}
*/
}
/*
void CAdaptiveModel::PrintSymbolCounts()
{
	POSITION pos;
	WORD w;
	void *pointer;
	CSymbolCount *sc;
	pos = m_symbolcountmap.GetStartPosition();
	while(pos != NULL)
	{
		m_symbolcountmap.GetNextAssoc(pos, w, pointer);
		sc = reinterpret_cast<CSymbolCount *>(pointer);
		CString str;
		str.Format("Symbol: '%s' %ld",sc->GetSymbol()->GetDescription(),
			sc->GetCount());
		printf(str);
		printf("\n");
	}
	
}
*/	
/*void CAdaptiveModel::ConstructModelFromCounts()
{
	POSITION mappos;
	WORD w;
	void *pointer;
	CSymbolCount *sc;
	mappos = m_symbolcountmap.GetStartPosition();
	while(mappos != NULL)
	{
		m_symbolcountmap.GetNextAssoc(mappos, w, pointer);
		sc = reinterpret_cast<CSymbolCount *>(pointer);

		// Find a place in the list for this symbol
		
		CSymbolData data;
		POSITION listpos = m_symboldatalist.GetHeadPosition();
		while (listpos != NULL)
		{
			data = m_symboldatalist.GetNext(listpos);

			ASSERT(sc->GetSymbol()->GetCode() != data.GetSymbol()->GetCode());
			if(sc->GetSymbol()->GetCode() < data.GetSymbol()->GetCode())
			{
				break;
			}
		}
		// this is the place
		CSymbolData *symboldata = new CSymbolData();
		symboldata->SetSymbol(sc->GetSymbol());
		m_symboldatalist.InsertBefore(listpos,*symboldata);
		delete symboldata;
		
	}

	// We now have an ordered list of symbols
	CSymbolData data;
	POSITION listpos = m_symboldatalist.GetHeadPosition();
	while (listpos != NULL)
	{
		data = m_symboldatalist.GetNext(listpos);
		
		ASSERT(sc->GetSymbol()->GetCode() != data.GetSymbol()->GetCode());
		if(sc->GetSymbol()->GetCode() < data.GetSymbol()->GetCode())
		{
			break;
		}
	}
}
*/

/**
 * Update the model to do better next time.
 * Works by increasing all counts and making sure the most common
 * symbols are in the beginning of the list.
 */
void CAdaptiveModel::UpdateWithWord(const WORD symbolcode)
{
	m_totalcount++;
	list<CSymbolCount*>::iterator it;

	it = m_symbolcountlist.begin();

	while(it != m_symbolcountlist.end())
	{
		CSymbolCount &sc = **it;

		sc.AddToCount(1);

		if(symbolcode != sc.GetSymbol()->GetCode())
		{
			it++;
			continue;
		}

		// We found it
		int belowcount, prevtotalcount;
		prevtotalcount = sc.GetCount();
		it++;
		if(it == m_symbolcountlist.end())
		{
			belowcount = prevtotalcount;
		}
		else
		{
			belowcount = prevtotalcount-(*it)->GetCount();
		}
		it--;

		// Go back up, swapping if we are better.
		while(it != m_symbolcountlist.begin())
		{
			// The actual count is in belowcount. 
			it--;
			int abovecount = (*it)->GetCount()-prevtotalcount;
			if(belowcount <= abovecount)
			{
				break;
			}

			CSymbolCount &above = **it;
			list<CSymbolCount*>::iterator tempit = it;
			tempit++;
			CSymbolCount &below = **tempit;
			iter_swap(it,tempit);
			it = tempit;
			// Recalculate counts
			above.SetCount(above.GetCount()-belowcount);
			below.SetCount(below.GetCount()+abovecount);

			prevtotalcount = below.GetCount();

			it--;
		
		}

		return;
	}

	// Wasn't in list at all
	CSymbol *newsymbol = new CSymbol();
	newsymbol->SetCode(symbolcode);
	if(symbolcode>0 && symbolcode<256 && isprint(symbolcode))
	{
		char c[2], *ch;
		c[0] = static_cast<char>(symbolcode);
		c[1] = '\0';
		ch = c;
		CString str(ch);
		newsymbol->SetDescription(str);
	}
	CSymbolCount *sc = new CSymbolCount();

	sc->SetSymbol(newsymbol);
	sc->SetCount(1);
	m_symbolcountlist.push_back(sc);

}

CSymbolData *CAdaptiveModel::MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale)
{
	list<CSymbolCount*>::iterator it;
	int low_count, high_count;

	it = m_symbolcountlist.end();

	while((it != m_symbolcountlist.begin()) && 
		(count < (*(--it))->GetCount()))
	{
	}

	CSymbolCount &sc = **it;
	high_count = sc.GetCount();
	it++;
	if(it == m_symbolcountlist.end())
	{
		low_count = 0;
	}
	else
	{
		low_count = (*it)->GetCount();
	}
	it--;


	CSymbolData *sd = new CSymbolData(new CSymbol(*sc.GetSymbol()),
		low_count, 
		high_count, 
		scale);

	return sd;
}

