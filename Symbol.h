// Symbol.h: interface for the CSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMBOL_H__3774FDBB_1403_403B_B344_774EE68D0F7B__INCLUDED_)
#define AFX_SYMBOL_H__3774FDBB_1403_403B_B344_774EE68D0F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ESCAPE_SYMBOLCODE 256
// END_OF_STREAM_SYMBOLCODE _MUST_ be the highest symbolcodenumber
#define END_OF_STREAM_SYMBOLCODE 257 

class CSymbol  
{
public:
	void SetCode(WORD new_code);
	WORD GetCode();
	CSymbol();
	CSymbol(const CSymbol &s);
	virtual ~CSymbol();
//	CString &GetDescription() {return m_description;}
//	void SetDescription(CString &new_description) {m_description = new_description;}

private:
	WORD m_code;
//	CString m_description;
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
