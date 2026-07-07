#include "UI/Navigation/MFD/Toolbar/Baro/BaroToolbar.hpp"
#include "RC.hpp"

namespace pizda {
	BaroToolbar::BaroToolbar() {
		auto& rc = RC::getInstance();

		row += &pressure;
		row += &minimums;

		// Metric units
		metricUnits.setActive(rc.getSettings().personalization.MFD.PFD.metricUnits);

		metricUnits.onPressed = [this, &rc] {
			rc.getSettings().personalization.MFD.PFD.metricUnits = !rc.getSettings().personalization.MFD.PFD.metricUnits;
			rc.getSettings().personalization.writeLater();

			metricUnits.setActive(rc.getSettings().personalization.MFD.PFD.metricUnits);

			rc.playFeedback();
		};

		row += &metricUnits;
	}
}
