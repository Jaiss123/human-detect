#include "stdafx.h"
#include "CColorAly.h"


void CColorAly::GetMaxRGB(cv::Rect _rect, vector<cv::Point> _Contours, cv::Mat& _colorROI, cv::Point3i& _colorRGB)
{
	cv::Mat ROI = _colorROI(_rect).clone();
	vector<cv::Point> ROIContours;
	for (auto it = _Contours.begin(); it != _Contours.end(); ++it)
	{
		cv::Point tem;
		tem.x = it->x - _rect.x;
		tem.y = it->y - _rect.y;
		ROIContours.push_back(tem);
	}

	vector<cv::Point3i> m_counts(256);
	for (int i = 0; i < ROI.rows; ++i)
	{
		Vec3b* imgData = ROI.ptr<Vec3b>(i);
		for (int j = 0; j < ROI.cols; ++j)
		{
			//if (cv::pointPolygonTest(ROIContours, cv::Point(j, i), 0) == 1)//��������������ͳ��,�ķѴ���ʱ��
			//{
				++(m_counts.at(imgData[j][0]).x);
				++(m_counts.at(imgData[j][1]).y);
				++(m_counts.at(imgData[j][2]).z);
			//}
		}
	}

	int countB(0), countG(0), countR(0);
	uchar idB(0), idG(0), idR(0);
	for (unsigned int k = 0; k < m_counts.size(); ++k)
	{
		if (m_counts[k].x > countB)
		{
			countB = m_counts[k].x;
			idB = (uchar)k;
		}
		if (m_counts[k].y > countG)
		{
			countG = m_counts[k].y;
			idG = (uchar)k;
		}
		if (m_counts[k].z > countR)
		{
			countR = m_counts[k].z;
			idR = (uchar)k;
		}
	}

	_colorRGB.x = idR;
	_colorRGB.y = idG;
	_colorRGB.z = idB;
}

void CColorAly::GetAverageRGB(cv::Rect _rect, vector<cv::Point> _Contours, cv::Mat& _colorROI, cv::Point3i& _colorRGB)
{
	cv::Mat ROI = _colorROI(_rect).clone();
	vector<double> sums(3);
	sums[0] = 0;
	sums[1] = 0;
	sums[2] = 0;

	for (int i = 0; i < ROI.rows; ++i)
	{
		Vec3b* imgData = ROI.ptr<Vec3b>(i);
		for (int j = 0; j < ROI.cols; ++j)
		{
			sums[0] += imgData[j][0];
			sums[1] += imgData[j][1];
			sums[2] += imgData[j][2];
		}
	}

	int num = ROI.rows*ROI.cols;

	_colorRGB.x = (uchar)(sums[2]/num);
	_colorRGB.y = (uchar)(sums[1] / num);
	_colorRGB.z = (uchar)(sums[0] / num);
}

//void CColorAly::GetAverageHSV(cv::Rect _rect, cv::Mat& _colorROI, const cv::Mat& _binROI, vector<ObjectColor> & _color, int _class)//���볤��Ϊ2����ɫ�����������������0Ϊ�ǳ���1Ϊ��
//{
//	Mat image = _colorROI.clone();
//	Mat binImage = _binROI.clone();
//	Mat ROI_HSV;
//	Mat ROI = image(_rect);
//	Mat binROI = binImage(_rect);
//	//Mat *RGB[2];
//	std::vector<cv::Mat> sbgr(ROI.channels());//ͨ��������
//	std::vector<cv::Mat> mbgr(ROI.channels());//ͨ���ϳ���
//	split(ROI, sbgr);
//	equalizeHist(sbgr[0], mbgr[0]);//����ͨ���ֱ�ֱ��ͼ���⻯
//	equalizeHist(sbgr[1], mbgr[1]);
//	equalizeHist(sbgr[2], mbgr[2]);
//
//	merge(mbgr, ROI);//����ͨ�����ºϳ�
//	cvtColor(ROI, ROI_HSV, COLOR_BGR2HSV);//��ʱH 0-180;
//	sbgr.clear();
//	split(ROI_HSV, sbgr);//�ָ��Hͨ��
//	double sum_V = 0;
//	int pixelCounter = 0;//ͳ�����������ص����������ƽ����V��
//	int colorCount[6] = { 0 };//ͳ�Ƹ�����ɫ������������������
//	if (_class == 0)//���˵Ļ�
//	{
//		//���ϰ���
//		for (int i = 0; i < (int)sbgr[0].rows/2; i++)
//		{
//			uchar* p0 = sbgr[0].ptr<uchar>(i);
//			uchar* p2 = sbgr[2].ptr<uchar>(i);
//			uchar* bin = binROI.ptr<uchar>(i);
//			for (int j = 0; j < sbgr[0].cols; j++)
//			{
//				if (bin[j] != 0)
//				{
//					pixelCounter++;
//					sum_V += p2[j];
//					p0[j] = p0[j] * 2;
//					if ((p0[j] >= 0 && p0[j] < 30) || (p0[j] >= 330 && p0[j] <= 360))
//						colorCount[0]++;//��ɫ
//					else if (p0[j] >= 30 && p0[j] < 90)
//						colorCount[1]++;//��ɫ
//					else if (p0[j] >= 90 && p0[j] < 150)
//						colorCount[2]++;//��ɫ
//					else if (p0[j] >= 150 && p0[j] < 210)
//						colorCount[3]++;//��
//					else if (p0[j] >= 210 && p0[j] < 270)
//						colorCount[4]++;//��
//					else if (p0[j] >= 270 && p0[j] < 330)
//						colorCount[5]++;//��
//				}
//			}
//		}
//		double  value_V = sum_V / pixelCounter;//����ƽ����Vֵ
//		int maxTem = 0;
//		int flag = 0;
//		if (value_V > 221 && value_V <= 255)
//		{
//			_color[0] = OBJECT_COLOR_WHITE;
//		}
//		else if (value_V >= 0 && value_V <= 46)
//		{
//			_color[0] = OBJECT_COLOR_BLACK;
//		}
//		else
//		{
//			maxTem = colorCount[0];
//			flag = 0;
//			for (int i = 1; i < 6;i++)//Ѱ��������ɫ�����
//			{
//				if (maxTem<colorCount[i])
//				{
//				    maxTem = colorCount[i];
//					flag = i;
//				}
//			}
//			switch (flag)
//			{
//			case 0:
//				_color[0] = OBJECT_COLOR_RED;
//				break;
//			case 1:
//				_color[0] = OBJECT_COLOR_YELLOW;
//				break;
//			case 2:
//				_color[0] = OBJECT_COLOR_GREEN;
//				break;
//			case 3:
//				_color[0] = OBJECT_COLOR_CYAN;
//				break;
//			case 4:
//				_color[0] = OBJECT_COLOR_BLUE;
//				break;
//			case 5:
//				_color[0] = OBJECT_COLOR_PURPLE;
//				break;
//			default:
//				_color[0] = OBJECT_COLOR_WHITE;
//				break;
//			}
//		}
//		//���°���
//		pixelCounter = 0;//����������
//		flag = 0;
//		sum_V = 0;
//		for (int i = 0; i < 6;i++)
//		{
//			colorCount[i] = 0;
//		}
//		for (int i = (int)sbgr[0].rows / 2; i < sbgr[0].rows; i++)
//		{
//			uchar* p0 = sbgr[0].ptr<uchar>(i);
//			uchar* p2 = sbgr[2].ptr<uchar>(i);
//			uchar* bin = binROI.ptr<uchar>(i);
//			for (int j = 0; j < sbgr[0].cols; j++)
//			{
//				if (bin[j] != 0)
//				{
//					pixelCounter++;
//					sum_V += p2[j];
//					p0[j] = p0[j] * 2;
//					if ((p0[j] >= 0 && p0[j] < 30) || (p0[j] >= 330 && p0[j] <= 360))
//						colorCount[0]++;//��ɫ
//					else if (p0[j] >= 30 && p0[j] < 90)
//						colorCount[1]++;//��ɫ
//					else if (p0[j] >= 90 && p0[j] < 150)
//						colorCount[2]++;//��ɫ
//					else if (p0[j] >= 150 && p0[j] < 210)
//						colorCount[3]++;//��
//					else if (p0[j] >= 210 && p0[j] < 270)
//						colorCount[4]++;//��
//					else if (p0[j] >= 270 && p0[j] < 330)
//						colorCount[5]++;//��
//				}
//			}
//		}
//		value_V = sum_V / pixelCounter;//����ƽ����Vֵ
//		maxTem = 0;
//		if (value_V > 221 && value_V <= 255)
//		{
//			_color[1] = OBJECT_COLOR_WHITE;
//		}
//		else if (value_V >= 0 && value_V <= 46)
//		{
//			_color[1] = OBJECT_COLOR_BLACK;
//		}
//		else
//		{
//			maxTem = colorCount[0];
//			flag = 0;
//			for (int i = 1; i < 6; i++)//Ѱ��������ɫ�����
//			{
//				if (maxTem < colorCount[i])
//				{
//					maxTem = colorCount[i];
//					flag = i;
//				}
//			}
//			switch (flag)
//			{
//			case 0:
//				_color[1] = OBJECT_COLOR_RED;
//				break;
//			case 1:
//				_color[1] = OBJECT_COLOR_YELLOW;
//				break;
//			case 2:
//				_color[1] = OBJECT_COLOR_GREEN;
//				break;
//			case 3:
//				_color[1] = OBJECT_COLOR_CYAN;
//				break;
//			case 4:
//				_color[1] = OBJECT_COLOR_BLUE;
//				break;
//			case 5:
//				_color[1] = OBJECT_COLOR_PURPLE;
//				break;
//			default:
//				_color[1] = OBJECT_COLOR_WHITE;
//				break;
//			}
//		}
//	}
//	else//class==1�ǳ�
//	{
//		for (int i = 0; i < sbgr[0].rows; i++)
//		{
//			uchar* p0 = sbgr[0].ptr<uchar>(i);
//			uchar* p2 = sbgr[2].ptr<uchar>(i);
//			uchar* bin = binROI.ptr<uchar>(i);
//			for (int j = 0; j < sbgr[0].cols; j++)
//			{
//				if (bin[j] != 0)
//				{
//					pixelCounter++;
//					sum_V += p2[j];
//					p0[j] = p0[j] * 2;
//					if ((p0[j] >= 0 && p0[j] < 30) || (p0[j] >= 330 && p0[j] <= 360))
//						colorCount[0]++;//��ɫ
//					else if (p0[j] >= 30 && p0[j] < 90)
//						colorCount[1]++;//��ɫ
//					else if (p0[j] >= 90 && p0[j] < 150)
//						colorCount[2]++;//��ɫ
//					else if (p0[j] >= 150 && p0[j] < 210)
//						colorCount[3]++;//��
//					else if (p0[j] >= 210 && p0[j] < 270)
//						colorCount[4]++;//��
//					else if (p0[j] >= 270 && p0[j] < 330)
//						colorCount[5]++;//��
//				}
//			}
//		}
//		double  value_V = sum_V / pixelCounter;//����ƽ����Vֵ
//		if (value_V > 221 && value_V <= 255)
//		{
//			_color[0] = OBJECT_COLOR_WHITE;
//			_color[1] = OBJECT_COLOR_WHITE;
//		}
//		else if (value_V >= 0 && value_V <= 46)
//		{
//			_color[0] = OBJECT_COLOR_BLACK;
//			_color[1] = OBJECT_COLOR_BLACK;
//		}
//		else
//		{
//			int maxTem = colorCount[0];
//			int flag = 0;
//			for (int i = 1; i < 6; i++)//Ѱ��������ɫ�����
//			{
//				if (maxTem < colorCount[i])
//				{
//					maxTem = colorCount[i];
//					flag = i;
//				}
//			}
//			switch (flag)
//			{
//			case 0:
//				_color[0] = OBJECT_COLOR_RED;
//				_color[1] = OBJECT_COLOR_RED;
//				break;
//			case 1:
//				_color[0] = OBJECT_COLOR_YELLOW;
//				_color[1] = OBJECT_COLOR_YELLOW;
//				break;
//			case 2:
//				_color[0] = OBJECT_COLOR_GREEN;
//				_color[1] = OBJECT_COLOR_GREEN;
//				break;
//			case 3:
//				_color[0] = OBJECT_COLOR_CYAN;
//				_color[1] = OBJECT_COLOR_CYAN;
//				break;
//			case 4:
//				_color[0] = OBJECT_COLOR_BLUE;
//				_color[1] = OBJECT_COLOR_BLUE;
//				break;
//			case 5:
//				_color[0] = OBJECT_COLOR_PURPLE;
//				_color[1] = OBJECT_COLOR_PURPLE;
//				break;
//			default:
//				_color[0] = OBJECT_COLOR_WHITE;
//				_color[1] = OBJECT_COLOR_WHITE;
//				break;
//			}
//		}
//	}
//}

void CColorAly::GetAverageHSV(cv::Rect _rect, cv::Mat& _colorROI, const cv::Mat& _binROI, vector<ObjectColor> & _color, int _class)//���볤��Ϊ2����ɫ�����������������0Ϊ�ǳ���1Ϊ��
{
	int whiteGrayThreshold = 125;//HSV�׻���ɫ����V����ֵ��ԭ��Ϊ221
	int blackGrayThresholdV = 46;//HSV�ڻ���ɫ����V����ֵ��ԭ��Ϊ46
	Mat binImage = _binROI.clone(); 
	Mat image = _colorROI.clone();
	Mat ROI_HSV;
	Mat ROI = image(_rect);
	Mat binROI = binImage(_rect);
	
	std::vector<cv::Mat> sbgr(ROI.channels());//ͨ��������
	std::vector<cv::Mat> mbgr(ROI.channels());//ͨ���ϳ���
	//split(ROI, sbgr);
	//equalizeHist(sbgr[0], mbgr[0]);//����ͨ���ֱ�ֱ��ͼ���⻯
	//equalizeHist(sbgr[1], mbgr[1]);
	//equalizeHist(sbgr[2], mbgr[2]);
	//merge(mbgr, ROI);//����ͨ�����ºϳ�

	cvtColor(ROI, ROI_HSV, COLOR_BGR2HSV);//��ʱH 0-180;
	sbgr.clear();
	split(ROI_HSV, sbgr);//�ָ��Hͨ��

	int colorCount[10] = { 0 };//ͳ��ÿ����ɫ���ص������˳��Ϊ  ��Ȼ��������ϰ׺�

	if (_class == -1)//�ж�����
	{
		//ͳ�����ϰ벿�ֵ���ɫ
		for (int i = 0; i < (int)(sbgr[0].rows / 2); i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					if ((p0[j] >= 0 && p0[j] <= 10 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255) || (p0[j] >= 156 && p0[j] <= 180 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255))
					{
						colorCount[0]+=2;//��ɫred
					}
					else if (p0[j] >= 11 && p0[j] <= 25 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[1]+=2;//��ɫorange
					}
					else if (p0[j] >= 26 && p0[j] <= 34 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[2]+=2;//��ɫyellow
					}
					else if (p0[j] >= 35 && p0[j] <= 77 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[3]+=2;//��ɫgreen
					}
					else if (p0[j] >= 78 && p0[j] <= 99 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[4]+=2;//��ɫcyan
					}
					else if (p0[j] >= 100 && p0[j] <= 124 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[5]+=2;//��ɫblue
					}
					else if (p0[j] >= 125 && p0[j] <= 155 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[6]+=2;//��ɫpurple
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 30 && p2[j] >= whiteGrayThreshold && p2[j] <= 255)
					{
						colorCount[7]++;//��ɫwhite
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 255 && p2[j] >= 0 && p2[j] <= blackGrayThresholdV)
					{
						colorCount[8]++;//��ɫblack
					}
					else
					{
						colorCount[9]++;//��ɫgray;
					}
				}
			}

		}
		int maxTemp = colorCount[0];
		int flag = 0;
		for (int i = 1; i < 10; i++)
		{
			if (maxTemp <= colorCount[i])
			{
				maxTemp = colorCount[i];
				flag = i;
			}
		}
		switch (flag)
		{
		case 0:
			_color[0] = OBJECT_COLOR_RED;
			break;
		case 1:
			_color[0] = OBJECT_COLOR_ORANGE;
			break;
		case 2:
			_color[0] = OBJECT_COLOR_YELLOW;
			break;
		case 3:
			_color[0] = OBJECT_COLOR_GREEN;
			break;
		case 4:
			_color[0] = OBJECT_COLOR_CYAN;
			break;
		case 5:
			_color[0] = OBJECT_COLOR_BLUE;
			break;
		case 6:
			_color[0] = OBJECT_COLOR_PURPLE;
			break;
		case 7:
			_color[0] = OBJECT_COLOR_WHITE;
			break;
		case 8:
			_color[0] = OBJECT_COLOR_BLACK;
			break;
		case 9:
			_color[0] = OBJECT_COLOR_GRAY;
			break;
		default:
			_color[0] = OBJECT_COLOR_WHITE;
			break;
		}


		//�ж������°벿��
		for (int i = 0; i < 10; i++)
		{
			colorCount[i] = 0;
		}
		maxTemp = 0;
		for (int i = (int)(sbgr[0].rows / 2); i < sbgr[0].rows; i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					if ((p0[j] >= 0 && p0[j] <= 10 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255) || (p0[j] >= 156 && p0[j] <= 180 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255))
					{
						colorCount[0] += 2;//��ɫred
					}
					else if (p0[j] >= 11 && p0[j] <= 25 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[1] += 2;//��ɫorange
					}
					else if (p0[j] >= 26 && p0[j] <= 34 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[2] += 2;//��ɫyellow
					}
					else if (p0[j] >= 35 && p0[j] <= 77 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[3] += 2;//��ɫgreen
					}
					else if (p0[j] >= 78 && p0[j] <= 99 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[4] += 2;//��ɫcyan
					}
					else if (p0[j] >= 100 && p0[j] <= 124 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[5] += 2;//��ɫblue
					}
					else if (p0[j] >= 125 && p0[j] <= 155 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[6] += 2;//��ɫpurple
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 30 && p2[j] >= whiteGrayThreshold && p2[j] <= 255)
					{
						colorCount[7]++;//��ɫwhite
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 255 && p2[j] >= 0 && p2[j] <= blackGrayThresholdV)
					{
						colorCount[8]++;//��ɫblack
					}
					else
					{
						colorCount[9]++;//��ɫgray;
					}
				}

			}

		}
		maxTemp = colorCount[0];
		flag = 0;
		for (int i = 1; i < 10; i++)
		{
			if (maxTemp <= colorCount[i])
			{
				maxTemp = colorCount[i];
				flag = i;
			}
		}
		switch (flag)
		{
		case 0:
			_color[1] = OBJECT_COLOR_RED;
			break;
		case 1:
			_color[1] = OBJECT_COLOR_ORANGE;
			break;
		case 2:
			_color[1] = OBJECT_COLOR_YELLOW;
			break;
		case 3:
			_color[1] = OBJECT_COLOR_GREEN;
			break;
		case 4:
			_color[1] = OBJECT_COLOR_CYAN;
			break;
		case 5:
			_color[1] = OBJECT_COLOR_BLUE;
			break;
		case 6:
			_color[1] = OBJECT_COLOR_PURPLE;
			break;
		case 7:
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		case 8:
			_color[1] = OBJECT_COLOR_BLACK;
			break;
		case 9:
			_color[1] = OBJECT_COLOR_GRAY;
			break;
		default:
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		}
	}
	else//����ʱ�� class==2
	{
		for (int i = 0; i < sbgr[0].rows; i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					if ((p0[j] >= 0 && p0[j] <= 10 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255) || (p0[j] >= 156 && p0[j] <= 180 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255))
					{
						colorCount[0] += 2;//��ɫred
					}
					else if (p0[j] >= 11 && p0[j] <= 25 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[1] += 2;//��ɫorange
					}
					else if (p0[j] >= 26 && p0[j] <= 34 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[2] += 2;//��ɫyellow
					}
					else if (p0[j] >= 35 && p0[j] <= 77 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[3] += 2;//��ɫgreen
					}
					else if (p0[j] >= 78 && p0[j] <= 99 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[4] += 2;//��ɫcyan
					}
					else if (p0[j] >= 100 && p0[j] <= 124 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[5] += 2;//��ɫblue
					}
					else if (p0[j] >= 125 && p0[j] <= 155 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[6] += 2;//��ɫpurple
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 30 && p2[j] >= whiteGrayThreshold && p2[j] <= 255)
					{
						colorCount[7]++;//��ɫwhite
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 255 && p2[j] >= 0 && p2[j] <= blackGrayThresholdV)
					{
						colorCount[8]++;//��ɫblack
					}
					else
					{
						colorCount[9]++;//��ɫblack;
					}
				}
			}

		}
		int maxTemp = colorCount[0];
		int flag = 0;
		for (int i = 1; i < 10; i++)
		{
			if (maxTemp <= colorCount[i])
			{
				maxTemp = colorCount[i];
				flag = i;
			}
		}
		switch (flag)
		{
		case 0:
			_color[0] = OBJECT_COLOR_WHITE;
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		case 8:
			_color[0] = OBJECT_COLOR_BLACK;
			_color[1] = OBJECT_COLOR_BLACK;
			break;
		case 9:
			_color[0] = OBJECT_COLOR_GRAY;
			_color[1] = OBJECT_COLOR_GRAY;
			break;
		default:
			_color[0] = OBJECT_COLOR_RED;
			_color[1] = OBJECT_COLOR_RED;
			break;
		case 1:
			_color[0] = OBJECT_COLOR_ORANGE;
			_color[1] = OBJECT_COLOR_ORANGE;
			break;
		case 2:
			_color[0] = OBJECT_COLOR_YELLOW;
			_color[1] = OBJECT_COLOR_YELLOW;
			break;
		case 3:
			_color[0] = OBJECT_COLOR_GREEN;
			_color[1] = OBJECT_COLOR_GREEN;
			break;
		case 4:
			_color[0] = OBJECT_COLOR_CYAN;
			_color[1] = OBJECT_COLOR_CYAN;
			break;
		case 5:
			_color[0] = OBJECT_COLOR_BLUE;
			_color[1] = OBJECT_COLOR_BLUE;
			break;
		case 6:
			_color[0] = OBJECT_COLOR_PURPLE;
			_color[1] = OBJECT_COLOR_PURPLE;
			break;
		case 7:
			_color[0] = OBJECT_COLOR_WHITE;
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		}
	}
};

void CColorAly::GetAverageHSV2(cv::Mat& _colorROI, const cv::Mat& _binROI, vector<ObjectColor> & _color, int _class)//���볤��Ϊ2����ɫ�����������������0Ϊ�ǳ���1Ϊ��
{
	int whiteGrayThreshold = 125;//HSV�׻���ɫ����V����ֵ��ԭ��Ϊ221
	int blackGrayThresholdV = 46;//HSV�ڻ���ɫ����V����ֵ��ԭ��Ϊ46
	Mat binImage = _binROI.clone();
	Mat image = _colorROI.clone();
	Mat ROI_HSV;
	Mat ROI = image;
	Mat binROI = binImage;

	std::vector<cv::Mat> sbgr(ROI.channels());//ͨ��������
	std::vector<cv::Mat> mbgr(ROI.channels());//ͨ���ϳ���
	//split(ROI, sbgr);
	//equalizeHist(sbgr[0], mbgr[0]);//����ͨ���ֱ�ֱ��ͼ���⻯
	//equalizeHist(sbgr[1], mbgr[1]);
	//equalizeHist(sbgr[2], mbgr[2]);
	//merge(mbgr, ROI);//����ͨ�����ºϳ�

	cvtColor(ROI, ROI_HSV, COLOR_BGR2HSV);//��ʱH 0-180;
	sbgr.clear();
	split(ROI_HSV, sbgr);//�ָ��Hͨ��

	int colorCount[10] = { 0 };//ͳ��ÿ����ɫ���ص������˳��Ϊ  ��Ȼ��������ϰ׺�

	if (_class == -1)//�ж�����
	{
		//ͳ�����ϰ벿�ֵ���ɫ
		for (int i = 0; i < (int)(sbgr[0].rows / 2); i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					if ((p0[j] >= 0 && p0[j] <= 10 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255) || (p0[j] >= 156 && p0[j] <= 180 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255))
					{
						colorCount[0] += 2;//��ɫred
					}
					else if (p0[j] >= 11 && p0[j] <= 25 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[1] += 2;//��ɫorange
					}
					else if (p0[j] >= 26 && p0[j] <= 34 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[2] += 2;//��ɫyellow
					}
					else if (p0[j] >= 35 && p0[j] <= 77 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[3] += 2;//��ɫgreen
					}
					else if (p0[j] >= 78 && p0[j] <= 99 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[4] += 2;//��ɫcyan
					}
					else if (p0[j] >= 100 && p0[j] <= 124 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[5] += 2;//��ɫblue
					}
					else if (p0[j] >= 125 && p0[j] <= 155 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[6] += 2;//��ɫpurple
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 30 && p2[j] >= whiteGrayThreshold && p2[j] <= 255)
					{
						colorCount[7]++;//��ɫwhite
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 255 && p2[j] >= 0 && p2[j] <= blackGrayThresholdV)
					{
						colorCount[8]++;//��ɫblack
					}
					else
					{
						colorCount[9]++;//��ɫgray;
					}
				}
			}

		}
		int maxTemp = colorCount[0];
		int flag = 0;
		for (int i = 1; i < 10; i++)
		{
			if (maxTemp <= colorCount[i])
			{
				maxTemp = colorCount[i];
				flag = i;
			}
		}
		switch (flag)
		{
		case 0:
			_color[0] = OBJECT_COLOR_RED;
			break;
		case 1:
			_color[0] = OBJECT_COLOR_ORANGE;
			break;
		case 2:
			_color[0] = OBJECT_COLOR_YELLOW;
			break;
		case 3:
			_color[0] = OBJECT_COLOR_GREEN;
			break;
		case 4:
			_color[0] = OBJECT_COLOR_CYAN;
			break;
		case 5:
			_color[0] = OBJECT_COLOR_BLUE;
			break;
		case 6:
			_color[0] = OBJECT_COLOR_PURPLE;
			break;
		case 7:
			_color[0] = OBJECT_COLOR_WHITE;
			break;
		case 8:
			_color[0] = OBJECT_COLOR_BLACK;
			break;
		case 9:
			_color[0] = OBJECT_COLOR_GRAY;
			break;
		default:
			_color[0] = OBJECT_COLOR_WHITE;
			break;
		}


		//�ж������°벿��
		for (int i = 0; i < 10; i++)
		{
			colorCount[i] = 0;
		}
		maxTemp = 0;
		for (int i = (int)(sbgr[0].rows / 2); i < sbgr[0].rows; i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					if ((p0[j] >= 0 && p0[j] <= 10 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255) || (p0[j] >= 156 && p0[j] <= 180 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255))
					{
						colorCount[0] += 2;//��ɫred
					}
					else if (p0[j] >= 11 && p0[j] <= 25 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[1] += 2;//��ɫorange
					}
					else if (p0[j] >= 26 && p0[j] <= 34 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[2] += 2;//��ɫyellow
					}
					else if (p0[j] >= 35 && p0[j] <= 77 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[3] += 2;//��ɫgreen
					}
					else if (p0[j] >= 78 && p0[j] <= 99 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[4] += 2;//��ɫcyan
					}
					else if (p0[j] >= 100 && p0[j] <= 124 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[5] += 2;//��ɫblue
					}
					else if (p0[j] >= 125 && p0[j] <= 155 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[6] += 2;//��ɫpurple
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 30 && p2[j] >= whiteGrayThreshold && p2[j] <= 255)
					{
						colorCount[7]++;//��ɫwhite
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 255 && p2[j] >= 0 && p2[j] <= blackGrayThresholdV)
					{
						colorCount[8]++;//��ɫblack
					}
					else
					{
						colorCount[9]++;//��ɫgray;
					}
				}

			}

		}
		maxTemp = colorCount[0];
		flag = 0;
		for (int i = 1; i < 10; i++)
		{
			if (maxTemp <= colorCount[i])
			{
				maxTemp = colorCount[i];
				flag = i;
			}
		}
		switch (flag)
		{
		case 0:
			_color[1] = OBJECT_COLOR_RED;
			break;
		case 1:
			_color[1] = OBJECT_COLOR_ORANGE;
			break;
		case 2:
			_color[1] = OBJECT_COLOR_YELLOW;
			break;
		case 3:
			_color[1] = OBJECT_COLOR_GREEN;
			break;
		case 4:
			_color[1] = OBJECT_COLOR_CYAN;
			break;
		case 5:
			_color[1] = OBJECT_COLOR_BLUE;
			break;
		case 6:
			_color[1] = OBJECT_COLOR_PURPLE;
			break;
		case 7:
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		case 8:
			_color[1] = OBJECT_COLOR_BLACK;
			break;
		case 9:
			_color[1] = OBJECT_COLOR_GRAY;
			break;
		default:
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		}
	}
	else//����ʱ�� class==2
	{
		for (int i = 0; i < sbgr[0].rows; i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					if ((p0[j] >= 0 && p0[j] <= 10 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255) || (p0[j] >= 156 && p0[j] <= 180 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255))
					{
						colorCount[0] += 2;//��ɫred
					}
					else if (p0[j] >= 11 && p0[j] <= 25 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[1] += 2;//��ɫorange
					}
					else if (p0[j] >= 26 && p0[j] <= 34 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[2] += 2;//��ɫyellow
					}
					else if (p0[j] >= 35 && p0[j] <= 77 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[3] += 2;//��ɫgreen
					}
					else if (p0[j] >= 78 && p0[j] <= 99 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[4] += 2;//��ɫcyan
					}
					else if (p0[j] >= 100 && p0[j] <= 124 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[5] += 2;//��ɫblue
					}
					else if (p0[j] >= 125 && p0[j] <= 155 && p1[j] >= 43 && p1[j] <= 255 && p2[j] >= 46 && p2[j] <= 255)
					{
						colorCount[6] += 2;//��ɫpurple
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 30 && p2[j] >= whiteGrayThreshold && p2[j] <= 255)
					{
						colorCount[7]++;//��ɫwhite
					}
					else if (p0[j] >= 0 && p0[j] <= 180 && p1[j] >= 0 && p1[j] <= 255 && p2[j] >= 0 && p2[j] <= blackGrayThresholdV)
					{
						colorCount[8]++;//��ɫblack
					}
					else
					{
						colorCount[9]++;//��ɫblack;
					}
				}
			}

		}
		int maxTemp = colorCount[0];
		int flag = 0;
		for (int i = 1; i < 10; i++)
		{
			if (maxTemp <= colorCount[i])
			{
				maxTemp = colorCount[i];
				flag = i;
			}
		}
		switch (flag)
		{
		case 0:
			_color[0] = OBJECT_COLOR_WHITE;
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		case 8:
			_color[0] = OBJECT_COLOR_BLACK;
			_color[1] = OBJECT_COLOR_BLACK;
			break;
		case 9:
			_color[0] = OBJECT_COLOR_GRAY;
			_color[1] = OBJECT_COLOR_GRAY;
			break;
		default:
			_color[0] = OBJECT_COLOR_RED;
			_color[1] = OBJECT_COLOR_RED;
			break;
		case 1:
			_color[0] = OBJECT_COLOR_ORANGE;
			_color[1] = OBJECT_COLOR_ORANGE;
			break;
		case 2:
			_color[0] = OBJECT_COLOR_YELLOW;
			_color[1] = OBJECT_COLOR_YELLOW;
			break;
		case 3:
			_color[0] = OBJECT_COLOR_GREEN;
			_color[1] = OBJECT_COLOR_GREEN;
			break;
		case 4:
			_color[0] = OBJECT_COLOR_CYAN;
			_color[1] = OBJECT_COLOR_CYAN;
			break;
		case 5:
			_color[0] = OBJECT_COLOR_BLUE;
			_color[1] = OBJECT_COLOR_BLUE;
			break;
		case 6:
			_color[0] = OBJECT_COLOR_PURPLE;
			_color[1] = OBJECT_COLOR_PURPLE;
			break;
		case 7:
			_color[0] = OBJECT_COLOR_WHITE;
			_color[1] = OBJECT_COLOR_WHITE;
			break;
		}
	}
};

//���RGB��ֵ
void CColorAly::GetAverageHSV3(cv::Mat& _colorROI, const cv::Mat& _binROI, vector<Vec3d> & _color, int _class)//���볤��Ϊ2����ɫ�����������������0Ϊ�ǳ���1Ϊ��
{
	Mat ROI_HSV;
	Mat ROI = _colorROI.clone();
	Mat binROI = _binROI.clone();
	std::vector<cv::Mat> sbgr(ROI.channels());//ͨ��������
	std::vector<cv::Mat> mbgr(ROI.channels());//ͨ���ϳ���
	//split(ROI, sbgr);
	//equalizeHist(sbgr[0], mbgr[0]);//����ͨ���ֱ�ֱ��ͼ���⻯
	//equalizeHist(sbgr[1], mbgr[1]);
	//equalizeHist(sbgr[2], mbgr[2]);
	//merge(mbgr, ROI);//����ͨ�����ºϳ�
	cvtColor(ROI, ROI_HSV, COLOR_BGR2HSV);//��ʱH 0-180;
	sbgr.clear();
	split(ROI_HSV, sbgr);//�ָ��HSVͨ��

	double _averageHSV_top[3];//�洢���ϰ벿��HSV����ͨ��ƽ��ֵ,˳��ΪHSV
	double _averageHSV_bottom[3];//�洢���°벿��HSV����ͨ��ƽ��ֵ
	double _averageHSV_car[3];//�洢����HSV����ͨ��ƽ��ֵ

	double H_Sum[2] = { 0, 0 };//1��������ͨ�������е��HSVֵ�úͣ������°�������_Sum[0]Ϊ�ϰ���2���ǳ���ֻ��_Sum[0]
	double S_Sum[2] = { 0, 0 };
	double V_Sum[2] = { 0, 0 };
	int ForgPointSum[2] = { 0, 0 };//1���ˣ�ͳ�������°���ǰ����ĸ�����ForgPointSum[0]Ϊ�ϰ���;2������ֻ��ForgPointSum[0]

	if (_class == -1)//�ж�����
	{
		//ͳ�����ϰ벿�ֵ���ɫ
		for (int i = 0; i < (int)(sbgr[0].rows / 2); i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					H_Sum[0] += p0[j];
					S_Sum[0] += p1[j];
					V_Sum[0] += p2[j];
					ForgPointSum[0]++;
				}
			}
		}
		//ͳ�����°벿�ֵ���ɫ
		for (int i = (int)(sbgr[0].rows / 2); i < sbgr[0].rows; i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					H_Sum[1] += p0[j];
					S_Sum[1] += p1[j];
					V_Sum[1] += p2[j];
					ForgPointSum[1]++;
				}
			}
		}
		//��������HSVƽ��ֵ
		_averageHSV_top[0] = H_Sum[0] / ForgPointSum[0];
		_averageHSV_top[1] = S_Sum[0] / ForgPointSum[0];
		_averageHSV_top[2] = V_Sum[0] / ForgPointSum[0];
		_averageHSV_bottom[0] = H_Sum[1] / ForgPointSum[1];
		_averageHSV_bottom[1] = S_Sum[1] / ForgPointSum[1];
		_averageHSV_bottom[2] = V_Sum[1] / ForgPointSum[1];
		Vec3d temp1,temp2;//push���°���hsv
		temp1[0] = _averageHSV_top[0];
		temp1[1] = _averageHSV_top[1];
		temp1[2] = _averageHSV_top[2];
		temp2[0] = _averageHSV_bottom[0];
		temp2[1] = _averageHSV_bottom[1];
		temp2[2] = _averageHSV_bottom[2];
		_color.push_back(temp1);
		_color.push_back(temp2);
	}
	else//����ʱ�� class==2
	{
		for (int i = 0; i < sbgr[0].rows; i++)
		{
			uchar* p0 = sbgr[0].ptr<uchar>(i);
			uchar* p1 = sbgr[1].ptr<uchar>(i);
			uchar* p2 = sbgr[2].ptr<uchar>(i);
			uchar* bin = binROI.ptr<uchar>(i);
			for (int j = 0; j < sbgr[0].cols; j++)
			{
				if (bin[j] != 0)
				{
					H_Sum[0] += p0[j];
					S_Sum[0] += p1[j];
					V_Sum[0] += p2[j];
					ForgPointSum[0]++;
				}
			}
		}
		//���㳵��ƽ��HSVֵ
		_averageHSV_car[0] = H_Sum[0] / ForgPointSum[0];
		_averageHSV_car[1] = S_Sum[0] / ForgPointSum[0];
		_averageHSV_car[2] = V_Sum[0] / ForgPointSum[0];

		Vec3d temp1;
		temp1[0] = _averageHSV_car[0];
		temp1[1] = _averageHSV_car[1];
		temp1[2] = _averageHSV_car[2];
		_color.push_back(temp1);
		_color.push_back(temp1);
	}
};