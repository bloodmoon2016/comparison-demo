
// Image contrast DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Image contrast Demo.h"
#include "Image contrast DemoDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImagecontrastDemoDlg 对话框


IMPLEMENT_DYNAMIC(CImagecontrastDemoDlg, CDialogEx);

CImagecontrastDemoDlg::CImagecontrastDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImagecontrastDemoDlg::IDD, pParent)
	, m_file_path(_T(""))
	, m_edit_light(0)
	, m_edit_contrast(0)
	, mlines(_T(""))
	, mlinee(_T(""))
	, mcolumns(_T(""))
	, mcolumne(_T(""))
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CImagecontrastDemoDlg::~CImagecontrastDemoDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CImagecontrastDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_PATH, m_file_path);
	DDX_Text(pDX, IDC_EDIT_LIGHT, m_edit_light);
	DDV_MinMaxInt(pDX, m_edit_light, 0, 100);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_edit_contrast);
	DDV_MinMaxInt(pDX, m_edit_contrast, 0, 100);
	DDX_Control(pDX, IDC_SLIDER_LIGHT, m_light);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_contrast);
	DDX_Control(pDX, IDC_LIST_RESULTS, m_list_results);
	DDX_Text(pDX, IDC_LINE_S, mlines);
	DDX_Text(pDX, IDC_LINE_E, mlinee);
	DDX_Text(pDX, IDC_COLUMN_S, mcolumns);
	DDX_Text(pDX, IDC_COLUMN_E, mcolumne);
}

BEGIN_MESSAGE_MAP(CImagecontrastDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_File_Open, &CImagecontrastDemoDlg::OnFileOpen)
	ON_BN_CLICKED(IDC_FILE_SAVE_AS, &CImagecontrastDemoDlg::OnFileSaveAs)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_LIGHT_TEST, &CImagecontrastDemoDlg::OnLightTest)
	ON_BN_CLICKED(IDC_EXIST_TEST, &CImagecontrastDemoDlg::OnExistTest)
END_MESSAGE_MAP()


// CImagecontrastDemoDlg 消息处理程序

BOOL CImagecontrastDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码
	CvSize ImgSize;
	ImgSize.height = IMAGE_HEIGHT;
	ImgSize.width = IMAGE_WIDTH;
	TheImage = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);

	m_light.SetRange(0, 100);//设置滑动范围
	m_light.SetTicFreq(1);//每10个单位画一刻度
	m_light.SetPageSize(1);
	m_light.SetPos(50);

	m_contrast.SetRange(0, 100);//设置滑动范围
	m_contrast.SetTicFreq(1);//每10个单位画一刻度
	m_contrast.SetPageSize(1);
	m_contrast.SetPos(50);

	m_edit_contrast = 50;
	m_edit_light = 50;//取得当前位置值	
	UpdateData(FALSE); //刷新edit控件

	m_list_results.DeleteAllItems();
	m_list_results.InsertColumn(0, _T("测试时间"));
	m_list_results.InsertColumn(1, _T("测试结果"));
	m_list_results.SetColumnWidth(0, 150);
	m_list_results.SetColumnWidth(1, 350);
	m_list_results.SetRedraw(FALSE);

	m_list_results.SetRedraw(TRUE);//显示

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImagecontrastDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImagecontrastDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();                // 重绘对话框

		CDialogEx::UpdateWindow();                // 更新windows窗口，如果无这步调用，图片显示还会出现问题
		ShowImage(TheImage, IDC_PIC);    // 重绘图片函数
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImagecontrastDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CImagecontrastDemoDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CImagecontrastDemoDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CImagecontrastDemoDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CImagecontrastDemoDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CImagecontrastDemoDlg::OnFileOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog *dlg = new CFileDialog(
		TRUE, _T("*.bmp; *.JPG"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.JPG)|*.bmp; *.JPG| All Files (*.*) |*.*||"), NULL
		);                                        // 选项图片的约定
	dlg->m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	CString mPath, mFileName;

	if (dlg->DoModal() != IDOK)                    // 判断是否获得图片
		return;

	mPath = dlg->GetPathName();            // 获取图片路径
	mFileName = dlg->m_ofn.lpstrFileTitle;

	const size_t strsize = (mPath.GetLength() + 1) * 2;
	char *pfilePath = new char[strsize];
	size_t sz = 0;
	wcstombs_s(&sz, pfilePath, strsize, mPath, _TRUNCATE);

	IplImage* ipl = cvLoadImage(pfilePath);    // 读取图片、缓存到一个局部变量 ipl 中

	if (!ipl)                                    // 判断是否成功载入图片
		return;
	if (TheImage)                                // 对上一幅显示的图片数据清零
		cvZero(TheImage);

	ResizeImage(ipl);    // 对读入的图片进行缩放，使其宽或高最大值者刚好等于 256，再复制到 TheImage 中
	ShowImage(TheImage, IDC_PIC);            // 调用显示图片函数    
	cvReleaseImage(&ipl);                        // 释放 ipl 占用的内存
	delete dlg;

	img = imread(pfilePath, IMREAD_COLOR);

	m_file_path.Empty();
	m_file_path += mPath;
	UpdateData(FALSE);

	m_light.SetPos(50);
	m_contrast.SetPos(50);
	m_edit_contrast = 50;
	m_edit_light = 50;//取得当前位置值	
	UpdateData(FALSE); //刷新edit控件
}


void CImagecontrastDemoDlg::OnFileSaveAs()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog *dlg = new CFileDialog(
		FALSE, _T("*.bmp; *.JPG"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("保存为(*.bmp;*.JPG)|*.bmp;*.JPG|所有文件(*.*)|*.*||"), NULL
		);
	CString strPath("");

	if (dlg->DoModal() == IDOK)
	{
		strPath = dlg->GetPathName();
		const size_t strsize = (strPath.GetLength() + 1) * 2;
		char *pfilePath = new char[strsize];
		size_t sz = 0;
		wcstombs_s(&sz, pfilePath, strsize, strPath, _TRUNCATE);
		cvSaveImage(pfilePath, TheImage);
	}
	delete dlg;
}


void CImagecontrastDemoDlg::ResizeImage(IplImage* img)
{
	// 读取图片的宽和高
	int w = img->width;
	int h = img->height;

	// 找出宽和高中的较大值者
	int max = (w > h) ? w : h;

	// 计算将图片缩放到TheImage区域所需的比例因子
	float scale = (float)((float)max / 256.0f);

	// 缩放后图片的宽和高
	int nw = (int)(w / scale);
	int nh = (int)(h / scale);

	// 为了将缩放后的图片存入 TheImage 的正中部位，需计算图片在 TheImage 左上角的期望坐标值
	int tlx = (nw > nh) ? 0 : (int)(256 - nw) / 2;
	int tly = (nw > nh) ? (int)(256 - nh) / 2 : 0;

	// 设置 TheImage 的 ROI 区域，用来存入图片 img
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// 对图片 img 进行缩放，并存入到 TheImage 中
	cvResize(img, TheImage);

	// 重置 TheImage 的 ROI 准备读入下一幅图片
	cvResetImageROI(TheImage);
}

void CImagecontrastDemoDlg::ShowImage(IplImage* img, UINT ID)    // ID 是Picture Control控件的ID号
{
	CDC* pDC = GetDlgItem(ID)->GetDC();        // 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();                // 获取 HDC(设备句柄) 来进行绘图操作

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;            // 求出图片控件的宽和高
	int rh = rect.bottom - rect.top;
	int iw = img->width;                        // 读取图片的宽和高
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                    // 使图片的显示位置正好在控件的正中
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);                            // 复制图片
	cimg.DrawToHDC(hDC, &rect);                // 将图片绘制到显示控件的指定区域内

	ReleaseDC(pDC);
}

void CImagecontrastDemoDlg::setContrastBrightness(double percentB, double percentC, Mat& img, Mat& result)
{
	const double pi = 3.1415926535898;

	//百分比转为调整系数，0~100  转为 -range~range，最大为[-1,1]
	const double Crange = 0.7;  //range越小，对比度调节的精度越高
	double C = (percentC - 50)* Crange / 50; //取值范围:[-range,range]
	const double Brange = 0.5;
	double B = (percentB - 50)* Brange / 50;

	double k = tan((45 + 44 * C) / 180 * pi);
	int channel = 0;
	int MAXGRAYVALUE = 0;
	int orgtype = img.type();
	switch (orgtype)
	{
	case CV_8UC1:
		channel = 1;
		MAXGRAYVALUE = 255;
		break;
	case CV_8UC3:
		channel = 3;
		MAXGRAYVALUE = 255;
		break;
	case CV_16UC1:
		channel = 1;
		MAXGRAYVALUE = 65535;
		break;
	default:
		MAXGRAYVALUE = 65535; break;
	}
	double threshold = MAXGRAYVALUE / 2;
	vector<Mat> mv(channel);
	Mat imgcyp;
	img.convertTo(imgcyp, CV_32F);
	split(imgcyp, mv);
	for (int i = 0; i < channel; i++)
	{
		mv[i] = (mv[i] - threshold * (1 - B)) * k + threshold * (1 + B);
	}
	merge(mv, result);

	result.convertTo(result, orgtype);
}

void CImagecontrastDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
	m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

	pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
	m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	
	UpdateData(FALSE); //刷新edit控件

	//刷新显示
	setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);

	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img1);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImagecontrastDemoDlg::SharpenKernel(const Mat &image, Mat &result)
{
	Mat kernel(3, 3, CV_32F, Scalar(0));
	kernel.at<float>(1, 1) = 5;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;
	filter2D(image, result, image.depth(), kernel);
	result.row(0).setTo(Scalar(0, 0, 0));
	result.row(result.rows - 1).setTo(Scalar(0, 0, 0));
	result.col(0).setTo(Scalar(0, 0, 0));
	result.col(result.cols - 1).setTo(Scalar(0, 0, 0));
}

string CImagecontrastDemoDlg::pHashValue(Mat &src)
{
	Mat imgg, dst;
	string rst(64, '\0');
	double dIdex[64];
	double mean = 0.0;
	int k = 0;
	if (src.channels() == 3)
	{
		cvtColor(src, src, CV_BGR2GRAY);
		imgg = Mat_<double>(src);
	}
	else
	{
		imgg = Mat_<double>(src);
	}

	/* 第一步，缩放尺寸*/
	resize(imgg, imgg, Size(8, 8));

	/* 第二步，离散余弦变换，DCT系数求取*/
	dct(imgg, dst);

	/* 第三步，求取DCT系数均值（左上角8*8区块的DCT系数）*/
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j)
		{
			dIdex[k] = dst.at<double>(i, j);
			mean += dst.at<double>(i, j) / 64;
			++k;
		}
	}

	/* 第四步，计算哈希值。*/
	for (int i = 0; i < 64; ++i)
	{
		if (dIdex[i] >= mean)
		{
			rst[i] = '1';
		}
		else
		{
			rst[i] = '0';
		}
	}
	return rst;
}

int CImagecontrastDemoDlg::HanmingDistance(string &str1, string &str2)
{
	if ((str1.size() != 64) || (str2.size() != 64))
		return -1;
	int difference = 0;
	for (int i = 0; i < 64; i++)
	{
		if (str1[i] != str2[i])
			difference++;
	}
	return difference;
}

void CImagecontrastDemoDlg::OnLightTest()
{
	// TODO:  在此添加控件通知处理程序代码
	cv::Mat	 img3, img4, img5, img6, img7, img8;
	IplImage *ipl_img = NULL;
	cv::Mat srcc = imread("F:\\show image\\img-06.JPG",1);
	
	GetDlgItem(IDC_LINE_S)->GetWindowText(mlines);
	GetDlgItem(IDC_LINE_E)->GetWindowText(mlinee);
	GetDlgItem(IDC_COLUMN_S)->GetWindowText(mcolumns);
	GetDlgItem(IDC_COLUMN_E)->GetWindowText(mcolumne);

	int m_lines = _ttoi(mlines);
	int m_linee = _ttoi(mlinee);
	int m_columns = _ttoi(mcolumns);
	int m_columne = _ttoi(mcolumne);

	Scalar     mean;
	Scalar     stddev;

	cv::meanStdDev(srcc, mean, stddev);
	uchar       mean_pxl = mean.val[0];
	uchar       stddev_pxl = stddev.val[0];

	cv::Mat  area_standard, area_test;
	area_standard = srcc;

	while (1){
		cv::Mat img_adj = cv::cvarrToMat(TheImage);
		cv::meanStdDev(img_adj, mean, stddev);
		uchar       mean_pxl_adj = mean.val[0];
		if (abs(mean_pxl_adj - mean_pxl) < 2) break;
		else {
			CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
			m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	

			if (mean_pxl_adj - mean_pxl < 0)
			{
				m_edit_light++;
				m_light.SetPos(m_edit_light);
			}
			else{
				m_edit_light--;
				m_light.SetPos(m_edit_light);
			}
			UpdateData(FALSE); //刷新edit控件
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);

			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}
	while (1){
		cv::Mat img_adj = cv::cvarrToMat(TheImage);
		cv::meanStdDev(img_adj, mean, stddev);
		uchar       stddev_pxl_adj = stddev.val[0];
		if (abs(stddev_pxl_adj - stddev_pxl) < 2) break;
		else {
			CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
			m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	

			if (stddev_pxl_adj - stddev_pxl < 0)
			{
				m_edit_contrast++;
				m_contrast.SetPos(m_edit_contrast);
			}
			else{
				m_edit_contrast--;
				m_contrast.SetPos(m_edit_contrast);
			}
			UpdateData(FALSE); //刷新edit控件
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);
			ipl_img = NULL;
			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}

	img3 = cv::cvarrToMat(TheImage);
	medianBlur(img3, img4, 3);//中值滤波

	blur(img4, img5, Size(3, 3), Point(-1, -1)); //均值滤波

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img5);
	ResizeImage(ipl_img);

	IplImage *gray = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);  //直方图均衡化
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvEqualizeHist(gray, ipl_img);
	cvCvtColor(ipl_img, TheImage, CV_GRAY2BGR);
	cvReleaseImage(&gray);

	img6 = cv::cvarrToMat(TheImage);    //锐化
	Mat kernela(3, 3, CV_32F, Scalar(0));
	kernela.at<float>(1, 1) = 5.0;
	kernela.at<float>(0, 1) = -1.0;
	kernela.at<float>(2, 1) = -1.0;
	kernela.at<float>(1, 0) = -1.0;
	kernela.at<float>(1, 2) = -1.0;
	SharpenKernel(img6, img7);

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img7);
	ResizeImage(ipl_img);

	area_test = cv::cvarrToMat(TheImage);

	Scalar     mean_test;
	Scalar     stddev_test;
	Scalar     mean_standard;
	Scalar     stddev_standard;

	cv::Mat area_test_1 = area_test(Range(m_lines, m_linee), Range(m_columns, m_columne));//灯（115，140）（80，140）
	cv::Mat area_standard_1 = area_standard(Range(m_lines, m_linee), Range(m_columns, m_columne));
	cv::rectangle(area_test, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);//(左顶点列，左顶点行，长，宽，颜色，粗细，坐标点小数点后位数)
	cv::rectangle(area_standard, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);

	cv::meanStdDev(area_test_1, mean_test, stddev_test);
	uchar       mean_pxl_test = mean_test.val[0];
	uchar       stddev_pxl_test = stddev_test.val[0];

	cv::meanStdDev(area_standard_1, mean_standard, stddev_standard);
	uchar       mean_pxl_standard = mean_standard.val[0];
	uchar       stddev_pxl_standard = stddev_standard.val[0];

	if (abs(mean_pxl_test - mean_pxl_standard) > 3) {
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("指示灯熄灭"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("指示灯正常"));
		m_list_results.SetRedraw(TRUE);//显示
	}

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(area_test);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}


void CImagecontrastDemoDlg::OnExistTest()
{
	// TODO:  在此添加控件通知处理程序代码
	cv::Mat	 img3, img4, img5, img6, img7, img8;
	IplImage *ipl_img = NULL;


	GetDlgItem(IDC_LINE_S)->GetWindowText(mlines);
	GetDlgItem(IDC_LINE_E)->GetWindowText(mlinee);
	GetDlgItem(IDC_COLUMN_S)->GetWindowText(mcolumns);
	GetDlgItem(IDC_COLUMN_E)->GetWindowText(mcolumne);

	int m_lines = _ttoi(mlines);
	int m_linee = _ttoi(mlinee);
	int m_columns = _ttoi(mcolumns);
	int m_columne = _ttoi(mcolumne);

	

	img3 = cv::cvarrToMat(TheImage);
	medianBlur(img3, img4, 3);//中值滤波

	blur(img4, img5, Size(3, 3), Point(-1, -1)); //均值滤波

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img5);
	ResizeImage(ipl_img);

	IplImage *gray = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);  //直方图均衡化
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvEqualizeHist(gray, ipl_img);
	cvCvtColor(ipl_img, TheImage, CV_GRAY2BGR);
	cvReleaseImage(&gray);

	img6 = cv::cvarrToMat(TheImage);    //锐化
	Mat kernela(3, 3, CV_32F, Scalar(0));
	kernela.at<float>(1, 1) = 5.0;
	kernela.at<float>(0, 1) = -1.0;
	kernela.at<float>(2, 1) = -1.0;
	kernela.at<float>(1, 0) = -1.0;
	kernela.at<float>(1, 2) = -1.0;
	SharpenKernel(img6, img7);

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img7);
	ResizeImage(ipl_img);

	cv::Mat srcc = imread("F:\\show image\\img-05.JPG", 1);

	Scalar     mean;
	Scalar     stddev;

	cv::meanStdDev(srcc, mean, stddev);
	uchar       mean_pxl = mean.val[0];
	uchar       stddev_pxl = stddev.val[0];

	while (1){
		cv::Mat img_adj = cv::cvarrToMat(TheImage);
		cv::meanStdDev(img_adj, mean, stddev);
		uchar       mean_pxl_adj = mean.val[0];
		if (abs(mean_pxl_adj - mean_pxl) < 2) break;
		else {
			CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
			m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	

			if (mean_pxl_adj - mean_pxl < 0)
			{
				m_edit_light++;
				m_light.SetPos(m_edit_light);
			}
			else{
				m_edit_light--;
				m_light.SetPos(m_edit_light);
			}
			UpdateData(FALSE); //刷新edit控件
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);

			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}
	while (1){
		cv::Mat img_adj = cv::cvarrToMat(TheImage);
		cv::meanStdDev(img_adj, mean, stddev);
		uchar       stddev_pxl_adj = stddev.val[0];
		if (abs(stddev_pxl_adj - stddev_pxl) < 2) break;
		else {
			CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
			m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	

			if (stddev_pxl_adj - stddev_pxl < 0)
			{
				m_edit_contrast++;
				m_contrast.SetPos(m_edit_contrast);
			}
			else{
				m_edit_contrast--;
				m_contrast.SetPos(m_edit_contrast);
			}
			UpdateData(FALSE); //刷新edit控件
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);
			ipl_img = NULL;
			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}

	cv::Mat  area_standard, area_test;
	area_standard = srcc;
	area_test = cv::cvarrToMat(TheImage);

	cv::Mat area_test_1 = area_test(Range(m_lines, m_linee), Range(m_columns, m_columne));//水瓶嘴(90,130)(45,80)   盒子（30，150）（80，170）
	cv::Mat area_standard_1 = area_standard(Range(m_lines, m_linee), Range(m_columns, m_columne));
	cv::rectangle(area_test, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);//(左顶点列，左顶点行，长，宽，颜色，粗细，坐标点小数点后位数)
	cv::rectangle(area_standard, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);

	string hash_1 = pHashValue(area_test_1);
	string hash_2 = pHashValue(area_standard_1);

	int Hamming = HanmingDistance(hash_1, hash_2);

	if (Hamming > 10) {
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("部件缺失"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("部件完好"));
		m_list_results.SetRedraw(TRUE);//显示
	}

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(area_test);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}
