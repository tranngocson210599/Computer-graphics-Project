
// DoAn3DView.h : interface of the CDoAn3DView class
//

#pragma once


#include"include/GL/glut.h"
#include<gl/GLAux.h>
#include <atlimage.h> 
   //Inserted for CImage class handling
#include<comdef.h> 
#include <stdio.h>
#include"MainFrm.h"
#include"texture.h"
class CDoAn3DView : public CView 
{
protected: // create from serialization only
	CDoAn3DView() noexcept;
	DECLARE_DYNCREATE(CDoAn3DView)

// Attributes
public:
	CDoAn3DDoc* GetDocument() const;
	CMainFrame* pMainFrame;
	//pMainFrame = (CMainFrame*)AfxGetMainWnd();    
	//	if (pMainFrame != NULL)    // Better safe than sorry...
	//	{
	//		pMainFrame->m_bMemberVarA = TRUE;    
	//			pMainFrame->SetMemberAFlag(TRUE);        
	//	}
// Operations
public:
	CPoint start_point, end_point;
	//bool shape_check{ false };
	int shape_check = 0;
	int draw_mode;
	int light;
	int scale;
	int light_shadow;
	float g_x = 0;
	float g_z = 0;
	CDoAn3DDoc* pscale;
	float angle = 0.0;
	int system;
	GLuint g_sun;
	GLuint g_earth;
	GLuint g_moon;
	GLuint cube;
	GLuint g_angle_day = 0;
	GLuint g_angle_year = 0;
	GLuint gl_angle_moon = 0;
	GLfloat     fNearPlane, fFarPlane;	//Array of the textures' names available	
	GLuint g_box;                          // sử dụng để tạo display list cho đối tượng.
	GLuint _textureId;
	int rotation=0;
	//
//	float g_x = 0.0;
//	float g_z = 0.0;
	float lz = -10.0;
	float lx = 0.0;
	//float angle = 0.0;
	float deltaAngle = 0.0f;
	int xOrigin = -1;
	bool g_is_rotate = false;
	//

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void GLResize(int cx, int cy);
	virtual void GLRenderScene(void);
//	virtual AUX_RGBImageRec* LoadBMP(char* Filename);
//	virtual bool LoadGLTextures();
	//virtual GLuint MakeSphere( int radius);
	virtual CBitmap* GetImgBitmap(CImage* pImg);
	virtual GLuint LoadGLTexture(BITMAP* pBm);
	virtual GLuint  LoadImgTexture(LPCTSTR fName);
	virtual void Init();
	virtual BOOL bSetupPixelFormat(void);
	virtual GLuint loadTexture(Image* image);
public:
	
	//virtual void GLRenderSceneCone(void);
// Implementation
public:
	virtual ~CDoAn3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	//OpenGL Setup
	//BOOL GetRenderingContext();
	//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	HDC     m_hDC1;
	CDC* m_pDC;
	CPalette    m_cPalette;
	CPalette* m_pOldPalette;
	CRect       m_oldRect;
	float       m_fRadius;
	//CClientDC* m_pDC;
	

	int m_texNum;				//Current order number of the name of the texture 
	CWordArray m_globTexture;	//Array of the textures' names available	
	int m_view_type;			//View performance:VIEW_DEFAULT or VIEW_TEXTURE
	enum VIEW_TYPE
	{
		VIEW_DEFAULT,
		VIEW_TEXTURE,
	};
protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnShapeTeapot();
	afx_msg void OnUpdateShapeTeapot(CCmdUI* pCmdUI);
	afx_msg void OnShapeCube();
	afx_msg void OnShapeTorus();
	afx_msg GLuint MakeSphere(float radius);
	afx_msg GLuint MakeCube( int size);
	afx_msg void OnShapeCube32774();
	afx_msg void OnShapeSphere();
	afx_msg void OnShapeCylinder();
	afx_msg void OnModeLine();
	afx_msg void OnModePoint();
	afx_msg void OnModeFace();
	afx_msg void OnLightOn();
	afx_msg void OnLightOff();
	afx_msg void OnLightShadow();
	afx_msg void OnAnimationSolarsystem();
	afx_msg void OnSolarsystemOn();
	afx_msg void OnSolarsystemOff();

	afx_msg void OnTextureView();
//	afx_msg AUX_RGBImageRec* LoadBMP(char* Filename);
//	afx_msg void arrow_keys(int a_keys, int x, int y);
	afx_msg void OnTextureTexture();
	afx_msg void OnAffineScale();
	afx_msg void OnScaleOn();
	afx_msg void OnScaleOff();
	afx_msg void OnRotationOn();
	afx_msg void OnRotationOff();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in DoAn3DView.cpp
inline CDoAn3DDoc* CDoAn3DView::GetDocument() const
   { return reinterpret_cast<CDoAn3DDoc*>(m_pDocument); }
#endif

