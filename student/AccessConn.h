// AccessConn.h: interface for the CAccessConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSCONN_H__6B4FD1EC_37A7_4DDD_9C99_EA12E246F501__INCLUDED_)
#define AFX_ACCESSCONN_H__6B4FD1EC_37A7_4DDD_9C99_EA12E246F501__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#import "C:\Program Files\Common Files\System\ado\msado15.dll"    no_namespace  rename("BOF","adoBOF") rename("EOF","adoEOF")



//�����ݿ����

class CAccessConn  
{
public:
	CAccessConn();
	virtual ~CAccessConn();
public:
	_ConnectionPtr m_pConnection;						//ָ��Connection�����ָ��
	_RecordsetPtr  m_pRecordset;						//....Recordset........	
public:
	void OnInitAccessConn();							//�������ݿ�ĳ�ʼ��
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);		//���в�ѯ������һ��Recordset�ĵ�ַ
	BOOL ExecuteSQL(_bstr_t bstrSQL);					//ִ��SQL���
	void CutConn();										//�Ͽ������ݿ������
};

#endif // !defined(AFX_ACCESSCONN_H__6B4FD1EC_37A7_4DDD_9C99_EA12E246F501__INCLUDED_)
