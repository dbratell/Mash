// Context.cpp: implementation of the CContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Context.h"

#include "AdaptiveModel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_ORDER 3
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContext::CContext(int order /* =1 */) : m_current_order(0)
{
	if(order>MAX_ORDER)
	{
		m_order = MAX_ORDER;
	}
	else if(order<0)
	{
		m_order = 0;
	}
	else
	{
		m_order = order;
	}

	m_history = new int[m_order];

}

CContext::~CContext()
{
	delete[] m_history;
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
	ASSERT(rel_order <= 0);
	if(m_current_order+rel_order<0)
	{
		return &m_escapemodel;
	}

	CModelSet *modelset = &m_models;
	for(int i=-rel_order; i<m_current_order; i++)
	{
		modelset = modelset->GetSubModelSet(m_history[i]);
	}
	return modelset->GetModel();
}

