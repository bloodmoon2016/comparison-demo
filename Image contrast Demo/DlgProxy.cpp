
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "Image contrast Demo.h"
#include "DlgProxy.h"
#include "Image contrast DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImagecontrastDemoDlgAutoProxy

IMPLEMENT_DYNCREATE(CImagecontrastDemoDlgAutoProxy, CCmdTarget)

CImagecontrastDemoDlgAutoProxy::CImagecontrastDemoDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CImagecontrastDemoDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CImagecontrastDemoDlg)))
		{
			m_pDialog = reinterpret_cast<CImagecontrastDemoDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CImagecontrastDemoDlgAutoProxy::~CImagecontrastDemoDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CImagecontrastDemoDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CImagecontrastDemoDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImagecontrastDemoDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IImagecontrastDemo 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {072139EB-DCE9-49BE-A510-D748DA0081F5}
static const IID IID_IImagecontrastDemo =
{ 0x72139EB, 0xDCE9, 0x49BE, { 0xA5, 0x10, 0xD7, 0x48, 0xDA, 0x0, 0x81, 0xF5 } };

BEGIN_INTERFACE_MAP(CImagecontrastDemoDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CImagecontrastDemoDlgAutoProxy, IID_IImagecontrastDemo, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {CD9729C6-53E9-459D-A876-96ED23ADD7CE}
IMPLEMENT_OLECREATE2(CImagecontrastDemoDlgAutoProxy, "ImagecontrastDemo.Application", 0xcd9729c6, 0x53e9, 0x459d, 0xa8, 0x76, 0x96, 0xed, 0x23, 0xad, 0xd7, 0xce)


// CImagecontrastDemoDlgAutoProxy 消息处理程序
