// ModelSet.h: interface for the CModelSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELSET_H__C5F26D4F_643E_4946_A1AD_04A5C67C1822__INCLUDED_)
#define AFX_MODELSET_H__C5F26D4F_643E_4946_A1AD_04A5C67C1822__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#include "Model.h"
#include "AdaptiveModel.h"

//#include <vector>
#include <map>

using namespace std;
class CModelSet;

//typedef vector<CModelSet *> CModelSetVector;
typedef CModelSet * ModelSetPointer;
typedef map<unsigned short, ModelSetPointer> CModelSetMap;

class CModelSet  
{
public:
	CModelSet();
	virtual ~CModelSet();

	CModel *GetModel();
	CModelSet *GetSubModelSet(int i);
	void HalveAndClear();
#ifdef DEBUG
	void Dump();
#endif

private:
	int Size();

	
	CAdaptiveModel *m_model;
	
//	CModelSetVector m_modelsetvector;
	CModelSetMap m_modelsetmap;
};

#endif // !defined(AFX_MODELSET_H__C5F26D4F_643E_4946_A1AD_04A5C67C1822__INCLUDED_)
