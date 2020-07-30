
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
	int obj_draw;
	int PixelIndex;
	int Led_Type;
	int Type_Affine;
	int Type_Shadow;
	int speed_rotate;
	int Set_Timer;
	int Type_CoordinateView;
	int xEye;
	int yEye;
	int AxisX;
	int AxisY;
	int AxisZ;

	double Width;
	double Height;
	double SizeZ;
	double NearZ;
	double FarZ;
	double xRotation;
	double yRotation;
	double zRotation;
	double xTranslate;
	double yTranslate;
	double zTranslate;
	double xScale;
	double yScale;
	double zScale;
	double angle;
	double AmbientRed;
	double AmbientGreen;
	double AmbientBlue;
	double DiffuseRed;
	double DiffuseGreen;
	double DiffuseBlue;
	double SpecularRed;
	double SpecularGreen;
	double SpecularBlue;
	double RotateAngle;
	double ViewX;
	double ViewY;
	double ViewZ;

	char* PathName;
	string path_name;

	BOOL isRotate;
	GLuint texName;
	CPoint lBtnPos;
	BOOL lBtnDown;
	GLUquadricObj* pShape;
	HGLRC hGLContext;

	void Init();
	void DrawCube(int LEDType);
	void DrawTeapot(int LEDType);
	void DrawSphere(int LEDType);
	void DrawCone(int LEDType);
	void DrawCylinder(int LEDType);
	void DrawTorus(int LEDType);
	void DrawDisk(int LEDType);
	void DrawPyramid(int LEDType);
	void DrawOctagon(int LEDType);
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
		obj_draw = is_draw;
	}
	void set_draw_type(int type_draw)
	{
		Led_Type = type_draw;
	}
	void set_size_perspective(int SizeX, int SizeY, int NearZ, int FarZ, int SizeZ)
	{
		Width = SizeX;
		Height = SizeY;
		this->NearZ = NearZ;
		this->FarZ = FarZ;
		this->SizeZ = SizeZ;
	}
	void set_affine_type(int TypeAffine)
	{
		this->Type_Affine = TypeAffine;
		lBtnDown = FALSE;
	}
	void set_ambient_rgb(int R, int G, int B)
	{
		AmbientRed = (double)R / 10;
		AmbientGreen = (double)G / 10;
		AmbientBlue = (double)B / 10;
	}
	void set_diff_use_rgb(int R, int G, int B)
	{
		DiffuseRed = (double)R / 10;
		DiffuseGreen = (double)G / 10;
		DiffuseBlue = (double)B / 10;
	}
	void set_specular_rgb(int R, int G, int B)
	{
		SpecularRed = (double)R / 10;
		SpecularGreen = (double)G / 10;
		SpecularBlue = (double)B / 10;
	}
	void set_shadow_type(int TypeShadow)
	{
		this->Type_Shadow = TypeShadow;
	}
	void set_status_rotate(BOOL isRotate)
	{
		this->isRotate = isRotate;
		if (this->isRotate == TRUE)
		{
			SetTimer(Set_Timer, 50, NULL);
		}
		else
		{
			KillTimer(Set_Timer);
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
	void set_coordinate_view(int TypeCoordinateView)
	{
		this->Type_CoordinateView = TypeCoordinateView;
		switch (TypeCoordinateView)
		{
		case X_VIEW:
		{
			ViewX = cos(PI / 180 * (yEye));
			ViewY = 0.0;
			ViewZ = 0.0;
			break;
		}
		case Y_VIEW:
		{
			ViewX = 0.0;
			ViewY = cos(PI / 180 * (yEye));
			ViewZ = 0.0;
			break;
		}
		case Z_VIEW:
		{
			ViewX = 0.0;
			ViewY = 0.0;
			ViewZ = cos(PI / 180 * (yEye));
			break;
		}
		default:
			break;
		}
	}
	void set_point_eye(int m_xPointEye, int m_yPointEye)
	{
		this->xEye = m_xPointEye;
		this->yEye = m_yPointEye;
	}
	void set_axis_rotate(int AxisX, int AxisY, int AxisZ)
	{
		this->AxisX = AxisX;
		this->AxisY = AxisY;
		this->AxisZ = AxisZ;
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

