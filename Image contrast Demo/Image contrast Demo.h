
// Image contrast Demo.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
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
// 有关此类的实现，请参阅 Image contrast Demo.cpp
//

class CImagecontrastDemoApp : public CWinApp
{
public:
	CImagecontrastDemoApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CImagecontrastDemoApp theApp;