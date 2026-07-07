#pragma once

#include "Settings/ControlSettings.hpp"
#include "Settings/AxesSettings.hpp"
#include "Settings/PersonalizationSettings.hpp"
#include "Settings/NavigationSettings.hpp"
#include "Settings/MotorsSettings.hpp"
#include "Settings/TransceiverSettings.hpp"
#include "Settings/AutopilotConfigurationSettings.hpp"
#include "Settings/FlightModeSelectionSettings.hpp"

namespace pizda {
	class Settings {
		public:
			ControlSettings controls {};
			AxesSettings axes {};
			PersonalizationSettings personalization {};
			NavigationSettings navigation {};
			MotorsSettings motors {};
			TransceiverSettings transceiver {};
			AutopilotConfigurationSettings APConfiguration {};
			FlightModeSelectionSettings flightModeSelection {};

			void readAll() {
				flightModeSelection.read();
				controls.read();
				axes.read();
				personalization.read();
				navigation.read();
				motors.read();
				transceiver.read();
				APConfiguration.read();
				flightModeSelection.read();
			}
	};
}
