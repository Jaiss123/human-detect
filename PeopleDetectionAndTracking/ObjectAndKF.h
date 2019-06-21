#pragma once
#include <opencv2/opencv.hpp>
#include <opencv/cv.h> 
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "DetectionDef.h"
#include "CColorAly.h"
//#include "FaceDetection_Interface.h"//����ʶ��
//#include "LPR_Interface.h" //����ʶ��

using namespace std;
using namespace cv;


class ObjectAndKF//���������
{
public:
	ObjectAndKF() :m_objID(-1)
	{
		m_colorH.resize(2);//һ��������ɫ���ϰ�κ��°��
		//m_allClassifyResults = 0;
	}
	//	ObjectAndKF& operator = (const ObjectAndKF&);

	vector<cv::Point> m_vecCenters;	//�洢����������й켣��
	cv::Rect m_rect;				//�洢���һ���켣���Ӧ����С��Ӿ���
	//vector<cv::Point> m_Contours;	//�洢���һ���켣���Ӧ������
	int m_objID;					//�洢�����id��
	//int m_class;					//��ǰ֡�˳����࣬-1��ʾ�ǳ���1��ʾ��
	vector<Vec3d> m_colorH;			//���������ɫ����Ϊ�ϰ�κ��°�Σ�ö�ٱ���

	//int m_allClassifyResults;       //������֡�˳��������ۼ����,����ʾ�ǳ�������ʾ��
	cv::Mat m_perfect_color_image;  //��ѵĲ�ɫROIͼ��
	cv::Mat m_perfect_color_big_image;  //��ѵĲ�ɫROIͼ��
	cv::Mat m_perfect_bin_image;	//��ѵ�ǰ��ROI

	void Init(GetInfoCallBackFun clsGetInfoCallBackFun, string strPictureFolder, bool bLPR, bool bFace);					//��ʼ���������˲�������Ҫ����m_vecCenters�еĵ�һ����
	cv::Point Predict();			//ʹ�ÿ������˲���Ԥ����һ���λ�ã�������һ��
	void Correct(int num);			//ʹ��ͼ������ʵ�����ĵ������˲���,numΪm_vecCenters������

	void UpdatePerfectImages(const cv::Mat& _binImg, cv::Mat& _colorImg, cv::Mat& _ori_image,int nResizeRatio);//�������ͼ��
	//void GetFinalOBjInfo(bool& _bObjectDistinguish, string& ObjectInfo, int& _nObjectClass);			//�������뿪����ʱ������Ϣ���
	void GetFinalOBjInfo( string& ObjectInfo, int& _nObjectClass);			//�������뿪����ʱ������Ϣ���
private:
	string m_output_filepath;//�������뿪����ʱ������Ϣ���������
	string m_output_imagepath; //�������뿪����ʱ,������ͼ��
	string m_output_faceimgpath;//�����뿪ʱ�������ͷ��ͼ��
	string m_output_lprimgpath;//�����뿪ʱ�������ͷ��ͼ��

	bool m_bLPR;
	bool m_bFace;
	GetInfoCallBackFun m_clsGetInfoCallBackFun;

	const int stateNum = 4;
	const int measureNum = 2;
	KalmanFilter KF;
	Mat state; //state(x,y,detaX,detaY)  
	Mat processNoise;
	Mat measurement;    //measurement(x,y) 

	

};