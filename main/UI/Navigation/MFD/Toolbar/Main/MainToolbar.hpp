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

			MarginLayout _flightControlsIndicatorMarginLayout {};
			FlightControlsIndicator _flightControlsIndicator {};
			ToolbarSection _flightControlsSection { "FCT", &_flightControlsIndicatorMarginLayout };

			MarginLayout _batteryRowsMarginLayout {};
			StackLayout _batteryRows {};
			BatteryIndicator _batteryIndicatorRC {};
			BatteryIndicator _batteryIndicatorAC {};
			ToolbarSection _batterySection { "BAT", &_batteryRowsMarginLayout };

			MarginLayout _radioMarginLayout {};
			RadioIndicator _radio {};
			ToolbarSection _radioSection { "SIG", &_radioMarginLayout };
	};
}