#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Elements/Titler.hpp"
#include "UI/Elements/Navigation/SelectWaypointDialog.hpp"
#include "UI/Elements/Navigation/WaypointButton.hpp"
#include "UI/Elements/TabSelector.hpp"

#include "Types/NavigationData.hpp"

namespace pizda {
	using namespace YOBA;

	class WaypointDialogSelectedItem : public NavigationWaypointDataIndexAware {
		public:
			WaypointDialogSelectedItem(const uint16_t waypointIndex) : NavigationWaypointDataIndexAware(waypointIndex) {

			}
	};

	class SelectWaypointDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			static void select(
				std::string_view titleText,
				const std::function<void(const WaypointDialogSelectedItem& selectedItem)>& onConfirm
			);

			static void edit(
				std::string_view titleText,
				const WaypointDialogSelectedItem& selectedItem,
				const std::function<void(const WaypointDialogSelectedItem& selectedItem)>& onConfirm
			);

		private:
			SelectWaypointDialog(
				std::string_view titleText,
				const std::optional<WaypointDialogSelectedItem>& selectedItem,
				const std::function<void(const WaypointDialogSelectedItem& selectedItem)>& onConfirm
			);

			TextField _searchTextField {};
			Titler _searchTextFieldTitle { "Search", &_searchTextField };

			WaypointButton _waypointButton {};
			Titler _waypointTitle = { "Waypoint", &_waypointButton };

			Button _confirmButton {};

			void updateVisualsFromWaypoint(uint16_t waypointIndex, const NavigationWaypointData& waypointData);
	};
}
