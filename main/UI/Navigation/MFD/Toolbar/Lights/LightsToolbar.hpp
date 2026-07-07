#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include "UI/Theme.hpp"

#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarSection.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarButton.hpp"
#include "UI/Navigation/MFD/Toolbar/RotaryControl.hpp"
#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;
	
	class LightsToolbar : public RowToolbar {
		public:
			explicit LightsToolbar();
		
		protected:
			void onTick() override;
			
		private:
			ImageToolbarButton navigation { "Nav", &Images::menuIconMFDLightsNavigation };
			ImageToolbarButton strobe { "Strobe", &Images::menuIconMFDLightsStrobe };
			ImageToolbarButton landing { "Landing", &Images::menuIconMFDLightsLanding };
			ImageToolbarButton cabin { "Cabin", &Images::menuIconMFDLightsCabin };
			
			void copyAircraftToRemote();
	};
}