
// Image contrast DemoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

class CImagecontrastDemoDlgAutoProxy;


// CImagecontrastDemoDlg 对话框
class CImagecontrastDemoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImagecontrastDemoDlg);
	friend class CImagecontrastDemoDlgAutoProxy;

// 构造
public:
	CImagecontrastDemoDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CImagecontrastDemoDlg();

// 对话框数据
	enum { IDD = IDD_IMAGECONTRASTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CImagecontrastDemoDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	IplImage* TheImage;
	Mat img, img1;
	CString m_file_path;
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_edit_light;
	int m_edit_contrast;
	afx_msg void OnLightTest();
	afx_msg void OnExistTest();
	CSliderCtrl m_light;
	CSliderCtrl m_contrast;
	CListCtrl m_list_results;
	afx_msg void ResizeImage(IplImage* img);
	afx_msg void ShowImage(IplImage* img, UINT ID);
	afx_msg void setContrastBrightness(double percentB, double percentC, Mat& img, Mat& result);
	afx_msg void SharpenKernel(const Mat &image, Mat &result);
	string pHashValue(Mat &src);
	int HanmingDistance(string &str1, string &str2);
	CString mlines;
	CString mlinee;
	CString mcolumns;
	CString mcolumne;
};
