#include <optional>
#include <string>

#include "UI/Navigation/Settings/Motors/MotorsSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	MotorEditorDialog::MotorEditorDialog(const std::string_view title, MotorEditor* motorEditor): _motorEditor(motorEditor) {
		Theme::apply(this);

		// Title
		titleTextView.setText(title);

		// Text fields row
		contentStackLayout += &_textFieldsRow;

		// Midpoint
		Theme::apply(&_midpointTextField);
		_midpointTextField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);

		_midpointTextField.setOnInput([this](const auto key, const auto text) {
			if (key == Key::enter)
				updatePreview();
		});

		Theme::apply(&_midpointTextFieldTitle);
		_textFieldsRow += &_midpointTextFieldTitle;

		// Range
		Theme::apply(&_rangeTextField);
		_rangeTextField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);

		_rangeTextField.setOnInput([this](const auto key, const auto text) {
			if (key == Key::enter)
				updatePreview();
		});

		Theme::apply(&_rangeTextFieldTitle);
		_textFieldsRow += &_rangeTextFieldTitle;

		// Reverse
		Theme::apply(&_reverseTextAndSwitch);
		contentStackLayout += &_reverseTextAndSwitch;

		// Preview
		Theme::applyDescription(&_previewTextView);
		_previewTextView.setTextColor(&Theme::fg6);
		contentStackLayout += &_previewTextView;

		// Confirm
		Theme::applyPrimary(&_confirmButton);
		_confirmButton.setText("Confirm");

		_confirmButton.setOnClick([this] {
			Application::getCurrent()->invokeLater([this] {
				auto& rc = RC::getInstance();

				// Remote data
				auto& motorSettings = rc.getRemoteData().motorSettings;
				motorSettings.type = _motorEditor->getMotorType();
				motorSettings.settings.reverse = _reverseTextAndSwitch.switch_.isActive();

				tryParse(motorSettings.settings.min, motorSettings.settings.max);

				motorSettings.settings.sanitize();

				// Settings
				*rc.getSettings().motors.getByType(_motorEditor->getMotorType()) = rc.getRemoteData().motorSettings.settings;
				rc.getSettings().motors.writeLater();

				// Packer
				rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::motors);

				// Motor editor
				_motorEditor->fromSettings();

				Theme::closeDialog(this);
			});
		});

		contentStackLayout += &_confirmButton;

		// Initialization
		{
			const auto motorSettings = RC::getInstance().getSettings().motors.getByType(_motorEditor->getMotorType());
			const auto range = motorSettings->max - motorSettings->min;

			_midpointTextField.setText(std::to_string(motorSettings->min + range / 2));
			_rangeTextField.setText(std::to_string(range));
			_reverseTextAndSwitch.switch_.setActive(motorSettings->reverse);

			updatePreview();
		}
	}

	void MotorEditorDialog::tryParse(uint16_t& min, uint16_t& max) const {
		const auto midpoint = Text::tryParseInt32Or(_midpointTextField.getText(), 1500);
		const auto range = Text::tryParseInt32Or(_rangeTextField.getText(), 500);
		const auto rangeDiv2 = range / 2;

		min = midpoint - rangeDiv2;
		max = midpoint + rangeDiv2;
	}

	void MotorEditorDialog::updatePreview() {
		uint16_t min, max;
		tryParse(min, max);

		char textBuffer[48];
		std::snprintf(textBuffer, sizeof(textBuffer), "Pulse width: %d - %d us", min, max);
		_previewTextView.setText(textBuffer);
	}

	MotorEditor::MotorEditor(const std::string_view dialogTitle, const MotorType motorType) : _dialogTitle(dialogTitle), _motorType(motorType) {
		// Main row
		setDefaultMargin(&_rowMargin, { 12, 9, 12, 8 });
		_row.setLayoutTransform(&_rowMargin);
		*this += &_row;

		// Range text views
		for (auto& textView : _rangeTextViews) {
			Theme::applyPageTitle(&textView);
			textView.setFont(&Theme::fontSmall);
			textView.setVerticalAlignment(Alignment::center);
			_row += &textView;
		}

		_rangeTextViews[0].setTextColor(&Theme::fg2);

		_rangeTextViews[1].setText(" / ");
		_rangeTextViews[1].setTextColor(&Theme::fg4);

		_rangeTextViews[2].setTextColor(&Theme::magenta1);

		// Reverse text view
		Theme::apply(&_reverseTextView);
		_reverseTextView.setVerticalAlignment(Alignment::center);
		_reverseTextView.setTextColor(&Theme::accent1);
		_reverseTextView.setText("REV");

		_reverseTextViewMargin.setMargin({ 10, 0, 0, 2 });
		_reverseTextView.setLayoutTransform(&_reverseTextViewMargin);

		_row += &_reverseTextView;

		fromSettings();
	}

	MotorType MotorEditor::getMotorType() const {
		return _motorType;
	}

	void MotorEditor::fromSettings() {
		const auto motorSettings = RC::getInstance().getSettings().motors.getByType(_motorType);
		const auto motorSettingsRange = motorSettings->max - motorSettings->min;

		// Range
		_rangeTextViews[0].setText(std::to_string(motorSettings->min + motorSettingsRange / 2));
		_rangeTextViews[2].setText(std::to_string(motorSettingsRange));

		// Reverse
		_reverseTextView.setVisible(motorSettings->reverse);
	}

	void MotorEditor::onClick() {
		Referencer::onClick();

		Theme::openDialog(new MotorEditorDialog(_dialogTitle, this));
	}

	MotorsSettingsPage::MotorsSettingsPage() {
		title.setText("Throttle");
		vaginoz(_throttleLeftTitle);
		vaginoz(_throttleRightTitle);

		// Ailerons
		Theme::apply(&_aileronsDivider);
		rows += &_aileronsDivider;

		penisula(_aileronsTitle);
		vaginoz(_aileronLeftTitle);
		vaginoz(_aileronRightTitle);

		// Flaps
		Theme::apply(&_flapsDivider);
		rows += &_flapsDivider;

		penisula(_flapsTitle);
		vaginoz(_flapLeftTitle);
		vaginoz(_flapRightTitle);

		// Tail
		Theme::apply(&_tailDivider);
		rows += &_tailDivider;

		penisula(_tailTitle);
		vaginoz(_tailLeftTitle);
		vaginoz(_tailRightTitle);

		// Nose
		Theme::apply(&_noseDivider);
		rows += &_noseDivider;

		penisula(_noseTitle);
		vaginoz(_cameraPitchTitle);
		vaginoz(_cameraYawTitle);
		vaginoz(_noseWheelTitle);

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	MotorsSettingsPage::~MotorsSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t MotorsSettingsPage::_scrollPosition = 0;

	void MotorsSettingsPage::penisula(TextView& titleTextView) {
		Theme::applyPageTitle(&titleTextView);

		rows += &titleTextView;
	}

	void MotorsSettingsPage::vaginoz(Titler& titler) {
		Theme::apply(&titler);
		rows += &titler;
	}
}