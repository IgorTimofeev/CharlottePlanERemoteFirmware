#pragma once

#include <cstdint>

#include <NVSSettings.hpp>

namespace pizda {
	using namespace YOBA;

	class PersonalizationSettingsMFDPFDSpeedRanges {
		public:
			uint16_t VS0 = 0;
			uint16_t VFE = 0;
			uint16_t VNO = 0;
			uint16_t VNE = 0;
	};

	class PersonalizationSettingsMFDPFD {
		public:
			uint8_t FOV = 0;
			bool flightDirector = false;
			bool metricUnits = false;
			bool waypointLabels = true;

			PersonalizationSettingsMFDPFDSpeedRanges speedRanges {};
	};

	enum class PersonalizationSettingsMFDNDMode : uint8_t {
		arc,
		map,

		maxValue = map
	};

	class PersonalizationSettingsMFDND {
		public:
			PersonalizationSettingsMFDNDMode mode = PersonalizationSettingsMFDNDMode::arc;
			bool earth = true;
	};

	enum class PersonalizationSettingsMFDToolbarMode : uint8_t {
		none,
		autopilot,
		baro,
		trim,
		lights,
		camera
	};

	class PersonalizationSettingsMFDToolbars {
		public:
			PersonalizationSettingsMFDToolbarMode topMode = PersonalizationSettingsMFDToolbarMode::none;
	};

	enum class PersonalizationSettingsMFDSplitMode : uint8_t {
		PFD,
		ND,
		split
	};

	class PersonalizationSettingsMFDSplit {
		public:
			PersonalizationSettingsMFDSplitMode mode = PersonalizationSettingsMFDSplitMode::PFD;
			// Percent
			uint8_t ratio = 60;
	};

	class PersonalizationSettingsMFD {
		public:
			PersonalizationSettingsMFDPFD PFD {};
			PersonalizationSettingsMFDND ND {};
			PersonalizationSettingsMFDToolbars toolbars {};
			PersonalizationSettingsMFDSplit split {};
	};
	
	class PersonalizationSettings : public NVSSettings {
		public:
			PersonalizationSettingsMFD MFD {};
			bool dataInterpolation = false;
			bool debugOverlay = false;
			bool audioFeedback = false;
			bool darkTheme = true;
		
		protected:
			const char* getNamespace() override {
				return _namespace;
			}

			void onRead(const NVSStream& stream) override {
				// PFD
				MFD.PFD.FOV = stream.readUint8(_MFDPFDFOV, 50);
				MFD.PFD.flightDirector = stream.readBool(_MFDPFDFlightDirector, true);
				MFD.PFD.metricUnits = stream.readBool(_MFDPFDFMetricUnits, false);
				MFD.PFD.waypointLabels = stream.readBool(_MFDPFDWaypointLabels, true);

				MFD.PFD.speedRanges.VS0 = stream.readUint16(_MFDPFDSpeedRangesVS0, 7);
				MFD.PFD.speedRanges.VFE = stream.readUint16(_MFDPFDSpeedRangesVFE, 17);
				MFD.PFD.speedRanges.VNO = stream.readUint16(_MFDPFDSpeedRangesVNO, 24);
				MFD.PFD.speedRanges.VNE = stream.readUint16(_MFDPFDSpeedRangesVNE, 40);

				// ND
				MFD.ND.mode = static_cast<PersonalizationSettingsMFDNDMode>(stream.readUint8(_MFDNDMode, static_cast<uint8_t>(PersonalizationSettingsMFDNDMode::arc)));
				MFD.ND.earth = stream.readBool(_MFDNDEarth, true);

				// Other
				MFD.toolbars.topMode = stream.readEnum<PersonalizationSettingsMFDToolbarMode>(_MFDToolbarsTopMode, PersonalizationSettingsMFDToolbarMode::autopilot);
				MFD.split.mode = static_cast<PersonalizationSettingsMFDSplitMode>(stream.readUint8(_MFDSplitMode, static_cast<uint8_t>(PersonalizationSettingsMFDSplitMode::PFD)));
				MFD.split.ratio = stream.readUint8(_MFDSplitRatio, 60);

				dataInterpolation = stream.readBool(_dataInterpolation, true);
				audioFeedback = stream.readBool(_audioFeedback, true);
				debugOverlay = stream.readBool(_debugOverlay, false);
				darkTheme = stream.readBool(_darkTheme, true);
			}

			void onWrite(const NVSStream& stream) override {
				// PFD
				stream.writeUint8(_MFDPFDFOV, MFD.PFD.FOV);
				stream.writeBool(_MFDPFDFlightDirector, MFD.PFD.flightDirector);
				stream.writeBool(_MFDPFDFMetricUnits, MFD.PFD.metricUnits);
				stream.writeBool(_MFDPFDWaypointLabels, MFD.PFD.waypointLabels);

				stream.writeUint16(_MFDPFDSpeedRangesVS0, MFD.PFD.speedRanges.VS0);
				stream.writeUint16(_MFDPFDSpeedRangesVFE, MFD.PFD.speedRanges.VFE);
				stream.writeUint16(_MFDPFDSpeedRangesVNO, MFD.PFD.speedRanges.VNO);
				stream.writeUint16(_MFDPFDSpeedRangesVNE, MFD.PFD.speedRanges.VNE);

				// ND
				stream.writeUint8(_MFDNDMode, static_cast<uint8_t>(MFD.ND.mode));
				stream.writeBool(_MFDNDEarth, MFD.ND.earth);

				// Other
				stream.writeEnum<PersonalizationSettingsMFDToolbarMode>(_MFDToolbarsTopMode, MFD.toolbars.topMode);
				stream.writeUint8(_MFDSplitMode, static_cast<uint8_t>(MFD.split.mode));
				stream.writeUint8(_MFDSplitRatio, MFD.split.ratio);

				stream.writeBool(_dataInterpolation, dataInterpolation);
				stream.writeBool(_audioFeedback, audioFeedback);
				stream.writeBool(_debugOverlay, debugOverlay);
				stream.writeBool(_darkTheme, darkTheme);
			}

		private:
			constexpr static auto _namespace = "pe0";

			// PFD
			constexpr static auto _MFDPFDFOV = "mpfo";
			constexpr static auto _MFDPFDFlightDirector = "mpfd";
			constexpr static auto _MFDPFDFMetricUnits = "mpmu";
			constexpr static auto _MFDPFDWaypointLabels = "mpwl";

			constexpr static auto _MFDPFDSpeedRangesVS0 = "mpvs0";
			constexpr static auto _MFDPFDSpeedRangesVFE = "mpvfe";
			constexpr static auto _MFDPFDSpeedRangesVNO = "mpvno";
			constexpr static auto _MFDPFDSpeedRangesVNE = "mpvne";

			// ND
			constexpr static auto _MFDNDMode = "mnmd";
			constexpr static auto _MFDNDEarth = "mnea";

			// Other
			constexpr static auto _MFDToolbarsTopMode = "mttm";
			constexpr static auto _MFDSplitMode = "msm";
			constexpr static auto _MFDSplitRatio = "msr";

			constexpr static auto _dataInterpolation = "di";
			constexpr static auto _audioFeedback = "af";
			constexpr static auto _debugOverlay = "do";
			constexpr static auto _darkTheme = "dt";
	};
}
