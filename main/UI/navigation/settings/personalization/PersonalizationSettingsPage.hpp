#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"
#include "UI/Elements/Titler.hpp"
#include "UI/Elements/Switcher.hpp"
#include "UI/Elements/Separator.hpp"

namespace pizda {
	using namespace YOBA;

	class PersonalizationSettingsPage : public ScrollViewPage {
		public:
			PersonalizationSettingsPage();
			~PersonalizationSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			// -------------------------------- General --------------------------------
			
			Switcher _generalAudioFeedback { "Audio feedback" };
			Switcher _generalDebugOverlay { "Debug overlay" };
			Switcher _generalDataInterpolation { "Data interpolation" };
			HorizontalSeparator _generalSeparator {};

			// -------------------------------- PFD --------------------------------

			TextView _PFDTitle {};

			// FOV
			Slider _PFDFOVSlider {};
			Titler _PFDFOVTitle = Titler("Field of view", &_PFDFOVSlider);

			// Waypoint labels
			Switcher _PFDWaypointLabels { "Waypoint labels" };

			HorizontalSeparator _PFDSeparator {};

			// -------------------------------- ND --------------------------------

			TextView _NDTitle {};

			// Earth grid
			Switcher _NDEarthGrid { "Earth grid" };
	};
}