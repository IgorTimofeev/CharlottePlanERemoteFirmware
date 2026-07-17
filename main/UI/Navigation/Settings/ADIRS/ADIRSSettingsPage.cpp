#include <cstdio>

#include "UI/Navigation/Settings/ADIRS/ADIRSSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	ADIRSSettingsPage::ADIRSSettingsPage() {
		// ----------------------------- ADIRS -----------------------------

		title.setText("ADIRS");

		// Magnetic declination
		Theme::apply(&_ADIRSMagneticDeclinationTextField);
		_ADIRSMagneticDeclinationTextField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);
		_ADIRSMagneticDeclinationTextField.setText(std::to_string(RC::getInstance().getSettings().flightModeSelection.magneticDeclinationDeg));

		_ADIRSMagneticDeclinationTextField.setOnInput([this](const Key key, std::optional<std::string_view>) {
			if (key != Key::enter)
				return;

			auto& rc = RC::getInstance();
			rc.getSettings().flightModeSelection.magneticDeclinationDeg = Text::tryParseInt32Or(_ADIRSMagneticDeclinationTextField.getText(), 0);
			rc.getSettings().flightModeSelection.writeLater();

			rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::magneticDeclination);
		});

		Theme::apply(&_ADIRSMagneticDeclinationTitle);
		rows += &_ADIRSMagneticDeclinationTitle;

		// ----------------------------- Calibration -----------------------------

		// Separator
		rows += &_calSeparator;

		// Title
		Theme::applyPageTitle(&_calTitle);
		_calTitle.setText("Calibration");
		rows += &_calTitle;
		
		// Progress bar
		Theme::apply(&_calProgressBar);
		rows += &_calProgressBar;
		
		// Progress text
		Theme::applyDescription(&_calProgressText);
		_calProgressText.setHorizontalAlignment(Alignment::center);
		rows += &_calProgressText;
		
		// Accel & gyro
		Theme::applyPrimary(&_calAccelAndGyroButton);
		_calAccelAndGyroButton.setText("Accel & gyro");
		
		_calAccelAndGyroButton.setOnClick([] {
			RC::getInstance().getRemoteData().calibrationSystem = AircraftCalibrationSystem::accelAndGyro;
			RC::getInstance().getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::calibrate);
		});
		
		rows += &_calAccelAndGyroButton;
		
		// Mag
		Theme::applyPrimary(&_calMagButton);
		_calMagButton.setText("Mag");
		
		_calMagButton.setOnClick([] {
			RC::getInstance().getRemoteData().calibrationSystem = AircraftCalibrationSystem::mag;
			RC::getInstance().getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::calibrate);
		});

		rows += &_calMagButton;

		// Description
		Theme::applyDescription(&_calDescriptionText);

		_calDescriptionText.setWrappingEnabled(true);

		_calDescriptionText.setText(
			R"(It is advisable to calibrate the accelerometer and gyroscope only after changing MCU location in the fuselage

The magnetometer should be calibrated each time before first takeoff in new geolocation to take into account the influence of parasitic magnetic fields from nearby metal structures)"
		);

		rows += &_calDescriptionText;

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	ADIRSSettingsPage::~ADIRSSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t ADIRSSettingsPage::_scrollPosition = 0;
	
	void ADIRSSettingsPage::onTick() {
		Layout::onTick();
		
		auto& rc = RC::getInstance();
		
		const auto calibrating = rc.getAircraftData().raw.calibration.isCalibrating();
		
		if (calibrating) {
			_calProgressBar.setValue(static_cast<float>(rc.getAircraftData().raw.calibration.progress) / 0xFF);

			char buffer[32];

			std::snprintf(
				buffer,
				sizeof(buffer),
				"Calibrating %s: %d%%",
				rc.getAircraftData().raw.calibration.system == AircraftCalibrationSystem::accelAndGyro
					 ? "accel & gyro"
					 : "mag",
				rc.getAircraftData().raw.calibration.progress * 100 / 0xFF
			);

			_calProgressText.setText(buffer);
		}
		
		_calProgressBar.setVisible(calibrating);
		_calProgressText.setVisible(calibrating);
		
		_calAccelAndGyroButton.setVisible(!calibrating);
		_calMagButton.setVisible(!calibrating);
	}
}