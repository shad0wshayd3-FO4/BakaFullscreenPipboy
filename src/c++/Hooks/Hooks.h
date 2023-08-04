#pragma once

#include "MCM/MCM.h"

class Hooks
{
public:
	static void Install()
	{
		hkGetByName<643948, 0x416>::Install();                    // PipboyMenu::ProcessMessage
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
		hkGetByName<1512675, 0x17>::Install();                    // Inventory3DManager::End3D
		hkGetByName<176578, 0x51>::Install();                     // Inventory3DManager::EnableRendering
		hkGetByName<255893, 0x23>::Install();                     // Inventory3DManager::DisableRendering
		hkGetByName<162712, 0x10>::Install();                     // Inventory3DManager::UpdateRenderingEnable
		hkGetByName<888792, 0x1A7>::Install();                    // Inventory3DManager::CenterOnBoundCenter
		hkGetByName<63218, 0x14>::Install();                      // Inventory3DManager::ClearModel
		hkGetByName<1006347, 0x346>::Install();                   // Inventory3DManager::AddLoadedModel
		hkGetByName<139664, 0x255>::Install();                    // Inventory3DManager::UpdateModelTransform
		hkGetByName<1531226, 0x10>::Install();                    // Inventory3DManager::lambda_1
		hkGetByName<998822, 0x10>::Install();                     // Inventory3DManager::lambda_2
		hkGetByName<683084, 0x6A>::Install();                     // Inventory3DManager::functor_1
		hkGetByName<999057, 0x10>::Install();                     // Inventory3DManager::functor_2
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
		hkSetCursorConstraints<726763, 0x7E>::Install();          // PipboyManager::RaisePipboy
		hkSetCursorConstraints<726763, 0xA3>::Install();          // PipboyManager::RaisePipboy
		hkSetCursorConstraints<1477369, 0x2D4>::Install();        // PipboyManager::InitPipboy
		hkSetCursorConstraints<1477369, 0x2F9>::Install();        // PipboyManager::InitPipboy
		hkSetCursorConstraints<900802, 0x4D>::Install();          // PipboyManager::UpdateCursorConstraint
		hkSetCursorConstraints<900802, 0x75>::Install();          // PipboyManager::UpdateCursorConstraint
		hkQActorInPowerArmor<643948, 0x3BD, false>::Install();    // PipboyMenu::ProcessMessage
		hkQActorInPowerArmor<1477369, 0x154, false>::Install();   // PipboyManager::InitPipboy
		hkQActorInPowerArmor<1477369, 0x24C, false>::Install();   // PipboyManager::InitPipboy
		hkQActorInPowerArmor<1477369, 0xE6, true>::Install();     // PipboyManager::InitPipboy
		hkQActorInPowerArmor<809076, 0x29, true>::Install();      // PipboyManager::PlayPipboyGenericOpenAnim
		hkQActorInPowerArmor<1444875, 0x46, true>::Install();     // PipboyManager::LowerPipboy
		hkQActorInPowerArmor<726763, 0xC6, true>::Install();      // PipboyManager::RaisePipboy
		hkPlayPipboyLoadHolotapeAnim<634650, 0x9E>::Install();    // PipboyInventoryMenu::PlayHolotape
		hkPlayPipboyLoadHolotapeAnim<1411297, 0x1BD>::Install();  // ReadyWeaponHandler::HandleEvent
		hkLowerPipboy<453340, 0xAC>::Install();                   // ExamineMenu::ShowInspectMenu
		hkLowerPipboy<43450, 0x247>::Install();                   // BookMenu::OpenBookMenu
		hkProcessMessageT<RE::PipboyHolotapeMenu>::Install();     // PipboyHolotapeMenu::ProcessMessage
		hkProcessMessagePipboyMenu::Install();                    // PipboyMenu::ProcessMessage
	}

	static void InstallPostLoad()
	{
		detail::PipBckScreenModel::Install();
		detail::PipboyScreenModel::Install();
	}

private:
	class detail
	{
	public:
		class PipBckScreenModel :
			public RE::BSTEventSink<RE::UIAdvanceMenusFunctionCompleteEvent>
		{
		public:
			PipBckScreenModel()
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
					((State.backBufferWidth / State.backBufferHeight) == (16 / 10))
						? "Interface\\Objects\\HUDGlassFlat16x10.nif"sv
						: "Interface\\Objects\\HUDGlassFlat.nif"sv;

				RE::NiTexture::SetAllowDegrade(false);
				RE::BSModelDB::Demand(
					ModelPath.data(),
					&model,
					args);
				CreateRenderer();
				RE::NiTexture::SetAllowDegrade(true);

				if (auto EventSource = RE::UIAdvanceMenusFunctionCompleteEvent::GetEventSource())
				{
					EventSource->RegisterSink(this);
				}
			}

			virtual ~PipBckScreenModel()
			{
				if (auto EventSource = RE::UIAdvanceMenusFunctionCompleteEvent::GetEventSource())
				{
					EventSource->UnregisterSink(this);
				}

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

			virtual RE::BSEventNotifyControl ProcessEvent(const RE::UIAdvanceMenusFunctionCompleteEvent&, RE::BSTEventSource<RE::UIAdvanceMenusFunctionCompleteEvent>*) override
			{
				return RE::BSEventNotifyControl::kContinue;
			}

		public:
			static void Install()
			{
				if (!singleton)
				{
					singleton = new PipBckScreenModel();
				}
			}

			[[nodiscard]] static PipBckScreenModel* GetSingleton()
			{
				return singleton;
			}

			[[nodiscard]] static RE::BSFixedString& GetRendererName()
			{
				static RE::BSFixedString rendererName{ "PipBckScreenModel"sv };
				return rendererName;
			}

			[[nodiscard]] static RE::Interface3D::Renderer* GetRenderer()
			{
				if (auto Renderer = RE::Interface3D::Renderer::GetByName(GetRendererName()))
				{
					return Renderer;
				}
				return PipBckScreenModel::GetSingleton()->CreateRenderer();
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
							RE::UI_DEPTH_PRIORITY::kStandard,
							0.0f,
							true))
					{
						Renderer->MainScreen_SetBackgroundMode(RE::Interface3D::BackgroundMode::kSolidColor);
						Renderer->MainScreen_SetScreenAttached3D(node);

						Renderer->Offscreen_SetDisplayMode(
							RE::Interface3D::ScreenMode::kScreenAttached,
							nullptr,
							nullptr);

						Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
						Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kNone);
						return Renderer;
					}
				}

				return nullptr;
			}

		protected:
			// members
			RE::NiPointer<RE::NiNode> model{ nullptr };

			inline static PipBckScreenModel* singleton{ nullptr };
		};

		class PipboyScreenModel :
			public RE::BSTEventSink<RE::UIAdvanceMenusFunctionCompleteEvent>
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
					((State.backBufferWidth / State.backBufferHeight) == (16 / 10))
						? "Interface\\Objects\\HUDGlassFlat16x10.nif"sv
						: "Interface\\Objects\\HUDGlassFlat.nif"sv;

				RE::NiTexture::SetAllowDegrade(false);
				RE::BSModelDB::Demand(
					ModelPath.data(),
					&model,
					args);
				CreateRenderer();
				RE::NiTexture::SetAllowDegrade(true);

				if (auto EventSource = RE::UIAdvanceMenusFunctionCompleteEvent::GetEventSource())
				{
					EventSource->RegisterSink(this);
				}
			}

			virtual ~PipboyScreenModel()
			{
				if (auto EventSource = RE::UIAdvanceMenusFunctionCompleteEvent::GetEventSource())
				{
					EventSource->UnregisterSink(this);
				}

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

			virtual RE::BSEventNotifyControl ProcessEvent(const RE::UIAdvanceMenusFunctionCompleteEvent&, RE::BSTEventSource<RE::UIAdvanceMenusFunctionCompleteEvent>*) override
			{
				return RE::BSEventNotifyControl::kContinue;
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
							RE::UI_DEPTH_PRIORITY::kPipboy,
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
						Renderer->menuEmitIntensity = 1.0f;
						Renderer->menuDiffuseIntensity = 3.0f;
						return Renderer;
					}
				}

				return nullptr;
			}

		protected:
			// members
			RE::NiPointer<RE::NiNode> model{ nullptr };

			inline static PipboyScreenModel* singleton{ nullptr };
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
			    && RE::PowerArmor::ActorInPowerArmor(*RE::PlayerCharacter::GetSingleton()))
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
		static const void EnablePipboyShader(
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
		static const void RefreshPipboyRenderSurface(
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
			if (!Renderer)
			{
				return _PickScreen(a_camera, a_firstPersonSceneGraph, a_screenThickness, a_refractStrength);
			}

			if (!Renderer->enabled || !Renderer->nativeAspect)
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
			if (!Renderer)
			{
				return _GetObjectByName(a_scene, a_name, a_testScenegraph, a_defer);
			}

			auto& root = Renderer->screenAttachedElementRoot;
			if (!Renderer->enabled || !root)
			{
				return _GetObjectByName(a_scene, a_name, a_testScenegraph, a_defer);
			}

			static RE::BSFixedString screenGeomName{ "HUDGlassFlat:0"sv };
			return _GetObjectByName(root.get(), &screenGeomName, a_testScenegraph, a_defer);
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

			if (!a_this)
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
	class hkSetCursorConstraints
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

		inline static REL::Relocation<decltype(&hkSetCursorConstraints::SetCursorConstraints)> _SetCursorConstraints;
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
		static const void PlayPipboyLoadHolotapeAnim(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] RE::BGSNote* a_holotape,
			[[maybe_unused]] bool a_noAnim)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyLoadHolotapeAnim(a_this, a_holotape, a_noAnim);
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
		static const void LowerPipboy(
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

	template<class T>
	class hkProcessMessageT
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ T::VTABLE[0] };
			_ProcessMessage = target.write_vfunc(0x3, reinterpret_cast<std::uintptr_t>(ProcessMessage));
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
						if (MCM::Settings::Pipboy::bDisableFX && Renderer->enabled)
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
						if (MCM::Settings::Pipboy::bDisableFX && Renderer->enabled)
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

	class hkProcessMessagePipboyMenu
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ RE::PipboyMenu::VTABLE[0] };
			_ProcessMessage = target.write_vfunc(0x3, reinterpret_cast<std::uintptr_t>(ProcessMessage));
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
					if (MCM::Settings::Pipboy::bBackground)
					{
						if (auto Renderer = detail::PipBckScreenModel::GetRenderer())
						{
							Renderer->Enable();
						}
					}

					if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
					{
						Renderer->Enable();
					}
					break;

				case RE::UI_MESSAGE_TYPE::kHide:
					if (MCM::Settings::Pipboy::bBackground)
					{
						if (auto Renderer = detail::PipBckScreenModel::GetRenderer())
						{
							Renderer->Disable();
						}
					}

					if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
					{
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
};
