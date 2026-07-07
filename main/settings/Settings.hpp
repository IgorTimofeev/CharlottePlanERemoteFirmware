#pragma once

#include "Settings/ControlSettings.hpp"
#include "Settings/AxesSettings.hpp"
#include "Settings/AutopilotSettings.hpp"
#include "Settings/PersonalizationSettings.hpp"
#include "Settings/NavigationSettings.hpp"
#include "Settings/MotorsSettings.hpp"
#include "Settings/TransceiverSettings.hpp"
#include "Settings/ADIRSSettings.hpp"

namespace pizda {
	class Settings {
		public:
			ADIRSSettings ADIRS {};
			ControlSettings controls {};
			AxesSettings axes {};
			AutopilotSettings autopilot {};
			PersonalizationSettings personalization {};
			NavigationSettings navigation {};
			MotorsSettings motors {};
			TransceiverSettings transceiver {};

			void readAll() {
				ADIRS.read();
				controls.read();
				axes.read();
				autopilot.read();
				personalization.read();
				navigation.read();
				motors.read();
				transceiver.read();
			}
	};
}
