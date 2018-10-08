#pragma once
#include <iostream>
#include "ModuleFactory.h"
#include "ModuleWrapper.h"
#include "StaticClassForCsharp.h"

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

		System::IntPtr Processing(System::IntPtr ptr)
		{
			auto mat = reinterpret_cast<cv::Mat*>(ptr.ToPointer());
			std::vector<ModuleBase*> modBases;

			for each (auto type in moduleTypes)
			{
				modBases.push_back(ModuleFactory::GetModule(type));
			}

			// ‰æ‘œˆ—
			for each (auto mod in modBases)
			{
				ModuleWrapper^ moduleWrapper = gcnew ModuleWrapper(mod);
				moduleWrapper->Processing(mat);
			}

			// ˜g•`‰æ
			for each (auto mod in modBases)
			{
				for (int i = 0; i < mod->GetRectCount(); i++) {
					StaticClassForCsharp::drawRectangle(mat, mod->GetRectData(i));
				}
			}

			// ‰ð•ú
			for each (auto mod in modBases) delete mod;

			return System::IntPtr(mat);
		}


	};
}
