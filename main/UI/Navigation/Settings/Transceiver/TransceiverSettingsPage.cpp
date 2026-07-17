#include "UI/Navigation/Settings/Transceiver/TransceiverSettingsPage.hpp"

#include "RC.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	TransceiverSettingsPage::TransceiverSettingsPage() {
		auto& rc = RC::getInstance();

		// Page title
		title.setText("Transceiver");

		// RF frequency
		Theme::apply(&_RFFrequency);
		_RFFrequency.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_RFFrequency.setText(std::to_string(rc.getSettings().transceiver.communication.frequencyHz / 1'000'000));
		Theme::apply(&_RFFrequencyTitle);
		rows += &_RFFrequencyTitle;

		// Bandwidth
		_bandwidth.setItems(_bandwidthItems);
		_bandwidth.setSelectedIndex(static_cast<uint8_t>(rc.getSettings().transceiver.communication.bandwidth));
		_bandwidth.setDialogTitle("Bandwidth");
		Theme::apply(&_bandwidthTitle);
		rows += &_bandwidthTitle;

		// Coding rate
		_codingRate.setItems(_codingRateItems);
		_codingRate.setSelectedIndex(static_cast<uint8_t>(rc.getSettings().transceiver.communication.codingRate));
		_codingRate.setDialogTitle("Coding rate");
		Theme::apply(&_codingRateTitle);
		rows += &_codingRateTitle;

		// Spreading factor
		_spreadingFactor.setItems(_spreadingFactorItems);
		_spreadingFactor.setSelectedIndex(rc.getSettings().transceiver.communication.spreadingFactor - 5);
		_spreadingFactor.setDialogTitle("Spreading factor");
		Theme::apply(&_spreadingFactorTitle);
		rows += &_spreadingFactorTitle;

		// Sync word
		Theme::apply(&_syncWord);
		_syncWord.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_syncWord.setText(std::to_string(rc.getSettings().transceiver.communication.syncWord));
		Theme::apply(&_syncWordTitle);
		rows += &_syncWordTitle;

		// Preamble length
		Theme::apply(&_preambleLength);
		_preambleLength.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_preambleLength.setText(std::to_string(rc.getSettings().transceiver.communication.preambleLength));
		Theme::apply(&_preambleLengthTitle);
		rows += &_preambleLengthTitle;

		// Current limit
		Theme::apply(&_currentLimit);
		_currentLimit.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_currentLimit.setText(std::to_string(rc.getSettings().transceiver.communication.currentLimitMA));
		Theme::apply(&_currentLimitTitle);
		rows += &_currentLimitTitle;

		// Power
		Theme::apply(&_power);
		_power.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_power.setText(std::to_string(rc.getSettings().transceiver.communication.powerDBm));
		Theme::apply(&_powerTitle);
		rows += &_powerTitle;

		// Receiving time offset
		Theme::apply(&_receivingTimeOffset);
		_receivingTimeOffset.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);
		_receivingTimeOffset.setText(std::to_string(rc.getSettings().transceiver.communication.receivingTimeOffsetUs));
		Theme::apply(&_receivingTimeOffsetTitle);
		rows += &_receivingTimeOffsetTitle;

		// Transmitting time offset
		Theme::apply(&_transmittingTimeOffset);
		_transmittingTimeOffset.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);
		_transmittingTimeOffset.setText(std::to_string(rc.getSettings().transceiver.communication.transmittingTimeOffsetUs));
		Theme::apply(&_transmittingTimeOffsetTitle);
		rows += &_transmittingTimeOffsetTitle;

		// ----------------------------- LE RAZJEBAT' BUTTON -----------------------------

		Theme::applyPrimary(&_confirmButton);
		_confirmButton.setText("Confirm");

		_confirmButton.setOnClick([this, &rc] {
			auto& settings = rc.getRemoteData().transceiver.communicationSettings;

			settings.frequencyHz = Text::tryParseInt32Or(_RFFrequency.getText(), 0) * 1'000'000;
			settings.bandwidth = static_cast<SX1262LoRaBandwidth>(_bandwidth.getSelectedIndex());
			settings.codingRate = static_cast<SX1262LoRaCodingRate>(_codingRate.getSelectedIndex());
			settings.spreadingFactor = _spreadingFactor.getSelectedIndex() + 5;
			settings.syncWord = Text::tryParseInt32Or(_syncWord.getText(), 0);
			settings.preambleLength = Text::tryParseInt32Or(_preambleLength.getText(), 0);

			settings.currentLimitMA = Text::tryParseInt32Or(_currentLimit.getText(), 60);
			settings.powerDBm = Text::tryParseInt32Or(_power.getText(), 22);

			settings.receivingTimeOffsetUs = Text::tryParseInt32Or(_receivingTimeOffset.getText(), 0);
			settings.transmittingTimeOffsetUs = Text::tryParseInt32Or(_transmittingTimeOffset.getText(), 0);

			settings.sanitize();

			rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::communicationSettings);
		});

		rows += &_confirmButton;

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	TransceiverSettingsPage::~TransceiverSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t TransceiverSettingsPage::_scrollPosition = 0;
}
