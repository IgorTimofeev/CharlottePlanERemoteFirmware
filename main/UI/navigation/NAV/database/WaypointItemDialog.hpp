#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"

namespace pizda {
	using namespace YOBA;

	class WaypointItemDialog : public ScrollViewDialog {
		public:
			explicit WaypointItemDialog(uint16_t waypointIndex);

		private:
			Button _removeButton {};
	};
}
