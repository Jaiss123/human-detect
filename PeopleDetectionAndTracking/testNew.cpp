#include "stdafx.h"
#include "VideoProcessor.h"

int main()
{
	//GetInfoCallBackFun clsGetInfoCallBackFun;
	char * path = "../output";
	bool bDistin;
	int objClass;
	string objInfo;
	unsigned int frame_count = 0;
	int frame_drump = 5;

	VideoProcessor videoProcessor;
	cv::VideoCapture VCcapture;

	//VCcapture.open("../VideoProcessor/images/视频2.mp4");
	//VCcapture.open("../PeopleDetectionAndTracking/images/视频4-1-4m.mp4");
	VCcapture.open("6.MP4");
	long totalFrameNumber = VCcapture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "整个视频共" << totalFrameNumber << "帧" << endl;

	//获取帧率  
	double rate = VCcapture.get(CV_CAP_PROP_FPS);
	cout << "帧率为:" << rate << endl;

	

	if (!VCcapture.isOpened())
	{
		std::cout << "视频打开失败！" << std::endl;
		return -1;
	}
	

	cv::Mat temp_frame;
	VCcapture.set(CAP_PROP_POS_FRAMES,50);
	VCcapture >> temp_frame;
	
	long nCount = 1;
	
		std::cout << " Current frame: " << nCount << std::endl;
		
		

	//GetInfoCallBackFun clsGetInfoCallBackFun;
	//videoProcessor.Init(clsGetInfoCallBackFun, 1080, 1920, 3, 0, 540, 1905, 540, 900, 0, 900, 1020);
	//videoProcessor.Init(clsGetInfoCallBackFun, false, false, path,temp_frame.rows, temp_frame.cols, 3);
	videoProcessor.Init(false, false, path, temp_frame.rows, temp_frame.cols, 5);

	while (VCcapture.read(temp_frame))
	{
		++frame_count;
		std::cout << " Current frame: " << nCount << std::endl;
		if (frame_count % frame_drump == 0)
		{
			videoProcessor.Run(temp_frame.data, temp_frame.rows * temp_frame.cols * 3, objInfo, objClass);
			
		}
		nCount++;
	}
	
	return 0;

}