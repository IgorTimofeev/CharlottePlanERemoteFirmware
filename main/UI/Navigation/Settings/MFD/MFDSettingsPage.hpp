#pragma once

#include <functional>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

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

			// -------------------------------- Speed ranges --------------------------------

			TextView _speedRangesTitle {};

			RelativeStackLayout _speedRangesColumns {};

			RelativeStackLayout _speedRangesBandRows {};

			StackLayout _speedRangesTextFieldRows {};

			RectangularShape _speedRangesPreVS0Band {};

			RectangularShape _speedRangesVS0Band {};
			TextField _speedRangesVS0TextField {};
			Titler _speedRangesVS0Title { "Stall speed in ldg cnf (Vs0)", &_speedRangesVS0TextField };

			RectangularShape _speedRangesVFEBand {};
			TextField _speedRangesVFETextField {};
			Titler _speedRangesVFETitle { "Max flap ext speed (Vfe)", &_speedRangesVFETextField };

			RectangularShape _speedRangesVNOBand {};
			TextField _speedRangesVNOTextField {};
			Titler _speedRangesVNOTitle { "Max cruising speed (Vno)", &_speedRangesVNOTextField };

			RectangularShape _speedRangesVNEBand {};
			TextField _speedRangesVNETextField {};
			Titler _speedRangesVNETitle { "Never exceed speed (Vne)", &_speedRangesVNETextField };

			Divider _speedRangesDivider {};

			// -------------------------------- Altitude tape --------------------------------

			TextView _altitudeTapeTitle {};

			TextField _altitudeTapeMinorTickStep {};
			Titler _altitudeTapeMinorTickStepTitle { "Minor tick step (ft)", &_altitudeTapeMinorTickStep };

			TextField _altitudeTapeMajorTickStep {};
			Titler _altitudeTapeMajorTickStepTitle { "Major tick step (ft)", &_altitudeTapeMajorTickStep };


			void setupPageTitle(TextView* textView, std::string_view text);
			void setupTitler(Titler* titler);

			void setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter);
			void setupUint8TextField(TextField& textField, uint8_t* value);
			void setupUint16TextField(TextField& textField, uint16_t* value);

			void setupSpeedBand(RectangularShape& band, const Color* color);
	};
}
