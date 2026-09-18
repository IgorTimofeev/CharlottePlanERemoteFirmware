#include "UI/Navigation/Settings/MFD/MFDSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "Types/Generic.hpp"
#include "RC.hpp"

namespace pizda {
	MFDSettingsPage::MFDSettingsPage() {
		auto& rc = RC::getInstance();
		auto& settings = rc.getSettings();
		
		title.setText("MFD");

		// Waypoint labels
		Theme::apply(&_PFDWaypointLabels);

		_PFDWaypointLabels.switch_.setActive(settings.personalization.MFD.PFD.waypointLabels);

		_PFDWaypointLabels.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.MFD.PFD.waypointLabels = _PFDWaypointLabels.switch_.isActive();
			settings.personalization.writeLater();
		});

		rows += &_PFDWaypointLabels;

		// Earth grid
		Theme::apply(&_NDEarthGrid);

		_NDEarthGrid.switch_.setActive(settings.personalization.MFD.ND.earth);

		_NDEarthGrid.switch_.setOnIsActiveChanged([this, &settings] {
			settings.personalization.MFD.ND.earth = _NDEarthGrid.switch_.isActive();
			settings.personalization.writeLater();
		});

		rows += &_NDEarthGrid;

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

		// Divider
		Theme::apply(&_PFDDivider);
		rows += &_PFDDivider;

		// -------------------------------- Speed tape --------------------------------

		// Title
		setupPageTitle(&_speedTapeTitle, "Speed tape");

		// Tick steps
		setupUint8TextField(_speedTapeMinorTickStep, &settings.personalization.MFD.PFD.speed.minorTickStepKt);
		Theme::apply(&_speedTapeMinorTickStepTitle);
		rows += &_speedTapeMinorTickStepTitle;

		setupUint8TextField(_speedTapeMajorTickStep, &settings.personalization.MFD.PFD.speed.majorTickStepKt);
		Theme::apply(&_speedTapeMajorTickStepTitle);
		rows += &_speedTapeMajorTickStepTitle;

		// Divider
		Theme::apply(&_speedTapeDivider);
		rows += &_speedTapeDivider;

		// -------------------------------- Altitude tape --------------------------------

		// Title
		setupPageTitle(&_altitudeTapeTitle, "Altitude tape");

		// Tick steps
		setupUint8TextField(_altitudeTapeMinorTickStep, &settings.personalization.MFD.PFD.altitude.minorTickStepFt);
		Theme::apply(&_altitudeTapeMinorTickStepTitle);
		rows += &_altitudeTapeMinorTickStepTitle;

		setupUint8TextField(_altitudeTapeMajorTickStep, &settings.personalization.MFD.PFD.altitude.majorTickStepFt);
		Theme::apply(&_altitudeTapeMajorTickStepTitle);
		rows += &_altitudeTapeMajorTickStepTitle;

		// Initialization
		scrollView.setVerticalPosition(_scrollPosition);
	}

	MFDSettingsPage::~MFDSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t MFDSettingsPage::_scrollPosition = 0;

	void MFDSettingsPage::setupPageTitle(TextView* textView, const std::string_view text) {
		Theme::applyPageTitle(textView);
		textView->setText(text);
		rows += textView;
	}

	void MFDSettingsPage::setupAnyTextField(TextField& textField, const std::string_view& text, const std::function<void()>& onEnter) {
		Theme::apply(&textField);
		textField.setText(text);

		textField.setOnInput([onEnter](const Key key, std::optional<std::string_view>) {
			if (key != Key::enter)
				return;

			onEnter();
		});
	}

	void MFDSettingsPage::setupUint8TextField(TextField& textField, uint8_t* value) {
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
