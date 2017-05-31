// Team18Dlg.h : 헤더 파일

#pragma once
#include "afxwin.h"
#include "BlobLabeling.h"
#include <highgui.h>
#include <cv.h>
#include <time.h>

// Display
#define MAIN	1
#define CARNUM	2

// 해상도
#define HIGH	100
#define LOW		20

// CTeam18Dlg 대화 상자
class CTeam18Dlg : public CDialog
{
// 생성
public:
	CTeam18Dlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_Team18_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IplImage* m_pImage;		//	이미지를 저장할 변수
	CvvImage m_cImage;		//	화면출력용
	CvCapture* m_pCapture;	//	화면출력용
	IplImage* labelImage;	//	레이블링이 표시되는 이미지 변수

	CString tempBuffer;		//	텍스트 등을 저장할 버퍼
	CBlobLabeling blob;		//	레이블링 추출할 클래스
	int resultNum[8][2];	//	인식된 결과
	int digit;				//	인식된 결과의 자릿수를 나타냄
	int resolution;			//	해상도를 나타낸다
	CFont font;				//	결과값 폰트를 나타낼 변수
	LOGFONT lf;				//	폰트정보가 저장될 변수

public:

	void ShowImage(CString, int nDisp);					//	nDisp에 따라 해당 디스플레이에 이미지를 출력한다.
	CString GetImagePath();								//	이미지의 경로를 얻어온다.

	//그레이 이미지를 이진화한다.
	void Gray2Binary(IplImage *srcImage, IplImage* dstImage, int threshold);

	//일정영역 부분을 path로 저장한다.
	IplImage* SaveRectArea(IplImage* srcImage, const char* path, CvRect area);

	//차량번호판 부분을 얻어온다.
	CvRect GetNumImage(IplImage* srcImage);

	void PrintResult();										//	결과를 출력한다.
	void RecogNum(IplImage* srcImage);						//	번호판으로부터 번호를 인식한다.
	int TemplateMatching(IplImage* image, IplImage* templ);	//	번호를 템플릿매칭하여 해당 번호를 인식한다.
	void BubbleSorting(int num[6][2]);						//	결과값을 x좌표에 따라서 정렬한다.

	IplImage* RGB2Gray(IplImage *src);
	int* HorizonProjection(IplImage* image);
	int* VerticalProjection(IplImage* image);

	//	UI관련 변수, 함수
	CStatic m_stDisplay;					//	Main 디스플레이 멤버변수
	afx_msg void OnBnClickedBtStart();		//	시작버튼을 눌렀을때의 이벤트
	afx_msg void OnBnClickedButtonLoad();	//	이미지 로드를 하는 이벤트
	CStatic m_carNum;						//	번호판 디스플레이 멤버변수
	CStatic m_result;						//	결과레이블의 멤버변수
	CStatic m_picCtrl;
	CString m_filename;
};
