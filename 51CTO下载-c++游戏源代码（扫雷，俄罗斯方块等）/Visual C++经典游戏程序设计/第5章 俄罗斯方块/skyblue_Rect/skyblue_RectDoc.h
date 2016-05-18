// skyblue_RectDoc.h : interface of the CSkyblue_RectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBLUE_RECTDOC_H__D01EB029_6B69_4664_B25B_F515EDC7F92D__INCLUDED_)
#define AFX_SKYBLUE_RECTDOC_H__D01EB029_6B69_4664_B25B_F515EDC7F92D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkyblue_RectDoc : public CDocument
{
protected: // create from serialization only
	CSkyblue_RectDoc();
	DECLARE_DYNCREATE(CSkyblue_RectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_RectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkyblue_RectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkyblue_RectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_RECTDOC_H__D01EB029_6B69_4664_B25B_F515EDC7F92D__INCLUDED_)
