#pragma once
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <list> 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "ObjectAndKF.h"
#include "CColorAly.h"
#include "DetectionDef.h"
//#include "pvclassify.h"

using namespace std;
using namespace cv;

class CBlob//���������
{
public:
	CBlob();	//�ڹ��캯���д�txt�����˳�������

	//void Init(GetInfoCallBackFun clsGetInfoCallBackFun, bool bLPR, bool bFace, string strPathName, int TrackPointNumThresh, int ContoursRectNumThresh, int DistanceThresh, int DistanceThreshKal, int nResizeRatio);
	void Init(bool bLPR, bool bFace, string strPathName, int TrackPointNumThresh, int ContoursRectNumThresh, int DistanceThresh, int DistanceThreshKal, int nResizeRatio);

	CColorAly m_CColorAly;//��ɫ������
	CPara m_para;//������
	//PVClassify m_pvclassify;//�˳�������

	void BlobDetecterUseRect(const cv::Mat& _binImg, cv::Mat& _colorImg,std::vector<cv::Rect> & _input_rects);
	void BlobDetecter(const cv::Mat& _binImg, cv::Mat& _outputImg);	//Ѱ��ǰ�������еĽϴ�������������Ӿ��κ����ĵ㻹������
	void ClassifyCenters(const cv::Mat& _binImg, cv::Mat& _colorImg, cv::Mat& _ori_image, bool& _bObjectDistinguish, string& _strObjectInfo, int& _nObjectClass);//��ǰ֡�ľ������Ĺ��ൽ��������
	void ClassifyCenters(const cv::Mat& _binImg, cv::Mat& _colorImg, cv::Mat& _ori_image, string& _strObjectInfo, int& _nObjectClass);//��ǰ֡�ľ������Ĺ��ൽ��������
	void DrawPaths(cv::Mat& _outputImg);							//�����켣

	int GetObjNum();		//���ص�ǰ�����е�Ŀ�������ֻ������id�ģ�
	void GetObjInfo(std::string& _objInfo);//���ַ�����ʽ���ص�ǰ֡������Ϣ
private:
	void FindNearstPointKal(cv::Point pLast, int& id);		//���ÿ������˲�������Ԥ����һ��λ�ã����ڸ���Ѱ����һ��
	void FindNearstPoint(cv::Point pLast, int& id);			//����һ�㷽����ȡĳһ��ĸ����ĵ�

	list<ObjectAndKF> m_listObjects;		//��һ������洢��ͬ�����壬����ÿһ��ObjectAndKF�������һ�����壬ÿһ�����嶼��Ҫ�и��������˲���
	list<ObjectAndKF> m_listVanishObj;		//�����洢�ڻ�������ʧ�����壬�ڻ���������ʧ�����岻�洢

	vector<cv::Point> m_centers;			//ÿһ֡�ҵ��ľ������ĵ㶼��������
	vector<cv::Rect> m_rects;				//ÿһ֡�ҵ�����Ӿ��δ�������
	std::vector<std::vector<cv::Point>> m_goodContours;//ÿһ֡ɸѡ������������
	vector<int> m_PorV;						//ÿһ�������ķ�������-1��ʾ�ǻ�������1��ʾ������
	vector<vector<Vec3d>> m_colorsRGB;        //ÿһ����������ҪRBGֵ��ÿ���������ϰ�κ��°��������ɫֵ

	long m_objCount;//ͳ����������

	string m_strPathName = "";

	int m_nResizeRatio = 0;

	GetInfoCallBackFun m_clsGetInfoCallBackFun;

	bool m_bLPR;
	bool m_bFace;

};
