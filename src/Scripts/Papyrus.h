#pragma once

#include "Hooks/Hooks.h"
#include "MCM/MCM.h"

namespace Papyrus
{
	class BakaFullscreenPipboy
	{
	public:
		static bool Register(RE::BSScript::IVirtualMachine* a_vm)
		{
			a_vm->BindNativeMethod(CLASS_NAME, "UpdateSettings", UpdateSettings);
			a_vm->BindNativeMethod(CLASS_NAME, "ToggleQuickBoy", ToggleQuickBoy);
			F4SE::log::info("Registered funcs for class {:s}"sv, CLASS_NAME);

			return true;
		}

	private:
		static constexpr auto CLASS_NAME{ "BakaFullscreenPipboy"sv };

		static void UpdateSettings(std::monostate)
		{
			MCM::Settings::Update();
		}

		static void ToggleQuickBoy(std::monostate)
		{
			Hooks::ToggleQuickBoy();
		}
	};
}
