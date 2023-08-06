#pragma once

#include "MCM/MCM.h"

class Hooks
{
public:
	static void Install()
	{
		hkGetByName<677805, 0x2F>::Install();                     // PipboyManager::~PipboyManager
		hkGetByName<726763, 0x25>::Install();                     // PipboyManager::RaisePipboy
		hkGetByName<309057, 0x11>::Install();                     // PipboyManager::EnableRenderer
		hkGetByName<920509, 0x0C>::Install();                     // PipboyManager::GetRendererEnabled
		hkGetByName<1159120, 0x0C>::Install();                    // PipboyManager::TriggerLargeBurst
		hkGetByName<627297, 0x0C>::Install();                     // PipboyManager::TriggerSmallBurst
		hkGetByName<95048, 0x0C>::Install();                      // PipboyManager::TriggerShudder
		hkGetByName<1145232, 0x0C>::Install();                    // PipboyManager::TriggerVHold
		hkGetByName<613441, 0x0C>::Install();                     // PipboyManager::TriggerVScan
		hkGetByName<347152, 0x0C>::Install();                     // PipboyManager::TriggerFlicker
		hkGetByName<662519, 0x15>::Install();                     // PipboyManager::DisablePipboyShader
		hkGetByName<302903, 0x3A>::Install();                     // PipboyManager::ProcessLoweringReason
		hkEnablePipboyShader<1477369, 0x28A>::Install();          // PipboyManager::InitPipboy
		hkRefreshPipboyRenderSurface<190194, 0xBF>::Install();    // PlayerCharacter::SetRefraction
		hkAddMenuToPipboy<300484, 0x16C, true>::Install();        // GenericMenu::GenericMenu
		hkAddMenuToPipboy<1155030, 0x8A, false>::Install();       // PipboyHolotapeMenu::PipboyHolotapeMenu
		hkAddMenuToPipboy<712982, 0x2E9, true>::Install();        // PipboyMenu::PipboyMenu
		hkPickScreen<643948, 0x492>::Install();                   // PipboyMenu::ProcessMessage
		hkPickScreen<926335, 0x92A>::Install();                   // TerminalMenu::ProcessMessage
		hkGetObjectByName<643948, 0x455>::Install();              // PipboyMenu::ProcessMessage
		hkGetObjectByName<926335, 0x8F2>::Install();              // TerminalMenu::ProcessMessage
		hkGet3DRendererName<643948, 0x2E4>::Install();            // PipboyMenu::ProcessMessage
		hkGet3DRendererName<188351, 0x257>::Install();            // TerminalMenu::InitMenu
		hkSetViewport<188351, 0x43A>::Install();                  // TerminalMenu::InitMenu
		hkSetCursorConstraintsRaw<726763, 0x7E>::Install();       // PipboyManager::RaisePipboy
		hkSetCursorConstraintsRaw<726763, 0xA3>::Install();       // PipboyManager::RaisePipboy
		hkSetCursorConstraintsRaw<1477369, 0x2D4>::Install();     // PipboyManager::InitPipboy
		hkSetCursorConstraintsRaw<1477369, 0x2F9>::Install();     // PipboyManager::InitPipboy
		hkSetCursorConstraintsRaw<900802, 0x4D>::Install();       // PipboyManager::UpdateCursorConstraint
		hkSetCursorConstraintsRaw<900802, 0x75>::Install();       // PipboyManager::UpdateCursorConstraint
		hkQActorInPowerArmor<809076, 0x29, true>::Install();      // PipboyManager::PlayPipboyGenericOpenAnim
		hkQActorInPowerArmorRW<1411297, 0x162>::Install();        // ReadyWeaponHandler::HandleEvent
		hkPlayPipboyLoadHolotapeAnim<634650, 0x9E>::Install();    // PipboyInventoryMenu::PlayHolotape
		hkPlayPipboyLoadHolotapeAnim<1411297, 0x1BD>::Install();  // ReadyWeaponHandler::HandleEvent
//		hkLowerPipboy<453340, 0xAC>::Install();                   // ExamineMenu::ShowInspectMenu
//		hkLowerPipboy<43450, 0x247>::Install();                   // BookMenu::OpenBookMenu
		hkProcessEvent::Install();                                // PipboyManager::ProcessEvent
		hkProcessMessage::Install();                              // PipboyMenu::ProcessMessage
		hkProcessMessageT<RE::PipboyHolotapeMenu>::Install();     // PipboyHolotapeMenu::ProcessMessage

		hkPlayPipboyOpenAnim<943894, 0x134>::Install();           // UseItemCommand::DoExecute
		hkPlayPipboyOpenAnim<743427, 0x20>::Install();            // PipboyManager::PlayPipboyOpenTerminalAnim
		hkPlayPipboyOpenAnim<181358, 0x23F>::Install();           // PipboyHandler::HandleEvent
		hkOnPipboyOpenAnim<477096, 0x185>::Install();             // PipboyManager::PlayPipboyLoadHolotapeAnim
		hkOnPipboyOpenAnim<809076, 0xDA>::Install();              // PipboyManager::PlayPipboyGenericOpenAnim
		hkOnPipboyOpenAnim<1546751, 0x26C1>::Install();           // TaskQueueInterface::TaskUnpackFunc
		hkPlayPipboyCloseAnim<273179, 0x3A>::Install();           // GenericMenu::ProcessMessage
		hkPlayPipboyCloseAnim<643948, 0x232>::Install();          // PipboyMenu::ProcessMessage
		hkPlayPipboyCloseAnim<643948, 0x245>::Install();          // PipboyMenu::ProcessMessage
		hkPlayPipboyCloseAnim<926335, 0x3E8>::Install();          // TerminalMenu::ProcessMessage
		hkPlayPipboyCloseAnim<1299608, 0x48>::Install();          // PipboyManager::OnPipboyOpened
		hkPlayPipboyCloseAnim<301794, 0x105>::Install();          // ActorEquipManager::UseObject
		hkStartPipboyMode<663900, 0x6A>::Install();               // PipboyManager::PlayPipboyOpenAnim
		hkStartPipboyMode<477096, 0x106>::Install();              // PipboyManager::PlayPipboyLoadHolotapeAnim
		hkStartPipboyMode<809076, 0xB0>::Install();               // PipboyManager::PlayPipboyGenericOpenAnim
		hkStopPipboyMode<702357, 0x10>::Install();                // PipboyManager::OnPipboyOpenAnimFailed
		hkStopPipboyMode<731410, 0x96>::Install();                // PipboyManager::ClosedownPipboy
		hkSetWeaponBonesCulled<1477369, 0xA1>::Install();         // PipboyManager::InitPipboy
		hkSetWeaponBonesCulled<731410, 0xE3>::Install();          // PipboyManager::ClosedownPipboy
		hkDoAction<1299608, 0x13A>::Install();                    // PipboyManager::LowerPipboy
		hkDoAction<1192694, 0x4C>::Install();                     // PipboyManager::StopExamineMenu
		hkDoAction<1444875, 0x61>::Install();                     // PipboyManager::LowerPipboy
		hkDoAction<726763, 0xE4>::Install();                      // PipboyManager::RaisePipboy
		hkQueueShowPipboy<663900, 0x96>::Install();               // PipboyManager::PlayPipboyOpenAnim
		hkQueueClosePipboy<273927, 0xB1>::Install();              // PipboyManager::PlayPipboyCloseAnim
		hkSetEnableDynamicResolution<1231000, 0xF5>::Install();   // PipboyManager::OnPipboyCloseAnim
		hkSetEnableDynamicResolution<1477369, 0x275>::Install();  // PipboyManager::InitPipboy
		hkStopAnimationGraphListening<731410, 0xA6>::Install();   // PipboyManager::ClosedownPipboy
	}

	static void InstallPostLoad()
	{
		MCM::Settings::Update();

		detail::PipboyScreenModel::Install();
		detail::PipboyBackgroundScreenModel::Install();

		if (auto UI = RE::UI::GetSingleton())
		{
			UI->RegisterMenu(
				"PipboyBackgroundMenu",
				detail::PipboyBackgroundMenu::Create);
		}
	}

private:
	class detail
	{
	public:
		class PipboyScreenModel
		{
		public:
			PipboyScreenModel()
			{
				auto args = RE::BSModelDB::DBTraits::ArgsType{
					RE::ENUM_LOD_MULT::kNone,
					0,
					true,
					false,
					true,
					true,
					true,
					true
				};

				auto State = RE::BSGraphics::State::GetSingleton();
				auto ModelPath =
					((static_cast<double>(State.backBufferWidth) / static_cast<double>(State.backBufferHeight)) == (16.0 / 10.0))
						? "Interface\\Objects\\HUDGlassFlat16x10.nif"sv
						: "Interface\\Objects\\HUDGlassFlat.nif"sv;

				RE::NiTexture::SetAllowDegrade(false);
				RE::BSModelDB::Demand(
					ModelPath.data(),
					&model,
					args);
				CreateRenderer();
				RE::NiTexture::SetAllowDegrade(true);
			}

			virtual ~PipboyScreenModel()
			{
				if (auto Renderer = GetRenderer())
				{
					Renderer->Release();
				}

				model.reset();
				if (singleton == this)
				{
					singleton = nullptr;
				}
			}

		public:
			static void Install()
			{
				if (!singleton)
				{
					singleton = new PipboyScreenModel();
				}
			}

			[[nodiscard]] static PipboyScreenModel* GetSingleton()
			{
				return singleton;
			}

			[[nodiscard]] static RE::BSFixedString& GetRendererName()
			{
				static RE::BSFixedString rendererName{ "PipboyScreenModel"sv };
				return rendererName;
			}

			[[nodiscard]] static RE::Interface3D::Renderer* GetRenderer()
			{
				if (auto Renderer = RE::Interface3D::Renderer::GetByName(GetRendererName()))
				{
					return Renderer;
				}
				return PipboyScreenModel::GetSingleton()->CreateRenderer();
			}

			F4_HEAP_REDEFINE_NEW();

		private:
			RE::Interface3D::Renderer* CreateRenderer()
			{
				if (!model)
				{
					return nullptr;
				}

				if (auto node = model->IsNode())
				{
					RE::NiUpdateData UpdateData;
					node->local.translate.x = 0;
					node->local.translate.y = 350;
					node->local.translate.z = 0;
					node->Update(UpdateData);

					if (auto Renderer = RE::Interface3D::Renderer::Create(
							GetRendererName(),
							RE::UI_DEPTH_PRIORITY::kPauseMenu,
							0.0f,
							true))
					{
						Renderer->MainScreen_SetBackgroundMode(RE::Interface3D::BackgroundMode::kLive);
						Renderer->MainScreen_SetScreenAttached3D(node);
						Renderer->MainScreen_SetPostAA(true);

						Renderer->Offscreen_SetDisplayMode(
							RE::Interface3D::ScreenMode::kScreenAttached,
							"HUDGlassFlat:0",
							"Materials\\Interface\\HUDGlassFlat.BGEM");
						Renderer->MainScreen_EnableScreenAttached3DMasking(
							"HUDShadowFlat:0",
							"Materials\\Interface\\ModMenuShadow.BGEM");

						if (MCM::Settings::Pipboy::bDisableFX)
						{
							Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
							Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kHUDGlass);
							Renderer->customRenderTarget = -1;
							Renderer->customSwapTarget = -1;
						}
						else
						{
							Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
							Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kPipboy);
							Renderer->customRenderTarget = 60;
							Renderer->customSwapTarget = 62;
						}

						Renderer->hideScreenWhenDisabled = true;
						return Renderer;
					}
				}

				return nullptr;
			}

		protected:
			RE::NiPointer<RE::NiNode> model{ nullptr };
			inline static PipboyScreenModel* singleton{ nullptr };
		};

		class PipboyBackgroundScreenModel
		{
		public:
			PipboyBackgroundScreenModel()
			{
				auto args = RE::BSModelDB::DBTraits::ArgsType{
					RE::ENUM_LOD_MULT::kNone,
					0,
					true,
					false,
					true,
					true,
					true,
					true
				};

				auto State = RE::BSGraphics::State::GetSingleton();
				auto ModelPath =
					((static_cast<double>(State.backBufferWidth) / static_cast<double>(State.backBufferHeight)) == (16.0 / 10.0))
						? "Interface\\Objects\\HUDGlassFlat16x10.nif"sv
						: "Interface\\Objects\\HUDGlassFlat.nif"sv;

				RE::NiTexture::SetAllowDegrade(false);
				RE::BSModelDB::Demand(
					ModelPath.data(),
					&model,
					args);
				CreateRenderer();
				RE::NiTexture::SetAllowDegrade(true);
			}

			virtual ~PipboyBackgroundScreenModel()
			{
				if (auto Renderer = GetRenderer())
				{
					Renderer->Disable();
					Renderer->Release();
				}

				model.reset();
				if (singleton == this)
				{
					singleton = nullptr;
				}
			}

		public:
			static void Install()
			{
				if (!singleton)
				{
					singleton = new PipboyBackgroundScreenModel();
				}
			}

			[[nodiscard]] static PipboyBackgroundScreenModel* GetSingleton()
			{
				return singleton;
			}

			[[nodiscard]] static RE::BSFixedString& GetRendererName()
			{
				static RE::BSFixedString rendererName{ "PipboyBackgroundScreenModel"sv };
				return rendererName;
			}

			[[nodiscard]] static RE::Interface3D::Renderer* GetRenderer()
			{
				if (auto Renderer = RE::Interface3D::Renderer::GetByName(GetRendererName()))
				{
					return Renderer;
				}
				return PipboyBackgroundScreenModel::GetSingleton()->CreateRenderer();
			}

			F4_HEAP_REDEFINE_NEW();

		private:
			RE::Interface3D::Renderer* CreateRenderer()
			{
				if (!model)
				{
					return nullptr;
				}

				if (auto node = model->IsNode())
				{
					RE::NiUpdateData UpdateData;
					node->local.translate.x = 0;
					node->local.translate.y = 350;
					node->local.translate.z = 0;
					node->Update(UpdateData);

					if (auto Renderer = RE::Interface3D::Renderer::Create(
							GetRendererName(),
							RE::UI_DEPTH_PRIORITY::kGameMessage,
							0.0f,
							true))
					{
						Renderer->MainScreen_SetBackgroundMode(RE::Interface3D::BackgroundMode::kLive);
						Renderer->MainScreen_SetScreenAttached3D(node);

						Renderer->Offscreen_SetDisplayMode(
							RE::Interface3D::ScreenMode::kScreenAttached,
							"HUDGlassFlat:0",
							"Materials\\Interface\\HUDGlassFlat.BGEM");

						Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
						Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kHUDGlass);
						return Renderer;
					}
				}

				return nullptr;
			}

		protected:
			RE::NiPointer<RE::NiNode> model{ nullptr };
			inline static PipboyBackgroundScreenModel* singleton{ nullptr };
		};

		class PipboyBackgroundMenu :
			RE::GameMenuBase
		{
		public:
			PipboyBackgroundMenu()
			{
				customRendererName = "PipboyBackgroundScreenModel";

				menuFlags.set(
					RE::UI_MENU_FLAGS::kCustomRendering,
					RE::UI_MENU_FLAGS::kRendersUnderPauseMenu);
				depthPriority.set(RE::UI_DEPTH_PRIORITY::kStandard);

				auto State = RE::BSGraphics::State::GetSingleton();
				auto MoviePath =
					((static_cast<double>(State.backBufferWidth) / static_cast<double>(State.backBufferHeight)) == (16.0 / 10.0))
						? "Interface\\PipboyBackgroundMenu16x10.swf"sv
						: "Interface\\PipboyBackgroundMenu.swf"sv;

				const auto ScaleformManager = RE::BSScaleformManager::GetSingleton();
				[[maybe_unused]] const auto LoadMovieSuccess =
					ScaleformManager->LoadMovieEx(*this, MoviePath, "root.Menu_mc");
				assert(LoadMovieSuccess);

				filterHolder = RE::msvc::make_unique<RE::BSGFxShaderFXTarget>(*uiMovie, "root.Menu_mc.Background_mc");
				if (filterHolder)
				{
					filterHolder->CreateAndSetFiltersToColor(0, 0, 0, 0.0f);
					shaderFXObjects.push_back(filterHolder.get());
				}
			}

			static RE::IMenu* Create(const RE::UIMessage&)
			{
				return new PipboyBackgroundMenu();
			}

			static void ShowMenu()
			{
				auto UIMessageQueue = RE::UIMessageQueue::GetSingleton();
				if (UIMessageQueue)
				{
					auto Renderer = PipboyBackgroundScreenModel::GetRenderer();
					if (!Renderer)
					{
						return;
					}

					Renderer->MainScreen_SetOpacityAlpha(
						static_cast<float>(MCM::Settings::Pipboy::fBackgroundAlpha));

					Renderer->Enable();
					UIMessageQueue->AddMessage(
						"PipboyBackgroundMenu",
						RE::UI_MESSAGE_TYPE::kShow);
				}
			}

			static void HideMenu()
			{
				auto UIMessageQueue = RE::UIMessageQueue::GetSingleton();
				if (UIMessageQueue)
				{
					auto Renderer = PipboyBackgroundScreenModel::GetRenderer();
					if (!Renderer)
					{
						return;
					}

					Renderer->Disable();
					UIMessageQueue->AddMessage(
						"PipboyBackgroundMenu",
						RE::UI_MESSAGE_TYPE::kHide);
				}
			}
		};

		static bool IsExempt()
		{
			if (auto PipboyManager = RE::PipboyManager::GetSingleton())
			{
				if (!MCM::Settings::Pipboy::bEnable
				    || PipboyManager->menuToOpen == "GenericMenu"sv
				    || PipboyManager->menuToOpen == "PipboyOpeningSequenceMenu"sv)
				{
					return true;
				}
			}

			return false;
		}

		static bool IsAnimOverride()
		{
			if (auto PipboyManager = RE::PipboyManager::GetSingleton())
			{
				if (!PipboyManager->QPipboyActive()
				    && (PipboyManager->menuToOpen == "PipboyHolotapeMenu"sv
				        || PipboyManager->menuToOpen == "TerminalMenu"sv
				        || PipboyManager->menuToOpen == "VoiceHolotape"sv))
				{
					return true;
				}
			}

			return false;
		}

		static void SetColorHelper(RE::GameMenuBase* a_menu, bool a_color = true)
		{
			if (!a_color)
			{
				return;
			}

			if (!a_menu->filterHolder)
			{
				a_menu->filterHolder = RE::msvc::make_unique<RE::BSGFxShaderFXTarget>(*a_menu->uiMovie, "root1");
				a_menu->shaderFXObjects.push_back(a_menu->filterHolder.get());
			}

			if (MCM::Settings::Pipboy::bUseColorPA
			    && RE::PowerArmor::PlayerInPowerArmor())
			{
				a_menu->filterHolder->CreateAndSetFiltersToHUD(RE::HUDColorTypes::kPowerArmorColorOnly);
			}
			else
			{
				std::uint8_t PipboyColorR{ 255 }, PipboyColorG{ 255 }, PipboyColorB{ 255 };
				if (auto INIPrefSettingCollection = RE::INIPrefSettingCollection::GetSingleton())
				{
					auto fPipboyEffectColorR = INIPrefSettingCollection->GetSetting("fPipboyEffectColorR:Pipboy");
					auto fPipboyEffectColorG = INIPrefSettingCollection->GetSetting("fPipboyEffectColorG:Pipboy");
					auto fPipboyEffectColorB = INIPrefSettingCollection->GetSetting("fPipboyEffectColorB:Pipboy");
					if (fPipboyEffectColorR && fPipboyEffectColorG && fPipboyEffectColorB)
					{
						PipboyColorR = static_cast<std::uint8_t>(fPipboyEffectColorR->GetFloat() * 255.0f);
						PipboyColorG = static_cast<std::uint8_t>(fPipboyEffectColorG->GetFloat() * 255.0f);
						PipboyColorB = static_cast<std::uint8_t>(fPipboyEffectColorB->GetFloat() * 255.0f);
					}
				}

				a_menu->filterHolder->CreateAndSetFiltersToColor(PipboyColorR, PipboyColorG, PipboyColorB, 1.0);
			}
		}

		inline static bool bPlayCloseAnim{ false };
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkGetByName
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_GetByName = trampoline.write_call<5>(target.address(), GetByName);
		}

	private:
		static RE::Interface3D::Renderer* GetByName(
			[[maybe_unused]] const RE::BSFixedString& a_name)
		{
			if (detail::IsExempt())
			{
				return _GetByName(a_name);
			}

			if (a_name != "PipboyMenu"sv)
			{
				return _GetByName(a_name);
			}

			return detail::PipboyScreenModel::GetRenderer();
		}

		inline static REL::Relocation<decltype(&hkGetByName::GetByName)> _GetByName;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkEnablePipboyShader
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_EnablePipboyShader = trampoline.write_call<5>(target.address(), EnablePipboyShader);
		}

	private:
		static void EnablePipboyShader(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _EnablePipboyShader(a_this);
			}

			a_this->inv3DModelManager.str3DRendererName = detail::PipboyScreenModel::GetRendererName();
			RE::ImageSpaceModifierInstanceForm::Trigger("PipboyMenuImod"sv);

			if (auto PowerArmor = RE::PowerArmorGeometry::GetSingleton())
			{
				PowerArmor->HidePipboyPAGeometry();
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			Renderer->Enable();
		}

		inline static REL::Relocation<decltype(&hkEnablePipboyShader::EnablePipboyShader)> _EnablePipboyShader;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkRefreshPipboyRenderSurface
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_RefreshPipboyRenderSurface = trampoline.write_call<5>(target.address(), RefreshPipboyRenderSurface);
		}

	private:
		static void RefreshPipboyRenderSurface(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _RefreshPipboyRenderSurface(a_this);
			}

			RE::ImageSpaceModifierInstanceForm::Trigger("PipboyMenuImod"sv);
		}

		inline static REL::Relocation<decltype(&hkRefreshPipboyRenderSurface::RefreshPipboyRenderSurface)> _RefreshPipboyRenderSurface;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF, bool COLOR>
	class hkAddMenuToPipboy
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_AddMenuToPipboy = trampoline.write_call<5>(target.address(), AddMenuToPipboy);
		}

	private:
		static void AddMenuToPipboy(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] RE::IMenu& a_menu,
			[[maybe_unused]] const RE::NiRect<float>& a_standVP,
			[[maybe_unused]] const RE::NiRect<float>& a_powerVP)
		{
			if (detail::IsExempt())
			{
				return _AddMenuToPipboy(a_this, a_menu, a_standVP, a_powerVP);
			}

			auto GameMenuBase = RE::fallout_cast<RE::GameMenuBase*>(&a_menu);
			if (!GameMenuBase)
			{
				return _AddMenuToPipboy(a_this, a_menu, a_standVP, a_powerVP);
			}

			if (MCM::Settings::Pipboy::bDisableFX
			    && MCM::Settings::Pipboy::bUseColor)
			{
				detail::SetColorHelper(GameMenuBase, COLOR);
			}

			a_menu.customRendererName = detail::PipboyScreenModel::GetRendererName();
			GameMenuBase->SetViewportRect({
				static_cast<float>(MCM::Settings::Pipboy::fPipboyViewportLeft),
				static_cast<float>(MCM::Settings::Pipboy::fPipboyViewportRight),
				static_cast<float>(MCM::Settings::Pipboy::fPipboyViewportTop),
				static_cast<float>(MCM::Settings::Pipboy::fPipboyViewportBottom),
			});
		}

		inline static REL::Relocation<decltype(&hkAddMenuToPipboy::AddMenuToPipboy)> _AddMenuToPipboy;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkPickScreen
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_PickScreen = trampoline.write_call<5>(target.address(), PickScreen);
		}

	private:
		static bool PickScreen(
			[[maybe_unused]] RE::NiCamera* a_camera,
			[[maybe_unused]] bool a_firstPersonSceneGraph,
			[[maybe_unused]] float a_screenThickness,
			[[maybe_unused]] float a_refractStrength)
		{
			if (detail::IsExempt())
			{
				return _PickScreen(a_camera, a_firstPersonSceneGraph, a_screenThickness, a_refractStrength);
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer || !Renderer->enabled || !Renderer->nativeAspect)
			{
				return _PickScreen(a_camera, a_firstPersonSceneGraph, a_screenThickness, a_refractStrength);
			}

			return _PickScreen(Renderer->nativeAspect.get(), false, 0.0f, 0.0f);
		}

		inline static REL::Relocation<decltype(&hkPickScreen::PickScreen)> _PickScreen;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkGetObjectByName
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_GetObjectByName = trampoline.write_call<5>(target.address(), GetObjectByName);
		}

	private:
		static RE::NiNode* GetObjectByName(
			[[maybe_unused]] RE::NiAVObject* a_scene,
			[[maybe_unused]] RE::BSFixedString* a_name,
			[[maybe_unused]] bool a_testScenegraph,
			[[maybe_unused]] bool a_defer)
		{
			if (detail::IsExempt())
			{
				return _GetObjectByName(a_scene, a_name, a_testScenegraph, a_defer);
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer || !Renderer->enabled || !Renderer->screenAttachedElementRoot)
			{
				return _GetObjectByName(a_scene, a_name, a_testScenegraph, a_defer);
			}

			static RE::BSFixedString screenGeomName{ "HUDGlassFlat:0"sv };
			return _GetObjectByName(
				Renderer->screenAttachedElementRoot.get(),
				&screenGeomName,
				a_testScenegraph,
				a_defer);
		}

		inline static REL::Relocation<decltype(&hkGetObjectByName::GetObjectByName)> _GetObjectByName;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkGet3DRendererName
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_Get3DRendererName = trampoline.write_call<5>(target.address(), Get3DRendererName);
		}

	private:
		static const RE::BSFixedString& Get3DRendererName(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _Get3DRendererName(a_this);
			}

			return detail::PipboyScreenModel::GetRendererName();
		}

		inline static REL::Relocation<decltype(&hkGet3DRendererName::Get3DRendererName)> _Get3DRendererName;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkSetViewport
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_SetViewport = trampoline.write_call<5>(target.address(), SetViewport);
		}

	private:
		static void SetViewport(
			[[maybe_unused]] RE::Interface3D::Renderer* a_this,
			[[maybe_unused]] RE::Scaleform::GFx::Movie* a_ui,
			[[maybe_unused]] const RE::NiRect<float>& a_viewport)
		{
			if (detail::IsExempt())
			{
				return _SetViewport(a_this, a_ui, a_viewport);
			}

			if (a_this->name != detail::PipboyScreenModel::GetRendererName())
			{
				return _SetViewport(a_this, a_ui, a_viewport);
			}

			if (MCM::Settings::Pipboy::bDisableFX
			    && MCM::Settings::Pipboy::bUseColor)
			{
				if (auto UI = RE::UI::GetSingleton())
				{
					if (auto TerminalMenu = UI->GetMenu<RE::TerminalMenu>())
					{
						detail::SetColorHelper(TerminalMenu.get());
						TerminalMenu->UpdateFlag(RE::UI_MENU_FLAGS::kCustomRendering, false);
					}
				}
			}

			RE::NiRect<float> viewport{
				static_cast<float>(MCM::Settings::Pipboy::fTerminalViewportLeft),
				static_cast<float>(MCM::Settings::Pipboy::fTerminalViewportRight),
				static_cast<float>(MCM::Settings::Pipboy::fTerminalViewportTop),
				static_cast<float>(MCM::Settings::Pipboy::fTerminalViewportBottom),
			};
			return _SetViewport(a_this, a_ui, viewport);
		}

		inline static REL::Relocation<decltype(&hkSetViewport::SetViewport)> _SetViewport;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkSetCursorConstraintsRaw
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_SetCursorConstraints = trampoline.write_call<5>(target.address(), SetCursorConstraints);
		}

	private:
		static void SetCursorConstraints(
			[[maybe_unused]] RE::MenuCursor* a_this,
			[[maybe_unused]] std::uint32_t a_x,
			[[maybe_unused]] std::uint32_t a_y,
			[[maybe_unused]] std::uint32_t a_w,
			[[maybe_unused]] std::uint32_t a_h)
		{
			if (detail::IsExempt())
			{
				return _SetCursorConstraints(a_this, a_x, a_y, a_w, a_h);
			}

			auto MenuCursor = RE::MenuCursor::GetSingleton();
			if (!MenuCursor)
			{
				return _SetCursorConstraints(a_this, a_x, a_y, a_w, a_h);
			}

			MenuCursor->ClearConstraints();
		}

		inline static REL::Relocation<decltype(&hkSetCursorConstraintsRaw::SetCursorConstraints)> _SetCursorConstraints;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF, bool RETN>
	class hkQActorInPowerArmor
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_QActorInPowerArmor = trampoline.write_call<5>(target.address(), QActorInPowerArmor);
		}

	private:
		static bool QActorInPowerArmor(
			[[maybe_unused]] RE::Actor* a_actor)
		{
			if (detail::IsExempt())
			{
				return _QActorInPowerArmor(a_actor);
			}

			return RETN;
		}

		inline static REL::Relocation<decltype(&hkQActorInPowerArmor::QActorInPowerArmor)> _QActorInPowerArmor;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkQActorInPowerArmorRW
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_QActorInPowerArmor = trampoline.write_call<5>(target.address(), QActorInPowerArmor);
		}

	private:
		static bool QActorInPowerArmor(
			[[maybe_unused]] RE::Actor* a_actor)
		{
			if (detail::IsExempt())
			{
				return _QActorInPowerArmor(a_actor);
			}

			if (auto PlayerCamera = RE::PlayerCamera::GetSingleton())
			{
				if (PlayerCamera->currentState
					&& PlayerCamera->currentState->id >= RE::CameraState::k3rdPerson)
				{
					return true;
				}
			}

			return _QActorInPowerArmor(a_actor);
		}

		inline static REL::Relocation<decltype(&hkQActorInPowerArmorRW::QActorInPowerArmor)> _QActorInPowerArmor;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkPlayPipboyLoadHolotapeAnim
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_PlayPipboyLoadHolotapeAnim = trampoline.write_call<5>(target.address(), PlayPipboyLoadHolotapeAnim);
		}

	private:
		static void PlayPipboyLoadHolotapeAnim(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] RE::BGSNote* a_holotape,
			[[maybe_unused]] bool a_noAnim)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyLoadHolotapeAnim(a_this, a_holotape, a_noAnim);
			}

			if (RE::PowerArmor::PlayerInPowerArmor())
			{
				return _PlayPipboyLoadHolotapeAnim(a_this, a_holotape, true);
			}

			if (auto PlayerCamera = RE::PlayerCamera::GetSingleton())
			{
				if (PlayerCamera->currentState
				    && PlayerCamera->currentState->id >= RE::CameraState::k3rdPerson)
				{
					return _PlayPipboyLoadHolotapeAnim(a_this, a_holotape, true);
				}
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer || !Renderer->enabled)
			{
				return _PlayPipboyLoadHolotapeAnim(a_this, a_holotape, a_noAnim);
			}

			_PlayPipboyLoadHolotapeAnim(a_this, a_holotape, true);
		}

		inline static REL::Relocation<decltype(&hkPlayPipboyLoadHolotapeAnim::PlayPipboyLoadHolotapeAnim)> _PlayPipboyLoadHolotapeAnim;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkLowerPipboy
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_LowerPipboy = trampoline.write_call<5>(target.address(), LowerPipboy);
		}

	private:
		static void LowerPipboy(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] RE::PipboyManager::LOWER_REASON a_reason)
		{
			if (detail::IsExempt())
			{
				return _LowerPipboy(a_this, a_reason);
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer)
			{
				return _LowerPipboy(a_this, a_reason);
			}

			Renderer->Disable();
			_LowerPipboy(a_this, a_reason);
		}

		inline static REL::Relocation<decltype(&hkLowerPipboy::LowerPipboy)> _LowerPipboy;
	};

	class hkProcessEvent
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ RE::PipboyManager::VTABLE[0] };
			_ProcessEvent = target.write_vfunc(0x01, reinterpret_cast<std::uintptr_t>(ProcessEvent));
		}

	private:
		static RE::BSEventNotifyControl ProcessEvent(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] const RE::BSAnimationGraphEvent& a_event,
			[[maybe_unused]] RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_source)
		{
			if (detail::IsExempt())
			{
				return _ProcessEvent(a_this, a_event, a_source);
			}

			if (detail::bPlayCloseAnim
			    && (a_event.animEvent == a_this->openAnimEvent
			        || a_event.animEvent == "holotapeLoaded"sv))
			{
				detail::bPlayCloseAnim = false;
				if (auto PlayerControls = RE::PlayerControls::GetSingleton())
				{
					PlayerControls->DoAction(
						RE::DEFAULT_OBJECT::kActionPipboyClose,
						RE::ActionInput::ACTIONPRIORITY::kTry);
				}

				a_this->StopAnimationGraphListening();
			}

			return RE::BSEventNotifyControl::kContinue;
		}

		inline static REL::Relocation<decltype(&ProcessEvent)> _ProcessEvent;
	};

	class hkProcessMessage
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ RE::PipboyMenu::VTABLE[0] };
			_ProcessMessage = target.write_vfunc(0x03, reinterpret_cast<std::uintptr_t>(ProcessMessage));
		}

	private:
		static RE::UI_MESSAGE_RESULTS ProcessMessage(
			[[maybe_unused]] RE::IMenu* a_this,
			[[maybe_unused]] RE::UIMessage& a_message)
		{
			if (detail::IsExempt())
			{
				return _ProcessMessage(a_this, a_message);
			}

			switch (a_message.type.get())
			{
				case RE::UI_MESSAGE_TYPE::kShow:
					if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
					{
						if (MCM::Settings::Pipboy::bBackground)
						{
							detail::PipboyBackgroundMenu::ShowMenu();
						}

						Renderer->Enable();
					}
					break;

				case RE::UI_MESSAGE_TYPE::kHide:
					if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
					{
						if (MCM::Settings::Pipboy::bBackground)
						{
							detail::PipboyBackgroundMenu::HideMenu();
						}

						Renderer->Disable();
					}
					break;

				default:
					break;
			}

			return _ProcessMessage(a_this, a_message);
		}

		inline static REL::Relocation<decltype(&ProcessMessage)> _ProcessMessage;
	};

	template<class T>
	class hkProcessMessageT
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ T::VTABLE[0] };
			_ProcessMessage = target.write_vfunc(0x03, reinterpret_cast<std::uintptr_t>(ProcessMessage));
		}

	private:
		static RE::UI_MESSAGE_RESULTS ProcessMessage(
			[[maybe_unused]] RE::IMenu* a_this,
			[[maybe_unused]] RE::UIMessage& a_message)
		{
			if (detail::IsExempt())
			{
				return _ProcessMessage(a_this, a_message);
			}

			switch (a_message.type.get())
			{
				case RE::UI_MESSAGE_TYPE::kShow:
					if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
					{
						if (Renderer->enabled && MCM::Settings::Pipboy::bDisableFX)
						{
							Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
							Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kPipboy);
							Renderer->customRenderTarget = 60;
							Renderer->customSwapTarget = 62;
						}
					}
					break;

				case RE::UI_MESSAGE_TYPE::kHide:
					if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
					{
						if (Renderer->enabled && MCM::Settings::Pipboy::bDisableFX)
						{
							Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
							Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kHUDGlass);
							Renderer->customRenderTarget = -1;
							Renderer->customSwapTarget = -1;
						}
					}
					break;

				default:
					break;
			}

			return _ProcessMessage(a_this, a_message);
		}

		inline static REL::Relocation<decltype(&ProcessMessage)> _ProcessMessage;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkPlayPipboyOpenAnim
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_PlayPipboyOpenAnim = trampoline.write_call<5>(target.address(), PlayPipboyOpenAnim);
		}

	private:
		static void PlayPipboyOpenAnim(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] const RE::BSFixedString& a_menu)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyOpenAnim(a_this, a_menu);
			}

			if (!a_this->pipboyOpening)
			{
				a_this->pipboyOpening = true;
				a_this->menuToOpen = a_menu;
				a_this->openAnimEvent = "pipboyOpened"sv;
				a_this->OnPipboyOpenAnim();
				a_this->OnPipboyOpened();
			}
		}

		inline static REL::Relocation<decltype(&hkPlayPipboyOpenAnim::PlayPipboyOpenAnim)> _PlayPipboyOpenAnim;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkOnPipboyOpenAnim
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_OnPipboyOpenAnim = trampoline.write_call<5>(target.address(), OnPipboyOpenAnim);
		}

	private:
		static void OnPipboyOpenAnim(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _OnPipboyOpenAnim(a_this);
			}

			if (detail::IsAnimOverride())
			{
				detail::bPlayCloseAnim = true;
				a_this->StartAnimationGraphListening();
			}

			_OnPipboyOpenAnim(a_this);
			a_this->OnPipboyOpened();
		}

		inline static REL::Relocation<decltype(&hkOnPipboyOpenAnim::OnPipboyOpenAnim)> _OnPipboyOpenAnim;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkPlayPipboyCloseAnim
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_PlayPipboyCloseAnim = trampoline.write_call<5>(target.address(), PlayPipboyCloseAnim);
		}

	private:
		static void PlayPipboyCloseAnim(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] bool a_noAnim)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyCloseAnim(a_this, a_noAnim);
			}

			if (!a_this->pipboyClosing && a_this->QPipboyActive())
			{
				a_this->pipboyClosing = true;
				if (a_noAnim)
				{
					a_this->closeAnimEvent = "ForceClose"sv;
					a_this->OnPipboyCloseAnim();
				}
				else if (RE::PowerArmor::PlayerInPowerArmor())
				{
					a_this->closeAnimEvent = "PowerArmorClose"sv;
					a_this->OnPipboyCloseAnim();
				}
				else
				{
					a_this->closeAnimEvent = "pipboyClosed"sv;
					a_this->OnPipboyCloseAnim();
					a_this->OnPipboyClosed();

					if (a_this->itemAnimOnClose)
					{
						a_this->PlayItemAnimOnClose();
						a_this->itemAnimOnClose = nullptr;
					}
				}
			}
		}

		inline static REL::Relocation<decltype(&hkPlayPipboyCloseAnim::PlayPipboyCloseAnim)> _PlayPipboyCloseAnim;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkStartPipboyMode
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_StartPipboyMode = trampoline.write_call<5>(target.address(), StartPipboyMode);
		}

	private:
		static void StartPipboyMode(
			[[maybe_unused]] RE::PlayerCamera* a_this,
			[[maybe_unused]] bool a_forcePipboyModeCamera)
		{
			if (detail::IsExempt())
			{
				return _StartPipboyMode(a_this, a_forcePipboyModeCamera);
			}

			return;
		}

		inline static REL::Relocation<decltype(&hkStartPipboyMode::StartPipboyMode)> _StartPipboyMode;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkStopPipboyMode
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_StopPipboyMode = trampoline.write_call<5>(target.address(), StopPipboyMode);
		}

	private:
		static void StopPipboyMode(
			[[maybe_unused]] RE::PlayerCamera* a_this)
		{
			if (detail::IsExempt())
			{
				return _StopPipboyMode(a_this);
			}

			return;
		}

		inline static REL::Relocation<decltype(&hkStopPipboyMode::StopPipboyMode)> _StopPipboyMode;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkSetWeaponBonesCulled
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_SetWeaponBonesCulled = trampoline.write_call<5>(target.address(), SetWeaponBonesCulled);
		}

	private:
		static bool SetWeaponBonesCulled(
			[[maybe_unused]] RE::AIProcess* a_this,
			[[maybe_unused]] RE::Actor& a_actor,
			[[maybe_unused]] bool a_stateToSet,
			[[maybe_unused]] RE::WEAPON_CULL_TYPE a_type)
		{
			if (detail::IsExempt())
			{
				return _SetWeaponBonesCulled(a_this, a_actor, a_stateToSet, a_type);
			}

			return true;
		}

		inline static REL::Relocation<decltype(&hkSetWeaponBonesCulled::SetWeaponBonesCulled)> _SetWeaponBonesCulled;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkDoAction
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_DoAction = trampoline.write_call<5>(target.address(), DoAction);
		}

	private:
		static bool DoAction(
			[[maybe_unused]] RE::PlayerControls* a_this,
			[[maybe_unused]] RE::DEFAULT_OBJECT a_action,
			[[maybe_unused]] RE::ActionInput::ACTIONPRIORITY a_priority)
		{
			if (detail::IsExempt())
			{
				return _DoAction(a_this, a_action, a_priority);
			}

			return true;
		}

		inline static REL::Relocation<decltype(&hkDoAction::DoAction)> _DoAction;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkQueueShowPipboy
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_QueueShowPipboy = trampoline.write_call<5>(target.address(), QueueShowPipboy);
		}

	private:
		static void QueueShowPipboy(
			[[maybe_unused]] RE::TaskQueueInterface* a_this,
			[[maybe_unused]] RE::DEFAULT_OBJECT a_animType)
		{
			if (detail::IsExempt())
			{
				return _QueueShowPipboy(a_this, a_animType);
			}

			return;
		}

		inline static REL::Relocation<decltype(&hkQueueShowPipboy::QueueShowPipboy)> _QueueShowPipboy;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkQueueClosePipboy
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_QueueClosePipboy = trampoline.write_call<5>(target.address(), QueueClosePipboy);
		}

	private:
		static void QueueClosePipboy(
			[[maybe_unused]] RE::TaskQueueInterface* a_this)
		{
			if (detail::IsExempt())
			{
				return _QueueClosePipboy(a_this);
			}

			return;
		}

		inline static REL::Relocation<decltype(&hkQueueClosePipboy::QueueClosePipboy)> _QueueClosePipboy;
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkSetEnableDynamicResolution
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			trampoline.write_call<5>(target.address(), SetEnableDynamicResolution);
		}

	private:
		static void SetEnableDynamicResolution(
			[[maybe_unused]] RE::BSGraphics::RenderTargetManager* a_this,
			[[maybe_unused]] bool a_enableDynamicResolution)
		{
			return;
		}
	};

	template<std::uint64_t ID, std::ptrdiff_t OFF>
	class hkStopAnimationGraphListening
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(ID), OFF };
			auto& trampoline = F4SE::GetTrampoline();
			_StopAnimationGraphListening = trampoline.write_call<5>(target.address(), StopAnimationGraphListening);
		}

	private:
		static void StopAnimationGraphListening(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _StopAnimationGraphListening(a_this);
			}

			if (detail::bPlayCloseAnim)
			{
				return;
			}

			return _StopAnimationGraphListening(a_this);
		}

		inline static REL::Relocation<decltype(&hkStopAnimationGraphListening::StopAnimationGraphListening)> _StopAnimationGraphListening;
	};

	class hkSetModelScreenPosition;
	class hkSetModelScale;
};
