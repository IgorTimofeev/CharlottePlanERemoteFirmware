#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"
#include "UI/Elements/Titler.hpp"
#include "UI/Elements/PID/PIDReferencer.hpp"
#include "UI/Elements/Separator.hpp"
#include "Systems/Transceiver/Packet.hpp"

namespace pizda {
	using namespace YOBA;

	class AutopilotSettingsPage : public ScrollViewPage {
		public:
			AutopilotSettingsPage();
			~AutopilotSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			// ----------------------------- Lateral -----------------------------

			TextField _latMaxRoll {};
			Titler _latMaxRollTitle { "Max roll angle (deg)", &_latMaxRoll };

			TextField _latTAEMAFPS {};
			Titler _latTAEMAFPSTitle { "Target angle EMA filter factor", &_latTAEMAFPS };

			TextField _latSMTAIRPS {};
			Titler _latSMTAIFRSTitle { "Target angle increment (deg)", &_latSMTAIRPS };

			TextField _latMaxAileronsFactor {};
			Titler _latMaxAileronsFactorTitle { "Max ailerons deflection (%)", &_latMaxAileronsFactor };

			PIDReferencer _latYawToRollPID { "Yaw to roll" };
			Titler _latYawToRollPIDTitle { "Yaw to roll", &_latYawToRollPID };

			PIDReferencer _latRollToAileronsPID { "Roll to ailerons" };
			Titler _latRollToAileronsPIDTitle { "Roll to ailerons", &_latRollToAileronsPID };

			// ----------------------------- Vertical -----------------------------

			HorizontalSeparator _verSeparator {};
			TextView _verTitle { "Vertical"};

			TextField _verMaxPitch {};
			Titler _verMaxPitchTitle { "Max pitch angle (deg)", &_verMaxPitch };

			TextField _verTAEMAFPS {};
			Titler _verTAEMAFPSTitle { "Target angle EMA filter factor", &_verTAEMAFPS };

			TextField _verSMTARFPS {};
			Titler _verSMTAIRPSTitle { "Target angle increment (deg)", &_verSMTARFPS };

			TextField _verMaxElevatorFactor {};
			Titler _verMaxElevatorFactorTitle { "Max elevator deflection (%)", &_verMaxElevatorFactor };

			PIDReferencer _verSpeedToPitchPID { "Speed to pitch" };
			Titler _verSpeedToPitchPIDTitle { "Speed to pitch", &_verSpeedToPitchPID };

			PIDReferencer _verAltitudeToPitchPID { "Altitude to pitch" };
			Titler _varAltitudeToPitchPIDTitle { "Altitude to pitch", &_verAltitudeToPitchPID };

			PIDReferencer _verPitchToElevatorPID { "Pitch to elevator" };
			Titler _verPitchToElevatorPIDTitle { "Pitch to elevator", &_verPitchToElevatorPID };

			// ----------------------------- Longitudinal -----------------------------

			HorizontalSeparator _lonSeparator {};
			TextView _lonTitle { "Longitudinal"};

			TextField _lonThrottleMin {};
			Titler _lonThrottleMinTitle { "Throttle idle power (%)", &_lonThrottleMin };

			TextField _lonThrottleMax {};
			Titler _lonThrottleMaxTitle { "Throttle climb power (%)", &_lonThrottleMax };

			PIDReferencer _lonSpeedToThrottlePID { "Speed to throttle" };
			Titler _lonSpeedToThrottlePIDTitle { "Speed to throttle", &_lonSpeedToThrottlePID };

			static void setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter);
			static void setupFloatTextField(TextField& textField, float* value, float fallbackValue, float min, float max, RemoteSystemPacketType  packetType);
			static void setupRadTextField(TextField& textField, float* angleRad, float fallbackAngleDeg, RemoteSystemPacketType packetType);
			static void setupUint8PercentTextField(TextField& textField, uint8_t* percent, float fallbackPercent, RemoteSystemPacketType packetType);

			void addPID(Titler& titler, PIDReferencer& referencer, RemoteSystemPacketType packetType, PIDCoefficients* settingsCoefficients);
	};
}
