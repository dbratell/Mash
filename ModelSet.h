// ModelSet.h: interface for the CModelSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELSET_H__C5F26D4F_643E_4946_A1AD_04A5C67C1822__INCLUDED_)
#define AFX_MODELSET_H__C5F26D4F_643E_4946_A1AD_04A5C67C1822__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"
#include <vector>

using namespace std;
class CModelSet;

typedef vector<CModelSet *> CModelSetVector;

class CModelSet  
{
public:
	CModelSet();
	virtual ~CModelSet();

	CModel *GetModel();
	CModelSet *GetSubModelSet(int i);

private:
	CModel *m_model;
	
	CModelSetVector m_modelsetvector;
};

#endif // !defined(AFX_MODELSET_H__C5F26D4F_643E_4946_A1AD_04A5C67C1822__INCLUDED_)
