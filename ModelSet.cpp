// ModelSet.cpp: implementation of the CModelSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModelSet.h"

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


#define TOTAL_SIZE_CUTOFF 3
#define AVERAGE_COUNT_CUTOFF 2
#define MODELSETSIZE_CUTOFF 10

#ifdef DEBUG
//#define DEBUG_FLUSHING
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModelSet::CModelSet() : m_model(NULL)
{
}

CModelSet::~CModelSet()
{
	delete m_model;
	CModelSetMap::iterator it = m_modelsetmap.begin();

	while(it != m_modelsetmap.end())
	{
		
		delete (*it).second;
		it++;
	}
}

CModel *CModelSet::GetModel()
{
	if(NULL == m_model)
	{
		m_model = new CAdaptiveModel();
	}
	return m_model;
}

CModelSet *CModelSet::GetSubModelSet(int index)
{
	CModelSetMap::iterator it = m_modelsetmap.find(index);

	if(it != m_modelsetmap.end())
	{
		return (*it).second;
	}

	// There was no earlier model

	CModelSet *modelset = new CModelSet();
	m_modelsetmap[index] = modelset;

	return modelset;

}

void CModelSet::HalveAndClear()
{
	if(NULL != m_model)
	{
		m_model->ScaleModel();
		// If the model is tiny, delete it
		int size = m_model->GetTotalEntries();
		int entries = m_model->GetDifferentEntries();
		if((size < TOTAL_SIZE_CUTOFF) ||
			(entries*AVERAGE_COUNT_CUTOFF > size))
		{
			delete m_model;
			m_model = NULL;
		}
	}

	// Recurse
	CModelSetMap::iterator it = m_modelsetmap.begin();

	while(it != m_modelsetmap.end())
	{
		(*it).second->HalveAndClear();
		if((*it).second->Size() < MODELSETSIZE_CUTOFF)
		{
			delete (*it).second;
			it = m_modelsetmap.erase(it);
//			it++;
			// it will point to the next element in the map
			// XXX: Will the map have the same "order" as before?
		} 
		else 
		{
#ifdef DEBUG_FLUSHING
		cout << "Behåll modell (" << (*it).second->Size() << ") ";
#endif

			it++;
		}
	}
}

int CModelSet::Size()
{
	int size = 0;
	if(NULL != m_model)
	{
		size = m_model->GetTotalEntries();
	}

	CModelSetMap::iterator it = m_modelsetmap.begin();

	while(it != m_modelsetmap.end())
	{
		CModelSet *set = (*it).second;
		if(set != NULL)
		{
			size += set->Size();
		}
		it++;
	}

	return size;
}

#ifdef DEBUG
void CModelSet::Dump()
{
	if(NULL != m_model)
		m_model->Dump();

	CModelSetMap::iterator it = m_modelsetmap.begin();

	while(it != m_modelsetmap.end())
	{
		(*it).second->Dump();
		it++;
	}
}
#endif
