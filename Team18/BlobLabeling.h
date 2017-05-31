#pragma once

#include <cv.h>
#include <highgui.h>

#define _DEF_MAX_BLOBS		10000	//	최대blob수
#define _DEF_MAX_LABEL		  100	//	최대 레이블 수

typedef struct 
{
	BOOL	bVisitedFlag;			//	방문기록을 나타냄
	CvPoint ptReturnPoint;			//	리턴포인트
} Visited;

class  CBlobLabeling
{
public:
	CBlobLabeling(void);
public:
	~CBlobLabeling(void);

public:
	IplImage*	m_Image;				//	레이블링을 위한 이미지
	int			m_nThreshold;			//	레이블링 스레스홀드 값
	Visited*	m_vPoint;				//	레이블링시 방문정보
	int			m_nBlobs;				//	레이블의 갯수
	CvRect*		m_recBlobs;				//	각 레이블 정보
	int			m_candidateLabel[_DEF_MAX_LABEL];			//	후보로 선정된 레이블
	CvRect*		m_candidateBlobs;		//	후보로 선정된 blob을 저장함
	int			m_nCandidate;			//	후보로 선정된 레이블 수

public:
	//	레이블링 이미지 선택
	void SetParam(IplImage* image, int nThreshold);

	//	레이블링(실행)
	void DoLabeling();

	//	레이블링 제거
	IplImage* DeleteLabeling(IplImage* srcImage);

	//	후보레이블 추출
	CvRect*	GetCandidateBlob(CvRect* m_recBlobs);

private:
	// 레이블링(동작)
	int Labeling(IplImage* image, int nThreshold);

	// 포인트 초기화
	void InitvPoint(int nWidth, int nHeight);
	void DeletevPoint();

	// 레이블링 결과 얻기
	void DetectLabelingRegion(int nLabelNumber, unsigned char *DataBuf, int nWidth, int nHeight);

	// 레이블링(실제 알고리즘)
	int	_Labeling(unsigned char *DataBuf, int nWidth, int nHeight, int nThreshold);
	
	// _Labling 내부 사용 함수
	int	__NRFIndNeighbor(unsigned char *DataBuf, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY );
	int	__Area(unsigned char *DataBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel);

	//	레이블링 제거
	IplImage* _DeleteLabeling(IplImage* srcImage, int m_nBlobs, CvRect* m_recBlobs);

	//	후보레이블 추출
	CvRect* _GetCandidateBlob(CvRect* m_recBlobs, int* candidateLabel);
};