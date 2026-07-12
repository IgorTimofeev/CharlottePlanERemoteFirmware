#pragma once

#include <esp_log.h>
#include <esp_adc/adc_oneshot.h>

#include <YOBA/Core.hpp>
#include <YOBA/Hardware/Displays/ILI9341Display.hpp>
#include <YOBA/Hardware/TouchPanels/FT6336UTouchPanel.hpp>
#include <YOBA/Hardware/Encoder.hpp>
#include <YOBA/Rendering.hpp>
#include <YOBA/UI.hpp>

#include <Units.hpp>
#include <ADCVoltmeter.hpp>
#include <EMAFilter.hpp>
#include <AudioPlayer.hpp>

#include "Config.hpp"

#include "Settings/Settings.hpp"

#include "Systems/Transceiver/Transceiver.hpp"
#include "Systems/Transceiver/RemoteTransceiver.hpp"
#include "Systems/Axes/Axes.hpp"

#include "Types/RemoteData.hpp"
#include "Types/AircraftData.hpp"
#include "Types/NavigationData.hpp"

#include "UI/Theme.hpp"
#include "UI/Navigation/Route.hpp"
#include "UI/Navigation/Menu/OpenMenuButton.hpp"
#include "UI/Elements/DebugOverlay.hpp"

namespace pizda {
	using namespace YOBA;

	class RC {
		public:
			static RC& getInstance();

			[[noreturn]] void start();

			Application& getApplication();
			Settings& getSettings();
			AudioPlayer& getAudioPlayer();
			PushButtonEncoder& getEncoder();
			Axes& getAxes();

			ADCVoltmeter getBattery() const;
			RemoteTransceiver& getTransceiver();
			
			void updateDebugOverlayVisibility();

			const Route* getRoute() const;
			void setRoute(const Route* route);
			
			RemoteData& getRemoteData();
			AircraftData& getAircraftData();
			NavigationData& getNavigationData();

			void playFeedback(const Sound* sound);
			void playFeedback();

			uint32_t getTickDeltaTimeUs() const;

			constexpr adc_oneshot_unit_handle_t getAssignedADCOneshotUnit(const adc_unit_t ADCUnit) const {
				switch (ADCUnit) {
					case ADC_UNIT_1: return _ADCOneshotUnit1;
					default: startErrorLoop("failed to find assigned ADC oneshot unit");
				}
			}

		private:
			constexpr static auto _logTag = "RC";
			
			RC() = default;

			// -------------------------------- Hardware --------------------------------

			adc_oneshot_unit_handle_t _ADCOneshotUnit1 {};

			ILI9341Display _display {};
			RGB565TransactionalBufferedRenderer _renderer {};
			FT6336UTouchPanel _touchPanel {};

			// Transceiver
			RemoteTransceiver _transceiver {};
			
			// Encoder
			PushButtonEncoder _encoder {
				config::encoder::a,
				config::encoder::b,
				config::encoder::sw
			};

			// Analog axes
			Axes _axes {};

			// Battery
			ADCVoltmeter _battery {};

			// Audio
			Buzzer _buzzer {
				config::buzzer::pin,
				config::buzzer::channel
			};

			AudioPlayer _audioPlayer { &_buzzer };

			// -------------------------------- UI --------------------------------

			Application _application {};
			Layout _pageLayout {};

			OpenMenuButton _openMenuButton {};
			DebugOverlay* _debugOverlay = nullptr;

			const Route* _route = nullptr;

			uint32_t _tickDeltaTimeUs = 0;

			// -------------------------------- Other shit --------------------------------

			Settings _settings;
			RemoteData _remoteData {};
			AircraftData _aircraftData {};
			NavigationData _navigationData {};

			int64_t _dataInterpolationTime = 0;
			int64_t _batteryTickTime = 0;

			float applyEMA(float oldValue, float newValue, float factor) const;
			float applyEMAToAngle(float oldValue, float newValue, float factor) const;
			void interpolateData();
			void batteryTick();

			[[noreturn]] static void startErrorLoop(const char* error);
	};
}