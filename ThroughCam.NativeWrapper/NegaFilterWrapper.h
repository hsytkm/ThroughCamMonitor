#pragma once
#pragma unmanaged
#include <opencv2/opencv.hpp>
#include "NegaFilter.h"
#pragma managed
#include <iostream>

using namespace System;

namespace ThroughCamVideoCaptureWrapper {
	public ref class NegaFilterWrapper
	{
	private:
		bool isResponsible;
		NegaFilter *p;

	public:
		NegaFilterWrapper() : isResponsible{ true }, p{ new NegaFilter() } {}
		//NegaFilterWrapper(NegaFilter^ obj) : isResponsible{ true }, p{ new NegaFilter(obj->p) } {}
		NegaFilterWrapper(NegaFilter *p) : isResponsible{ false }, p{ p } {}

		// �}�l�[�W�h�y�уA���}�l�[�W�h���\�[�X�̉��
		~NegaFilterWrapper() { this->!NegaFilterWrapper(); }

		// �A���}�l�[�W�h���\�[�X�̉��
		!NegaFilterWrapper()
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
