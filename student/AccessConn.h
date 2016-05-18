// AccessConn.h: interface for the CAccessConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSCONN_H__6B4FD1EC_37A7_4DDD_9C99_EA12E246F501__INCLUDED_)
#define AFX_ACCESSCONN_H__6B4FD1EC_37A7_4DDD_9C99_EA12E246F501__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#import "C:\Program Files\Common Files\System\ado\msado15.dll"    no_namespace  rename("BOF","adoBOF") rename("EOF","adoEOF")



//对数据库的类

class CAccessConn  
{
public:
	CAccessConn();
	virtual ~CAccessConn();
public:
	_ConnectionPtr m_pConnection;						//指向Connection对象的指针
	_RecordsetPtr  m_pRecordset;						//....Recordset........	
public:
	void OnInitAccessConn();							//连接数据库的初始化
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);		//进行查询，返回一个Recordset的地址
	BOOL ExecuteSQL(_bstr_t bstrSQL);					//执行SQL语句
	void CutConn();										//断开与数据库的连接
};

#endif // !defined(AFX_ACCESSCONN_H__6B4FD1EC_37A7_4DDD_9C99_EA12E246F501__INCLUDED_)
