#pragma once
#pragma unmanaged
#include <opencv2/opencv.hpp>
#include "ModuleBase.h"
#pragma managed
#include <iostream>
#include "IModuleWrapper.h"

namespace ThroughCamVideoCaptureWrapper {
	public ref class ModuleWrapper : public IModuleWrapper
	{
	private:
		bool isResponsible;
		ModuleBase *p;

	public:
		ModuleWrapper(ModuleBase *p) : isResponsible{ true }, p{ p } {}
		//ModuleWrapper(ModuleBase^ obj) : isResponsible{ true }, p{ new ModuleBase(obj->p) } {}
		//ModuleWrapper(ModuleBase *p) : isResponsible{ false }, p{ p } {}

		// マネージド及びアンマネージドリソースの解放
		~ModuleWrapper() { this->!ModuleWrapper(); }

		// アンマネージドリソースの解放
		!ModuleWrapper()
		{
			if (isResponsible && p)
			{
				delete p;
				p = nullptr;
			}
		}

		virtual void Processing(System::IntPtr ptr) {
			cv::Mat* src = reinterpret_cast<cv::Mat*>(ptr.ToPointer());
			p->Processing(src);
		}

	};
}
