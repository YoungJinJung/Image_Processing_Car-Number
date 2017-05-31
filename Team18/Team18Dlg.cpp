// Team18Dlg.cpp : 구현 파일

#include "stdafx.h"
#include "Team18.h"
#include "Team18Dlg.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자
class CAboutDlg : public CDialog
{
public:
	CAboutDlg(){};

	// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

protected:
	DECLARE_MESSAGE_MAP()
};

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTeam18Dlg 대화 상자
CTeam18Dlg::CTeam18Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTeam18Dlg::IDD, pParent), m_pImage(NULL), m_pCapture(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_filename = _T("");
}

void CTeam18Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_stDisplay);
	DDX_Control(pDX, IDC_STATIC_NUMBER, m_carNum);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_result);
	DDX_Control(pDX, IDC_Team18, m_picCtrl);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_filename);
}

BEGIN_MESSAGE_MAP(CTeam18Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_START, &CTeam18Dlg::OnBnClickedBtStart)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTeam18Dlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CTeam18Dlg 메시지 처리기

BOOL CTeam18Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	tempBuffer.Empty();
	for(int i=0;i<8;i++) resultNum[i][1] = 0;
	


	m_result.SetFont(&font, true);
	
	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_Team18)); 
    m_picCtrl.SetBitmap(hBit);
   
    CRect rt;
    GetClientRect(&rt);
	m_picCtrl.SetWindowPos(NULL, 530, 330, 220, 200, SWP_SHOWWINDOW);
	
	//출력 폰트 및 크기 설정
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 30;
	lf.lfCharSet = DEFAULT_CHARSET;
	font.CreateFontIndirectA(&lf);

    UpdateData(false);

	return TRUE;  
}

void CTeam18Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTeam18Dlg::OnPaint()
{
	// 그림 그리는 DC
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTeam18Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTeam18Dlg::OnBnClickedButtonLoad() // 파일 로드 이벤트
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//파일 열기 다이얼로그 이용 BMP, JPG,PNG 형식 불러오기
	CFileDialog Dlg(TRUE, _T("BMP"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
		_T("JPG Files(*.jpg)|*.jpg|Bitmap Files(*.bmp)|*.bmp|PNG Files(*.png)|*.png|All Files(*.*)|*.*||"), this);
	if(Dlg.DoModal()==IDOK)
	{
		m_filename = Dlg.GetPathName();
	}

	tempBuffer = GetImagePath();
	ShowImage(tempBuffer, MAIN);
	UpdateData(FALSE);
}

void CTeam18Dlg::ShowImage(CString imagePath, int nDisp)
{
	switch(nDisp)
	{
	case MAIN:
		m_pImage = cvLoadImage(imagePath, -1);

		Invalidate(FALSE);

		if(m_pImage)
		{
			CDC* pDC;
			CRect rect;

			pDC = m_stDisplay.GetDC();
			m_stDisplay.GetClientRect(&rect);
			m_cImage.CopyOf(m_pImage);
			m_cImage.DrawToHDC(pDC->m_hDC, rect);
			ReleaseDC(pDC);
		}
		break;
	case CARNUM:
		m_pImage = cvLoadImage(imagePath, -1);

		Invalidate(FALSE);

		if(m_pImage)
		{
			CDC* pDC;
			CRect rect;
			pDC = m_carNum.GetDC();
			m_carNum.GetClientRect(&rect);
			m_cImage.CopyOf(m_pImage);
			m_cImage.DrawToHDC(pDC->m_hDC, rect);
			ReleaseDC(pDC);
		}
		break;
	}
}

#define WIDTHSTEP 200

void CTeam18Dlg::OnBnClickedBtStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//경로를 통해 이미지를 받아온다.
	tempBuffer = GetImagePath();

	if(m_pImage!=NULL) cvReleaseImage(&m_pImage);
	m_pImage = cvLoadImage(tempBuffer, -1);

	if(m_pImage->width >=640 || m_pImage->height>=480) resolution = HIGH;
	else resolution = LOW;
	IplConvKernel *element = cvCreateStructuringElementEx(7, 7, 4, 4, CV_SHAPE_RECT, NULL);//침식연산을 위한 커널

	//임시이미지파일
	IplImage* tempImage;
	IplImage* orgImage;
	tempImage = cvCreateImage(cvGetSize(m_pImage), 8, 1);
	orgImage = cvCreateImage(cvGetSize(m_pImage), 8, 1);


	switch(resolution)
	{
	case HIGH:
		cvCvtColor(m_pImage, orgImage, CV_BGR2GRAY);//Gray변환
		cvSmooth(orgImage, tempImage, CV_GAUSSIAN, 5, 5);//가우시안필터

		cvErode(orgImage, tempImage, element, 1);//침식연산
		cvErode(tempImage, tempImage, element, 1);//침식연산
		cvSub(orgImage, tempImage, tempImage);//Top-Hat연산
		Gray2Binary(tempImage, tempImage, 128);//이진화
		Gray2Binary(orgImage, orgImage, 128);//원본이미지 이진화

		break;
	case LOW:
		cvCvtColor(m_pImage, orgImage, CV_BGR2GRAY);//Gray변환
		Gray2Binary(orgImage, tempImage, 128);//이진화
		Gray2Binary(orgImage, orgImage, 128);//원본이미지 이진화

		break;
	}

	//레이블링 및 영역추출	
	blob.SetParam(tempImage, resolution);
	blob.DoLabeling();	

	CvRect numRect = GetNumImage(tempImage);//레이블링 제거 및 번호영역 가져오기
	IplImage* numImage = SaveRectArea(orgImage, "./rabelingSec.bmp", numRect);//후보레이블링 영역 저장

	//문자추출 및 번호인식
	RecogNum(numImage);
	
	//이미지저장 및 출력
	ShowImage(_T("./test2.jpg"), MAIN);

	//결과출력
	PrintResult();

	//이미지 자원 반납
	cvReleaseImage(&tempImage);
	cvReleaseImage(&orgImage);
	cvReleaseImage(&m_pImage);
}

IplImage* CTeam18Dlg::SaveRectArea(IplImage* srcImage, const char* path, CvRect area)
{
	//원본이미지의 가로세로길이를 저장
	int nWidth = srcImage->widthStep;
	int nHeight = srcImage->height;
	
	//일정범위를 저장할 변수 선언
	IplImage* tempImage = cvCreateImage(cvSize(area.width, area.height), 8, 1);

	//픽셀을 가리키는 포인터
	int X=0;

	//가로의 길이가 4배수가 아닐경우 4배수로 맞춰주는 부분
	int reminder = 0;
	(area.width%4)==0 ? reminder = 0 : reminder = 4-area.width%4;
	
	//픽셀값을 복사함
	for(int i=area.y; i<area.y+area.height; i++)
	{
		for(int j=area.x; j<area.x+area.width; j++)
		{
			tempImage->imageData[X] = srcImage->imageData[i*nWidth+j];
			X++;
		}
		X = X + reminder;//가로의 길이를 4배수로 맞춰줌
	}
	
	//이진화시킨다.
	cvThreshold( tempImage, tempImage, 1, 255, CV_THRESH_BINARY_INV );
	
	//고해상도일때만 번호판이미지를 팽창연산을 한다.
	if(resolution == HIGH)
	{
		IplConvKernel *element = cvCreateStructuringElementEx(3, 3, 2, 2, CV_SHAPE_RECT, NULL);
		cvDilate(tempImage, tempImage, element, 1);
	}

	//이미지 저장
	cvSaveImage(path, tempImage);

	//이미지 보이기
	ShowImage(_T(path), CARNUM);

	return tempImage;
}


CvRect CTeam18Dlg::GetNumImage(IplImage* srcImage)
{
	//각종 변수 선언
	int nWidth = srcImage->widthStep;
	int nHeight = srcImage->height;
	int nBlob=0;

	//레이블링 한 결과에서 번호판영역을 검출한다.
	for(int i=0; i<blob.m_nBlobs; i++)
	{
		//번호판 영역을 표시할 점들
		CvPoint pt1 = cvPoint(blob.m_recBlobs[i].x, blob.m_recBlobs[i].y);
		CvPoint pt2 = cvPoint(pt1.x+blob.m_recBlobs[i].width, pt1.y+blob.m_recBlobs[i].height);

		if((blob.m_recBlobs[i].height>blob.m_recBlobs[i].width)||
			(blob.m_recBlobs[i].width>nWidth*0.8)||
			(blob.m_recBlobs[i].height>nHeight*0.8)&&
			((float)blob.m_recBlobs[i].width/(float)blob.m_recBlobs[i].height<1.5)||
			((float)blob.m_recBlobs[i].width/(float)blob.m_recBlobs[i].height>5.0)||
			blob.m_recBlobs[i].x < nWidth*0.1||
			blob.m_recBlobs[i].y < nHeight*0.1||
			(blob.m_recBlobs[i].x+blob.m_recBlobs[i].width)>nWidth*0.9||
			(blob.m_recBlobs[i].y+blob.m_recBlobs[i].height)>nHeight*0.9){}
		else
		{
			// 이미지 관심영역 설정
			cvSetImageROI( srcImage, blob.m_recBlobs[i] );

			IplImage* sub_gray = cvCreateImage( cvSize( blob.m_recBlobs[i].width, blob.m_recBlobs[i].height ), 8, 1 );

			cvThreshold( srcImage, sub_gray, 1, 255, CV_THRESH_BINARY_INV );

			// 관심영역 해제
			cvResetImageROI( srcImage );

			// 레이블링
			CBlobLabeling inner;
			inner.SetParam( sub_gray, resolution );

			inner.DoLabeling();

			for( int j=0; j < inner.m_nBlobs; j++ )
			{
				CvPoint	s_pt1 = cvPoint(	pt1.x + inner.m_recBlobs[j].x,				
											pt1.y + inner.m_recBlobs[j].y );
				CvPoint s_pt2 = cvPoint(	s_pt1.x + inner.m_recBlobs[j].width,	
											s_pt1.y + inner.m_recBlobs[j].height );
				if(inner.m_recBlobs[j].height<inner.m_recBlobs[j].width){}
				else
				{
					// green
					CvScalar green = cvScalar( 0, 255, 0 );
					cvDrawRect( m_pImage, s_pt1, s_pt2, green, 2 );
				}
			}
			cvReleaseImage( &sub_gray );
			if(inner.m_nBlobs > 3)
			{
				nBlob = i;
			}

			//red-zone
			CvScalar color = cvScalar(0,0, 255);
			cvDrawRect(m_pImage, pt1, pt2, color);
		}
	}

	cvSaveImage("./result.bmp", m_pImage);

	return blob.m_recBlobs[nBlob];
}

void CTeam18Dlg::RecogNum(IplImage* srcImage)
{
	IplImage* numImage[10];//0~9까지 번호를 저장할 이미지변수
	char pathName[128];//이미지를 가져올 경로
	CBlobLabeling numBlob;
	digit=0; //인식된 결과의 자릿수를 0으로 초기화
	labelImage = cvCreateImage(cvGetSize(srcImage), 8, 3);
	cvCvtColor(srcImage, labelImage, CV_GRAY2BGR );//그레이를 RGB로 바꿔준다.

	FILE* fp = fopen("./matching.txt", "w+");
	char buf[512];

	//문자영역 추출
	numBlob.SetParam(srcImage, resolution);
	numBlob.DoLabeling();

	//문자후보영역만 레이블링 수행과 템플릿 매칭
	for(int i=0; i<numBlob.m_nBlobs; i++)
	{
		CvRect rect = numBlob.m_recBlobs[i];
		//세로의 길이가 가로보다 긴 직사각형
		if(rect.height<rect.width||
			(float)rect.height/(float)rect.width>5||
			(float)rect.height/(float)rect.width<1.3){}
		else
		{
			CvPoint pt1 = cvPoint(numBlob.m_recBlobs[i].x, numBlob.m_recBlobs[i].y);
			CvPoint pt2 = cvPoint(pt1.x+numBlob.m_recBlobs[i].width, pt1.y+numBlob.m_recBlobs[i].height);
			CvScalar color = cvScalar(0,0, 255);
			cvDrawRect(labelImage, pt1, pt2, color);
			
			//숫자번호 이미지들을 가져온다
			for(int n=0; n<10; n++)
			{
				numImage[n] = cvCreateImage(cvSize(rect.width, rect.height), 8, 1);
				sprintf(pathName, "./templete/%d.bmp", n);
				IplImage* temp = cvLoadImage(pathName, 0);
				cvResize(temp, numImage[n]);
				cvThreshold( numImage[n], numImage[n], 1, 255, CV_THRESH_BINARY_INV );
			}


			IplImage* blobImage = cvCreateImage(cvSize(rect.width, rect.height), 8, 1);
			cvSetImageROI(srcImage, rect);			//영역지정
			cvCopy(srcImage, blobImage, NULL);			//저장
			cvResetImageROI(srcImage);			//해제
			cvThreshold( blobImage, blobImage, 1, 255, CV_THRESH_BINARY_INV );

			//템플릿매칭
			float max=0;
			int matchingNum=0;
			for(int n=0; n<10; n++)
			{
				int matchingCount = TemplateMatching(blobImage, numImage[n]);
				float matchingPercent = 100*(float)matchingCount / (float)(blobImage->width*blobImage->height);
				fputs(buf, fp);
				
				if(matchingPercent > max) 
				{	
					max = matchingPercent;
					matchingNum = n;
				}
			}
			fputs("\n", fp);

			if(max > 70.0f)
			{
				resultNum[digit][0] = rect.x;
				resultNum[digit][1] = matchingNum;
				digit++;
			}
			cvReleaseImage(&blobImage);
		}
	}

	CDC*	pDC;
	CRect	rect;

	pDC = m_carNum.GetDC();
	m_carNum.GetClientRect(&rect);

	m_cImage.CopyOf(labelImage);
	m_cImage.DrawToHDC(pDC->m_hDC, rect);

	cvReleaseImage(&labelImage);
	ReleaseDC(pDC);
	Invalidate(FALSE);

	BubbleSorting(resultNum);

	fclose(fp);
}

void CTeam18Dlg::BubbleSorting(int num[8][2])
{
	int temp=0;
	int temp2=0;

	for(int i=0; i<digit; i++)
	{
		for(int j=0; j<digit-i-1; j++)
		{
			if(num[j][0]>num[j+1][0]) 
			{
				temp = num[j][0];
				temp2 = num[j][1];
				num[j][0] = num[j+1][0];
				num[j][1] = num[j+1][1];
				num[j+1][0] = temp;
				num[j+1][1] = temp2;
			}
		}
	}
}

int CTeam18Dlg::TemplateMatching(IplImage* image, IplImage* templ)
{
	int percent=0;
	int nWidth = image->widthStep;
	int nHeight = image->height;

	for(int i=0; i<nHeight; i++)
	{
		for(int j=0; j<nWidth; j++)
		{
			if(image->imageData[i*nWidth+j] == templ->imageData[i*nWidth+j])
				percent++;
		}
	}

	return percent;
}

//출력양식 
void CTeam18Dlg::PrintResult()
{
	CString result;

	//인식된 갯수가 6개일때
	if(digit==6)
	{
		result.Format("%d%d %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[2][1], resultNum[3][1], resultNum[4][1], resultNum[5][1]);
	}
	//인식된 갯수가 7개일때, 즉 중간 문자까지 인식됨
	else if(digit==7)
	{
		result.Format("%d%d %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[3][1], resultNum[4][1], resultNum[5][1], resultNum[6][1]);
	}
	//인식된 갯수가 8개일때, 중간 문자가 두개로 인식됨
	else if(digit==8)
	{
		result.Format("%d%d %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[4][1], resultNum[5][1], resultNum[6][1], resultNum[7][1]);
	}
	//뒷자리만 인식되었을 경우
	else if(digit==4)
	{
		result.Format("?? %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[2][1], resultNum[3][1]);
	}
	//인식이 안되었을 경우
	else
	{
		result = _T("Fail");
	}
	m_result.SetWindowTextA(result);
	for(int i=0; i<8; i++) resultNum[i][1]= 0;
}


void CTeam18Dlg::Gray2Binary(IplImage *srcImage, IplImage *dstImage, int threshold)
{
	int nWidth = srcImage->width;
	int nHeight = srcImage->height;
	uchar *data = (uchar*)srcImage->imageData;

	for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			if(data[i*nWidth+j]>threshold)
				dstImage->imageData[i*nWidth+j] = 255;
			else
				dstImage->imageData[i*nWidth+j] = 0;
		}
	}
}

//수직투영
int* CTeam18Dlg::VerticalProjection(IplImage* image)
{
	int nWidth = image->width;
	int nHeight = image->height;

	FILE* fp = fopen("./test.txt", "w+");
	char buf[30];

	int reminder = 0;
	(nWidth%4)==0 ? reminder = 0 : reminder = 4-nWidth%4;
	
	int* VerticalData=(int*)malloc(sizeof(nWidth*4));

	for(int i=0; i<nWidth-reminder;i++)
	{
		VerticalData[i]=0;

		for(int j=0; j<nHeight;j++)
		{
			VerticalData[i]+=image->imageData[j*nWidth+i];
		}
		sprintf(buf, "%d\n",VerticalData[i]);
		fputs(buf, fp);
	}

	fclose(fp);
	
	return VerticalData;
}



//수평투영
int* CTeam18Dlg::HorizonProjection(IplImage* image)
{
	int nWidth = image->widthStep;
	int nHeight = image->height;

	FILE* fp = fopen("./test.txt", "w+");
	char buf[30];
	
	int* HorizonData=(int*)malloc(sizeof(nHeight*4));

	for(int i=0; i<nHeight;i++)
	{
		HorizonData[i]=0;

		for(int j=0; j<nWidth;j++)
		{
			HorizonData[i]+=image->imageData[j*nHeight+i];
		}
		sprintf(buf, "%d\n",HorizonData[i]);
		fputs(buf, fp);
	}

	fclose(fp);
	
	return HorizonData;
}


CString CTeam18Dlg::GetImagePath()
{
	CString temp = m_filename.GetString();
	return temp;
}