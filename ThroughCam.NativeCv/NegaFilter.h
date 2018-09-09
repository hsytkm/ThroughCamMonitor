#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

class NegaFilter {
private:
	int x;

public:
	NegaFilter() {}
	~NegaFilter() {}

	void Processing(cv::Mat* mat) {
		*mat = ~(*mat);
	}
};
