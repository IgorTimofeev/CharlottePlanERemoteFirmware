#include "UI/Navigation/MFD/Toolbar/Baro/ReferencePressureRotaryControl.hpp"
#include "RC.hpp"

namespace pizda {
	ReferencePressureRotaryControl::ReferencePressureRotaryControl() : SevenRotaryControl(5, 9000, 11000, false, 1, 10) {
		setVariants({
			&seven
		});

		setVariantIndex(0);

		seven.setDecimalSeparatorIndex(0);
		seven.setValue(RC::getInstance().getSettings().flightModeSelection.referencePressurePa / 10);
		
		updateColor();
	}
	
	std::string_view ReferencePressureRotaryControl::variantIndexToTitle(uint8_t index) {
		return "Baro";
	}
	
	bool ReferencePressureRotaryControl::isVariantEditable(const uint8_t index) {
		return index == 0;
	}
	
	void ReferencePressureRotaryControl::onRotate(const bool clockwise, const bool big) {
		SevenRotaryControl::onRotate(clockwise, big);
		
		RC::getInstance().getSettings().flightModeSelection.referencePressurePa = static_cast<uint16_t>(seven.getValue()) * 10;
		RC::getInstance().getSettings().flightModeSelection.writeLater();
		
		RC::getInstance().getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::referencePressure);
	}
	
	void ReferencePressureRotaryControl::onPress() {
		RotaryControl::onPress();
		
		RC::getInstance().getSettings().flightModeSelection.referencePressureSTD = !RC::getInstance().getSettings().flightModeSelection.referencePressureSTD;
		RC::getInstance().getSettings().flightModeSelection.writeLater();
		
		updateColor();
		
		RC::getInstance().getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::referencePressure);
	}
	
	void ReferencePressureRotaryControl::onTick() {
		RotaryControl::onTick();
		
		updateColor();
	}
	
	void ReferencePressureRotaryControl::updateColor() {
		setBorderColor(
			RC::getInstance().getSettings().flightModeSelection.referencePressureSTD
			? &Theme::fg1
			: nullptr
		);
	}
}