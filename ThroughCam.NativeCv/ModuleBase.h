#pragma once
#include <opencv2/opencv.hpp>

class ModuleBase {
public:
	virtual ~ModuleBase() {}

	virtual void Processing(cv::Mat* mat) = 0;

};
