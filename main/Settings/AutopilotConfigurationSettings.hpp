#pragma once

#include <cstdint>

#include <YOBA/Core.hpp>

#include <NVSSettings.hpp>

#include "Types/Generic.hpp"

namespace pizda {
	using namespace YOBA;

	class AutopilotConfigurationSettingsPIDs {
		public:
			PIDCoefficients yawToRoll {};
			PIDCoefficients altitudeToPitch {};
			PIDCoefficients speedToPitch {};

			PIDCoefficients rollToAilerons {};
			PIDCoefficients pitchToElevator {};

			PIDCoefficients speedToThrottle {};

			static void read(const NVSStream& stream, const char* keyP, const char* keyI, const char* keyD, PIDCoefficients& coefficients, const PIDCoefficients& fallbackCoefficients) {
				coefficients.p = stream.readFloat(keyP, fallbackCoefficients.p);
				coefficients.i = stream.readFloat(keyI, fallbackCoefficients.i);
				coefficients.d = stream.readFloat(keyD, fallbackCoefficients.d);
			}

			static void write(const NVSStream& stream, const char* keyP, const char* keyI, const char* keyD, const PIDCoefficients& coefficients) {
				stream.writeFloat(keyP, coefficients.p);
				stream.writeFloat(keyI, coefficients.i);
				stream.writeFloat(keyD, coefficients.d);
			}
	};

	class AutopilotConfigurationSettings : public NVSSettings {
		public:
			// Lateral
			float maxRollAngleRad = 0;
			float stabilizedModeRollAngleIncrementRadPerSecond = 0;
			float rollAngleEMAFilterFactorPerSecond = 0;
			uint8_t maxAileronsPercent = 0;

			// Vertical
			float maxPitchAngleRad = 0;
			float stabilizedModePitchAngleIncrementRadPerSecond = 0;
			float pitchAngleEMAFilterFactorPerSecond = 0;
			uint8_t maxElevatorPercent = 0;

			// Longitudinal
			uint8_t minThrottlePercent = 0;
			uint8_t maxThrottlePercent = 0;

			// PIDs
			AutopilotConfigurationSettingsPIDs PIDs {};

		protected:
			const char* getNamespace() override {
				return _namespace;
			}

			void onRead(const NVSStream& stream) override {
				// Lateral
				maxRollAngleRad = stream.readFloat(_maxRollAngleRad, toRadians(30));
				stabilizedModeRollAngleIncrementRadPerSecond = stream.readFloat(_stabilizedModeRollAngleIncrementRadPerSecond, toRadians(5));
				rollAngleEMAFilterFactorPerSecond = stream.readFloat(_rollAngleEMAFilterFactorPerSecond, 0.8f);
				maxAileronsPercent = stream.readUint8(_maxAileronsPercent, 100);

				// Vertical
				maxPitchAngleRad = stream.readFloat(_maxPitchAngleRad, toRadians(15));
				stabilizedModePitchAngleIncrementRadPerSecond = stream.readFloat(_stabilizedModePitchAngleIncrementRadPerSecond, toRadians(5));
				pitchAngleEMAFilterFactorPerSecond = stream.readFloat(_pitchAngleEMAFilterFactorPerSecond, 0.8f);
				maxElevatorPercent = stream.readUint8(_maxElevatorPercent, 100);

				// Longitudinal
				minThrottlePercent = stream.readUint8(_minThrottlePercent, 0);
				maxThrottlePercent = stream.readUint8(_maxThrottlePercent, 100);

				// PIDs
				AutopilotConfigurationSettingsPIDs::read(stream, _yawToRollP, _yawToRollI, _yawToRollD, PIDs.yawToRoll, { 0.8f, 0.1f, 0.3f });
				AutopilotConfigurationSettingsPIDs::read(stream, _altitudeToPitchP, _altitudeToPitchI, _altitudeToPitchD, PIDs.altitudeToPitch, { 0.04f, 0.01f, 0.01f });
				AutopilotConfigurationSettingsPIDs::read(stream, _speedToPitchP, _speedToPitchI, _speedToPitchD, PIDs.speedToPitch, { 0.2f, 0.05f, 0.01f });
				AutopilotConfigurationSettingsPIDs::read(stream, _rollToAileronsP, _rollToAileronsI, _rollToAileronsD, PIDs.rollToAilerons, { 2.5f, 0.01f, 0.2f });
				AutopilotConfigurationSettingsPIDs::read(stream, _pitchToElevatorP, _pitchToElevatorI, _pitchToElevatorD, PIDs.pitchToElevator, { 3.5f, 0.3f, 0.2f });
				AutopilotConfigurationSettingsPIDs::read(stream, _speedToThrottleP, _speedToThrottleI, _speedToThrottleD, PIDs.speedToThrottle, { 0.4f, 0.1f, 0.1f });
			}

			void onWrite(const NVSStream& stream) override {
				// Lateral
				stream.writeFloat(_maxRollAngleRad, maxRollAngleRad);
				stream.writeFloat(_stabilizedModeRollAngleIncrementRadPerSecond, stabilizedModeRollAngleIncrementRadPerSecond);
				stream.writeFloat(_rollAngleEMAFilterFactorPerSecond, rollAngleEMAFilterFactorPerSecond);
				stream.writeUint8(_maxAileronsPercent, maxAileronsPercent);

				// Vertical
				stream.writeFloat(_maxPitchAngleRad, maxPitchAngleRad);
				stream.writeFloat(_stabilizedModePitchAngleIncrementRadPerSecond, stabilizedModePitchAngleIncrementRadPerSecond);
				stream.writeFloat(_pitchAngleEMAFilterFactorPerSecond, pitchAngleEMAFilterFactorPerSecond);
				stream.writeUint8(_maxElevatorPercent, maxElevatorPercent);

				// Longitudinal
				stream.writeUint8(_minThrottlePercent, minThrottlePercent);
				stream.writeUint8(_maxThrottlePercent, maxThrottlePercent);

				// PIDs
				AutopilotConfigurationSettingsPIDs::write(stream, _yawToRollP, _yawToRollI, _yawToRollD, PIDs.yawToRoll);
				AutopilotConfigurationSettingsPIDs::write(stream, _altitudeToPitchP, _altitudeToPitchI, _altitudeToPitchD, PIDs.altitudeToPitch);
				AutopilotConfigurationSettingsPIDs::write(stream, _speedToPitchP, _speedToPitchI, _speedToPitchD, PIDs.speedToPitch);
				AutopilotConfigurationSettingsPIDs::write(stream, _rollToAileronsP, _rollToAileronsI, _rollToAileronsD, PIDs.rollToAilerons);
				AutopilotConfigurationSettingsPIDs::write(stream, _pitchToElevatorP, _pitchToElevatorI, _pitchToElevatorD, PIDs.pitchToElevator);
				AutopilotConfigurationSettingsPIDs::write(stream, _speedToThrottleP, _speedToThrottleI, _speedToThrottleD, PIDs.speedToThrottle);
			}

		private:
			constexpr static auto _namespace = "apc";

			// Lateral
			constexpr static auto _maxRollAngleRad = "mrla";
			constexpr static auto _stabilizedModeRollAngleIncrementRadPerSecond = "rair";
			constexpr static auto _rollAngleEMAFilterFactorPerSecond = "raef";
			constexpr static auto _maxAileronsPercent = "aipe";

			// Vertical
			constexpr static auto _maxPitchAngleRad = "mpia";
			constexpr static auto _stabilizedModePitchAngleIncrementRadPerSecond = "pair";
			constexpr static auto _pitchAngleEMAFilterFactorPerSecond = "paef";
			constexpr static auto _maxElevatorPercent = "elpe";

			// Longitudinal
			constexpr static auto _minThrottlePercent = "tmip";
			constexpr static auto _maxThrottlePercent = "tmap";

			// PIDs
			constexpr static auto _yawToRollP = "pyrp";
			constexpr static auto _yawToRollI = "pyri";
			constexpr static auto _yawToRollD = "pyrd";

			constexpr static auto _altitudeToPitchP = "papp";
			constexpr static auto _altitudeToPitchI = "papi";
			constexpr static auto _altitudeToPitchD = "papd";

			constexpr static auto _speedToPitchP = "pspp";
			constexpr static auto _speedToPitchI = "pspi";
			constexpr static auto _speedToPitchD = "pspd";

			constexpr static auto _rollToAileronsP = "prap";
			constexpr static auto _rollToAileronsI = "prai";
			constexpr static auto _rollToAileronsD = "prad";

			constexpr static auto _pitchToElevatorP = "ppep";
			constexpr static auto _pitchToElevatorI = "ppei";
			constexpr static auto _pitchToElevatorD = "pped";

			constexpr static auto _speedToThrottleP = "pstp";
			constexpr static auto _speedToThrottleI = "psti";
			constexpr static auto _speedToThrottleD = "pstd";
	};
}