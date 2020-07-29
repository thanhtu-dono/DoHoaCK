
// DoAnDHMTDoc.cpp : implementation of the CDoAnDHMTDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DoAnDHMT.h"
#endif

#include "DoAnDHMTDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDoAnDHMTDoc

IMPLEMENT_DYNCREATE(CDoAnDHMTDoc, CDocument)

BEGIN_MESSAGE_MAP(CDoAnDHMTDoc, CDocument)
END_MESSAGE_MAP()


// CDoAnDHMTDoc construction/destruction

CDoAnDHMTDoc::CDoAnDHMTDoc() noexcept
{
	// TODO: add one-time construction code here

}

CDoAnDHMTDoc::~CDoAnDHMTDoc()
{
}

BOOL CDoAnDHMTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}
string WcharToString(wchar_t* wch) {
	std::string str("");
	int index = 0;
	while (wch[index] != 0) {
		str += (char)wch[index];
		++index;
	}
	return str;
}
BOOL CDoAnDHMTDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	USES_CONVERSION;
	texture_name = WcharToString((wchar_t*)lpszPathName);
	return TRUE;
}

char* CDoAnDHMTDoc::encode(const wchar_t* wstr, unsigned int codePage)
{
	int sizeNeeded = WideCharToMultiByte(codePage, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* encodedStr = new char[sizeNeeded];
	WideCharToMultiByte(codePage, 0, wstr, -1, encodedStr, sizeNeeded, NULL, NULL);
	return encodedStr;
}



// CDoAnDHMTDoc serialization

void CDoAnDHMTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDoAnDHMTDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDoAnDHMTDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDoAnDHMTDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDoAnDHMTDoc diagnostics

#ifdef _DEBUG
void CDoAnDHMTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDoAnDHMTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDoAnDHMTDoc commands
