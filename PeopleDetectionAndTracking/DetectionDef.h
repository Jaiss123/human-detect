#ifndef DETECTIONDEF_H_
#define DETECTIONDEF_H_

#include <string>
using namespace std;
///��ɫ
enum ObjectColor
{
	OBJECT_COLOR_RED = 0,
	OBJECT_COLOR_ORANGE = 1,
	OBJECT_COLOR_YELLOW = 2,
	OBJECT_COLOR_GREEN = 3,
	OBJECT_COLOR_CYAN = 4,//��ɫ
	OBJECT_COLOR_BLUE = 5,
	OBJECT_COLOR_PURPLE = 6,
	OBJECT_COLOR_WHITE = 7,
	OBJECT_COLOR_BLACK = 8,
	OBJECT_COLOR_GRAY = 9,

};

string ColorEnum2String(ObjectColor _color);

///�����࣬���в������洢������
class CPara
{
public:
	unsigned short CBlob_TrackPointNumThresh ;//����켣������һ����Ŀ��Ϊ�Ǹ���
	unsigned short CBlob_ContoursRectNumThresh ;//����ɸѡ��ȥ������С��20*20������
	unsigned short CBlob_DistanceThresh ; //��֡���ĵ���С������ֵ
	unsigned short CBlob_DistanceThreshKal ; //Ӧ�ÿ������˲�Ԥ��ʱ��Ԥ����͵�ǰ֡���ĵ���С������ֵ

	unsigned short m_nResizeRatio;//����ϵ��
public:
	CPara();//���캯������ʼ���б���ֵ
	void Init(int TrackPointNumThresh, int ContoursRectNumThresh, int DistanceThresh, int DistanceThreshKal, int ResizeRatio);
	~CPara();

};

#endif