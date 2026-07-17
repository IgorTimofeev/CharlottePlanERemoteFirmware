#pragma once

#include "UI/Elements/Navigation/WaypointButton.hpp"
#include "UI/Navigation/NAV/Database/WaypointItemDialog.hpp"

namespace pizda {
	class WaypointItem : public WaypointButton {
		public:
			explicit WaypointItem(uint32_t waypointIndex) : WaypointButton(waypointIndex) {

			}

		protected:
			void onClick() override {
				if (getWaypointIndex() < 0)
					return;

				Theme::openDialog(new WaypointItemDialog(getWaypointIndex()));
			}
	};
}
