#ifndef _PV_CLASSIFY_
#define _PV_CLASSIFY_
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "ObjectAndKF.h"
using namespace std;
using namespace cv;

class PVClassify{
public:

	void ImportClassify0();//��ָ��·��������������m_classify0��
	int GetObjClassify(const vector<cv::Point>& _Contours, const cv::Rect& _rect);//��ȡĳ�������ĸ�������,�����з���,������-1Ϊ�ǻ�������1Ϊ������
	void GetSamples(ObjectAndKF& _obj);//��ĳһ���嵱ǰ֡��6������������ļ���
private:
	string m_classify_filepath = "../data/classifys/classify.txt";//������txt�洢�����·��,�÷�����ѵ����ȷ��99.1%
	string m_output_samples_filepath = "../data/ClassifyTrainer/dataSet.txt";//��ȡ��������txt�ļ���·��

	vector<vector<double>> m_classify0;//�洢�˳�adaboost��������ÿ������6��������������-1Ϊ�ǻ�������1Ϊ������,m_classify0��һά��ÿ�������������������ڶ�ά�Ǿ������ĸ�������

	void GetObjRatio1323(const vector<cv::Point>& _contours, const cv::Rect& _rect, double & _ratio13, double& _ratio23);//��ȡ����߶���������1/3��2/3����ȵı���
};
#endif