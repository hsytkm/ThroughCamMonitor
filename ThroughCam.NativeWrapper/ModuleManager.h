#pragma once
#include <iostream>

#include "IModuleWrapper.h"
#include "ModuleWrapper.h"
#include "NegaFilterWrapper.h"
#include "FaceDetectWrapper.h"

using namespace System::Collections::ObjectModel;

namespace ThroughCamVideoCaptureWrapper {

	public ref class ModuleManager
	{
	public:
		// C++/CLI‚Ì—ñ‹“‘Ì’è‹` https://msdn.microsoft.com/ja-jp/library/tzz3794d.aspx?f=255&MSPPError=-2147217396
		enum class ModuleType { Nega, Face };

	private:
		ReadOnlyCollection<ModuleType>^ moduleTypes;

	public:
		ModuleManager(ReadOnlyCollection<ModuleType>^ types) : moduleTypes{ types } {}

		~ModuleManager() { this->!ModuleManager(); }

		!ModuleManager() {}

		void Processing(System::IntPtr ptr)
		{
			for each (auto type in moduleTypes)
			{
				//System::Console::WriteLine(type.ToString());
				auto mod = ModuleFactory(type);
				mod->Processing(ptr);
			}
		}

	private:
		IModuleWrapper^ ModuleFactory(ModuleType type) {
			switch (type)
			{
			case ModuleType::Nega:
				return gcnew NegaFilterWrapper();
			case ModuleType::Face:
				return gcnew FaceDetectWrapper();
			default:
				throw gcnew NotImplementedException();
			}
		}
	};
}
