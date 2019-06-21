#ifndef _CCOLORALY_
#define  _CCOLORALY_
#include <opencv2/opencv.hpp>
#include <vector>
#include "DetectionDef.h"
using namespace cv;
using namespace std;

class CColorAly
{
public:

	void GetMaxRGB(cv::Rect _rect, vector<cv::Point> _Contours, cv::Mat& _colorROI, cv::Point3i& _colorRGB);//Ѱ��RBGÿ��ͨ������������ɫֵ����
	void GetAverageRGB(cv::Rect _rect, vector<cv::Point> _Contours, cv::Mat& _colorROI, cv::Point3i& _colorRGB);//Ѱ��RBG����ͨ����ƽ��ֵ����
	//void GetAverageHSV(cv::Rect _rect, cv::Mat& _colorROI, vector<ObjectColor> & _color, int _class);//���볤��Ϊ2����ɫ�����������������0Ϊ�ǳ���1Ϊ��
	void GetAverageHSV(cv::Rect _rect, cv::Mat& _colorROI,const cv::Mat& _binROI, vector<ObjectColor> & _color, int _class);//���볤��Ϊ2����ɫ�����������������-1Ϊ�ǳ���1Ϊ��
	void GetAverageHSV2(cv::Mat& _colorROI, const cv::Mat& _binROI, vector<ObjectColor> & _color, int _class);//���볤��Ϊ2����ɫ�����������������-1Ϊ�ǳ���1Ϊ��

	//���RGB��ֵ
	void GetAverageHSV3(cv::Mat& _colorROI, const cv::Mat& _binROI, vector<Vec3d> & _color, int _class);
private:
	enum ObjectColor color;
};

#endif /