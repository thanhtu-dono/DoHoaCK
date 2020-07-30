
// DoAnDHMTView.cpp : implementation of the CDoAnDHMTView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DoAnDHMT.h"
#endif

#include "DoAnDHMTDoc.h"
#include "DoAnDHMTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDoAnDHMTView

IMPLEMENT_DYNCREATE(CDoAnDHMTView, CView)

BEGIN_MESSAGE_MAP(CDoAnDHMTView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDoAnDHMTView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDoAnDHMTView construction/destruction

CDoAnDHMTView::CDoAnDHMTView() noexcept
{
	CDoAnDHMTView::Init();
	m_hGLContext = NULL;
	// TODO: add construction code here

}

void CDoAnDHMTView::Init()
{
	type_is_draw = 0;
	m_GLPixelIndex = 0;
	m_RotateAngle = 0.0;

	m_nLEDType = WIRE;
	m_TypeAffine = ROTATE;
	m_TypeShadow = SMOOTH;
	m_TypeCoordinateView = X_VIEW;

	m_pShape = gluNewQuadric();

	Width = 50;
	Height = 50;
	fovy = 90;
	zNear = 1;
	zFar = 80;

	m_xRotation = 0.0;
	m_yRotation = 0.0;
	m_zRotation = 0.0;
	m_lBtnPos = (0, 0);
	m_xTranslate = 0.0;
	m_yTranslate = 0.0;
	m_zTranslate = 0.0;
	m_xScale = 1.0;
	m_yScale = 1.0;
	m_zScale = 1.0;
	angle = 0;
	m_AmbientRed = 0.1;
	m_AmbientGreen = 0.1;
	m_AmbientBlue = 0.1;
	m_DiffuseRed = 0.5;
	m_DiffuseGreen = 0.5;
	m_DiffuseBlue = 0.5;
	m_SpecularRed = 1.0;
	m_SpecularGreen = 1.0;
	m_SpecularBlue = 1.0;

	speed_rotate = 5.0;
	ID_SetTimer = 1;

	m_xPointEye = 20;
	m_yPointEye = 20;
	m_xCoordinate = cos(PI / 180 * (m_yPointEye));
	m_yCoordinate = 0.0;
	m_zCoordinate = 0.0;

	m_AxisX = 0.0;
	m_AxisY = 0.0;
	m_AxisZ = 1.0;

	m_lBtnDown = FALSE;
	isRotate = FALSE;
	PathName = NULL;
	path_name = "";
	texName = NULL;
}
void CDoAnDHMTView::DrawCube(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidCube(1.2);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutSolidCube(1.2);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidCube(1.2);
		break;
	}
	}

}

void CDoAnDHMTView::DrawTeapot(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidTeapot(1.2);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutWireTeapot(1.2);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidTeapot(1.2);
		break;
	}
	}
}

void CDoAnDHMTView::DrawSphere(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidSphere(1, 64, 64);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutWireSphere(1, 64, 64);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidSphere(1, 64, 64);
		break;
	}
	}
}

void CDoAnDHMTView::DrawCone(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidCone(0.7, 2.3, 64, 64);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutSolidCone(0.7, 2.3, 64, 64);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidCone(0.7, 2.3, 64, 64);
		break;
	}
	}
}

void CDoAnDHMTView::DrawCylinder(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		gluCylinder(quadratic_obj, 0.5, 0.5, 1.8, 64, 64);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		gluCylinder(quadratic_obj, 0.5, 0.5, 1.8, 64, 64);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		gluCylinder(quadratic_obj, 0.5, 0.5, 1.8, 64, 64);
		break;
	}
	}
}

void CDoAnDHMTView::DrawTorus(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidTorus(0.4, 0.7, 20, 64);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutSolidTorus(0.4, 0.7, 20, 64);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidTorus(0.4, 0.7, 20, 64);
		break;
	}
	}
}
void CDoAnDHMTView::DrawDisk(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		gluDisk(quadratic_obj, 0.5, 1, 48, 64);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		gluDisk(quadratic_obj, 0.5, 1, 48, 64);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		GLUquadricObj* quadratic_obj;
		quadratic_obj = gluNewQuadric();
		gluDisk(quadratic_obj, 0.5, 1, 48, 64);
		break;
	}
	}
}
void CDoAnDHMTView::DrawPyramid(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Pyramid(1, 1.5);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Pyramid(1, 1.5);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		Pyramid(1, 1.5);
	}
	}
}
void CDoAnDHMTView::DrawOctagon(int m_nLEDType)
{
	switch (m_nLEDType)
	{
	case SOLID:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Octagon(0.7, 1.5);
		break;
	}

	case WIRE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Octagon(0.7, 1.5);
		break;
	}

	case POINTS:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		Octagon(0.7, 1.5);
		break;
	}
	}
}
void CDoAnDHMTView::Pyramid(double size, double height)
{
	double half_size = size * 0.5;
	glBegin(GL_TRIANGLES);
	//glBegin(GL_QUADS);
	//Front face
	glNormal3f(0.0, 0.0, 1.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(-half_size, 0, half_size);
	glVertex3f(half_size, 0, half_size);

	//left face
	glNormal3f(-1.0, 0.0, 0.0f);
	glVertex3f(0.0, height, 0.0);
	glVertex3f(-half_size, 0.0, -half_size);
	glVertex3f(-half_size, 0.0, half_size);

	//back face
	glNormal3f(0.0, 0.0, -1.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(-half_size, 0, -half_size);
	glVertex3f(half_size, 0, -half_size);

	//Right face
	glNormal3f(1.0, 0.0, 0.0f);
	glVertex3f(0.0, height, 0.0);
	glVertex3f(half_size, 0.0, -half_size);
	glVertex3f(half_size, 0.0, half_size);
	glEnd();

	//Bottom face
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0f);
	glVertex3f(half_size, 0.0, half_size);
	glVertex3f(half_size, 0.0, -half_size);
	glVertex3f(-half_size, 0.0, -half_size);
	glVertex3f(-half_size, 0.0, half_size);
	glEnd();

}
void CDoAnDHMTView::Octagon(double side, double thickness)
{
	double anpha = PI / 4.0;
	float x = sin(anpha) * side;
	float y = 0.5 * side;

	float z = thickness;
	float center_to_mid_size = x + y;
	for (int j = 0; j < 8; j++)
	{
		glPushMatrix();
		glTranslatef(-center_to_mid_size, 0.0, 0.0);
		//Draw 8 rectangle side
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(0.0, -y, z);
		glVertex3f(0.0, y, z);
		glVertex3f(0.0, y, 0);
		glVertex3f(0.0, -y, 0);
		glEnd();
		glPopMatrix();

		glBegin(GL_TRIANGLES);
		//glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, z);
		glVertex3f(-center_to_mid_size, -y, z);
		glVertex3f(-center_to_mid_size, y, z);

		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-center_to_mid_size, y, 0.0);
		glVertex3f(-center_to_mid_size, -y, 0.0);
		glEnd();

		glRotatef(45.0, 0.0, 0.0, 1.0);
	}

}
void CDoAnDHMTView::Light()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_pos[] = { 0.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat ambient[] = { m_AmbientRed, m_AmbientGreen, m_AmbientBlue, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diff_use[] = { m_DiffuseRed, m_DiffuseGreen, m_DiffuseBlue, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	GLfloat specular[] = { m_SpecularRed, m_SpecularGreen, m_SpecularBlue, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	GLfloat shininess = 60.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}

bool CDoAnDHMTView::LoadGLTextures()
{
	CDoAnDHMTDoc* pDoc = GetDocument();
	path_name = pDoc->texture_name;
	PathName = new char[path_name.size()];
	copy(path_name.begin(), path_name.end(), PathName);
	PathName[path_name.size()] = '\0';
	int ret = false;
	AUX_RGBImageRec* texture_image = NULL;
	//memset(texture_image, 0, sizeof(void*) * 1);
	int size = 0;
	if (texture_image = LoadBMP(PathName, path_name))
	{
		int pet = false;
		glGenTextures(1, &texName);  // Bắt đầu quá trình gen texture.
		glBindTexture(GL_TEXTURE_2D, texName);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		size = min(texture_image->sizeX, texture_image->sizeY);
		int n = 6;
		while (size > pow(2, n))
		{
			n++;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pow(2, n - 1),
			pow(2, n - 1), 0, GL_RGB,
			GL_UNSIGNED_BYTE, texture_image->data);
		//map dữ liệu bit map vào texture.
	}
	else
	{
		ret = false;
		if (texture_image)
		{
			if (texture_image->data)
				free(texture_image->data);
			free(texture_image);
		}
	}
	return ret;
	return false;
}

AUX_RGBImageRec* CDoAnDHMTView::LoadBMP(char* Filename, string str)
{
	FILE* File = NULL;
	if (!Filename)
		return NULL;
	fopen_s(&File, Filename, "r");
	int32_t search_index = str.find(".bmp");
	if (File && search_index != -1)
	{
		fclose(File);
		return auxDIBImageLoadA((LPCSTR)Filename);
	}
	return NULL;
}

BOOL CDoAnDHMTView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
		return FALSE;
	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;
	return TRUE;
}

BOOL CDoAnDHMTView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (m_GLPixelIndex == 0) // Choose default
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
			return FALSE;
	}
	if (!SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc))
		return FALSE;
	return TRUE;
}

void CDoAnDHMTView::RenderScene(int type_is_draw, int m_nLEDType)
{
	double Ex = -4 * sin(PI / 180 * (m_xPointEye)) * cos(PI / 180 * (m_yPointEye));
	double Ey = 4 * sin(PI / 180 * (m_yPointEye));
	double Ez = 4 * cos(PI / 180 * (m_xPointEye)) * cos(PI / 180 * (m_yPointEye));
	switch (type_is_draw)
	{
	case CUBE:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawCube(m_nLEDType);
		break;
	}
	case TEAPOT:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawTeapot(m_nLEDType);
		break;
	}
	case SPHERE:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawSphere(m_nLEDType);
		break;
	}
	case CONE:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawCone(m_nLEDType);
		break;
	}
	case CYLINDER:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawCylinder(m_nLEDType);
		break;
	}
	case TORUS:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawTorus(m_nLEDType);
		break;
	}
	case DISK:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawDisk(m_nLEDType);
		break;
	}
	case PYRAMID:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawPyramid(m_nLEDType);
		break;
	}
	case OCTAGON:
	{
		gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, m_xCoordinate, m_yCoordinate, m_zCoordinate);
		CDoAnDHMTView::DrawOctagon(m_nLEDType);
		break;
	}
	default:
		break;
	}
}

void CDoAnDHMTView::ReShape(double SizeX, double SizeY, double fovy, double zNear, double zFar)
{
	double aspect = (double)SizeX / (double)SizeY;
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	gluPerspective(fovy, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);

}


CDoAnDHMTView::~CDoAnDHMTView()
{
	gluDeleteQuadric(m_pShape);
}

BOOL CDoAnDHMTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CDoAnDHMTView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	wglMakeCurrent(hDC, m_hGLContext);
	CDoAnDHMTView::Light();
	switch (m_TypeShadow)
	{
	case SMOOTH:
	{
		glShadeModel(GL_SMOOTH);
		break;
	}
	case FLAT:
	{
		glShadeModel(GL_FLAT);
		break;
	}
	default:
		break;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	CDoAnDHMTView::ReShape(Width, Height, fovy, zNear, zFar);
	CDoAnDHMTView::LoadGLTextures();
	glBindTexture(GL_TEXTURE_2D, texName);
	glPushMatrix();
	//Affine
	glRotatef(m_xRotation, 1.0, 0.0, 0.0);
	glRotatef(m_yRotation, 0.0, 1.0, 0.0);
	glRotatef(m_RotateAngle, m_AxisX, m_AxisY, m_AxisZ);
	//Rotate continuously in real time
	glTranslatef(m_xTranslate, m_yTranslate, m_zTranslate);
	glScalef(m_xScale, m_yScale, m_zScale);
	glFrontFace(GL_CW);

	RenderScene(type_is_draw, m_nLEDType);
	glPopMatrix();
	SwapBuffers(dc.m_ps.hdc);
}

void CDoAnDHMTView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CSize size(cx, cy);
	// Set OpenGL perspective, viewport and mode
	glViewport(0, 0, size.cx, size.cy);
}

int CDoAnDHMTView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	if (SetWindowPixelFormat(hDC) == FALSE)
		return 0;
	if (CreateViewGLContext(hDC) == FALSE)
		return 0;
	return 0;
}

void CDoAnDHMTView::Destroy()
{
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);
	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
	CView::OnDestroy();
}


// CDoAnDHMTView drawing

void CDoAnDHMTView::OnDraw(CDC* /*pDC*/)
{
	CDoAnDHMTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CDoAnDHMTView printing


void CDoAnDHMTView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDoAnDHMTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDoAnDHMTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDoAnDHMTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDoAnDHMTView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDoAnDHMTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_lBtnDown = FALSE;
	m_lBtnPos = point;
	CView::OnLButtonUp(nFlags, point);
}

void CDoAnDHMTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_lBtnDown = TRUE;
	m_lBtnPos = point;
	CView::OnLButtonDown(nFlags, point);
}

void CDoAnDHMTView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_lBtnDown)
	{
		switch (m_TypeAffine)
		{
		case ROTATE:
		{
			m_yRotation -= (double)(m_lBtnPos.x - point.x) / 9.0f;
			m_xRotation -= (double)(m_lBtnPos.y - point.y) / 9.0f;
			m_lBtnPos = point;
			Invalidate(FALSE);
			break;
		}
		case TRANSLATE:
		{
			if (isRotate == FALSE)
			{
				m_xTranslate += (double)(point.x - m_lBtnPos.x) / 54.0f;
				m_yTranslate += (double)(point.y - m_lBtnPos.y) / 54.0f;
				m_lBtnPos = point;
				Invalidate(FALSE);
			}
			break;
		}
		case SCALE:
		{
			m_xScale += (double)(point.x - m_lBtnPos.x) / 27.0f;
			m_yScale += (double)(point.y - m_lBtnPos.y) / 27.0f;
			m_lBtnPos = point;
			Invalidate(FALSE);
			break;
		}
		default:
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CDoAnDHMTView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		m_RotateAngle += speed_rotate;
		Invalidate(FALSE);
	}
	default:
		break;
	}
	CView::OnTimer(nIDEvent);
}

void CDoAnDHMTView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDoAnDHMTView diagnostics

#ifdef _DEBUG
void CDoAnDHMTView::AssertValid() const
{
	CView::AssertValid();
}

void CDoAnDHMTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDoAnDHMTDoc* CDoAnDHMTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoAnDHMTDoc)));
	return (CDoAnDHMTDoc*)m_pDocument;
}
#endif //_DEBUG


// CDoAnDHMTView message handlers
