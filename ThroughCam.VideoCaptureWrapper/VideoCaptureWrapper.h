#pragma once
#include "MyVideoCapture.h"

using namespace System;

namespace ThroughCamVideoCaptureWrapper {
	public ref class VideoCaptureWrapper
	{
	private:
		bool isResponsible;
		MyVideoCapture *p;

	public:
		VideoCaptureWrapper() : isResponsible{ true }, p{ new MyVideoCapture() } {}
		//VideoCaptureWrapper(MyVideoCapture^ obj) : isResponsible{ true }, p{ new MyVideoCapture(obj->p) } {}
		VideoCaptureWrapper(MyVideoCapture *p) : isResponsible { false }, p{ p } {}

		// マネージド及びアンマネージドリソースの解放
		~VideoCaptureWrapper() { this->!VideoCaptureWrapper(); }

		// アンマネージドリソースの解放
		!VideoCaptureWrapper()
		{
			if (isResponsible && p)
			{
				delete p;
				p = nullptr;
			}
		}

		void ShowVideo() { p->ShowVideo(); }
		void GetVideoImage() { p->GetVideoImage(); }

	};
}
