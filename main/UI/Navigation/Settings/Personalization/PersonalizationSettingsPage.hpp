#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"
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

			TextAndSwitch _darkTheme { "Dark theme" };
			TextAndSwitch _generalAudioFeedback { "Audio feedback" };
			TextAndSwitch _generalDataInterpolation { "Data interpolation" };
			TextAndSwitch _generalDebugOverlay { "Debug overlay" };
			HorizontalSeparator _generalSeparator {};

			// -------------------------------- PFD --------------------------------

			TextView _PFDTitle {};

			// FOV
			Slider _PFDFOVSlider {};
			Titler _PFDFOVTitle { "Field of view", &_PFDFOVSlider };

			// Waypoint labels
			TextAndSwitch _PFDWaypointLabels { "Waypoint labels" };

			HorizontalSeparator _PFDSeparator {};

			// -------------------------------- ND --------------------------------

			TextView _NDTitle {};

			// Earth grid
			TextAndSwitch _NDEarthGrid { "Earth grid" };
	};
}