// ScaleDlg.cpp : implementation file
//

#include "pch.h"
#include "DoAn3D.h"
#include "ScaleDlg.h"
#include "afxdialogex.h"


// ScaleDlg dialog

IMPLEMENT_DYNAMIC(ScaleDlg, CDialogEx)

ScaleDlg::ScaleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	scaleValueX = 1;
	scaleValueY = 1;
	scaleValueZ = 1;
}

ScaleDlg::~ScaleDlg()
{
}

//BOOL ScaleDlg::OnInitDialog()
//{
//	return 0;
//}

BOOL ScaleDlg::OnInitDialog()
{
	BOOL ret = CDialogEx::OnInitDialog();
	valueX.SetWindowText(_T("1"));
	valueY.SetWindowText(_T("1"));
	valueZ.SetWindowText(_T("1"));
	UpdateData(FALSE);
	return ret;
}

void ScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, decrX);
	DDX_Control(pDX, IDC_BUTTON3, decrY);
	DDX_Control(pDX, IDC_BUTTON4, decrZ);
	DDX_Control(pDX, IDC_BUTTON1, icrX);
	DDX_Control(pDX, IDC_BUTTON5, incY);
	DDX_Control(pDX, IDC_BUTTON6, icrZ);
	DDX_Control(pDX, IDC_EDIT1, valueX);
	DDX_Control(pDX, IDC_EDIT2, valueY);
	DDX_Control(pDX, IDC_EDIT3, valueZ);
}


BEGIN_MESSAGE_MAP(ScaleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &ScaleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &ScaleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &ScaleDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &ScaleDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &ScaleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &ScaleDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// ScaleDlg message handlers


void ScaleDlg::OnBnClickedButton2()

{
	// TODO: Add your control notification handler code here
	CString currentval;
	valueX.GetWindowText(currentval);
	scaleValueX = _tstof(currentval);
	scaleValueX -= 0.5;
	CString strval;
	strval.Format(_T("%f"), scaleValueX);
	valueX.SetWindowText(strval);
	UpdateData(FALSE);
}


void ScaleDlg::OnBnClickedButton1()

{
	// TODO: Add your control notification handler code here
	CString currentval;
	valueX.GetWindowText(currentval);
	scaleValueX = _tstof(currentval);
	scaleValueX += 0.5;
	CString strval;
	strval.Format(_T("%f"), scaleValueX);
	valueX.SetWindowText(strval);
	UpdateData(FALSE);
}


void ScaleDlg::OnBnClickedButton3()

{
	// TODO: Add your control notification handler code here
	CString currentval;
	valueY.GetWindowText(currentval);
	scaleValueY = _tstof(currentval);
	scaleValueY -= 0.5;
	CString strval;
	strval.Format(_T("%f"), scaleValueY);
	valueY.SetWindowText(strval);
	UpdateData(FALSE);
}


void ScaleDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	CString currentval;
	valueY.GetWindowText(currentval);
	scaleValueY = _tstof(currentval);
	scaleValueY += 0.5;
	CString strval;
	strval.Format(_T("%f"), scaleValueY);
	valueY.SetWindowText(strval);
	UpdateData(FALSE);
}


void ScaleDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString currentval;
	valueZ.GetWindowText(currentval);
	scaleValueZ = _tstof(currentval);
	scaleValueZ -= 0.5;
	CString strval;
	strval.Format(_T("%f"), scaleValueZ);
	valueZ.SetWindowText(strval);
	UpdateData(FALSE);
}


void ScaleDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	CString currentval;
	valueZ.GetWindowText(currentval);
	scaleValueZ = _tstof(currentval);
	scaleValueZ += 0.5;
	CString strval;
	strval.Format(_T("%f"), scaleValueZ);
	valueZ.SetWindowText(strval);
	UpdateData(FALSE);
}

float ScaleDlg::getvalueX()
{
	return scaleValueX;
}

float ScaleDlg::getvalueY()
{
	return scaleValueY;
}

float ScaleDlg::getvalueZ()
{
	return scaleValueZ;
}
