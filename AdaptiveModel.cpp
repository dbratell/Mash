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

#ifdef DEBUG
//#define DEBUG_PROBABILITY
//#define DEBUG_INCODES
#define DEBUG_MODEL_COUNT
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifdef DEBUG_MODEL_COUNT
	static long number_of_models = 0;
#endif


CAdaptiveModel::CAdaptiveModel()
{
	// Only symbol from the beginning is the ESCAPE symbol

	CSymbol *escape = new CSymbol();
	escape->SetCode(ESCAPE_SYMBOLCODE);
	CSymbolCount *sc = new CSymbolCount();

	sc->SetSymbol(escape);
	sc->SetCount(1);
	m_symbolcountlist.push_front(sc);
	m_totalcount=1;

#ifdef DEBUG_MODEL_COUNT
	++number_of_models;
	if(!(number_of_models%100))
		cout << number_of_models << " ";
#endif

}

CAdaptiveModel::~CAdaptiveModel()
{
	while(!m_symbolcountlist.empty())
	{
		CSymbolCount *sc = m_symbolcountlist.front();
		m_symbolcountlist.pop_front();
		delete sc;
	}

#ifdef DEBUG_MODEL_COUNT
	number_of_models--;
#endif
}

unsigned short int CAdaptiveModel::GetScale() const
{
	return m_totalcount;
}


/**
 * Returns a reference to the symbol attached to the given code. 
 */ 
void CAdaptiveModel::MakeSymbolDataFromWord(const WORD symbolcode,
											CSymbolData &symboldata /* OUT */)
{
#ifdef DEBUG_INCODES
	cout << "code(A): "<<symbolcode<<endl;
#endif
	unsigned short int top_value=0, bottom_value=0,range_value=0;

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

			CSymbol *symbol = symboldata.GetSymbol();
			if(symbol)
			{
				symbol->SetCode(sc.GetSymbol()->GetCode());
			}
			else
			{
				symbol = new CSymbol(*sc.GetSymbol());
				symboldata.SetSymbol(symbol);
			}
			symboldata.SetLowCount(bottom_value);
			symboldata.SetHighCount(top_value);
			symboldata.SetScale(m_totalcount);

			ASSERT(bottom_value<top_value);
#ifdef DEBUG_PROBABILITY
			float probability = ((float)(top_value-bottom_value))/m_totalcount;
			cout << " (" << probability;
			cout << " = " << -log(probability)/log(2) << ")" ;
#endif
			return;
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

			CSymbol *symbol = symboldata.GetSymbol();
			if(symbol)
			{
				symbol->SetCode(sc.GetSymbol()->GetCode());
			}
			else
			{
				symbol = new CSymbol(*sc.GetSymbol());
				symboldata.SetSymbol(symbol);
			}
			symboldata.SetLowCount(bottom_value);
			symboldata.SetHighCount(top_value);
			symboldata.SetScale(m_totalcount);

			ASSERT(bottom_value<top_value);
#ifdef DEBUG_PROBABILITY
			float probability = ((float)(top_value-bottom_value))/m_totalcount;
			cout << " (" << probability;
			cout << " = " << -log(probability)/log(2) << ")" ;
#endif
			return;
		}
	}

	ASSERT(FALSE); // Shouldn't be possible since the list must contain a escape symbol
}

/**
 * Update the model to do better next time.
 * Works by increasing all counts and making sure the most common
 * symbols are in the beginning of the list.
 */
void CAdaptiveModel::UpdateWithWord(const WORD symbolcode)
{
	// The algorithm can only take 14 bit total
	while(m_totalcount > 16383) 
	{
		ScaleModel();
	}


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
	CSymbolCount *sc = new CSymbolCount();

	sc->SetSymbol(newsymbol);
	sc->SetCount(1);
	m_symbolcountlist.push_back(sc);

}

void CAdaptiveModel::MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale,
		CSymbolData &symboldata /* OUT */)
{
#ifdef DEBUG_INCODES
	cout << "decode(A): "<<count<<endl;
#endif
	list<CSymbolCount*>::iterator it;
	int low_count, high_count;

	it = m_symbolcountlist.end();

	while((it != m_symbolcountlist.begin()) && 
		((*(--it))->GetCount() <= count))
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
	it--; // XXX: Remove?


	CSymbol *symbol = symboldata.GetSymbol();
	if(symbol)
	{
		symbol->SetCode(sc.GetSymbol()->GetCode());
	}
	else
	{
		symbol = new CSymbol(*sc.GetSymbol());
		symboldata.SetSymbol(symbol);
	}
	symboldata.SetLowCount(low_count);
	symboldata.SetHighCount(high_count);
	symboldata.SetScale(scale);

	return;
}

/**
 * Halves all values in the model. This is used to keep the total within 14 bits.
 */
void CAdaptiveModel::ScaleModel()
{
	int new_total=0;
	list<CSymbolCount*>::iterator it;

	while(it != m_symbolcountlist.end())
	{
		int new_count;
		CSymbolCount *sc = m_symbolcountlist.front();
		new_count = sc->GetCount();
		if(new_count>1)
			new_count /= 2;
		sc->SetCount(new_count);
		new_total += new_count;
		it++;
	}

	m_totalcount = new_total;
}
