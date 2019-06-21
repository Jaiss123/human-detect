// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� YV12TORGB24_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// YV12TORGB24_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MTTAM_EXPORTS
#define MTTAM_API __declspec(dllexport)
#else
#define MTTAM_API __declspec(dllimport)
#endif
#include "VideoProcessor.h"
#include <opencv2/opencv.hpp>




//		1.�ϲ�ѽ�����ÿ֡RGB���ݴ�������DLL
//      2.DLL����ÿ֡ͼ�񲢴��������������ǰ�Ĺ��ܣ����ֲ��䣩����ԭʼĿ��ͼ�����������ڴ��С�
//      3.Ŀ����ʧʱ����Ŀ���ϵ����Ƶ���Ŀ�����У�飬ȷ��Ŀ���������ԣ�����ķ�ʽ��
//      4.���ж�Ϊ�˵�Ŀ��Ƚ�ѡ���������������Ƶ��Ŀ���������ʱ��ͼƬ������ͼƬ�ϵ�ԭʼĿ�������ȡ��������ΪͼƬ�����ڷ��������Ĳ����������һ�bool bObjectDistinguish������ֵΪ���ʾ������ȡ������ʶ�����
//      5.���ж�Ϊ����Ŀ�꽫��ԭʼͼƬ�пٳ���ͼƬ��������ʶ�������г���ʶ�����ʶ���������Ϣ��Ҳ�ڷ��������Ĳ����������һ�bool bObjectDistinguish������ֵΪ���ʾ������ȡ������ʶ�����
//      6.�ϲ�һ����⵽bool bObjectDistinguishΪ�漴���ñ�ʶ����Ϣ������������Ŀ����Ϣ��
//      7.����һ��Ŀ��ʶ����Ϣ�����������ú������������int nObjectType)��0����ʾ����ķ���ֵ��ϢΪ���������·������ʽʾ��:"PathName:..\output\2-people.bmp;"����1����ʾ����ķ���ֵ��ϢΪ������Ϣ����ʽʾ��:"PathName:..\output\2-��E 8HG64.bmp;LicensePlate:��E 8HG64;"����

//VideoProcessor*		m_pclsVideoProcessor = NULL;
VideoProcessor			m_clsVideoProcessor;
std::string				m_strObjInfo;

MTTAM_API bool		YV12ToBGR24(unsigned char* pYUV,unsigned char* pBGR24,int width,int height);

MTTAM_API bool		onMTTAMInit(GetInfoCallBackFun clsGetInfoCallBackFun, bool bLPR, bool bFace, char* pathName, int _height, int _width, int nResizeRatio);

MTTAM_API bool		onMTTAMInputFrame(unsigned char* pBGR24, int _size, char* strObjectInfo, int& nNum);
																																							
MTTAM_API bool		onMTTAMStop();
