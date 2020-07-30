// FormViewBar.cpp : implementation file
//

#include "pch.h"
#include "DoAnDHMT.h"
#include "FormViewBar.h"


// FormViewBar

IMPLEMENT_DYNCREATE(FormViewBar, CFormView)

FormViewBar::FormViewBar()
	: CFormView(IDD_FormViewBar)
{
	type_is_draw = 0;
	m_nLEDType = WIRE;
	m_TypeAffine = ROTATE;
	m_TypeShadow = SMOOTH;
	m_TypeCoordinateView = X_VIEW;

	IDC_Draw_Type = IDC_RADIO2;
	IDC_Type_Affine = IDC_RADIO4;
	IDC_Type_Shadow = IDC_RADIO7;
	IDC_View_Coordinate = IDC_RADIO9;

	IDC_SizeX = 50;
	IDC_SizeY = 50;
	IDC_Fovy = 90;
	IDC_Znear = 1;
	IDC_Zfar = 80;

	IDC_Ambient_R = 1;
	IDC_Ambient_G = 1;
	IDC_Ambient_B = 1;

	IDC_Diff_use_R = 5;
	IDC_Diff_use_G = 5;
	IDC_Diff_use_B = 5;

	IDC_Specular_R = 10;
	IDC_Specular_G = 10;
	IDC_Specular_B = 10;

	IDC_SpeedRotate = 5.0;

	IDC_Axis_X = 0.0;
	IDC_Axis_Y = 0.0;
	IDC_Axis_Z = 1.0;

	m_xPointEye = 20.0;
	m_yPointEye = 20.0;

	isRotate = FALSE;
}

FormViewBar::~FormViewBar()
{
}

void FormViewBar::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_VSliderBarX.SetRange(1, 100, FALSE);
	m_VSliderBarY.SetRange(1, 100, FALSE);
	m_VSliderBarFovy.SetRange(0, 180, FALSE);
	m_VSliderBarzNear.SetRange(1, 10, FALSE);
	m_VSliderBarzFar.SetRange(1, 100, FALSE);

	m_AmbientRed.SetRange(0, 10, FALSE);
	m_AmbientGreen.SetRange(0, 10, FALSE);
	m_AmbientBlue.SetRange(0, 10, FALSE);

	m_DiffuseRed.SetRange(0, 10, FALSE);
	m_DiffuseGreen.SetRange(0, 10, FALSE);
	m_DiffuseBlue.SetRange(0, 10, FALSE);

	m_SpecularRed.SetRange(0, 10, FALSE);
	m_SpecularGreen.SetRange(0, 10, FALSE);
	m_SpecularBlue.SetRange(0, 10, FALSE);

	m_VSliderBarSpeedRotate.SetRange(1, 10, FALSE);

	m_VSliderBarAxisX.SetRange(0, 20);
	m_VSliderBarAxis_Y.SetRange(0, 20);
	m_VSliderBarAxisZ.SetRange(0, 20);

	m_VSliderBarX.SetPos(IDC_SizeX);
	m_VSliderBarY.SetPos(IDC_SizeY);
	m_VSliderBarFovy.SetPos(IDC_Fovy);
	m_VSliderBarzNear.SetPos(IDC_Znear);
	m_VSliderBarzFar.SetPos(IDC_Zfar);

	m_AmbientRed.SetPos(IDC_Ambient_R);
	m_AmbientGreen.SetPos(IDC_Ambient_G);
	m_AmbientBlue.SetPos(IDC_Ambient_B);

	m_DiffuseRed.SetPos(IDC_Diff_use_R);
	m_DiffuseGreen.SetPos(IDC_Diff_use_G);
	m_DiffuseBlue.SetPos(IDC_Diff_use_B);

	m_SpecularRed.SetPos(IDC_Specular_R);
	m_SpecularGreen.SetPos(IDC_Specular_G);
	m_SpecularBlue.SetPos(IDC_Specular_B);

	m_VSliderBarSpeedRotate.SetPos(IDC_SpeedRotate);

	m_VSliderBarAxisX.SetPos(IDC_Axis_X);
	m_VSliderBarAxis_Y.SetPos(IDC_Axis_Y);
	m_VSliderBarAxisZ.SetPos(IDC_Axis_Z);

	m_EditControlzNear.SetWindowTextW(convert_int_to_CString(IDC_Znear));
	m_EditControlSizeX.SetWindowTextW(convert_int_to_CString(IDC_SizeX));
	m_EditControlSizeY.SetWindowTextW(convert_int_to_CString(IDC_SizeY));
	m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
	m_EditControlzFar.SetWindowTextW(convert_int_to_CString(IDC_Zfar));
	m_EditControlSpeedRotate.SetWindowTextW(convert_int_to_CString(IDC_SpeedRotate));
	m_EditControlAxisX.SetWindowTextW(convert_int_to_CString(IDC_Axis_X));
	m_EditControlAxisY.SetWindowTextW(convert_int_to_CString(IDC_Axis_Y));
	m_EditControlAxisZ.SetWindowTextW(convert_int_to_CString(IDC_Axis_Z));

	FormViewBar::UpdateTypeDraw();
	FormViewBar::UpdateTypeAffine();
	FormViewBar::UpdateTypeShadow();
	FormViewBar::UpdateTypeCoordinateView();
}


void FormViewBar::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
	pButton2->SetCheck(true);
	CButton* pButton4 = (CButton*)GetDlgItem(IDC_RADIO4);
	pButton4->SetCheck(true);
	CButton* pButton7 = (CButton*)GetDlgItem(IDC_RADIO7);
	pButton7->SetCheck(true);
	CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
	pButton9->SetCheck(true);

	DDX_Control(pDX, IDC_SLIDER1, m_VSliderBarX);
	DDX_Control(pDX, IDC_SLIDER2, m_VSliderBarY);
	DDX_Control(pDX, IDC_SLIDER4, m_VSliderBarzNear);
	DDX_Control(pDX, IDC_SLIDER5, m_VSliderBarzFar);
	DDX_Control(pDX, IDC_SLIDER3, m_VSliderBarFovy);
	DDX_Control(pDX, IDC_SLIDER6, m_AmbientRed);
	DDX_Control(pDX, IDC_SLIDER7, m_AmbientGreen);
	DDX_Control(pDX, IDC_SLIDER8, m_AmbientBlue);
	DDX_Control(pDX, IDC_SLIDER9, m_DiffuseRed);
	DDX_Control(pDX, IDC_SLIDER10, m_DiffuseGreen);
	DDX_Control(pDX, IDC_SLIDER11, m_DiffuseBlue);
	DDX_Control(pDX, IDC_SLIDER12, m_SpecularRed);
	DDX_Control(pDX, IDC_SLIDER13, m_SpecularGreen);
	DDX_Control(pDX, IDC_SLIDER14, m_SpecularBlue);
	DDX_Control(pDX, IDC_SLIDER15, m_VSliderBarSpeedRotate);
	DDX_Control(pDX, IDC_SLIDER18, m_VSliderBarAxisZ);
	DDX_Control(pDX, IDC_SLIDER16, m_VSliderBarAxisX);
	DDX_Control(pDX, IDC_SLIDER17, m_VSliderBarAxis_Y);
	DDX_Control(pDX, IDC_EDIT1, m_EditControlzNear);
	DDX_Control(pDX, IDC_EDIT2, m_EditControlSizeX);
	DDX_Control(pDX, IDC_EDIT3, m_EditControlSizeY);
	DDX_Control(pDX, IDC_EDIT4, m_EditControlFovy);
	DDX_Control(pDX, IDC_EDIT5, m_EditControlzFar);
	DDX_Control(pDX, IDC_EDIT6, m_EditControlSpeedRotate);
	DDX_Control(pDX, IDC_EDIT7, m_EditControlAxisX);
	DDX_Control(pDX, IDC_EDIT8, m_EditControlAxisY);
	DDX_Control(pDX, IDC_EDIT9, m_EditControlAxisZ);
}

BEGIN_MESSAGE_MAP(FormViewBar, CFormView)
	ON_BN_CLICKED(ID_DRAW_CUBE, &FormViewBar::OnBnClickedDrawCube)
	ON_BN_CLICKED(ID_DRAW_TEAPOT, &FormViewBar::OnBnClickedDrawTeapot)
	ON_BN_CLICKED(IDC_RADIO1, &FormViewBar::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &FormViewBar::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &FormViewBar::OnBnClickedRadio3)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO4, &FormViewBar::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &FormViewBar::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &FormViewBar::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_BUTTON1, &FormViewBar::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &FormViewBar::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &FormViewBar::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &FormViewBar::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_RADIO7, &FormViewBar::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &FormViewBar::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_BUTTON5, &FormViewBar::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &FormViewBar::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_RADIO9, &FormViewBar::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &FormViewBar::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &FormViewBar::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_BUTTON7, &FormViewBar::OnBnClickedButton7)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON9, &FormViewBar::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &FormViewBar::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON8, &FormViewBar::OnBnClickedButton8)
END_MESSAGE_MAP()


// FormViewBar diagnostics

#ifdef _DEBUG
void FormViewBar::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FormViewBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
//Get data MainView to FormView

void FormViewBar::UpdateTypeDraw()
{
	switch (IDC_Draw_Type)
	{
	case IDC_RADIO1:
	{
		CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
		pButton1->SetCheck(true);
		CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
		pButton2->SetCheck(false);
		CButton* pButton3 = (CButton*)GetDlgItem(IDC_RADIO3);
		pButton3->SetCheck(false);
		break;
	}
	case IDC_RADIO2:
	{
		CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
		pButton1->SetCheck(false);
		CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
		pButton2->SetCheck(true);
		CButton* pButton3 = (CButton*)GetDlgItem(IDC_RADIO3);
		pButton3->SetCheck(false);
		break;
	}
	case IDC_RADIO3:
	{
		CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
		pButton1->SetCheck(false);
		CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
		pButton2->SetCheck(false);
		CButton* pButton3 = (CButton*)GetDlgItem(IDC_RADIO3);
		pButton3->SetCheck(true);
		break;
	}
	default:
		break;
	}
}

void FormViewBar::UpdateTypeAffine()
{
	switch (IDC_Type_Affine)
	{
	case IDC_RADIO4:
	{
		CButton* pButton4 = (CButton*)GetDlgItem(IDC_RADIO4);
		pButton4->SetCheck(true);
		CButton* pButton5 = (CButton*)GetDlgItem(IDC_RADIO5);
		pButton5->SetCheck(false);
		CButton* pButton6 = (CButton*)GetDlgItem(IDC_RADIO6);
		pButton6->SetCheck(false);
		break;
	}
	case IDC_RADIO5:
	{
		CButton* pButton4 = (CButton*)GetDlgItem(IDC_RADIO4);
		pButton4->SetCheck(false);
		CButton* pButton5 = (CButton*)GetDlgItem(IDC_RADIO5);
		pButton5->SetCheck(true);
		CButton* pButton6 = (CButton*)GetDlgItem(IDC_RADIO6);
		pButton6->SetCheck(false);
		break;
	}
	case IDC_RADIO6:
	{
		CButton* pButton4 = (CButton*)GetDlgItem(IDC_RADIO4);
		pButton4->SetCheck(false);
		CButton* pButton5 = (CButton*)GetDlgItem(IDC_RADIO5);
		pButton5->SetCheck(false);
		CButton* pButton6 = (CButton*)GetDlgItem(IDC_RADIO6);
		pButton6->SetCheck(true);
		break;
	}
	default:
		break;
	}
}

void FormViewBar::UpdateTypeShadow()
{
	switch (IDC_Type_Shadow)
	{
	case IDC_RADIO7:
	{
		CButton* pButton7 = (CButton*)GetDlgItem(IDC_RADIO7);
		pButton7->SetCheck(true);
		CButton* pButton8 = (CButton*)GetDlgItem(IDC_RADIO8);
		pButton8->SetCheck(false);
		break;
	}
	case IDC_RADIO8:
	{
		CButton* pButton7 = (CButton*)GetDlgItem(IDC_RADIO7);
		pButton7->SetCheck(false);
		CButton* pButton8 = (CButton*)GetDlgItem(IDC_RADIO8);
		pButton8->SetCheck(true);
		break;
	}
	default:
		break;
	}
}

void FormViewBar::UpdateTypeCoordinateView()
{
	switch (IDC_View_Coordinate)
	{
	case IDC_RADIO9:
	{
		CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
		pButton9->SetCheck(true);
		CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
		pButton10->SetCheck(false);
		CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
		pButton11->SetCheck(false);
		break;
	}
	case IDC_RADIO10:
	{
		CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
		pButton9->SetCheck(false);
		CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
		pButton10->SetCheck(true);
		CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
		pButton11->SetCheck(false);
		break;
	}
	case IDC_RADIO11:
	{
		CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
		pButton9->SetCheck(false);
		CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
		pButton10->SetCheck(false);
		CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
		pButton11->SetCheck(true);
		break;
	}
	default:
		break;
	}
}

void FormViewBar::Reset()
{
	type_is_draw = 0;
	m_nLEDType = WIRE;
	m_TypeAffine = ROTATE;
	m_TypeShadow = SMOOTH;
	m_TypeCoordinateView = X_VIEW;

	IDC_Draw_Type = IDC_RADIO2;
	IDC_Type_Affine = IDC_RADIO4;
	IDC_Type_Shadow = IDC_RADIO7;
	IDC_View_Coordinate = IDC_RADIO9;

	IDC_SizeX = 50;
	IDC_SizeY = 50;
	IDC_Fovy = 90;
	IDC_Znear = 1;
	IDC_Zfar = 80;

	IDC_Ambient_R = 1;
	IDC_Ambient_G = 1;
	IDC_Ambient_B = 1;

	IDC_Diff_use_R = 5;
	IDC_Diff_use_G = 5;
	IDC_Diff_use_B = 5;

	IDC_Specular_R = 10;
	IDC_Specular_G = 10;
	IDC_Specular_B = 10;

	IDC_SpeedRotate = 5.0;

	IDC_Axis_X = 0.0;
	IDC_Axis_Y = 0.0;
	IDC_Axis_Z = 1.0;

	m_xPointEye = 20.0;
	m_yPointEye = 20.0;

	m_EditControlzNear.SetWindowTextW(convert_int_to_CString(IDC_Znear));
	m_EditControlSizeX.SetWindowTextW(convert_int_to_CString(IDC_SizeX));
	m_EditControlSizeY.SetWindowTextW(convert_int_to_CString(IDC_SizeY));
	m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
	m_EditControlzFar.SetWindowTextW(convert_int_to_CString(IDC_Zfar));
	m_EditControlSpeedRotate.SetWindowTextW(convert_int_to_CString(IDC_SpeedRotate));
	m_EditControlAxisX.SetWindowTextW(convert_int_to_CString(IDC_Axis_X));
	m_EditControlAxisY.SetWindowTextW(convert_int_to_CString(IDC_Axis_Y));
	m_EditControlAxisZ.SetWindowTextW(convert_int_to_CString(IDC_Axis_Z));

	isRotate = FALSE;
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
	pButton2->SetCheck(true);
	CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
	pButton1->SetCheck(false);
	CButton* pButton3 = (CButton*)GetDlgItem(IDC_RADIO3);
	pButton3->SetCheck(false);
	CButton* pButton4 = (CButton*)GetDlgItem(IDC_RADIO4);
	pButton4->SetCheck(true);
	CButton* pButton5 = (CButton*)GetDlgItem(IDC_RADIO5);
	pButton5->SetCheck(false);
	CButton* pButton6 = (CButton*)GetDlgItem(IDC_RADIO6);
	pButton6->SetCheck(false);
	CButton* pButton7 = (CButton*)GetDlgItem(IDC_RADIO7);
	pButton7->SetCheck(true);
	CButton* pButton8 = (CButton*)GetDlgItem(IDC_RADIO8);
	pButton8->SetCheck(false);
	CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
	pButton9->SetCheck(true);
	CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
	pButton10->SetCheck(false);
	CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
	pButton11->SetCheck(false);
	FormViewBar::OnInitialUpdate();
	if (GetAppView())
	{
		GetAppView()->set_status_rotate(isRotate);
		GetAppView()->Reset_CDoAnDHMTView();
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::is_type_shape()
{
	if (GetAppView())
	{
		GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_Znear, IDC_Zfar, IDC_Fovy);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::is_set_ambient()
{
	if (GetAppView())
	{
		GetAppView()->set_ambient_rgb(IDC_Ambient_R, IDC_Ambient_G, IDC_Ambient_B);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::is_set_diff_use()
{
	if (GetAppView())
	{
		GetAppView()->set_diff_use_rgb(IDC_Diff_use_R, IDC_Diff_use_G, IDC_Diff_use_B);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::is_set_specular()
{
	if (GetAppView())
	{
		GetAppView()->set_specular_rgb(IDC_Specular_R, IDC_Specular_G, IDC_Specular_B);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::is_set_speedrotate()
{
	if (GetAppView())
	{
		GetAppView()->set_speed_rotate(IDC_SpeedRotate);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::is_set_axisrotate()
{
	if (GetAppView())
	{
		GetAppView()->set_axis_rotate(IDC_Axis_X, IDC_Axis_Y, IDC_Axis_Z);
		GetAppView()->Invalidate(FALSE);
	}
}

CString FormViewBar::convert_int_to_CString(int value)
{
	CString str;
	str.Format(_T("%d"), value);
	return str;
}

CDoAnDHMTView* FormViewBar::GetAppView()
{
	CDoAnDHMTApp* pApp = (CDoAnDHMTApp*)AfxGetApp();
	CMainFrame* pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
	CDoAnDHMTView* pLeftView = (CDoAnDHMTView*)pMainFrame->GetMainView();
	return pLeftView;
}


// FormViewBar message handlers


void FormViewBar::OnBnClickedDrawCube()
{
	type_is_draw = CUBE;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

void FormViewBar::OnBnClickedDrawTeapot()
{
	type_is_draw = TEAPOT;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton1()
{
	type_is_draw = SPHERE;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton2()
{
	type_is_draw = CONE;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton3()
{
	type_is_draw = CYLINDER;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton4()
{
	type_is_draw = TORUS;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio1()
{
	m_nLEDType = POINTS;
	IDC_Draw_Type = IDC_RADIO1;
	if (GetAppView())
	{
		GetAppView()->set_draw_type(m_nLEDType);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio2()
{
	m_nLEDType = WIRE;
	IDC_Draw_Type = IDC_RADIO2;
	if (GetAppView())
	{
		GetAppView()->set_draw_type(m_nLEDType);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio3()
{
	m_nLEDType = SOLID;
	IDC_Draw_Type = IDC_RADIO3;
	if (GetAppView())
	{
		GetAppView()->set_draw_type(m_nLEDType);;
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

void FormViewBar::OnBnClickedRadio4()
{
	m_TypeAffine = ROTATE;
	IDC_Type_Affine = IDC_RADIO4;
	if (GetAppView())
	{
		GetAppView()->set_affine_type(m_TypeAffine);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio5()
{
	m_TypeAffine = TRANSLATE;
	IDC_Type_Affine = IDC_RADIO5;
	if (GetAppView())
	{
		GetAppView()->set_affine_type(m_TypeAffine);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio6()
{
	m_TypeAffine = SCALE;
	IDC_Type_Affine = IDC_RADIO6;
	if (GetAppView())
	{
		GetAppView()->set_affine_type(m_TypeAffine);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

void FormViewBar::OnBnClickedRadio7()
{
	m_TypeShadow = SMOOTH;
	IDC_Type_Shadow = IDC_RADIO7;
	if (GetAppView())
	{
		GetAppView()->set_shadow_type(m_TypeShadow);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio8()
{
	m_TypeShadow = FLAT;
	IDC_Type_Shadow = IDC_RADIO8;
	if (GetAppView())
	{
		GetAppView()->set_shadow_type(m_TypeShadow);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton5()
{
	isRotate = TRUE;
	if (GetAppView())
	{
		GetAppView()->set_status_rotate(isRotate);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton6()
{
	isRotate = FALSE;
	if (GetAppView())
	{
		GetAppView()->set_status_rotate(isRotate);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio9()
{
	m_TypeCoordinateView = X_VIEW;
	IDC_View_Coordinate = IDC_RADIO9;
	if (GetAppView())
	{
		GetAppView()->set_coordinate_view(m_TypeCoordinateView);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio10()
{
	m_TypeCoordinateView = Y_VIEW;
	IDC_View_Coordinate = IDC_RADIO10;
	if (GetAppView())
	{
		GetAppView()->set_coordinate_view(m_TypeCoordinateView);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio11()
{
	m_TypeCoordinateView = Z_VIEW;
	IDC_View_Coordinate = IDC_RADIO11;
	if (GetAppView())
	{
		GetAppView()->set_coordinate_view(m_TypeCoordinateView);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton7()
{
	FormViewBar::Reset();
	// TODO: Add your control notification handler code here
}

BOOL FormViewBar::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_F5:
		{
			FormViewBar::Reset();
			break;
		}
		case VK_SUBTRACT:
		{
			IDC_Fovy++;
			if (IDC_Fovy > 180)
			{
				IDC_Fovy = 180;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_Znear, IDC_Zfar, IDC_Fovy);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_Fovy);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
			break;
		}
		case VK_OEM_MINUS:
		{
			IDC_Fovy++;
			if (IDC_Fovy > 180)
			{
				IDC_Fovy = 180;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_Znear, IDC_Zfar, IDC_Fovy);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_Fovy);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
			break;
		}
		case VK_OEM_PLUS:
		{
			IDC_Fovy--;
			if (IDC_Fovy < 0)
			{
				IDC_Fovy = 0;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_Znear, IDC_Zfar, IDC_Fovy);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_Fovy);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
			break;
		}
		case VK_ADD:
		{
			IDC_Fovy--;
			if (IDC_Fovy < 0)
			{
				IDC_Fovy = 0;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_Znear, IDC_Zfar, IDC_Fovy);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_Fovy);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
			break;
		}
		case 0x52:
		{
			isRotate = TRUE;
			if (GetAppView())
			{
				GetAppView()->set_status_rotate(isRotate);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_SPACE:
		{
			isRotate = FALSE;
			if (GetAppView())
			{
				GetAppView()->set_status_rotate(isRotate);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_LEFT:
		{
			m_xPointEye--;
			{
				GetAppView()->set_point_eye(m_xPointEye, m_yPointEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_RIGHT:
		{
			m_xPointEye++;
			{
				GetAppView()->set_point_eye(m_xPointEye, m_yPointEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_UP:
		{
			m_yPointEye++;
			{
				GetAppView()->set_point_eye(m_xPointEye, m_yPointEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_DOWN:
		{
			m_yPointEye--;
			{
				GetAppView()->set_point_eye(m_xPointEye, m_yPointEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case 0x58:
		{
			m_TypeCoordinateView = X_VIEW;
			IDC_View_Coordinate = IDC_RADIO9;
			CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
			pButton9->SetCheck(true);
			CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
			pButton10->SetCheck(false);
			CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
			pButton11->SetCheck(false);
			if (GetAppView())
			{
				GetAppView()->set_coordinate_view(m_TypeCoordinateView);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case 0x59:
		{
			m_TypeCoordinateView = Y_VIEW;
			IDC_View_Coordinate = IDC_RADIO10;
			CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
			pButton9->SetCheck(false);
			CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
			pButton10->SetCheck(true);
			CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
			pButton11->SetCheck(false);
			if (GetAppView())
			{
				GetAppView()->set_coordinate_view(m_TypeCoordinateView);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case 0x5A:
		{
			m_TypeCoordinateView = Z_VIEW;
			IDC_View_Coordinate = IDC_RADIO11;
			CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
			pButton9->SetCheck(false);
			CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
			pButton10->SetCheck(false);
			CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
			pButton11->SetCheck(true);
			if (GetAppView())
			{
				GetAppView()->set_coordinate_view(m_TypeCoordinateView);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		default:
			break;
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYUP)
		return TRUE;
	else
		return CFormView::PreTranslateMessage(pMsg);
}




void FormViewBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	switch (pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER1:
	{
		IDC_SizeX = m_VSliderBarX.GetPos();
		m_EditControlSizeX.SetWindowTextW(convert_int_to_CString(IDC_SizeX));
		FormViewBar::is_type_shape();
		break;
	}
	case IDC_SLIDER2:
	{
		IDC_SizeY = m_VSliderBarY.GetPos();
		m_EditControlSizeY.SetWindowTextW(convert_int_to_CString(IDC_SizeY));
		FormViewBar::is_type_shape();
		break;
	}
	case IDC_SLIDER3:
	{
		IDC_Fovy = m_VSliderBarFovy.GetPos();
		m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_Fovy));
		FormViewBar::is_type_shape();
		break;
	}
	case IDC_SLIDER4:
	{
		IDC_Znear = m_VSliderBarzNear.GetPos();
		m_EditControlzNear.SetWindowTextW(convert_int_to_CString(IDC_Znear));
		FormViewBar::is_type_shape();
		break;
	}
	case IDC_SLIDER5:
	{
		IDC_Zfar = m_VSliderBarzFar.GetPos();
		m_EditControlzFar.SetWindowTextW(convert_int_to_CString(IDC_Zfar));
		FormViewBar::is_type_shape();
		break;
	}
	case IDC_SLIDER6:
	{
		IDC_Ambient_R = m_AmbientRed.GetPos();
		FormViewBar::is_set_ambient();
		break;
	}
	case IDC_SLIDER7:
	{
		IDC_Ambient_G = m_AmbientGreen.GetPos();
		FormViewBar::is_set_ambient();
		break;
	}
	case IDC_SLIDER8:
	{
		IDC_Ambient_B = m_AmbientBlue.GetPos();
		FormViewBar::is_set_ambient();
		break;
	}
	case IDC_SLIDER9:
	{
		IDC_Diff_use_R = m_DiffuseRed.GetPos();
		FormViewBar::is_set_diff_use();
		break;
	}
	case IDC_SLIDER10:
	{
		IDC_Diff_use_G = m_DiffuseGreen.GetPos();
		FormViewBar::is_set_diff_use();
		break;
	}
	case IDC_SLIDER11:
	{
		IDC_Diff_use_B = m_DiffuseBlue.GetPos();
		FormViewBar::is_set_diff_use();
		break;
	}
	case IDC_SLIDER12:
	{
		IDC_Specular_R = m_SpecularRed.GetPos();
		FormViewBar::is_set_specular();
		break;
	}
	case IDC_SLIDER13:
	{
		IDC_Specular_G = m_SpecularGreen.GetPos();
		FormViewBar::is_set_specular();
		break;
	}
	case IDC_SLIDER14:
	{
		IDC_Specular_B = m_SpecularBlue.GetPos();
		FormViewBar::is_set_specular();
		break;
	}
	case IDC_SLIDER15:
	{
		IDC_SpeedRotate = m_VSliderBarSpeedRotate.GetPos();
		m_EditControlSpeedRotate.SetWindowTextW(convert_int_to_CString(IDC_SpeedRotate));
		FormViewBar::is_set_speedrotate();
		break;
	}
	case IDC_SLIDER16:
	{
		IDC_Axis_X = m_VSliderBarAxisX.GetPos();
		m_EditControlAxisX.SetWindowTextW(convert_int_to_CString(IDC_Axis_X));
		FormViewBar::is_set_axisrotate();
		break;
	}
	case IDC_SLIDER17:
	{
		IDC_Axis_Y = m_VSliderBarAxis_Y.GetPos();
		m_EditControlAxisY.SetWindowTextW(convert_int_to_CString(IDC_Axis_Y));
		FormViewBar::is_set_axisrotate();
		break;
	}
	case IDC_SLIDER18:
	{
		IDC_Axis_Z = m_VSliderBarAxisZ.GetPos();
		m_EditControlAxisZ.SetWindowTextW(convert_int_to_CString(IDC_Axis_Z));
		FormViewBar::is_set_axisrotate();
		break;
	}
	default:
		break;
	}
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}




void FormViewBar::OnBnClickedButton9()
{
	type_is_draw = PYRAMID;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}


void FormViewBar::OnBnClickedButton10()
{
	type_is_draw = OCTAGON;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}


void FormViewBar::OnBnClickedButton8()
{
	type_is_draw = DISK;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(type_is_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

