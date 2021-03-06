#pragma once
#include "DoAnDHMT.h"
#include "DoAnDHMTDoc.h"
#include "DoAnDHMTView.h"
#include "MainFrm.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


#define SPHERE 1
#define CONE 2
#define CUBE  3
#define CYLINDER 4
#define TORUS 5
#define TEAPOT 6
#define DISK	7
#define PYRAMID 18
#define OCTAGON 19

#define WIRE 1
#define SOLID 2
#define POINTS 3
#define SILHOUETTE 4

#define ROTATE 10
#define TRANSLATE 11
#define SCALE 12

#define FLAT	  13
#define SMOOTH	 14

#define X_VIEW 15
#define Y_VIEW 16
#define Z_VIEW 17



// FormViewBar form view

class FormViewBar : public CFormView
{
	DECLARE_DYNCREATE(FormViewBar)
protected:
	int obj_draw;
	int Led_Type;
	int Type_Affine;
	int Type_Shadow;
	int TypeCoordinateView;
	int IDC_Draw_Type;
	int IDC_Type_Affine;
	int IDC_Type_Shadow;
	int IDC_SizeX;
	int IDC_SizeY;
	int IDC_NearZ;
	int IDC_FarZ;
	int IDC_SizeZ;
	int IDC_Ambient_Red;
	int IDC_Ambient_Green;
	int IDC_Ambient_Blue;
	int IDC_Diff_use_Red;
	int IDC_Diff_use_Green;
	int IDC_Diff_use_Blue;
	int IDC_Specular_Red;
	int IDC_Specular_Green;
	int IDC_Specular_Blue;

	int IDC_Axis_X;
	int IDC_Axis_Y;
	int IDC_Axis_Z;

	int IDC_Coordinate_View;

	int IDC_Speed_Rotate;

	int xEye;
	int yEye;

	BOOL isRotate;
public:
	void UpdateTypeDraw();
	void UpdateTypeAffine();
	void UpdateTypeShadow();
	void UpdateTypeCoordinateView();
	void Reset();

	void type_shape();
	void set_ambient();
	void set_diff_use();
	void set_specular();
	void set_speedrotate();
	void set_axisrotate();

	CString convert_int_to_CString(int value);
	// method of class FormViewBar
public:
	CDoAnDHMTView* GetAppView();

protected:
	FormViewBar();           // protected constructor used by dynamic creation
	virtual ~FormViewBar();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FormViewBar };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDrawCube();
	afx_msg void OnBnClickedDrawTeapot();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	CSliderCtrl m_VSliderBarX;
	CSliderCtrl m_VSliderBarY;
	CSliderCtrl m_VSliderBarzNear;
	CSliderCtrl m_VSliderBarzFar;
	CSliderCtrl m_VSliderBarFovy;
	CSliderCtrl m_DiffuseRed;
	CSliderCtrl m_DiffuseGreen;
	CSliderCtrl m_DiffuseBlue;
	CSliderCtrl m_SpecularRed;
	CSliderCtrl m_SpecularGreen;
	CSliderCtrl m_SpecularBlue;
	CSliderCtrl m_AmbientRed;
	CSliderCtrl m_AmbientGreen;
	CSliderCtrl m_AmbientBlue;
	CSliderCtrl m_VSliderBarSpeedRotate;
	CSliderCtrl m_VSliderBarAxisZ;
	CSliderCtrl m_VSliderBarAxis_Y;
	CSliderCtrl m_VSliderBarAxisX;
	CEdit m_EditControlzNear;
	CEdit m_EditControlSizeX;
	CEdit m_EditControlSizeY;
	CEdit m_EditControlFovy;
	CEdit m_EditControlzFar;
	CEdit m_EditControlSpeedRotate;
	CEdit m_EditControlAxisX;
	CEdit m_EditControlAxisY;
	CEdit m_EditControlAxisZ;
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedButton7();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton8();
};


