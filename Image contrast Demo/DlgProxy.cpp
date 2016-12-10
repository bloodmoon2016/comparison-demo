
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CImagecontrastDemoDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CImagecontrastDemoDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImagecontrastDemoDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IImagecontrastDemo ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {072139EB-DCE9-49BE-A510-D748DA0081F5}
static const IID IID_IImagecontrastDemo =
{ 0x72139EB, 0xDCE9, 0x49BE, { 0xA5, 0x10, 0xD7, 0x48, 0xDA, 0x0, 0x81, 0xF5 } };

BEGIN_INTERFACE_MAP(CImagecontrastDemoDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CImagecontrastDemoDlgAutoProxy, IID_IImagecontrastDemo, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {CD9729C6-53E9-459D-A876-96ED23ADD7CE}
IMPLEMENT_OLECREATE2(CImagecontrastDemoDlgAutoProxy, "ImagecontrastDemo.Application", 0xcd9729c6, 0x53e9, 0x459d, 0xa8, 0x76, 0x96, 0xed, 0x23, 0xad, 0xd7, 0xce)


// CImagecontrastDemoDlgAutoProxy ��Ϣ�������
