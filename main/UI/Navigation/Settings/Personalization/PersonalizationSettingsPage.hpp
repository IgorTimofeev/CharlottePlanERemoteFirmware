#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"

namespace pizda {
	using namespace YOBA;

	class PersonalizationSettingsPage : public ScrollViewPage {
		public:
			PersonalizationSettingsPage();
			~PersonalizationSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			// -------------------------------- General --------------------------------

			TextAndSwitch _generalDarkTheme { "Dark theme" };
			TextAndSwitch _generalAudioFeedback { "Audio feedback" };
			TextAndSwitch _generalDataInterpolation { "Data interpolation" };
			TextAndSwitch _generalDebugOverlay { "Debug overlay" };

			// -------------------------------- PFD --------------------------------

			Divider _PFDDivider {};
			TextView _PFDTitle { "PFD" };

			// FOV
			Slider _PFDFOVSlider {};
			Titler _PFDFOVTitle { "Field of view", &_PFDFOVSlider };

			// Waypoint labels
			TextAndSwitch _PFDWaypointLabels { "Waypoint labels" };

			// Speed tape
			TextField _speedTapeMinorTickStep {};
			Titler _speedTapeMinorTickStepTitle { "Spd minor tick step (kt)", &_speedTapeMinorTickStep };

			TextField _speedTapeMajorTickStep {};
			Titler _speedTapeMajorTickStepTitle { "Spd major tick step (kt)", &_speedTapeMajorTickStep };

			// Altitude tape
			TextField _altitudeTapeMinorTickStep {};
			Titler _altitudeTapeMinorTickStepTitle { "Alt minor tick step (ft)", &_altitudeTapeMinorTickStep };

			TextField _altitudeTapeMajorTickStep {};
			Titler _altitudeTapeMajorTickStepTitle { "Alt major tick step (ft)", &_altitudeTapeMajorTickStep };

			// -------------------------------- N/D --------------------------------

			Divider _NDDivider {};

			TextView _NDTitle { "N/D" };

			// Earth grid
			TextAndSwitch _NDEarthGrid { "Earth grid" };

			void setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter);
			void setupUint8TextField(TextField& textField, uint8_t* value);
	};
}