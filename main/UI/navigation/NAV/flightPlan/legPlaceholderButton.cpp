#include "UI/Navigation/NAV/FlightPlan/LegPlaceholderButton.hpp"
#include "UI/Navigation/NAV/FlightPlan/FlightPlanItemDialog.hpp"

#include "UI/Theme.hpp"
#include "UI/Elements/Navigation/WaypointButton.hpp"
#include "Types/NavigationData.hpp"
#include "RC.hpp"

namespace pizda {
	LegPlaceholderButton::LegPlaceholderButton() {
		Theme::applyPlaceholder(this);
		setHeight(WaypointButton::height);
		setText("Add route");
	}

	void LegPlaceholderButton::onClick() {
		Button::onClick();

		FlightPlanItemDialog::showWaypointSelectionDialogToInsertAt(getText(), RC::getInstance().getNavigationData().flightPlan.legs.size());
	}
}
