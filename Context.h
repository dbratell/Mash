// Context.h: interface for the CContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTEXT_H__F9E5EE42_5BFB_4FF3_B753_0C95B9AA29CF__INCLUDED_)
#define AFX_CONTEXT_H__F9E5EE42_5BFB_4FF3_B753_0C95B9AA29CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"
#include "ModelSet.h"
#include "StaticModel.h"

class CContext  
{
public:
	CContext(int order=1);
	virtual ~CContext();
	int GetOrder();
	void AddHistory(int symbolcode);
	CModel *GetModel(int rel_order=0);

private:

	int m_order;
	int m_current_order;
	int *m_history;
	CModelSet m_models;

	CStaticModel m_escapemodel;
};

#endif // !defined(AFX_CONTEXT_H__F9E5EE42_5BFB_4FF3_B753_0C95B9AA29CF__INCLUDED_)
