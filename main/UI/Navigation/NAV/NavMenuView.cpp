#include "UI/Navigation/NAV/NavMenuView.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	const Route* NavMenuView::_lastRoute = nullptr;
	
	void NavMenuView::setup() {
		MenuView::setup();
		
		setupButtons(_buttons.data(), _buttons.size(), &_lastRoute);
	}
}