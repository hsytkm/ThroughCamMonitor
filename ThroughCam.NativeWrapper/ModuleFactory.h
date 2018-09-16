#pragma once
#include <iostream>
#pragma unmanaged
#include "NegaFilter.h"
#include "FaceDetect.h"
#pragma managed

namespace ThroughCamVideoCaptureWrapper {

	public ref class ModuleFactory abstract sealed
	{
	public:
		// C++/CLI‚Ì—ñ‹“‘Ì’è‹` https://msdn.microsoft.com/ja-jp/library/tzz3794d.aspx?f=255&MSPPError=-2147217396
		enum class ModuleType { Nega, Face, };

		static ModuleBase* GetModule(ModuleType type) {
			switch (type)
			{
			case ModuleType::Nega:
				return new NegaFilter();
			case ModuleType::Face:
				return new FaceDetect();
			default:
				return nullptr;
			}
		}
	};
}
