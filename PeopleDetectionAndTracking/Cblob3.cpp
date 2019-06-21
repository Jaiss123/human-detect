#include "stdafx.h"
#include "Cblob3.h"

///����Ϊ���������---------------------------------------------------------------------------------------------------------------

//���캯������ʼ��������Ϊ0���ҵ��������
CBlob::CBlob()
{
	m_objCount = 0;
	//m_pvclassify.ImportClassify0();
	
}

//void CBlob::Init(GetInfoCallBackFun clsGetInfoCallBackFun, bool bLPR, bool bFace, string strPathName, int TrackPointNumThresh, int ContoursRectNumThresh, int DistanceThresh, int DistanceThreshKal, int nResizeRatio)
void CBlob::Init(bool bLPR, bool bFace, string strPathName, int TrackPointNumThresh, int ContoursRectNumThresh, int DistanceThresh, int DistanceThreshKal, int nResizeRatio)
{
	//m_clsGetInfoCallBackFun = clsGetInfoCallBackFun;
	m_bLPR = bLPR;
	m_bFace = bFace;
	m_nResizeRatio = nResizeRatio;
	m_strPathName = strPathName;
	m_para.Init(TrackPointNumThresh, ContoursRectNumThresh, DistanceThresh, DistanceThreshKal, nResizeRatio);
}

int CBlob::GetObjNum()
{
	int count = 0;
	for (auto it = m_listObjects.begin(); it != m_listObjects.end();++it)
	{
		if (it->m_objID != -1)
		{
			++count;
		}
	}
	return count;
}

void CBlob::BlobDetecterUseRect(const cv::Mat& _binImg, cv::Mat& _colorImg,std::vector<cv::Rect>& _input_rects)
{
	m_centers.clear();
	m_rects.clear();
	m_colorsRGB.clear();

	for (auto it = _input_rects.begin(); it != _input_rects.end(); ++it)
	{
		m_rects.push_back(*it);

		cv::Point center;		
		center.x = it->x + it->width / 2;//���ε����ĵ�
		center.y = it->y + it->height / 2;
		m_centers.push_back(center);//������Ӿ��ε����ĵ�

		vector<Vec3d> colorRGB;
		m_CColorAly.GetAverageHSV3(_colorImg(*it), _binImg(*it), colorRGB, -1);
		m_colorsRGB.push_back(colorRGB);
	}
}

void CBlob::BlobDetecter(const cv::Mat& _binImg, cv::Mat& _colorImg)
{
	cv::Mat src = _binImg.clone();
	//cv::Mat srcROI = src(cv::Rect(0, src.rows * 3 / 10, src.cols, src.rows * 7 / 10));//�е�ͼ��ı�Ե5%
	//cv::Mat outROI = _outputImg(cv::Rect(0, _outputImg.rows * 3 / 10, _outputImg.cols, _outputImg.rows * 7 / 10));//Ϊ�����귽�㣬���ͼ��ҲҪ��ȡROI

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(src, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

	//m_goodContours.clear();//����ÿһ֡ͼ�񣬶�Ҫ���֮ǰ�ĵ�
	m_centers.clear();
	m_rects.clear();
	//m_PorV.clear();
	m_colorsRGB.clear();
	//����ɸѡ��ֻ�������ο����30*30�����������ĵ�;��ο�
	for (auto i = contours.begin(); i != contours.end(); ++i)
	{
		cv::Rect temRect = cv::boundingRect(*i);//����������Ӿ���
		//����������������ֵ�����е������ϲ���30%
		//if (temRect.width > m_para.CBlob_ContoursRectNumThresh && temRect.height > m_para.CBlob_ContoursRectNumThresh && temRect.y > _binImg.rows * 3 / 10)
		if (temRect.width > m_para.CBlob_ContoursRectNumThresh && temRect.height > m_para.CBlob_ContoursRectNumThresh )
		{
			//m_goodContours.push_back(*i);
			m_rects.push_back(temRect);
			cv::Point center;
			int xSum(0), ySum(0);
			for (auto j = i->begin(); j != i->end(); ++j)
			{
				xSum += j->x;
				ySum += j->y;
			}
			center.x = (int)(xSum / i->size());//���������ĵ�
			center.y = (int)(ySum / i->size());
			//center.x = temRect.x + temRect.width / 2;//���ε����ĵ�
			//center.y = temRect.y + temRect.height / 2;
			m_centers.push_back(center);//������Ӿ��ε����ĵ�
		
			//m_PorV.push_back(m_pvclassify.GetObjClassify(*i, temRect));

			vector<Vec3d> colorRGB;
			m_CColorAly.GetAverageHSV3( _colorImg(temRect), _binImg(temRect), colorRGB,-1);
			m_colorsRGB.push_back(colorRGB);
		}
	}

	//m_centers,m_goodContours,m_rects��Ԫ�ظ���Ӧһ��
	//cout<<"��ǰ֡�����ĵ���� = "<<m_centers.size()<<endl;
}

//Ѱ��m_centers����pLast�����һ�㣬������������
void CBlob::FindNearstPoint(cv::Point pLast, int& id)
{
	double dist = 0;
	double minDist = 10000;
	int count = 0;
	//	if (m_centers.empty())cout << "m_centersΪ��" << endl;
	for (auto i = m_centers.begin(); i != m_centers.end(); ++i)//���ȱ�����ǰ֡�������ĵ㼯����ȡ����������С����
	{
		dist = sqrt((pLast.x - (i->x))*(pLast.x - (i->x)) + (pLast.y - (i->y))*(pLast.y - (i->y)));

		if (dist < minDist )
		{
			minDist = dist;
			id = count;
		}
		++count;
	}
	if (minDist < m_para.CBlob_DistanceThresh)//�������������ĵ㼯��С��������Ҫ������Ӧλ�õı����Ϊ0����ʾ�õ��ѱ��ù�
	{
	}
	else//�������̫�󣬻��߸���û�о������ĵ㣬����ǰ֡û������
	{
		id = -1;
	}
}
void CBlob::FindNearstPointKal(cv::Point pLast, int& id)
{
	double dist = 0;
	double minDist = 10000;
	int count = 0;
	//	if (m_centers.empty())cout << "m_centersΪ��" << endl;
	for (auto i = m_centers.begin(); i != m_centers.end(); ++i)
	{
		dist = sqrt((pLast.x - (i->x))*(pLast.x - (i->x)) + (pLast.y - (i->y))*(pLast.y - (i->y)));

		if (dist < minDist)
		{
			minDist = dist;
			id = count;
		}
		++count;
	}
	if (minDist < m_para.CBlob_DistanceThreshKal)//����һ����������ͬ��ֻ������ĵ�Ϊ�������˲���Ԥ��㣬�ڸ�Ԥ��㸽������
	{
	}
	else
	{
		id = -1;
	}
}

//void CBlob::ClassifyCenters(const cv::Mat& _binImg, cv::Mat& _colorImg, cv::Mat& _ori_image, bool& _bObjectDistinguish, string& _strObjectInfo,int& _nObjectClass)
void CBlob::ClassifyCenters(const cv::Mat& _binImg, cv::Mat& _colorImg, cv::Mat& _ori_image, string& _strObjectInfo, int& _nObjectClass)
{
	/*_bObjectDistinguish = false;*/
	//_strLP = "";

	//cv::Mat outROI = _outputImg(cv::Rect(0, _outputImg.rows * 3 / 10, _outputImg.cols, _outputImg.rows * 7 / 10));
	if (m_listObjects.empty())//����洢���������Ϊ�գ������õ�ǰ֡�ľ������ĵ㼯ȥ��ʼ����������,������ο�
	{
		for (unsigned int i = 0; i != m_centers.size(); ++i)//ÿһ�㶼��һ���µ�����
		{
			ObjectAndKF obj1;
			obj1.m_vecCenters.push_back(cv::Point(m_centers.at(i).x, m_centers.at(i).y));
			obj1.m_rect = m_rects.at(i);
			//obj1.m_Contours = m_goodContours.at(i);
			//obj1.m_class = m_PorV.at(i);
			obj1.m_colorH = m_colorsRGB.at(i);
			//obj1.m_allClassifyResults += obj1.m_class; //�ۼ����
			obj1.UpdatePerfectImages(_binImg, _colorImg, _ori_image,m_nResizeRatio);//�������ͼ��

			obj1.Init(m_clsGetInfoCallBackFun, m_strPathName, m_bLPR,m_bFace);//���������ĵ�һ�����ĵ�λ�ú󣬳�ʼ���俨�����˲���
			m_listObjects.push_back(obj1);
		}
	}

	else//�����������Ԫ�أ��������һ֡������
	{

		for (auto it = m_listObjects.begin(); it != m_listObjects.end();)//���������е�ÿһ���������
		{
			if (it->m_vecCenters.size() ==1)//������������ֻ������һ��λ�õ㣬����ʹ�ÿ������˲�
			{
				cv::Point pLast = it->m_vecCenters.back();//�õ��б�ǰobj�����һ����
				int id;
				FindNearstPoint(pLast, id);//Ѱ�Һ���һ������ĵ�ǰ֡�еĵ㣬��Ϊ����һ��

				if (id == -1)//���û�ҵ�������Ϊ�����Ѿ���ʧ����ɾ�������еĸ���
				{
					////������岻��ͼ���Ե�����������id�Ų�Ϊ-1������Ϊ����ʱ��ʧ
					//if (it->m_objID != -1 && pLast.x > _outputImg.cols / 10 && pLast.x<_outputImg.cols * 9 / 10 && pLast.y>_outputImg.rows / 10 && pLast.y < _outputImg.rows * 9 / 10)
					//{
					//	m_listVanishObj.push_back(*it);
					//	it = m_listObjects.erase(it);
					//}
					//else//������Ϊ���ƶ����˻���
					//{
						it = m_listObjects.erase(it);
					//}
				}
				else//����ҵ��ˣ��򽫵ڶ�����������������������Ӧ���ο���£��������������������˲��������Ҵӵ�ǰ֡��ɾ���Ѿ�ʹ���˵����ĵ�
				{
					it->m_vecCenters.push_back(m_centers.at(id));
					it->m_rect = m_rects.at(id);
					//it->m_Contours = m_goodContours.at(id);
					//it->m_class = m_PorV.at(id);
					//it->m_colorH = m_colorsRGB.at(id);
					//it->m_allClassifyResults += it->m_class; //�ۼ����
					it->UpdatePerfectImages(_binImg, _colorImg, _ori_image, m_para.m_nResizeRatio);//�������ͼ��

					m_centers.erase(m_centers.begin() + id);//�ڵ�ǰ֡�����ĵ㼯����Ӿ��μ�ɾ���Ѿ�ʹ�ù��ĵ�;���
					m_rects.erase(m_rects.begin() + id);
					//m_goodContours.erase(m_goodContours.begin() + id);
					//m_PorV.erase(m_PorV.begin() + id);
					m_colorsRGB.erase(m_colorsRGB.begin() + id);

					it->Predict();
					it->Correct(1);
					++it;
				}
			}
			else//���������������2�����ϵ�λ�õ㣬�����ʹ�ÿ������˲���
			{
				cv::Point prePoint = it->Predict();//Ԥ������ǰ֡��һ���λ��

               //   cv::circle(outROI, prePoint, 5, cv::Scalar(0, 255, 255), 3, 8);//����Ԥ���ĵ�

				int id;
				FindNearstPointKal(prePoint, id);//��Ԥ����λ�ø���Ѱ����ʵ�ĵ��λ��

				if (id == -1)//���û�ҵ�������Ϊ�����Ѿ���ʧ����ɾ�������еĸ���
				{
					//������岻��ͼ���Ե�����������id�Ų�Ϊ-1���������б�ţ�����Ϊ����ʱ��ʧ����idΪ-1����ʱ���廹�������Ǹ���
					//if (it->m_objID != -1 && prePoint.x > _outputImg.cols / 10 && prePoint.x<_outputImg.cols * 9 / 10 && prePoint.y>_outputImg.rows / 10 && prePoint.y < _outputImg.rows * 9 / 10)
					//{
					//	m_listVanishObj.push_back(*it);
					//	it = m_listObjects.erase(it);
					//}
					//else//������Ϊ���ƶ����˻���
					//{
					if (it->m_objID != -1)
					{
						//it->GetFinalOBjInfo(_bObjectDistinguish, _strObjectInfo, _nObjectClass); //�����뿪���棬����������ͼ�����Ϣ
						it->GetFinalOBjInfo(_strObjectInfo, _nObjectClass); //�����뿪���棬����������ͼ�����Ϣ
					}
					it = m_listObjects.erase(it);
					//}
				}
				else//����ҵ��ˣ��������������������������Ӧ���ο���£��������������������˲���
				{
					it->m_vecCenters.push_back(m_centers.at(id));
					it->m_rect = m_rects.at(id);
					//it->m_Contours = m_goodContours.at(id);
					//it->m_class = m_PorV.at(id);
					//it->m_colorH = m_colorsRGB.at(id);
					//it->m_allClassifyResults += it->m_class; //�ۼ����
					it->UpdatePerfectImages(_binImg, _colorImg, _ori_image, m_para.m_nResizeRatio);//�������ͼ��

					m_centers.erase(m_centers.begin() + id);//�ڵ�ǰ֡�����ĵ㼯����Ӿ��μ�ɾ���Ѿ�ʹ�ù��ĵ�;���
					m_rects.erase(m_rects.begin() + id);
					//m_goodContours.erase(m_goodContours.begin() + id);
					//m_PorV.erase(m_PorV.begin() + id);
					m_colorsRGB.erase(m_colorsRGB.begin() + id);

					it->Correct((int)it->m_vecCenters.size()-1);
					//������켣�㹻����������һ��id�ţ�������Ϊ�Ǹ��ţ�������������
					if (it->m_vecCenters.size() > m_para.CBlob_TrackPointNumThresh && it->m_objID == -1)
					{
						time_t now = 0;
						//it->m_objID = (long)time(&now) + (++m_objCount);
						it->m_objID = (++m_objCount);
					}
					//�����˳�������������
					//if (it->m_objID != -1)
					//{
					//	m_pvclassify.GetSamples(*it);
					//}

					++it;
				}
			}
		}

		for (unsigned int i = 0; i < m_centers.size(); ++i)//�������ĵ㼯��ʣ�µĵ㣬��Ϊ�����Ǳ�֡���³��ֵ���������ĵ㣬�����֮ǰ������ʧ������
		{
			ObjectAndKF obj2;//�򴴽��µ��������
			obj2.m_vecCenters.push_back(cv::Point(m_centers[i].x,m_centers[i].y));
			obj2.m_rect = m_rects[i];
			//obj2.m_Contours = m_goodContours[i];
			//obj2.m_class = m_PorV[i];
			obj2.m_colorH = m_colorsRGB[i];
			//obj2.m_allClassifyResults += obj2.m_class; //�ۼ����
			obj2.UpdatePerfectImages(_binImg, _colorImg, _ori_image, m_para.m_nResizeRatio);//�������ͼ��

			obj2.Init(m_clsGetInfoCallBackFun, m_strPathName, m_bLPR, m_bFace);
			m_listObjects.push_back(obj2);//���ö����������

		}
	}

	//cout << "list�Ĵ�С = " << m_listObjects.size() << endl;
	//cout << "vinash�Ĵ�С = " << m_listVanishObj.size() << endl;
}

void CBlob::DrawPaths(cv::Mat& _outputImg)
{
	//��������ԭ�򣬻�ͼʱҲӦȡ��ROI
	cv::Mat outROI = _outputImg(cv::Rect(0, _outputImg.rows* 3/10, _outputImg.cols , _outputImg.rows * 7 / 10));
	for (auto lisIt = m_listObjects.begin(); lisIt != m_listObjects.end(); ++lisIt)//���������еĸ��㣬ÿ������ĵ��������ֱ��
	{
		if (lisIt->m_vecCenters.size() >m_para.CBlob_TrackPointNumThresh)//ɸѡȥ����10���켣������壬��Ϊ�Ǹ���
		{
			//for (unsigned int i = 0; i < lisIt->m_vecCenters.size(); ++i)
			//{
			//	if (i>0)
			//	{
			//		cv::line(_outputImg, lisIt->m_vecCenters.at(i - 1), lisIt->m_vecCenters.at(i), cv::Scalar(0, 0, 255), 2, 8);//ÿһ֡����һ���������й켣��������
			//	}
			//}
			cv::circle(_outputImg, lisIt->m_vecCenters.at(lisIt->m_vecCenters.size() - 1), 4, cv::Scalar(0, 0, 255), 3, 8);//�����������ĵ�

			cv::rectangle(_outputImg, lisIt->m_rect, cv::Scalar(255, 0, 0), 2, 8);//�������������Ӿ���

			/*std::vector<std::vector<cv::Point>> conts;
			conts.push_back(lisIt->m_Contours);
			cv::drawContours(outROI, conts, -1, cv::Scalar(255, 0, 0), 2, 8);*/

			ostringstream text;
			ostringstream textRGB;
			//if (lisIt->m_class == -1)
			if (true)
			{
				text <<"P"<< lisIt->m_objID << "(" << lisIt->m_vecCenters.at(lisIt->m_vecCenters.size() - 1).x << "," << lisIt->m_vecCenters.at(lisIt->m_vecCenters.size() - 1).y << ")";
				cv::Size textsize = getTextSize(text.str(), CV_FONT_HERSHEY_SIMPLEX, 0.5, 2, 0);
				cv::putText(_outputImg, text.str(), cvPoint(lisIt->m_rect.x + lisIt->m_rect.width, lisIt->m_rect.y - 3), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0), 2, 8);
				textRGB << "(" << "(" << lisIt->m_colorH.at(0)[0] << "," << lisIt->m_colorH.at(0)[1] << "," << lisIt->m_colorH.at(0)[2] << ")" << "," << "(" << lisIt->m_colorH.at(1)[0] << "," << lisIt->m_colorH.at(1)[1] << "," << lisIt->m_colorH.at(1)[2] << ")" << ")";
				textsize = getTextSize(textRGB.str(), CV_FONT_HERSHEY_SIMPLEX, 0.5, 2, 0);
				//cv::putText(_outputImg, textRGB.str(), cvPoint(lisIt->m_rect.x + lisIt->m_rect.width, lisIt->m_rect.y + lisIt->m_rect.height + textsize.height + 3), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2, 8);
			}
			else
			{
				text <<"V"<< lisIt->m_objID << "(" << lisIt->m_vecCenters.at(lisIt->m_vecCenters.size() - 1).x << "," << lisIt->m_vecCenters.at(lisIt->m_vecCenters.size() - 1).y << ")";
				cv::Size textsize = getTextSize(text.str(), CV_FONT_HERSHEY_SIMPLEX, 0.5, 2, 0);
				cv::putText(_outputImg, text.str(), cvPoint(lisIt->m_rect.x + lisIt->m_rect.width, lisIt->m_rect.y - 3), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 2, 8);
				textRGB << "(" << lisIt->m_colorH.at(0)[0] << "," << lisIt->m_colorH.at(0)[1] << "," << lisIt->m_colorH.at(0)[2] << ")";
				//textRGB << "(" << ColorEnum2String(lisIt->m_colorH.at(0)) << "," << ColorEnum2String(lisIt->m_colorH.at(1)) << ")";
				textsize = getTextSize(textRGB.str(), CV_FONT_HERSHEY_SIMPLEX, 0.5, 2, 0);
				//cv::putText(_outputImg, textRGB.str(), cvPoint(lisIt->m_rect.x + lisIt->m_rect.width, lisIt->m_rect.y + lisIt->m_rect.height + textsize.height + 3), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2, 8);
			}
		}
	}

	//�����ǰ֡��Ŀ����
	ostringstream numText;
	numText << "num= " << m_objCount;
	cv::Size numTextsize = getTextSize(numText.str(), CV_FONT_HERSHEY_COMPLEX, 0.9, 2, 0);
	cv::putText(_outputImg, numText.str(), cvPoint(5, _outputImg.rows - 5), CV_FONT_HERSHEY_COMPLEX, 0.9, cv::Scalar(255, 0, 0), 2, 8);
}

//���ַ�����ʽ���ص�ǰ֡������Ϣ
void CBlob::GetObjInfo(string& _objInfo)
{
	ostringstream _objInfoStream;
	_objInfoStream << "objectnum:" << GetObjNum() << ";";
	int tempCount = 0;
	for (auto it = m_listObjects.begin(); it != m_listObjects.end(); ++it)
	{
		if (it->m_objID != -1)
		{
			++tempCount;
			_objInfoStream << "ID" << setfill('0') << setw(3) << tempCount << ":" << "object" << setfill('0') << setw(5) << it->m_objID << ";";
			_objInfoStream << "Type" << setfill('0') << setw(3) << tempCount << ":" << -1 << ";";
			_objInfoStream << "UpperPart" << setfill('0') << setw(3) << tempCount << ":" << "(" << it->m_colorH.at(0)[0] << "," << it->m_colorH.at(0)[1] << "," << it->m_colorH.at(0)[2] << ")" << ";";
			_objInfoStream << "LowerPart" << setfill('0') << setw(3) << tempCount << ":" << "(" << it->m_colorH.at(1)[0] << "," << it->m_colorH.at(1)[1] << "," << it->m_colorH.at(1)[2] << ")" << ";";
			_objInfoStream << "X" << setfill('0') << setw(3) << tempCount << ":" << ((it->m_vecCenters.back().x) * m_nResizeRatio) << ";";
			_objInfoStream << "Y" << setfill('0') << setw(3) << tempCount << ":" << ((it->m_vecCenters.back().y) * m_nResizeRatio) << ";";
		}
	}
	_objInfo = _objInfoStream.str();
}