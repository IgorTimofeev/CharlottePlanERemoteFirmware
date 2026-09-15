#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Menu/PagesMenuView.hpp"
#include "UI/Navigation/Menu/PageMenuViewButton.hpp"
#include "UI/Navigation/Routes.hpp"
#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;

	class SettingsMenuView : public PagesMenuView {
		public:
			void setup() override;
		
		private:
			static const Route* _lastRoute;
			
			std::array<PageMenuViewButton, 8> _buttons {
				PageMenuViewButton(&Images::menuIconPersonalization, "Personal", &Routes::settingsPersonalization),
				PageMenuViewButton(&Images::menuIconMFDSettings, "MFD", &Routes::settingsMFD),
				PageMenuViewButton(&Images::menuIconAutopilotSettings, "Autopilot", &Routes::settingsAutopilot),
				PageMenuViewButton(&Images::menuIconADIRS, "ADIRS", &Routes::settingsADIRS),
				PageMenuViewButton(&Images::menuIconMotors, "Motors", &Routes::settingsMotors),
				PageMenuViewButton(&Images::menuIconTransceiver, "XCVR", &Routes::settingsTransceiver),
				PageMenuViewButton(&Images::menuIconAxes, "Axes", &Routes::settingsAxes),
				PageMenuViewButton(&Images::menuIconSpectrumScan, "Scan", &Routes::settingsSpectrumScan),
			};
	};
}