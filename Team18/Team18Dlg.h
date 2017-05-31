// Team18Dlg.h : ��� ����

#pragma once
#include "afxwin.h"
#include "BlobLabeling.h"
#include <highgui.h>
#include <cv.h>
#include <time.h>

// Display
#define MAIN	1
#define CARNUM	2

// �ػ�
#define HIGH	100
#define LOW		20

// CTeam18Dlg ��ȭ ����
class CTeam18Dlg : public CDialog
{
// ����
public:
	CTeam18Dlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_Team18_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IplImage* m_pImage;		//	�̹����� ������ ����
	CvvImage m_cImage;		//	ȭ����¿�
	CvCapture* m_pCapture;	//	ȭ����¿�
	IplImage* labelImage;	//	���̺��� ǥ�õǴ� �̹��� ����

	CString tempBuffer;		//	�ؽ�Ʈ ���� ������ ����
	CBlobLabeling blob;		//	���̺� ������ Ŭ����
	int resultNum[8][2];	//	�νĵ� ���
	int digit;				//	�νĵ� ����� �ڸ����� ��Ÿ��
	int resolution;			//	�ػ󵵸� ��Ÿ����
	CFont font;				//	����� ��Ʈ�� ��Ÿ�� ����
	LOGFONT lf;				//	��Ʈ������ ����� ����

public:

	void ShowImage(CString, int nDisp);					//	nDisp�� ���� �ش� ���÷��̿� �̹����� ����Ѵ�.
	CString GetImagePath();								//	�̹����� ��θ� ���´�.

	//�׷��� �̹����� ����ȭ�Ѵ�.
	void Gray2Binary(IplImage *srcImage, IplImage* dstImage, int threshold);

	//�������� �κ��� path�� �����Ѵ�.
	IplImage* SaveRectArea(IplImage* srcImage, const char* path, CvRect area);

	//������ȣ�� �κ��� ���´�.
	CvRect GetNumImage(IplImage* srcImage);

	void PrintResult();										//	����� ����Ѵ�.
	void RecogNum(IplImage* srcImage);						//	��ȣ�����κ��� ��ȣ�� �ν��Ѵ�.
	int TemplateMatching(IplImage* image, IplImage* templ);	//	��ȣ�� ���ø���Ī�Ͽ� �ش� ��ȣ�� �ν��Ѵ�.
	void BubbleSorting(int num[6][2]);						//	������� x��ǥ�� ���� �����Ѵ�.

	IplImage* RGB2Gray(IplImage *src);
	int* HorizonProjection(IplImage* image);
	int* VerticalProjection(IplImage* image);

	//	UI���� ����, �Լ�
	CStatic m_stDisplay;					//	Main ���÷��� �������
	afx_msg void OnBnClickedBtStart();		//	���۹�ư�� ���������� �̺�Ʈ
	afx_msg void OnBnClickedButtonLoad();	//	�̹��� �ε带 �ϴ� �̺�Ʈ
	CStatic m_carNum;						//	��ȣ�� ���÷��� �������
	CStatic m_result;						//	������̺��� �������
	CStatic m_picCtrl;
	CString m_filename;
};
