#pragma once
#pragma unmanaged
#include "FaceDetect.h"
#pragma managed
#include "ModuleWrapper.h"

namespace ThroughCamVideoCaptureWrapper {
	public ref class FaceDetectWrapper : public ModuleWrapper
	{
	public:
		FaceDetectWrapper() : ModuleWrapper(new FaceDetect()) {}

		~FaceDetectWrapper() { this->!FaceDetectWrapper(); }

		!FaceDetectWrapper() {}
	};
}
