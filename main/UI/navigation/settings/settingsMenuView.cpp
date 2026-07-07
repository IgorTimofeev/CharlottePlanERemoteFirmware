#include "UI/Navigation/Settings/SettingsMenuView.hpp"

#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	const Route* SettingsMenuView::_lastRoute = nullptr;
	
	void SettingsMenuView::setup() {
		MenuView::setup();
		
		setupButtons(_buttons.data(), _buttons.size(), &_lastRoute);
	}
}