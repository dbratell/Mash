// StaticModel.cpp: implementation of the CStaticModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StaticModel.h"
#include "Symbol.h"
#include "SymbolData.h"
#ifdef DEBUG
#include <iostream>
#include <math.h>
using namespace std;
#endif // ifdef DEBUG


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef DEBUG
#define DEBUG_PROBABILITY
//#define DEBUG_INCODES
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaticModel::CStaticModel()
{

}

CStaticModel::~CStaticModel()
{
}


CSymbolData *CStaticModel::MakeSymbolDataFromWord(const WORD symbolcode)
{
#ifdef DEBUG_INCODES
	cout << "code(S): "<<symbolcode<<endl;
#endif
	CSymbol *symbol = new CSymbol();
	symbol->SetCode(symbolcode);
	CString string("<escaped symbol>");
	symbol->SetDescription(string);

	CSymbolData *sd = new CSymbolData(symbol,
		symbolcode,
		symbolcode+1,
		END_OF_STREAM_SYMBOLCODE+1);
#ifdef DEBUG_PROBABILITY
			float probability = ((float)1.0)/(END_OF_STREAM_SYMBOLCODE+1);
			cout << " (" << probability;
			cout << " = " << -log(probability)/log(2) << ")" ;
#endif

	return sd;
}

void CStaticModel::UpdateWithWord(const WORD symbolcode)
{
	// We never update the static model
}

unsigned short int CStaticModel::GetScale() const
{
	return END_OF_STREAM_SYMBOLCODE+1;
}

CSymbolData *CStaticModel::MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale)
{
#ifdef DEBUG_INCODES
	cout << "decode(S): "<<count<<endl;
#endif
	CSymbol *symbol = new CSymbol();
	symbol->SetCode(count);
	CString string("<escaped symbol>");
	symbol->SetDescription(string);

	CSymbolData *sd = new CSymbolData(symbol,
		count,
		count+1,
		END_OF_STREAM_SYMBOLCODE+1);
	return sd;
}
