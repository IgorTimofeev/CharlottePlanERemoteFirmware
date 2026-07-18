#include "UI/Navigation/Settings/Personalization/PersonalizationSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	PersonalizationSettingsPage::PersonalizationSettingsPage() {
		auto& rc = RC::getInstance();
		auto& settings = rc.getSettings();

		// ----------------------------- General -----------------------------

		title.setText("General");

		// Dark theme
		Theme::apply(&_darkTheme);

		_darkTheme.switch_.setActive(settings.personalization.darkTheme);

		_darkTheme.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.darkTheme = _darkTheme.switch_.isActive();
			settings.personalization.writeLater();

			Theme::updateColorScheme();
		});

		rows += &_darkTheme;

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
		
		// Divider
		Theme::apply(&_generalDivider);
		rows += &_generalDivider;
		
		// -------------------------------- PFD --------------------------------

		Theme::applyPageTitle(&_PFDTitle);
		_PFDTitle.setText("PFD");
		rows += &_PFDTitle;
				
		// FOV
		Theme::apply(&_PFDFOVSlider);
		_PFDFOVSlider.setMinimumValue(20);
		_PFDFOVSlider.setMaximumValue(120);
		_PFDFOVSlider.setValue(settings.personalization.MFD.PFD.FOV);

		_PFDFOVSlider.setTickCount(10);
		_PFDFOVSlider.setBigTickStep(5);
		_PFDFOVSlider.setTickLabelBuilder(Slider::int32TickLabelBuilder);

		_PFDFOVSlider.setOnValueChanged([this, &settings] {
			settings.personalization.MFD.PFD.FOV = _PFDFOVSlider.getValue();
			settings.personalization.writeLater();
		});

		Theme::apply(&_PFDFOVTitle);
		rows += &_PFDFOVTitle;

		// Waypoint labels
		Theme::apply(&_PFDWaypointLabels);

		_PFDWaypointLabels.switch_.setActive(settings.personalization.MFD.PFD.waypointLabels);

		_PFDWaypointLabels.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.MFD.PFD.waypointLabels = _PFDWaypointLabels.switch_.isActive();
			settings.personalization.writeLater();
		});

		rows += &_PFDWaypointLabels;

		// Divider
		Theme::apply(&_PFDDivider);
		rows += &_PFDDivider;

		// -------------------------------- ND --------------------------------

		Theme::applyPageTitle(&_NDTitle);
		_NDTitle.setText("ND");
		rows += &_NDTitle;

		// Earth grid
		Theme::apply(&_NDEarthGrid);

		_NDEarthGrid.switch_.setActive(settings.personalization.MFD.ND.earth);
		
		_NDEarthGrid.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.MFD.ND.earth = _NDEarthGrid.switch_.isActive();
			settings.personalization.writeLater();
		});
		
		rows += &_NDEarthGrid;

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	PersonalizationSettingsPage::~PersonalizationSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t PersonalizationSettingsPage::_scrollPosition = 0;
}