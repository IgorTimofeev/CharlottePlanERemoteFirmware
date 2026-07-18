#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class WaypointItemDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			explicit WaypointItemDialog(uint16_t waypointIndex);

		private:
			TextButton _removeButton {};
	};
}
