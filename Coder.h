// Coder.h: interface for the CCoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODER_H__8D7B874E_29C1_4BE2_9881_EAE3225864B0__INCLUDED_)
#define AFX_CODER_H__8D7B874E_29C1_4BE2_9881_EAE3225864B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCoder  
{
public:
	CCoder();
	virtual ~CCoder();

	virtual void EncodeFile(CFile &in, CFile &out) = 0;
	virtual void DecodeFile(CFile &in, CFile &out) = 0;

};

#endif // !defined(AFX_CODER_H__8D7B874E_29C1_4BE2_9881_EAE3225864B0__INCLUDED_)
