// ModelSet.cpp: implementation of the CModelSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModelSet.h"

#include "AdaptiveModel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModelSet::CModelSet() : m_model(NULL)
{
	m_modelsetvector.reserve(256);
	for(int i = 0; i<256; i++)
	{
		m_modelsetvector[i]=NULL;
	}

}

CModelSet::~CModelSet()
{
	delete m_model;
	
	for(int i=0; i<256; i++)
	{
		delete m_modelsetvector[i];
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
	if(NULL == m_modelsetvector[index])
		m_modelsetvector[index] = new CModelSet();

	return m_modelsetvector[index];
}
