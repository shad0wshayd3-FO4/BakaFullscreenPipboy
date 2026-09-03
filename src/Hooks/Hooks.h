#pragma once

#include "MCM/MCM.h"

class Hooks
{
public:
	static void Install()
	{
		MCM::Settings::Update();

		detail::PipboyScreenModel::Install();
		detail::PipboyBackgroundScreenModel::Install();

		if (auto UI = RE::UI::GetSingleton())
		{
			UI->RegisterMenu("PipboyBackgroundMenu", detail::PipboyBackgroundMenu::Create);
			UI->RegisterMenu("PipboyBackgroundMenuSmall", detail::PipboyBackgroundMenuSmall::Create);
		}
	}

	static void ToggleQuickBoy()
	{
		if (!MCM::Settings::Pipboy::bEnable)
		{
			return;
		}

		if (MCM::Settings::Runtime::bQuickBoyTransition)
		{
			return;
		}

		auto UI = RE::UI::GetSingleton();
		if (!UI)
		{
			return;
		}

		if (!UI->GetMenuOpen("PipboyMenu"sv))
		{
			return;
		}

		if (MCM::Settings::Runtime::bQuickBoy)
		{
			if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
			{
				Renderer->Disable();
				Renderer->Release();
			}

			if (auto PlayerCamera = RE::PlayerCamera::GetSingleton())
			{
				PlayerCamera->StartPipboyMode(false);
			}

			if (auto PlayerCharacter = RE::PlayerCharacter::GetSingleton())
			{
				if (PlayerCharacter->currentProcess)
				{
					PlayerCharacter->currentProcess->SetWeaponBonesCulled(
						*PlayerCharacter,
						true,
						RE::WEAPON_CULL_TYPE::kGeneral);
				}

				if (auto PipboyManager = RE::PipboyManager::GetSingleton())
				{
					if (PipboyManager->wasPipboyLightActive)
					{
						PlayerCharacter->ShowPipboyLight(false, true);
					}
				}
			}

			detail::QuickBoyAnimationHandler::Register(true);
			if (auto TaskQueueInterface = RE::TaskQueueInterface::GetSingleton())
			{
				TaskQueueInterface->QueueShowPipboy(RE::DEFAULT_OBJECT::kActionPipboy);
			}
		}
		else
		{
			if (auto Renderer = RE::Interface3D::Renderer::GetByName("PipboyMenu"sv))
			{
				Renderer->Disable();
				Renderer->Release();
			}

			if (auto PlayerCamera = RE::PlayerCamera::GetSingleton())
			{
				PlayerCamera->StopPipboyMode();
			}

			if (auto PlayerCharacter = RE::PlayerCharacter::GetSingleton())
			{
				if (PlayerCharacter->currentProcess)
				{
					PlayerCharacter->currentProcess->SetWeaponBonesCulled(
						*PlayerCharacter,
						false,
						RE::WEAPON_CULL_TYPE::kGeneral);
				}

				if (auto PipboyManager = RE::PipboyManager::GetSingleton())
				{
					if (PipboyManager->wasPipboyLightActive)
					{
						PlayerCharacter->ShowPipboyLight(true, true);
					}
				}
			}

			MCM::Settings::Runtime::bQuickBoy = true;
			if (auto PlayerControls = RE::PlayerControls::GetSingleton())
			{
				PlayerControls->DoAction(RE::DEFAULT_OBJECT::kActionPipboyClose, RE::ActionInput::ACTIONPRIORITY::kTry);
			}

			if (auto Renderer = detail::PipboyScreenModel::GetRenderer())
			{
				if (auto PipboyMenu = UI->GetMenu<RE::PipboyMenu>())
				{
					PipboyMenu->customRendererName = detail::PipboyScreenModel::GetRendererName();
					if (auto PipboyManager = RE::PipboyManager::GetSingleton())
					{
						PipboyManager->inv3DModelManager.DisableRendering("InventoryMenu"sv);
						PipboyManager->inv3DModelManager.str3DRendererName = detail::PipboyScreenModel::GetRendererName();
						PipboyManager->inv3DModelManager.SetModelScale(MCM::Settings::Pipboy::fPipboy3DItemScale);
						PipboyManager->inv3DModelManager.SetModelScreenPosition(
							{ MCM::Settings::Pipboy::fPipboy3DItemScreenPosX, MCM::Settings::Pipboy::fPipboy3DItemScreenPosY, 1.0f },
							true);
						PipboyManager->inv3DModelManager.EnableRendering("InventoryMenu"sv);
						PipboyManager->UpdateCursorConstraint(false);
					}

					if (MCM::Settings::Pipboy::bDisableFX && MCM::Settings::Pipboy::bUseColor)
					{
						detail::SetColorHelper(PipboyMenu.get());
					}

					PipboyMenu->SetViewportRect(detail::FullViewport);

					Scaleform::GFx::Value root;
					if (PipboyMenu->uiMovie && PipboyMenu->uiMovie->GetVariable(&root, "root"))
					{
						auto scaleX = MCM::Settings::Pipboy::fPipboyMenuScaleX.GetValue();
						auto scaleY = MCM::Settings::Pipboy::fPipboyMenuScaleY.GetValue();
						if (scaleY == 0.0f)
							scaleY = scaleX;

						root.SetMember("x", MCM::Settings::Pipboy::fPipboyMenuX.GetValue());
						root.SetMember("y", MCM::Settings::Pipboy::fPipboyMenuY.GetValue());
						root.SetMember("scaleX", scaleX);
						root.SetMember("scaleY", scaleY);
					}

					Renderer->Enable();
				}
			}
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

				auto& ModelPath = GetAspectRatioString(
					"Interface\\Objects\\HUDGlassFlat.nif"sv,
					"Interface\\Objects\\HUDGlassFlat16x10.nif"sv);

				RE::NiTexture::SetAllowDegrade(false);
				RE::BSModelDB::Demand(ModelPath.data(), &model, args);
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

			F4_HEAP_REDEFINE_NEW(PipboyScreenModel);

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
					node->local.translate.x = setting::fUIFlatModel_TranslateX->GetFloat();
					node->local.translate.y = setting::fUIFlatModel_TranslateY->GetFloat();
					node->local.translate.z = setting::fUIFlatModel_TranslateZ->GetFloat();
					node->Update(UpdateData);

					if (auto Renderer = RE::Interface3D::Renderer::Create(GetRendererName(), RE::UI_DEPTH_PRIORITY::kMessage, 0.0f, true))
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
			RE::NiPointer<RE::NiNode>        model{ nullptr };
			inline static PipboyScreenModel* singleton{ nullptr };
		};

		class PipboyBackgroundScreenModel :
			public RE::BSTEventSink<RE::UIAdvanceMenusFunctionCompleteEvent>
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

				auto& ModelPath = GetAspectRatioString(
					"Interface\\Objects\\HUDGlassFlat.nif"sv,
					"Interface\\Objects\\HUDGlassFlat16x10.nif"sv);

				RE::NiTexture::SetAllowDegrade(false);
				RE::BSModelDB::Demand(ModelPath.data(), &model, args);
				CreateRenderer();
				RE::NiTexture::SetAllowDegrade(true);

				if (auto EventSource = RE::UIAdvanceMenusFunctionCompleteEvent::GetEventSource())
				{
					EventSource->RegisterSink(this);
				}
			}

			virtual ~PipboyBackgroundScreenModel()
			{
				if (auto EventSource = RE::UIAdvanceMenusFunctionCompleteEvent::GetEventSource())
				{
					EventSource->UnregisterSink(this);
				}

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

			virtual RE::BSEventNotifyControl ProcessEvent(const RE::UIAdvanceMenusFunctionCompleteEvent&, RE::BSTEventSource<RE::UIAdvanceMenusFunctionCompleteEvent>*) override
			{
				if (!MCM::Settings::QQuickBoy())
				{
					return RE::BSEventNotifyControl::kContinue;
				}

				if (!MCM::Settings::Pipboy::bBackground)
				{
					return RE::BSEventNotifyControl::kContinue;
				}

				auto Renderer = GetRenderer();
				if (Renderer->enabled != PipboyScreenModel::GetRenderer()->enabled)
				{
					Renderer->enabled = !Renderer->enabled;
					if (Renderer->enabled)
					{
						Renderer->MainScreen_SetOpacityAlpha(MCM::Settings::Pipboy::fBackgroundAlpha);
						Renderer->MainScreen_SetPostAA(RE::PowerArmor::PlayerInPowerArmor());
						PipboyBackgroundMenu::ShowMenu();
					}
					else
					{
						PipboyBackgroundMenu::HideMenu();
					}
				}

				return RE::BSEventNotifyControl::kContinue;
			}

			F4_HEAP_REDEFINE_NEW(PipboyBackgroundScreenModel);

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
					node->local.translate.x = setting::fUIFlatModel_TranslateX->GetFloat();
					node->local.translate.y = setting::fUIFlatModel_TranslateY->GetFloat();
					node->local.translate.z = setting::fUIFlatModel_TranslateZ->GetFloat();
					node->Update(UpdateData);

					if (auto Renderer = RE::Interface3D::Renderer::Create(GetRendererName(), RE::UI_DEPTH_PRIORITY::kLoadingMenu, 0.0f, true))
					{
						Renderer->MainScreen_SetBackgroundMode(RE::Interface3D::BackgroundMode::kLive);
						Renderer->MainScreen_SetScreenAttached3D(node);

						Renderer->Offscreen_SetDisplayMode(
							RE::Interface3D::ScreenMode::kScreenAttached,
							"HUDGlassFlat:0",
							"Materials\\Interface\\HUDGlassFlat.BGEM");
						Renderer->MainScreen_EnableScreenAttached3DMasking(
							"HUDShadowFlat:0",
							"Materials\\Interface\\ModMenuShadow.BGEM");

						Renderer->Offscreen_SetRenderTargetSize(RE::Interface3D::OffscreenMenuSize::kFullFrame);
						Renderer->Offscreen_SetPostEffect(RE::Interface3D::PostEffect::kHUDGlass);
						Renderer->hideScreenWhenDisabled = true;
						return Renderer;
					}
				}

				return nullptr;
			}

		protected:
			RE::NiPointer<RE::NiNode>                  model{ nullptr };
			inline static PipboyBackgroundScreenModel* singleton{ nullptr };
		};

		class PipboyBackgroundMenu :
			public RE::GameMenuBase
		{
		public:
			PipboyBackgroundMenu()
			{
				customRendererName = "PipboyBackgroundScreenModel";

				menuFlags.set(
					RE::UI_MENU_FLAGS::kCustomRendering,
					RE::UI_MENU_FLAGS::kRendersUnderPauseMenu);
				depthPriority = RE::UI_DEPTH_PRIORITY::kStandard;

				auto& MoviePath =
					GetAspectRatioString(
						"Interface\\PipboyBackgroundMenu.swf"sv,
						"Interface\\PipboyBackgroundMenu16x10.swf"sv,
						"Interface\\PipboyBackgroundMenu21x9.swf"sv);

				const auto                  ScaleformManager = RE::BSScaleformManager::GetSingleton();
				[[maybe_unused]] const auto LoadMovieSuccess = ScaleformManager->LoadMovieEx(*this, MoviePath, "root.Menu_mc");
				assert(LoadMovieSuccess);

				filterHolder = std::make_unique<RE::BSGFxShaderFXTarget>(*uiMovie, "root.Menu_mc.Background_mc");
				if (filterHolder)
				{
					filterHolder->CreateAndSetFiltersToColor(0, 0, 0, 1.0f);
					shaderFXObjects.push_back(filterHolder.get());
				}
			}

			static RE::IMenu* Create(const RE::UIMessage&)
			{
				return new PipboyBackgroundMenu();
			}

			static void ShowMenu()
			{
				if (!MCM::Settings::Pipboy::bBackground)
				{
					return;
				}

				if (auto UIMessageQueue = RE::UIMessageQueue::GetSingleton())
				{
					if (!MCM::Settings::Pipboy::bBackgroundSmall)
					{
						UIMessageQueue->AddMessage("PipboyBackgroundMenu", RE::UI_MESSAGE_TYPE::kShow);
					}
					else
					{
						UIMessageQueue->AddMessage("PipboyBackgroundMenuSmall", RE::UI_MESSAGE_TYPE::kShow);
					}
				}
			}

			static void HideMenu()
			{
				if (!MCM::Settings::Pipboy::bBackground)
				{
					return;
				}

				if (auto UIMessageQueue = RE::UIMessageQueue::GetSingleton())
				{
					if (!MCM::Settings::Pipboy::bBackgroundSmall)
					{
						UIMessageQueue->AddMessage("PipboyBackgroundMenu", RE::UI_MESSAGE_TYPE::kHide);
					}
					else
					{
						UIMessageQueue->AddMessage("PipboyBackgroundMenuSmall", RE::UI_MESSAGE_TYPE::kHide);
					}
				}
			}
		};

		class PipboyBackgroundMenuSmall :
			public RE::GameMenuBase
		{
		public:
			PipboyBackgroundMenuSmall()
			{
				customRendererName = "PipboyBackgroundScreenModel";

				menuFlags.set(
					RE::UI_MENU_FLAGS::kCustomRendering,
					RE::UI_MENU_FLAGS::kRendersUnderPauseMenu);
				depthPriority = RE::UI_DEPTH_PRIORITY::kStandard;

				auto                        MoviePath = "Interface\\PipboyBackgroundMenuSmall.swf"sv;
				const auto                  ScaleformManager = RE::BSScaleformManager::GetSingleton();
				[[maybe_unused]] const auto LoadMovieSuccess = ScaleformManager->LoadMovieEx(*this, MoviePath, "root.Menu_mc");
				assert(LoadMovieSuccess);

				filterHolder = std::make_unique<RE::BSGFxShaderFXTarget>(*uiMovie, "root.Menu_mc.Background_mc");
				if (filterHolder)
				{
					filterHolder->CreateAndSetFiltersToColor(0, 0, 0, 1.0f);
					shaderFXObjects.push_back(filterHolder.get());

					filterHolder->SetMember("x", MCM::Settings::Pipboy::fPipboyBackgroundX.GetValue());
					filterHolder->SetMember("y", MCM::Settings::Pipboy::fPipboyBackgroundY.GetValue());
					filterHolder->SetMember("scaleX", MCM::Settings::Pipboy::fPipboyBackgroundScale.GetValue());
					filterHolder->SetMember("scaleY", MCM::Settings::Pipboy::fPipboyBackgroundScale.GetValue());
				}
			}

			static RE::IMenu* Create(const RE::UIMessage&)
			{
				return new PipboyBackgroundMenuSmall();
			}
		};

		class QuickBoyAnimationHandler :
			RE::BSTEventSink<RE::BSAnimationGraphEvent>
		{
		public:
			static void Register(bool a_register)
			{
				MCM::Settings::Runtime::bQuickBoyTransition = a_register;
				PipboyAnim::Register(a_register);
			}

			[[nodiscard]] static QuickBoyAnimationHandler* GetSingleton()
			{
				static QuickBoyAnimationHandler singleton;
				return std::addressof(singleton);
			}

			virtual RE::BSEventNotifyControl ProcessEvent(const RE::BSAnimationGraphEvent& a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>*) override
			{
				if (MCM::Settings::Runtime::bQuickBoy)
				{
					if (a_event.tag == "pipboyLightOff"sv || a_event.tag == "pipboyOpened"sv)
					{
						MCM::Settings::Runtime::bQuickBoy = false;
						if (auto PipboyManager = RE::PipboyManager::GetSingleton())
						{
							PipboyManager->inv3DModelManager.DisableRendering("InventoryMenu"sv);
							PipboyManager->inv3DModelManager.str3DRendererName = "PipboyMenu"sv;
							if (RE::PowerArmor::PlayerInPowerArmor())
							{
								PipboyManager->inv3DModelManager.SetModelScale(setting::fPipboy3DItemPAScale->GetFloat());
								PipboyManager->inv3DModelManager.SetModelScreenPosition(
									{ setting::fPipboy3DItemPAScreenPosX->GetFloat(), setting::fPipboy3DItemPAScreenPosY->GetFloat(), 1.0f },
									true);
							}
							else
							{
								PipboyManager->inv3DModelManager.SetModelScale(setting::fPipboy3DItemPAScale->GetFloat());
								PipboyManager->inv3DModelManager.SetModelScreenPosition(
									{ setting::fPipboy3DItemScreenPosX->GetFloat(), setting::fPipboy3DItemScreenPosY->GetFloat(), 1.0f },
									true);
							}
							PipboyManager->inv3DModelManager.EnableRendering("InventoryMenu"sv);

							PipboyManager->UpdateCursorConstraint(true);
							PipboyManager->EnablePipboyShader();

							if (auto UI = RE::UI::GetSingleton())
							{
								if (auto PipboyMenu = UI->GetMenu<RE::PipboyMenu>())
								{
									PipboyManager->AddMenuToPipboy(
										*PipboyMenu,
										{ 0.0375f, 0.9625f, 0, 1.0f },
										{ 0, 1.0f, 0.15f, 0.85f });
									PipboyManager->StartAnimationGraphListening();
								}
							}
						}

						QuickBoyAnimationHandler::Register(false);
					}
				}

				return RE::BSEventNotifyControl::kContinue;
			}

		private:
			class PipboyAnim
			{
			public:
				static void Register(bool a_register)
				{
					if (auto PlayerCharacter = RE::PlayerCharacter::GetSingleton())
					{
						RE::BSTSmartPointer<RE::BSAnimationGraphManager> Manager;
						if (PlayerCharacter->GetAnimationGraphManagerImpl(Manager))
						{
							auto functor = functor_t{ a_register };
							ForEachAnimationGraph(Manager.get(), functor);
						}
					}
				}

			private:
				struct functor_t
				{
				private:
					// clang-format off
					static void RegisterSink(void* a_source, void* a_sink)
					{
						using func_t = decltype(&functor_t::RegisterSink);
						static REL::Relocation<func_t> func{ REL::ID(2201528) };
						return func(a_source, a_sink);
					}

					static void UnregisterSink(void* a_source, void* a_sink)
					{
						using func_t = decltype(&functor_t::UnregisterSink);
						static REL::Relocation<func_t> func{ REL::ID(2201532) };
						return func(a_source, a_sink);
					}
					// clang-format on

				public:
					functor_t(bool a_listen, bool a_third = true)
					{
						sink = QuickBoyAnimationHandler::GetSingleton();
						listen = a_listen;
						third = a_third;
					}

					bool operator()(const RE::BSTSmartPointer<RE::BShkbAnimationGraph>& a_graph)
					{
						if (a_graph && !this->third)
						{
							if (auto source = REX::ADJUST_POINTER<void>(a_graph.get(), 0x68))
							{
								if (this->listen)
								{
									RegisterSink(source, this->sink);
									this->third = false;
									return true;
								}
								UnregisterSink(source, this->sink);
							}
						}

						this->third = false;
						return true;
					}

					// members
					void* sink;    // 00
					bool  listen;  // 08
					bool  third;   // 09
				};

				static_assert(sizeof(functor_t) == 0x10);

				static void ForEachAnimationGraph(RE::BSAnimationGraphManager* a_this, functor_t& a_functor)
				{
					using func_t = decltype(&ForEachAnimationGraph);
					static REL::Relocation<func_t> func{ REL::ID(2225494) };
					return func(a_this, a_functor);
				}
			};
		};

		static bool IsExempt()
		{
			if (auto PipboyManager = RE::PipboyManager::GetSingleton())
			{
				if (!MCM::Settings::QQuickBoy() || PipboyManager->menuToOpen == "GenericMenu"sv || PipboyManager->menuToOpen == "PipboyOpeningSequenceMenu"sv)
				{
					return true;
				}
				else if (MCM::Settings::Pipboy::bPowerArmorOnly && !RE::PowerArmor::PlayerInPowerArmor())
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
				if (!PipboyManager->QPipboyActive() && (PipboyManager->menuToOpen == "PipboyHolotapeMenu"sv || PipboyManager->menuToOpen == "TerminalMenu"sv || PipboyManager->menuToOpen == "VoiceHolotape"sv))
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
				a_menu->filterHolder = std::make_unique<RE::BSGFxShaderFXTarget>(*a_menu->uiMovie, "root1");
				a_menu->shaderFXObjects.push_back(a_menu->filterHolder.get());
			}

			if (MCM::Settings::Pipboy::bUseColorPA && RE::PowerArmor::PlayerInPowerArmor())
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

		static const std::string_view& GetAspectRatioString(
			const std::string_view& a_16x09,
			const std::string_view& a_16x10 = ""sv,
			const std::string_view& a_21x09 = ""sv)
		{
			if (auto state = RE::BSGraphics::State::GetSingleton())
			{
				auto ratio = static_cast<double>(state->backBufferWidth) / static_cast<double>(state->backBufferHeight);
				if (ratio == ratio_16x10 && !a_16x10.empty())
				{
					return a_16x10;
				}

				if (ratio == ratio_21x09 && !a_21x09.empty())
				{
					return a_21x09;
				}
			}

			return a_16x09;
		}

		inline static RE::NiRect<float> FullViewport{ 0.0f, 1.0f, 0.0f, 1.0f };

	private:
		static constexpr auto ratio_16x10{ 16.0 / 10.0 };
		static constexpr auto ratio_21x09{ 21.0 / 09.0 };
	};

	class setting
	{
	public:
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fPipboy3DItemScreenPosX{ REL::ID(858699) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fPipboy3DItemScreenPosY{ REL::ID(1517083) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fPipboy3DItemScale{ REL::ID(592946) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fPipboy3DItemPAScreenPosX{ REL::ID(1251037) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fPipboy3DItemPAScreenPosY{ REL::ID(326697) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fPipboy3DItemPAScale{ REL::ID(984624) };

		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fUIFlatModel_TranslateX{ REL::ID(314513) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fUIFlatModel_TranslateY{ REL::ID(972452) };
		inline static REL::Relocation<RE::SettingT<RE::INISettingCollection>*> fUIFlatModel_TranslateZ{ REL::ID(48328) };
	};

	class hkGetByName
	{
	private:
		static RE::Interface3D::Renderer* GetByName(
			[[maybe_unused]] const RE::BSFixedString& a_name)
		{
			if (detail::IsExempt())
			{
				return _GetByName00(a_name);
			}

			if (a_name != "PipboyMenu"sv)
			{
				return _GetByName00(a_name);
			}

			return detail::PipboyScreenModel::GetRenderer();
		}

		inline static REL::THook _GetByName00{ REL::ID(2225504), 0x36, GetByName };  // PipboyManager::~PipboyManager
		inline static REL::THook _GetByName01{ REL::ID(2225455), 0x25, GetByName };  // PipboyManager::RaisePipboy
		inline static REL::THook _GetByName02{ REL::ID(2225458), 0x9D, GetByName };  // PipboyManager::OnPipboyClosed
		inline static REL::THook _GetByName03{ REL::ID(2225468), 0x11, GetByName };  // PipboyManager::EnableRenderer
		inline static REL::THook _GetByName04{ REL::ID(2225469), 0x0C, GetByName };  // PipboyManager::GetRendererEnabled
		inline static REL::THook _GetByName05{ REL::ID(2225472), 0x0C, GetByName };  // PipboyManager::TriggerLargeBurst
		inline static REL::THook _GetByName06{ REL::ID(2225473), 0x0C, GetByName };  // PipboyManager::TriggerSmallBurst
		inline static REL::THook _GetByName07{ REL::ID(2225474), 0x0C, GetByName };  // PipboyManager::TriggerShudder
		inline static REL::THook _GetByName08{ REL::ID(2225475), 0x0C, GetByName };  // PipboyManager::TriggerVHold
		inline static REL::THook _GetByName09{ REL::ID(2225476), 0x0C, GetByName };  // PipboyManager::TriggerVScan
		inline static REL::THook _GetByName0A{ REL::ID(2225477), 0x0C, GetByName };  // PipboyManager::TriggerFlicker
		inline static REL::THook _GetByName0B{ REL::ID(2225480), 0x9D, GetByName };  // PipboyManager::ClosedownPipboy
		inline static REL::THook _GetByName0C{ REL::ID(2225486), 0x3A, GetByName };  // PipboyManager::ProcessLoweringReason
	};

	class hkEnablePipboyShader
	{
	private:
		static void EnablePipboyShader(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _EnablePipboyShader0(a_this);
			}

			a_this->inv3DModelManager.str3DRendererName = detail::PipboyScreenModel::GetRendererName();

			if (MCM::Settings::Pipboy::bBackgroundBlur)
			{
				RE::ImageSpaceModifierInstanceForm::Trigger("PipboyMenuImod"sv);
			}

			if (auto PowerArmor = RE::PowerArmorGeometry::GetSingleton())
			{
				PowerArmor->HidePipboyPAGeometry();
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			Renderer->Enable();
		}

		inline static REL::THook _EnablePipboyShader0{ REL::ID(2225479), 0x28A, EnablePipboyShader };  // PipboyManager::InitPipboy
	};

	class hkRefreshPipboyRenderSurface
	{
	private:
		static void RefreshPipboyRenderSurface(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _RefreshPipboyRenderSurface0(a_this);
			}

			if (MCM::Settings::Pipboy::bBackgroundBlur)
			{
				RE::ImageSpaceModifierInstanceForm::Trigger("PipboyMenuImod"sv);
			}
		}

		inline static REL::THook _RefreshPipboyRenderSurface0{ REL::ID(2232942), 0xBF, RefreshPipboyRenderSurface };  // PlayerCharacter::SetRefraction
	};

	class hkAddMenuToPipboy
	{
	private:
		template <bool COLOR>
		static void AddMenuToPipboy(
			[[maybe_unused]] RE::PipboyManager*       a_this,
			[[maybe_unused]] RE::IMenu&               a_menu,
			[[maybe_unused]] const RE::NiRect<float>& a_standVP,
			[[maybe_unused]] const RE::NiRect<float>& a_powerVP)
		{
			if (detail::IsExempt())
			{
				return _AddMenuToPipboy0(a_this, a_menu, a_standVP, a_powerVP);
			}

			auto GameMenuBase = RE::fallout_cast<RE::GameMenuBase*>(&a_menu);
			if (!GameMenuBase)
			{
				return _AddMenuToPipboy0(a_this, a_menu, a_standVP, a_powerVP);
			}

			if (MCM::Settings::Pipboy::bDisableFX && MCM::Settings::Pipboy::bUseColor)
			{
				detail::SetColorHelper(GameMenuBase, COLOR);
			}

			a_menu.customRendererName = detail::PipboyScreenModel::GetRendererName();
			GameMenuBase->SetViewportRect(detail::FullViewport);

			Scaleform::GFx::Value root;
			if (GameMenuBase->uiMovie && GameMenuBase->uiMovie->GetVariable(&root, "root"))
			{
				auto scaleX = MCM::Settings::Pipboy::fPipboyMenuScaleX.GetValue();
				auto scaleY = MCM::Settings::Pipboy::fPipboyMenuScaleY.GetValue();
				if (scaleY == 0.0f)
					scaleY = scaleX;

				root.SetMember("x", MCM::Settings::Pipboy::fPipboyMenuX.GetValue());
				root.SetMember("y", MCM::Settings::Pipboy::fPipboyMenuY.GetValue());
				root.SetMember("scaleX", scaleX);
				root.SetMember("scaleY", scaleY);
			}
		}

		inline static REL::THook _AddMenuToPipboy0{ REL::ID(2223215), 0x178, AddMenuToPipboy<true> };   // GenericMenu::GenericMenu
		inline static REL::THook _AddMenuToPipboy1{ REL::ID(2224049), 0x0E1, AddMenuToPipboy<false> };  // PipboyHolotapeMenu::PipboyHolotapeMenu
		inline static REL::THook _AddMenuToPipboy2{ REL::ID(2224179), 0x317, AddMenuToPipboy<true> };   // PipboyMenu::PipboyMenu
	};

	class hkPickScreen
	{
	private:
		static bool PickScreen(
			[[maybe_unused]] RE::NiCamera* a_camera,
			[[maybe_unused]] bool          a_firstPersonSceneGraph,
			[[maybe_unused]] float         a_screenThickness,
			[[maybe_unused]] float         a_refractStrength)
		{
			if (detail::IsExempt())
			{
				return _PickScreen0(a_camera, a_firstPersonSceneGraph, a_screenThickness, a_refractStrength);
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer || !Renderer->enabled || !Renderer->nativeAspect)
			{
				return _PickScreen0(a_camera, a_firstPersonSceneGraph, a_screenThickness, a_refractStrength);
			}

			return _PickScreen0(Renderer->nativeAspect.get(), false, 0.0f, 0.0f);
		}

		inline static REL::THook _PickScreen0{ REL::ID(2224181), 0x513, PickScreen };  // PipboyMenu::ProcessMessage
		inline static REL::THook _PickScreen1{ REL::ID(2224614), 0x8AD, PickScreen };  // TerminalMenu::ProcessMessage
	};

	class hkGetObjectByName
	{
	private:
		static RE::NiNode* GetObjectByName(
			[[maybe_unused]] RE::NiAVObject*    a_scene,
			[[maybe_unused]] RE::BSFixedString* a_name,
			[[maybe_unused]] bool               a_testScenegraph,
			[[maybe_unused]] bool               a_defer)
		{
			if (detail::IsExempt())
			{
				return _GetObjectByName0(a_scene, a_name, a_testScenegraph, a_defer);
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer || !Renderer->enabled || !Renderer->screenAttachedElementRoot)
			{
				return _GetObjectByName0(a_scene, a_name, a_testScenegraph, a_defer);
			}

			static RE::BSFixedString screenGeomName{ "HUDGlassFlat:0"sv };
			return _GetObjectByName0(
				Renderer->screenAttachedElementRoot.get(),
				&screenGeomName,
				a_testScenegraph,
				a_defer);
		}

		inline static REL::THook _GetObjectByName0{ REL::ID(2224181), 0x4D6, GetObjectByName };  // PipboyMenu::ProcessMessage
		inline static REL::THook _GetObjectByName1{ REL::ID(2224614), 0x875, GetObjectByName };  // TerminalMenu::ProcessMessage
	};

	class hkGet3DRendererName
	{
	private:
		static const RE::BSFixedString& Get3DRendererName(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _Get3DRendererName0(a_this);
			}

			return detail::PipboyScreenModel::GetRendererName();
		}

		inline static REL::THook _Get3DRendererName0{ REL::ID(2224181), 0x365, Get3DRendererName };  // PipboyMenu::ProcessMessage
		inline static REL::THook _Get3DRendererName1{ REL::ID(2224616), 0x25F, Get3DRendererName };  // TerminalMenu::InitMenu
	};

	class hkSetViewport
	{
	private:
		static void SetViewport(
			[[maybe_unused]] RE::Interface3D::Renderer* a_this,
			[[maybe_unused]] Scaleform::GFx::Movie*     a_ui,
			[[maybe_unused]] const RE::NiRect<float>&   a_viewport)
		{
			if (detail::IsExempt())
			{
				return _SetViewport0(a_this, a_ui, a_viewport);
			}

			if (a_this->name != detail::PipboyScreenModel::GetRendererName())
			{
				return _SetViewport0(a_this, a_ui, a_viewport);
			}

			if (auto UI = RE::UI::GetSingleton())
			{
				if (auto TerminalMenu = UI->GetMenu<RE::TerminalMenu>())
				{
					if (MCM::Settings::Pipboy::bDisableFX && MCM::Settings::Pipboy::bUseColor)
					{
						detail::SetColorHelper(TerminalMenu.get());
						TerminalMenu->UpdateFlag(RE::UI_MENU_FLAGS::kCustomRendering, false);
					}

					Scaleform::GFx::Value root;
					if (TerminalMenu->uiMovie && TerminalMenu->uiMovie->GetVariable(&root, "root"))
					{
						root.SetMember("x", MCM::Settings::Pipboy::fTerminalMenuX.GetValue());
						root.SetMember("y", MCM::Settings::Pipboy::fTerminalMenuY.GetValue());
						root.SetMember("scaleX", MCM::Settings::Pipboy::fTerminalMenuScale.GetValue() * 0.70);
						root.SetMember("scaleY", MCM::Settings::Pipboy::fTerminalMenuScale.GetValue());
					}
				}
			}

			return _SetViewport0(a_this, a_ui, detail::FullViewport);
		}

		inline static REL::THook _SetViewport0{ REL::ID(2224616), 0x3C9, SetViewport };  // TerminalMenu::InitMenu
	};

	class hkSetCursorConstraintsRaw
	{
	private:
		static void SetCursorConstraintsRaw(
			[[maybe_unused]] RE::MenuCursor* a_this,
			[[maybe_unused]] std::uint32_t   a_x,
			[[maybe_unused]] std::uint32_t   a_y,
			[[maybe_unused]] std::uint32_t   a_w,
			[[maybe_unused]] std::uint32_t   a_h)
		{
			if (detail::IsExempt())
			{
				return _SetCursorConstraintsRaw0(a_this, a_x, a_y, a_w, a_h);
			}

			auto MenuCursor = RE::MenuCursor::GetSingleton();
			if (!MenuCursor)
			{
				return _SetCursorConstraintsRaw0(a_this, a_x, a_y, a_w, a_h);
			}

			MenuCursor->ClearConstraints();
		}

		inline static REL::THook _SetCursorConstraintsRaw0{ REL::ID(2225455), 0x07E, SetCursorConstraintsRaw };  // PipboyManager::RaisePipboy
		inline static REL::THook _SetCursorConstraintsRaw1{ REL::ID(2225455), 0x0A3, SetCursorConstraintsRaw };  // PipboyManager::RaisePipboy
		inline static REL::THook _SetCursorConstraintsRaw2{ REL::ID(2225479), 0x2D4, SetCursorConstraintsRaw };  // PipboyManager::InitPipboy
		inline static REL::THook _SetCursorConstraintsRaw3{ REL::ID(2225479), 0x2F9, SetCursorConstraintsRaw };  // PipboyManager::InitPipboy
		inline static REL::THook _SetCursorConstraintsRaw4{ REL::ID(2225488), 0x04D, SetCursorConstraintsRaw };  // PipboyManager::UpdateCursorConstraint
		inline static REL::THook _SetCursorConstraintsRaw5{ REL::ID(2225488), 0x075, SetCursorConstraintsRaw };  // PipboyManager::UpdateCursorConstraint
	};

	class hkQActorInPowerArmor
	{
	private:
		static bool QActorInPowerArmor(
			[[maybe_unused]] RE::Actor* a_actor)
		{
			if (detail::IsExempt())
			{
				return _QActorInPowerArmor0(a_actor);
			}

			return true;
		}

		inline static REL::THook _QActorInPowerArmor0{ REL::ID(2225447), 0x29, QActorInPowerArmor };  // PipboyManager::PlayPipboyGenericOpenAnim
		inline static REL::THook _QActorInPowerArmor1{ REL::ID(2225454), 0x46, QActorInPowerArmor };  // PipboyManager::LowerPipboy
		inline static REL::THook _QActorInPowerArmor2{ REL::ID(2225455), 0xC6, QActorInPowerArmor };  // PipboyManager::RaisePipboy
		inline static REL::THook _QActorInPowerArmor3{ REL::ID(2225486), 0x29, QActorInPowerArmor };  // PipboyManager::ProcessLoweringReason
	};

	class hkQActorInPowerArmorRW
	{
	private:
		static bool QActorInPowerArmor(
			[[maybe_unused]] RE::Actor* a_actor)
		{
			if (detail::IsExempt())
			{
				return _QActorInPowerArmor0(a_actor);
			}

			if (auto PlayerCamera = RE::PlayerCamera::GetSingleton())
			{
				if (PlayerCamera->currentState && PlayerCamera->currentState->id.underlying() >= RE::CameraState::k3rdPerson)
				{
					return true;
				}
			}

			return _QActorInPowerArmor0(a_actor);
		}

		inline static REL::THook _QActorInPowerArmor0{ REL::ID(2234886), 0x155, QActorInPowerArmor };  // ReadyWeaponHandler::HandleEvent
	};

	class hkPlayPipboyLoadHolotapeAnim
	{
	private:
		static void PlayPipboyLoadHolotapeAnim(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] RE::BGSNote*       a_holotape,
			[[maybe_unused]] bool               a_noAnim)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyLoadHolotapeAnim0(a_this, a_holotape, a_noAnim);
			}

			if (RE::PowerArmor::PlayerInPowerArmor())
			{
				return _PlayPipboyLoadHolotapeAnim0(a_this, a_holotape, true);
			}

			if (auto PlayerCamera = RE::PlayerCamera::GetSingleton())
			{
				if (PlayerCamera->currentState && PlayerCamera->currentState->id.underlying() >= RE::CameraState::k3rdPerson)
				{
					return _PlayPipboyLoadHolotapeAnim0(a_this, a_holotape, true);
				}
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer || !Renderer->enabled)
			{
				return _PlayPipboyLoadHolotapeAnim0(a_this, a_holotape, a_noAnim);
			}

			_PlayPipboyLoadHolotapeAnim0(a_this, a_holotape, true);
		}

		inline static REL::THook _PlayPipboyLoadHolotapeAnim0{ REL::ID(2224162), 0x147, PlayPipboyLoadHolotapeAnim };  // unk
		inline static REL::THook _PlayPipboyLoadHolotapeAnim1{ REL::ID(2224169), 0x09E, PlayPipboyLoadHolotapeAnim };  // PipboyInventoryMenu::PlayHolotape
		inline static REL::THook _PlayPipboyLoadHolotapeAnim2{ REL::ID(2234886), 0x1B3, PlayPipboyLoadHolotapeAnim };  // ReadyWeaponHandler::HandleEvent
	};

	class hkLowerPipboy
	{
	private:
		static void LowerPipboy(
			[[maybe_unused]] RE::PipboyManager*              a_this,
			[[maybe_unused]] RE::PipboyManager::LOWER_REASON a_reason)
		{
			if (detail::IsExempt())
			{
				return _LowerPipboy0(a_this, a_reason);
			}

			auto Renderer = detail::PipboyScreenModel::GetRenderer();
			if (!Renderer)
			{
				return _LowerPipboy0(a_this, a_reason);
			}

			Renderer->Disable();
			_LowerPipboy0(a_this, a_reason);
		}

		inline static REL::THook _LowerPipboy0{ REL::ID(2223010), 0x0AC, LowerPipboy };  // ExamineMenu::ShowInspectMenu
		inline static REL::THook _LowerPipboy1{ REL::ID(2248510), 0x1C3, LowerPipboy };  // BookMenu::OpenBookMenu
	};

	class hkProcessEvent
	{
	private:
		static RE::BSEventNotifyControl ProcessEvent(
			[[maybe_unused]] RE::PipboyManager*                             a_this,
			[[maybe_unused]] const RE::BSAnimationGraphEvent&               a_event,
			[[maybe_unused]] RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_source)
		{
			if (MCM::Settings::Runtime::bQuickBoyTransition)
			{
				return RE::BSEventNotifyControl::kContinue;
			}

			if (detail::IsExempt())
			{
				return _ProcessEvent0(a_this, a_event, a_source);
			}

			if (MCM::Settings::Runtime::bPlayClose && (a_event.tag == a_this->openAnimEvent || a_event.tag == "holotapeLoaded"sv))
			{
				MCM::Settings::Runtime::bPlayClose = false;
				if (auto PlayerControls = RE::PlayerControls::GetSingleton())
				{
					PlayerControls->DoAction(RE::DEFAULT_OBJECT::kActionPipboyClose, RE::ActionInput::ACTIONPRIORITY::kTry);
					if (a_this->menuToOpen == "VoiceHolotape"sv)
					{
						a_this->closeAnimEvent = "pipboyClosed"sv;
						a_this->OnPipboyCloseAnim();
						a_this->OnPipboyClosed();
					}
				}

				a_this->StopAnimationGraphListening();
			}

			return RE::BSEventNotifyControl::kContinue;
		}

		inline static REL::THookVFT _ProcessEvent0{ RE::PipboyManager::VTABLE[0], 0x01, ProcessEvent };
	};

	class hkProcessMessage
	{
	private:
		static RE::UI_MESSAGE_RESULTS ProcessMessage(
			[[maybe_unused]] RE::IMenu*     a_this,
			[[maybe_unused]] RE::UIMessage& a_message)
		{
			if (detail::IsExempt())
			{
				return _ProcessMessage0(a_this, a_message);
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

			return _ProcessMessage0(a_this, a_message);
		}

		inline static REL::THookVFT _ProcessMessage0{ RE::PipboyHolotapeMenu::VTABLE[0], 0x03, ProcessMessage };
	};

	class hkPlayPipboyOpenAnim
	{
	private:
		static void PlayPipboyOpenAnim(
			[[maybe_unused]] RE::PipboyManager*       a_this,
			[[maybe_unused]] const RE::BSFixedString& a_menu)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyOpenAnim0(a_this, a_menu);
			}

			if (!a_this->pipboyOpening)
			{
				a_this->pipboyOpening = true;
				a_this->menuToOpen = a_menu;
				a_this->openAnimEvent = "pipboyOpened"sv;
				a_this->OnPipboyOpenAnim();
				a_this->OnPipboyOpened();

				if (auto PlayerControls = RE::PlayerControls::GetSingleton())
				{
					PlayerControls->DoAction(RE::DEFAULT_OBJECT::kActionMoveStop, RE::ActionInput::ACTIONPRIORITY::kTry);
					MCM::Settings::Runtime::bWeaponDrawn = PlayerControls->DoAction(RE::DEFAULT_OBJECT::kActionSheath, RE::ActionInput::ACTIONPRIORITY::kTry);
				}
			}
		}

		inline static REL::THook _PlayPipboyOpenAnim0{ REL::ID(2219795), 0x134, PlayPipboyOpenAnim };  // UseItemCommand::DoExecute
		// inline static REL::THook _PlayPipboyOpenAnim1{ REL::ID(743427), 0x020, PlayPipboyOpenAnim };   // PipboyManager::PlayPipboyOpenTerminalAnim - inlined (maybe unused)
		inline static REL::THook _PlayPipboyOpenAnim2{ REL::ID(2249426), 0x32F, PlayPipboyOpenAnim };  // PipboyHandler::HandleEvent
	};

	class hkOnPipboyOpenAnim
	{
	private:
		static void OnPipboyOpenAnim(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (MCM::Settings::Runtime::bQuickBoyTransition)
			{
				return;
			}

			if (detail::IsExempt())
			{
				return _OnPipboyOpenAnim0(a_this);
			}

			if (detail::IsAnimOverride())
			{
				MCM::Settings::Runtime::bPlayClose = true;
				a_this->StartAnimationGraphListening();
			}

			_OnPipboyOpenAnim0(a_this);
			a_this->OnPipboyOpened();
		}

		inline static REL::THook _OnPipboyOpenAnim0{ REL::ID(2225446), 0x0247, OnPipboyOpenAnim };  // PipboyManager::PlayPipboyLoadHolotapeAnim
		inline static REL::THook _OnPipboyOpenAnim1{ REL::ID(2225447), 0x00A4, OnPipboyOpenAnim };  // PipboyManager::PlayPipboyGenericOpenAnim
		inline static REL::THook _OnPipboyOpenAnim2{ REL::ID(2229323), 0x2878, OnPipboyOpenAnim };  // TaskQueueInterface::TaskUnpackFunc
	};

	class hkPlayPipboyCloseAnim
	{
	private:
		static void PlayPipboyCloseAnim(
			[[maybe_unused]] RE::PipboyManager* a_this,
			[[maybe_unused]] bool               a_noAnim)
		{
			if (detail::IsExempt())
			{
				return _PlayPipboyCloseAnim0(a_this, a_noAnim);
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
					RE::BSUIMessageData::SendUIBoolMessage("PipboyMenu"sv, RE::UI_MESSAGE_TYPE::kHide, true);
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

				if (MCM::Settings::Runtime::bWeaponDrawn)
				{
					MCM::Settings::Runtime::bWeaponDrawn = false;
					if (auto PlayerControls = RE::PlayerControls::GetSingleton())
					{
						PlayerControls->DoAction(RE::DEFAULT_OBJECT::kActionDraw, RE::ActionInput::ACTIONPRIORITY::kTry);
					}
				}
			}
		}

		inline static REL::THook _PlayPipboyCloseAnim0{ REL::ID(2223217), 0x03F, PlayPipboyCloseAnim };  // GenericMenu::ProcessMessage
		inline static REL::THook _PlayPipboyCloseAnim1{ REL::ID(2224181), 0x21D, PlayPipboyCloseAnim };  // PipboyMenu::ProcessMessage
		inline static REL::THook _PlayPipboyCloseAnim2{ REL::ID(2224181), 0x230, PlayPipboyCloseAnim };  // PipboyMenu::ProcessMessage
		inline static REL::THook _PlayPipboyCloseAnim3{ REL::ID(2224614), 0x346, PlayPipboyCloseAnim };  // TerminalMenu::ProcessMessage
		inline static REL::THook _PlayPipboyCloseAnim4{ REL::ID(2231392), 0x232, PlayPipboyCloseAnim };  // unk
		inline static REL::THook _PlayPipboyCloseAnim5{ REL::ID(2231408), 0x105, PlayPipboyCloseAnim };  // ActorEquipManager::UseObject
	};

	class hkOnPipboyCloseAnim
	{
	private:
		static void OnPipboyCloseAnim(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (MCM::Settings::Runtime::bQuickBoyTransition)
			{
				return;
			}

			return _OnPipboyCloseAnim0(a_this);
		}

		inline static REL::THook _OnPipboyCloseAnim0{ REL::ID(2229323), 0x28B3, OnPipboyCloseAnim };  // TaskQueueInterface::TaskUnpackFunc
	};

	class hkStartPipboyMode
	{
	private:
		static void StartPipboyMode(
			[[maybe_unused]] RE::PlayerCamera* a_this,
			[[maybe_unused]] bool              a_forcePipboyModeCamera)
		{
			if (detail::IsExempt())
			{
				return _StartPipboyMode0(a_this, a_forcePipboyModeCamera);
			}

			return;
		}

		inline static REL::THook _StartPipboyMode0{ REL::ID(2225444), 0x05D, StartPipboyMode };  // PipboyManager::PlayPipboyOpenAnim
		inline static REL::THook _StartPipboyMode1{ REL::ID(2225445), 0x069, StartPipboyMode };  // PipboyManager::PlayPipboyOpenTerminalAnim
		inline static REL::THook _StartPipboyMode2{ REL::ID(2225446), 0x1A2, StartPipboyMode };  // PipboyManager::PlayPipboyLoadHolotapeAnim
		inline static REL::THook _StartPipboyMode3{ REL::ID(2225447), 0x07B, StartPipboyMode };  // PipboyManager::PlayPipboyGenericOpenAnim
	};

	class hkStopPipboyMode
	{
	private:
		static void StopPipboyMode(
			[[maybe_unused]] RE::PlayerCamera* a_this)
		{
			if (detail::IsExempt())
			{
				return _StopPipboyMode0(a_this);
			}

			return;
		}

		inline static REL::THook _StopPipboyMode0{ REL::ID(2225449), 0x10, StopPipboyMode };  // PipboyManager::OnPipboyOpenAnimFailed
		inline static REL::THook _StopPipboyMode1{ REL::ID(2225458), 0x90, StopPipboyMode };  // PipboyManager::OnPipboyClosed
		inline static REL::THook _StopPipboyMode2{ REL::ID(2225480), 0x90, StopPipboyMode };  // PipboyManager::ClosedownPipboy
	};

	class hkSetWeaponBonesCulled
	{
	private:
		static bool SetWeaponBonesCulled(
			[[maybe_unused]] RE::AIProcess*       a_this,
			[[maybe_unused]] RE::Actor&           a_actor,
			[[maybe_unused]] bool                 a_stateToSet,
			[[maybe_unused]] RE::WEAPON_CULL_TYPE a_type)
		{
			if (detail::IsExempt())
			{
				return _SetWeaponBonesCulled0(a_this, a_actor, a_stateToSet, a_type);
			}

			return true;
		}

		inline static REL::THook _SetWeaponBonesCulled0{ REL::ID(2225458), 0x11F, SetWeaponBonesCulled };  // PipboyManager::OnPipboyClosed
		inline static REL::THook _SetWeaponBonesCulled1{ REL::ID(2225479), 0x0A7, SetWeaponBonesCulled };  // PipboyManager::InitPipboy
		inline static REL::THook _SetWeaponBonesCulled2{ REL::ID(2225480), 0x11F, SetWeaponBonesCulled };  // PipboyManager::ClosedownPipboy
	};

	class hkDoAction
	{
	private:
		static bool DoAction(
			[[maybe_unused]] RE::PlayerControls*             a_this,
			[[maybe_unused]] RE::DEFAULT_OBJECT              a_action,
			[[maybe_unused]] RE::ActionInput::ACTIONPRIORITY a_priority)
		{
			if (detail::IsExempt())
			{
				return _DoAction0(a_this, a_action, a_priority);
			}

			return true;
		}

		inline static REL::THook _DoAction0{ REL::ID(2225450), 0x1D3, DoAction };  // PipboyManager::OnPipboyOpened
		inline static REL::THook _DoAction1{ REL::ID(2225452), 0x04C, DoAction };  // PipboyManager::StopExamineMenu
		inline static REL::THook _DoAction2{ REL::ID(2225454), 0x061, DoAction };  // PipboyManager::LowerPipboy
	};

	class hkQueueShowPipboy
	{
	private:
		static void QueueShowPipboy(
			[[maybe_unused]] RE::TaskQueueInterface* a_this,
			[[maybe_unused]] RE::DEFAULT_OBJECT      a_animType)
		{
			if (detail::IsExempt())
			{
				return _QueueShowPipboy0(a_this, a_animType);
			}

			return;
		}

		inline static REL::THook _QueueShowPipboy0{ REL::ID(2225444), 0x89, QueueShowPipboy };  // PipboyManager::PlayPipboyOpenAnim
	};

	class hkQueueClosePipboy
	{
	private:
		static void QueueClosePipboy(
			[[maybe_unused]] RE::TaskQueueInterface* a_this)
		{
			if (detail::IsExempt())
			{
				return _QueueClosePipboy0(a_this);
			}

			return;
		}

		inline static REL::THook _QueueClosePipboy0{ REL::ID(2225450), 0xE1, QueueClosePipboy };  // PipboyManager::OnPipboyOpened
		inline static REL::THook _QueueClosePipboy1{ REL::ID(2225456), 0xCC, QueueClosePipboy };  // PipboyManager::PlayPipboyCloseAnim
	};

	class hkSetEnableDynamicResolution
	{
	private:
		static void SetEnableDynamicResolution(
			[[maybe_unused]] RE::BSGraphics::RenderTargetManager* a_this,
			[[maybe_unused]] bool                                 a_enableDynamicResolution)
		{
			return;
		}

		inline static REL::THook _SetEnableDynamicResolution0{ REL::ID(2225457), 0x10F, SetEnableDynamicResolution };  // PipboyManager::OnPipboyCloseAnim
		inline static REL::THook _SetEnableDynamicResolution1{ REL::ID(2225479), 0x275, SetEnableDynamicResolution };  // PipboyManager::InitPipboy
	};

	class hkStopAnimationGraphListening
	{
	private:
		static void StopAnimationGraphListening(
			[[maybe_unused]] RE::PipboyManager* a_this)
		{
			if (detail::IsExempt())
			{
				return _StopAnimationGraphListening0(a_this);
			}

			if (MCM::Settings::Runtime::bPlayClose)
			{
				return;
			}

			return _StopAnimationGraphListening0(a_this);
		}

		inline static REL::THook _StopAnimationGraphListening0{ REL::ID(2225449), 0x18, StopAnimationGraphListening };  // PipboyManager::OnPipboyOpenAnimFailed
		inline static REL::THook _StopAnimationGraphListening1{ REL::ID(2225458), 0xE2, StopAnimationGraphListening };  // PipboyManager::OnPipboyClosed
		inline static REL::THook _StopAnimationGraphListening2{ REL::ID(2225480), 0xE2, StopAnimationGraphListening };  // PipboyManager::ClosedownPipboy
	};

	class hkShouldHandleEvent
	{
	private:
		static bool ShouldHandleEvent(
			[[maybe_unused]] RE::IMenu*            a_this,
			[[maybe_unused]] const RE::InputEvent* a_event)
		{
			return _ShouldHandleEvent0(a_this, a_event) && !MCM::Settings::Runtime::bQuickBoyTransition;
		}

		inline static REL::THookVFT _ShouldHandleEvent0{ RE::PipboyMenu::VTABLE[1], 0x01, ShouldHandleEvent };
	};

	class hkOnButtonEvent
	{
	private:
		static void OnButtonEvent(
			[[maybe_unused]] RE::IMenu*             a_this,
			[[maybe_unused]] const RE::ButtonEvent* a_event)
		{
			if (!MCM::Settings::Pipboy::bQuickBoyKey)
			{
				return _OnButtonEvent0(a_this, a_event);
			}

			if (a_event->QJustPressed() && (a_event->idCode == MCM::Settings::Runtime::QuickBoyKey))
			{
				ToggleQuickBoy();
				return;
			}

			return _OnButtonEvent0(a_this, a_event);
		}

		inline static REL::THookVFT _OnButtonEvent0{ RE::PipboyMenu::VTABLE[1], 0x08, OnButtonEvent };
	};

	class hkSetModelScale
	{
	private:
		static void SetModelScale(
			[[maybe_unused]] RE::Inventory3DManager* a_this,
			[[maybe_unused]] float                   a_scale)
		{
			if (detail::IsExempt())
			{
				return _SetModelScale0(a_this, a_scale);
			}

			return _SetModelScale0(a_this, MCM::Settings::Pipboy::fPipboy3DItemScale);
		}

		inline static REL::THook _SetModelScale0{ REL::ID(2225479), 0x1D7, SetModelScale };  // PipboyManager::InitPipboy
	};

	class hkSetModelScreenPosition
	{
	private:
		static void SetModelScreenPosition(
			[[maybe_unused]] RE::Inventory3DManager* a_this,
			[[maybe_unused]] const RE::NiPoint3&     a_position,
			[[maybe_unused]] bool                    a_screenCoords)
		{
			if (detail::IsExempt())
			{
				return _SetModelScreenPosition0(a_this, a_position, a_screenCoords);
			}

			RE::NiPoint3 ScreenPosition{
				MCM::Settings::Pipboy::fPipboy3DItemScreenPosX,
				MCM::Settings::Pipboy::fPipboy3DItemScreenPosY,
				1.0f,
			};
			return _SetModelScreenPosition0(a_this, ScreenPosition, a_screenCoords);
		}

		inline static REL::THook _SetModelScreenPosition0{ REL::ID(2225479), 0x1B2, SetModelScreenPosition };  // PipboyManager::InitPipboy
	};

	class hkKillScreenEffects
	{
	private:
		static void KillScreenEffects()
		{
			if (detail::IsExempt())
			{
				return _KillScreenEffects0();
			}

			if (MCM::Settings::Pipboy::bKeepLowHealthIMod)
			{
				return;
			}

			return _KillScreenEffects0();
		}

		inline static REL::THook _KillScreenEffects0{ REL::ID(2224181), 0x6B, KillScreenEffects };  // PipboyMenu::ProcessMessage
	};

	class hkInstanceFormTrigger
	{
	private:
		static void InstanceFormTrigger(
			[[maybe_unused]] const RE::BSFixedString& a_modName)
		{
			if (detail::IsExempt())
			{
				return _InstanceFormTrigger0(a_modName);
			}

			if (MCM::Settings::Pipboy::bBackgroundBlur)
			{
				return _InstanceFormTrigger0(a_modName);
			}

			return;
		}

		inline static REL::THook _InstanceFormTrigger0{ REL::ID(2225479), 0x240, InstanceFormTrigger };  // PipboyManager::InitPipboy
	};

	class hkShowPipboyLight
	{
	private:
		static void ShowPipboyLight(
			[[maybe_unused]] RE::PlayerCharacter* a_this,
			[[maybe_unused]] bool                 a_show,
			[[maybe_unused]] bool                 a_skipEffects)
		{
			if (detail::IsExempt())
			{
				return _ShowPipboyLight0(a_this, a_show, a_skipEffects);
			}

			return;
		}

		inline static REL::THook _ShowPipboyLight0{ REL::ID(2225457), 0x0A4, ShowPipboyLight };  // PipboyManager::OnPipboyCloseAnim
		inline static REL::THook _ShowPipboyLight1{ REL::ID(2225479), 0x34E, ShowPipboyLight };  // PipboyManager::InitPipboy
	};

	class hkRenderEffect
	{
	private:
		static void RenderEffect(
			[[maybe_unused]] RE::ImageSpaceManager*     a_this,
			[[maybe_unused]] std::int32_t               a_effect,  // ImageSpaceManager::ImageSpaceEffectEnum
			[[maybe_unused]] std::int32_t               a_sourceTarget,
			[[maybe_unused]] std::int32_t               a_destTarget,
			[[maybe_unused]] RE::ImageSpaceEffectParam* a_param)
		{
			if (MCM::Settings::Pipboy::bDisableFX && MCM::Settings::Pipboy::bDisableFXBoth)
			{
				return _RenderEffect0(a_this, 0x48, a_sourceTarget, a_destTarget, a_param);
			}

			return _RenderEffect0(a_this, a_effect, a_sourceTarget, a_destTarget, a_param);
		}

		inline static REL::THook _RenderEffect0{ REL::ID(2222569), 0x1C0, RenderEffect };  // Interface3D::Renderer::DrawPostFX
	};
};
