#include "UI/Navigation/Settings/FlyByWire/FlyByWireSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "Types/Generic.hpp"
#include "RC.hpp"

namespace pizda {
	FlyByWireSettingsPage::FlyByWireSettingsPage() {
		auto& rc = RC::getInstance();
		auto& settings = rc.getSettings();

		// ----------------------------- Lateral -----------------------------

		title.setText("Lateral");

		// Angle max
		setupRadTextField(
			_latMaxRoll,
			&settings.FBW.maxRollAngleRad,
			30.f,
			RemoteSystemPacketType::flyByWireMaxRollAngleDeg
		);

		Theme::apply(&_latMaxRollTitle);
		rows += &_latMaxRollTitle;

		// Angle increment
		setupRadTextField(
			_latSMTAIRPS,
			&settings.FBW.stabilizedModeRollAngleIncrementRadPerSecond,
			5,
			RemoteSystemPacketType::flyByWireStabilizedModeRollAngleIncrementRadPerSecond
		);

		Theme::apply(&_latSMTAIFRSTitle);
		rows += &_latSMTAIFRSTitle;

		// Angle EMA filter factor
		setupFloatTextField(
			_latTAEMAFPS,
			&settings.FBW.rollAngleEMAFilterFactorPerSecond,
			0.6f,
			0.0f,
			1000.0f,
			RemoteSystemPacketType::flyByWireRollAngleEMAFilterFactorPerSecond
		);

		Theme::apply(&_latTAEMAFPSTitle);
		rows += &_latTAEMAFPSTitle;

		// Surface factor
		setupUint8PercentTextField(
			_latMaxAileronsFactor,
			&settings.FBW.maxAileronsPercent,
			100,
			RemoteSystemPacketType::flyByWireMaxAileronsPercent
		);

		Theme::apply(&_latMaxAileronsFactorTitle);
		rows += &_latMaxAileronsFactorTitle;

		// PIDs
		setupPID(
			_latYawToRollPIDTitle,
			_latYawToRollPID,
			RemoteSystemPacketType::flyByWireYawToRollPID,
			&settings.FBW.PIDs.yawToRoll
		);

		setupPID(
			_latRollToAileronsPIDTitle,
			_latRollToAileronsPID,
			RemoteSystemPacketType::flyByWireRollToAileronsPID,
			&settings.FBW.PIDs.rollToAilerons
		);


		// ----------------------------- Vertical -----------------------------

		Theme::apply(&_verDivider);
		rows += &_verDivider;

		Theme::applyPageTitle(&_verTitle);
		rows += &_verTitle;

		// Angle min
		setupRadTextField(
			_verMinPitch,
			&settings.FBW.minPitchAngleRad,
			-15.f,
			RemoteSystemPacketType::flyByWireMinPitchAngleDeg
		);
		
		_verMinPitch.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional | KeyboardLayoutOptions::allowSigned);

		Theme::apply(&_verMinPitchTitle);
		rows += &_verMinPitchTitle;

		// Angle max
		setupRadTextField(
			_verMaxPitch,
			&settings.FBW.maxPitchAngleRad,
			15.f,
			RemoteSystemPacketType::flyByWireMaxPitchAngleDeg
		);

		Theme::apply(&_verMaxPitchTitle);
		rows += &_verMaxPitchTitle;

		// Angle increment
		setupRadTextField(
			_verSMTARFPS,
			&settings.FBW.stabilizedModePitchAngleIncrementRadPerSecond,
			5,
			RemoteSystemPacketType::flyByWireStabilizedModePitchAngleIncrementRadPerSecond
		);

		Theme::apply(&_verSMTAIRPSTitle);
		rows += &_verSMTAIRPSTitle;

		// Angle EMA filter factor
		setupFloatTextField(
			_verTAEMAFPS,
			&settings.FBW.pitchAngleEMAFilterFactorPerSecond,
			0.6f,
			0.0f,
			1000.0f,
			RemoteSystemPacketType::flyByWirePitchAngleEMAFilterFactorPerSecond
		);

		Theme::apply(&_verTAEMAFPSTitle);
		rows += &_verTAEMAFPSTitle;

		// Surface factor
		setupUint8PercentTextField(
			_verMaxElevatorFactor,
			&settings.FBW.maxElevatorPercent,
			100,
			RemoteSystemPacketType::flyByWireMaxElevatorPercent
		);

		Theme::apply(&_verMaxElevatorFactorTitle);
		rows += &_verMaxElevatorFactorTitle;

		// PIDs
		setupPID(
			_varAltitudeToPitchPIDTitle,
			_verAltitudeToPitchPID,
			RemoteSystemPacketType::flyByWireAltitudeToPitchPID,
			&settings.FBW.PIDs.altitudeToPitch
		);

		setupPID(
			_verSpeedToPitchPIDTitle,
			_verSpeedToPitchPID,
			RemoteSystemPacketType::flyByWireSpeedToPitchPID,
			&settings.FBW.PIDs.speedToPitch
		);

		setupPID(
			_verPitchToElevatorPIDTitle,
			_verPitchToElevatorPID,
			RemoteSystemPacketType::flyByWirePitchToElevatorPID,
			&settings.FBW.PIDs.pitchToElevator
		);

		// ----------------------------- Longitudinal -----------------------------

		Theme::apply(&_logDivider);
		rows += &_logDivider;

		Theme::applyPageTitle(&_lonTitle);
		rows += &_lonTitle;

		// V-speeds
		_lonVSpeedsColumns.setGap(10);
		_lonVSpeedsColumns.setOrientation(Orientation::horizontal);

		// Band rows
		_lonVSpeedsColumns.setAutoSize(&_lonVSpeedsBandRows);
		_lonVSpeedsColumns += &_lonVSpeedsBandRows;

		rows += &_lonVSpeedsColumns;

		// Text field rows
		_lonVSpeedsTextFieldRows.setGap(10);
		_lonVSpeedsColumns += &_lonVSpeedsTextFieldRows;

		// Vne
		setupSpeedBand(_lonVSpeedsVNEBand, &Theme::red);
		_lonVSpeedsBandRows.setAutoSize(&_lonVSpeedsVNEBand);
		_lonVSpeedsVNEBand.setHeight(15 + Theme::elementHeight / 2);

		setupVSpeedTextField(_lonVSpeedsVNETextField, &settings.FBW.speeds.VNE, RemoteSystemPacketType::flyByWireVNE);
		Theme::apply(&_lonVSpeedsVNETitle);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVNETitle;

		// Vno
		setupSpeedBand(_lonVSpeedsVNOBand, &Theme::yellow);
		setupVSpeedTextField(_lonVSpeedsVNOTextField, &settings.FBW.speeds.VNO, RemoteSystemPacketType::flyByWireVNO);
		Theme::apply(&_lonVSpeedsVNOTitle);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVNOTitle;

		// Vfe
		setupSpeedBand(_lonVSpeedsVFEBand, &Theme::green1);
		setupVSpeedTextField(_lonVSpeedsVFETextField, &settings.FBW.speeds.VFE, RemoteSystemPacketType::flyByWireVFE);
		Theme::apply(&_lonVSpeedsVFETitle);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVFETitle;

		// Vs0
		setupSpeedBand(_lonVSpeedsVS0Band, &Theme::white);
		setupVSpeedTextField(_lonVSpeedsVS0TextField, &settings.FBW.speeds.VS0, RemoteSystemPacketType::flyByWireVS0);
		Theme::apply(&_lonVSpeedsVS0Title);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVS0Title;

		// Pre Vs0
		setupSpeedBand(_lonVSpeedsPreVS0Band, &Theme::red);
		_lonVSpeedsBandRows.setAutoSize(&_lonVSpeedsPreVS0Band);
		_lonVSpeedsPreVS0Band.setHeight(Theme::elementHeight / 2);

		// Stall protection margin
		setupAnyTextField(
			_lonStallProtectionMargin,
			std::to_string(settings.FBW.speeds.stallProtectionMargin),
			[&rc, &settings, this] {
				settings.FBW.speeds.stallProtectionMargin = Text::tryParseInt32Or(_lonStallProtectionMargin.getText(), 0);
				settings.FBW.writeLater();

				rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::flyByWireStallSpeedProtectionMargin);
			}
		);

		_lonStallProtectionMargin.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);

		Theme::apply(&_lonStallProtectionMarginTitle);
		rows += &_lonStallProtectionMarginTitle;

		// Overspeed protection margin
		setupAnyTextField(
			_lonOverspeedProtectionMargin,
			std::to_string(settings.FBW.speeds.overspeedProtectionMargin),
			[&rc, &settings, this] {
				settings.FBW.speeds.overspeedProtectionMargin = Text::tryParseInt32Or(_lonOverspeedProtectionMargin.getText(), 0);
				settings.FBW.writeLater();

				rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::flyByWireOverspeedProtectionMargin);
			}
		);

		_lonOverspeedProtectionMargin.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);

		Theme::apply(&_lonOverspeedProtectionMarginTitle);
		rows += &_lonOverspeedProtectionMarginTitle;

		// Min
		setupUint8PercentTextField(
			_lonThrottleMin,
			&settings.FBW.minThrottlePercent,
			100,
			RemoteSystemPacketType::flyByWireMinThrottlePercent
		);

		Theme::apply(&_lonThrottleMinTitle);
		rows += &_lonThrottleMinTitle;

		// Max
		setupUint8PercentTextField(
			_lonThrottleMax,
			&settings.FBW.maxThrottlePercent,
			100,
			RemoteSystemPacketType::flyByWireMaxThrottlePercent
		);

		Theme::apply(&_lonThrottleMaxTitle);
		rows += &_lonThrottleMaxTitle;

		// PIDs
		setupPID(
			_lonSpeedToThrottlePIDTitle,
			_lonSpeedToThrottlePID,
			RemoteSystemPacketType::flyByWireSpeedToThrottlePID,
			&settings.FBW.PIDs.speedToThrottle
		);

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	FlyByWireSettingsPage::~FlyByWireSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t FlyByWireSettingsPage::_scrollPosition = 0;

	void FlyByWireSettingsPage::setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter) {
		Theme::apply(&textField);
		textField.setText(text);

		textField.setOnInput([onEnter](const Key key, std::optional<std::string_view>) {
			if (key != Key::enter)
				return;

			onEnter();
		});
	}

	void FlyByWireSettingsPage::setupFloatTextField(TextField& textField, float* value, float fallbackValue, float min, float max, RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(*value),
			[&textField, fallbackValue, value, min, max, packetType] {
				auto& rc = RC::getInstance();

				*value = std::clamp(Text::tryParseFloatOr(textField.getText(), fallbackValue), min, max);
				rc.getSettings().FBW.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}

	void FlyByWireSettingsPage::setupRadTextField(TextField& textField, float* angleRad, float fallbackAngleDeg, RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(Math::round(Math::toDegrees(*angleRad), 2)),
			[&textField, fallbackAngleDeg, angleRad, packetType] {
				auto& rc = RC::getInstance();

				*angleRad = Math::toRadians(Text::tryParseFloatOr(textField.getText(), fallbackAngleDeg));
				rc.getSettings().FBW.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}

	void FlyByWireSettingsPage::setupUint8PercentTextField(TextField& textField, uint8_t* percent, float fallbackPercent, RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(*percent),
			[&textField, fallbackPercent, percent, packetType] {
				auto& rc = RC::getInstance();

				*percent = static_cast<uint8_t>(std::clamp<int32_t>(Text::tryParseInt32Or(textField.getText(), fallbackPercent), 0, 100));
				rc.getSettings().FBW.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
	}

	void FlyByWireSettingsPage::setupPID(Titler& titler, PIDReferencer& referencer,
		RemoteSystemPacketType packetType, PIDCoefficients* settingsCoefficients) {
		referencer.setCoefficients(*settingsCoefficients);

		referencer.setOnCoefficientsChanged([settingsCoefficients, packetType](const PIDCoefficients& newCoefficients) {
			auto& rc = RC::getInstance();

			*settingsCoefficients = newCoefficients;
			rc.getSettings().FBW.writeLater();

			rc.getTransceiver().enqueueSystemPacket(packetType);
		});

		Theme::apply(&titler);
		rows += &titler;
	}

	void FlyByWireSettingsPage::setupVSpeedTextField(TextField& textField, uint16_t* value, const RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(*value),
			[&textField, value, packetType] {
				auto& rc = RC::getInstance();

				*value = std::max<uint16_t>(0, Text::tryParseInt32Or(textField.getText(), 0));
				rc.getSettings().FBW.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}

	void FlyByWireSettingsPage::setupSpeedBand(RectangularShape& band, const Color* color) {
		band.setWidth(2);
		band.setFillColor(color);

		_lonVSpeedsBandRows += &band;
	}
}
