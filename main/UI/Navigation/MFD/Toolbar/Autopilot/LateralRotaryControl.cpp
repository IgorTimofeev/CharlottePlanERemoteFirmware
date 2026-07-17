#include "UI/Navigation/MFD/Toolbar/Autopilot/LateralRotaryControl.hpp"
#include "RC.hpp"

namespace pizda {
	LateralRotaryControlStab::LateralRotaryControlStab() {
		setDigitCount(3);
		setSignVisible(true);

		setActiveColor(&Theme::magenta1);
	}

	void LateralRotaryControlStab::onTick() {
		RotaryControlSevenVariant::onTick();

		setValue(static_cast<int32_t>(std::round(Math::toDegrees(RC::getInstance().getAircraftData().computed.autopilot.rollRad))));
	}

	LateralRotaryControl::LateralRotaryControl() : SevenRotaryControl(3, 1, 360, true, 1, 10) {
		setVariants({
			&seven,
			&stab
		});

		seven.setValue(RC::getInstance().getSettings().flightModeSelection.headingDeg);

		switch (RC::getInstance().getSettings().flightModeSelection.lateralMode) {
			case AutopilotLateralMode::stab:
				setVariantIndex(1);
				break;

			default:
				setVariantIndex(0);
				break;
		}
	}
	
	std::string_view LateralRotaryControl::variantIndexToTitle(const uint8_t index) {
		switch (index) {
			case 0: return "HDG";
			default: return "LSTB";
		}
	}
	
	bool LateralRotaryControl::isVariantEditable(const uint8_t index) {
		return index == 0;
	}
	
	void LateralRotaryControl::onRotate(const bool clockwise, const bool big) {
		SevenRotaryControl::onRotate(clockwise, big);

		auto& rc = RC::getInstance();

		rc.getSettings().flightModeSelection.headingDeg = static_cast<uint16_t>(seven.getValue());
		rc.getSettings().flightModeSelection.writeLater();

		rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::autopilotHeading);
	}

	void LateralRotaryControl::onVariantChanged() {
		auto& rc = RC::getInstance();

		switch (getVariantIndex()) {
			case 0:
				rc.getSettings().flightModeSelection.lateralMode = AutopilotLateralMode::hdg;
				break;

			default:
				rc.getSettings().flightModeSelection.lateralMode = AutopilotLateralMode::stab;
				break;
		}

		rc.getSettings().flightModeSelection.writeLater();
	}
	
	void LateralRotaryControl::onPress() {
		RotaryControl::onPress();

		auto& rc = RC::getInstance();

		rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::autopilotLateralMode);
	}
	
	void LateralRotaryControl::onTick() {
		RotaryControl::onTick();
		
		switch (RC::getInstance().getAircraftData().raw.autopilot.lateralMode) {
			case AutopilotLateralMode::dir:
				setBorderColor(nullptr);
				break;

			case AutopilotLateralMode::stab:
				setBorderColor(getVariantIndex() == 1 ? &Theme::fg1 : &Theme::yellow);
				break;

			case AutopilotLateralMode::hdg:
				setBorderColor(getVariantIndex() == 0 ? &Theme::fg1 : &Theme::yellow);
				break;
		}
	}
}