#include "motorsSettingsPage.h"

#include <optional>

#include "rc.h"
#include "UI/theme.h"

namespace pizda {
	MotorEditor::MotorEditor(const std::string_view title, const MotorType type) : Titler(title), _type(type) {
		const auto settings = RC::getInstance().getSettings().motors.getByType(type);

		constexpr static uint8_t buttonSideMargin = Theme::cornerRadius + 1;

		// Main row
		*this += &_mainLayout;

		// Confirm
		Theme::applyPrimary(&_confirm);
		_confirm.setWidth(24);
		_confirm.setHorizontalAlignment(Alignment::end);
		_confirm.setContentMargin(Margin(buttonSideMargin - 1, 0, 0, 0));
		_confirm.setFont(&Theme::fontSmall);
		_confirm.setText(">");

		_confirm.setOnClick([this] {
			auto& rc = RC::getInstance();

			rc.getRemoteData().motorSettings.type = _type;
			rc.getRemoteData().motorSettings.settings.min = static_cast<uint16_t>(StringUtils::tryParseInt32Or(_min.getText(), 1'000));
			rc.getRemoteData().motorSettings.settings.max = static_cast<uint16_t>(StringUtils::tryParseInt32Or(_max.getText(), 2'000));
			rc.getRemoteData().motorSettings.settings.reverse = _reverse.isActive();
			rc.getRemoteData().motorSettings.settings.sanitize();

			*rc.getSettings().motors.getByType(_type) = rc.getRemoteData().motorSettings.settings;
			rc.getSettings().motors.writeLater();

			rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::motors);
		});

		_mainLayout += &_confirm;

		// Reverse
		Theme::applySecondary(&_reverse);
		_reverse.setWidth(_confirm.getSize().getWidth() + 1);
		_reverse.setMargin(Margin(0, 0, _confirm.getSize().getWidth() - buttonSideMargin, 0));
		_reverse.setContentMargin(Margin(buttonSideMargin - 1, 0, 0, 0));
		_reverse.setHorizontalAlignment(Alignment::end);

		_reverse.setDefaultBackgroundColor(&Theme::bg2);
		_reverse.setDefaultTextColor(&Theme::fg4);

		_reverse.setActiveBackgroundColor(&Theme::bg6);
		_reverse.setActiveTextColor(&Theme::fg1);
		
		_reverse.setFont(&Theme::fontSmall);
		_reverse.setText("<>");
		_reverse.setToggle(true);
		
		_reverse.setActive(settings->reverse);
		_mainLayout += &_reverse;

		// Min / max
		_minMaxRow.setOrientation(Orientation::horizontal);
		_minMaxRow.setGap(8);
		_minMaxRow.setMargin(Margin(0, 0, _confirm.getSize().getWidth() + _reverse.getSize().getWidth() - buttonSideMargin * 2, 0));
		_mainLayout += &_minMaxRow;

		// Min
		addTextField(_min, settings->min);
		
		// Max
		addTextField(_max, settings->max);
	}

	MotorsSettingsPage::MotorsSettingsPage() {
		title.setText("Throttle");
		vaginoz(&_throttleLeft);
		vaginoz(&_throttleRight);
		rows += &_throttleSeparator;

		penisula(&_aileronsTitle);
		vaginoz(&_aileronLeft);
		vaginoz(&_aileronRight);
		rows += &_aileronsSeparator;

		penisula(&_flapsTitle);
		vaginoz(&_flapLeft);
		vaginoz(&_flapRight);
		rows += &_flapsSeparator;

		penisula(&_tailTitle);
		vaginoz(&_tailLeft);
		vaginoz(&_tailRight);
		rows += &_tailSeparator;

		penisula(&_noseTitle);
		vaginoz(&_cameraPitch);
		vaginoz(&_cameraYaw);
		vaginoz(&_noseWheel);

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	MotorsSettingsPage::~MotorsSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t MotorsSettingsPage::_scrollPosition = 0;

	void MotorsSettingsPage::penisula(TextView* text) {
		Theme::applyPageTitle(text);

		rows += text;
	}

	void MotorsSettingsPage::vaginoz(MotorEditor* motorEditor) {
		rows += motorEditor;
	}
}