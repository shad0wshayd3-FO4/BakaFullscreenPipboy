#pragma once

namespace MCM
{
	class Settings
	{
	public:
		class Pipboy
		{
		public:
			inline static REX::INI::Bool bEnable{ "Pipboy", "bEnable", true };
			inline static REX::INI::Bool bQuickBoyKey{ "Pipboy", "bQuickBoyKey", false };
			inline static REX::INI::Bool bDisableFX{ "Pipboy", "bDisableFX", true };
			inline static REX::INI::Bool bDisableFXBoth{ "Pipboy", "bDisableFXBoth", true };
			inline static REX::INI::Bool bUseColor{ "Pipboy", "bUseColor", true };
			inline static REX::INI::Bool bUseColorPA{ "Pipboy", "bUseColorPA", true };
			inline static REX::INI::Bool bBackground{ "Pipboy", "bBackground", false };
			inline static REX::INI::Bool bBackgroundBlur{ "Pipboy", "bBackgroundBlur", true };
			inline static REX::INI::Bool bBackgroundSmall{ "Pipboy", "bBackgroundSmall", false };
			inline static REX::INI::Bool bKeepLowHealthIMod{ "Pipboy", "bKeepLowHealthIMod", false };
			inline static REX::INI::Bool bPowerArmorOnly{ "Pipboy", "bPowerArmorOnly", false };

			inline static REX::INI::F64 fBackgroundAlpha{ "Pipboy", "fBackgroundAlpha", 1.0 };
			inline static REX::INI::F64 fPipboyMenuX{ "Pipboy", "fPipboyMenuX", 35.0 };
			inline static REX::INI::F64 fPipboyMenuY{ "Pipboy", "fPipboyMenuY", 0.0 };
			inline static REX::INI::F64 fPipboyMenuScale{ "Pipboy", "fPipboyMenuScale", 0.92 };
			inline static REX::INI::F64 fPipboyBackgroundX{ "Pipboy", "fPipboyBackgroundX", 42.0 };
			inline static REX::INI::F64 fPipboyBackgroundY{ "Pipboy", "fPipboyBackgroundY", 0.0 };
			inline static REX::INI::F64 fPipboyBackgroundScale{ "Pipboy", "fPipboyBackgroundScale", 0.90 };
			inline static REX::INI::F64 fTerminalMenuX{ "Pipboy", "fTerminalMenuX", 135.0 };
			inline static REX::INI::F64 fTerminalMenuY{ "Pipboy", "fTerminalMenuY", 0.0 };
			inline static REX::INI::F64 fTerminalMenuScale{ "Pipboy", "fTerminalMenuScale", 0.92 };

			inline static REX::INI::F64 fPipboy3DItemScale{ "Pipboy", "fPipboy3DItemScale", 0.6 };
			inline static REX::INI::F64 fPipboy3DItemScreenPosX{ "Pipboy", "fPipboy3DItemScreenPosX", 0.68 };
			inline static REX::INI::F64 fPipboy3DItemScreenPosY{ "Pipboy", "fPipboy3DItemScreenPosY", 0.28 };
		};

		class Runtime
		{
		public:
			inline static bool bQuickBoy{ true };
			inline static bool bQuickBoyTransition{ false };
			inline static bool bPlayClose{ false };
			inline static std::int32_t QuickBoyKey{ 0 };
		};

		static void Update()
		{
			ResetStateInit();

			const auto ini = REX::INI::SettingStore::GetSingleton();
			ini->Init(
				"Data/MCM/Config/BakaFullscreenPipboy/settings.ini",
				"Data/MCM/Settings/BakaFullscreenPipboy.ini");
			ini->Load();

			HandleKeybinds();
		}

		static bool QQuickBoy()
		{
			return (MCM::Settings::Pipboy::bEnable.GetValue() && MCM::Settings::Runtime::bQuickBoy);
		}

	private:
		static void ResetStateInit()
		{
			if (auto UI = RE::UI::GetSingleton())
			{
				if (UI->GetMenuOpen("PipboyMenu"sv))
				{
					if (auto UIMessageQueue = RE::UIMessageQueue::GetSingleton())
					{
						UIMessageQueue->AddMessage(
							"PipboyMenu"sv,
							RE::UI_MESSAGE_TYPE::kHide);
					}
				}
			}

			if (auto Renderer = RE::Interface3D::Renderer::GetByName("PipboyScreenModel"sv))
			{
				Renderer->Disable();
				Renderer->Release();
			}

			if (auto Renderer = RE::Interface3D::Renderer::GetByName("PipboyBackgroundScreenModel"sv))
			{
				Renderer->Disable();
				Renderer->Release();
			}
		}

		static void HandleKeybinds()
		{
			/*
			try
			{
				std::ifstream fstream{ "Data/MCM/Settings/Keybinds.json" };
				nlohmann::json data =
					nlohmann::json::parse(fstream);
				fstream.close();

				for (auto& iter : data["keybinds"sv])
				{
					if (iter["id"sv] == "ToggleQuickBoy" && iter["modName"sv] == "BakaFullscreenPipboy")
					{
						Runtime::QuickBoyKey = iter["keycode"sv];
						break;
					}
				}
			}
			catch (std::exception& a_exception)
			{
				Runtime::QuickBoyKey = 0;
				F4SE::log::debug("{:s}"sv, a_exception.what());
			}
			*/
		}
	};
}
