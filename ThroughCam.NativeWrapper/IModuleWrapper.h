#pragma once

namespace ThroughCamVideoCaptureWrapper {
	public interface class IModuleWrapper
	{
	public:
		virtual void Processing(cv::Mat*);
		virtual void Processing(System::IntPtr);

	};
}
