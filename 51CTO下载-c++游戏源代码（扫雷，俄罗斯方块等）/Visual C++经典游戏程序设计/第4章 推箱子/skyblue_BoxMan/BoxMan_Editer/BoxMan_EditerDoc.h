// BoxMan_EditerDoc.h : interface of the CBoxMan_EditerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOXMAN_EDITERDOC_H__461E0BD9_186E_47C0_97D0_CACC6D0E8262__INCLUDED_)
#define AFX_BOXMAN_EDITERDOC_H__461E0BD9_186E_47C0_97D0_CACC6D0E8262__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBoxMan_EditerDoc : public CDocument
{
protected: // create from serialization only
	CBoxMan_EditerDoc();
	DECLARE_DYNCREATE(CBoxMan_EditerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxMan_EditerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBoxMan_EditerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBoxMan_EditerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMAN_EDITERDOC_H__461E0BD9_186E_47C0_97D0_CACC6D0E8262__INCLUDED_)
