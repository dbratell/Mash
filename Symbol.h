// Symbol.h: interface for the CSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMBOL_H__3774FDBB_1403_403B_B344_774EE68D0F7B__INCLUDED_)
#define AFX_SYMBOL_H__3774FDBB_1403_403B_B344_774EE68D0F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ESCAPE_SYMBOLCODE 256
#define FLUSH_MODEL_SYMBOLCODE 257
// END_OF_STREAM_SYMBOLCODE _MUST_ be the highest symbolcodenumber
#define END_OF_STREAM_SYMBOLCODE 258 

class CSymbol  
{
public:
	void SetCode(WORD new_code);
	WORD GetCode();
	CSymbol();
	CSymbol(const CSymbol &s);
	virtual ~CSymbol();

private:
	WORD m_code;
};


inline WORD CSymbol::GetCode()
{
	return m_code;
}

inline void CSymbol::SetCode(WORD new_code)
{
	m_code = static_cast<WORD>(new_code);
}

#endif // !defined(AFX_SYMBOL_H__3774FDBB_1403_403B_B344_774EE68D0F7B__INCLUDED_)
