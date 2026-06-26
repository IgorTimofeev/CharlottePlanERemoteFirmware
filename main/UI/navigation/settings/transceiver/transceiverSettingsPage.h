#pragma once

#include <YOBA/core.h>
#include <YOBA/UI.h>

#include "UI/navigation/page.h"
#include "UI/elements/titler.h"
#include "UI/elements/comboBox.h"
#include "UI/elements/PID/PIDReferencer.h"

namespace pizda {
	using namespace YOBA;

	class TransceiverSettingsPage : public ScrollViewPage {
		public:
			TransceiverSettingsPage();
			~TransceiverSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			TextField _RFFrequency {};
			Titler _RFFrequencyTitle { "Radio frequency [120; 960] (MHz)", &_RFFrequency };

			constexpr static  std::array<std::string_view, 10> _bandwidthItems {
				"7.81",
				"10.42",
				"15.63",
				"20.83",
				"31.25",
				"41.67",
				"62.5",
				"125",
				"250",
				"500"
			};

			ComboBox _bandwidth {};
			Titler _bandwidthTitle { "Bandwidth (kHz)", &_bandwidth };

			constexpr static  std::array<std::string_view, 4> _codingRateItems {
				"4/5",
				"4/6",
				"4/7",
				"4/8"
			};

			ComboBox _codingRate {};
			Titler _codingRateTitle { "Coding rate", &_codingRate };

			constexpr static  std::array<std::string_view, 8> _spreadingFactorItems {
				"SF5",
				"SF6",
				"SF7",
				"SF8",
				"SF9",
				"SF10",
				"SF11",
				"SF12"
			};

			ComboBox _spreadingFactor {};
			Titler _spreadingFactorTitle { "Spreading factor", &_spreadingFactor };

			TextField _syncWord {};
			Titler _syncWordTitle { "Sync word [0; 255]", &_syncWord };

			TextField _preambleLength {};
			Titler _preambleLengthTitle { "Preamble length [0; 65535] (s)", &_preambleLength };

			TextField _currentLimit {};
			Titler _currentLimitTitle { "Current limit [0; 140] (mA)", &_currentLimit };

			TextField _power {};
			Titler _powerTitle { "TX power [-17; 22] (dBm)", &_power };

			TextField _receivingTimeOffset {};
			Titler _receivingTimeOffsetTitle { "RX time offset (us)", &_receivingTimeOffset };

			TextField _transmittingTimeOffset {};
			Titler _transmittingTimeOffsetTitle { "TX time offset (us)", &_transmittingTimeOffset };

			Button _confirmButton {};
	};
}
