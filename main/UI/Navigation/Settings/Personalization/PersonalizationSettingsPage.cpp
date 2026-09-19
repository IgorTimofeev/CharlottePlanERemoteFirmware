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

		// -------------------------------- PFD --------------------------------

		// Divider
		Theme::apply(&_PFDDivider);
		rows += &_PFDDivider;

		// Title
		Theme::applyPageTitle(&_PFDTitle);
		rows += &_PFDTitle;

		// Waypoint labels
		Theme::apply(&_PFDWaypointLabels);

		_PFDWaypointLabels.switch_.setActive(settings.personalization.MFD.PFD.waypointLabels);

		_PFDWaypointLabels.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.MFD.PFD.waypointLabels = _PFDWaypointLabels.switch_.isActive();
			settings.personalization.writeLater();
		});

		rows += &_PFDWaypointLabels;

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

		// Speed tape
		setupUint8TextField(_speedTapeMinorTickStep, &settings.personalization.MFD.PFD.speed.minorTickStepKt);
		Theme::apply(&_speedTapeMinorTickStepTitle);
		rows += &_speedTapeMinorTickStepTitle;

		setupUint8TextField(_speedTapeMajorTickStep, &settings.personalization.MFD.PFD.speed.majorTickStepKt);
		Theme::apply(&_speedTapeMajorTickStepTitle);
		rows += &_speedTapeMajorTickStepTitle;

		// Altitude tape
		setupUint8TextField(_altitudeTapeMinorTickStep, &settings.personalization.MFD.PFD.altitude.minorTickStepFt);
		Theme::apply(&_altitudeTapeMinorTickStepTitle);
		rows += &_altitudeTapeMinorTickStepTitle;

		setupUint8TextField(_altitudeTapeMajorTickStep, &settings.personalization.MFD.PFD.altitude.majorTickStepFt);
		Theme::apply(&_altitudeTapeMajorTickStepTitle);
		rows += &_altitudeTapeMajorTickStepTitle;

		// -------------------------------- N/D --------------------------------

		// Divider
		Theme::apply(&_NDDivider);
		rows += &_NDDivider;

		// Title
		Theme::applyPageTitle(&_NDTitle);
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

	void PersonalizationSettingsPage::setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter) {
		Theme::apply(&textField);
		textField.setText(text);

		textField.setOnInput([onEnter](const Key key, std::optional<std::string_view>) {
			if (key != Key::enter)
				return;

			onEnter();
		});
	}

	void PersonalizationSettingsPage::setupUint8TextField(TextField& textField, uint8_t* value) {
		setupAnyTextField(
			textField,
			std::to_string(*value),
			[&textField, value] {
				auto& rc = RC::getInstance();

				*value = std::max<uint8_t>(0, Text::tryParseInt32Or(textField.getText(), 0));
				rc.getSettings().personalization.writeLater();
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}
}