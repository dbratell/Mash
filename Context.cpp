// Context.cpp: implementation of the CContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Context.h"

#include "AdaptiveModel.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_ORDER 6
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContext::CContext(int order /* =1 */) : m_current_order(0)
{
	if(order>MAX_ORDER)
	{
		m_order = MAX_ORDER;
#ifdef DEBUG
		cout << "ILLEGAL ORDER! Max is "<< MAX_ORDER << " and you said " 
			<< order << endl;
#endif
	}
	else if(order<0)
	{
		m_order = 0;
#ifdef DEBUG
		cout << "ILLEGAL ORDER! Mus pe positive and you said " << order << endl;
#endif
	}
	else
	{
		m_order = order;
	}

	m_history = new int[m_order];
	m_models = new CModelSet();

#ifdef DEBUG
	m_escapemodel.name="<ESC>";
#endif
}

CContext::~CContext()
{
	delete[] m_history;
	delete m_models;
}

int CContext::GetOrder()
{
	return m_order;
}

void CContext::AddHistory(int symbolcode)
{
	if(0 == m_order)
		return;

	if(m_current_order == m_order)
	{
		// History full
		// Move down data to make room for the new code
		for(int i=0; i<m_current_order-1; i++)
		{
			m_history[i] = m_history[i+1];
		}
	}
	else
	{
		m_current_order++;
	}

	m_history[m_current_order-1] = symbolcode;

}

/**
 * rel_order is a negative (or zero) number that can be used
 * to use previous contexts
 */
CModel *CContext::GetModel(int rel_order /* =0 */)
{
#ifdef DEBUG
	CString name;
#endif

	ASSERT(rel_order <= 0);
	if(m_current_order+rel_order<0)
	{
		return &m_escapemodel;
	}

	CModelSet *modelset = m_models;
	for(int i=-rel_order; i<m_current_order; i++)
	{
#ifdef DEBUG
		if(isprint(m_history[i]))
		{
			name += (char)m_history[i];
		}
		else
		{
			name += "?";
		}
#endif
		modelset = modelset->GetSubModelSet(m_history[i]);
	}
	CModel *model = modelset->GetModel();
#ifdef DEBUG
	model->name=name;
#endif
	return model;
}


#ifdef DEBUG
void CContext::Dump()
{
	cout << "CONTEXT : '";
	for(int i=0; i<m_current_order; i++)
	{
		if(isprint(m_history[i]))
		{
			cout << (char)m_history[i];
		}
		else
		{
			cout << "?";
		}
	}
	cout << "'" << endl;

	m_models->Dump();
}
#endif

/**
 * Called to empty the context and restart. This is used to keep memory usage down
 * and maybe to remove an ineffective model.
 */
void CContext::ResetContext()
{
	m_current_order = 0;

	delete m_models;
	m_models = new CModelSet();

}

void CContext::DampenHistory()
{
	m_models->HalveAndClear();
}

