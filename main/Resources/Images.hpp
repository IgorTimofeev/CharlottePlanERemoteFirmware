#pragma once

#include "Resources/Images/SplashScreenImage.hpp"

#include "Resources/Images/MenuIconMFDImage.hpp"
#include "Resources/Images/MenuIconMFDAutopilotImage.hpp"
#include "Resources/Images/MenuIconMFDAutopilotFlightDirectorImage.hpp"
#include "Resources/Images/MenuIconMFDAutopilotEngageImage.hpp"
#include "Resources/Images/MenuIconMFDBaroImage.hpp"
#include "Resources/Images/MenuIconMFDTrimImage.hpp"
#include "Resources/Images/MenuIconMFDMetricUnitsImage.hpp"
#include "Resources/Images/MenuIconMFDCameraImage.hpp"
#include "Resources/Images/MenuIconMFDCameraResetImage.hpp"

#include "Resources/Images/MenuIconMFDLightsImage.hpp"
#include "Resources/Images/MenuIconMFDLightsNavigationImage.hpp"
#include "Resources/Images/MenuIconMFDLightsStrobeImage.hpp"
#include "Resources/Images/MenuIconMFDLightsLandingImage.hpp"
#include "Resources/Images/MenuIconMFDLightsCabinImage.hpp"

#include "Resources/Images/MenuIconFlightPlanImage.hpp"
#include "Resources/Images/MenuIconWaypointsImage.hpp"

#include "Resources/Images/MenuIconPersonalizationImage.hpp"
#include "Resources/Images/MenuIconADIRSImage.hpp"
#include "Resources/Images/MenuIconMotorsImage.hpp"
#include "Resources/Images/MenuIconAxesImage.hpp"
#include "Resources/Images/MenuIconSpectrumScanImage.hpp"
#include "Resources/Images/MenuIconAutopilotSettingsImage.hpp"
#include "Resources/Images/MenuIconTransceiverImage.hpp"

namespace pizda {
	class Images {
		public:
			constexpr static SplashScreenImage splashScreen {};

			constexpr static MenuIconMFDImage menuIconMFD {};
			constexpr static MenuIconMFDAutopilotImage menuIconMFDAutopilot {};
			constexpr static MenuIconMFDAutopilotFlightDirectorImage menuIconMFDAutopilotFlightDirector {};
			constexpr static MenuIconMFDAutopilotEngageImage menuIconMFDAutopilotEngage {};
			constexpr static MenuIconMFDBaroImage menuIconMFDBaro {};
			constexpr static MenuIconMFDTrimImage menuIconMFDTrim {};
			constexpr static MenuIconMFDLightsImage menuIconMFDLights {};
			constexpr static MenuIconMFDMetricUnitsImage menuIconMFDMetricUnits {};
			constexpr static MenuIconMFDCameraImage menuIconMFDCameraImage {};
			constexpr static MenuIconMFDCameraResetImage menuIconMFDCameraResetImage {};

			constexpr static MenuIconMFDLightsNavigationImage menuIconMFDLightsNavigation {};
			constexpr static MenuIconMFDLightsStrobeImage menuIconMFDLightsStrobe {};
			constexpr static MenuIconMFDLightsLandingImage menuIconMFDLightsLanding {};
			constexpr static MenuIconMFDLightsCabinImage menuIconMFDLightsCabin {};

			constexpr static MenuIconFlightPlanImage menuIconFlightPlan {};
			constexpr static MenuIconWaypointsImage menuIconWaypointsImage {};

			constexpr static MenuIconPersonalizationImage menuIconPersonalization {};
			constexpr static MenuIconADIRSImage menuIconADIRS {};
			constexpr static MenuIconMotorsImage menuIconMotors {};
			constexpr static MenuIconAxesImage menuIconAxes {};
			constexpr static MenuIconSpectrumScanImage menuIconSpectrumScan {};
			constexpr static MenuIconAutopilotSettingsImage menuIconAutopilotSettings {};
			constexpr static MenuIconTransceiverImage menuIconTransceiverImage {};
	};
}