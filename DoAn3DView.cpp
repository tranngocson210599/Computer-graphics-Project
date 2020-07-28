
// DoAn3DView.cpp : implementation of the CDoAn3DView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DoAn3D.h"
#endif
#include <stdio.h>
#include "DoAn3DDoc.h"
#include "DoAn3DView.h"
#include"include/GL/glut.h"
#include"include/GL/GLAux.h"
#include"include/GL/GL.H"
#include"include/GL/GLU.H"
#include<gl/GLAux.h>
#include <atlimage.h> 
#include"MainFrm.h"
#include"ScaleDlg.h"
   //Inserted for CImage class handling
#include<comdef.h> 
#include"texture.h"
// #pragma comment(lib, "Glaux.lib")
//#pragma comment(lib,"OpenGLUT.lib")
//#pragma comment(lib,"OpenGLUT_static.lib")
//#pragma comment(lib, glaux.lib)
//#include "BMP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDoAn3DView

IMPLEMENT_DYNCREATE(CDoAn3DView, CView)

BEGIN_MESSAGE_MAP(CDoAn3DView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDoAn3DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SHAPE_TEAPOT, &CDoAn3DView::OnShapeTeapot)
	//ON_UPDATE_COMMAND_UI(ID_SHAPE_TEAPOT, &CDoAn3DView::OnUpdateShapeTeapot)
	ON_COMMAND(ID_SHAPE_CUBE, &CDoAn3DView::OnShapeCube)
	ON_COMMAND(ID_SHAPE_TORUS, &CDoAn3DView::OnShapeTorus)
	ON_COMMAND(ID_SHAPE_CUBE32774, &CDoAn3DView::OnShapeCube32774)
	ON_COMMAND(ID_SHAPE_SPHERE, &CDoAn3DView::OnShapeSphere)
	ON_COMMAND(ID_SHAPE_CYLINDER, &CDoAn3DView::OnShapeCylinder)
	ON_COMMAND(ID_MODE_LINE, &CDoAn3DView::OnModeLine)
	ON_COMMAND(ID_MODE_POINT, &CDoAn3DView::OnModePoint)
	ON_COMMAND(ID_MODE_FACE, &CDoAn3DView::OnModeFace)
	ON_COMMAND(ID_LIGHT_ON, &CDoAn3DView::OnLightOn)
	ON_COMMAND(ID_LIGHT_OFF, &CDoAn3DView::OnLightOff)
	ON_COMMAND(ID_LIGHT_SHADOW, &CDoAn3DView::OnLightShadow)
	ON_COMMAND(ID_ANIMATION_SOLARSYSTEM, &CDoAn3DView::OnAnimationSolarsystem)
	ON_COMMAND(ID_SOLARSYSTEM_ON, &CDoAn3DView::OnSolarsystemOn)
	ON_COMMAND(ID_SOLARSYSTEM_OFF, &CDoAn3DView::OnSolarsystemOff)
	ON_COMMAND(ID_TEXTURE_TEXTURE, &CDoAn3DView::OnTextureTexture)
	ON_COMMAND(ID_AFFINE_SCALE, &CDoAn3DView::OnAffineScale)
	ON_COMMAND(ID_SCALE_ON, &CDoAn3DView::OnScaleOn)
	ON_COMMAND(ID_SCALE_OFF, &CDoAn3DView::OnScaleOff)
	ON_COMMAND(ID_ROTATION_ON, &CDoAn3DView::OnRotationOn)
	ON_COMMAND(ID_ROTATION_OFF, &CDoAn3DView::OnRotationOff)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CDoAn3DView construction/destruction

CDoAn3DView::CDoAn3DView() noexcept
:m_view_type(VIEW_DEFAULT)
	,m_texNum(0)
{
	// TODO: add construction code here
	
	
		m_pDC = NULL;
		m_pOldPalette = NULL;
	//	m_play = FALSE;
	
}

CDoAn3DView::~CDoAn3DView()
{
}

BOOL CDoAn3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= (WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS | CS_OWNDC);

	return CView::PreCreateWindow(cs);
}

// CDoAn3DView drawing

void CDoAn3DView::OnDraw(CDC* pDC)
{
	CDoAn3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	wglMakeCurrent(m_hDC1, m_hRC);
	GLRenderScene();
	
//	glutSpecialFunc(arrow_keys);
	SwapBuffers(m_hDC1);
	wglMakeCurrent(m_hDC1, NULL);
}


// CDoAn3DView printing

void CDoAn3DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDoAn3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDoAn3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDoAn3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDoAn3DView::GLResize(int cx, int cy)
{
	/*GLfloat fAspect;

	if (cy == 0)
		cy = 1;

	glViewport(0, 0, cx, cy);

	fAspect = (GLfloat)cx / (GLfloat)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
	///code cu
	/*glViewport(0, 0, (GLsizei)cx, (GLsizei)cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)cx / (GLfloat)cy, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 5, 0.0, 0.0, 0.0, 1, 0, 0);*/


	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)cx / (float)cy;
	gluPerspective(45.0, ratio, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void CDoAn3DView::GLRenderScene(void)
{



	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	//glColor3f(1.0, 1.0, 0.0);

	//if (shape_check == 1)
	////	//MakeCube(r);
	//	glutWireTeapot(r/20);
	////	glutWireCube(r/20);
	////	// glutWireSphere(r, 10*r,10*r);
	////	//MakeSphere(r);
	////	//glutWireCone(r, 2 * r, 20 * r, 20 * r);
 //// // glutWireIcosahedron();
	//if (shape_check == 2)
	//	//	glutWireCone(r, r , r , r );
	//	glutWireCone(r/100, r/100, 10, 10);
	//if (shape_check == 3)
	//	//glutWireTorus(r , 1.8* r , r , 50* r );
	//	glutWireTorus(r /30, r / 10, 20, 20);
	//if(shape_check==4)
	//	glutWireCube(r / 20);
	int r = sqrt((start_point.x - end_point.x) * (start_point.x - end_point.x) + (start_point.y - end_point.y) * (start_point.y - end_point.y));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glColor3f(1.0, 1.0, 0.0);

	glLoadIdentity();
	gluLookAt(g_x, 1.0, g_z, 0, 1.0, 0, 0, 1, 0);
	//glutSolidTeapot(2);
	if (light == 1)
	{


		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
		GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

		
	}
	if (light == 0)
	{
		glDisable(GL_LIGHTING);
	}

	if (draw_mode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (draw_mode == 2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (draw_mode == 3)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	
	if (shape_check == 1)
	{
		glutSolidTeapot(2);
		
		if (scale == 1)
		{
			ScaleDlg dlgScale;
			if (dlgScale.DoModal() == IDOK)
			{
				((CDoAn3DDoc*)GetDocument())->ValueScale.x = dlgScale.getvalueX();
				((CDoAn3DDoc*)GetDocument())->ValueScale.y = dlgScale.getvalueY();
				((CDoAn3DDoc*)GetDocument())->ValueScale.z = dlgScale.getvalueZ();
				Invalidate();
			}

			CDoAn3DDoc* pscale = (CDoAn3DDoc*)GetDocument();
			glScaled(pscale->ValueScale.x, pscale->ValueScale.y, pscale->ValueScale.z);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSolidTeapot(2);
		}
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//Image* image = loadBMP("vtr.bmp");
		//_textureId = loadTexture(image);

	}
		
	
	//	glutWireTeapot(r / 20);
	if (shape_check == 2)
	{
	//	gluLookAt(0, 5, 5, 0.0, 0.0, 0.0, 0, 1, 0);
		glutSolidCone(2, 2, 20, 20);
		if (scale == 1)
		{
			ScaleDlg dlgScale;
			if (dlgScale.DoModal() == IDOK)
			{
				((CDoAn3DDoc*)GetDocument())->ValueScale.x = dlgScale.getvalueX();
				((CDoAn3DDoc*)GetDocument())->ValueScale.y = dlgScale.getvalueY();
				((CDoAn3DDoc*)GetDocument())->ValueScale.z = dlgScale.getvalueZ();
				Invalidate();
			}

			CDoAn3DDoc* pscale = (CDoAn3DDoc*)GetDocument();
			glScaled(pscale->ValueScale.x, pscale->ValueScale.y, pscale->ValueScale.z);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSolidCone(2, 2, 20, 20);
		}
	//	glutWireCone(r / 100, r / 100, 10, 10);

	}
	//glutSolidCone(r/100, r/100, 20, 20);
//	glutSolidCone(2, 2, 20, 20);
	if (shape_check == 3)
	{
		//glutSolidTorus(r /30, r / 10, 20, 20);
		glutSolidTorus(0.5, 1.5, 20, 20);
		if (scale == 1)
		{
			ScaleDlg dlgScale;
			if (dlgScale.DoModal() == IDOK)
			{
				((CDoAn3DDoc*)GetDocument())->ValueScale.x = dlgScale.getvalueX();
				((CDoAn3DDoc*)GetDocument())->ValueScale.y = dlgScale.getvalueY();
				((CDoAn3DDoc*)GetDocument())->ValueScale.z = dlgScale.getvalueZ();
				Invalidate();
			}

			CDoAn3DDoc* pscale = (CDoAn3DDoc*)GetDocument();
			glScaled(pscale->ValueScale.x, pscale->ValueScale.y, pscale->ValueScale.z);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSolidTorus(0.5, 1.5, 20, 20);
		}
		//glutWireTorus(r / 30, r / 10, 20, 20);
	//glutSolidTorus()
	}
	if (shape_check == 4)
		//glutSolidCube(r / 20);
		//glutSolidCube(2);
	{
		glutSolidCube(2);
		if (scale == 1)
		{
			ScaleDlg dlgScale;
			if (dlgScale.DoModal() == IDOK)
			{
				((CDoAn3DDoc*)GetDocument())->ValueScale.x = dlgScale.getvalueX();
				((CDoAn3DDoc*)GetDocument())->ValueScale.y = dlgScale.getvalueY();
				((CDoAn3DDoc*)GetDocument())->ValueScale.z = dlgScale.getvalueZ();
				Invalidate();
			}

			CDoAn3DDoc* pscale = (CDoAn3DDoc*)GetDocument();
			glScaled(pscale->ValueScale.x, pscale->ValueScale.y, pscale->ValueScale.z);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSolidCube(2);
		}
		/*cube = MakeCube(1);
		glCallList(cube);*/
	}
	if (shape_check == 5)
		//glutSolidSphere(r / 20, 20, 20);
	{
		/*GLfloat mat_ambien[] = { 1.0, 1.0, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien);*/
		g_sun = MakeSphere(2);
		glCallList(g_sun);
		if (scale == 1)
		{
			ScaleDlg dlgScale;
			if (dlgScale.DoModal() == IDOK)
			{
				((CDoAn3DDoc*)GetDocument())->ValueScale.x = dlgScale.getvalueX();
				((CDoAn3DDoc*)GetDocument())->ValueScale.y = dlgScale.getvalueY();
				((CDoAn3DDoc*)GetDocument())->ValueScale.z = dlgScale.getvalueZ();
				Invalidate();
			}

			CDoAn3DDoc* pscale = (CDoAn3DDoc*)GetDocument();
			glScaled(pscale->ValueScale.x, pscale->ValueScale.y, pscale->ValueScale.z);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			g_sun = MakeSphere(2);
			glCallList(g_sun);
		}
	//	glutSolidSphere(2, 20, 20);
	}
	//	glutSolidSphere(2, 20, 20);
		
	if (shape_check == 6)
	{

		gluLookAt(0, 5, 5, 0.0, 0.0, 0.0, 0, 1, 0);
		glTranslatef(0, 2, 0);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		//gluCylinder(quadratic_obj, r / 30, r / 30, r / 10, 32, 32);
		gluCylinder(quadratic_obj, 1, 1, 5, 32, 32);
		if (scale == 1)
		{
			ScaleDlg dlgScale;
			if (dlgScale.DoModal() == IDOK)
			{
				((CDoAn3DDoc*)GetDocument())->ValueScale.x = dlgScale.getvalueX();
				((CDoAn3DDoc*)GetDocument())->ValueScale.y = dlgScale.getvalueY();
				((CDoAn3DDoc*)GetDocument())->ValueScale.z = dlgScale.getvalueZ();
				Invalidate();
			}

			CDoAn3DDoc* pscale = (CDoAn3DDoc*)GetDocument();
			glScaled(pscale->ValueScale.x, pscale->ValueScale.y, pscale->ValueScale.z);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			gluCylinder(quadratic_obj, 1, 1, 5, 32, 32);
		}
		
	}
	/*GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);*/

	g_x = 10 * sin(angle);
	g_z = 10 * cos(angle);
	//if (affine == 1)
	//{
	//	//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	//		glTranslatef((end_point.x - start_point.x) / 80, (end_point.y - start_point.y) / 80, 0);
	//		//	glTranslatef(1, 1 , 1);
	//		//	glTranslatef(end_point.x, end_point.y , 0);
	//	//		glutSolidTeapot(2);
	//		//	GLUquadricObj* quadratic_obj;
	//		//	quadratic_obj = gluNewQuadric();
	//			//gluCylinder(quadratic_obj, r / 30, r / 30, r / 10, 32, 32);
	//		//	gluCylinder(quadratic_obj, 1, 1, 5, 32, 32);
	//		//	gluLookAt(g_x, 0, g_z, 0.0, 0.0, 0.0, 0, 1, 0);
	//			//gluLookAt(0, 5, 5, 0.0, 0.0, 0.0, 0, 1, 0);
	//		//	gluLookAt(g_x, 1.0, g_z, 0, 1.0, 0, 0, 1, 0);
	//		//	glLoadIdentity(); //remove transforms from previous display() call
	//			//glu mouse_callback_func();
	//			//glutMotionFunc(mouseMove);
	//		//	glTranslatef(-cameraX, -cameraY, 0.0f);
	//			//glutSpecialFunc(OnKeyDown);
	//			//glutSpecialFunc(OnKeyDown);
	//			/*glutSpecialFunc(OnKeyDown);
	//			glutMouseFunc(mouseButton);
	//			glutMotionFunc(mouseMove);*/
	//}
	if (light_shadow == 1 && light == 1)
	{
		//	//glLoadIdentity();
		//	glTranslatef(0, -10, 0);
		////	gluLookAt(5, 0, 5, 0, 1.0, 0, 0, 1, 0);
		//	glEnable(GL_TEXTURE_2D);
		//	//glEnable(GL_NORMALIZE);
		//	//glBindTexture(GL_TEXTURE_2D, g_Texture[0]);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//	//glColor3f(.5, 0.5, 0.7);
		//	glBegin(GL_TRIANGLE_FAN);
		//	glNormal3f(0.0f, 1.0f, 0.0f);
		//	glTexCoord2f(0.0f, 0.0f);

		//	glVertex3f(-50, 0, -50);
		//	glTexCoord2f(10.0f, 0.0f);
		//	glVertex3f(25, 0, -25);
		//	glTexCoord2f(10.0f, 10.0f);
		//	glVertex3f(50, 0, 50);
		//	glTexCoord2f(0.0f, 10.0f);
		//	glVertex3f(-50, 0, 50);
		//	glEnd();
		//	glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		static GLfloat floorVertices[4][3] =
		{
		 { -20.0, 0.0, 20.0 },
		 { 20.0, 0.0, 20.0 },
		 { 20.0, 0.0, -20.0 },
		 { -20.0, 0.0, -20.0 },
		};
		glTranslatef(0, -4, 0);
		//	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(floorVertices[0]);
		glTexCoord2f(0.0, 16.0);
		glVertex3fv(floorVertices[1]);
		glTexCoord2f(16.0, 16.0);
		glVertex3fv(floorVertices[2]);
		glTexCoord2f(16.0, 0.0);
		glVertex3fv(floorVertices[3]);
		glEnd();


		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glEnable(GL_DEPTH_TEST);
		GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
		GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

		GLfloat qaLightPosition[] = { .5,.5,0.0,1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition);
		glPopMatrix();
		
	}

	if (system == 1)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

		GLfloat ambient[] = { 1.0, 1.0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

		GLfloat diff_use[] = { 0.5, 0.5, 0.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

		GLfloat shininess = 50.0f;
		glMateriali(GL_FRONT, GL_SHININESS, shininess);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0, 1.0, 0);

		GLfloat mat_ambien[] = { 1.0, 1.0, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien);
		GLfloat diff[] = { 05, 0.5, 0.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glCallList(g_sun);

		glRotatef(g_angle_year, 0.0f, 1.0f, 0.0f);
		glTranslated(8.0, 0.0, 0.0);
		glRotatef(g_angle_day, 0.0f, 1.0f, 0.0f);

		GLfloat mat_ambien2[] = { 0.0, 0.0, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien2);
		GLfloat diff2[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff2);
		glCallList(g_earth);

		glPushMatrix();
		glRotatef(gl_angle_moon, 0.0f, 1.0f, 0.0f);
		glTranslated(2.0, 0.0, 0.0);

		GLfloat mat_ambien3[] = { 0.7, 0.7, 0.7f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien3);
		GLfloat diff3[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff3);

		glCallList(g_moon);
		glPopMatrix();

		glPopMatrix();

		  Sleep(83);
		gl_angle_moon = (gl_angle_moon + 13);
		if (gl_angle_moon >= 360)
		{
			gl_angle_moon = 0;
		}

		g_angle_day = (g_angle_day + 360);
		if (g_angle_day >= 360)
		{
			g_angle_day = 0;
		}

		g_angle_year = (g_angle_year + 1);
		if (g_angle_year >= 360)
		{
			g_angle_year = 0;
		}
		//glutWireTeapot(2);
		/*g_sun = MakeSphere(4.2);
		g_earth = MakeSphere(2.2);
		g_moon = MakeSphere(1);*/
		g_sun = MakeSphere(2);
		g_earth = MakeSphere(1);
		g_moon = MakeSphere(0.2);

	//	glutSwapBuffers();
		glFlush();

	//	glutPostRedisplay();

	}


}
CBitmap* CDoAn3DView::GetImgBitmap(CImage* pImg)
{
	if (pImg == NULL)
		return NULL;

	CDC* pDC = new CDC;
	if (!pDC->CreateCompatibleDC(CDC::FromHandle(pImg->GetDC())))
	{
		pImg->ReleaseDC();
		return NULL;
	}
		
	CBitmap* pBm = new CBitmap;
	pBm->CreateCompatibleBitmap(CDC::FromHandle(pImg->GetDC()), pImg->GetWidth(), pImg->GetHeight());

	CBitmap* pBmOld = pDC->SelectObject(pBm);
	pImg->BitBlt(pDC->m_hDC, CPoint(0, 0));
	pDC->DeleteDC();
	ReleaseDC(pDC);
	pImg->ReleaseDC();
	
	return pBm;
}
GLuint CDoAn3DView::LoadGLTexture(BITMAP* pBm)
{
	GLuint texi;								//Name of the new texture
	glGenTextures(1, &texi);					//Name of the new texture generation
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, texi);			//Connection to texture mapping

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBm->bmWidth, pBm->bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBm->bmBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return texi;
}
GLuint CDoAn3DView::LoadImgTexture(LPCTSTR fName)
{
	CImage img;
	HRESULT hResult = img.Load(fName);  //Standart procedure of CImage loading
	if (FAILED(hResult)) {
		_TCHAR fmt[1028];
		//	_stprintf_s((_TCHAR *)fmt, hResult, _T("Error %d\n%s\nin file:\n%s"), _com_error(hResult).ErrorMessage(), fName);
	//	MessageBox(NULL, fmt, _T("Error:"), MB_OK | MB_ICONERROR);
		return FALSE;
	}//if(FAILED(hResult))

	CBitmap* pBm = NULL;
	if (img.GetBPP() != 24)                               //if Bitmap format not compatible with GL_BGR_EXT 
	{
		CImage tmg;
		tmg.Create(img.GetWidth(), img.GetHeight(), 24);    //Create CImage compatible with GL_BGR_EXT
		img.BitBlt(tmg.GetDC(), CPoint(0, 0));				//Copy Original Image to the environment created
		tmg.ReleaseDC();
		pBm = GetImgBitmap(&tmg);	//Get the class CBitmap from CImage class
		
	}
	else
		pBm = GetImgBitmap(&img);  //Get the class CBitmap from CImage class
	//img.ReleaseDC();
	BITMAP BMP;
	pBm->GetBitmap(&BMP);			//Standard procedure of BITMAP structure derived from CBitmap class
	return  LoadGLTexture(&BMP);	//Load Texture from BITMAP structure

}
void CDoAn3DView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int         n;
	HGLRC       hrc;
	GLfloat     fMaxObjSize, fAspect;


	m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if (!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

//	CreateRGBPalette();

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	GetClientRect(&m_oldRect);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	//if (m_oldRect.bottom)
	//	fAspect = (GLfloat)m_oldRect.right / m_oldRect.bottom;
	//else    // don't divide by zero, not that we should ever run into that...
	//	fAspect = 1.0f;
	//fNearPlane = 3.0f;
	//fFarPlane = 7.0f;
	//fMaxObjSize = 3.0f;
	//m_fRadius = (fNearPlane + fFarPlane) * 0.5f;

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
	//glMatrixMode(GL_MODELVIEW);

   /* glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("vtr.bmp");
	_textureId = loadTexture(image);
	delete image;*/
}
BOOL CDoAn3DView::bSetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		  PFD_SUPPORT_OPENGL |          // support OpenGL
		  PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox(_T("ChoosePixelFormat failed"));
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}

	return TRUE;
}
GLuint CDoAn3DView::loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId;
}
//#define auxDIBImageLoad auxDIBImageLoadA
//AUX_RGBImageRec* CDoAn3DView::LoadBMP(char* Filename)
//{
//	FILE* File = NULL;
//
//	if (!Filename)
//		return NULL;
//	fopen_s(&File, Filename, "r");
//	if (File)
//	{
//		fclose(File);
//		return auxDIBImageLoadA((LPCSTR)Filename);
//	}
//	return NULL;
//}

//void CDoAn3DView::arrow_keys(int a_keys, int x, int y)
//{
//	//switch (a_keys) {
//	//case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
//	//	xspeed -= 0.01f;
//	//	break;
//	//case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
//	//	xspeed += 0.01f;
//	//	break;
//	//case GLUT_KEY_RIGHT:
//	//	yspeed += 0.01f;
//	//	break;
//	//case GLUT_KEY_LEFT:
//	//	yspeed -= 0.01f;
//	//	break;
//	//case GLUT_KEY_F1:
//	//	glutFullScreen();
//	//	break;
//	//case GLUT_KEY_F2:
//	//	glutReshapeWindow(500, 500);
//	//	break;
//	//default:
//	//	break;
//	//}
//}

//bool CDoAn3DView::LoadGLTextures()
//{
//	int ret = false;
//	AUX_RGBImageRec* texture_image = NULL;
//
//	if (texture_image = LoadBMP(texture_name))
//	{
//		glGenTextures(1, &texture);  // Bắt đầu quá trình gen texture.
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		//map dữ liệu bit map vào texture.
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture_image->sizeX,
//			texture_image->sizeY, 0, GL_RGB,
//			GL_UNSIGNED_BYTE, texture_image->data);
//	}
//	else
//	{
//		ret = false;
//		if (texture_image)
//		{
//			if (texture_image->data)
//				free(texture_image->data);
//			free(texture_image);
//		}
//	}
//	return TRUE;
//}
//
//
//


void CDoAn3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDoAn3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDoAn3DView diagnostics

#ifdef _DEBUG
void CDoAn3DView::AssertValid() const
{
	CView::AssertValid();
}

void CDoAn3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDoAn3DDoc* CDoAn3DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoAn3DDoc)));
	return (CDoAn3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CDoAn3DView message handlers

//void CDoAn3DView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	/*start_point.x = point.x;
//	start_point.y = point.y;*/
//	
//	if (rotation == 1 )
//	{
//		deltaAngle = 0.0;
//		xOrigin = point.x;
//		CView::OnLButtonDown(nFlags, point);
//	}
//	if (rotation == 0)
//	{
//		/*start_point.x = point.x;
//	    start_point.y = point.y;*/
//		CView::OnLButtonDown(nFlags, point);
//	}
//
//	
//}

//void CDoAn3DView::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	if (rotation == 1 )
//	{
//		/*end_point.x = point.x;
//		end_point.y = point.y;*/
//		angle += deltaAngle;
//		xOrigin = -1;
//		Invalidate();
//	}
//	if (rotation == 0)
//	{
//		/*end_point.x = point.x;
//		end_point.y = point.y;*/
//		CView::OnLButtonUp(nFlags, point);
//	}
//
//	
//}
//
//void CDoAn3DView::OnMouseMove(UINT nFlags, CPoint point)
//{
//	if (rotation == 1)
//	{
//		if (nFlags && MK_LBUTTON)
//		{
//			/*end_point.x = point.x;
//			end_point.y = point.y;
//			Invalidate();*/
//			deltaAngle += (point.x - xOrigin) * 0.0005f;
//			// update camera's direction
//			g_x = 10 * sin(angle + deltaAngle);
//			g_z = 10 * cos(angle + deltaAngle);
//			
//		}
//		
//	}
//	if (rotation == 0)
//	{
//		/*end_point.x = point.x;
//		end_point.y = point.y;*/
//	//	if (nFlags && MK_LBUTTON)
//	//	{
//			end_point.x = point.x;
//			end_point.y = point.y;
//			Invalidate();
//
//	//	}
//		
//	}
//	/*if (nFlags && MK_LBUTTON)
//	{
//		end_point.x = point.x;
//		end_point.y = point.y;
//		Invalidate();
//
//	}*/
//	CView::OnMouseMove(nFlags, point);
//}

void CDoAn3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
		if (rotation == 1 )
		{
			deltaAngle = 0.0;
			xOrigin = point.x;
			CView::OnLButtonDown(nFlags, point);
		}
	start_point.x = point.x;
	start_point.y = point.y;
	CView::OnLButtonDown(nFlags, point);
}

void CDoAn3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
		if (rotation == 1 )
	{
		/*end_point.x = point.x;
		end_point.y = point.y;*/
		angle += deltaAngle;
		xOrigin = -1;
		Invalidate();
	}
	end_point.x = point.x;
	end_point.y = point.y;
	Invalidate();
}

void CDoAn3DView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (rotation == 1)

	{
		if (nFlags && MK_LBUTTON)
		{
			
			deltaAngle += (point.x - xOrigin) * 0.0005f;
			// update camera's direction
			g_x = 10 * sin(angle + deltaAngle);
			g_z = 10 * cos(angle + deltaAngle);
			
		}
		
	}
	if (nFlags && MK_LBUTTON)
	{
		end_point.x = point.x;
		end_point.y = point.y;
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}



int CDoAn3DView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	Init();

	int nPixelFormat;
	m_hDC1 = ::GetDC(m_hWnd);

	static PIXELFORMATDESCRIPTOR pfd =
	{
	 sizeof(PIXELFORMATDESCRIPTOR),
	 1,
	 PFD_DRAW_TO_WINDOW |
	 PFD_SUPPORT_OPENGL |
	 PFD_DOUBLEBUFFER,
	 PFD_TYPE_RGBA,
	 24,
	 0,0,0,0,0,0,
	 0,0,
	 0,0,0,0,0,
	 32,
	 0,
	 0,
	 PFD_MAIN_PLANE,
	 0,
	 0,0,0
	};
	nPixelFormat = ChoosePixelFormat(m_hDC1, &pfd);
	VERIFY(SetPixelFormat(m_hDC1, nPixelFormat, &pfd));
	m_hRC = wglCreateContext(m_hDC1);
	VERIFY(wglMakeCurrent(m_hDC1, m_hRC));
	wglMakeCurrent(NULL, NULL);

	return 0;
}

void CDoAn3DView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	VERIFY(wglMakeCurrent(m_hDC1, m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL, NULL));
}

BOOL CDoAn3DView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CDoAn3DView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC1);
}


void CDoAn3DView::OnShapeTeapot()
{
	// TODO: Add your command handler code here
	shape_check = 1;
}


//void CDoAn3DView::OnUpdateShapeTeapot(CCmdUI* pCmdUI)
//{
//	// TODO: Add your command update UI handler code here
//	pCmdUI->SetCheck(1);
//}


void CDoAn3DView::OnShapeCube()
{
	// TODO: Add your command handler code here
	shape_check = 2;
}


void CDoAn3DView::OnShapeTorus()
{
	// TODO: Add your command handler code here
	shape_check = 3;
}

GLuint CDoAn3DView::MakeSphere(float radius)
{
	GLuint boxDisplay;
	boxDisplay = glGenLists(1);
	glNewList(boxDisplay, GL_COMPILE);
	glutSolidSphere(radius, 64, 16);
	glEndList();
	return boxDisplay;
}

GLuint CDoAn3DView::MakeCube(int size)
{
	GLuint boxDisplay;
	boxDisplay = glGenLists(1);
	glNewList(boxDisplay, GL_COMPILE);

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, -size);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, -size, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, -size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
	glEnd();

	glEndList();
	return boxDisplay;
}



void CDoAn3DView::OnShapeCube32774()
{
	shape_check = 4;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnShapeSphere()
{
	shape_check = 5;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnShapeCylinder()
{
	shape_check = 6;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnModeLine()
{
	draw_mode = 1;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnModePoint()
{
	draw_mode = 2;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnModeFace()
{
	draw_mode = 3;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnLightOn()
{
	light = 1;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnLightOff()

{
	// TODO: Add your command handler code here
	light = 0;
}


void CDoAn3DView::OnLightShadow()
{
	// TODO: Add your command handler code here
	light_shadow = 1;
}


void CDoAn3DView::OnAnimationSolarsystem()
{
	
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnSolarsystemOn()
{
	system = 1;
	// TODO: Add your command handler code here
}


void CDoAn3DView::OnSolarsystemOff()
{
	// TODO: Add your command handler code here
	system = 0;
}

void CDoAn3DView::OnTextureView()
{
	glEnable(GL_TEXTURE_2D);
	GLuint glErr = (GLuint)glGetError();
	if (glErr != GL_NO_ERROR)
	{
		/*CString wString;
		wString.Format(_T("1 CImgTextureView::OnTextureView\nglErr = 0x%04x\nnn = %d\n"), glErr, m_texNum);
		AfxMessageBox(wString);*/
	}

	//m_view_type = VIEW_TEXTURE;
	glBindTexture(GL_TEXTURE_2D, (GLuint)m_globTexture.GetAt(m_texNum));

	glErr = (GLuint)glGetError();
	if (glErr != GL_NO_ERROR)
	{
		/*CString wString;
		wString.Format(_T("2 CImgTextureView::OnTextureView\nglErr = 0x%04x\nnn = %d\n"), glErr, m_texNum);
		AfxMessageBox(wString);*/
	}

	Invalidate();
	UpdateWindow();
}


void CDoAn3DView::OnTextureTexture()

{
	//// TODO: Add your command handler code here
	CString strFilter;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;

	CImage img;
	hResult = img.GetImporterFilterString(strFilter, aguidFileTypes, _T("All Images"));
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format(_T("Error %d\n%s"), hResult, _com_error(hResult).ErrorMessage());
		MessageBox(fmt, _T("Error:"), MB_OK | MB_ICONERROR);

		return;
	}//if(FAILED(hResult))


	DWORD dwFlags = OFN_CREATEPROMPT | OFN_EXPLORER;


	CFileDialog dlg(TRUE, _T("*"), _T("*.*"), OFN_FILEMUSTEXIST, strFilter);

	dlg.m_ofn.nFilterIndex = 0; //m_nFilterLoad;

	if (dlg.DoModal() != IDOK)
		return;

	m_globTexture.Add((WORD)LoadImgTexture(dlg.GetPathName()));
	m_texNum = m_globTexture.GetUpperBound();

	m_view_type = VIEW_TEXTURE;
	OnTextureView();

	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Image* image = loadBMP("vtr.bmp");
	_textureId = loadTexture(image);*/
}


void CDoAn3DView::OnAffineScale()
{
	// TODO: Add your command handler code here
	scale = 1;
}


void CDoAn3DView::OnScaleOn()
{
	// TODO: Add your command handler code here
	scale = 1;
}


void CDoAn3DView::OnScaleOff()
{
	// TODO: Add your command handler code here
	scale = 0;
}


void CDoAn3DView::OnRotationOn()
{
	// TODO: Add your command handler code here
	rotation = 1;
}


void CDoAn3DView::OnRotationOff()
{
	// TODO: Add your command handler code here
	rotation = 0;
}


void CDoAn3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_RIGHT:
		g_x +=1;
		break;
	case VK_LEFT:
		g_x -= 1;
		break;
	case VK_UP:
		g_z -= 1;
		break;
	case VK_DOWN:
		g_z += 1;
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
