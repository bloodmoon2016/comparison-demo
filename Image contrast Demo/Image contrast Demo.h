
// Image contrast Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "stdlib.h"
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
#include "opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "string.h"
#include <iostream>
#include "cxcore.h"
#include "time.h"

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256
#define IMAGE_CHANNELS 3

using namespace cv;
using namespace std;

// CImagecontrastDemoApp: 
// �йش����ʵ�֣������ Image contrast Demo.cpp
//

class CImagecontrastDemoApp : public CWinApp
{
public:
	CImagecontrastDemoApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CImagecontrastDemoApp theApp;