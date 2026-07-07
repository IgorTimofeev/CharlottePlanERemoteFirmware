#pragma once

#include <cstdint>

#include <YOBA/Core.hpp>

#include <NVSSettings.hpp>

#include "Types/Generic.hpp"

namespace pizda {
	using namespace YOBA;

	class FlightModeSelectionSettings : public NVSSettings {
		public:
			// Lateral
			AutopilotLateralMode lateralMode = AutopilotLateralMode::hdg;
			uint16_t headingDeg = 0;

			int16_t magneticDeclinationDeg = 0;

			// Vertical
			AutopilotVerticalMode verticalMode = AutopilotVerticalMode::flc;
			uint16_t altitudeFt = 0;

			uint32_t referencePressurePa = 0;
			bool referencePressureSTD = false;

			uint32_t minimumAltitudeFt = 0;
			bool minimumAltitudeEnabled = false;

			// Longitudinal
			uint16_t speedKt = 0;

		protected:
			const char* getNamespace() override {
				return _namespace;
			}

			void onRead(const NVSStream& stream) override {
				// Lateral
				lateralMode = stream.readEnum<AutopilotLateralMode>(_lateralMode, AutopilotLateralMode::hdg);
				headingDeg = stream.readUint16(_headingDeg, 0);

				magneticDeclinationDeg = stream.readInt8(_magneticDeclinationDeg, 0);

				// Vertical
				verticalMode = stream.readEnum<AutopilotVerticalMode>(_verticalMode, AutopilotVerticalMode::flc);
				altitudeFt = stream.readUint16(_altitudeFt, 100);

				referencePressurePa = stream.readUint32(_referencePressurePa, 101325);
				referencePressureSTD = stream.readBool(_referencePressureSTD, false);

				minimumAltitudeFt = stream.readUint32(_minimumAltitudeFt, 350);
				minimumAltitudeEnabled = stream.readBool(_minimumAltitudeEnabled, true);

				// Longitudinal
				speedKt = stream.readUint16(_speedKt, 90);
			}

			void onWrite(const NVSStream& stream) override {
				// Lateral
				stream.writeEnum<AutopilotLateralMode>(_lateralMode, lateralMode);
				stream.writeUint16(_headingDeg, headingDeg);

				stream.writeInt8(_magneticDeclinationDeg, magneticDeclinationDeg);

				// Vertical
				stream.writeEnum<AutopilotVerticalMode>(_verticalMode, verticalMode);
				stream.writeUint16(_altitudeFt, altitudeFt);

				stream.writeUint32(_referencePressurePa, referencePressurePa);
				stream.writeBool(_referencePressureSTD, referencePressureSTD);

				stream.writeUint32(_minimumAltitudeFt, minimumAltitudeFt);
				stream.writeBool(_minimumAltitudeEnabled, minimumAltitudeEnabled);

				// Longitudinal
				stream.writeUint16(_speedKt, speedKt);
			}

		private:
			constexpr static auto _namespace = "fms";

			// Lateral
			constexpr static auto _lateralMode = "ltmd";
			constexpr static auto _headingDeg = "thdg";

			constexpr static auto _magneticDeclinationDeg = "md";

			// Vertical
			constexpr static auto _verticalMode = "vtmd";
			constexpr static auto _altitudeFt = "talt";

			constexpr static auto _referencePressurePa = "rp";
			constexpr static auto _referencePressureSTD = "rs";

			constexpr static auto _minimumAltitudeFt = "ma";
			constexpr static auto _minimumAltitudeEnabled = "me";

			// Longitudinal
			constexpr static auto _speedKt = "tspd";
	};
}
