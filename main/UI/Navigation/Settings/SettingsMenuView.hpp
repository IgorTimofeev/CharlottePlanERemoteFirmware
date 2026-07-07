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
			
			std::array<PageMenuViewButton, 7> _buttons {
				PageMenuViewButton(&resources::images::menuIconPersonalization, "Personal", &Routes::settingsPersonalization),
				PageMenuViewButton(&resources::images::menuIconADIRS, "ADIRS", &Routes::settingsADIRS),
				PageMenuViewButton(&resources::images::menuIconMotors, "Motors", &Routes::settingsMotors),
				PageMenuViewButton(&resources::images::menuIconTransceiverImage, "XCVR", &Routes::settingsTransceiver),
				PageMenuViewButton(&resources::images::menuIconAxes, "Axes", &Routes::settingsAxes),
				PageMenuViewButton(&resources::images::menuIconSpectrumScan, "Scan", &Routes::settingsSpectrumScan),
				PageMenuViewButton(&resources::images::menuIconAutopilotSettings, "Autopilot", &Routes::settingsAutopilot),
			};
	};
}