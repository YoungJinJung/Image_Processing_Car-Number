// Team18Dlg.cpp : ���� ����

#include "stdafx.h"
#include "Team18.h"
#include "Team18Dlg.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ ����
class CAboutDlg : public CDialog
{
public:
	CAboutDlg(){};

	// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

protected:
	DECLARE_MESSAGE_MAP()
};

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTeam18Dlg ��ȭ ����
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


// CTeam18Dlg �޽��� ó����

BOOL CTeam18Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	tempBuffer.Empty();
	for(int i=0;i<8;i++) resultNum[i][1] = 0;
	


	m_result.SetFont(&font, true);
	
	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_Team18)); 
    m_picCtrl.SetBitmap(hBit);
   
    CRect rt;
    GetClientRect(&rt);
	m_picCtrl.SetWindowPos(NULL, 530, 330, 220, 200, SWP_SHOWWINDOW);
	
	//��� ��Ʈ �� ũ�� ����
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTeam18Dlg::OnPaint()
{
	// �׸� �׸��� DC
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTeam18Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTeam18Dlg::OnBnClickedButtonLoad() // ���� �ε� �̺�Ʈ
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//���� ���� ���̾�α� �̿� BMP, JPG,PNG ���� �ҷ�����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//��θ� ���� �̹����� �޾ƿ´�.
	tempBuffer = GetImagePath();

	if(m_pImage!=NULL) cvReleaseImage(&m_pImage);
	m_pImage = cvLoadImage(tempBuffer, -1);

	if(m_pImage->width >=640 || m_pImage->height>=480) resolution = HIGH;
	else resolution = LOW;
	IplConvKernel *element = cvCreateStructuringElementEx(7, 7, 4, 4, CV_SHAPE_RECT, NULL);//ħ�Ŀ����� ���� Ŀ��

	//�ӽ��̹�������
	IplImage* tempImage;
	IplImage* orgImage;
	tempImage = cvCreateImage(cvGetSize(m_pImage), 8, 1);
	orgImage = cvCreateImage(cvGetSize(m_pImage), 8, 1);


	switch(resolution)
	{
	case HIGH:
		cvCvtColor(m_pImage, orgImage, CV_BGR2GRAY);//Gray��ȯ
		cvSmooth(orgImage, tempImage, CV_GAUSSIAN, 5, 5);//����þ�����

		cvErode(orgImage, tempImage, element, 1);//ħ�Ŀ���
		cvErode(tempImage, tempImage, element, 1);//ħ�Ŀ���
		cvSub(orgImage, tempImage, tempImage);//Top-Hat����
		Gray2Binary(tempImage, tempImage, 128);//����ȭ
		Gray2Binary(orgImage, orgImage, 128);//�����̹��� ����ȭ

		break;
	case LOW:
		cvCvtColor(m_pImage, orgImage, CV_BGR2GRAY);//Gray��ȯ
		Gray2Binary(orgImage, tempImage, 128);//����ȭ
		Gray2Binary(orgImage, orgImage, 128);//�����̹��� ����ȭ

		break;
	}

	//���̺� �� ��������	
	blob.SetParam(tempImage, resolution);
	blob.DoLabeling();	

	CvRect numRect = GetNumImage(tempImage);//���̺� ���� �� ��ȣ���� ��������
	IplImage* numImage = SaveRectArea(orgImage, "./rabelingSec.bmp", numRect);//�ĺ����̺� ���� ����

	//�������� �� ��ȣ�ν�
	RecogNum(numImage);
	
	//�̹������� �� ���
	ShowImage(_T("./test2.jpg"), MAIN);

	//������
	PrintResult();

	//�̹��� �ڿ� �ݳ�
	cvReleaseImage(&tempImage);
	cvReleaseImage(&orgImage);
	cvReleaseImage(&m_pImage);
}

IplImage* CTeam18Dlg::SaveRectArea(IplImage* srcImage, const char* path, CvRect area)
{
	//�����̹����� ���μ��α��̸� ����
	int nWidth = srcImage->widthStep;
	int nHeight = srcImage->height;
	
	//���������� ������ ���� ����
	IplImage* tempImage = cvCreateImage(cvSize(area.width, area.height), 8, 1);

	//�ȼ��� ����Ű�� ������
	int X=0;

	//������ ���̰� 4����� �ƴҰ�� 4����� �����ִ� �κ�
	int reminder = 0;
	(area.width%4)==0 ? reminder = 0 : reminder = 4-area.width%4;
	
	//�ȼ����� ������
	for(int i=area.y; i<area.y+area.height; i++)
	{
		for(int j=area.x; j<area.x+area.width; j++)
		{
			tempImage->imageData[X] = srcImage->imageData[i*nWidth+j];
			X++;
		}
		X = X + reminder;//������ ���̸� 4����� ������
	}
	
	//����ȭ��Ų��.
	cvThreshold( tempImage, tempImage, 1, 255, CV_THRESH_BINARY_INV );
	
	//���ػ��϶��� ��ȣ���̹����� ��â������ �Ѵ�.
	if(resolution == HIGH)
	{
		IplConvKernel *element = cvCreateStructuringElementEx(3, 3, 2, 2, CV_SHAPE_RECT, NULL);
		cvDilate(tempImage, tempImage, element, 1);
	}

	//�̹��� ����
	cvSaveImage(path, tempImage);

	//�̹��� ���̱�
	ShowImage(_T(path), CARNUM);

	return tempImage;
}


CvRect CTeam18Dlg::GetNumImage(IplImage* srcImage)
{
	//���� ���� ����
	int nWidth = srcImage->widthStep;
	int nHeight = srcImage->height;
	int nBlob=0;

	//���̺� �� ������� ��ȣ�ǿ����� �����Ѵ�.
	for(int i=0; i<blob.m_nBlobs; i++)
	{
		//��ȣ�� ������ ǥ���� ����
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
			// �̹��� ���ɿ��� ����
			cvSetImageROI( srcImage, blob.m_recBlobs[i] );

			IplImage* sub_gray = cvCreateImage( cvSize( blob.m_recBlobs[i].width, blob.m_recBlobs[i].height ), 8, 1 );

			cvThreshold( srcImage, sub_gray, 1, 255, CV_THRESH_BINARY_INV );

			// ���ɿ��� ����
			cvResetImageROI( srcImage );

			// ���̺�
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
	IplImage* numImage[10];//0~9���� ��ȣ�� ������ �̹�������
	char pathName[128];//�̹����� ������ ���
	CBlobLabeling numBlob;
	digit=0; //�νĵ� ����� �ڸ����� 0���� �ʱ�ȭ
	labelImage = cvCreateImage(cvGetSize(srcImage), 8, 3);
	cvCvtColor(srcImage, labelImage, CV_GRAY2BGR );//�׷��̸� RGB�� �ٲ��ش�.

	FILE* fp = fopen("./matching.txt", "w+");
	char buf[512];

	//���ڿ��� ����
	numBlob.SetParam(srcImage, resolution);
	numBlob.DoLabeling();

	//�����ĺ������� ���̺� ����� ���ø� ��Ī
	for(int i=0; i<numBlob.m_nBlobs; i++)
	{
		CvRect rect = numBlob.m_recBlobs[i];
		//������ ���̰� ���κ��� �� ���簢��
		if(rect.height<rect.width||
			(float)rect.height/(float)rect.width>5||
			(float)rect.height/(float)rect.width<1.3){}
		else
		{
			CvPoint pt1 = cvPoint(numBlob.m_recBlobs[i].x, numBlob.m_recBlobs[i].y);
			CvPoint pt2 = cvPoint(pt1.x+numBlob.m_recBlobs[i].width, pt1.y+numBlob.m_recBlobs[i].height);
			CvScalar color = cvScalar(0,0, 255);
			cvDrawRect(labelImage, pt1, pt2, color);
			
			//���ڹ�ȣ �̹������� �����´�
			for(int n=0; n<10; n++)
			{
				numImage[n] = cvCreateImage(cvSize(rect.width, rect.height), 8, 1);
				sprintf(pathName, "./templete/%d.bmp", n);
				IplImage* temp = cvLoadImage(pathName, 0);
				cvResize(temp, numImage[n]);
				cvThreshold( numImage[n], numImage[n], 1, 255, CV_THRESH_BINARY_INV );
			}


			IplImage* blobImage = cvCreateImage(cvSize(rect.width, rect.height), 8, 1);
			cvSetImageROI(srcImage, rect);			//��������
			cvCopy(srcImage, blobImage, NULL);			//����
			cvResetImageROI(srcImage);			//����
			cvThreshold( blobImage, blobImage, 1, 255, CV_THRESH_BINARY_INV );

			//���ø���Ī
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

//��¾�� 
void CTeam18Dlg::PrintResult()
{
	CString result;

	//�νĵ� ������ 6���϶�
	if(digit==6)
	{
		result.Format("%d%d %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[2][1], resultNum[3][1], resultNum[4][1], resultNum[5][1]);
	}
	//�νĵ� ������ 7���϶�, �� �߰� ���ڱ��� �νĵ�
	else if(digit==7)
	{
		result.Format("%d%d %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[3][1], resultNum[4][1], resultNum[5][1], resultNum[6][1]);
	}
	//�νĵ� ������ 8���϶�, �߰� ���ڰ� �ΰ��� �νĵ�
	else if(digit==8)
	{
		result.Format("%d%d %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[4][1], resultNum[5][1], resultNum[6][1], resultNum[7][1]);
	}
	//���ڸ��� �νĵǾ��� ���
	else if(digit==4)
	{
		result.Format("?? %d%d%d%d", resultNum[0][1], resultNum[1][1], resultNum[2][1], resultNum[3][1]);
	}
	//�ν��� �ȵǾ��� ���
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

//��������
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



//��������
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