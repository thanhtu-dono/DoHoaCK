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
	obj_draw = 0;
	Led_Type = WIRE;
	Type_Affine = ROTATE;
	Type_Shadow = SMOOTH;
	TypeCoordinateView = Y_VIEW;

	IDC_Draw_Type = IDC_RADIO2;
	IDC_Type_Affine = IDC_RADIO4;
	IDC_Type_Shadow = IDC_RADIO7;
	IDC_Coordinate_View = IDC_RADIO10;

	IDC_SizeX = 50;
	IDC_SizeY = 50;
	IDC_SizeZ = 90;
	IDC_NearZ = 1;
	IDC_FarZ = 80;

	IDC_Ambient_Red = 1;
	IDC_Ambient_Green = 1;
	IDC_Ambient_Blue = 1;

	IDC_Diff_use_Red = 5;
	IDC_Diff_use_Green = 5;
	IDC_Diff_use_Blue = 5;

	IDC_Specular_Red = 10;
	IDC_Specular_Green = 10;
	IDC_Specular_Blue = 10;

	IDC_Speed_Rotate = 5.0;

	IDC_Axis_X = 0.0;
	IDC_Axis_Y = 0.0;
	IDC_Axis_Z = 1.0;

	xEye = 20.0;
	yEye = 20.0;

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
	m_VSliderBarFovy.SetPos(IDC_SizeZ);
	m_VSliderBarzNear.SetPos(IDC_NearZ);
	m_VSliderBarzFar.SetPos(IDC_FarZ);

	m_AmbientRed.SetPos(IDC_Ambient_Red);
	m_AmbientGreen.SetPos(IDC_Ambient_Green);
	m_AmbientBlue.SetPos(IDC_Ambient_Blue);

	m_DiffuseRed.SetPos(IDC_Diff_use_Red);
	m_DiffuseGreen.SetPos(IDC_Diff_use_Green);
	m_DiffuseBlue.SetPos(IDC_Diff_use_Blue);

	m_SpecularRed.SetPos(IDC_Specular_Red);
	m_SpecularGreen.SetPos(IDC_Specular_Green);
	m_SpecularBlue.SetPos(IDC_Specular_Blue);

	m_VSliderBarSpeedRotate.SetPos(IDC_Speed_Rotate);

	m_VSliderBarAxisX.SetPos(IDC_Axis_X);
	m_VSliderBarAxis_Y.SetPos(IDC_Axis_Y);
	m_VSliderBarAxisZ.SetPos(IDC_Axis_Z);

	m_EditControlzNear.SetWindowTextW(convert_int_to_CString(IDC_NearZ));
	m_EditControlSizeX.SetWindowTextW(convert_int_to_CString(IDC_SizeX));
	m_EditControlSizeY.SetWindowTextW(convert_int_to_CString(IDC_SizeY));
	m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
	m_EditControlzFar.SetWindowTextW(convert_int_to_CString(IDC_FarZ));
	m_EditControlSpeedRotate.SetWindowTextW(convert_int_to_CString(IDC_Speed_Rotate));
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
	CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
	pButton10->SetCheck(true);

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
	switch (IDC_Coordinate_View)
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
	obj_draw = 0;
	Led_Type = WIRE;
	Type_Affine = ROTATE;
	Type_Shadow = SMOOTH;
	TypeCoordinateView = Y_VIEW;

	IDC_Draw_Type = IDC_RADIO2;
	IDC_Type_Affine = IDC_RADIO4;
	IDC_Type_Shadow = IDC_RADIO7;
	IDC_Coordinate_View = IDC_RADIO10;

	IDC_SizeX = 50;
	IDC_SizeY = 50;
	IDC_SizeZ = 90;
	IDC_NearZ = 1;
	IDC_FarZ = 80;

	IDC_Ambient_Red = 1;
	IDC_Ambient_Green = 1;
	IDC_Ambient_Blue = 1;

	IDC_Diff_use_Red = 5;
	IDC_Diff_use_Green = 5;
	IDC_Diff_use_Blue = 5;

	IDC_Specular_Red = 10;
	IDC_Specular_Green = 10;
	IDC_Specular_Blue = 10;

	IDC_Speed_Rotate = 5.0;

	IDC_Axis_X = 0.0;
	IDC_Axis_Y = 0.0;
	IDC_Axis_Z = 1.0;

	xEye = 20.0;
	yEye = 20.0;


	m_EditControlzNear.SetWindowTextW(convert_int_to_CString(IDC_NearZ));
	m_EditControlSizeX.SetWindowTextW(convert_int_to_CString(IDC_SizeX));
	m_EditControlSizeY.SetWindowTextW(convert_int_to_CString(IDC_SizeY));
	m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
	m_EditControlzFar.SetWindowTextW(convert_int_to_CString(IDC_FarZ));
	m_EditControlSpeedRotate.SetWindowTextW(convert_int_to_CString(IDC_Speed_Rotate));
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
	CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
	pButton10->SetCheck(true);
	CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
	pButton9->SetCheck(false);
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

void FormViewBar::type_shape()
{
	if (GetAppView())
	{
		GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_NearZ, IDC_FarZ, IDC_SizeZ);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::set_ambient()
{
	if (GetAppView())
	{
		GetAppView()->set_ambient_rgb(IDC_Ambient_Red, IDC_Ambient_Green, IDC_Ambient_Blue);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::set_diff_use()
{
	if (GetAppView())
	{
		GetAppView()->set_diff_use_rgb(IDC_Diff_use_Red, IDC_Diff_use_Green, IDC_Diff_use_Blue);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::set_specular()
{
	if (GetAppView())
	{
		GetAppView()->set_specular_rgb(IDC_Specular_Red, IDC_Specular_Green, IDC_Specular_Blue);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::set_speedrotate()
{
	if (GetAppView())
	{
		GetAppView()->set_speed_rotate(IDC_Speed_Rotate);
		GetAppView()->Invalidate(FALSE);
	}
}

void FormViewBar::set_axisrotate()
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
	obj_draw = CUBE;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

void FormViewBar::OnBnClickedDrawTeapot()
{
	obj_draw = TEAPOT;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton1()
{
	obj_draw = SPHERE;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton2()
{
	obj_draw = CONE;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton3()
{
	obj_draw = CYLINDER;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedButton4()
{
	obj_draw = TORUS;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio1()
{
	Led_Type = POINTS;
	IDC_Draw_Type = IDC_RADIO1;
	if (GetAppView())
	{
		GetAppView()->set_draw_type(Led_Type);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio2()
{
	Led_Type = WIRE;
	IDC_Draw_Type = IDC_RADIO2;
	if (GetAppView())
	{
		GetAppView()->set_draw_type(Led_Type);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio3()
{
	Led_Type = SOLID;
	IDC_Draw_Type = IDC_RADIO3;
	if (GetAppView())
	{
		GetAppView()->set_draw_type(Led_Type);;
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

void FormViewBar::OnBnClickedRadio4()
{
	Type_Affine = ROTATE;
	IDC_Type_Affine = IDC_RADIO4;
	if (GetAppView())
	{
		GetAppView()->set_affine_type(Type_Affine);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio5()
{
	Type_Affine = TRANSLATE;
	IDC_Type_Affine = IDC_RADIO5;
	if (GetAppView())
	{
		GetAppView()->set_affine_type(Type_Affine);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio6()
{
	Type_Affine = SCALE;
	IDC_Type_Affine = IDC_RADIO6;
	if (GetAppView())
	{
		GetAppView()->set_affine_type(Type_Affine);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

void FormViewBar::OnBnClickedRadio7()
{
	Type_Shadow = SMOOTH;
	IDC_Type_Shadow = IDC_RADIO7;
	if (GetAppView())
	{
		GetAppView()->set_shadow_type(Type_Shadow);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio8()
{
	Type_Shadow = FLAT;
	IDC_Type_Shadow = IDC_RADIO8;
	if (GetAppView())
	{
		GetAppView()->set_shadow_type(Type_Shadow);
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
	TypeCoordinateView = X_VIEW;
	IDC_Coordinate_View = IDC_RADIO9;
	if (GetAppView())
	{
		GetAppView()->set_coordinate_view(TypeCoordinateView);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio10()
{
	TypeCoordinateView = Y_VIEW;
	IDC_Coordinate_View = IDC_RADIO10;
	if (GetAppView())
	{
		GetAppView()->set_coordinate_view(TypeCoordinateView);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}
void FormViewBar::OnBnClickedRadio11()
{
	TypeCoordinateView = Z_VIEW;
	IDC_Coordinate_View = IDC_RADIO11;
	if (GetAppView())
	{
		GetAppView()->set_coordinate_view(TypeCoordinateView);
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
			IDC_SizeZ++;
			if (IDC_SizeZ > 180)
			{
				IDC_SizeZ = 180;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_NearZ, IDC_FarZ, IDC_SizeZ);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_SizeZ);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
			break;
		}
		case VK_OEM_MINUS:
		{
			IDC_SizeZ++;
			if (IDC_SizeZ > 180)
			{
				IDC_SizeZ = 180;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_NearZ, IDC_FarZ, IDC_SizeZ);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_SizeZ);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
			break;
		}
		case VK_OEM_PLUS:
		{
			IDC_SizeZ--;
			if (IDC_SizeZ < 0)
			{
				IDC_SizeZ = 0;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_NearZ, IDC_FarZ, IDC_SizeZ);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_SizeZ);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
			break;
		}
		case VK_ADD:
		{
			IDC_SizeZ--;
			if (IDC_SizeZ < 0)
			{
				IDC_SizeZ = 0;
			}
			if (GetAppView())
			{
				GetAppView()->set_size_perspective(IDC_SizeX, IDC_SizeY, IDC_NearZ, IDC_FarZ, IDC_SizeZ);
				GetAppView()->Invalidate(FALSE);
			}
			m_VSliderBarFovy.SetPos(IDC_SizeZ);
			m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
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
			xEye--;
			{
				GetAppView()->set_point_eye(xEye, yEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_RIGHT:
		{
			xEye++;
			{
				GetAppView()->set_point_eye(xEye, yEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_UP:
		{
			yEye++;
			{
				GetAppView()->set_point_eye(xEye, yEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case VK_DOWN:
		{
			yEye--;
			{
				GetAppView()->set_point_eye(xEye, yEye);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case 0x58:
		{
			TypeCoordinateView = X_VIEW;
			IDC_Coordinate_View = IDC_RADIO9;
			CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
			pButton9->SetCheck(true);
			CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
			pButton10->SetCheck(false);
			CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
			pButton11->SetCheck(false);
			if (GetAppView())
			{
				GetAppView()->set_coordinate_view(TypeCoordinateView);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case 0x59:
		{
			TypeCoordinateView = Y_VIEW;
			IDC_Coordinate_View = IDC_RADIO10;
			CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
			pButton9->SetCheck(false);
			CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
			pButton10->SetCheck(true);
			CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
			pButton11->SetCheck(false);
			if (GetAppView())
			{
				GetAppView()->set_coordinate_view(TypeCoordinateView);
				GetAppView()->Invalidate(FALSE);
			}
			break;
		}
		case 0x5A:
		{
			TypeCoordinateView = Z_VIEW;
			IDC_Coordinate_View = IDC_RADIO11;
			CButton* pButton9 = (CButton*)GetDlgItem(IDC_RADIO9);
			pButton9->SetCheck(false);
			CButton* pButton10 = (CButton*)GetDlgItem(IDC_RADIO10);
			pButton10->SetCheck(false);
			CButton* pButton11 = (CButton*)GetDlgItem(IDC_RADIO11);
			pButton11->SetCheck(true);
			if (GetAppView())
			{
				GetAppView()->set_coordinate_view(TypeCoordinateView);
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
		FormViewBar::type_shape();
		break;
	}
	case IDC_SLIDER2:
	{
		IDC_SizeY = m_VSliderBarY.GetPos();
		m_EditControlSizeY.SetWindowTextW(convert_int_to_CString(IDC_SizeY));
		FormViewBar::type_shape();
		break;
	}
	case IDC_SLIDER3:
	{
		IDC_SizeZ = m_VSliderBarFovy.GetPos();
		m_EditControlFovy.SetWindowTextW(convert_int_to_CString(IDC_SizeZ));
		FormViewBar::type_shape();
		break;
	}
	case IDC_SLIDER4:
	{
		IDC_NearZ = m_VSliderBarzNear.GetPos();
		m_EditControlzNear.SetWindowTextW(convert_int_to_CString(IDC_NearZ));
		FormViewBar::type_shape();
		break;
	}
	case IDC_SLIDER5:
	{
		IDC_FarZ = m_VSliderBarzFar.GetPos();
		m_EditControlzFar.SetWindowTextW(convert_int_to_CString(IDC_FarZ));
		FormViewBar::type_shape();
		break;
	}
	case IDC_SLIDER6:
	{
		IDC_Ambient_Red = m_AmbientRed.GetPos();
		FormViewBar::set_ambient();
		break;
	}
	case IDC_SLIDER7:
	{
		IDC_Ambient_Green = m_AmbientGreen.GetPos();
		FormViewBar::set_ambient();
		break;
	}
	case IDC_SLIDER8:
	{
		IDC_Ambient_Blue = m_AmbientBlue.GetPos();
		FormViewBar::set_ambient();
		break;
	}
	case IDC_SLIDER9:
	{
		IDC_Diff_use_Red = m_DiffuseRed.GetPos();
		FormViewBar::set_diff_use();
		break;
	}
	case IDC_SLIDER10:
	{
		IDC_Diff_use_Green = m_DiffuseGreen.GetPos();
		FormViewBar::set_diff_use();
		break;
	}
	case IDC_SLIDER11:
	{
		IDC_Diff_use_Blue = m_DiffuseBlue.GetPos();
		FormViewBar::set_diff_use();
		break;
	}
	case IDC_SLIDER12:
	{
		IDC_Specular_Red = m_SpecularRed.GetPos();
		FormViewBar::set_specular();
		break;
	}
	case IDC_SLIDER13:
	{
		IDC_Specular_Green = m_SpecularGreen.GetPos();
		FormViewBar::set_specular();
		break;
	}
	case IDC_SLIDER14:
	{
		IDC_Specular_Blue = m_SpecularBlue.GetPos();
		FormViewBar::set_specular();
		break;
	}
	case IDC_SLIDER15:
	{
		IDC_Speed_Rotate = m_VSliderBarSpeedRotate.GetPos();
		m_EditControlSpeedRotate.SetWindowTextW(convert_int_to_CString(IDC_Speed_Rotate));
		FormViewBar::set_speedrotate();
		break;
	}
	case IDC_SLIDER16:
	{
		IDC_Axis_X = m_VSliderBarAxisX.GetPos();
		m_EditControlAxisX.SetWindowTextW(convert_int_to_CString(IDC_Axis_X));
		FormViewBar::set_axisrotate();
		break;
	}
	case IDC_SLIDER17:
	{
		IDC_Axis_Y = m_VSliderBarAxis_Y.GetPos();
		m_EditControlAxisY.SetWindowTextW(convert_int_to_CString(IDC_Axis_Y));
		FormViewBar::set_axisrotate();
		break;
	}
	case IDC_SLIDER18:
	{
		IDC_Axis_Z = m_VSliderBarAxisZ.GetPos();
		m_EditControlAxisZ.SetWindowTextW(convert_int_to_CString(IDC_Axis_Z));
		FormViewBar::set_axisrotate();
		break;
	}
	default:
		break;
	}
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}




void FormViewBar::OnBnClickedButton9()
{
	obj_draw = PYRAMID;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}


void FormViewBar::OnBnClickedButton10()
{
	obj_draw = OCTAGON;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}


void FormViewBar::OnBnClickedButton8()
{
	obj_draw = DISK;
	if (GetAppView())
	{
		GetAppView()->set_draw_cicurlar(obj_draw);
		GetAppView()->Invalidate(FALSE);
	}
	// TODO: Add your control notification handler code here
}

