#pragma once
#pragma unmanaged
#include "NegaFilter.h"
#pragma managed
#include "ModuleWrapper.h"

namespace ThroughCamVideoCaptureWrapper {
	public ref class NegaFilterWrapper : public ModuleWrapper
	{
	public:
		NegaFilterWrapper() : ModuleWrapper(new NegaFilter()) {}

		~NegaFilterWrapper() { this->!NegaFilterWrapper(); }

		!NegaFilterWrapper() {}
	};
}
