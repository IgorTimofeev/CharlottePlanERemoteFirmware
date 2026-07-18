#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class FlightPlanItemDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			explicit FlightPlanItemDialog(uint16_t legIndex);

			static void showWaypointSelectionDialogToInsertAt(
				std::string_view title,
				size_t insertAt
			);

		private:
			TextButton _activateLegButton {};
			TextButton _editButton {};
			TextButton _insertBeforeButton {};
			TextButton _insertAfterButton {};
			TextButton _removeButton {};

			void insertOnButtonClick(const std::string& title, uint16_t insertAt);
	};
}
