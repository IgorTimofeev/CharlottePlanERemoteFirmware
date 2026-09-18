#pragma once

#include <functional>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "Systems/Transceiver/Packet.hpp"
#include "UI/Navigation/Page.hpp"

namespace pizda {
	using namespace YOBA;

	class MFDSettingsPage : public ScrollViewPage {
		public:
			MFDSettingsPage();
			~MFDSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			// -------------------------------- PFD --------------------------------

			// FOV
			Slider _PFDFOVSlider {};
			Titler _PFDFOVTitle { "Field of view", &_PFDFOVSlider };

			// Waypoint labels
			TextAndSwitch _PFDWaypointLabels { "Waypoint labels" };

			// Earth grid
			TextAndSwitch _NDEarthGrid { "Earth grid" };

			Divider _PFDDivider {};

			// -------------------------------- Speed tape --------------------------------

			TextView _speedTapeTitle {};

			TextField _speedTapeMinorTickStep {};
			Titler _speedTapeMinorTickStepTitle { "Minor tick step (kt)", &_speedTapeMinorTickStep };

			TextField _speedTapeMajorTickStep {};
			Titler _speedTapeMajorTickStepTitle { "Major tick step (kt)", &_speedTapeMajorTickStep };

			Divider _speedTapeDivider {};


			// -------------------------------- Altitude tape --------------------------------

			TextView _altitudeTapeTitle {};

			TextField _altitudeTapeMinorTickStep {};
			Titler _altitudeTapeMinorTickStepTitle { "Minor tick step (ft)", &_altitudeTapeMinorTickStep };

			TextField _altitudeTapeMajorTickStep {};
			Titler _altitudeTapeMajorTickStepTitle { "Major tick step (ft)", &_altitudeTapeMajorTickStep };

			void setupPageTitle(TextView* textView, std::string_view text);
			void setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter);
			void setupUint8TextField(TextField& textField, uint8_t* value);
	};
}
