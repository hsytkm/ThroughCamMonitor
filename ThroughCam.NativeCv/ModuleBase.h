#pragma once
#include <opencv2/opencv.hpp>

class ModuleBase {
public:
	virtual ~ModuleBase() {}

	virtual void Processing(cv::Mat* mat) = 0;

	virtual int GetRectCount() = 0;
	virtual cv::Rect GetRectData(int i) = 0;

};
