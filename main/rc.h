#pragma once

#include <esp_log.h>
#include <esp_adc/adc_oneshot.h>

#include <YOBA/core.h>
#include <YOBA/hardware/displays/ILI9341Display.h>
#include <YOBA/hardware/touchPanels/FT6336UTouchPanel.h>
#include <YOBA/hardware/encoder.h>
#include <YOBA/rendering.h>
#include <YOBA/UI.h>

#include <units.h>
#include <ADCVoltmeter.h>
#include <EMAFilter.h>
#include <audioPlayer.h>

#include "config.h"
#include "config.h"
#include "UI/theme.h"
#include "UI/navigation/route.h"
#include "UI/navigation/menu/openMenuButton.h"
#include "UI/elements/debugOverlay.h"

#include "config.h"
#include "settings/settings.h"

#include "systems/transceiver/transceiver.h"
#include "systems/transceiver/remoteTransceiver.h"
#include "systems/axes/axes.h"

#include "types/remoteData.h"
#include "types/remoteData.h"
#include "types/aircraftData.h"
#include "types/navigationData.h"

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
			RGB565Renderer _renderer {};

			FT6336UTouchPanel _touchPanel {
				config::I2C::SDA,
				config::I2C::SCL,
				config::screen::touch::RST,
				config::screen::touch::INT,

				FT6336UTouchPanel::defaultI2CAddress,
				config::screen::touch::I2CFrequencyHz
			};

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