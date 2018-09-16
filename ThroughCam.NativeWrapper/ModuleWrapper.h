#pragma once
#pragma unmanaged
#include <opencv2/opencv.hpp>
#include "ModuleBase.h"
#pragma managed
#include <iostream>

namespace ThroughCamVideoCaptureWrapper {
	public ref class ModuleWrapper
	{
	private:
		bool isResponsible;
		ModuleBase *p;

	public:
		ModuleWrapper(ModuleBase *p) : isResponsible{ true }, p{ p } {}
		//ModuleWrapper(ModuleBase^ obj) : isResponsible{ true }, p{ new ModuleBase(obj->p) } {}
		//ModuleWrapper(ModuleBase *p) : isResponsible{ false }, p{ p } {}

		// �}�l�[�W�h�y�уA���}�l�[�W�h���\�[�X�̉��
		~ModuleWrapper() { this->!ModuleWrapper(); }

		// �A���}�l�[�W�h���\�[�X�̉��
		!ModuleWrapper()
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
