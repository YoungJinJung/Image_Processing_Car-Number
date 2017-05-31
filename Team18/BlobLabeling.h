#pragma once

#include <cv.h>
#include <highgui.h>

#define _DEF_MAX_BLOBS		10000	//	�ִ�blob��
#define _DEF_MAX_LABEL		  100	//	�ִ� ���̺� ��

typedef struct 
{
	BOOL	bVisitedFlag;			//	�湮����� ��Ÿ��
	CvPoint ptReturnPoint;			//	��������Ʈ
} Visited;

class  CBlobLabeling
{
public:
	CBlobLabeling(void);
public:
	~CBlobLabeling(void);

public:
	IplImage*	m_Image;				//	���̺��� ���� �̹���
	int			m_nThreshold;			//	���̺� ������Ȧ�� ��
	Visited*	m_vPoint;				//	���̺��� �湮����
	int			m_nBlobs;				//	���̺��� ����
	CvRect*		m_recBlobs;				//	�� ���̺� ����
	int			m_candidateLabel[_DEF_MAX_LABEL];			//	�ĺ��� ������ ���̺�
	CvRect*		m_candidateBlobs;		//	�ĺ��� ������ blob�� ������
	int			m_nCandidate;			//	�ĺ��� ������ ���̺� ��

public:
	//	���̺� �̹��� ����
	void SetParam(IplImage* image, int nThreshold);

	//	���̺�(����)
	void DoLabeling();

	//	���̺� ����
	IplImage* DeleteLabeling(IplImage* srcImage);

	//	�ĺ����̺� ����
	CvRect*	GetCandidateBlob(CvRect* m_recBlobs);

private:
	// ���̺�(����)
	int Labeling(IplImage* image, int nThreshold);

	// ����Ʈ �ʱ�ȭ
	void InitvPoint(int nWidth, int nHeight);
	void DeletevPoint();

	// ���̺� ��� ���
	void DetectLabelingRegion(int nLabelNumber, unsigned char *DataBuf, int nWidth, int nHeight);

	// ���̺�(���� �˰���)
	int	_Labeling(unsigned char *DataBuf, int nWidth, int nHeight, int nThreshold);
	
	// _Labling ���� ��� �Լ�
	int	__NRFIndNeighbor(unsigned char *DataBuf, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY );
	int	__Area(unsigned char *DataBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel);

	//	���̺� ����
	IplImage* _DeleteLabeling(IplImage* srcImage, int m_nBlobs, CvRect* m_recBlobs);

	//	�ĺ����̺� ����
	CvRect* _GetCandidateBlob(CvRect* m_recBlobs, int* candidateLabel);
};