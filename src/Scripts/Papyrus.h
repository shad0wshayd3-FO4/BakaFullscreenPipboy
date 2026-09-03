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
			a_vm->BindNativeMethod("BakaFullscreenPipboy"sv, "UpdateSettings", UpdateSettings);
			a_vm->BindNativeMethod("BakaFullscreenPipboy"sv, "ToggleQuickBoy", ToggleQuickBoy);
			REX::DEBUG("Registered funcs for class BakaFullscreenPipboy"sv);

			return true;
		}

	private:
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
