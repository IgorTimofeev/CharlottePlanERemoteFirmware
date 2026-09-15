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

			Divider _PFDDivider {};

			// -------------------------------- Speed --------------------------------

			TextView _speedTitle {};

			TextField _speedVS0 {};
			Titler _speedVS0Title { "Stall speed in ldg cnf (Vs0)", &_speedVS0 };

			TextField _speedVFE {};
			Titler _speedVFETitle { "Max flap extended speed (Vfe)", &_speedVFE };

			TextField _speedVNO {};
			Titler _speedVNOTitle { "Max cruising speed for norm op (Vno)", &_speedVNO };

			TextField _speedVNE {};
			Titler _speedVNETitle { "Never exceed speed (Vne)", &_speedVNE };

			Divider _speedDivider {};

			// -------------------------------- ND --------------------------------

			TextView _NDTitle {};

			// Earth grid
			TextAndSwitch _NDEarthGrid { "Earth grid" };

			void setupPageTitle(TextView* textView, std::string_view text);
			void setupTitler(Titler* titler);

			void setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter);

			void setupUint16TextField(TextField& textField, uint16_t* value);
	};
}
