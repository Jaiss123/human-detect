#include "stdafx.h"
#include "DetectionDef.h"

string ColorEnum2String(ObjectColor _color)
{
	string returnName = "ERROR";
	switch (_color)
	{
	case OBJECT_COLOR_RED:
		returnName = "RED";
		return returnName;
		break;
	case OBJECT_COLOR_ORANGE:
		returnName = "ORANGE";
		return returnName;
		break;
	case OBJECT_COLOR_YELLOW:
		returnName = "YELLOW";
		return returnName;
		break;
	case OBJECT_COLOR_GREEN:
		returnName = "GREEN";
		return returnName;
		break;
	case OBJECT_COLOR_BLUE:
		returnName = "BLUE";
		return returnName;
		break;
	case OBJECT_COLOR_CYAN:
		returnName = "CYAN";
		return returnName;
		break;
	case OBJECT_COLOR_PURPLE:
		returnName = "PURPLE";
		return returnName;
		break;
	case OBJECT_COLOR_BLACK:
		returnName = "BLACK";
		return returnName;
		break;
	case OBJECT_COLOR_WHITE:
		returnName = "WHITE";
		return returnName;
		break;
	case OBJECT_COLOR_GRAY:
		returnName = "GRAY";
		return returnName;
		break;
	default:
		return returnName;
		break;
	}
}

CPara::CPara()
{
	CBlob_TrackPointNumThresh = 15;//����켣������һ����Ŀ��Ϊ�Ǹ���
	CBlob_ContoursRectNumThresh = 10;//����ɸѡ��ȥ������С��4*resize_Ratio*4*resize_Ratio������
	CBlob_DistanceThresh = 50; //��֡���ĵ���С������ֵ
	CBlob_DistanceThreshKal = 96; //Ӧ�ÿ������˲�Ԥ��ʱ��Ԥ����͵�ǰ֡���ĵ���С������ֵ
	m_nResizeRatio = 2;//����ϵ��
}

void CPara::Init(int TrackPointNumThresh, int ContoursRectNumThresh, int DistanceThresh, int DistanceThreshKal, int ResizeRatio)
{
	CBlob_TrackPointNumThresh = TrackPointNumThresh;//����켣������һ����Ŀ��Ϊ�Ǹ���
	CBlob_ContoursRectNumThresh = ContoursRectNumThresh;//����ɸѡ��ȥ������С��4*resize_Ratio*4*resize_Ratio������
	CBlob_DistanceThresh = DistanceThresh; //��֡���ĵ���С������ֵ
	CBlob_DistanceThreshKal = DistanceThreshKal; //Ӧ�ÿ������˲�Ԥ��ʱ��Ԥ����͵�ǰ֡���ĵ���С������ֵ
	m_nResizeRatio = ResizeRatio;//����ϵ��
}

CPara::~CPara()
{
	CBlob_TrackPointNumThresh = 15;//����켣������һ����Ŀ��Ϊ�Ǹ���
	CBlob_ContoursRectNumThresh = 10;//����ɸѡ��ȥ������С��4*resize_Ratio*4*resize_Ratio������
	CBlob_DistanceThresh = 50; //��֡���ĵ���С������ֵ
	CBlob_DistanceThreshKal = 96; //Ӧ�ÿ������˲�Ԥ��ʱ��Ԥ����͵�ǰ֡���ĵ���С������ֵ
	m_nResizeRatio = 2;//����ϵ��
}