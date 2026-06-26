#include "transceiverSettingsPage.h"

#include "rc.h"
#include "UI/theme.h"
#include "utilities/string.h"

namespace pizda {
	TransceiverSettingsPage::TransceiverSettingsPage() {
		auto& rc = RC::getInstance();

		// Page title
		title.setText("Transceiver");

		// RF frequency
		Theme::apply(&_RFFrequency);
		_RFFrequency.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_RFFrequency.setText(std::to_string(rc.getSettings().transceiver.communication.frequencyHz / 1'000'000));
		rows += &_RFFrequencyTitle;

		// Bandwidth
		_bandwidth.setItems(_bandwidthItems);
		_bandwidth.setSelectedIndex(static_cast<uint8_t>(rc.getSettings().transceiver.communication.bandwidth));
		_bandwidth.setDialogTitle("Bandwidth");
		rows += &_bandwidthTitle;

		// Coding rate
		_codingRate.setItems(_codingRateItems);
		_codingRate.setSelectedIndex(static_cast<uint8_t>(rc.getSettings().transceiver.communication.codingRate));
		_codingRate.setDialogTitle("Coding rate");
		rows += &_codingRateTitle;

		// Spreading factor
		_spreadingFactor.setItems(_spreadingFactorItems);
		_spreadingFactor.setSelectedIndex(rc.getSettings().transceiver.communication.spreadingFactor - 5);
		_spreadingFactor.setDialogTitle("Spreading factor");
		rows += &_spreadingFactorTitle;

		// Sync word
		Theme::apply(&_syncWord);
		_syncWord.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_syncWord.setText(std::to_string(rc.getSettings().transceiver.communication.syncWord));
		rows += &_syncWordTitle;

		// Preamble length
		Theme::apply(&_preambleLength);
		_preambleLength.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_preambleLength.setText(std::to_string(rc.getSettings().transceiver.communication.preambleLength));
		rows += &_preambleLengthTitle;

		// Current limit
		Theme::apply(&_currentLimit);
		_currentLimit.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_currentLimit.setText(std::to_string(rc.getSettings().transceiver.communication.currentLimitMA));
		rows += &_currentLimitTitle;

		// Power
		Theme::apply(&_power);
		_power.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
		_power.setText(std::to_string(rc.getSettings().transceiver.communication.powerDBm));
		rows += &_powerTitle;

		// Receiving time offset
		Theme::apply(&_receivingTimeOffset);
		_receivingTimeOffset.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);
		_receivingTimeOffset.setText(std::to_string(rc.getSettings().transceiver.communication.receivingTimeOffsetUs));
		rows += &_receivingTimeOffsetTitle;

		// Transmitting time offset
		Theme::apply(&_transmittingTimeOffset);
		_transmittingTimeOffset.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);
		_transmittingTimeOffset.setText(std::to_string(rc.getSettings().transceiver.communication.transmittingTimeOffsetUs));
		rows += &_transmittingTimeOffsetTitle;

		// ----------------------------- LE RAZJEBAT' BUTTON -----------------------------

		Theme::applyPrimary(&_confirmButton);
		_confirmButton.setText("Confirm");

		_confirmButton.setOnClick([this, &rc] {
			auto& settings = rc.getRemoteData().transceiver.communicationSettings;

			settings.frequencyHz = StringUtils::tryParseInt32Or(_RFFrequency.getText(), 0) * 1'000'000;
			settings.bandwidth = static_cast<SX1262LoRaBandwidth>(_bandwidth.getSelectedIndex());
			settings.codingRate = static_cast<SX1262LoRaCodingRate>(_codingRate.getSelectedIndex());
			settings.spreadingFactor = _spreadingFactor.getSelectedIndex() + 5;
			settings.syncWord = StringUtils::tryParseInt32Or(_syncWord.getText(), 0);
			settings.preambleLength = StringUtils::tryParseInt32Or(_preambleLength.getText(), 0);

			settings.currentLimitMA = StringUtils::tryParseInt32Or(_currentLimit.getText(), 60);
			settings.powerDBm = StringUtils::tryParseInt32Or(_power.getText(), 22);

			settings.receivingTimeOffsetUs = StringUtils::tryParseInt32Or(_receivingTimeOffset.getText(), 0);
			settings.transmittingTimeOffsetUs = StringUtils::tryParseInt32Or(_transmittingTimeOffset.getText(), 0);

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
