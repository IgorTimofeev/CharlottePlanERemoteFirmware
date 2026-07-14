#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	RGB565Color Theme::bg1 { 0 };
	RGB565Color Theme::bg2 { 0 };
	RGB565Color Theme::bg3 { 0 };
	RGB565Color Theme::bg4 { 0 };
	RGB565Color Theme::bg5 { 0 };
	RGB565Color Theme::bg6 { 0 };
	RGB565Color Theme::bg7 { 0 };
	RGB565Color Theme::fg1 { 0 };
	RGB565Color Theme::fg2 { 0 };
	RGB565Color Theme::fg3 { 0 };
	RGB565Color Theme::fg4 { 0 };
	RGB565Color Theme::fg5 { 0 };
	RGB565Color Theme::fg6 { 0 };
	RGB565Color Theme::fg7 { 0 };
	RGB565Color Theme::accent1 { 0 };
	RGB565Color Theme::accent2 { 0 };
	RGB565Color Theme::good1 { 0 };
	RGB565Color Theme::good2 { 0 };
	RGB565Color Theme::bad1 { 0 };
	RGB565Color Theme::bad2 { 0 };
	RGB565Color Theme::bad3 { 0 };
	RGB565Color Theme::red { 0 };
	RGB565Color Theme::green1 { 0 };
	RGB565Color Theme::green2 { 0 };
	RGB565Color Theme::blue { 0 };
	RGB565Color Theme::magenta1 { 0 };
	RGB565Color Theme::magenta2 { 0 };
	RGB565Color Theme::ocean { 0 };
	RGB565Color Theme::yellow { 0 };
	RGB565Color Theme::ground1 { 0 };
	RGB565Color Theme::ground2 { 0 };
	RGB565Color Theme::sky1 { 0 };
	RGB565Color Theme::sky2 { 0 };

	void Theme::setup() {
		updateColorScheme();

		// Keyboard
		KeyboardController::setOnShow([](Keyboard* keyboard) {
			keyboard->setFont(&Theme::fontNormal);
			keyboard->setBackgroundColor(&Theme::bg1);

			keyboard->setKeyHeight(24);
			keyboard->setKeyCornerRadius(0);

			keyboard->setHorizontalKeyGap(1);
			keyboard->setVerticalKeyGap(1);

			keyboard->setDefaultKeyBackgroundColor(&Theme::bg3);
			keyboard->setDefaultKeyTextColor(&Theme::fg1);

			keyboard->setActionKeyBackgroundColor(&Theme::bg2);
			keyboard->setActionKeyTextColor(&Theme::fg1);

			keyboard->setDisabledKeyBackgroundColor(&Theme::bg2);
			keyboard->setDisabledKeyTextColor(&Theme::fg6);

			keyboard->setNumericLayoutBuilder([] {
				return new NumericKeyboardLayout();
			});

			keyboard->setCharactersLayoutBuilder([] {
				return new CharactersKeyboardLayout();
			});

			keyboard->setCyclicLayoutBuilders({
				[] {
					return new EnglishKeyboardLayout();
				}
			});
		});
	}

	void Theme::updateColorScheme() {
		if (RC::getInstance().getSettings().personalization.darkTheme) {
			bg1 = RGB888Color(0x000000).toRGB565BE();
			bg2 = RGB888Color(0x0C0C0C).toRGB565BE();
			bg3 = RGB888Color(0x1C1C1C).toRGB565BE();
			bg4 = RGB888Color(0x2C2C2C).toRGB565BE();
			bg5 = RGB888Color(0x3C3C3C).toRGB565BE();
			bg6 = RGB888Color(0x4C4C4C).toRGB565BE();
			bg7 = RGB888Color(0x5C5C5C).toRGB565BE();

			fg1 = RGB888Color(0xF0F0F0).toRGB565BE();
			fg2 = RGB888Color(0xCCCCCC).toRGB565BE();
			fg3 = RGB888Color(0x999999).toRGB565BE();
			fg4 = RGB888Color(0x888888).toRGB565BE();
			fg5 = RGB888Color(0x777777).toRGB565BE();
			fg6 = RGB888Color(0x666666).toRGB565BE();
			fg7 = RGB888Color(0x555555).toRGB565BE();

			accent1 = RGB888Color(0xffd200).toRGB565BE();
			accent2 = RGB888Color(0x997e53).toRGB565BE();
			good1 = RGB888Color(0x1db153).toRGB565BE();
			good2 = RGB888Color(0x28DA69).toRGB565BE();
			bad1 = RGB888Color(0xf24949).toRGB565BE();
			bad2 = RGB888Color(0x962828).toRGB565BE();
			bad3 = RGB888Color(0x4b1313).toRGB565BE();
			red = RGB888Color(0xff0000).toRGB565BE();
			green1 = RGB888Color(0x00FF00).toRGB565BE();
			green2 = RGB888Color(0x007F00).toRGB565BE();
			blue = RGB888Color(0x0000FF).toRGB565BE();
			magenta1 = RGB888Color(0xFF00FF).toRGB565BE();
			magenta2 = RGB888Color(0xAA00AA).toRGB565BE();
			ocean = RGB888Color(0x00FFFF).toRGB565BE();
			yellow = RGB888Color(0xffd200).toRGB565BE();
			ground1 = RGB888Color(0x97b838).toRGB565BE();
			ground2 = RGB888Color(0xdef2a2).toRGB565BE();
			sky1 = RGB888Color(0x317fcb).toRGB565BE();
			sky2 = RGB888Color(0xaed1f2).toRGB565BE();
		}
		else {
			bg1 = RGB888Color(0xF0F0F0).toRGB565BE();
			bg2 = RGB888Color(0xE0E0E0).toRGB565BE();
			bg3 = RGB888Color(0xD0D0D0).toRGB565BE();
			bg4 = RGB888Color(0xC0C0C0).toRGB565BE();
			bg5 = RGB888Color(0xB0B0B0).toRGB565BE();
			bg6 = RGB888Color(0xA0A0A0).toRGB565BE();
			bg7 = RGB888Color(0x000000).toRGB565BE();

			fg1 = RGB888Color(0x000000).toRGB565BE();
			fg2 = RGB888Color(0x111111).toRGB565BE();
			fg3 = RGB888Color(0x222222).toRGB565BE();
			fg4 = RGB888Color(0x333333).toRGB565BE();
			fg5 = RGB888Color(0x444444).toRGB565BE();
			fg6 = RGB888Color(0x555555).toRGB565BE();
			fg7 = RGB888Color(0x666666).toRGB565BE();

			accent1 = RGB888Color(0xffd200).toRGB565BE();
			accent2 = RGB888Color(0x997e53).toRGB565BE();
			good1 = RGB888Color(0x1db153).toRGB565BE();
			good2 = RGB888Color(0x28DA69).toRGB565BE();
			bad1 = RGB888Color(0xf24949).toRGB565BE();
			bad2 = RGB888Color(0x962828).toRGB565BE();
			bad3 = RGB888Color(0x4b1313).toRGB565BE();
			red = RGB888Color(0xff0000).toRGB565BE();
			green1 = RGB888Color(0x00FF00).toRGB565BE();
			green2 = RGB888Color(0x007F00).toRGB565BE();
			blue = RGB888Color(0x0000FF).toRGB565BE();
			magenta1 = RGB888Color(0xFF00FF).toRGB565BE();
			magenta2 = RGB888Color(0xAA00AA).toRGB565BE();
			ocean = RGB888Color(0x00FFFF).toRGB565BE();
			yellow = RGB888Color(0xffd200).toRGB565BE();
			ground1 = RGB888Color(0x97b838).toRGB565BE();
			ground2 = RGB888Color(0xdef2a2).toRGB565BE();
			sky1 = RGB888Color(0x317fcb).toRGB565BE();
			sky2 = RGB888Color(0xaed1f2).toRGB565BE();
		}
	}

	void Theme::apply(TextView* text) {
		text->setTextColor(&Theme::fg1);
		text->setFont(&Theme::fontNormal);
	}

	void Theme::applyDescription(TextView* text) {
		text->setTextColor(&Theme::fg4);
		text->setFont(&Theme::fontNormal);
	}

	void Theme::applyPageTitle(TextView* text) {
		text->setTextColor(&Theme::fg1);
		text->setFont(&Theme::fontNormal);
		text->setFontScale(2);
	}

	void Theme::applyElementTitle(TextView* text) {
		text->setFont(&Theme::fontNormal);
		text->setTextColor(&Theme::fg4);
	}

	void Theme::applyPrimary(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&Theme::accent1);
		button->setDefaultTextColor(&Theme::bg1);

		button->setActiveBackgroundColor(&Theme::accent2);
		button->setActiveTextColor(&Theme::bg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::applySecondary(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&Theme::bg3);
		button->setDefaultTextColor(&Theme::fg3);

		button->setActiveBackgroundColor(&Theme::bg5);
		button->setActiveTextColor(&Theme::fg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::applyCritical(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&Theme::bad1);
		button->setDefaultTextColor(&Theme::fg1);

		button->setActiveBackgroundColor(&Theme::bad3);
		button->setActiveTextColor(&Theme::fg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::applyPlaceholder(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(nullptr);
		button->setDefaultBorderColor(&Theme::fg5);
		button->setDefaultTextColor(&Theme::fg5);

		button->setActiveBackgroundColor(nullptr);
		button->setActiveBorderColor(&Theme::fg1);
		button->setActiveTextColor(&Theme::fg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::apply(Switch* sw) {
		sw->setSize(Size(38, 16));
		sw->setCornerRadius(sw->getSize().getHeight() / 2);

		sw->setTrackColor(&Theme::bg3);
		sw->setActiveColor(&Theme::accent1);

		sw->setHandleColor(&Theme::fg1);

		sw->setAnimationDuration(250'000);
	}

	void Theme::apply(Slider* slider) {
		slider->setMinimumValue(0);
		slider->setMaximumValue(1);

		// Track
		slider->setTrackSize(5);
		slider->setTrackCornerRadius(slider->getTrackSize() / 2);
		slider->setTrackColor(&Theme::bg3);

		// Fill
		slider->setFillColor(&Theme::accent1);

		// Handle
		slider->setHandleSize({ 2, 10 });
		slider->setHandleCornerRadius(0);
		slider->setHandleColor(&Theme::fg1);

		// Tick
		slider->setTickCount(10);
		slider->setBigTickStep(5);
		slider->setTickOffset(0);
		slider->setBigTickLineLength(5);
		slider->setSmallTickLineLength(3);
		slider->setTickColor(&Theme::fg6);

		slider->setTickLabelFont(&Theme::fontNormal);
		slider->setTickLabelOffset(1);

		slider->setTickLabelBuilder(Slider::percentTickLabelBuilder);
	}

	void Theme::apply(ProgressBar* progressBar) {
		progressBar->setHeight(5);
		progressBar->setCornerRadius(2);
		progressBar->setTrackColor(&Theme::bg3);
		progressBar->setFillColor(&Theme::accent1);
	}

	void Theme::apply(ScrollView* scrollView) {
		scrollView->setScrollBarSize(3);
		scrollView->setScrollBarCornerRadius(1);
		scrollView->setScrollBarOffset(3);
		scrollView->setScrollBarThumbColor(&Theme::bg3);
	}

	void Theme::apply(TextField* textField) {
		textField->setHeight(elementHeight);
		textField->setCornerRadius(cornerRadius);
		textField->setTextMargin(10);

		textField->setDefaultBackgroundColor(&Theme::bg3);
		textField->setFocusedBackgroundColor(&Theme::bg4);

		textField->setDefaultTextColor(&Theme::fg1);
		textField->setFocusedTextColor(&Theme::fg1);

		textField->setDefaultBorderColor(&Theme::bg4);
		textField->setFocusedBorderColor(&Theme::accent1);

		textField->setPlaceholderColor(&Theme::fg5);
		textField->setCursorColor(&Theme::accent1);

		textField->setFont(&Theme::fontNormal);
	}

	void Theme::apply(Divider* divider) {
		divider->setOrientation(Orientation::horizontal);
		divider->setHeight(5);
		divider->setFillColor(&Theme::bg4);
	}

	void Theme::apply(Badge* badge) {
		badge->setHeight(14);
		badge->setCornerRadius(badge->getSize().getHeight() / 2);
		badge->setTextMargin(Margin(5, 0, 5, 0));

		badge->setFillColor(&Theme::bad1);
		badge->setTextColor(&Theme::fg1);

		badge->setFont(&Theme::fontSmall);
	}
}