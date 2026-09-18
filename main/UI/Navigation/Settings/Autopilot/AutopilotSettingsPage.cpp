#include "UI/Navigation/Settings/Autopilot/AutopilotSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "Types/Generic.hpp"
#include "RC.hpp"

namespace pizda {
	AutopilotSettingsPage::AutopilotSettingsPage() {
		auto& rc = RC::getInstance();
		auto& settings = rc.getSettings();

		// ----------------------------- Lateral -----------------------------

		title.setText("Lateral");

		// Angle max
		setupRadTextField(
			_latMaxRoll,
			&settings.APConfiguration.maxRollAngleRad,
			30.f,
			RemoteSystemPacketType::autopilotMaxRollAngleDeg
		);

		Theme::apply(&_latMaxRollTitle);
		rows += &_latMaxRollTitle;

		// Angle increment
		setupRadTextField(
			_latSMTAIRPS,
			&settings.APConfiguration.stabilizedModeRollAngleIncrementRadPerSecond,
			5,
			RemoteSystemPacketType::autopilotStabilizedModeRollAngleIncrementRadPerSecond
		);

		Theme::apply(&_latSMTAIFRSTitle);
		rows += &_latSMTAIFRSTitle;

		// Angle EMA filter factor
		setupFloatTextField(
			_latTAEMAFPS,
			&settings.APConfiguration.rollAngleEMAFilterFactorPerSecond,
			0.6f,
			0.0f,
			1000.0f,
			RemoteSystemPacketType::autopilotRollAngleEMAFilterFactorPerSecond
		);

		Theme::apply(&_latTAEMAFPSTitle);
		rows += &_latTAEMAFPSTitle;

		// Surface factor
		setupUint8PercentTextField(
			_latMaxAileronsFactor,
			&settings.APConfiguration.maxAileronsPercent,
			100,
			RemoteSystemPacketType::autopilotMaxAileronsPercent
		);

		Theme::apply(&_latMaxAileronsFactorTitle);
		rows += &_latMaxAileronsFactorTitle;

		// PIDs
		setupPID(
			_latYawToRollPIDTitle,
			_latYawToRollPID,
			RemoteSystemPacketType::autopilotYawToRollPID,
			&settings.APConfiguration.PIDs.yawToRoll
		);

		setupPID(
			_latRollToAileronsPIDTitle,
			_latRollToAileronsPID,
			RemoteSystemPacketType::autopilotRollToAileronsPID,
			&settings.APConfiguration.PIDs.rollToAilerons
		);


		// ----------------------------- Vertical -----------------------------

		Theme::apply(&_verDivider);
		rows += &_verDivider;

		Theme::applyPageTitle(&_verTitle);
		rows += &_verTitle;

		// Angle min
		setupRadTextField(
			_verMinPitch,
			&settings.APConfiguration.minPitchAngleRad,
			-15.f,
			RemoteSystemPacketType::autopilotMinPitchAngleDeg
		);
		
		_verMinPitch.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional | KeyboardLayoutOptions::allowSigned);

		Theme::apply(&_verMinPitchTitle);
		rows += &_verMinPitchTitle;

		// Angle max
		setupRadTextField(
			_verMaxPitch,
			&settings.APConfiguration.maxPitchAngleRad,
			15.f,
			RemoteSystemPacketType::autopilotMaxPitchAngleDeg
		);

		Theme::apply(&_verMaxPitchTitle);
		rows += &_verMaxPitchTitle;

		// Angle increment
		setupRadTextField(
			_verSMTARFPS,
			&settings.APConfiguration.stabilizedModePitchAngleIncrementRadPerSecond,
			5,
			RemoteSystemPacketType::autopilotStabilizedModePitchAngleIncrementRadPerSecond
		);

		Theme::apply(&_verSMTAIRPSTitle);
		rows += &_verSMTAIRPSTitle;

		// Angle EMA filter factor
		setupFloatTextField(
			_verTAEMAFPS,
			&settings.APConfiguration.pitchAngleEMAFilterFactorPerSecond,
			0.6f,
			0.0f,
			1000.0f,
			RemoteSystemPacketType::autopilotPitchAngleEMAFilterFactorPerSecond
		);

		Theme::apply(&_verTAEMAFPSTitle);
		rows += &_verTAEMAFPSTitle;

		// Surface factor
		setupUint8PercentTextField(
			_verMaxElevatorFactor,
			&settings.APConfiguration.maxElevatorPercent,
			100,
			RemoteSystemPacketType::autopilotMaxElevatorPercent
		);

		Theme::apply(&_verMaxElevatorFactorTitle);
		rows += &_verMaxElevatorFactorTitle;

		// PIDs
		setupPID(
			_varAltitudeToPitchPIDTitle,
			_verAltitudeToPitchPID,
			RemoteSystemPacketType::autopilotAltitudeToPitchPID,
			&settings.APConfiguration.PIDs.altitudeToPitch
		);

		setupPID(
			_verSpeedToPitchPIDTitle,
			_verSpeedToPitchPID,
			RemoteSystemPacketType::autopilotSpeedToPitchPID,
			&settings.APConfiguration.PIDs.speedToPitch
		);

		setupPID(
			_verPitchToElevatorPIDTitle,
			_verPitchToElevatorPID,
			RemoteSystemPacketType::autopilotPitchToElevatorPID,
			&settings.APConfiguration.PIDs.pitchToElevator
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

		setupVSpeedTextField(_lonVSpeedsVNETextField, &settings.APConfiguration.speeds.VNE, RemoteSystemPacketType::autopilotVNE);
		Theme::apply(&_lonVSpeedsVNETitle);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVNETitle;

		// Vno
		setupSpeedBand(_lonVSpeedsVNOBand, &Theme::yellow);
		setupVSpeedTextField(_lonVSpeedsVNOTextField, &settings.APConfiguration.speeds.VNO, RemoteSystemPacketType::autopilotVNO);
		Theme::apply(&_lonVSpeedsVNOTitle);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVNOTitle;

		// Vfe
		setupSpeedBand(_lonVSpeedsVFEBand, &Theme::green1);
		setupVSpeedTextField(_lonVSpeedsVFETextField, &settings.APConfiguration.speeds.VFE, RemoteSystemPacketType::autopilotVFE);
		Theme::apply(&_lonVSpeedsVFETitle);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVFETitle;

		// Vs0
		setupSpeedBand(_lonVSpeedsVS0Band, &Theme::white);
		setupVSpeedTextField(_lonVSpeedsVS0TextField, &settings.APConfiguration.speeds.VS0, RemoteSystemPacketType::autopilotVS0);
		Theme::apply(&_lonVSpeedsVS0Title);
		_lonVSpeedsTextFieldRows += &_lonVSpeedsVS0Title;

		// Pre Vs0
		setupSpeedBand(_lonVSpeedsPreVS0Band, &Theme::red);
		_lonVSpeedsBandRows.setAutoSize(&_lonVSpeedsPreVS0Band);
		_lonVSpeedsPreVS0Band.setHeight(Theme::elementHeight / 2);

		// Stall protection margin
		setupAnyTextField(
			_lonStallProtectionMargin,
			std::to_string(settings.APConfiguration.speeds.stallProtectionMargin),
			[&rc, &settings, this] {
				settings.APConfiguration.speeds.stallProtectionMargin = Text::tryParseInt32Or(_lonStallProtectionMargin.getText(), 0);
				settings.APConfiguration.writeLater();

				rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::autopilotStallSpeedProtectionMargin);
			}
		);

		_lonStallProtectionMargin.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);

		Theme::apply(&_lonStallProtectionMarginTitle);
		rows += &_lonStallProtectionMarginTitle;

		// Overspeed protection margin
		setupAnyTextField(
			_lonOverspeedProtectionMargin,
			std::to_string(settings.APConfiguration.speeds.overspeedProtectionMargin),
			[&rc, &settings, this] {
				settings.APConfiguration.speeds.overspeedProtectionMargin = Text::tryParseInt32Or(_lonOverspeedProtectionMargin.getText(), 0);
				settings.APConfiguration.writeLater();

				rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::autopilotOverspeedProtectionMargin);
			}
		);

		_lonOverspeedProtectionMargin.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);

		Theme::apply(&_lonOverspeedProtectionMarginTitle);
		rows += &_lonOverspeedProtectionMarginTitle;

		// Min
		setupUint8PercentTextField(
			_lonThrottleMin,
			&settings.APConfiguration.minThrottlePercent,
			100,
			RemoteSystemPacketType::autopilotMinThrottlePercent
		);

		Theme::apply(&_lonThrottleMinTitle);
		rows += &_lonThrottleMinTitle;

		// Max
		setupUint8PercentTextField(
			_lonThrottleMax,
			&settings.APConfiguration.maxThrottlePercent,
			100,
			RemoteSystemPacketType::autopilotMaxThrottlePercent
		);

		Theme::apply(&_lonThrottleMaxTitle);
		rows += &_lonThrottleMaxTitle;

		// PIDs
		setupPID(
			_lonSpeedToThrottlePIDTitle,
			_lonSpeedToThrottlePID,
			RemoteSystemPacketType::autopilotSpeedToThrottlePID,
			&settings.APConfiguration.PIDs.speedToThrottle
		);

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	AutopilotSettingsPage::~AutopilotSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t AutopilotSettingsPage::_scrollPosition = 0;

	void AutopilotSettingsPage::setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter) {
		Theme::apply(&textField);
		textField.setText(text);

		textField.setOnInput([onEnter](const Key key, std::optional<std::string_view>) {
			if (key != Key::enter)
				return;

			onEnter();
		});
	}

	void AutopilotSettingsPage::setupFloatTextField(TextField& textField, float* value, float fallbackValue, float min, float max, RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(*value),
			[&textField, fallbackValue, value, min, max, packetType] {
				auto& rc = RC::getInstance();

				*value = std::clamp(Text::tryParseFloatOr(textField.getText(), fallbackValue), min, max);
				rc.getSettings().APConfiguration.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}

	void AutopilotSettingsPage::setupRadTextField(TextField& textField, float* angleRad, float fallbackAngleDeg, RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(Math::round(Math::toDegrees(*angleRad), 2)),
			[&textField, fallbackAngleDeg, angleRad, packetType] {
				auto& rc = RC::getInstance();

				*angleRad = Math::toRadians(Text::tryParseFloatOr(textField.getText(), fallbackAngleDeg));
				rc.getSettings().APConfiguration.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}

	void AutopilotSettingsPage::setupUint8PercentTextField(TextField& textField, uint8_t* percent, float fallbackPercent, RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(*percent),
			[&textField, fallbackPercent, percent, packetType] {
				auto& rc = RC::getInstance();

				*percent = static_cast<uint8_t>(std::clamp<int32_t>(Text::tryParseInt32Or(textField.getText(), fallbackPercent), 0, 100));
				rc.getSettings().APConfiguration.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
	}

	void AutopilotSettingsPage::setupPID(Titler& titler, PIDReferencer& referencer,
		RemoteSystemPacketType packetType, PIDCoefficients* settingsCoefficients) {
		referencer.setCoefficients(*settingsCoefficients);

		referencer.setOnCoefficientsChanged([settingsCoefficients, packetType](const PIDCoefficients& newCoefficients) {
			auto& rc = RC::getInstance();

			*settingsCoefficients = newCoefficients;
			rc.getSettings().APConfiguration.writeLater();

			rc.getTransceiver().enqueueSystemPacket(packetType);
		});

		Theme::apply(&titler);
		rows += &titler;
	}

	void AutopilotSettingsPage::setupVSpeedTextField(TextField& textField, uint16_t* value, const RemoteSystemPacketType packetType) {
		setupAnyTextField(
			textField,
			std::to_string(*value),
			[&textField, value, packetType] {
				auto& rc = RC::getInstance();

				*value = std::max<uint16_t>(0, Text::tryParseInt32Or(textField.getText(), 0));
				rc.getSettings().personalization.writeLater();

				rc.getTransceiver().enqueueSystemPacket(packetType);
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}

	void AutopilotSettingsPage::setupSpeedBand(RectangularShape& band, const Color* color) {
		band.setWidth(2);
		band.setFillColor(color);

		_lonVSpeedsBandRows += &band;
	}
}
