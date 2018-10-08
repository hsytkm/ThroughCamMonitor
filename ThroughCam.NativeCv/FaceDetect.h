#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ModuleBase.h"

class FaceDetect : public ModuleBase {
private:
	const std::string cascade_file = "C:\\OpenCV\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";
	cv::CascadeClassifier cascade;
	std::vector<cv::Rect> *faceRects;

public:
	FaceDetect() :faceRects{ nullptr } {
		cascade.load(cascade_file);
	}

	~FaceDetect() {
		if (faceRects != nullptr) { delete faceRects; faceRects = nullptr; }
	}

	void Processing(cv::Mat* mat) {
#if true
		if (faceRects != nullptr) { delete faceRects; faceRects = nullptr; }
		faceRects = new std::vector<cv::Rect>();
		cascade.detectMultiScale(*mat, *faceRects, 1.1, 3, 0, cv::Size(20, 20));
#else
		std::vector<cv::Rect> faces;
		cascade.detectMultiScale(*mat, faces, 1.1, 3, 0, cv::Size(20, 20));

		for (uint i = 0; i < faces.size(); i++) {
			cv::rectangle(*mat,
				cv::Point(faces[i].x, faces[i].y),
				cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
				cv::Scalar(0, 200, 0), 3, CV_AA);
		}
#endif
	}

	int GetRectCount() {
		if (faceRects == nullptr) return 0;
		return faceRects->size();
	}

	cv::Rect GetRectData(int i) {
		if (GetRectCount() < i - 1) return cv::Rect();
		return faceRects->at(i);
	}


};
