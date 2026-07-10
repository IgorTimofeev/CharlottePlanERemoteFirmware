#include "UI/Navigation/MFD/Toolbar/Main/MainToolbar.hpp"
#include "RC.hpp"
#include "Resources/Images.hpp"
#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"

namespace pizda {
	MainToolbar::MainToolbar() {
		// ----------------------------- Left -----------------------------
		
		leftRow.setOrientation(Orientation::horizontal);
		leftRow.setHorizontalAlignment(Alignment::start);
		*this += &leftRow;

		// Controls
		ToolbarSection::setDefaultMargin(&_flightControlsIndicatorMarginLayout, 3);
		_flightControlsIndicatorMarginLayout += &_flightControlsIndicator;
		_flightControlsSection.setFocusable(false);
		leftRow += &_flightControlsSection;

		// Throttle
		leftRow += &_throttleSection;
		
		// ----------------------------- Right -----------------------------
		
		rightRow.setOrientation(Orientation::horizontal);
		rightRow.setHorizontalAlignment(Alignment::end);
		*this += &rightRow;
		
		// Radio
		ToolbarSection::setDefaultMargin(&_radioMarginLayout, 8);
		_radioMarginLayout += &_radio;
		_radioSection.setFocusable(false);
		rightRow += &_radioSection;
		
		// Battery
		_batteryRows.setGap(3);
		ToolbarSection::setDefaultMargin(&_batteryRowsMarginLayout, 4);
		_batteryRowsMarginLayout += &_batteryRows;
		_batteryRows += &_batteryIndicatorRC;
		_batteryRows += &_batteryIndicatorAC;
		_batterySection.setFocusable(false);
		rightRow += &_batterySection;
	}

	void MainToolbar::onTick() {
		Layout::onTick();

		auto& rc = RC::getInstance();
		
		// ----------------------------- Battery -----------------------------

		// Remote
		_batteryIndicatorRC.setVoltage(rc.getBattery().getVoltageMV());
		_batteryIndicatorRC.setCharge(rc.getBattery().getCharge16());

		// Aircraft
		_batteryIndicatorAC.setVoltage(
			rc.getTransceiver().isConnected()
			? rc.getAircraftData().raw.batteryVoltageMV
			: BatteryIndicator::voltageNotAvailable
		);

		_batteryIndicatorAC.setCharge(
			rc.getTransceiver().isConnected()
			? static_cast<uint16_t>(
				rc.getAircraftData().raw.batteryVoltageMV < config::battery::aircraft::voltageMin
				? 0
				: (
					(rc.getAircraftData().raw.batteryVoltageMV - config::battery::aircraft::voltageMin)
					* 0xFFFF
					/ (config::battery::aircraft::voltageMax - config::battery::aircraft::voltageMin)
				)
			)
			: 0
		);
	}
}