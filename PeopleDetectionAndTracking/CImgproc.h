#ifndef _IMGPROC_
#define  _IMGPROC_
#include <opencv2/opencv.hpp>

using namespace cv;


class CImgproc
{
public:

	void FillHole(const Mat srcBw, Mat &dstBw);//��ˮ��䷨�����ն�������Ϊ�ڣ�ǰ��Ϊ��
	void AddEdge(const Mat srcFw, const Mat srcBw, Mat &dstBw);
	
};

#endif // DEBUG
