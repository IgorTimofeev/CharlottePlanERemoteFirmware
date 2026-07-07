#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/MFD/Toolbar/Main/ThrottleSection.hpp"
#include "UI/Navigation/MFD/Toolbar/Main/FlightControlsIndicator.hpp"
#include "UI/Navigation/MFD/Toolbar/Main/BatteryIndicator.hpp"
#include "UI/Navigation/MFD/Toolbar/Main/RadioIndicator.hpp"

#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarSection.hpp"

namespace pizda {
	using namespace YOBA;

	class MainToolbar : public Toolbar {
		public:
			MainToolbar();

		protected:
			void onTick() override;

		private:
			StackLayout leftRow {};
			StackLayout rightRow {};
			
			ThrottleSection _throttleSection {};

			FlightControlsIndicator _flightControlsIndicator {};
			ToolbarSection _flightControlsSection = { "FCT", &_flightControlsIndicator };

			BatteryIndicator _batteryIndicatorRC {};
			BatteryIndicator _batteryIndicatorAC {};
			StackLayout _batteryRows {};
			ToolbarSection _batterySection = { "BAT", &_batteryRows };

			RadioIndicator _radio {};
			ToolbarSection _radioSection = { "SIG", &_radio };
	};
}