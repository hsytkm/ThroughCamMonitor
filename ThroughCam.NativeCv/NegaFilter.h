#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ModuleBase.h"

class NegaFilter : public ModuleBase {
private:
	int x;

public:
	NegaFilter() {}
	~NegaFilter() {}

	void Processing(cv::Mat* mat) {
		*mat = ~(*mat);
	}
};
