
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CImagecontrastDemoDlg;


// CImagecontrastDemoDlgAutoProxy ����Ŀ��

class CImagecontrastDemoDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CImagecontrastDemoDlgAutoProxy)

	CImagecontrastDemoDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CImagecontrastDemoDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CImagecontrastDemoDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CImagecontrastDemoDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

