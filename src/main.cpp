#include "Hooks/Hooks.h"
#include "Scripts/Papyrus.h"
#include "Serialization/Serialization.h"

namespace
{
	void MessageCallback(F4SE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case F4SE::MessagingInterface::kGameDataReady:
			if (static_cast<bool>(a_msg->data))
			{
				Hooks::Install();
			}
			break;
		default:
			break;
		}
	}
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se, { .trampoline = true, .trampolineSize = 512 });

	Serialization::Register();

	F4SE::GetMessagingInterface()->RegisterListener(MessageCallback);
	F4SE::GetPapyrusInterface()->Register(Papyrus::BakaFullscreenPipboy::Register);

	return true;
}
