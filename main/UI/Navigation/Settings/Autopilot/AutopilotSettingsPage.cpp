#include "UI/Navigation/Settings/Autopilot/AutopilotSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "Types/Generic.hpp"
#include "RC.hpp"

namespace pizda {
	AutopilotSettingsPage::AutopilotSettingsPage() {
		auto& rc = RC::getInstance();

		// ----------------------------- Lateral -----------------------------

		title.setText("Lateral");

		// Angle max
		setupRadTextField(
			_latMaxRoll,
			&rc.getSettings().APConfiguration.maxRollAngleRad,
			30.f,
			RemoteSystemPacketType::autopilotMaxRollAngleRad
		);

		rows += &_latMaxRollTitle;

		// Angle increment
		setupRadTextField(
			_latSMTAIRPS,
			&rc.getSettings().APConfiguration.stabilizedModeRollAngleIncrementRadPerSecond,
			5,
			RemoteSystemPacketType::autopilotStabilizedModeRollAngleIncrementRadPerSecond
		);

		rows += &_latSMTAIFRSTitle;

		// Angle EMA filter factor
		setupFloatTextField(
			_latTAEMAFPS,
			&rc.getSettings().APConfiguration.rollAngleEMAFilterFactorPerSecond,
			0.6f,
			0.0f,
			1000.0f,
			RemoteSystemPacketType::autopilotRollAngleEMAFilterFactorPerSecond
		);

		rows += &_latTAEMAFPSTitle;

		// Surface factor
		setupUint8PercentTextField(
			_latMaxAileronsFactor,
			&rc.getSettings().APConfiguration.maxAileronsPercent,
			100,
			RemoteSystemPacketType::autopilotMaxAileronsPercent
		);

		rows += &_latMaxAileronsFactorTitle;

		// PIDs
		addPID(
			_latYawToRollPIDTitle,
			_latYawToRollPID,
			RemoteSystemPacketType::autopilotYawToRollPID,
			&rc.getSettings().APConfiguration.PIDs.yawToRoll
		);

		addPID(
			_latRollToAileronsPIDTitle,
			_latRollToAileronsPID,
			RemoteSystemPacketType::autopilotRollToAileronsPID,
			&rc.getSettings().APConfiguration.PIDs.rollToAilerons
		);


		// ----------------------------- Vertical -----------------------------

		rows += &_verSeparator;

		Theme::applyPageTitle(&_verTitle);
		rows += &_verTitle;

		// Angle max
		setupRadTextField(
			_verMaxPitch,
			&rc.getSettings().APConfiguration.maxPitchAngleRad,
			15.f,
			RemoteSystemPacketType::autopilotMaxPitchAngleRad
		);

		rows += &_verMaxPitchTitle;

		// Angle increment
		setupRadTextField(
			_verSMTARFPS,
			&rc.getSettings().APConfiguration.stabilizedModePitchAngleIncrementRadPerSecond,
			5,
			RemoteSystemPacketType::autopilotStabilizedModePitchAngleIncrementRadPerSecond
		);

		rows += &_verSMTAIRPSTitle;

		// Angle EMA filter factor
		setupFloatTextField(
			_verTAEMAFPS,
			&rc.getSettings().APConfiguration.pitchAngleEMAFilterFactorPerSecond,
			0.6f,
			0.0f,
			1000.0f,
			RemoteSystemPacketType::autopilotPitchAngleEMAFilterFactorPerSecond
		);

		rows += &_verTAEMAFPSTitle;

		// Surface factor
		setupUint8PercentTextField(
			_verMaxElevatorFactor,
			&rc.getSettings().APConfiguration.maxElevatorPercent,
			100,
			RemoteSystemPacketType::autopilotMaxElevatorPercent
		);

		rows += &_verMaxElevatorFactorTitle;

		// PIDs
		addPID(
			_varAltitudeToPitchPIDTitle,
			_verAltitudeToPitchPID,
			RemoteSystemPacketType::autopilotAltitudeToPitchPID,
			&rc.getSettings().APConfiguration.PIDs.altitudeToPitch
		);

		addPID(
			_verSpeedToPitchPIDTitle,
			_verSpeedToPitchPID,
			RemoteSystemPacketType::autopilotSpeedToPitchPID,
			&rc.getSettings().APConfiguration.PIDs.speedToPitch
		);

		addPID(
			_verPitchToElevatorPIDTitle,
			_verPitchToElevatorPID,
			RemoteSystemPacketType::autopilotPitchToElevatorPID,
			&rc.getSettings().APConfiguration.PIDs.pitchToElevator
		);

		// ----------------------------- Longitudinal -----------------------------

		rows += &_lonSeparator;

		Theme::applyPageTitle(&_lonTitle);
		rows += &_lonTitle;

		// Min
		setupUint8PercentTextField(
			_lonThrottleMin,
			&rc.getSettings().APConfiguration.minThrottlePercent,
			100,
			RemoteSystemPacketType::autopilotMinThrottlePercent
		);

		rows += &_lonThrottleMinTitle;

		// Max
		setupUint8PercentTextField(
			_lonThrottleMax,
			&rc.getSettings().APConfiguration.maxThrottlePercent,
			100,
			RemoteSystemPacketType::autopilotMaxThrottlePercent
		);

		rows += &_lonThrottleMaxTitle;

		// PIDs
		addPID(
			_lonSpeedToThrottlePIDTitle,
			_lonSpeedToThrottlePID,
			RemoteSystemPacketType::autopilotSpeedToThrottlePID,
			&rc.getSettings().APConfiguration.PIDs.speedToThrottle
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

	void AutopilotSettingsPage::addPID(Titler& titler, PIDReferencer& referencer,
		RemoteSystemPacketType packetType, PIDCoefficients* settingsCoefficients) {
		referencer.setCoefficients(*settingsCoefficients);

		referencer.setOnCoefficientsChanged([settingsCoefficients, packetType](const PIDCoefficients& newCoefficients) {
			auto& rc = RC::getInstance();

			*settingsCoefficients = newCoefficients;
			rc.getSettings().APConfiguration.writeLater();

			rc.getTransceiver().enqueueSystemPacket(packetType);
		});

		rows += &titler;
	}
}
