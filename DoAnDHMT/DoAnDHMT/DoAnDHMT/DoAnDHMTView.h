
// DoAnDHMTView.h : interface of the CDoAnDHMTView class
//

#pragma once
#include <Windows.h>
#include <iostream>
#include "include/GL/GL.H"
#include "include/GL/GLU.H"
#include "include/GL/glut.h"
#include "include/GL/GLAux.h"
#include "DoAnDHMTDoc.h"
#include <math.h>
#include <string>
using namespace std;
#pragma comment(lib, "legacy_stdio_definitions.lib")

//define the Actions
#define CAMERA_PAN      0
#define SCENE_PAN      1
#define CAMERA_ROTATE    2
#define SCENE_ROTATE    3

#define ROTATE 10
#define TRANSLATE 11
#define SCALE 12

#define SELECT          9

//define the ViewMode
#define X_VIEW 15
#define Y_VIEW 16
#define Z_VIEW 17

// define drawing modes
#define WIRE 1
#define SOLID 2
#define POINTS 3
#define SILHOUETTE 4

// define Lighting normals facing Inside or Outside
#define INSIDE	1
#define OUTSIDE	 2

// define Shading effects None, Flat or Smooth
#define FLAT	  13
#define SMOOTH	 14

// define Shapes type
#define SPHERE 1
#define CONE 2
#define CUBE  3
#define CYLINDER 4
#define TORUS 5
#define TEAPOT 6
#define DISK	7
#define PYRAMID 18
#define OCTAGON 19

#define PI 3.1415926535898
class CDoAnDHMTView : public CView
{
protected: // create from serialization only
	CDoAnDHMTView() noexcept;
	DECLARE_DYNCREATE(CDoAnDHMTView)
public:
	int type_is_draw;
	int m_GLPixelIndex;
	int m_nLEDType;
	int m_TypeAffine;
	int m_TypeShadow;
	int speed_rotate;
	int ID_SetTimer;
	int m_TypeCoordinateView;
	int m_xPointEye;
	int m_yPointEye;
	int m_AxisX;
	int m_AxisY;
	int m_AxisZ;

	double Width;
	double Height;
	double fovy;
	double zNear;
	double zFar;
	double m_xRotation;
	double m_yRotation;
	double m_zRotation;
	double m_xTranslate;
	double m_yTranslate;
	double m_zTranslate;
	double m_xScale;
	double m_yScale;
	double m_zScale;
	double angle;
	double m_AmbientRed;
	double m_AmbientGreen;
	double m_AmbientBlue;
	double m_DiffuseRed;
	double m_DiffuseGreen;
	double m_DiffuseBlue;
	double m_SpecularRed;
	double m_SpecularGreen;
	double m_SpecularBlue;
	double m_RotateAngle;
	double m_xCoordinate;
	double m_yCoordinate;
	double m_zCoordinate;

	char* PathName;
	string path_name;

	BOOL isRotate;
	GLuint texName;
	CPoint m_lBtnPos;
	BOOL m_lBtnDown;
	GLUquadricObj* m_pShape;
	HGLRC m_hGLContext;

	void Init();
	void DrawCube(int m_nLEDType);
	void DrawTeapot(int m_nLEDType);
	void DrawSphere(int m_nLEDType);
	void DrawCone(int m_nLEDType);
	void DrawCylinder(int m_nLEDType);
	void DrawTorus(int m_nLEDType);
	void DrawDisk(int m_nLEDType);
	void DrawPyramid(int m_nLEDType);
	void DrawOctagon(int m_nLEDType);
	void Pyramid(double size, double height);
	void Octagon(double side, double thickness);
	void Light();
	bool LoadGLTextures();
	AUX_RGBImageRec* LoadBMP(char* Filename, string str);

	// Attributes
public:
	CDoAnDHMTDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	void set_draw_cicurlar(int is_draw)
	{
		type_is_draw = is_draw;
	}
	void set_draw_type(int type_draw)
	{
		m_nLEDType = type_draw;
	}
	void set_size_perspective(int SizeX, int SizeY, int zNear, int zFar, int fovy)
	{
		Width = SizeX;
		Height = SizeY;
		this->zNear = zNear;
		this->zFar = zFar;
		this->fovy = fovy;
	}
	void set_affine_type(int m_TypeAffine)
	{
		this->m_TypeAffine = m_TypeAffine;
		m_lBtnDown = FALSE;
	}
	void set_ambient_rgb(int R, int G, int B)
	{
		m_AmbientRed = (double)R / 10;
		m_AmbientGreen = (double)G / 10;
		m_AmbientBlue = (double)B / 10;
	}
	void set_diff_use_rgb(int R, int G, int B)
	{
		m_DiffuseRed = (double)R / 10;
		m_DiffuseGreen = (double)G / 10;
		m_DiffuseBlue = (double)B / 10;
	}
	void set_specular_rgb(int R, int G, int B)
	{
		m_SpecularRed = (double)R / 10;
		m_SpecularGreen = (double)G / 10;
		m_SpecularBlue = (double)B / 10;
	}
	void set_shadow_type(int m_TypeShadow)
	{
		this->m_TypeShadow = m_TypeShadow;
	}
	void set_status_rotate(BOOL isRotate)
	{
		this->isRotate = isRotate;
		if (this->isRotate == TRUE)
		{
			SetTimer(ID_SetTimer, 50, NULL);
		}
		else
		{
			KillTimer(ID_SetTimer);
		}
	}
	void set_speed_rotate(int speed_rotate)
	{
		this->speed_rotate = speed_rotate;
	}
	void Reset_CDoAnDHMTView()
	{
		CDoAnDHMTView::Init();
		CDoAnDHMTDoc* pDoc = GetDocument();
		pDoc->is_set_path_texture(path_name);
	}
	void set_coordinate_view(int m_TypeCoordinateView)
	{
		this->m_TypeCoordinateView = m_TypeCoordinateView;
		switch (m_TypeCoordinateView)
		{
		case X_VIEW:
		{
			m_xCoordinate = cos(PI / 180 * (m_yPointEye));
			m_yCoordinate = 0.0;
			m_zCoordinate = 0.0;
			break;
		}
		case Y_VIEW:
		{
			m_xCoordinate = 0.0;
			m_yCoordinate = cos(PI / 180 * (m_yPointEye));
			m_zCoordinate = 0.0;
			break;
		}
		case Z_VIEW:
		{
			m_xCoordinate = 0.0;
			m_yCoordinate = 0.0;
			m_zCoordinate = cos(PI / 180 * (m_yPointEye));
			break;
		}
		default:
			break;
		}
	}
	void set_point_eye(int m_xPointEye, int m_yPointEye)
	{
		this->m_xPointEye = m_xPointEye;
		this->m_yPointEye = m_yPointEye;
	}
	void set_axis_rotate(int m_AxisX, int m_AxisY, int m_AxisZ)
	{
		this->m_AxisX = m_AxisX;
		this->m_AxisY = m_AxisY;
		this->m_AxisZ = m_AxisZ;
	}

	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	BOOL CreateViewGLContext(HDC hDC);
	BOOL SetWindowPixelFormat(HDC hDC);
	void RenderScene(int type_is_draw, int m_nLEDType);
	void ReShape(double SizeX, double Sizey, double fovy, double zNear, double zFar);
	virtual ~CDoAnDHMTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void Destroy();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DoAnDHMTView.cpp
inline CDoAnDHMTDoc* CDoAnDHMTView::GetDocument() const
{
	return reinterpret_cast<CDoAnDHMTDoc*>(m_pDocument);
}
#endif

