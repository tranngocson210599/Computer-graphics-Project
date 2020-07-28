
// DoAn3DDoc.h : interface of the CDoAn3DDoc class
//


#pragma once
struct ScaleReturn
{
	float x, y, z;

};

class CDoAn3DDoc : public CDocument
{
protected: // create from serialization only
	CDoAn3DDoc() noexcept;
	DECLARE_DYNCREATE(CDoAn3DDoc)

// Attributes
public:
	ScaleReturn ValueScale;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDoAn3DDoc();
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
