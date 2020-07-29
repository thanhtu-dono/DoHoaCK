
// DoAnDHMTDoc.h : interface of the CDoAnDHMTDoc class
//

#include <string>
#include<iostream>
using namespace std;
#pragma once


class CDoAnDHMTDoc : public CDocument
{
protected: // create from serialization only
	CDoAnDHMTDoc() noexcept;
	DECLARE_DYNCREATE(CDoAnDHMTDoc)

	// Attributes
public:
	string texture_name;
	void is_set_path_texture(string texture_name)
	{
		this->texture_name = texture_name;
	}
	// Operations
public:
	char* encode(const wchar_t* wstr, unsigned int codePage);
	// Overrides
public:
	virtual BOOL OnNewDocument();
	BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CDoAnDHMTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
