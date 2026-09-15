#include "UI/Navigation/Settings/MFD/MFDSettingsPage.hpp"
#include "UI/Theme.hpp"
#include "Types/Generic.hpp"
#include "RC.hpp"

namespace pizda {
	MFDSettingsPage::MFDSettingsPage() {
		auto& rc = RC::getInstance();
		auto& settings = rc.getSettings();
		
		title.setText("PFD");

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

		// -------------------------------- Speed --------------------------------

		// Title
		setupPageTitle(&_speedTitle, "Speed ranges");

		// Ranges
		setupUint16TextField(_speedVS0, &settings.personalization.MFD.PFD.speedRanges.VS0);
		setupTitler(&_speedVS0Title);

		setupUint16TextField(_speedVFE, &settings.personalization.MFD.PFD.speedRanges.VFE);
		setupTitler(&_speedVFETitle);

		setupUint16TextField(_speedVNO, &settings.personalization.MFD.PFD.speedRanges.VNO);
		setupTitler(&_speedVNOTitle);

		setupUint16TextField(_speedVNE, &settings.personalization.MFD.PFD.speedRanges.VNE);
		setupTitler(&_speedVNETitle);

		// Divider
		Theme::apply(&_speedDivider);
		rows += &_speedDivider;

		// -------------------------------- ND --------------------------------

		setupPageTitle(&_NDTitle, "ND");

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

	MFDSettingsPage::~MFDSettingsPage() {
		_scrollPosition = scrollView.getVerticalPosition();
	}

	int32_t MFDSettingsPage::_scrollPosition = 0;

	void MFDSettingsPage::setupPageTitle(TextView* textView, const std::string_view text) {
		Theme::applyPageTitle(textView);
		textView->setText(text);
		rows += textView;
	}

	void MFDSettingsPage::setupTitler(Titler* titler) {
		Theme::apply(titler);
		rows += titler;
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

	void MFDSettingsPage::setupUint16TextField(TextField& textField, uint16_t* value) {
		setupAnyTextField(
			textField,
			std::to_string(*value),
			[&textField, value] {
				auto& rc = RC::getInstance();

				*value = std::max<uint16_t>(0, Text::tryParseInt32Or(textField.getText(), 0));
				rc.getSettings().personalization.writeLater();
			}
		);

		textField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowFractional);
	}
}
