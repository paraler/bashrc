// skyblue_BoxManDoc.h : interface of the CSkyblue_BoxManDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBLUE_BOXMANDOC_H__9BF7AF38_7BC0_4E0F_A1C8_11CBB24F9ED7__INCLUDED_)
#define AFX_SKYBLUE_BOXMANDOC_H__9BF7AF38_7BC0_4E0F_A1C8_11CBB24F9ED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkyblue_BoxManDoc : public CDocument
{
protected: // create from serialization only
	CSkyblue_BoxManDoc();
	DECLARE_DYNCREATE(CSkyblue_BoxManDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_BoxManDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkyblue_BoxManDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkyblue_BoxManDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_BOXMANDOC_H__9BF7AF38_7BC0_4E0F_A1C8_11CBB24F9ED7__INCLUDED_)
