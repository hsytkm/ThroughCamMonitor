#pragma once
#pragma unmanaged
#include <opencv2/opencv.hpp>
#pragma managed

namespace ThroughCamVideoCaptureWrapper {

	public ref class MatBuffer
	{
	private:
		cv::Mat *matLocal;

	public:
		MatBuffer() {}

		~MatBuffer() { this->!MatBuffer(); }
		!MatBuffer() {
			if (matLocal != nullptr)
			{
				delete matLocal;
				matLocal = nullptr;
			}
		}

		System::IntPtr CopyIntPtrMat(System::IntPtr src) {
			auto mat = reinterpret_cast<const cv::Mat*>(src.ToPointer());
			matLocal = new cv::Mat(mat->clone());
			return System::IntPtr(matLocal);
		}

	};
}
