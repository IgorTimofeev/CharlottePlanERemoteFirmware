#include "UI/Navigation/MFD/Toolbar/Main/ThrottleSection.hpp"
#include "RC.hpp"
#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "Resources/Sounds.hpp"

namespace pizda {
	ThrottleSection::ThrottleSection() : ToolbarSection("THR") {
		setFocusable(false);

		setDefaultMargin(&rowMargin, 6);
		row.setLayoutTransform(&rowMargin);

		row.setGap(7);
		row += &throttleIndicator1;
		row += &throttleIndicator2;
		*this += &row;
	}

	void ThrottleSection::onTick() {
		Layout::onTick();

		auto& rc = RC::getInstance();

		// Throttles
		throttleIndicator1.setRemoteValue(rc.getAxes().getLeverLeft().getFilteredValueUint8());
		throttleIndicator1.setAircraftValue(static_cast<uint8_t>(rc.getAircraftData().computed.throttle_0_1 * 0xFF));
		
		throttleIndicator2.setRemoteValue(throttleIndicator1.getRemoteValue());
		throttleIndicator2.setAircraftValue(throttleIndicator1.getAircraftValue());
	}
}