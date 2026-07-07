#pragma once

#include "UI/Navigation/Route.hpp"
#include "UI/Navigation/MFD/MFDPage.hpp"

#include "UI/Navigation/NAV/FlightPlan/FlightPlanPage.hpp"
#include "UI/Navigation/NAV/Database/DatabasePage.hpp"

#include "UI/Navigation/Settings/Personalization/personalizationSettingsPage.hpp"
#include "UI/Navigation/Settings/ADIRS/ADIRSSettingsPage.hpp"
#include "UI/Navigation/Settings/SpectrumScan/spectrumScanPage.hpp"
#include "UI/Navigation/Settings/Autopilot/autopilotSettingsPage.hpp"
#include "UI/Navigation/Settings/Motors/motorsSettingsPage.hpp"
#include "UI/Navigation/Settings/Axis/axesSettingsPage.hpp"
#include "UI/Navigation/Settings/Transceiver/transceiverSettingsPage.hpp"

namespace pizda {
	class Routes {
		public:
			constexpr static ElementRoute<MFDPage> MFD {};

			constexpr static ElementRoute<FlightPlanPage> navFlightPlan {};
			constexpr static ElementRoute<DatabasePage> navWaypoints {};

			constexpr static ElementRoute<PersonalizationSettingsPage> settingsPersonalization {};
			constexpr static ElementRoute<ADIRSSettingsPage> settingsADIRS {};
			constexpr static ElementRoute<SpectrumScanPage> settingsSpectrumScan {};
			constexpr static ElementRoute<AutopilotSettingsPage> settingsAutopilot {};
			constexpr static ElementRoute<MotorsSettingsPage> settingsMotors {};
			constexpr static ElementRoute<AxesSettingsPage> settingsAxes {};
			constexpr static ElementRoute<TransceiverSettingsPage> settingsTransceiver {};
	};
}