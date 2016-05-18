// AccessConn.cpp: implementation of the CAccessConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "student.h"
#include "AccessConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccessConn::CAccessConn()
{

}

CAccessConn::~CAccessConn()
{

}



void CAccessConn::OnInitAccessConn()
{
	CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->ConnectionString="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db11.mdb";

		m_pConnection->Open("","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	


}
_RecordsetPtr& CAccessConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pConnection==NULL)
		{
			OnInitAccessConn();
		}
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),
		adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

BOOL CAccessConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
		if(m_pConnection==NULL)
			OnInitAccessConn();
		m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return TRUE;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
}
void CAccessConn::CutConn()
{
	if(m_pRecordset!=NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	CoUninitialize();
}