
// Image contrast DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image contrast Demo.h"
#include "Image contrast DemoDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CImagecontrastDemoDlg �Ի���


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
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
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


// CImagecontrastDemoDlg ��Ϣ�������

BOOL CImagecontrastDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CvSize ImgSize;
	ImgSize.height = IMAGE_HEIGHT;
	ImgSize.width = IMAGE_WIDTH;
	TheImage = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);

	m_light.SetRange(0, 100);//���û�����Χ
	m_light.SetTicFreq(1);//ÿ10����λ��һ�̶�
	m_light.SetPageSize(1);
	m_light.SetPos(50);

	m_contrast.SetRange(0, 100);//���û�����Χ
	m_contrast.SetTicFreq(1);//ÿ10����λ��һ�̶�
	m_contrast.SetPageSize(1);
	m_contrast.SetPos(50);

	m_edit_contrast = 50;
	m_edit_light = 50;//ȡ�õ�ǰλ��ֵ	
	UpdateData(FALSE); //ˢ��edit�ؼ�

	m_list_results.DeleteAllItems();
	m_list_results.InsertColumn(0, _T("����ʱ��"));
	m_list_results.InsertColumn(1, _T("���Խ��"));
	m_list_results.SetColumnWidth(0, 150);
	m_list_results.SetColumnWidth(1, 350);
	m_list_results.SetRedraw(FALSE);

	m_list_results.SetRedraw(TRUE);//��ʾ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CImagecontrastDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();                // �ػ�Ի���

		CDialogEx::UpdateWindow();                // ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
		ShowImage(TheImage, IDC_PIC);    // �ػ�ͼƬ����
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CImagecontrastDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

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
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CImagecontrastDemoDlg::OnFileOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog *dlg = new CFileDialog(
		TRUE, _T("*.bmp; *.JPG"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.JPG)|*.bmp; *.JPG| All Files (*.*) |*.*||"), NULL
		);                                        // ѡ��ͼƬ��Լ��
	dlg->m_ofn.lpstrTitle = _T("Open Image");    // ���ļ��Ի���ı�����
	CString mPath, mFileName;

	if (dlg->DoModal() != IDOK)                    // �ж��Ƿ���ͼƬ
		return;

	mPath = dlg->GetPathName();            // ��ȡͼƬ·��
	mFileName = dlg->m_ofn.lpstrFileTitle;

	const size_t strsize = (mPath.GetLength() + 1) * 2;
	char *pfilePath = new char[strsize];
	size_t sz = 0;
	wcstombs_s(&sz, pfilePath, strsize, mPath, _TRUNCATE);

	IplImage* ipl = cvLoadImage(pfilePath);    // ��ȡͼƬ�����浽һ���ֲ����� ipl ��

	if (!ipl)                                    // �ж��Ƿ�ɹ�����ͼƬ
		return;
	if (TheImage)                                // ����һ����ʾ��ͼƬ��������
		cvZero(TheImage);

	ResizeImage(ipl);    // �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
	ShowImage(TheImage, IDC_PIC);            // ������ʾͼƬ����    
	cvReleaseImage(&ipl);                        // �ͷ� ipl ռ�õ��ڴ�
	delete dlg;

	img = imread(pfilePath, IMREAD_COLOR);

	m_file_path.Empty();
	m_file_path += mPath;
	UpdateData(FALSE);

	m_light.SetPos(50);
	m_contrast.SetPos(50);
	m_edit_contrast = 50;
	m_edit_light = 50;//ȡ�õ�ǰλ��ֵ	
	UpdateData(FALSE); //ˢ��edit�ؼ�
}


void CImagecontrastDemoDlg::OnFileSaveAs()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog *dlg = new CFileDialog(
		FALSE, _T("*.bmp; *.JPG"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("����Ϊ(*.bmp;*.JPG)|*.bmp;*.JPG|�����ļ�(*.*)|*.*||"), NULL
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
	// ��ȡͼƬ�Ŀ�͸�
	int w = img->width;
	int h = img->height;

	// �ҳ���͸��еĽϴ�ֵ��
	int max = (w > h) ? w : h;

	// ���㽫ͼƬ���ŵ�TheImage��������ı�������
	float scale = (float)((float)max / 256.0f);

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)(w / scale);
	int nh = (int)(h / scale);

	// Ϊ�˽����ź��ͼƬ���� TheImage �����в�λ�������ͼƬ�� TheImage ���Ͻǵ���������ֵ
	int tlx = (nw > nh) ? 0 : (int)(256 - nw) / 2;
	int tly = (nw > nh) ? (int)(256 - nh) / 2 : 0;

	// ���� TheImage �� ROI ������������ͼƬ img
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// ��ͼƬ img �������ţ������뵽 TheImage ��
	cvResize(img, TheImage);

	// ���� TheImage �� ROI ׼��������һ��ͼƬ
	cvResetImageROI(TheImage);
}

void CImagecontrastDemoDlg::ShowImage(IplImage* img, UINT ID)    // ID ��Picture Control�ؼ���ID��
{
	CDC* pDC = GetDlgItem(ID)->GetDC();        // �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();                // ��ȡ HDC(�豸���) �����л�ͼ����

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;            // ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;
	int iw = img->width;                        // ��ȡͼƬ�Ŀ�͸�
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                    // ʹͼƬ����ʾλ�������ڿؼ�������
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);                            // ����ͼƬ
	cimg.DrawToHDC(hDC, &rect);                // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������

	ReleaseDC(pDC);
}

void CImagecontrastDemoDlg::setContrastBrightness(double percentB, double percentC, Mat& img, Mat& result)
{
	const double pi = 3.1415926535898;

	//�ٷֱ�תΪ����ϵ����0~100  תΪ -range~range�����Ϊ[-1,1]
	const double Crange = 0.7;  //rangeԽС���Աȶȵ��ڵľ���Խ��
	double C = (percentC - 50)* Crange / 50; //ȡֵ��Χ:[-range,range]
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
	m_edit_contrast = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ 

	pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
	m_edit_light = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ	
	UpdateData(FALSE); //ˢ��edit�ؼ�

	//ˢ����ʾ
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

	/* ��һ�������ųߴ�*/
	resize(imgg, imgg, Size(8, 8));

	/* �ڶ�������ɢ���ұ任��DCTϵ����ȡ*/
	dct(imgg, dst);

	/* ����������ȡDCTϵ����ֵ�����Ͻ�8*8�����DCTϵ����*/
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j)
		{
			dIdex[k] = dst.at<double>(i, j);
			mean += dst.at<double>(i, j) / 64;
			++k;
		}
	}

	/* ���Ĳ��������ϣֵ��*/
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			m_edit_contrast = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ	

			if (mean_pxl_adj - mean_pxl < 0)
			{
				m_edit_light++;
				m_light.SetPos(m_edit_light);
			}
			else{
				m_edit_light--;
				m_light.SetPos(m_edit_light);
			}
			UpdateData(FALSE); //ˢ��edit�ؼ�
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
			m_edit_contrast = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ	

			if (stddev_pxl_adj - stddev_pxl < 0)
			{
				m_edit_contrast++;
				m_contrast.SetPos(m_edit_contrast);
			}
			else{
				m_edit_contrast--;
				m_contrast.SetPos(m_edit_contrast);
			}
			UpdateData(FALSE); //ˢ��edit�ؼ�
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);
			ipl_img = NULL;
			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}

	img3 = cv::cvarrToMat(TheImage);
	medianBlur(img3, img4, 3);//��ֵ�˲�

	blur(img4, img5, Size(3, 3), Point(-1, -1)); //��ֵ�˲�

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img5);
	ResizeImage(ipl_img);

	IplImage *gray = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);  //ֱ��ͼ���⻯
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvEqualizeHist(gray, ipl_img);
	cvCvtColor(ipl_img, TheImage, CV_GRAY2BGR);
	cvReleaseImage(&gray);

	img6 = cv::cvarrToMat(TheImage);    //��
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

	cv::Mat area_test_1 = area_test(Range(m_lines, m_linee), Range(m_columns, m_columne));//�ƣ�115��140����80��140��
	cv::Mat area_standard_1 = area_standard(Range(m_lines, m_linee), Range(m_columns, m_columne));
	cv::rectangle(area_test, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);//(�󶥵��У��󶥵��У���������ɫ����ϸ�������С�����λ��)
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
		m_list_results.SetItemText(nIndex, 1, _T("ָʾ��Ϩ��"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("ָʾ������"));
		m_list_results.SetRedraw(TRUE);//��ʾ
	}

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(area_test);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}


void CImagecontrastDemoDlg::OnExistTest()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	medianBlur(img3, img4, 3);//��ֵ�˲�

	blur(img4, img5, Size(3, 3), Point(-1, -1)); //��ֵ�˲�

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img5);
	ResizeImage(ipl_img);

	IplImage *gray = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);  //ֱ��ͼ���⻯
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvEqualizeHist(gray, ipl_img);
	cvCvtColor(ipl_img, TheImage, CV_GRAY2BGR);
	cvReleaseImage(&gray);

	img6 = cv::cvarrToMat(TheImage);    //��
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
			m_edit_contrast = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ	

			if (mean_pxl_adj - mean_pxl < 0)
			{
				m_edit_light++;
				m_light.SetPos(m_edit_light);
			}
			else{
				m_edit_light--;
				m_light.SetPos(m_edit_light);
			}
			UpdateData(FALSE); //ˢ��edit�ؼ�
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
			m_edit_contrast = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ	

			if (stddev_pxl_adj - stddev_pxl < 0)
			{
				m_edit_contrast++;
				m_contrast.SetPos(m_edit_contrast);
			}
			else{
				m_edit_contrast--;
				m_contrast.SetPos(m_edit_contrast);
			}
			UpdateData(FALSE); //ˢ��edit�ؼ�
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

	cv::Mat area_test_1 = area_test(Range(m_lines, m_linee), Range(m_columns, m_columne));//ˮƿ��(90,130)(45,80)   ���ӣ�30��150����80��170��
	cv::Mat area_standard_1 = area_standard(Range(m_lines, m_linee), Range(m_columns, m_columne));
	cv::rectangle(area_test, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);//(�󶥵��У��󶥵��У���������ɫ����ϸ�������С�����λ��)
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
		m_list_results.SetItemText(nIndex, 1, _T("����ȱʧ"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("�������"));
		m_list_results.SetRedraw(TRUE);//��ʾ
	}

	ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(area_test);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}
