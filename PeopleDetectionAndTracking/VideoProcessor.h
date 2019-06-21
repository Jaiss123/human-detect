#ifndef _VIDEOPROCESSOR_
#define  _VIDEOPROCESSOR_
#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include "Cblob3.h"
#include "CImgproc.h"
#include "CColorAly.h"
using namespace cv;


class VideoProcessor
{
public:
	VideoProcessor();//���캯������ʼ���б���ֵ
	~VideoProcessor();

	//void Init(GetInfoCallBackFun clsGetInfoCallBackFun, bool bLPR, bool bFace, char* pathName, int _height, int _width, int nResizeRatio);
	void Init(bool bLPR, bool bFace, char* pathName, int _height, int _width, int nResizeRatio);
	void GetObjectInfo(std::string& _objInfo);//���ַ�����ʽ���ص�ǰ֡������Ϣ
	//void Run(unsigned char* pBGR24, int _size, bool& _bObjectDistinguish, string& _strObjectInfo, int& _nObjectClass);//��ʼ����ѭ��
	void Run(unsigned char* pBGR24, int _size, string& _strObjectInfo, int& _nObjectClass);//��ʼ����ѭ��
	void onStop();
	string strObjectInfo;//Ŀ��������Ϣ�������ַ��������洢·����
	int nObjectClass;//Ŀ�����1Ϊ����-1Ϊ�ˣ�

	cv::Mat		m_frame;//����֮���ͼ��
private:
	int			m_height;//m_frame�ĸ�
	int			m_width;//m_frame�Ŀ�

	int			m_nResizeRatio;//����ϵ��
	string		m_pathName;

	cv::Mat		m_foreImage;//ǰ��ͼ��


	cv::Mat		m_ori_image;//ԭʼͼ��
	cv::Mat		m_element;//��̬ѧ�ṹԪ��

	CBlob m_CBlob;//������
	CImgproc m_CImgproc;//ͼ������
	//cv::Ptr<cv::BackgroundSubtractorMOG2> m_MOG2;//��ϸ�˹��
	//Ptr<BackgroundSubtractorMOG2> m_MOG2;
	Ptr<BackgroundSubtractorKNN> m_KNN;
	cv::Mat m_TempImage;
};

#endif