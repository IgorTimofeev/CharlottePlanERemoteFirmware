#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarButton.hpp"
#include "UI/Navigation/MFD/Toolbar/Autopilot/SpeedRotaryControl.hpp"
#include "UI/Navigation/MFD/Toolbar/Autopilot/LateralRotaryControl.hpp"
#include "UI/Navigation/MFD/Toolbar/Autopilot/VerticalRotaryControl.hpp"

#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;
	
	class AutopilotToolbar : public RowToolbar {
		public:
			explicit AutopilotToolbar();
		
		protected:
			void onTick() override;
		
		private:
			ImageToolbarButton flightDirector { "FD", &resources::images::menuIconMFDAutopilotFlightDirector };
			
			SpeedRotaryControl speed {};
			LateralRotaryControl lateral {};
			VerticalRotaryControl vertical {};
			
			ImageToolbarButton autopilot { "A/P", &resources::images::menuIconMFDAutopilotEngage };

	};
}