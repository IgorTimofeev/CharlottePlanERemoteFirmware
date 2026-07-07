#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"

namespace pizda {
	using namespace YOBA;

	class FlightPlanItemDialog : public ScrollViewDialog {
		public:
			explicit FlightPlanItemDialog(uint16_t legIndex);

			static void showWaypointSelectionDialogToInsertAt(
				std::string_view title,
				size_t insertAt
			);

		private:
			Button _activateLegButton {};
			Button _editButton {};
			Button _insertBeforeButton {};
			Button _insertAfterButton {};
			Button _removeButton {};

			void insertOnButtonClick(const std::string& title, uint16_t insertAt);
	};
}
