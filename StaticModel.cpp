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
//#define DEBUG_PROBABILITY
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


void CStaticModel::MakeSymbolDataFromWord(const WORD symbolcode,
		CSymbolData &symboldata /* OUT */)
{
#ifdef DEBUG_INCODES
	cout << "code(S): "<<symbolcode<<endl;
#endif
	CSymbol *symbol = symboldata.GetSymbol();
	if(symbol)
	{
		symbol->SetCode(symbolcode);
	}
	else
	{
		symbol = new CSymbol();
		symbol->SetCode(symbolcode);
		symboldata.SetSymbol(symbol);
	}

	symboldata.SetLowCount(symbolcode);
	symboldata.SetHighCount(symbolcode+1);
	symboldata.SetScale(END_OF_STREAM_SYMBOLCODE+1);
#ifdef DEBUG_PROBABILITY
			float probability = ((float)1.0)/(END_OF_STREAM_SYMBOLCODE+1);
			cout << " (" << probability;
			cout << " = " << -log(probability)/log(2) << ")" ;
#endif

	return;
}

void CStaticModel::UpdateWithWord(const WORD symbolcode)
{
	// We never update the static model
}

unsigned short int CStaticModel::GetScale() const
{
	return END_OF_STREAM_SYMBOLCODE+1;
}

void CStaticModel::MakeSymbolDataFromCode(unsigned short int count,
		unsigned short int scale,
		CSymbolData &symboldata /* OUT */)
{
#ifdef DEBUG_INCODES
	cout << "decode(S): "<<count<<endl;
#endif
	CSymbol *symbol = symboldata.GetSymbol();
	if(symbol)
	{
		symbol->SetCode(count);
	}
	else
	{
		symbol = new CSymbol();
		symbol->SetCode(count);
		symboldata.SetSymbol(symbol);
	}

	symboldata.SetLowCount(count);
	symboldata.SetHighCount(count+1);
	symboldata.SetScale(END_OF_STREAM_SYMBOLCODE+1);
	return;
}

#ifdef DEBUG
void CStaticModel::Dump()
{
	cout << "--- " << name << " ---" << endl;
	cout << "Static Model with all symbols from <0> to <255> plus ESCAPE and END_OF_STREAM" <<endl;
	cout << endl << endl;
}
#endif
