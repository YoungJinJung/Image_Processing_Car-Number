#pragma once

#include <cv.h>
#include <highgui.h>

typedef struct
{
	BOOL	bVisitedFlag;
	CvPoint	ptReturnPoint;
}Visited;

class CLabeling
{
public:
	CLabeling(void);
	~CLabeling(void);

public:
	int	m_nThreshold;
	Visited*	m_vPoint;
	int	m_nLabels;
	CvRect*	m_recInfo;

public:
	void	SetParam(IplImage* image, int nThreshold);
	void	DoLabeling();
};
