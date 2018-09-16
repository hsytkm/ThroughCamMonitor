#pragma once
#include <iostream>
#include "ModuleFactory.h"
#include "ModuleWrapper.h"

using namespace System::Collections::ObjectModel;

namespace ThroughCamVideoCaptureWrapper {

	public ref class ModuleManager
	{
	private:
		ReadOnlyCollection<ModuleFactory::ModuleType>^ moduleTypes;

	public:
		ModuleManager(ReadOnlyCollection<ModuleFactory::ModuleType>^ types) : moduleTypes{ types } {}

		~ModuleManager() { this->!ModuleManager(); }

		!ModuleManager() {}

		void Processing(System::IntPtr ptr)
		{
			auto mat = reinterpret_cast<cv::Mat*>(ptr.ToPointer());

			for each (auto type in moduleTypes)
			{
				//System::Console::WriteLine(type.ToString());

				auto mod = ModuleFactory::GetModule(type);
				ModuleWrapper^ moduleWrapper = gcnew ModuleWrapper(mod);
				moduleWrapper->Processing(mat);
				delete mod;
			}
		}

	};
}
