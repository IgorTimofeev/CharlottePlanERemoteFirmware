#pragma once

#include "Resources/Sounds/BootSound.hpp"
#include "Resources/Sounds/TransceiverConnectSound.hpp"
#include "Resources/Sounds/TransceiverDisconnectSound.hpp"
#include "Resources/Sounds/EngagedSound.hpp"
#include "Resources/Sounds/DisengagedSound.hpp"
#include "Resources/Sounds/FeedbackSound.hpp"

namespace pizda {
	class Sounds {
		public:
			constexpr static BootSound boot {};
			constexpr static FeedbackSound feedback {};
			constexpr static TransceiverConnectSound transceiverConnect {};
			constexpr static TransceiverDisconnectSound transceiverDisconnect {};
			constexpr static EngagedSound engaged {};
			constexpr static DisengagedSound disengaged {};
	};
}