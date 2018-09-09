#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "FaceDetect.h"

using namespace System;

namespace ThroughCamVideoCaptureWrapper {
	public ref class FaceDetectWrapper
	{
	private:
		bool isResponsible;
		FaceDetect *p;

	public:
		FaceDetectWrapper() : isResponsible{ true }, p{ new FaceDetect() } {}
		//FaceDetectWrapper(FaceDetect^ obj) : isResponsible{ true }, p{ new FaceDetect(obj->p) } {}
		FaceDetectWrapper(FaceDetect *p) : isResponsible{ false }, p{ p } {}

		// マネージド及びアンマネージドリソースの解放
		~FaceDetectWrapper() { this->!FaceDetectWrapper(); }

		// アンマネージドリソースの解放
		!FaceDetectWrapper()
		{
			if (isResponsible && p)
			{
				delete p;
				p = nullptr;
			}
		}

		void Processing(System::IntPtr ptr) {
			cv::Mat* src = reinterpret_cast<cv::Mat*>(ptr.ToPointer());
			p->Processing(src);
		}

	};
}
