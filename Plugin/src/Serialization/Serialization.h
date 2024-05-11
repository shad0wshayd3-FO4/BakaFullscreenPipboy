#pragma once

#include "MCM/MCM.h"

namespace Serialization
{
	namespace
	{
		void RevertCallback([[maybe_unused]] const F4SE::SerializationInterface* a_intfc)
		{
			MCM::Settings::Runtime::bQuickBoy = true;
			// MCM::Settings::Runtime::bQuickBoyTransition = false;
		}

		void SaveCallback([[maybe_unused]] const F4SE::SerializationInterface* a_intfc)
		{
			a_intfc->WriteRecord('BQBE', 1, &MCM::Settings::Runtime::bQuickBoy, sizeof(bool));
		}

		void LoadCallback([[maybe_unused]] const F4SE::SerializationInterface* a_intfc)
		{
			RevertCallback(a_intfc);

			std::uint32_t sig{ 0 }, ver{ 0 }, len{ 0 };
			while (a_intfc->GetNextRecordInfo(sig, ver, len))
			{
				if (sig == 'BQBE')
				{
					a_intfc->ReadRecordData(&MCM::Settings::Runtime::bQuickBoy, sizeof(bool));
					break;
				}
			}
		}
	}

	bool Register()
	{
		const auto serialization = F4SE::GetSerializationInterface();
		if (!serialization)
		{
			logger::critical("Failed to register Serialization callbacks, marking as incompatible."sv);
			return false;
		}

		serialization->SetUniqueID(static_cast<std::uint32_t>('BFSP'));
		serialization->SetRevertCallback(RevertCallback);
		serialization->SetSaveCallback(SaveCallback);
		serialization->SetLoadCallback(LoadCallback);

		return true;
	}
}
