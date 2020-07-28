#pragma once


// ScaleDlg dialog

class ScaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDlg)

public:
	ScaleDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ScaleDlg();
	BOOL OnInitDialog();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton decrX;
	CButton decrY;
	CButton decrZ;
	CButton icrX;
	CButton incY;
	CButton icrZ;
	CEdit valueX;
	CEdit valueY;
	CEdit valueZ;
	float scaleValueX;
	float scaleValueY;
	float scaleValueZ;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg float getvalueX();
	afx_msg float getvalueY();
	afx_msg float getvalueZ();
};
