#include "UI/Navigation/NAV/Database/WaypointItemDialog.hpp"
#include "UI/Navigation/NAV/Database/DatabasePage.hpp"

#include "Types/NavigationData.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	WaypointItemDialog::WaypointItemDialog(uint16_t waypointIndex) {
		auto& rc = RC::getInstance();
		const auto& waypointData = rc.getNavigationData().waypoints[waypointIndex];

		Theme::apply(this);

		titleTextView.setText(waypointData.name);

		// Remove button
		Theme::applyCritical(&_removeButton);
		_removeButton.setText("Delete");

		_removeButton.setOnClick([&rc, waypointIndex, this] {
			rc.getApplication().invokeLater([&rc, waypointIndex, this] {
				Theme::closeDialog(this);

				rc.getNavigationData().removeWaypointAt(waypointIndex);

				const auto page = DatabasePage::getInstance();

				if (page)
					page->updateFromNavigationData();
			});
		});

		contentStackLayout += &_removeButton;
	}
}