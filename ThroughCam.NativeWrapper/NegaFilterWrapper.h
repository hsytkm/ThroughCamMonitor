#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "NegaFilter.h"

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

		// マネージド及びアンマネージドリソースの解放
		~NegaFilterWrapper() { this->!NegaFilterWrapper(); }

		// アンマネージドリソースの解放
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
