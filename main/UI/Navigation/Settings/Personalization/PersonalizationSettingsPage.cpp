#include "UI/Navigation/Settings/Personalization/PersonalizationSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	PersonalizationSettingsPage::PersonalizationSettingsPage() {
		auto& rc = RC::getInstance();
		auto& settings = rc.getSettings();

		// ----------------------------- General -----------------------------

		title.setText("Personalization");

		// Dark theme
		Theme::apply(&_generalDarkTheme);

		_generalDarkTheme.switch_.setActive(settings.personalization.darkTheme);

		_generalDarkTheme.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.darkTheme = _generalDarkTheme.switch_.isActive();
			settings.personalization.writeLater();

			Theme::updateColorScheme();
		});

		rows += &_generalDarkTheme;

		// Audio feedback
		Theme::apply(&_generalAudioFeedback);

		_generalAudioFeedback.switch_.setActive(settings.personalization.audioFeedback);
		
		_generalAudioFeedback.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.audioFeedback = _generalAudioFeedback.switch_.isActive();
			settings.personalization.writeLater();
		});
		
		rows += &_generalAudioFeedback;
		
		// Interpolation
		Theme::apply(&_generalDataInterpolation);

		_generalDataInterpolation.switch_.setActive(settings.personalization.dataInterpolation);
		
		_generalDataInterpolation.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.dataInterpolation = _generalDataInterpolation.switch_.isActive();
			settings.personalization.writeLater();
		});
		
		rows += &_generalDataInterpolation;

		// Debug overlay
		Theme::apply(&_generalDebugOverlay);

		_generalDebugOverlay.switch_.setActive(settings.personalization.debugOverlay);

		_generalDebugOverlay.switch_.setOnIsActiveChanged([this, &rc, &settings] {
			settings.personalization.debugOverlay = _generalDebugOverlay.switch_.isActive();
			settings.personalization.writeLater();

			rc.updateDebugOverlayVisibility();
		});

		rows += &_generalDebugOverlay;

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	PersonalizationSettingsPage::~PersonalizationSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t PersonalizationSettingsPage::_scrollPosition = 0;
}