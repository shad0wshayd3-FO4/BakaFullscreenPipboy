#pragma once

namespace MCM
{
	class Settings
	{
	public:
		class Pipboy
		{
		public:
			inline static bool bEnable{ true };
			inline static bool bQuickBoyKey{ false };
			inline static bool bDisableFX{ true };
			inline static bool bDisableFXBoth{ true };
			inline static bool bUseColor{ true };
			inline static bool bUseColorPA{ true };
			inline static bool bBackground{ false };
			inline static bool bBackgroundBlur{ true };
			inline static bool bBackgroundSmall{ false };
			inline static bool bKeepLowHealthIMod{ false };
			inline static bool bPowerArmorOnly{ false };

			inline static double fBackgroundAlpha{ 1.0 };
			inline static double fPipboyMenuX{ 35.0 };
			inline static double fPipboyMenuY{ 0.0 };
			inline static double fPipboyMenuScale{ 0.92 };
			inline static double fPipboyBackgroundX{ 42.0 };
			inline static double fPipboyBackgroundY{ 0.0 };
			inline static double fPipboyBackgroundScale{ 0.90 };
			inline static double fTerminalMenuX{ 135.0 };
			inline static double fTerminalMenuY{ 0.0 };
			inline static double fTerminalMenuScale{ 0.92 };

			inline static double fPipboy3DItemScale{ 0.6 };
			inline static double fPipboy3DItemScreenPosX{ 0.68 };
			inline static double fPipboy3DItemScreenPosY{ 0.28 };
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
			if (m_FirstRun)
			{
				m_FirstRun = false;
			}

			ResetStateInit();

			GetModSettingBool("Pipboy", "bEnable", Pipboy::bEnable);
			GetModSettingBool("Pipboy", "bQuickBoyKey", Pipboy::bQuickBoyKey);
			GetModSettingBool("Pipboy", "bDisableFX", Pipboy::bDisableFX);
			GetModSettingBool("Pipboy", "bDisableFXBoth", Pipboy::bDisableFXBoth);
			GetModSettingBool("Pipboy", "bUseColor", Pipboy::bUseColor);
			GetModSettingBool("Pipboy", "bUseColorPA", Pipboy::bUseColorPA);
			GetModSettingBool("Pipboy", "bBackground", Pipboy::bBackground);
			GetModSettingBool("Pipboy", "bBackgroundBlur", Pipboy::bBackgroundBlur);
			GetModSettingBool("Pipboy", "bBackgroundSmall", Pipboy::bBackgroundSmall);
			GetModSettingBool("Pipboy", "bKeepLowHealthIMod", Pipboy::bKeepLowHealthIMod);
			GetModSettingBool("Pipboy", "bPowerArmorOnly", Pipboy::bPowerArmorOnly);

			GetModSettingDouble("Pipboy", "fBackgroundAlpha", Pipboy::fBackgroundAlpha);
			GetModSettingDouble("Pipboy", "fPipboyMenuX", Pipboy::fPipboyMenuX);
			GetModSettingDouble("Pipboy", "fPipboyMenuY", Pipboy::fPipboyMenuY);
			GetModSettingDouble("Pipboy", "fPipboyMenuScale", Pipboy::fPipboyMenuScale);
			GetModSettingDouble("Pipboy", "fPipboyBackgroundX", Pipboy::fPipboyBackgroundX);
			GetModSettingDouble("Pipboy", "fPipboyBackgroundY", Pipboy::fPipboyBackgroundY);
			GetModSettingDouble("Pipboy", "fPipboyBackgroundScale", Pipboy::fPipboyBackgroundScale);
			GetModSettingDouble("Pipboy", "fTerminalMenuX", Pipboy::fTerminalMenuX);
			GetModSettingDouble("Pipboy", "fTerminalMenuY", Pipboy::fTerminalMenuY);
			GetModSettingDouble("Pipboy", "fTerminalMenuScale", Pipboy::fTerminalMenuScale);

			GetModSettingDouble("Pipboy", "fPipboy3DItemScale", Pipboy::fPipboy3DItemScale);
			GetModSettingDouble("Pipboy", "fPipboy3DItemScreenPosX", Pipboy::fPipboy3DItemScreenPosX);
			GetModSettingDouble("Pipboy", "fPipboy3DItemScreenPosY", Pipboy::fPipboy3DItemScreenPosY);

			HandleKeybinds();
			ResetStatePost();
		}

		static bool QQuickBoy()
		{
			return (MCM::Settings::Pipboy::bEnable && MCM::Settings::Runtime::bQuickBoy);
		}

		inline static bool m_FirstRun{ true };

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

			m_ini_base.LoadFile("Data/MCM/Config/BakaFullscreenPipboy/settings.ini");
			m_ini_user.LoadFile("Data/MCM/Settings/BakaFullscreenPipboy.ini");
		}

		static void ResetStatePost()
		{
			m_ini_base.Reset();
			m_ini_user.Reset();
		}

		static void HandleKeybinds()
		{
			try
			{
				std::ifstream fstream{ "Data/MCM/Settings/Keybinds.json" };
				nlohmann::json data =
					nlohmann::json::parse(fstream);
				fstream.close();

				for (auto& iter : data["keybinds"sv])
				{
					if (iter["id"sv] == "ToggleQuickBoy"
					    && iter["modName"sv] == "BakaFullscreenPipboy")
					{
						Runtime::QuickBoyKey = iter["keycode"sv];
						break;
					}
				}
			}
			catch (std::exception& a_exception)
			{
				Runtime::QuickBoyKey = 0;
				logger::debug("{:s}"sv, a_exception.what());
			}
		}

	protected:
		static void GetModSettingChar(const std::string& a_section, const std::string& a_setting, std::string_view& a_value)
		{
			auto base = m_ini_base.GetValue(a_section.c_str(), a_setting.c_str(), a_value.data());
			auto user = m_ini_user.GetValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingBool(const std::string& a_section, const std::string& a_setting, bool& a_value)
		{
			auto base = m_ini_base.GetBoolValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetBoolValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingLong(const std::string& a_section, const std::string& a_setting, std::int32_t& a_value)
		{
			auto base = m_ini_base.GetLongValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetLongValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = static_cast<std::int32_t>(user);
		}

		static void GetModSettingDouble(const std::string& a_section, const std::string& a_setting, double& a_value)
		{
			auto base = m_ini_base.GetDoubleValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetDoubleValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		inline static CSimpleIniA m_ini_base{ true };
		inline static CSimpleIniA m_ini_user{ true };
	};
}
