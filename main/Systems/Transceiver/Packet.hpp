#pragma once

#include <cstdint>
#include <numbers>

namespace pizda {
	#pragma pack(push, 1)

	class Packet {
		public:
			constexpr static uint8_t checksumLengthBytes = 1;
	};

	// -------------------------------- Remote --------------------------------

	enum class RemotePacketType : uint8_t {
		controls,
		system,

		maxValue = system
	};

	class RemotePacket {
		public:
			constexpr static uint8_t typeLengthBits = 1;
	};

	class RemoteControlsPacket {
		public:
			constexpr static uint8_t motorLengthBits = 12;
	};

	enum class RemoteSystemPacketType : uint8_t {
		referencePressure,
		camera,
		trim,
		lights,
		homeCoordinates,
		calibrate,
		magneticDeclination,
		motors,

		// ----------------------------- FlyByWire -----------------------------

		// Generic
		flyByWireAutopilot,
		flyByWireAutothrottle,

		// Lateral
		flyByWireLateralMode,
		flyByWireSelectedHeadingDeg,
		flyByWireMaxRollAngleDeg,
		flyByWireYawToRollPID,
		flyByWireRollToAileronsPID,
		flyByWireStabilizedModeRollAngleIncrementRadPerSecond,
		flyByWireRollAngleEMAFilterFactorPerSecond,
		flyByWireMaxAileronsPercent,

		// Vertical
		flyByWireVerticalMode,
		flyByWireSelectedAltitudeM,
		flyByWireMinPitchAngleDeg,
		flyByWireMaxPitchAngleDeg,
		flyByWireSpeedToPitchPID,
		flyByWireAltitudeToPitchPID,
		flyByWirePitchToElevatorPID,
		flyByWireStabilizedModePitchAngleIncrementRadPerSecond,
		flyByWirePitchAngleEMAFilterFactorPerSecond,
		flyByWireMaxElevatorPercent,

		// Longitudinal
		flyByWireSelectedSpeedMPS,
		flyByWireSpeedToThrottlePID,
		flyByWireMinThrottlePercent,
		flyByWireMaxThrottlePercent,

		flyByWireVS0,
		flyByWireVFE,
		flyByWireVNO,
		flyByWireVNE,
		flyByWireStallSpeedProtectionMargin,
		flyByWireOverspeedProtectionMargin,

		communicationSettings,

		maxValue = communicationSettings
	};

	class RemoteSystemPacket {
		public:
			// Max val = 63
			constexpr static uint8_t typeLengthBits = 6;

			constexpr static uint8_t magneticDeclinationLengthBits = 9;

			// Reference pressure
			// 1 hectopascal ~= 7.88 meters ~= 30 feet of altitude. But it's quite a large scale for low altitude RC aircraft
			// So we'll be using decapascals. Cool fact: The maximum recorded atmospheric pressure on Earth, adjusted to sea level,
			// is around 1085.7 hPa (32.09 inHg), occurring in Tonsontsengel, Mongolia (2001)
			// So in theory 1100 daPa will be more than enough
			// So 14 bits
			constexpr static uint8_t referencePressureLengthBits = 14;

			// Home point
			constexpr static uint8_t homeCoordinatesLatitudeLengthBits = 25;
			constexpr static uint8_t homeCoordinatesLongitudeLengthBits = 26;

			// Trim
			constexpr static uint8_t trimValueLengthBits = RemoteControlsPacket::motorLengthBits;

			// Calibration
			constexpr static uint8_t calibrateSystemLengthBits = 2;

			// Motor
			constexpr static uint8_t motorConfigurationTypeLengthBits = 4;
			constexpr static uint8_t motorConfigurationMinLengthBits = 12;
			constexpr static uint8_t motorConfigurationMaxLengthBits = motorConfigurationMinLengthBits;

			// Camera
			constexpr static uint8_t cameraPitchLengthBits = 9;
			constexpr static uint8_t cameraYawLengthBits = cameraPitchLengthBits;

			// -------------------------------- FlyByWire --------------------------------

			// Speed
			// The Guinness World Record for the fastest RC jet-powered aircraft is 749.221 km/h, set by Niels Herbrich in 2017.
			// In our case 350 km/h (97.2 m/s) will be enough, because it gives precision of ~0.37 m/s per 1 bit
			constexpr static uint8_t flyByWireSelectedSpeedLengthBits = 8;
			constexpr static int16_t flyByWireSelectedSpeedMaxMPS = 97;

			// 360 deg = 9 bits
			constexpr static uint8_t flyByWireSelectedHeadingDegLengthBits = 9;

			// Altitude
			// 13 bit = 8191, not enough
			// 14 bit = 16383, more than enough
			// Mapping [-1000; 10000] to [0; 16383]
			constexpr static uint8_t flyByWireSelectedAltitudeLengthBits = 14;
			constexpr static int16_t flyByWireSelectedAltitudeMinM = -1'000;
			constexpr static int16_t flyByWireSelectedAltitudeMaxM = 10'000;

			// Mode
			constexpr static uint8_t flyByWireLateralModeLengthBits = 2;
			constexpr static uint8_t flyByWireVerticalModeLengthBits = 3;

			// Ailerons, elevator, throttle
			constexpr static uint8_t flyByWirePercentLengthBits = 7;

			constexpr static uint8_t flyByWireMinMaxPitchLengthBits = 7;
			constexpr static uint8_t flyByWireMaxRollLengthBits = 7;

			constexpr static uint8_t flyByWireVSpeedsLengthBits = 8;
			constexpr static uint8_t flyByWireSpeedProtectionLengthBits = 5;
	};

	class RemoteSystemCommunicationSettingsPacket {
		public:
			constexpr static uint8_t RFFrequencyLengthBits = 10;
			constexpr static uint8_t bandwidthLengthBits = 4;
			constexpr static uint8_t spreadingFactorLengthBits = 4;
			constexpr static uint8_t codingRateLengthBits = 3;
			constexpr static uint8_t syncWordLengthBits = 8;
			constexpr static uint8_t preambleLengthLengthBits = 16;

			constexpr static uint8_t currentLimitMALengthBits = 8;
			constexpr static uint8_t powerDBmLengthBits = 8;

			// 20 bit = 1 048 575, one second
			constexpr static uint8_t receivingTimeOffsetLengthBits = 20;
			constexpr static uint8_t transmittingTimeOffsetLengthBits = receivingTimeOffsetLengthBits;
	};

	class RemoteSystemPIDPacket {
		public:
			constexpr static uint8_t typeLengthBits = 4;
			constexpr static uint8_t coefficientLengthBits = 32;
	};

	// -------------------------------- Aircraft --------------------------------

	enum class AircraftPacketType : uint8_t {
		STierTelemetry,
		ATierTelemetry,
		BTierTelemetry,
		system,

		maxValue = system
	};

	class AircraftPacket {
		public:
			constexpr static uint8_t typeLengthBits = 2;
	};

	class AircraftSTierTelemetryPacket {
		public:
			// Roll / pitch / yaw
			// Precision of 0.25 - 0.5 deg should be enough for any client-side visualization with EMA filter
			// So 360 * 1 / 0.25 = 1440 ~= 10 bits

			// Roll range is [-180; 180] deg
			constexpr static uint8_t rollLengthBits = 10;
			constexpr static float rollRangeRad = 2 * std::numbers::pi_v<float>;

			// Pitch is [-90; 90] deg, but we can't use fewer bits
			constexpr static uint8_t pitchLengthBits = 10;
			constexpr static float pitchRangeRad = std::numbers::pi_v<float>;

			// Same as roll, [-180; 180] deg
			constexpr static uint8_t yawLengthBits = 10;
			constexpr static float yawRangeRad = 2 * std::numbers::pi_v<float>;

			// Slip & skid
			// 8 bit = [-127; 127]
			constexpr static uint8_t slipAndSkidLengthBits = 8;
			constexpr static uint8_t slipAndSkidMaxG = 2;

			constexpr static uint8_t speedLengthBits = RemoteSystemPacket::flyByWireSelectedSpeedLengthBits;
			constexpr static int16_t speedMaxMPS = RemoteSystemPacket::flyByWireSelectedSpeedMaxMPS;

			constexpr static uint8_t altitudeLengthBits = RemoteSystemPacket::flyByWireSelectedAltitudeLengthBits;
			constexpr static int16_t altitudeMinM = RemoteSystemPacket::flyByWireSelectedAltitudeMinM;
			constexpr static int16_t altitudeMaxM = RemoteSystemPacket::flyByWireSelectedAltitudeMaxM;

			constexpr static uint8_t flyByWireTargetRollLengthBits = rollLengthBits;
			constexpr static float flyByWireTargetRollRangeRad = rollRangeRad;

			constexpr static uint8_t flyByWireTargetPitchLengthBits = pitchLengthBits;
			constexpr static float flyByWireTargetPitchRangeRad = pitchRangeRad;
	};

	class AircraftATierTelemetryPacket {
		public:
			constexpr static uint8_t throttleLengthBits = 7;

			constexpr static uint8_t latitudeLengthBits = RemoteSystemPacket::homeCoordinatesLatitudeLengthBits;
			constexpr static uint8_t longitudeLengthBits = RemoteSystemPacket::homeCoordinatesLongitudeLengthBits;
	};

	class AircraftBTierTelemetryPacket {
		public:
			constexpr static uint8_t batteryLengthBits = 9;

			constexpr static uint8_t flyByWireLateralModeLengthBits =
				RemoteSystemPacket::flyByWireLateralModeLengthBits;
			constexpr static uint8_t flyByWireVerticalModeLengthBits =
				RemoteSystemPacket::flyByWireVerticalModeLengthBits;

			constexpr static uint8_t flyByWireAltitudeLengthBits = RemoteSystemPacket::flyByWireSelectedAltitudeLengthBits;
			constexpr static int16_t flyByWireAltitudeMinM = RemoteSystemPacket::flyByWireSelectedAltitudeMinM;
			constexpr static int16_t flyByWireAltitudeMaxM = RemoteSystemPacket::flyByWireSelectedAltitudeMaxM;
	};

	enum class AircraftSystemPacketType : uint8_t {
		calibration,
		communicationSettingsACK,

		maxValue = communicationSettingsACK
	};

	class AircraftSystemPacket {
		public:
			constexpr static uint8_t typeLengthBits = 1;
	};

	class AircraftSystemCalibrationPacket {
		public:
			constexpr static uint8_t systemLengthBits = RemoteSystemPacket::calibrateSystemLengthBits;
			constexpr static uint8_t progressLengthBits = 7;
	};

	#pragma pack(pop)
}