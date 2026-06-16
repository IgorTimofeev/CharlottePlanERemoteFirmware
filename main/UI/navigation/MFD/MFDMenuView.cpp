#include "MFDMenuView.h"

#include "UI/theme.h"
#include "rc.h"
#include "settings/settings.h"

#include "UI/navigation/routes.h"
#include "MFDPage.h"

namespace pizda {
	// Top
	MFDMenuViewTopToolbarButton::MFDMenuViewTopToolbarButton(const Image* image, const std::string_view text, const PersonalizationSettingsMFDToolbarMode mode) : MenuViewButton(image, text), _mode(mode) {
		setToggle(true);
		setActive(RC::getInstance().getSettings().personalization.MFD.toolbars.topMode == mode);
	}

	void MFDMenuViewTopToolbarButton::onClick() {
		MenuViewButton::onClick();

		auto& settings = RC::getInstance().getSettings();
		settings.personalization.MFD.toolbars.topMode = settings.personalization.MFD.toolbars.topMode == _mode ? PersonalizationSettingsMFDToolbarMode::none : _mode;
		settings.personalization.writeLater();

		// Deselecting other buttons
		const auto menuView = reinterpret_cast<MFDMenuView*>(getMenuView());

		for (const auto modeButton : menuView->topToolbarButtons)
			modeButton->setActive(modeButton->_mode == settings.personalization.MFD.toolbars.topMode);

		MFDPage::getInstance()->fromSettings();
	}

	MFDMenuView::MFDMenuView() {
		for (const auto button : topToolbarButtons) {
			*this += button;
		}
	}

	const Route* MFDMenuView::getRoute() {
		return &Routes::MFD;
	}
}